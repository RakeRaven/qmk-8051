#ifndef __RGBLED_H__
#define __RGBLED_H__

#ifdef __cplusplus
extern "C" {
#endif
 
//CH559 Timer1时钟选择   
//bTMR_CLK同时影响Timer0&1&2,使用时要注意                                                       
#define mTimer1ClkFsys( ) (T2MOD |= bTMR_CLK | bT1_CLK)                     //定时器,时钟=Fsys
#define mTimer1Clk4DivFsys( ) (T2MOD &= ~bTMR_CLK;T2MOD |=  bT1_CLK)        //定时器,时钟=Fsys/4
#define mTimer1Clk12DivFsys( ) (T2MOD &= ~(bTMR_CLK | bT1_CLK))             //定时器,时钟=Fsys/12
#define mTimer1CountClk( ) (TMOD |= bT1_CT)                                 //计数器,T1引脚的下降沿有效

//CH559 Timer1 开始(SS=1)/结束(SS=0)
#define mTimer1RunCTL( SS ) (TR1 = SS ? START : STOP)
    
void InitRGBLED( void );
void showLogo(void);
void init_Timer(void);  
void paramInit();   
#ifdef __cplusplus
}
#endif

#endif