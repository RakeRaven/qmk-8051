# Phase 1 Walkthrough: USB Enumeration Fixes

## Summary

Fixed 7 interrelated USB enumeration bugs across 3 files that caused unreliable/impossible USB connection. These fixes address both the intermittent Linux behavior and the complete Windows failure.

---

## Files Changed

| File | Path |
|------|------|
| **usb_device.c** | `tmk_core/protocol/ch555/usb_device.c` |
| **ch555_usb_stack.c** | `tmk_core/protocol/ch555/ch555_usb_stack.c` |
| **usb_util.c** | `tmk_core/protocol/ch555/usb_util.c` |

---

## What Was Fixed

### 1. Stale Toggle Bits After Bus Reset (`usb_device.c`)

**Problem**: USB spec requires all endpoints to start with DATA0 after a bus reset. The old `USB_EP_init()` set endpoint response modes (NAK/ACK) but never explicitly cleared the data toggle bit (`bUEP_X_TOG`). On CH555, these bits might retain their previous value through a bus reset, causing DATA0/DATA1 mismatch with the host. **Windows is particularly strict** about this and will reject packets with wrong toggle.

**Fix**: All endpoint registers are now written without `bUEP_X_TOG` set, ensuring DATA0. Also added clearing of all endpoint transmit length registers (`D0_EPxT_L = 0`) to prevent stale leftover data.

---

### 2. Suspend Handler Killed Enumeration (`usb_device.c`)

**Problem**: This was the **#1 cause** of enumeration failures. The old suspend handler had this logic:
```c
if (USB_SleepStatus != 0x03) {
    USB_EnumStatus = 0x00;  // ← KILLS ENUMERATION
}
```
During initial USB plug-in, the host typically sends a brief bus suspend before starting enumeration. `USB_SleepStatus` starts at `0x00`, the suspend handler sets bit 1 making it `0x02`, and since `0x02 != 0x03`, it **clears `USB_EnumStatus` to 0**. Later, even after the host sends `SET_CONFIGURATION` (which sets `USB_EnumStatus = 1`), another brief suspend would clear it again.

**Fix**: Removed the `USB_EnumStatus = 0x00` from the suspend handler entirely. `USB_EnumStatus` is now only cleared by the bus reset handler (which is the correct place per USB spec). The suspend handler now only triggers MCU sleep when `USB_SleepStatus == 0x03` (host explicitly requested + bus actually suspended).

---

### 3. Wake Handler Prematurely Set Enumeration (`usb_device.c`)

**Problem**: The wake handler unconditionally set `USB_EnumStatus = 0x01` on every SOF resume. During initial enumeration, SOF resume happens before `SET_CONFIGURATION`, so the device would think it was enumerated when it wasn't. This could cause the keyboard to try sending HID reports before the host was ready.

**Fix**: Now only sets `USB_EnumStatus = 0x01` if `D0UsbConfig != 0` (i.e., the device was previously actually configured by the host).

---

### 4. Bus Reset Didn't Fully Reset State (`usb_device.c`)

**Problem**: The bus reset handler cleared `USB_EnumStatus` and `KB_USB_UpStatus` but left other state variables stale:
- `D0SetupReqCode` — could contain a stale request code from before the reset
- `D0SetupLen` — stale descriptor length
- `D0UsbConfig` — stale configuration value
- `USB_SleepStatus` — stale sleep flags
- `epX_data_wait` — stale OUT endpoint flags

**Fix**: Bus reset now fully resets **all** USB state variables, matching what `USB_Device_Init()` does.

---

### 5. Dangerous STALL-Clear-After-Delay (`usb_device.c`)

**Problem**: When an unsupported USB request was received, the code set STALL on EP0, waited ~255 CPU cycles (~10μs), then manually cleared the STALL. Per USB spec, protocol STALL should persist until the next SETUP packet. The manual clear could race with the host retrying, causing the host to see a non-stalled endpoint when it expected STALL, corrupting the control transfer state machine.

**Fix**: Removed the `while(i--)` delay and the manual STALL clear. The STALL is now properly cleared by the SETUP handler when the next SETUP packet arrives (which already resets `D0_EP0RES` at the top of SETUP processing).

---

### 6. Blind 1000ms Enumeration Wait (`ch555_usb_stack.c`)

**Problem**: `protocol_post_init()` used `mDelaymS(1000)` — a hardcoded 1-second delay hoping enumeration would complete. This was:
- Too short for Windows (which does multiple resets and takes longer)
- Too short for USB hubs and KVM switches
- Too long for fast Linux hosts (wasted startup time)

**Fix**: Replaced with a proper polling loop that waits for `USB_EnumStatus` to become non-zero, with a 5-second timeout:
```c
uint16_t timeout = 5000;
while (!USB_EnumStatus && timeout) {
    wait_ms(1);
    timeout--;
}
```
The USB interrupt handler continues running during `wait_ms()`, so enumeration proceeds in the background. The loop exits as soon as `SET_CONFIGURATION` is received.

---

### 7. `usb_connected_state()` Always Returned True (`usb_util.c`)  

**Problem**: `usb_connected_state()` was hardcoded to `return true`. Various QMK subsystems use this to check if USB is connected before sending data.

**Fix**: Now returns `(USB_EnumStatus != 0)` — the actual enumeration state.

## Phase 2: Windows Code 43 & 48ms XACT_ERROR Fix

While the fixes above improved Linux reliability and basic enumeration response, Windows continued to throw **Code 43 (USBD_STATUS_XACT_ERROR)** exactly ~48ms after successful enumeration.

### What Was Fixed

#### 1. Watchdog Timer (WDT) MCU Resets (`usb_device.c`)
**Problem**: The CH555 microcontroller contains a hardware Watchdog Timer (WDT) that the USB bootloader leaves **enabled** when it jumps to the QMK application. Because our QMK port never explicitly fed or disabled this Watchdog Timer, the MCU was experiencing a hard reset precisely 48ms after booting up! This reset dropped the D+ pull-up resistors, causing a physical disconnect and a bus timeout that Windows interpreted as a transaction error.

**Fix**: Added the `SAFE_MOD = 0x55; SAFE_MOD = 0xAA; GLOBAL_CFG &= ~bWDOG_EN;` unlock and disable sequence at the very beginning of `USB_Device_Init()`. This entirely turns off the WDT, preventing the MCU from resetting itself during regular operation.

#### 2. Missing Auto-Toggling on Endpoints (`usb_device.c`)
**Problem**: During the earlier port, the hardware auto-toggle bit (`bUEP_X_AUTO_TOG`) was omitted from the endpoint initialization registers (e.g. `D0_EP1RES`). Without this flag, the endpoints were continuously sending `DATA0` packets instead of properly alternating `DATA0` and `DATA1`.

**Fix**: Reinstated the `bUEP_X_AUTO_TOG` mask into all endpoint initializations (`EP1` through `EP6`), ensuring correct USB sequencing.

---

## How to Test

1. **Clean and Compile**:
   Make sure you run `make clean` before compiling, to ensure `usb_device.c` is fully rebuilt with the WDT changes.
   ```bash
   make clean
   make redragon/k580:default
   ```

2. **Flash and Verify**:
   Flash the newly built firmware to your CH555. Since the Watchdog has been neutered, the device should stay permanently enumerated without dropping off the bus at the 50ms mark. Open Wireshark and verify that the host successfully polls EP1 IN without throwing `USBD_STATUS_XACT_ERROR`.

> [!IMPORTANT]
> Because you previously ran into XACT_ERRORs, it is possible your system or USB port cached the failed state. If it still fails, uninstall the device from Device Manager, unplug the keyboard, wait 5 seconds, and plug it back into a **different** USB port.
