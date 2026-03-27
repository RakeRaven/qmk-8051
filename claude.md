# Project Context — QMK CH555 Port (Redragon K580 Vata)

## About the User
- Working on a custom QMK firmware port for the **Redragon K580 Vata** full-size keyboard
- The keyboard is physically on their desk and being actively developed/tested
- Keyboard directory: `keyboards/redragon/k580/`

---

## Hardware Specifications

### Microcontroller — WCH CH555

From the official datasheet:

- **ROM**: 64KB total Flash-ROM. Split as: 60KB program space + 1KB Data-Flash (EEPROM) + 3KB bootloader/ISP at 0xF400
- **EEPROM (Data-Flash)**: 1KB at 0xF000–0xF3FF, divided into **16 independent 64-byte blocks**. Supports single-byte read, single-byte write, block write (1–64B), block erase (64B). **~100K erase/program cycles** in typical environment.
- **OTP**: 32 bytes one-time programmable area (4-byte dword read, single-byte write)
- **IRAM**: 256-byte internal iRAM (fast temp storage and stack)
- **XRAM**: 8KB on-chip xRAM (0x0000–0x1FFF, large temp storage and DMA)
- **CPU speed**: 48MHz (configured via `CfgFsys()`, internal PLL × external 24MHz)
- **Bootloader**: CH55x USB ISP bootloader at 0xF400, address `lcall #0xF400`
- **Package**: LQFP48 (up to 45 GPIO), LQFP64 (up to 58 GPIO)

### Peripherals (from datasheet)
- **USB**: Built-in USB composite device controller. USB device-hub + 3 HID sub-devices, 24 USB endpoints. USB 2.0 Full-Speed (12Mbps), 64-byte packets, built-in FIFO, supports DMA.
- **RGB LED**: 3×8 channels PWM + 1/16 dynamic scanning. Max 384 monochrome LEDs or 128 RGB groups. 8-bit brightness PWM (256 grayscale levels), 24-bit color (16.7M colors). Dedicated DMA from Flash-ROM or xRAM.
- **Timers**: 3× 16-bit timers (T0, T1, T2, standard MCS51 + T2 with 2-channel signal capture)
- **UART**: 2× UARTs. UART0 = standard MCS51, UART1 = with built-in baud rate register
- **SPI**: 2× SPIs with FIFO (~Fsys/2 max). SPI0 = master/slave, SPI1 = master only
- **I2C**: I2CS — I2C slave only (NOT master), with DMA, designed for 24C EEPROM emulation
- **ADC**: 14-channel 12-bit ADC
- **GPIO**: Up to 45 pins (LQFP48), quasi-bidirectional / high-Z input / push-pull / open-drain
- **Interrupts**: 14 sources (6 standard MCS51 + 8 extended: SPI0, USB, ADC, UART1, LED/I2C, GPIO, WDOG)
- **Watch-Dog**: 8-bit presettable WDOG, timing interrupt
- **Reset**: 5 types: power-on, low-voltage, software (bSW_RESET), watchdog overflow, external RST# pin
- **Sleep**: Low-power sleep, wake by USB, UART0, UART1, SPI0, GPIO
- **Clock**: Built-in 24MHz oscillator, external crystal optional, internal PLL → USB clock + Fsys
- **Power**: Built-in 5V→3.3V LDO, supports 2.8V–6V input, built-in DC-DC controller

> [!IMPORTANT]
> **I2C is slave-only** on the CH555. There is NO I2C master. External I2C devices (like EEPROM ICs or IS31FL LED drivers) CANNOT be driven by the CH555. The built-in I2CS is designed so the CH555 *acts as* an I2C EEPROM (24C format) for a host. LED drivers must use SPI or native LED controller.

---

## Keyboard: Redragon K580 Vata

- **Form factor**: Full-size, 104 working switches
- **Layout**: Standard US ANSI

### Physical PCB structure:
- **Main PCB**: Rows 0–5, Columns 0–17 (18 columns = COM0 through COM17 on the CH555 LED controller)
- **2nd daughter board**: Row 6
- **3rd daughter board**: Row 7 (assumed, needs confirmation)

### Matrix config in firmware:
```c
#define MATRIX_ROWS 7      // Rows 0–6 (plus row 7 guessed for 3rd board)
#define MATRIX_COLS 18     // Columns 0–17
#define DIODE_DIRECTION ROW2COL

#define MATRIX_ROW_PINS { PORT4_0, PORT4_1, PORT4_2, PORT4_3, PORT4_4, PORT4_5, PORT4_6 }
#define MATRIX_COL_PINS { PORT0_0, PORT0_1, PORT0_2, PORT0_3, PORT0_4, PORT0_5, PORT0_6, PORT0_7, \
                          PORT3_0, PORT3_1, PORT3_2, PORT3_3, PORT3_4, PORT3_5, PORT3_6, PORT3_7, \
                          PORT7_0, PORT7_1 }
```

### Encoder:
- 1× rotary encoder — **pins unknown**, need to trace the PCB

### LEDs:
- **120 RGB LEDs** (per-key, main layout)
- **14 single-color LEDs** (indicators/underglow/numpad)
- **No external LED driver IC** — driven by CH555's built-in LED controller directly via hardware DMA
- PCB wiring: COMs are columns 0–17 (matching the 18 matrix columns)

---

## CH555 Built-in RGB LED Controller

All registers are documented in `lib/ch555/ch555.h`. Key summary:

| Register | Address | Purpose |
|----------|---------|---------|
| `LED_COMMON` | 0xA6 SFR | Select active COM line (0–31). `0xFF` = all inactive. |
| `LED_PWM_OE` | 0xA7 SFR | Bit mask: enable each of 8 PWM output channels |
| `LED_DMA` | 0xC6/C7 SFR16 | XRAM address of DMA buffer (auto-increments during scan) |
| `LED_STATUS` | 0xF7 SFR | Inhibit flag (`bLED_INHIB`), interrupt flag (`bLED_IF`), intensity count |
| `LED_CTRL` | 0x21D1 XSFR | `bLED_EN`, `bLED_RED_EN`, `bLED_GREEN_EN`, `bLED_BLUE_EN`, `bLED_PWM_INHIB`, `bLED_IE_INHIB` |
| `LED_CYCLE` | 0x21D2 XSFR | Clock divisor, PWM cycle depth (64/128/256 levels) |
| `LED_FRAME` | 0x21D3 XSFR | Inhibit timer, PWM repeat count |
| `LED_INT_ADJ` | 0x21D8 XSFR | Global intensity adjustment |
| `LED_RED_ADJ` | 0x21D9 XSFR | Red channel adjustment |
| `LED_GRE_ADJ` | 0x21DA XSFR | Green channel adjustment |
| `LED_BLU_ADJ` | 0x21DB XSFR | Blue channel adjustment |

### DMA Buffer Layout (from EVT demo — rgbled.c)
```c
// 128 groups × 4 bytes each = 512 bytes in XRAM
UINT8X RGBdataBuffer[128][4];
// [i][0] = intensity byte (global dimming for group i)
// [i][1] = R (red PWM value)
// [i][2] = G (green PWM value)
// [i][3] = B (blue PWM value)
```

### LED Init Sequence (from EVT demo — InitRGBLED)
```c
// 1. Set all GPIO ports high (inverted output — low = active for sink current)
P4 = P2 = P1 = 0xFF;  // R/G/B PWM pins — high = off (inverted)
P0 = P3 = 0xFF;        // COM pins — high = off (low drives external PMOS)

// 2. Configure all as push-pull output
P4_MOD_OC = P2_MOD_OC = P1_MOD_OC = 0;
P0_MOD_OC = P3_MOD_OC = 0;

// 3. Basic LED enable
LED_CTRL = bLED_EN;

// 4. Configure cycle timing
LED_CYCLE = bLED_INTEN_CYC0;  // 128-intensity PWM cycles

// 5. Configure frame: 8 inhibit cycles, 1 repeat
LED_FRAME = bLED_INH_TMR2 | bLED_INH_TMR0;  // 101 = 8 intensity cycles

// 6. Point DMA at buffer
LED_DMA = (UINT16)(&RGBdataBuffer[0]);

// 7. Intensity/color adjustment
LED_INT_ADJ = 0x05;

// 8. Enable all PWM channels except PWM0 global
LED_PWM_OE = 0xFE;

// 9. Preset COMMON to 0xFF (all inactive), next ISR starts at COM 0
LED_COMMON = 0xFF;

// 10. Full enable with interrupts
LED_CTRL = bLED_IE_INHIB | bLED_BLUE_EN | bLED_GREEN_EN | bLED_RED_EN
         | bLED_COM_AHEAD | bLED_PWM_INHIB | bLED_EN;

// 11. Force first interrupt to start scanning
LED_STATUS |= bLED_IF_SET;
IE_PWM_I2C = 1;  // Enable LED/I2C interrupt
```

### LED ISR Pattern (from EVT demo — LED_INT interrupt INT_NO_PWM_I2C)
The ISR fires at each COM cycle end:
1. Increment `LED_COMMON` — moves to next column
2. When `LED_COMMON & 0x0F == 0` → wrapped around → reset to `COM 0x10` (COM16), reset DMA
3. Load next data from XRAM via `LED_LOAD_XRAM()` (assembly, very fast)
4. Toggle P4 to key-scan mode (reads matrix row), then back to PWM mode
5. The key scan is interleaved with the LED scan in the same interrupt!

Key insight: **COM advances through 0x10–0x1F (COM16–COM31 = P0.0–P3.7)** in the EVT demo. For the K580 with 18 columns, we use COM0–COM17.

---

## Flashing / ISP

### To flash after entering bootloader:
1. `bootloader_jump()` disconnects USB and jumps to 0xF400
2. Keyboard re-enumerates as `CH55x USB Bootloader` (VID:PID = 0x4348:0x5537)
3. Use one of:
   - **WCHISPTool** (Windows GUI, from WCH website)
   - **wchisp** (cross-platform CLI, Rust-based: `cargo install wchisp` or download binary)
   - **chprog.py** (Python script, already referenced in `platform.mk`)

### Bootloader disconnect safety:
- CH55x bootloader has a **~30 second USB inactivity timeout**
- If you disconnect / close the ISP tool without flashing, the bootloader self-resets (bSW_RESET)
- The keyboard reboots into normal firmware — nothing is lost (firmware only written atomically at end of ISP session)
- `mcu_reset()` is now properly implemented (SAFE_MOD sequence + bSW_RESET)

---

## Current Firmware Status (as of 2026-03-27)

| Feature | Status | Notes |
|---------|--------|-------|
| USB enumeration | ✅ Working | Windows Code 43 fixed |
| HID keyboard reports | ✅ Working | |
| UART debug output | ✅ Working | UART1 via `mInitSTDIO()` |
| Matrix scan | ✅ Working | |
| Bootloader jump | ✅ Working | `lcall #0xF400` |
| `mcu_reset()` | ✅ Fixed | Now uses SAFE_MOD + bSW_RESET |
| `CONSOLE_ENABLE` | ❌ Broken | Uses stale LUFA Endpoint_* API — needs rewrite |
| `BOOTMAGIC_ENABLE` | ❌ Disabled | Trivial to enable (2 defines + rules.mk change) |
| EEPROM/DataFlash | ❌ Stub only | Empty functions in lib/ch555/eeprom.c |
| RGB LED driver | ❌ Not started | Registers known, EVT demo studied |

---

## Key File Locations

| File | Purpose |
|------|---------|
| `keyboards/redragon/k580/rules.mk` | Feature flags |
| `keyboards/redragon/k580/config.h` | Matrix, encoder, pin config |
| `tmk_core/protocol/ch555/ch555_usb_stack.c` | USB stack, sendchar, Console_Task |
| `tmk_core/protocol/ch555/usb_device.c` | USB interrupt handler, EP control |
| `lib/ch555/eeprom.c` | DataFlash EEPROM driver (currently empty stubs) |
| `lib/ch555/FLASH.C` + `FLASH.H` | WCH DataFlash read/write/erase API |
| `lib/ch555/ch555.h` | All CH555 SFR/XSFR definitions including LED registers |
| `platforms/mcs51/platform.mk` | SDCC compiler flags |
| `platforms/mcs51/bootloaders/ch55xbl.c` | Bootloader jump + mcu_reset |
| `CH555EVT .../RGB test/Code/rgbled.c` | WCH reference RGB LED demo (GB2312 encoded) |

---

## Build System Notes

- **Compiler**: SDCC (Small Device C Compiler) — NOT gcc
- **Memory qualifiers**: `__xdata` = XRAM, `__code` = Flash, `__idata` = IRAM, `__data` = direct IRAM
- **Attributes**: `__attribute__((weak))` works via stubs in `sdcc_dummy_macros.h`
- **Build script**: `compile.sh` — runs `qmk compile` then manual SDCC assemble/link
- **Target**: `make redragon/k580:default` (or `compile.sh` with `kb=redragon/k580`)
- **SDCC constraints**: No float printf, no long long, limited stack, function pointers are expensive
- **XRAM split**: USB buffers use ~1.5KB, leaving ~6.5KB free for LED DMA buffer (512B) + other data
