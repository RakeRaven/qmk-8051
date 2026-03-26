/* 调试 */
/* 提供printf子程序和延时函数 */

#ifndef	__DEBUG_H__
#define __DEBUG_H__

#include <absacc.h>
#include <CH555.H>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <intrins.h>

//定义函数返回值
#ifndef  SUCCESS
#define  SUCCESS  1
#endif
#ifndef  FAIL
#define  FAIL    0
#endif

//定义定时器起始
#ifndef  START
#define  START  1
#endif
#ifndef  STOP
#define  STOP    0
#endif

#define	 FREQ_SYS        	48000000	                                                   //系统主频
#define  OSC_EN_XT          0
#ifndef  DEBUGBUAD
#define  DEBUGBUAD          115200
#endif

#define DEBUG               0

#define PIN_DEBUG           P6_OUT_PU    
void	CfgFsys( );                        //CH555时钟选择和配置
void	mDelayuS( UINT16 n );              // 以uS为单位延时
void	mDelaymS( UINT16 n );              // 以mS为单位延时
void    CH555UART0Alter();                //CH55串口0引脚映射
void	mInitSTDIO( );                     //T1作为波特率发生器


#endif
