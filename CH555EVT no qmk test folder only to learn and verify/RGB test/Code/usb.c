

#include "usb.h"

#define bUEP_R_TOG        0x80      // expected data toggle flag of USB endpoint X receiving (OUT): 0=DATA0, 1=DATA1
#define bUEP_T_TOG        0x40      // prepared data toggle flag of USB endpoint X transmittal (IN): 0=DATA0, 1=DATA1
#define bUEP_R_RES1       0x08      // handshake response type high bit for USB endpoint X receiving (OUT)
#define bUEP_R_RES0       0x04      // handshake response type low bit for USB endpoint X receiving (OUT)
#define MASK_UEP_R_RES    0x0C      // bit mask of handshake response type for USB endpoint X receiving (OUT)
#define UEP_R_RES_ACK     0x00
#define UEP_R_RES_TOUT    0x04
#define UEP_R_RES_NAK     0x08
#define UEP_R_RES_STALL   0x0C
// bUEP_R_RES1 & bUEP_R_RES0: handshake response type for USB endpoint X receiving (OUT)
//   00: ACK (ready)
//   01: no response, time out to host, for non-zero endpoint isochronous transactions
//   10: NAK (busy)
//   11: STALL (error)
#define bUEP_T_RES1       0x02      // handshake response type high bit for USB endpoint X transmittal (IN)
#define bUEP_T_RES0       0x01      // handshake response type low bit for USB endpoint X transmittal (IN)
#define MASK_UEP_T_RES    0x03      // bit mask of handshake response type for USB endpoint X transmittal (IN)
#define UEP_T_RES_ACK     0x00
#define UEP_T_RES_TOUT    0x01
#define UEP_T_RES_NAK     0x02
#define UEP_T_RES_STALL   0x03
// bUEP_T_RES1 & bUEP_T_RES0: handshake response type for USB endpoint X transmittal (IN)
//   00: DATA0 or DATA1 then expecting ACK (ready)
//   01: DATA0 or DATA1 then expecting no response, time out from host, for non-zero endpoint isochronous transactions
//   10: NAK (busy)
//   11: STALL (error)


 
//#if DEBUG
//        printf();
//#endif

#define	MAX_DESCR_SIZE		    0x7f
#define THIS_ENDP0_SIZE         DEFAULT_ENDP0_SIZE
#define EP1_IN_SIZE             DEFAULT_ENDP0_SIZE                                              //键盘端点数据包大小
#define EP2_IN_SIZE             64 
UINT8C	MyDevDescr[] = { 0x12,0x01,0x00,0x02,0x00,0x00,0x00,THIS_ENDP0_SIZE,
                         0x86,0x1A,0xE5,0xE7,0x00,0x00,0x00,0x00,
                         0x00,0x01};
/*HID类报表描述符*/
UINT8C KeyRepDesc[] =
{
    0x05,0x01,0x09,0x06,0xA1,0x01,0x05,0x07,
    0x19,0xe0,0x29,0xe7,0x15,0x00,0x25,0x01,
    0x75,0x01,0x95,0x08,0x81,0x02,0x95,0x01,
    0x75,0x08,0x81,0x01,0x95,0x03,0x75,0x01,
    0x05,0x08,0x19,0x01,0x29,0x03,0x91,0x02,
    0x95,0x05,0x75,0x01,0x91,0x01,0x95,0x06,
    0x75,0x08,0x26,0xFF,0x00,0x05,0x07,0x19,
    0x00,0x29,0x91,0x81,0x00,0xC0
};

UINT8C MY_HID_Report_Desc[  ] = //特性描述符，用来控制灯
{
    //每行第一字节为该条目的前缀
    //7-4:bTag  3-2:bType(主 全局  局部  保留)   1-0:bSize(0 1 2 4)
    0x06, 0x00,0xff,
    0x09, 0x04,
    0xa1, 0x01,                                                   //集合开始
    0x15, 0x00,                                                   //Logical  Minimun
    0x26, 0xff,0x00,                                              //Logical  Maximun
    0x95, 64,                                                     //Report Counet
    0x75, 0x08,
    0x09, 0x02,                                                   //Usage Page  用法
    0xb1, 0x02,                                                   //Logical  Minimun
    0x09, 0x02,                                                   //Logical  Maximun
    0x81, 0x02,                                                   //Report Size
    0x09, 0x04,                                                   //Report Counet
    0x91, 0x02,                                                   //Output
    0xC0    

};
// 配置描述符
UINT8C	MyCfgDescr[] = { 	  
    0x09,0x02,0x42,0x00,0x02,0x01,0x00,0xA0,0xFA,             //配置描述符
    0x09,0x04,0x00,0x00,0x01,0x03,0x01,0x01,0x00,             //接口描述符,键盘
    0x09,0x21,0x11,0x01,0x00,0x01,0x22,sizeof(KeyRepDesc)&0xFF,sizeof(KeyRepDesc)>>8,             //HID类描述符
    0x07,0x05,0x81,0x03,EP1_IN_SIZE,0x00,0x0A,                       //端点描述符
    0x09,0x04,0x01,0x00,0x02,0x03,0x00,0x00,0x00,             //接口描述符,鼠标
    0x09,0x21,0x11,0x01,0x00,0x01,0x22,sizeof(MY_HID_Report_Desc)&0xFF,sizeof(MY_HID_Report_Desc)>>8,             //HID类描述符    
    0x07,0x05,0x83,0x03,EP2_IN_SIZE,0x00,0x01,                        //端点描述符
    0x07,0x05,0x02,0x03,EP2_IN_SIZE,0x00,0x01,                        //端点描述符
    };
// 语言描述符
UINT8C	MyLangDescr[] = { 0x04, 0x03, 0x09, 0x04 };
// 厂家信息
UINT8C	MyManuInfo[] = { 0x0E, 0x03, 'w', 0, 'c', 0, 'h', 0, '.', 0, 'c', 0, 'n', 0 };
// 产品信息
UINT8C	MyProdInfo[] = { 0x0C, 0x03, 'C', 0, 'H', 0, '5', 0, '5', 0, '5', 0 };

UINT8	UsbConfig = 0;	// USB配置标志
UINT8    FLAG,Feature;
static bit sleep=0;

extern UINT8D RGBMode;               //RGB模式
//void	USB_DeviceInterrupt( void ) interrupt INT_NO_USB using 1
//{
//    if(USB_IF&bUX_IF_D0_TRANS){
//        printf("USB_IF1:%x\n",(UINT16)USB_IF); 
//        D0_EP0T_L = 8;
//        D0_EP0RES = bUEP_R_TOG | bUEP_T_TOG | UEP_R_RES_STALL | UEP_T_RES_STALL;
//        D0_EP0RES = bUEP_R_TOG | bUEP_T_TOG | UEP_R_RES_ACK | UEP_T_RES_ACK;  // 默认数据包是DATA1  
//        USB_IF = bUX_IF_D0_TRANS;
//        UIF_USBX_IF = 0;
//        printf("D0_EP0RES:%x\n",(UINT16)D0_EP0RES); 
//        printf("USB_IF2:%x\n",(UINT16)USB_IF); 
//    }else if(USB_IF & bUX_IF_BUS_RST) /*总线复位事件*/
//    {
//#if DEBUG
//        printf("reset...\n");
//#endif 
//        USB_CTRL = 0;
//        D0_EP0RES = UEP_R_RES_ACK | UEP_T_RES_NAK;
//        D0_EP1RES = bUEP_X_AUTO_TOG | UEP_X_RES_NAK;
//        D0_EP2RES = bUEP_X_AUTO_TOG | UEP_X_RES_NAK;
//        
//        D0_EP_MOD = bUX_EP1O_EN|bUX_EP2O_EN | bUX_DEV_EN; 
//        D0_ADDR = 0;
//        HB_ADDR = 0x7F;             //将收到的数据直接转发到D0
//        USB_IE = bUX_IE_SUSPEND|bUX_IE_TRANSFER|bUX_IE_BUS_RST;
//        USB_CTRL = bUX_DP_PU_EN;
//        USB_IF = bUX_IF_BUS_RST;
//    }
//    USB_IF = 0xff;
//  //  printf("USB_IF3:%x\n",(UINT16)USB_IF); 
//}
UINT8X	USBRGBdataBuffer[128*4]={0};
static UINT16X  USB_IO=0;

void	SleepWithKey( void )	// sleep until any key press
{
    
	UINT8	savePortCfg;
    putchar(0xAD);
    putchar(WAKE_CTRL);
	EA = 0;	// disable all interrupt
	P4_LED_KEY = 0xFF;	// enable key mode
    P4_MOD_OC = 0xFF;	// disable push-pull output
    LED_CTRL &= ~bLED_EN;
//	P4_DIR_PU = 0xFF;	// always
//	P4 = 0xFF;	// always
	P0 = P3 = 0;	// COMMON all low to support any key wakeup
//	P7 &= ~ 0x03;	// if P7 used for COMMON
    
	savePortCfg = PORT_CFG;
	PORT_CFG |= bP4_IE_LEVEL;	// enable P4 level change to wakeup, P4 input@pullup vs P4 output@0xFF, so low action
    
//  SAFE_MOD = 0x55;
//	SAFE_MOD = 0xAA;
//	WAKE_CTRL = bWAK_BY_USB | bWAK_RXD0_LO;  // USB或者RXD0有信号时可被唤醒
   
	PCON |= PD;	// sleep
   
//	SAFE_MOD = 0x55;
//	SAFE_MOD = 0xAA;
//	WAKE_CTRL = 0x00;
    
//	wakeup if P4 low
	_nop_( );
	PORT_CFG = savePortCfg;
	if ( GPIO_IE & bIE_IO_EDGE ) {	// edge mode interrupt
		GPIO_IE &= ~ bIE_IO_EDGE;	// clear P4 level change interrupt flag
		GPIO_IE |= bIE_IO_EDGE;
	}
    savePortCfg = USB_CTRL;
    USB_CTRL |= bUX_DP_PU_EN|bUX_DM_PU_EN;
    mDelaymS(30);  
    USB_CTRL ^= savePortCfg;
       
	P0 = P3 = 0xFF;  // COMMON pin invert output
//	P7 |= 0x03;	// if P7 used for COMMON
//  check key or by RGB interrupt
    LED_CTRL = bLED_IE_INHIB | bLED_BLUE_EN | bLED_GREEN_EN | bLED_RED_EN | bLED_COM_AHEAD |bLED_PWM_INHIB | bLED_EN;
	LED_STATUS |= bLED_IF_SET;  // force bLED_IF to enter interrupt service 
	IE_PWM_I2C = 1;
    
	EA = 1;
    putchar(0x56);
    
}
void	USB_DeviceInterrupt( void ) interrupt INT_NO_USB using 1
{
    UINT8 len,us,i;
    static	UINT8	D0SetupReqCode, D0SetupLen,CMD;
    static	PUINT8	pD0Descr;
USB_DevIntNext:
    us = USB_IF; 
    if(us & bUX_IF_D0_TRANS)            /*D0数据传输完成*/
    {
        switch(D0_STATUS & ( bUXS_SETUP_ACT | MASK_UXS_TOKEN | MASK_UXS_ENDP ))     // 分析操作令牌和端点号
        {
            case UXS_TOKEN_IN | 0:                       // endpoint 0# IN  
            case bUXS_SETUP_ACT | UXS_TOKEN_IN | 0:
                switch( D0SetupReqCode ) {
					case USB_GET_DESCRIPTOR:
						len = D0SetupLen >= THIS_ENDP0_SIZE ? THIS_ENDP0_SIZE : D0SetupLen;  // 本次传输长度
						memcpy( pD0_EP0_BUF, pD0Descr, len );  /* 加载上传数据 */
						D0SetupLen -= len;
						pD0Descr += len;
						D0_EP0T_L = len;
						D0_EP0RES ^= bUEP_T_TOG;  // 翻转
						break;
					case USB_SET_ADDRESS:
						D0_ADDR = D0SetupLen;
						D0_EP0RES = UEP_R_RES_ACK | UEP_T_RES_NAK;
						break;
					default:
						D0_EP0T_L = 0;  // 状态阶段完成中断或者是强制上传0长度数据包结束控制传输
						D0_EP0RES = UEP_R_RES_ACK | UEP_T_RES_NAK;
						break;
				}
                break;
            case UXS_TOKEN_OUT | 2:  //  endpoint 2# 端点下传
            case bUXS_SETUP_ACT | UXS_TOKEN_OUT | 2:
                if ( D0_STATUS & bUXS_TOG_OK ) {  // 不同步的数据包将丢弃
						len = D0_RX_LEN;
                        if(((pUSB_BUF_DEV0+UX_EP2_ADDR)[0] == PACKAGE1) && ((pUSB_BUF_DEV0+UX_EP2_ADDR)[1] == PACKAGE2)){
                            CMD = (pUSB_BUF_DEV0+UX_EP2_ADDR)[2];
                            switch(CMD){
                                case Get_RGBMODEL:
                                     memset(pUSB_BUF_DEV0+UX_EP3_ADDR,0,64);
                                    (pUSB_BUF_DEV0+UX_EP3_ADDR)[0] =  PACKAGE1; 
                                    (pUSB_BUF_DEV0+UX_EP3_ADDR)[1] =  PACKAGE2;
                                    (pUSB_BUF_DEV0+UX_EP3_ADDR)[2] =  RGBMode;
                                    D0_EP3T_L = len;
                                    D0_EP3RES = D0_EP3RES & ~MASK_UEP_X_RES | UEP_X_RES_ACK; // 上传
                                    break;
                                case Set_RGBMODEL:                                  
                                    RGBMode =(pUSB_BUF_DEV0+UX_EP2_ADDR)[4];
                                    LED_GRE_ADJ = 0;
                                     memset(pUSB_BUF_DEV0+UX_EP3_ADDR,0,64);
                                    (pUSB_BUF_DEV0+UX_EP3_ADDR)[0] =  PACKAGE1; 
                                    (pUSB_BUF_DEV0+UX_EP3_ADDR)[1] =  PACKAGE2;
                                    (pUSB_BUF_DEV0+UX_EP3_ADDR)[2] =  RGBMode;
                                    D0_EP3T_L = len;
                                    D0_EP3RES = D0_EP3RES & ~MASK_UEP_X_RES | UEP_X_RES_ACK; // 上传
                                    break;
                                case Get_RGBDATA: 
                                    USB_IO=56;                                    
                                    memset(pUSB_BUF_DEV0+UX_EP3_ADDR,0,64);
                                    (pUSB_BUF_DEV0+UX_EP3_ADDR)[0] =  PACKAGE1; 
                                    (pUSB_BUF_DEV0+UX_EP3_ADDR)[1] =  PACKAGE2;
                                    (pUSB_BUF_DEV0+UX_EP3_ADDR)[2] =  0xFA;
                                    (pUSB_BUF_DEV0+UX_EP3_ADDR)[3] =  0xFA;
                                    (pUSB_BUF_DEV0+UX_EP3_ADDR)[4] =  USB_IO;
                                    (pUSB_BUF_DEV0+UX_EP3_ADDR)[5] =  USB_IO>>8;
                                    (pUSB_BUF_DEV0+UX_EP3_ADDR)[6] =  0;
                                    (pUSB_BUF_DEV0+UX_EP3_ADDR)[7] =  0;
                                    memcpy(&(pUSB_BUF_DEV0+UX_EP3_ADDR)[8],USBRGBdataBuffer,USB_IO);
                                   
                                    D0_EP3T_L = len;
                                    D0_EP3RES = D0_EP3RES & ~MASK_UEP_X_RES | UEP_X_RES_ACK; // 上传
                                    break;
                                case Set_RGBDATA:
                                    i=(pUSB_BUF_DEV0+UX_EP2_ADDR)[4];
                                    memcpy(USBRGBdataBuffer+USB_IO,&(pUSB_BUF_DEV0+UX_EP2_ADDR)[8],i);
                                    USB_IO += i;
                                    memset(pUSB_BUF_DEV0+UX_EP3_ADDR,0,64);
                                    (pUSB_BUF_DEV0+UX_EP3_ADDR)[0] =  PACKAGE1; 
                                    (pUSB_BUF_DEV0+UX_EP3_ADDR)[1] =  PACKAGE2;
                                    (pUSB_BUF_DEV0+UX_EP3_ADDR)[2] =  0xFA; 
                                    (pUSB_BUF_DEV0+UX_EP3_ADDR)[3] =  0xFA;
                                    (pUSB_BUF_DEV0+UX_EP3_ADDR)[4] =  USB_IO;
                                    (pUSB_BUF_DEV0+UX_EP3_ADDR)[5] =  USB_IO>>8;
                                    D0_EP3T_L = len;
                                    D0_EP3RES = D0_EP3RES & ~MASK_UEP_X_RES | UEP_X_RES_ACK; // 上传
                                    break;
                                default:break;
                            }
                        }
                    }
                break;           
            case UXS_TOKEN_IN | 3:  // endpoint 3# 端点上传完成
            case bUXS_SETUP_ACT | UXS_TOKEN_IN | 3:
                D0_EP3RES = D0_EP3RES & ~MASK_UEP_X_RES | UEP_X_RES_NAK; // 暂停上传
                if(CMD == Get_RGBDATA){
                    if(USB_IO>=128*4) {
                        USB_IO = 0;
                        break;
                    }
                    i = (128*4-USB_IO)>=56?56:(128*4-USB_IO);
                    memset(pUSB_BUF_DEV0+UX_EP3_ADDR,0,64);
                    (pUSB_BUF_DEV0+UX_EP3_ADDR)[0] =  PACKAGE1; 
                    (pUSB_BUF_DEV0+UX_EP3_ADDR)[1] =  PACKAGE2;
                    (pUSB_BUF_DEV0+UX_EP3_ADDR)[2] =  0xFA;
                    (pUSB_BUF_DEV0+UX_EP3_ADDR)[3] =  0xFA;
                    
                    (pUSB_BUF_DEV0+UX_EP3_ADDR)[4] =  i;
                    (pUSB_BUF_DEV0+UX_EP3_ADDR)[5] =  0;
                    (pUSB_BUF_DEV0+UX_EP3_ADDR)[6] =  USB_IO;
                    (pUSB_BUF_DEV0+UX_EP3_ADDR)[7] =  USB_IO>>8;
                    
                    memcpy(&(pUSB_BUF_DEV0+UX_EP3_ADDR)[8],USBRGBdataBuffer+USB_IO,i);
                    USB_IO+=i;
                    D0_EP3T_L = len;
                    D0_EP3RES = D0_EP3RES & ~MASK_UEP_X_RES | UEP_X_RES_ACK; // 上传
                }
                
                break;
            case UXS_TOKEN_IN | 1:  // endpoint 2# 端点上传完成
            case bUXS_SETUP_ACT | UXS_TOKEN_IN | 1:
                FLAG = 1;
                D0_EP1RES = D0_EP1RES & ~MASK_UEP_X_RES | UEP_X_RES_NAK; // 暂停上传
                break;
            case bUXS_SETUP_ACT | UXS_TOKEN_FREE | 0:    // endpoint 0# SETUP
            case bUXS_SETUP_ACT | UXS_TOKEN_FREE | 1:    
            case bUXS_SETUP_ACT | UXS_TOKEN_FREE | 2:    
            case bUXS_SETUP_ACT | UXS_TOKEN_FREE | 3:    
            case bUXS_SETUP_ACT | UXS_TOKEN_FREE | 4:    
            case bUXS_SETUP_ACT | UXS_TOKEN_FREE | 5:    
            case bUXS_SETUP_ACT | UXS_TOKEN_FREE | 6:    
            case bUXS_SETUP_ACT | UXS_TOKEN_FREE | 7:    
                D0SetupLen = pD0_SETUP_REQ->wLengthL;
                if(pD0_SETUP_REQ->wLengthH ||D0SetupLen > MAX_DESCR_SIZE) D0SetupLen = MAX_DESCR_SIZE;  // 限制总长度
                len = 0;  // 默认为成功并且上传0长度
                D0SetupReqCode = pD0_SETUP_REQ->bRequest;
                if((pD0_SETUP_REQ->bRequestType & USB_REQ_TYP_MASK ) == USB_REQ_TYP_STANDARD ){ /* 标准请求 */                                   
                    switch( D0SetupReqCode ) {  
                        case USB_GET_DESCRIPTOR:            //描述符
                            switch(pD0_SETUP_REQ->wValueH){
                                case USB_DESCR_TYP_DEVICE:  // 设备描述符
                                    pD0Descr = (PUINT8)( &MyDevDescr[0] );
                                    len = sizeof( MyDevDescr );
                                    break;
                                case USB_DESCR_TYP_CONFIG:  // 配置描述符
									pD0Descr = (PUINT8)( &MyCfgDescr[0] );
									len = sizeof( MyCfgDescr );
									break;
                                case USB_DESCR_TYP_STRING:  // 字符串描述符
									switch( pD0_SETUP_REQ->wValueL ) {
										case 1:
											pD0Descr = (PUINT8)( &MyManuInfo[0] );
											len = sizeof( MyManuInfo );
											break;
										case 2:
											pD0Descr = (PUINT8)( &MyProdInfo[0] );
											len = sizeof( MyProdInfo );
											break;
										case 0:
											pD0Descr = (PUINT8)( &MyLangDescr[0] );
											len = sizeof( MyLangDescr );
											break;
										default:
											len = 0xFF;  // 不支持的字符串描述符
											break;
										}
										break;
							  case USB_DESCR_TYP_REPORT:  // 报表描述符
                                   switch( pD0_SETUP_REQ->wIndexL ) {       //选择接口
										case 1:
											 pD0Descr = MY_HID_Report_Desc;      //数据准备上传
                                             len = sizeof(MY_HID_Report_Desc);
											break;									
										case 0:
											pD0Descr = KeyRepDesc;          //数据准备上传
                                            len = sizeof(KeyRepDesc);
											break;
										default:
											len = 0xFF;  // 不支持的字符串描述符
											break;
										}
									break;
							
							 default:
									len = 0xFF;  // 不支持的描述符类型
									break;
                                        
                            }
                            if ( D0SetupLen > len ) D0SetupLen = len;  // 限制总长度
							len = D0SetupLen >= THIS_ENDP0_SIZE ? THIS_ENDP0_SIZE : D0SetupLen;  // 本次传输长度
                            D0SetupLen -= len;
                            memcpy( pD0_EP0_BUF, pD0Descr, len );  /* 加载上传数据 */
							pD0Descr += len;
                            break;
                        case USB_SET_ADDRESS:               // 暂存USB设备地址
                            D0SetupLen = pD0_SETUP_REQ->wValueL;  // 暂存USB设备地址
                            break;
                        case USB_GET_CONFIGURATION:
                            pD0_EP0_BUF[0] = UsbConfig;
							if ( D0SetupLen >= 1 ) len = 1;
							break;
                            break;
                        case USB_SET_CONFIGURATION:
                            UsbConfig = pD0_SETUP_REQ->wValueL;
                            FLAG = 1;
                            break;
                        case USB_SET_FEATURE:
                                if(pD0_SETUP_REQ->wValueL == 1){ //设置睡眠
                                    sleep = 1;             
                                }else{
                                    len = 0xFF;
                                }
                            break;
                        case USB_CLEAR_FEATURE:
                            if ( ( pD0_SETUP_REQ->bRequestType & USB_REQ_RECIP_MASK ) == USB_REQ_RECIP_ENDP ) {  // 端点
                                switch( pD0_SETUP_REQ->wIndexL ) {
                                    case 0x82:
                                        D0_EP2RES = D0_EP2RES & ~ ( bUEP_X_TOG | MASK_UEP_X_RES ) | UEP_X_RES_NAK;
                                        break;
                                    case 0x02:
                                        D0_EP2RES = D0_EP2RES & ~ ( bUEP_X_TOG | MASK_UEP_X_RES ) | UEP_X_RES_ACK;
                                        break;
                                    case 0x81:
                                        D0_EP1RES = D0_EP1RES & ~ ( bUEP_X_TOG | MASK_UEP_X_RES ) | UEP_X_RES_NAK;
                                        break;
                                    case 0x01:
                                        D0_EP1RES = D0_EP1RES & ~ ( bUEP_X_TOG | MASK_UEP_X_RES ) | UEP_X_RES_ACK;
                                        break;
                                    default:
                                        len = 0xFF;  // 不支持的端点
                                        break;
                                    }
								}
								else len = 0xFF;  // 不是端点不支持
                            break;
                        case USB_GET_INTERFACE:
                            pD0_EP0_BUF[0] = 0x00;
                            if ( D0SetupLen >= 1 ) len = 1;
                            break;
                        case USB_GET_STATUS: 
                            pD0_EP0_BUF[0] = 0x00;
							pD0_EP0_BUF[1] = 0x00;
							if ( D0SetupLen >= 2 ) len = 2;
							else len = D0SetupLen;
                            break;
                        default:
                            len = 0xFF;  // 操作失败
                            break;
                        
                    }
                }else if ( ( pD0_SETUP_REQ->bRequestType & USB_REQ_TYP_MASK ) != USB_REQ_TYP_STANDARD ) {  /* 非标准请求 */
                     switch( D0SetupReqCode )
                    {
                        case 0x01://GetReport
                            break;
                        case 0x02://GetIdle
                            break;
                        case 0x03://GetProtocol
                            break;
                        case 0x09://SetReport
                                Feature = pD0_SETUP_REQ->wValueH;
                            break;
                        case 0x0A://SetIdle
                            break;
                        case 0x0B://SetProtocol
                            break;
                        default:
                            len = 0xFF;                                  /*命令不支持*/
                            break;
                     }
                }else{  /* 只支持标准请求/类请求 */
                    len = 0xFF;  // 操作失败
#if DEBUG
					printf("ErrEp0ReqType=%02X\n",(UINT16)pD0_SETUP_REQ->bRequestType);
#endif
				}
            if ( len == 0xFF ) {  // 操作失败
				D0SetupReqCode = 0xFF;
				D0_EP0RES = bUEP_R_TOG | bUEP_T_TOG | UEP_R_RES_STALL | UEP_T_RES_STALL;  // STALL
			}
			else if ( len <= THIS_ENDP0_SIZE ) {  // 上传数据或者状态阶段返回0长度包
               
				D0_EP0T_L = len;
				D0_EP0RES = bUEP_R_TOG | bUEP_T_TOG | UEP_R_RES_ACK | UEP_T_RES_ACK;  // 默认数据包是DATA1    
			}
			else {  // 下传数据或其它
				D0_EP0T_L = 0;  // 虽然尚未到状态阶段，但是提前预置上传0长度数据包以防主机提前进入状态阶段
				D0_EP0RES = bUEP_R_TOG | bUEP_T_TOG | UEP_R_RES_ACK | UEP_T_RES_ACK;  // 默认数据包是DATA1
			}
            
            break;
            case UXS_TOKEN_OUT | 0:  // endpoint 0# OUT
            case bUXS_SETUP_ACT | UXS_TOKEN_OUT | 0:
                	switch(D0SetupReqCode ) {
                        case HID_SET_REPORT: 
                                if(Feature == 0x02)//点灯
							 {
                                 
								  if( (pUSB_BUF_DEV0+UX_EP1_ADDR)[0] & 0x01 ){
								  //	P5_OUT_PU &= 0x7F;
								  }
								  else{
								//	P5_OUT_PU |= 0x80;
								  }
								  if( (pUSB_BUF_DEV0+UX_EP1_ADDR)[0] & 0x02 ){
								  //	P5_OUT_PU &= 0xBF;
								  }
								  else{
								  //	P5_OUT_PU |= 0x40;
								  }
								  if( (pUSB_BUF_DEV0+UX_EP1_ADDR)[0] & 0x04 ){
								 // 	P5_OUT_PU &= 0xDF;
								  }
								  else{
								 // 	P5_OUT_PU |= 0x20;
							    } 
							 }
                            D0_EP0RES ^= bUEP_R_TOG;
                         //   D0_EP0RES |= UEP_R_RES_ACK | UEP_T_RES_ACK;  // 默认数据包是DATA1    
                        break;
						case USB_GET_DESCRIPTOR:
						default:
							if ( D0_STATUS & bUXS_TOG_OK ) {  // 不同步的数据包将丢弃

							}
							D0_EP0RES = UEP_R_RES_ACK | UEP_T_RES_NAK;  // 准备下一控制传输
							break;
					}
                break;
                        default:
#if DEBUG
            printf("ErrEndp\n");            
#endif
                            break;
                
        }
       // UIF_USBX_IF = 0;
        D0_STATUS = 0;
        //USB_IF |= bUX_IF_D0_TRANS;
    }else if(us & bUX_IF_SUSPEND)/*挂起或者唤醒事件*/
    {
        USB_IF |= bUX_IF_SUSPEND;
        if(us & bUX_SUSPEND){       //挂起
#if DEBUG
        printf("zzz...\n");
#endif   
          if(sleep)// sleep
               SleepWithKey();
        }else{                      //唤醒
            sleep = 0;
            
        }
//         USB_IF |= bUX_IF_SUSPEND;
    }else if(us & bUX_IF_BUS_RST) /*总线复位事件*/
    {
#if DEBUG
        printf("reset...\n");
#endif 
        USB_CTRL = 0;
        D0_EP0RES = UEP_R_RES_ACK | UEP_T_RES_NAK;
        D0_EP1RES = bUEP_X_AUTO_TOG | UEP_X_RES_NAK;
       	D0_EP2RES = bUEP_X_AUTO_TOG | UEP_X_RES_ACK;
        D0_EP3RES = bUEP_X_AUTO_TOG | UEP_X_RES_NAK;
        
        D0_EP_MOD = bUX_EP2O_EN|bUX_DEV_EN;  
        D0_ADDR = 0;
        HB_ADDR = 0x7F;             //将收到的数据直接转发到D0
        USB_IF = 0xFF;
        FLAG = 0;
        USB_IE = bUX_IE_SUSPEND|bUX_IE_TRANSFER|bUX_IE_BUS_RST;
        USB_CTRL = bUX_DP_PU_EN;
        USB_IF |= bUX_IF_BUS_RST;
    }else/*是不需要处理的中断，直接清*/
    {
#if DEBUG
        printf("@@@\n");
#endif
        D0_STATUS = 0;
    }
    
    if(USB_IF &(bUX_IF_D0_TRANS|bUX_IF_SUSPEND|bUX_IF_BUS_RST)) goto USB_DevIntNext;

    
}


void	InitUSB_Device( void )  // 初始化USB设备
{
	IE_USB = 0;
	IP_EX &= ~bIP_USB;
    
	SAFE_MOD = 0x55;
	SAFE_MOD = 0xAA;
	GLOBAL_CFG |= bXIR_XSFR;                         
    
    /*设定模式,数据缓冲区都是固定地址*/
    USB_CTRL = 0;
    D0_EP0RES = UEP_R_RES_ACK | UEP_T_RES_NAK;
    D0_EP1RES = bUEP_X_AUTO_TOG | UEP_X_RES_NAK;
	D0_EP2RES = bUEP_X_AUTO_TOG | UEP_X_RES_ACK;
    D0_EP3RES = bUEP_X_AUTO_TOG | UEP_X_RES_NAK;
    
    D0_EP_MOD = bUX_EP2O_EN|bUX_DEV_EN; 
    D0_ADDR = 0;
    HB_ADDR = 0x7F;             //将收到的数据直接转发到D0
    FLAG = 0;
    USB_IF = 0xFF;
    USB_IE = bUX_IE_SUSPEND|bUX_IE_TRANSFER|bUX_IE_BUS_RST;
    USB_CTRL = bUX_DP_PU_EN; 
	IE_USB = 1;
}
