#ifndef __USB_H__
#define __USB_H__

#ifdef __cplusplus
extern "C" {
#endif
#include "DEBUG.H"
#define PACKAGE1    0x57
#define PACKAGE2    0xAB 

    
#define   Get_RGBMODEL  0x01
#define   Set_RGBMODEL  0x02  
#define   Get_RGBDATA   0x03
#define   Set_RGBDATA   0x04     
typedef struct				//数据位对齐
{
	UINT8 first;		
	UINT8 second;	    

	UINT8 cmd1;		    
	UINT8 cmd2;		    
    
    UINT8 cou1;		
	UINT8 cou2;		

	UINT8 len1;		    
	UINT8 len2;		

    UINT8 dat[56];

}HID_VALUE;  

#define pHID_VALUE     ((HID_VALUE *)pUSB_BUF_DEV0+UX_EP2_ADDR)    
void	InitUSB_Device( void );

#ifdef __cplusplus
}
#endif

#endif