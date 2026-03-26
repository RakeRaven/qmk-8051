#include "usb.h"
#include "rgbled.h"
#include "debug.h"


extern UINT8 UsbConfig;
extern bit key_up;
extern UINT8X key_buf[8];
extern void key_up_data( UINT8 *pupdata,UINT8 len ); 

void main(){
    CfgFsys( );
    mDelaymS(20);
    
    paramInit();
#if DEBUG
	mInitSTDIO( );  /* Ϊ���ü����ͨ�����ڼ����ʾ���� */
    CH555UART0Alter();
	printf("ID=%02X\n", (UINT16)CHIP_ID );
#endif   
     P6_OUT_PU |= (1<<2);//debug
     P6_DIR |= (1<<2);          
    
         
    InitUSB_Device();
    EA = 1; 
    while(!UsbConfig);
    mDelaymS(10);
    
    InitRGBLED( ); 
    LED_RED_ADJ = 0;
    LED_GRE_ADJ = 0;
    LED_BLU_ADJ = 0;

        
    showLogo();
    init_Timer();           
    
    while(1){  
      if(key_up){
        key_up_data(key_buf,8);
        key_up = 0;
      }        
  }
}