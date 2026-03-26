
#line 1 "rgbled.c" /0
 
  
#line 1 "DEBUG.H" /0
 
 
 
 
 
 
  
#line 1 "C:\Keil_v5\C51\Inc\absacc.h" /0






 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
#line 28 "C:\Keil_v5\C51\Inc\absacc.h" /1
  
  
  
  
 
#line 33 "C:\Keil_v5\C51\Inc\absacc.h" /0
 
 
 
 
 
 
 
#line 40 "C:\Keil_v5\C51\Inc\absacc.h" /1
  
  
  
  
 
#line 45 "C:\Keil_v5\C51\Inc\absacc.h" /0
 
 
 
 
 
 
 
 
 
#line 7 "DEBUG.H" /0
 
  
#line 1 "CH555.H" /0







 
 
 
 
 
 
 
 
#line 16 "CH555.H" /1
 
 
#line 18 "CH555.H" /0
 
 
 
 
 
 
 
 
 
 
 
 
 typedef bit                             BOOL;
 
 
 typedef unsigned char                   UINT8;
 
 
 typedef unsigned short                  UINT16;
 
 
 typedef unsigned long                   UINT32;
 
 
 typedef unsigned char  data             UINT8D;
 
 
 typedef unsigned short data             UINT16D;
 
 
 typedef unsigned long  data             UINT32D;
 
 
 typedef unsigned char  idata            UINT8I;
 
 
 typedef unsigned short idata            UINT16I;
 
 
 typedef unsigned long  idata            UINT32I;
 
 
 typedef unsigned char  xdata            UINT8X;
 
 
 typedef unsigned short xdata            UINT16X;
 
 
 typedef unsigned long  xdata            UINT32X;
 
 
 typedef unsigned char volatile          UINT8V;
 
 
 typedef unsigned char volatile data     UINT8DV;
 
 
 typedef unsigned char volatile xdata    UINT8XV;
 
 
 typedef unsigned char volatile pdata    UINT8PV;
 
 
 typedef const unsigned char code        UINT8C;
 
 
 typedef unsigned char                 *PUINT8;
 
 
 typedef unsigned short                *PUINT16;
 
 
 typedef unsigned long                 *PUINT32;
 
 
 typedef unsigned char  idata          *PUINT8I;
 
 
 typedef unsigned short idata          *PUINT16I;
 
 
 typedef unsigned long  idata          *PUINT32I;
 
 
 typedef unsigned char  xdata          *PUINT8X;
 
 
 typedef unsigned short xdata          *PUINT16X;
 
 
 typedef unsigned long  xdata          *PUINT32X;
 
 
 typedef unsigned char volatile        *PUINT8V;
 
 
 typedef unsigned char volatile data   *PUINT8DV;
 
 
 typedef unsigned char volatile xdata  *PUINT8XV;
 
 
 typedef unsigned char volatile pdata  *PUINT8PV;
 
 
 typedef const unsigned char code      *PUINT8C;
 
 
 
 
 
 
 
#line 131 "CH555.H" /1
 
 
#line 133 "CH555.H" /0
 
 
 
 
 
 
 
#line 140 "CH555.H" /1
 
 
#line 142 "CH555.H" /0
 
 
 
 
 
 sfr PSW             = 0xD0;          
 sbit CY            = PSW^7;         
 sbit AC            = PSW^6;         
 sbit F0            = PSW^5;         
 sbit RS1           = PSW^4;         
 sbit RS0           = PSW^3;         
 
 
 
 
 
 
 sbit OV            = PSW^2;         
 sbit F1            = PSW^1;         
 sbit P             = PSW^0;         
 sfr ACC             = 0xE0;          
 sfr B               = 0xF0;          
 sfr A_INV           = 0xFD;          
 sfr SP              = 0x81;          
 
 sfr DPL             = 0x82;          
 sfr DPH             = 0x83;          
 sfr SAFE_MOD        = 0xA1;          
 
 
 sfr GLOBAL_CFG      = 0xB1;          
 
 
 
 
 
 
 
 
 sfr PCON            = 0x87;          
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 sfr POWER_CFG       = 0xBA;          
 
 
 
 
 
 
 sfr CLOCK_CFG       = 0xB9;          
 
 
 
 














 
 sfr WAKE_CTRL       = 0xA9;          
 
 
 
 
 
 
 
 sfr RESET_KEEP      = 0xFE;          
 sfr WDOG_COUNT      = 0xFF;          
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 sfr IE              = 0xA8;          
 sbit EA            = IE^7;          
 sbit E_DIS         = IE^6;          
 sbit ET2           = IE^5;          
 sbit ES            = IE^4;          
 sbit ET1           = IE^3;          
 sbit EX1           = IE^2;          
 sbit ET0           = IE^1;          
 sbit EX0           = IE^0;          
 sfr IP              = 0xB8;          
 sbit PH_FLAG       = IP^7;          
 sbit PL_FLAG       = IP^6;          
 
 
 
 
 
 sbit PT2           = IP^5;          
 sbit PS            = IP^4;          
 sbit PT1           = IP^3;          
 sbit PX1           = IP^2;          
 sbit PT0           = IP^1;          
 sbit PX0           = IP^0;          
 sfr IE_EX           = 0xE8;          
 sbit IE_WDOG       = IE_EX^7;       
 sbit IE_GPIO       = IE_EX^6;       
 sbit IE_PWM_I2C    = IE_EX^5;       
 sbit IE_UART1      = IE_EX^4;       
 sbit IE_ADC        = IE_EX^3;       
 sbit IE_USB        = IE_EX^1;       
 sbit IE_SPI0       = IE_EX^0;       
 sfr IP_EX           = 0xE9;          
 
 
 
 
 
 
 
 sfr GPIO_IE         = 0xB2;          
 
 
 
 
 
 
 
 
 
 
 
 sfr16 ROM_ADDR      = 0x84;          
 sfr ROM_ADDR_L      = 0x84;          
 sfr ROM_ADDR_H      = 0x85;          
 
 
 
 
 
 
 sfr16 ROM_DATA_HI   = 0x8E;          
 sfr ROM_DATA_HL     = 0x8E;          
 sfr ROM_DATA_HH     = 0x8F;          
 
 
 
 
 
 
 sfr ROM_CTRL        = 0x86;          
 
 
 
 
 
 
 
 
 
 
 sfr P0              = 0x80;          
 sbit P0_7          = P0^7;
 sbit P0_6          = P0^6;
 sbit P0_5          = P0^5;
 sbit P0_4          = P0^4;
 sbit P0_3          = P0^3;
 sbit P0_2          = P0^2;
 sbit P0_1          = P0^1;
 sbit P0_0          = P0^0;
 sbit SDA0          = P0^1;          
 sbit SCL0          = P0^0;          
 sbit TXD_          = P0^3;          
 sbit RXD_          = P0^2;          
 sbit AIN13         = P0^5;          
 sbit AIN12         = P0^4;          
 sbit AIN11         = P0^3;          
 sbit AIN10         = P0^2;          
 sbit AIN9          = P0^1;          
 sbit AIN8          = P0^0;          
 sfr P0_MOD_OC       = 0xC4;          
 sfr P0_DIR_PU       = 0xC5;          
 
 
 
 
 
 
 
 
 
 
 sfr P1              = 0x90;          
 sbit P1_7          = P1^7;
 sbit P1_6          = P1^6;
 sbit P1_5          = P1^5;
 sbit P1_4          = P1^4;
 sbit P1_3          = P1^3;
 sbit P1_2          = P1^2;
 sbit P1_1          = P1^1;
 sbit P1_0          = P1^0;
 sbit TXD1_         = P1^7;          
 sbit RXD1_         = P1^6;          
 sbit SCK           = P1^7;          
 sbit MISO          = P1^6;          
 sbit MOSI          = P1^5;          
 sbit SCS           = P1^4;          
 sbit INT0_         = P1^2;          
 sbit T2EX          = P1^1;          
 sbit CAP2          = P1^1;          
 sbit T2            = P1^0;          
 sbit CAP1          = P1^0;          
 sbit AIN7          = P1^7;          
 sbit AIN6          = P1^6;          
 sbit AIN5          = P1^5;          
 sbit AIN4          = P1^4;          
 sbit AIN3          = P1^3;          
 sbit AIN2          = P1^2;          
 sbit AIN1          = P1^1;          
 sbit AIN0          = P1^0;          
 sfr P1_MOD_OC       = 0x92;          
 sfr P1_DIR_PU       = 0x93;          
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 sfr P2              = 0xA0;          
 sbit P2_7          = P2^7;
 sbit P2_6          = P2^6;
 sbit P2_5          = P2^5;
 sbit P2_4          = P2^4;
 sbit P2_3          = P2^3;
 sbit P2_2          = P2^2;
 sbit P2_1          = P2^1;
 sbit P2_0          = P2^0;
 sbit TXD1          = P2^7;          
 sbit RXD1          = P2^6;          
 sbit T2EX_         = P2^5;          
 sbit CAP2_         = P2^5;          
 sbit T2_           = P2^4;          
 sbit CAP1_         = P2^4;          
 sfr P2_MOD_OC       = 0x94;          
 sfr P2_DIR_PU       = 0x95;          
 
 
 
 
 
 
 sfr P3              = 0xB0;          
 sbit P3_7          = P3^7;
 sbit P3_6          = P3^6;
 sbit P3_5          = P3^5;
 sbit P3_4          = P3^4;
 sbit P3_3          = P3^3;
 sbit P3_2          = P3^2;
 sbit P3_1          = P3^1;
 sbit P3_0          = P3^0;
 sbit T1            = P3^5;          
 sbit T0            = P3^4;          
 sbit INT1          = P3^3;          
 sbit INT0          = P3^2;          
 sbit TXD           = P3^1;          
 sbit RXD           = P3^0;          
 sfr P3_MOD_OC       = 0x96;          
 sfr P3_DIR_PU       = 0x97;          
 
 
 
 
 
 
 sfr P4              = 0xC0;          
 sbit P4_6          = P4^6;
 sbit P4_5          = P4^5;
 sbit P4_4          = P4^4;
 sbit P4_3          = P4^3;
 sbit P4_2          = P4^2;
 sbit P4_1          = P4^1;
 sbit P4_0          = P4^0;
 sfr P4_MOD_OC       = 0xC2;          
 sfr P4_DIR_PU       = 0xC3;          
 sfr P4_LED_KEY      = 0xC1;          
 
 
 
 
 
 
 
 
 sfr P6_IN           = 0xAD;          
 sfr P6_OUT_PU       = 0xAE;          
 sfr P6_DIR          = 0xAF;          
 
 
 
 
 
 
 
 sfr P7              = 0xF1;          
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 sfr XBUS_AUX        = 0xA2;          
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 sfr TCON            = 0x88;          
 sbit TF1           = TCON^7;        
 sbit TR1           = TCON^6;        
 sbit TF0           = TCON^5;        
 sbit TR0           = TCON^4;        
 sbit IE1           = TCON^3;        
 sbit IT1           = TCON^2;        
 sbit IE0           = TCON^1;        
 sbit IT0           = TCON^0;        
 sfr TMOD            = 0x89;          
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 sfr TL0             = 0x8A;          
 sfr TL1             = 0x8B;          
 sfr TH0             = 0x8C;          
 sfr TH1             = 0x8D;          
 
 
 sfr SCON            = 0x98;          
 sbit SM0           = SCON^7;        
 sbit SM1           = SCON^6;        
 
 
 
 
 
 sbit SM2           = SCON^5;        
 
 sbit REN           = SCON^4;        
 sbit TB8           = SCON^3;        
 sbit RB8           = SCON^2;        
 sbit TI            = SCON^1;        
 sbit RI            = SCON^0;        
 sfr SBUF            = 0x99;          
 
 
 sfr T2CON           = 0xC8;          
 sbit TF2           = T2CON^7;       
 sbit CAP1F         = T2CON^7;       
 sbit EXF2          = T2CON^6;       
 sbit RCLK          = T2CON^5;       
 sbit TCLK          = T2CON^4;       
 sbit EXEN2         = T2CON^3;       
 sbit TR2           = T2CON^2;       
 sbit C_T2          = T2CON^1;       
 sbit CP_RL2        = T2CON^0;       
 sfr T2MOD           = 0xC9;          
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 sfr16 RCAP2         = 0xCA;          
 sfr RCAP2L          = 0xCA;          
 sfr RCAP2H          = 0xCB;          
 sfr16 T2COUNT       = 0xCC;          
 sfr TL2             = 0xCC;          
 sfr TH2             = 0xCD;          
 sfr16 T2CAP1        = 0xCE;          
 sfr T2CAP1L         = 0xCE;          
 sfr T2CAP1H         = 0xCF;          
 
 
 sfr SPI0_STAT       = 0xF8;          
 sbit S0_FST_ACT    = SPI0_STAT^7;   
 sbit S0_IF_OV      = SPI0_STAT^6;   
 sbit S0_IF_FIRST   = SPI0_STAT^5;   
 sbit S0_IF_BYTE    = SPI0_STAT^4;   
 sbit S0_FREE       = SPI0_STAT^3;   
 sbit S0_T_FIFO     = SPI0_STAT^2;   
 sbit S0_R_FIFO     = SPI0_STAT^0;   
 sfr SPI0_DATA       = 0xF9;          
 sfr SPI0_CTRL       = 0xFA;          
 
 
 
 
 
 
 
 
 sfr SPI0_CK_SE      = 0xFB;          
 
 
 sfr SPI0_SETUP      = 0xFC;          
 
 
 
 
 
 
 
 
 
 sfr SCON1           = 0xBC;          
 
 
 
 
 
 
 
 
 sfr SBUF1           = 0xBD;          
 sfr SBAUD1          = 0xBE;          
 sfr SIF1            = 0xBF;          
 
 
 
 
 sfr ADC_CTRL        = 0xF3;          
 
 
 
 
 
 
 
 
 
 
 
 sfr16 ADC_DAT       = 0xF4;          
 sfr ADC_DAT_L       = 0xF4;          
 sfr ADC_DAT_H       = 0xF5;          
 sfr ADC_CHAN        = 0xF6;          
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 sfr LED_COMMON      = 0xA6;          
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 sfr LED_PWM_OE      = 0xA7;          
 
 
 
 
 
 
 
 
 sfr16 LED_DMA       = 0xC6;          
 sfr LED_DMA_L       = 0xC6;          
 sfr LED_DMA_H       = 0xC7;          
 sfr LED_STATUS      = 0xF7;          
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 sfr I2CX_INT        = 0xB3;          
 
 
 sfr I2CS_INT_ST     = 0xBB;          
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 

















 
 
 
#line 1217 "CH555.H" /1
 
 
#line 1219 "CH555.H" /0
 
 
 
 
 
 
 
#line 1226 "CH555.H" /1
 
 
#line 1228 "CH555.H" /0
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 typedef struct _USB_SETUP_REQ {
 UINT8 bRequestType;
 UINT8 bRequest;
 UINT8 wValueL;
 UINT8 wValueH;
 UINT8 wIndexL;
 UINT8 wIndexH;
 UINT8 wLengthL;
 UINT8 wLengthH;
 } USB_SETUP_REQ, *PUSB_SETUP_REQ;
 
 typedef USB_SETUP_REQ xdata *PXUSB_SETUP_REQ;
 
 typedef struct _USB_DEVICE_DESCR {
 UINT8 bLength;
 UINT8 bDescriptorType;
 UINT8 bcdUSBL;
 UINT8 bcdUSBH;
 UINT8 bDeviceClass;
 UINT8 bDeviceSubClass;
 UINT8 bDeviceProtocol;
 UINT8 bMaxPacketSize0;
 UINT8 idVendorL;
 UINT8 idVendorH;
 UINT8 idProductL;
 UINT8 idProductH;
 UINT8 bcdDeviceL;
 UINT8 bcdDeviceH;
 UINT8 iManufacturer;
 UINT8 iProduct;
 UINT8 iSerialNumber;
 UINT8 bNumConfigurations;
 } USB_DEV_DESCR, *PUSB_DEV_DESCR;
 
 typedef USB_DEV_DESCR xdata *PXUSB_DEV_DESCR;
 
 typedef struct _USB_CONFIG_DESCR {
 UINT8 bLength;
 UINT8 bDescriptorType;
 UINT8 wTotalLengthL;
 UINT8 wTotalLengthH;
 UINT8 bNumInterfaces;
 UINT8 bConfigurationValue;
 UINT8 iConfiguration;
 UINT8 bmAttributes;
 UINT8 MaxPower;
 } USB_CFG_DESCR, *PUSB_CFG_DESCR;
 
 typedef USB_CFG_DESCR xdata *PXUSB_CFG_DESCR;
 
 typedef struct _USB_INTERF_DESCR {
 UINT8 bLength;
 UINT8 bDescriptorType;
 UINT8 bInterfaceNumber;
 UINT8 bAlternateSetting;
 UINT8 bNumEndpoints;
 UINT8 bInterfaceClass;
 UINT8 bInterfaceSubClass;
 UINT8 bInterfaceProtocol;
 UINT8 iInterface;
 } USB_ITF_DESCR, *PUSB_ITF_DESCR;
 
 typedef USB_ITF_DESCR xdata *PXUSB_ITF_DESCR;
 
 typedef struct _USB_ENDPOINT_DESCR {
 UINT8 bLength;
 UINT8 bDescriptorType;
 UINT8 bEndpointAddress;
 UINT8 bmAttributes;
 UINT8 wMaxPacketSizeL;
 UINT8 wMaxPacketSizeH;
 UINT8 bInterval;
 } USB_ENDP_DESCR, *PUSB_ENDP_DESCR;
 
 typedef USB_ENDP_DESCR xdata *PXUSB_ENDP_DESCR;
 
 typedef struct _USB_CONFIG_DESCR_LONG {
 USB_CFG_DESCR   cfg_descr;
 USB_ITF_DESCR   itf_descr;
 USB_ENDP_DESCR  endp_descr[1];
 } USB_CFG_DESCR_LONG, *PUSB_CFG_DESCR_LONG;
 
 typedef USB_CFG_DESCR_LONG xdata *PXUSB_CFG_DESCR_LONG;
 
 typedef struct _USB_HUB_DESCR {
 UINT8 bDescLength;
 UINT8 bDescriptorType;
 UINT8 bNbrPorts;
 UINT8 wHubCharacteristicsL;
 UINT8 wHubCharacteristicsH;
 UINT8 bPwrOn2PwrGood;
 UINT8 bHubContrCurrent;
 UINT8 DeviceRemovable;
 UINT8 PortPwrCtrlMask;
 } USB_HUB_DESCR, *PUSB_HUB_DESCR;
 
 typedef USB_HUB_DESCR xdata *PXUSB_HUB_DESCR;
 
 typedef struct _USB_HID_DESCR {
 UINT8 bLength;
 UINT8 bDescriptorType;
 UINT8 bcdHIDL;
 UINT8 bcdHIDH;
 UINT8 bCountryCode;
 UINT8 bNumDescriptors;
 UINT8 bDescriptorTypeX;
 UINT8 wDescriptorLengthL;
 UINT8 wDescriptorLengthH;
 } USB_HID_DESCR, *PUSB_HID_DESCR;
 
 typedef USB_HID_DESCR xdata *PXUSB_HID_DESCR;
 
 typedef struct _UDISK_BOC_CBW {          
 UINT8 mCBW_Sig0;
 UINT8 mCBW_Sig1;
 UINT8 mCBW_Sig2;
 UINT8 mCBW_Sig3;
 UINT8 mCBW_Tag0;
 UINT8 mCBW_Tag1;
 UINT8 mCBW_Tag2;
 UINT8 mCBW_Tag3;
 UINT8 mCBW_DataLen0;
 UINT8 mCBW_DataLen1;
 UINT8 mCBW_DataLen2;
 UINT8 mCBW_DataLen3;                 
 UINT8 mCBW_Flag;                     
 UINT8 mCBW_LUN;
 UINT8 mCBW_CB_Len;                   
 UINT8 mCBW_CB_Buf[16];               
 } UDISK_BOC_CBW, *PUDISK_BOC_CBW;
 
 typedef UDISK_BOC_CBW xdata *PXUDISK_BOC_CBW;
 
 typedef struct _UDISK_BOC_CSW {          
 UINT8 mCSW_Sig0;
 UINT8 mCSW_Sig1;
 UINT8 mCSW_Sig2;
 UINT8 mCSW_Sig3;
 UINT8 mCSW_Tag0;
 UINT8 mCSW_Tag1;
 UINT8 mCSW_Tag2;
 UINT8 mCSW_Tag3;
 UINT8 mCSW_Residue0;                 
 UINT8 mCSW_Residue1;
 UINT8 mCSW_Residue2;
 UINT8 mCSW_Residue3;                 
 UINT8 mCSW_Status;                   
 } UDISK_BOC_CSW, *PUDISK_BOC_CSW;
 
 typedef UDISK_BOC_CSW xdata *PXUDISK_BOC_CSW;
 
 
#line 1550 "CH555.H" /1
 
 
#line 1552 "CH555.H" /0
 
 
#line 8 "DEBUG.H" /0
 
  
#line 1 "C:\Keil_v5\C51\Inc\stdio.h" /0






 
 
 
 
 
 
 
 
 
 
#line 17 "C:\Keil_v5\C51\Inc\stdio.h" /1
  
 
#line 19 "C:\Keil_v5\C51\Inc\stdio.h" /0
 
 
 
 typedef unsigned int size_t;
 
 
 #pragma SAVE
 #pragma REGPARMS
 extern char _getkey (void);
 extern char getchar (void);
 extern char ungetchar (char);
 extern char putchar (char);
 extern int printf   (const char *, ...);
 extern int sprintf  (char *, const char *, ...);
 extern int vprintf  (const char *, char *);
 extern int vsprintf (char *, const char *, char *);
 extern char *gets (char *, int n);
 extern int scanf (const char *, ...);
 extern int sscanf (char *, const char *, ...);
 extern int puts (const char *);
 
 #pragma RESTORE
 
 
 
#line 9 "DEBUG.H" /0
 
  
#line 1 "C:\Keil_v5\C51\Inc\string.h" /0







 
 
 
 
 
 
#line 14 "C:\Keil_v5\C51\Inc\string.h" /1
  
 
 
#line 17 "C:\Keil_v5\C51\Inc\string.h" /0
 
 
#line 19 "C:\Keil_v5\C51\Inc\string.h" /1
  
 
#line 21 "C:\Keil_v5\C51\Inc\string.h" /0
 
 #pragma SAVE
 #pragma REGPARMS
 extern char  *strcat  (char *s1, const char *s2);
 extern char  *strncat (char *s1, const char *s2, size_t n);
 
 extern char   strcmp  (const char *s1, const char *s2);
 extern char   strncmp (const char *s1, const char *s2, size_t n);
 
 extern char  *strcpy  (char *s1, const char *s2);
 extern char  *strncpy (char *s1, const char *s2, size_t n);
 
 extern size_t strlen  (const char *);
 
 extern char  *strchr  (const char *s, char c);
 extern int    strpos  (const char *s, char c);
 extern char  *strrchr (const char *s, char c);
 extern int    strrpos (const char *s, char c);
 
 extern size_t strspn  (const char *s, const char *set);
 extern size_t strcspn (const char *s, const char *set);
 extern char  *strpbrk (const char *s, const char *set);
 extern char  *strrpbrk(const char *s, const char *set);
 extern char  *strstr  (const char *s, const char *sub);
 extern char  *strtok  (char *str, const char *set);
 
 extern char   memcmp  (const void *s1, const void *s2, size_t n);
 extern void  *memcpy  (void *s1, const void *s2, size_t n);
 extern void  *memchr  (const void *s, char val, size_t n);
 extern void  *memccpy (void *s1, const void *s2, char val, size_t n);
 extern void  *memmove (void *s1, const void *s2, size_t n);
 extern void  *memset  (void *s, char val, size_t n);
 #pragma RESTORE
 
 
#line 10 "DEBUG.H" /0
 
  
#line 1 "C:\Keil_v5\C51\Inc\stdlib.h" /0







 
 
 
 
 
 
#line 14 "C:\Keil_v5\C51\Inc\stdlib.h" /1
  
 
 
#line 17 "C:\Keil_v5\C51\Inc\stdlib.h" /0
 
 
#line 19 "C:\Keil_v5\C51\Inc\stdlib.h" /1
  
 
#line 21 "C:\Keil_v5\C51\Inc\stdlib.h" /0
 
 
 
 typedef char wchar_t;
 
 
 
#line 28 "C:\Keil_v5\C51\Inc\stdlib.h" /1
 
 
 
 
 
 
 
 
 
  
 
 
#line 40 "C:\Keil_v5\C51\Inc\stdlib.h" /0
 
 
 
 
 
 
#line 46 "C:\Keil_v5\C51\Inc\stdlib.h" /1
 
 
 
 
 
 
#line 52 "C:\Keil_v5\C51\Inc\stdlib.h" /0
 
 #pragma SAVE
 #pragma REGPARMS
 
 extern char   cabs (char  val);
 
 extern int    abs  (int   val);
 
 extern long   labs (long  val);
 
 extern float  atof (const char *s1);
 extern long   atol (const char *s1);
 extern int    atoi (const char *s1);
 extern int    rand (void);
 extern void   srand (unsigned int seed);
 
 
#line 69 "C:\Keil_v5\C51\Inc\stdlib.h" /1
 
  
 
 
#line 73 "C:\Keil_v5\C51\Inc\stdlib.h" /0
 
 extern float         strtod  (const char *nptr, char **endptr);
 extern long          strtol  (const char *nptr, char **endptr, unsigned char base);
 extern unsigned long strtoul (const char *nptr, char **endptr, unsigned char base);
 
 
 
 extern void init_mempool          (void xdata *p, size_t size);
 extern void xdata *malloc  (size_t size);
 extern void free                  (void xdata *p);
 extern void xdata *realloc (void xdata *p, size_t size);
 extern void xdata *calloc  (size_t nmemb, size_t size);
 
 
#line 87 "C:\Keil_v5\C51\Inc\stdlib.h" /1
 
 
#line 89 "C:\Keil_v5\C51\Inc\stdlib.h" /0
 
 #pragma RESTORE
 
 
#line 11 "DEBUG.H" /0
 
 
  
#line 1 "C:\Keil_v5\C51\Inc\intrins.h" /0






 
 
 
 
 
 #pragma SAVE
 
 
#line 15 "C:\Keil_v5\C51\Inc\intrins.h" /1
 
 
 
#line 18 "C:\Keil_v5\C51\Inc\intrins.h" /0
 
 extern void          _nop_     (void);
 extern bit           _testbit_ (bit);
 extern unsigned char _cror_    (unsigned char, unsigned char);
 extern unsigned int  _iror_    (unsigned int,  unsigned char);
 extern unsigned long _lror_    (unsigned long, unsigned char);
 extern unsigned char _crol_    (unsigned char, unsigned char);
 extern unsigned int  _irol_    (unsigned int,  unsigned char);
 extern unsigned long _lrol_    (unsigned long, unsigned char);
 extern unsigned char _chkfloat_(float);
 
#line 29 "C:\Keil_v5\C51\Inc\intrins.h" /1
 
 
 
#line 32 "C:\Keil_v5\C51\Inc\intrins.h" /0
 
 extern void          _push_    (unsigned char _sfr);
 extern void          _pop_     (unsigned char _sfr);
 
 
 #pragma RESTORE
 
 
 
#line 13 "DEBUG.H" /0
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 void	CfgFsys( );                         
 void	mDelayuS( UINT16 n );               
 void	mDelaymS( UINT16 n );               
 void    CH555UART0Alter();                 
 void	mInitSTDIO( );                      
 
 
 
#line 2 "rgbled.c" /0
 
  
#line 1 "rgbled.h" /0
 
 
 
 
#line 5 "rgbled.h" /1
 
 
#line 7 "rgbled.h" /0
 
 
 
 
 
 
 
 
 
 
 
 void InitRGBLED( void );
 void showLogo(void);
 void init_Timer(void);  
 void paramInit();   
 
#line 23 "rgbled.h" /1
 
 
#line 25 "rgbled.h" /0
 
 
#line 3 "rgbled.c" /0
 
 
 BOOL  data	 IsCode;
 UINT16D	 BufferAddr;
 UINT8X	RGBdataBuffer[128][4]={0};      
 UINT8X	RGBdataBuffer1[128][4]={0};  
 
 
 
 
 
 
 UINT8I RGB_stauts = 0;           
 UINT8D RGBMode=0;                
 UINT8I timeCount=0;              
 signed char data incre=0;
 
 void	InitRGBLED( void )
 { 
 P4 = P2 = P1 = 0xFF;   
 P0 = P3 = 0xFF;   
 P4_MOD_OC = P2_MOD_OC = P1_MOD_OC = 0;   
 P0_MOD_OC = P3_MOD_OC = 0;   
   ((unsigned char volatile xdata *) 0)[0x21D1] = 0x01;
   ((unsigned char volatile xdata *) 0)[0x21D2] = 0x10;  
   ((unsigned char volatile xdata *) 0)[0x21D3] =  0x40|0x10;   
 LED_DMA = BufferAddr = (UINT16)( &RGBdataBuffer[0] );   
 IsCode = 0;            
   ((unsigned char volatile xdata *) 0)[0x21D8] = 0x05;   
 LED_PWM_OE = 0xFE;
 LED_COMMON = 0xFF;   
   ((unsigned char volatile xdata *) 0)[0x21D1] = 0x80 | 0x40 | 0x20 | 0x10 | 0x08 |0x04 | 0x01;
 LED_STATUS |= 0x40;   
 IE_PWM_I2C = 1;
 
 }
 
 
 void showLogo(void)
 {
 UINT8 i;
 
 
 for(i=0;i<128;i++){
 RGBdataBuffer[i][0]=127;
 RGBdataBuffer[i][1]=255; 
 RGBdataBuffer[i][2]=127; 
 RGBdataBuffer[i][3]=127; 
 }
 for(i=0;i<128;i++){
 RGBdataBuffer1[i][0]=0;
 RGBdataBuffer1[i][1]=0; 
 RGBdataBuffer1[i][2]=0; 
 RGBdataBuffer1[i][3]=0; 
 }    
 mDelaymS(200);
 BufferAddr = (UINT16)( &RGBdataBuffer1[0] );  
 mDelaymS(200);
 BufferAddr = (UINT16)( &RGBdataBuffer[0] ); 
 mDelaymS(200); 
 BufferAddr = (UINT16)( &RGBdataBuffer1[0] );  
 mDelaymS(200);  
 BufferAddr = (UINT16)( &RGBdataBuffer[0] ); 
 mDelaymS(200); 
 BufferAddr = (UINT16)( &RGBdataBuffer1[0] );  
 mDelaymS(200); 
 }
 
 
 UINT8V	NewKey;
 void	LED_LOAD_XRAM( void );
 void	LED_LOAD_CODE( void );
 UINT8C key_board_tale[  ]=					 
 {
 
 0x29,0x35,0x2b,0x39,0x02,0x01,0x62,0x00, 
 0x3a,0x1e,0x14,0x04,0x1d,0x08,0x59,0x00, 
 0x3b,0x1f,0x1a,0x16,0x1b,0x04,0x5a,0x00, 
 0x3c,0x20,0x08,0x07,0x06,0x2c,0x5b,0x00, 
 0x3d,0x21,0x15,0x09,0x19,0x40,0x5c,0x00, 
 0x3e,0x22,0x17,0x0a,0x05,0x80,0x5d,0x00, 
 
 0x3f,0x23,0x1c,0x0b,0x11,0x65,0x5e,0x00, 
 0x40,0x24,0x18,0x0d,0x10,0x10,0x5f,0x00, 
 0x41,0x25,0x0c,0x0e,0x36,0x00,0x60,0x00, 
 0x42,0x26,0x12,0x0f,0x37,0x00,0x61,0x00, 
 0x43,0x27,0x13,0x33,0x38,0x00,0x57,0x00, 
 0x44,0x2d,0x2f,0x34,0x20,0x50,0x56,0x00, 
 0x45,0x2e,0x30,0x28,0x52,0x51,0x55,0x00, 
 
 0x46,0x2a,0x31,0x00,0x00,0x4f,0x54,0x00, 
 0x47,0x49,0x4c,0x4b,0x00,0x53,0x63,0x00, 
 0x48,0x4a,0x4d,0x4e,0x00,0x58,0x00,0x00, 
 
 
 };
 
 typedef struct				 
 {
 UINT8 first_key_count;		 
 UINT8 first_key_buf[20];	 
 
 UINT8 sec_key_count;		 
 UINT8 sec_key_buf[20];		 
 
 UINT8 end_key_count;		 
 UINT8 end_key_buf[20];		 
 
 }KEY_VALUE;
 
 bit  scan_count = 0;     
 KEY_VALUE scan_key;
 UINT8X back_key_buf[8];
 UINT8X key_buf[8];
 UINT8X  HIDKey[8] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
 bit temp = 0;     
 bit key_up=0; 
 UINT8D buf[20];    
 UINT8V count=0; 
 extern UINT8    FLAG;
 void paramInit(void)
 {
 scan_count = 0;
 count = 0;
 scan_key.first_key_count = 0;
 memset(scan_key.first_key_buf,0xff,20);
 scan_key.sec_key_count = 0;
 memset(scan_key.sec_key_buf,0xff,20);
 scan_key.end_key_count = 0;
 memset(scan_key.end_key_buf,0xff,20);
 memset( back_key_buf,0x00,8 );   
 memset( key_buf,0x00,8 );
 memset( buf,0xff,20 );
 }
 
 
 
 void enp1IntIn( )
 {
 
 while(( ((unsigned char volatile xdata *) 0)[0x2201] & 0x03 ) == 0x00);                   
 memcpy( ((PUINT8X)0x1000)+0x40, HIDKey, 8);              
 putchar(55);
 putchar(HIDKey[2]);
   ((unsigned char volatile xdata *) 0)[0x2209] = sizeof(HIDKey);                                              
   ((unsigned char volatile xdata *) 0)[0x2201] = ((unsigned char volatile xdata *) 0)[0x2201] & ~ 0x03 | 0x00;                 
 }
 
 void key_up_data( UINT8 *pupdata,UINT8 len )
 {
 UINT8 i;
 if(FLAG ){  																						 
 i = memcmp( pupdata,back_key_buf,8 );							                                 
 if( i ){
 FLAG = 0;
 memcpy( &HIDKey[0],pupdata,len );
 memcpy( back_key_buf,pupdata,len );
 enp1IntIn(  );
 if(HIDKey[2] == 0x14){
 RGBMode++;
 if(RGBMode > 5) RGBMode = 0;
   ((unsigned char volatile xdata *) 0)[0x21DA] = 0; 
 }
 if(RGBMode == 4){
 srand(TL1);
 for(i=0;i<scan_key.sec_key_count;i++){
 RGBdataBuffer1[buf[i]][0] = 220;
 RGBdataBuffer1[buf[i]][1] = rand()%256;
 RGBdataBuffer1[buf[i]][2] = rand()%256;
 RGBdataBuffer1[buf[i]][3] = rand()%256;
 }
 }
 
 }
 }
 }
 
 void Key_Porcess( UINT8 num )    
 {
 UINT8 i,j,s;
 UINT8 *p1,*p2;
 UINT8X buff[20];
 for( i=0;i!=num;i++ )
 {
 p1 = memchr( scan_key.end_key_buf,scan_key.sec_key_buf[i],scan_key.end_key_count );		
 if( p1==0 ){
 scan_key.end_key_buf[scan_key.end_key_count] = 	scan_key.sec_key_buf[i];
 scan_key.end_key_count++;
 }
 }
 
 
 for( i=0;i<scan_key.end_key_count;i++ )
 {
 p1 = memchr( scan_key.sec_key_buf,scan_key.end_key_buf[i],num ); 
 if( p1 == 0 ){
 scan_key.end_key_buf[i]	= 0xff;
 }
 }
 
 
 j = 0;
 p1 = scan_key.end_key_buf;
 p2 = buff;
 for( i=0;i!=scan_key.end_key_count;i++ )
 {
 if( *p1!=0xff ){
 *p2 = *p1;
 p2++;j++;
 }
 p1++;
 }
 memset( scan_key.end_key_buf,0xff,20 );																																																
 memcpy( scan_key.end_key_buf,buff,j );
 scan_key.end_key_count = j;
 
 j = 0;
 memset(key_buf,0x00,8);
 
 for( i=0;i!=scan_key.end_key_count;i++ ){
 s = 0;																			 
 if( (scan_key.end_key_buf[i] == 0x04))			            
 {
 key_buf[0] |= key_board_tale[ scan_key.end_key_buf[i] ]; 
 s = 1;
 }
 if( (scan_key.end_key_buf[i] == 0x05) ){
 key_buf[0] |= key_board_tale[ scan_key.end_key_buf[i] ]; 
 s = 1;
 }
 if( (scan_key.end_key_buf[i] == 0x0D) ){
 key_buf[0] |= key_board_tale[ scan_key.end_key_buf[i] ]; 
 s = 1;
 }
 if( (scan_key.end_key_buf[i] == 0x15) ){
 key_buf[0] |= key_board_tale[ scan_key.end_key_buf[i] ]; 
 s = 1;
 }
 if( (scan_key.end_key_buf[i] == 0x25) ){
 key_buf[0] |= key_board_tale[ scan_key.end_key_buf[i] ]; 
 s = 1;
 }
 
 
 
 
 
 
 
 
 if( (scan_key.end_key_buf[i] == 0x2D) ){
 key_buf[0] |= key_board_tale[ scan_key.end_key_buf[i] ]; 
 s = 1;
 }
 if( (scan_key.end_key_buf[i] == 0x3D) ){
 key_buf[0] |= key_board_tale[ scan_key.end_key_buf[i] ]; 
 s = 1;
 }
 if( (scan_key.end_key_buf[i] == 0x5C) ){
 key_buf[0] |= key_board_tale[ scan_key.end_key_buf[i] ];	 
 s = 1;
 }
 
 if( s == 0 ){
 
 if( j <6 ){
 key_buf[2+j]  = key_board_tale[ scan_key.end_key_buf[i] ];
 
 j++;
 }
 }
 }	
 }
 void	LED_INT( void ) interrupt 11 using 1	 
 {
 UINT8 data i;
 i = (++LED_COMMON)&0x0f;
 
 
 if ( i == 0 ) {	 
 LED_COMMON = 0x10;	 
 LED_DMA = BufferAddr;	 
 if( scan_count == 0) { 
 scan_key.first_key_count = count;
 memcpy(scan_key.first_key_buf,buf,count);	
 scan_count = 1;
 }else{      
 scan_key.sec_key_count = count;
 memcpy(scan_key.sec_key_buf,buf,count);		
 scan_count = 0;
 if(count != 0){
 i = memcmp( scan_key.first_key_buf,scan_key.sec_key_buf,count ); 
 if( i == 0 )		 
 {
 
 Key_Porcess(count);
 }                
 }else{ 
 memset( key_buf,0x00,8 );        
 memset(scan_key.end_key_buf,0xff,20);
 scan_key.end_key_count = 0;	
 if(RGBMode == 4){
 for(i=0;i<128;i++){
 RGBdataBuffer1[i][0] = 0;
 RGBdataBuffer1[i][1] = 0;
 RGBdataBuffer1[i][2] = 0;
 RGBdataBuffer1[i][3] = 0;
 }
 }
 }
 key_up = 1;
 } 
 count = 0;
 }
 if ( IsCode ) LED_LOAD_CODE( );	 
 else LED_LOAD_XRAM( );	 
 
 
 
 P4_LED_KEY = 0xFF;	 
 P4_MOD_OC = 0xFF;	 
 
 
 _nop_( );	 
 _nop_( );
 ACC = ((unsigned char volatile xdata *) 0)[0x21D1];	 
 _nop_( ); _nop_( ); _nop_( ); _nop_( ); _nop_( );	 
 _nop_( ); _nop_( ); _nop_( ); _nop_( ); _nop_( );
 _nop_( ); _nop_( ); _nop_( ); _nop_( ); _nop_( );
 _nop_( ); _nop_( ); _nop_( ); _nop_( ); _nop_( );
 NewKey = P4;
 
 P4_MOD_OC = 0;	 
 P4_LED_KEY = 0;	 
 LED_PWM_OE = 0xFF;	 
 P0 = P3 = 0xFF;   
 
 
 
 
 i=LED_COMMON&0x0F;
 
 if(count<21 && NewKey!=0xFF){ 
 if((NewKey & 0x01) == 0){
 buf[count] = 8*i+0;
 count++;
 }
 if((NewKey & 0x02) == 0){
 buf[count] = 8*i+1;
 count++;
 }
 if((NewKey & 0x04) == 0){
 buf[count] = 8*i+2;
 count++;
 }
 if((NewKey & 0x08) == 0){
 buf[count] = 8*i+3;
 count++;
 }
 if((NewKey & 0x10) == 0){
 buf[count] = 8*i+4;
 count++;
 }
 if((NewKey & 0x20) == 0){
 buf[count] = 8*i+5;
 count++;
 }
 if((NewKey & 0x40) == 0){
 buf[count] = 8*i+6;
 count++;
 }
 }
 }
 










 
 void mTimer1ModSetup(UINT8 mode)
 {
 TMOD &= 0x0f;
 TMOD |= mode << 4; 
 }
 






 
 void mTimer1SetData(UINT16 dat)
 {
 UINT16 tmp;
 tmp = 65536 - dat;
 TL1 = tmp & 0xff;
 TH1 = (tmp>>8) & 0xff;
 }
 
 
 void mTimer1Interrupt( void ) interrupt 3                 
 {    
 mTimer1SetData(0x9C40);
 timeCount++;
 switch(RGBMode){
 case 0:
 BufferAddr = (UINT16)( &RGBdataBuffer[0] );            
 if(incre >= 127)  RGB_stauts = 1;
 if(incre <= -127) RGB_stauts = 0;
   ((unsigned char volatile xdata *) 0)[0x21DA]=RGB_stauts?(incre--):(incre++);                  
 break;
 case 1:
 BufferAddr = (UINT16)( &RGBdataBuffer[0] );
 break;
 case 2:
 BufferAddr = (UINT16)( &RGBdataBuffer1[0] );
 break;
 case 3:
 if(timeCount>=127)RGB_stauts = 1;
 if(timeCount<127 )RGB_stauts = 0;
 BufferAddr =RGB_stauts?(UINT16)( &RGBdataBuffer1[0] ):(UINT16)( &RGBdataBuffer[0] );
 break;
 case 4:
 BufferAddr =(UINT16)( &RGBdataBuffer1[0] );           
 break;
 default:
 RGBMode = 0;
 break;
 }
 
 
 }
 void init_Timer(void){
 
  (T2MOD &= ~(0x80 | 0x20));                                                     
 mTimer1ModSetup(1);	                                                      
 mTimer1SetData(0x9C40);                                                     
  (TR1 = 1 ? 1 : 0);                                                           
 ET1 = 1;                                                                    
 
 }
