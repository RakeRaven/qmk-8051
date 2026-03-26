/********************************** (C) COPYRIGHT *******************************
* File Name          : DEBUG.C
* Author             : WCH
* Version            : V1.3
* Date               : 2016/06/24
* Description        : CH555 DEBUG Interface
                     (1)、串口0输出打印信息，波特率可变;              				   
*******************************************************************************/
#include "DEBUG.H"
/*******************************************************************************
* Function Name  : CfgFsys( )
* Description    : CH555时钟选择和配置函数,默认使用内部晶振12MHz，如果定义了FREQ_SYS可以
                   根据PLL_CFG和CLOCK_CFG配置得到，公式如下：
                   Fsys = (Fosc * ( PLL_CFG & MASK_PLL_MULT ))/(CLOCK_CFG & MASK_SYS_CK_DIV);
                   具体时钟需要自己配置
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/ 
void	CfgFsys( )  
{
#if OSC_EN_XT	
		SAFE_MOD = 0x55;
		SAFE_MOD = 0xAA;
    CLOCK_CFG |= bOSC_EN_XT;                          //使能外部晶振
    CLOCK_CFG &= ~bOSC_EN_INT;                        //关闭内部晶振 
#else
		SAFE_MOD = 0x55;
		SAFE_MOD = 0xAA;
    CLOCK_CFG |= bOSC_EN_INT;                        //使能内部晶振 
    CLOCK_CFG &= ~bOSC_EN_XT;                        //关闭外部晶振	
#endif	
		SAFE_MOD = 0x55;
		SAFE_MOD = 0xAA;
#if FREQ_SYS == 48000000	
		CLOCK_CFG = CLOCK_CFG & ~ MASK_SYS_CK_SEL | 0x07;  // 48MHz	
#endif	
#if FREQ_SYS == 32000000	
		CLOCK_CFG = CLOCK_CFG & ~ MASK_SYS_CK_SEL | 0x06;  // 32MHz	
#endif	
#if FREQ_SYS == 24000000		
		CLOCK_CFG = CLOCK_CFG & ~ MASK_SYS_CK_SEL | 0x05;  // 24MHz	
#endif
#if FREQ_SYS == 16000000		
		CLOCK_CFG = CLOCK_CFG & ~ MASK_SYS_CK_SEL | 0x04;  // 16MHz
#endif	
#if FREQ_SYS == 12000000		
		CLOCK_CFG = CLOCK_CFG & ~ MASK_SYS_CK_SEL | 0x03;  // 12MHz	
#endif	
#if FREQ_SYS == 3000000	
		CLOCK_CFG = CLOCK_CFG & ~ MASK_SYS_CK_SEL | 0x02;  // 3MHz	
#endif
#if FREQ_SYS == 750000	
		CLOCK_CFG = CLOCK_CFG & ~ MASK_SYS_CK_SEL | 0x01;  // 750KHz
#endif
#if FREQ_SYS == 187500	
		CLOCK_CFG = CLOCK_CFG & ~ MASK_SYS_CK_SEL | 0x00;  // 187.5KHz	
#endif
		SAFE_MOD = 0x00;
}

/*******************************************************************************
* Function Name  : mDelayus(UNIT16 n)
* Description    : us延时函数
* Input          : UNIT16 n
* Output         : None
* Return         : None
*******************************************************************************/ 
void	mDelayuS( UINT16 n )  // 以uS为单位延时
{
	while ( n ) {  // total = 12~13 Fsys cycles, 1uS @Fsys=12MHz
		++ SAFE_MOD;  // 2 Fsys cycles, for higher Fsys, add operation here
#ifdef	FREQ_SYS
#if		FREQ_SYS >= 14000000
		++ SAFE_MOD;
#endif
#if		FREQ_SYS >= 16000000
		++ SAFE_MOD;
#endif
#if		FREQ_SYS >= 18000000
		++ SAFE_MOD;
#endif
#if		FREQ_SYS >= 20000000
		++ SAFE_MOD;
#endif
#if		FREQ_SYS >= 22000000
		++ SAFE_MOD;
#endif
#if		FREQ_SYS >= 24000000
		++ SAFE_MOD;
#endif
#if		FREQ_SYS >= 26000000
		++ SAFE_MOD;
#endif
#if		FREQ_SYS >= 28000000
		++ SAFE_MOD;
#endif
#if		FREQ_SYS >= 30000000
		++ SAFE_MOD;
#endif
#if		FREQ_SYS >= 32000000
		++ SAFE_MOD;
#endif
#if		FREQ_SYS >= 34000000
		++ SAFE_MOD;
#endif
#if		FREQ_SYS >= 36000000
		++ SAFE_MOD;
#endif
#if		FREQ_SYS >= 38000000
		++ SAFE_MOD;
#endif
#if		FREQ_SYS >= 40000000
		++ SAFE_MOD;
#endif
#if		FREQ_SYS >= 42000000
		++ SAFE_MOD;
#endif
#if		FREQ_SYS >= 44000000
		++ SAFE_MOD;
#endif
#if		FREQ_SYS >= 46000000
		++ SAFE_MOD;
#endif
#if		FREQ_SYS >= 48000000
		++ SAFE_MOD;
#endif
#if		FREQ_SYS >= 50000000
		++ SAFE_MOD;
#endif
#if		FREQ_SYS >= 52000000
		++ SAFE_MOD;
#endif
#if		FREQ_SYS >= 54000000
		++ SAFE_MOD;
#endif
#if		FREQ_SYS >= 56000000
		++ SAFE_MOD;
#endif
#endif
		-- n;
	}
}


/*******************************************************************************
* Function Name  : mDelayms(UNIT16 n)
* Description    : ms延时函数
* Input          : UNIT16 n
* Output         : None
* Return         : None
*******************************************************************************/
void	mDelaymS( UINT16 n )                                                  // 以mS为单位延时
{
	while ( n ) 
	{
		mDelayuS( 1000 );
		-- n;
	}
}                                         

/*******************************************************************************
* Function Name  : CH555UART0Alter()
* Description    : CH555串口0引脚映射
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void CH555UART0Alter()
{
     PIN_FUNC |= bUART0_PIN_X;
}

/*******************************************************************************
* Function Name  : mInitSTDIO()
* Description    : CH555串口0初始化,默认使用T1作UART0的波特率发生器,也可以使用T2
                   作为波特率发生器
* Input          : None
* Output         : None+
* Return         : None
*******************************************************************************/
void	mInitSTDIO( )
{
    UINT32 x;
    UINT8 x2; 

    SM0 = 0;
    SM1 = 1;
    SM2 = 0;                                                                   //串口0使用模式1
                                                                               //使用Timer1作为波特率发生器
    RCLK = 0;                                                                  //UART0接收时钟
    TCLK = 0;                                                                  //UART0发送时钟
    PCON |= SMOD;
    x = 10 * FREQ_SYS / DEBUGBUAD / 16;                                             //如果更改主频，注意x的值不要溢出                            
    x2 = x % 10;
    x /= 10;
    if ( x2 >= 5 ) x ++;                                                       //四舍五入

    TMOD = TMOD & ~ bT1_GATE & ~ bT1_CT & ~ MASK_T1_MOD | bT1_M1;              //0X20，Timer1作为8位自动重载定时器
    T2MOD = T2MOD | bTMR_CLK | bT1_CLK;                                        //Timer1时钟选择
    TH1 = 0-x;                                                                 //12MHz晶振,buad/12为实际需设置波特率
    TR1 = 1;                                                                   //启动定时器1
    TI = 1;
//    REN = 1;                                                                   //串口0接收使能
}

/*******************************************************************************
* Function Name  : putchar
* Description    : 通过调试引脚输出字符(921600bps@48MHZ)
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
char putchar( char c )
{
	E_DIS = 1;
	
	/* 起始位 */
	//PIN_DEBUG = 0;
    PIN_DEBUG &= ~(1<<2);
	_nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); 
	_nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); 
	_nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_();
	_nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_();
	_nop_(); _nop_(); _nop_(); _nop_(); 
	
	/* BIT0 */
//	PIN_DEBUG = c & 0x01;
    if( c & 0x01)  PIN_DEBUG |= (1<<2);
    else PIN_DEBUG &= ~(1<<2);
	c >>= 1;
	_nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); 
	_nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); 
	_nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_();
	_nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_();
	_nop_(); _nop_(); _nop_(); _nop_();   

	/* BIT1 */
//	PIN_DEBUG = c & 0x01;
    if( c & 0x01)  PIN_DEBUG |= (1<<2);
    else PIN_DEBUG &= ~(1<<2);
	c >>= 1;
	_nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); 
	_nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); 
	_nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_();
	_nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_();
	_nop_(); _nop_(); _nop_(); _nop_();  
	
	/* BIT2 */
//	PIN_DEBUG = c & 0x01;
    if( c & 0x01)  PIN_DEBUG |= (1<<2);
    else PIN_DEBUG &= ~(1<<2);
	c >>= 1;
	_nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); 
	_nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); 
	_nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_();
	_nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_();
	_nop_(); _nop_(); _nop_(); _nop_();  
		
	/* BIT3 */
//	PIN_DEBUG = c & 0x01;
    if( c & 0x01)  PIN_DEBUG |= (1<<2);
    else PIN_DEBUG &= ~(1<<2);
	c >>= 1;
	_nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); 
	_nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); 
	_nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_();
	_nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_();
	_nop_(); _nop_(); _nop_(); _nop_();  

	/* BIT4 */
//	PIN_DEBUG = c & 0x01;
    if( c & 0x01)  PIN_DEBUG |= (1<<2);
    else PIN_DEBUG &= ~(1<<2);
	c >>= 1;
	_nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); 
	_nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); 
	_nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_();
	_nop_(); _nop_(); _nop_(); _nop_(); 
	  
	/* BIT5 */
//	PIN_DEBUG = c & 0x01;
    if( c & 0x01)  PIN_DEBUG |= (1<<2);
    else PIN_DEBUG &= ~(1<<2);
	c >>= 1;
	_nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); 
	_nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); 
	_nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_();
	_nop_(); _nop_(); _nop_(); _nop_();  
	 

	/* BIT6 */
//	PIN_DEBUG = c & 0x01;
    if( c & 0x01)  PIN_DEBUG |= (1<<2);
    else PIN_DEBUG &= ~(1<<2);
	c >>= 1;
	_nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); 
	_nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); 
	_nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_();
	_nop_(); _nop_(); _nop_(); _nop_(); 
	

	/* BIT7 */
//	PIN_DEBUG = c & 0x01;
    if( c & 0x01)  PIN_DEBUG |= (1<<2);
    else PIN_DEBUG &= ~(1<<2);
	c >>= 1;
	_nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); 
	_nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); 
	_nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_();
	_nop_(); _nop_(); _nop_(); _nop_(); 
	 

//	PIN_DEBUG = 1;
    PIN_DEBUG |= (1<<2); 
    _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); 
	_nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); 
	_nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_();
	_nop_(); _nop_(); _nop_(); _nop_();
	E_DIS = 0;
	return( c );
}
