
#include "DEBUG.H"
#include "rgbled.h"

BOOL  data	 IsCode;
UINT16D	 BufferAddr;
UINT8X	RGBdataBuffer[128][4]={0};      
UINT8X	RGBdataBuffer1[128][4]={0};  

#define Mode_0      0           //全暗
#define Mode_1      1           //全亮
#define Mode_2      2           //呼吸灯
#define Mode_3      3           //闪烁
#define Mode_4      4           //跟随按键，随机色
UINT8I RGB_stauts = 0;          //RGB色彩转换时，用作状态为
UINT8D RGBMode=0;               //RGB模式
UINT8I timeCount=0;             //计时器
signed char data incre=0;

void	InitRGBLED( void )
{ 
	P4 = P2 = P1 = 0xFF;  // R/G/B PWM pins invert output, low action for sink current
	P0 = P3 = 0xFF;  // COMMON pin invert output, low action for drive external PMOS
	P4_MOD_OC = P2_MOD_OC = P1_MOD_OC = 0;  // R/G/B PWM pins push-pull output
	P0_MOD_OC = P3_MOD_OC = 0;  // COMMON pins push-pull output
	LED_CTRL = bLED_EN;
	LED_CYCLE = bLED_INTEN_CYC0; // PWM_128@color,PWM_128@intenisy,1x bLED_COLOR_CYC|  MASK_LED_INT_CYC;//
	LED_FRAME =  bLED_INH_TMR2|bLED_INH_TMR0;  // 101->8 intenisy PWM cycles, same PWM data repeat 1 time
	LED_DMA = BufferAddr = (UINT16)( &RGBdataBuffer[0] );  // buffer start address 
	IsCode = 0;           // indicate data@xRAM (1=data@flash ROM)
	LED_INT_ADJ = 0x05;  // adjust: increase intenisy
	LED_PWM_OE = 0xFE;
	LED_COMMON = 0xFF;  // preset COMMON selection, next is 0, start @interrupt
	LED_CTRL = bLED_IE_INHIB | bLED_BLUE_EN | bLED_GREEN_EN | bLED_RED_EN | bLED_COM_AHEAD |bLED_PWM_INHIB | bLED_EN;
	LED_STATUS |= bLED_IF_SET;  // force bLED_IF to enter interrupt service 
	IE_PWM_I2C = 1;
  
}


void showLogo(void)
{
    UINT8 i;
    /*变量初始化*/
      
    for(i=0;i<128;i++){
        RGBdataBuffer[i][0]=127;
        RGBdataBuffer[i][1]=255;//R
        RGBdataBuffer[i][2]=127;//G
        RGBdataBuffer[i][3]=127;//B
    }
    for(i=0;i<128;i++){
        RGBdataBuffer1[i][0]=0;
        RGBdataBuffer1[i][1]=0;//R
        RGBdataBuffer1[i][2]=0;//G
        RGBdataBuffer1[i][3]=0;//B
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
UINT8C key_board_tale[  ]=					//默认的键码表
{
//   R0   R1   R2   R3   R4   R5    R6	R7(配合光)								      (特殊按键,04)
	0x29,0x35,0x2b,0x39,0x02,0x01,0x62,0x00,//c0				//esc ~`   tab   caps-lock  shifi-L  ctr-l(特殊按键05) 
	0x3a,0x1e,0x14,0x04,0x1d,0x08,0x59,0x00,//c1				//F1  1!   Q     A          Z        win-l(特殊按键0b) 
	0x3b,0x1f,0x1a,0x16,0x1b,0x04,0x5a,0x00,//c2				//f2  2@   W     S          X        alt-l(特殊按键11)
	0x3c,0x20,0x08,0x07,0x06,0x2c,0x5b,0x00,//c3				//F3  3#   E     D          C        Space //17
	0x3d,0x21,0x15,0x09,0x19,0x40,0x5c,0x00,//c4				//F4  4$   R     F          V      	 alt-r(特殊按键1d)
	0x3e,0x22,0x17,0x0a,0x05,0x80,0x5d,0x00,//c5				//F5  5%   T     G          B        FN		//23	
                                      
	0x3f,0x23,0x1c,0x0b,0x11,0x65,0x5e,0x00,//c6				//F6  6^   Y     H          N      			//29  
	0x40,0x24,0x18,0x0d,0x10,0x10,0x5f,0x00,//c7				//F7  7&   U     J          M        Win-r(特殊按键2f)
	0x41,0x25,0x0c,0x0e,0x36,0x00,0x60,0x00,//c8				//F8  8*   I     K          <,       ctr-r(特殊按键35)
	0x42,0x26,0x12,0x0f,0x37,0x00,0x61,0x00,//c9				//F9  9    O     L          >.       		  //3b
	0x43,0x27,0x13,0x33,0x38,0x00,0x57,0x00,//c10				//F10 0    P     ;:         /?				//41
	0x44,0x2d,0x2f,0x34,0x20,0x50,0x56,0x00,//c11				//F11 -_   [{    '"        shift-r(特殊按键46)//47
	0x45,0x2e,0x30,0x28,0x52,0x51,0x55,0x00,//c12				//F12 =+   ]}    \|                                     4D
                                       
	0x46,0x2a,0x31,0x00,0x00,0x4f,0x54,0x00,//c13				//0x00 Backspace                                            53
	0x47,0x49,0x4c,0x4b,0x00,0x53,0x63,0x00,//c14				//Print-screen  Insert     Delete   0x00, 		0x00, 		左    
	0x48,0x4a,0x4d,0x4e,0x00,0x58,0x00,0x00,//c15				//Scroll-Lock   End        Home     0x00,  		上  		下
				
	
};

typedef struct				//数据位对齐
{
	UINT8 first_key_count;		//第一次按键的个数
	UINT8 first_key_buf[20];	//第一次按键的键值

	UINT8 sec_key_count;		//第二次按键的个数
	UINT8 sec_key_buf[20];		//第二次按键的键值

	UINT8 end_key_count;		//最终按键的个数
	UINT8 end_key_buf[20];		//最终按键的键值

}KEY_VALUE;

bit  scan_count = 0;    //两次全扫描标志位  
KEY_VALUE scan_key;
UINT8X back_key_buf[8];
UINT8X key_buf[8];
UINT8X  HIDKey[8] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
bit temp = 0;    //
bit key_up=0;//键值有效标志
UINT8D buf[20];   //扫描暂存
UINT8V count=0;//扫描键值数
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
  memset( back_key_buf,0x00,8 );  //保证上电初始化和key_buf一样，避免第一次传值
  memset( key_buf,0x00,8 );
  memset( buf,0xff,20 );
}

 //UINT8X  a[0x400*4]  _at_   0x01000;//USBX_SEL = bUSBX_XSFR_OFS | bUSBX_XRAM_OFS | USBX_INT & ( MASK_UX_PC_ID | MASK_UX_DEV_ID );

void enp1IntIn( )
{
   
    while(( D0_EP1RES & MASK_UEP_X_RES ) == UEP_X_RES_ACK);                  //等待上传完成，避免同时读写缓冲区
    memcpy( pUSB_BUF_DEV0+UX_EP1_ADDR, HIDKey, 8);             //加载上传数据
    putchar(55);
    putchar(HIDKey[2]);
    D0_EP1T_L = sizeof(HIDKey);                                             //上传数据长度
    D0_EP1RES = D0_EP1RES & ~ MASK_UEP_X_RES | UEP_X_RES_ACK;                //有数据时上传数据并应答ACK
}

void key_up_data( UINT8 *pupdata,UINT8 len )
{
  	UINT8 i;
	if(FLAG ){  																						//按键开始                                     
	    i = memcmp( pupdata,back_key_buf,8 );							                                //表示有按键上传
        if( i ){
			FLAG = 0;
			memcpy( &HIDKey[0],pupdata,len );
			memcpy( back_key_buf,pupdata,len );
            enp1IntIn(  );
            if(HIDKey[2] == 0x14){
                RGBMode++;
                if(RGBMode > 5) RGBMode = 0;
                LED_GRE_ADJ = 0; 
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
//扫描到按键，转换键值,由于长按多键，在第二次扫描过来时可能会改变键值顺序，以下方式是多键长按仅传第一次检测的顺序
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
	
#if 1    
	for( i=0;i<scan_key.end_key_count;i++ )
	{
		p1 = memchr( scan_key.sec_key_buf,scan_key.end_key_buf[i],num ); 
		if( p1 == 0 ){
			scan_key.end_key_buf[i]	= 0xff;
		}
	}
#endif
/*下面处理把FF数据剔除*/
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
		if( (scan_key.end_key_buf[i] == 0x04))			           //特殊按键处理SIHFT-L
		{
			key_buf[0] |= key_board_tale[ scan_key.end_key_buf[i] ];//特殊按键处理
			s = 1;
		}
		if( (scan_key.end_key_buf[i] == 0x05) ){
			key_buf[0] |= key_board_tale[ scan_key.end_key_buf[i] ];//特殊按键处理CTRL-L
			s = 1;
		}
		if( (scan_key.end_key_buf[i] == 0x0D) ){
			key_buf[0] |= key_board_tale[ scan_key.end_key_buf[i] ];//特殊按键处理WIN-L
			s = 1;
		}
		if( (scan_key.end_key_buf[i] == 0x15) ){
			key_buf[0] |= key_board_tale[ scan_key.end_key_buf[i] ];//特殊按键处理ALT-L
			s = 1;
		}
		if( (scan_key.end_key_buf[i] == 0x25) ){
			key_buf[0] |= key_board_tale[ scan_key.end_key_buf[i] ];//特殊按键处理ALT-R
			s = 1;
		}
//		if( (scan_key.end_key_buf[i] == 0x23) ){					//特殊按键处理  fn，如果此时按下多个数字键处理最后一个&& (scan_key.end_key_count < 0x3e)
//			if((scan_key.end_key_buf[scan_key.end_key_count-1] % 6 == 1) && (scan_key.end_key_buf[scan_key.end_key_count-1] < 0x3e))
//			{
//				key_buf[2]  = key_board_tale[ scan_key.end_key_buf[scan_key.end_key_count-1] - 1];//
//				return;
//			}
//			return ;//按键不对，本次不上传数据
//		}
		if( (scan_key.end_key_buf[i] == 0x2D) ){
			key_buf[0] |= key_board_tale[ scan_key.end_key_buf[i] ];//特殊按键处理WIN-R
			s = 1;
		}
		if( (scan_key.end_key_buf[i] == 0x3D) ){
			key_buf[0] |= key_board_tale[ scan_key.end_key_buf[i] ];//特殊按键处理CTRL-R
			s = 1;
		}
		if( (scan_key.end_key_buf[i] == 0x5C) ){
			key_buf[0] |= key_board_tale[ scan_key.end_key_buf[i] ];	//特殊按键处理	SHIFT-R
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
void	LED_INT( void ) interrupt INT_NO_PWM_I2C using 1	// speed
{
    UINT8 data i;
    i = (++LED_COMMON)&0x0f;
//    if(i == 03) return;
//	if ( ( I2CX_INT & bLED_INT_ACT ) == 0 ) return;	// if multi-interrupt enabled
	if ( i == 0 ) {	// switch COMMON, clear interrupt flag       
		LED_COMMON = 0x10;	// restart
		LED_DMA = BufferAddr;	// reset buffer start address
         if( scan_count == 0) {//第一次
             scan_key.first_key_count = count;
             memcpy(scan_key.first_key_buf,buf,count);	
             scan_count = 1;
         }else{     //第二次
             scan_key.sec_key_count = count;
             memcpy(scan_key.sec_key_buf,buf,count);		
             scan_count = 0;
             if(count != 0){
             i = memcmp( scan_key.first_key_buf,scan_key.sec_key_buf,count );//比对按键
             if( i == 0 )		//说明两次按键检测一致
             {
                
                 Key_Porcess(count);
             }                
             }else{//没有按键，直接把数据清空
                 memset( key_buf,0x00,8 );       //USB没有按键了
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
	if ( IsCode ) LED_LOAD_CODE( );	// load data from code ROM, and prepare COMMON pin low for key scan, ASM for speed
	else LED_LOAD_XRAM( );	// load data from XRAM, and prepare COMMON pin low for key scan, ASM for speed
    
    
// scan key
	P4_LED_KEY = 0xFF;	// enable key mode
	P4_MOD_OC = 0xFF;	// disable push-pull output
//	P4_DIR_PU = 0xFF;	// always
//	P4 = 0xFF;	// always
	_nop_( );	// delay at least 500nS for key input stable
	_nop_( );
	ACC = LED_CTRL;	// delay, and use DPTR to force PUSH DPTR (because LED_LOAD_* use DPTR)
	_nop_( ); _nop_( ); _nop_( ); _nop_( ); _nop_( );	// delay for Fsys=48MHz
	_nop_( ); _nop_( ); _nop_( ); _nop_( ); _nop_( );
	_nop_( ); _nop_( ); _nop_( ); _nop_( ); _nop_( );
	_nop_( ); _nop_( ); _nop_( ); _nop_( ); _nop_( );
	NewKey = P4;
   
	P4_MOD_OC = 0;	// push-pull output for PWM
	P4_LED_KEY = 0;	// disable key mode 
	LED_PWM_OE = 0xFF;	// enable PWM output
	P0 = P3 = 0xFF;  // COMMON pin invert output
    
//	P7 |= 0x03;	// if P7 used for COMMON

 
   i=LED_COMMON&0x0F;
   // analyse & upload NewKey @here
   if(count<21 && NewKey!=0xFF){//count<21 && 
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
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*******************************************************************************
* Function Name  : mTimer1ModSetup(UINT8 mode)
* Description    : CH559定时计数器1模式设置
* Input          : UINT8 mode,Timer1模式选择
                   0：模式0，13位定时器，TL1的高3位无效
                   1：模式1，16位定时器
                   2：模式2，8位自动重装定时器
                   3：模式3，停止Timer1
* Output         : None
* Return         : None
*******************************************************************************/
void mTimer1ModSetup(UINT8 mode)
{
    TMOD &= 0x0f;
    TMOD |= mode << 4; 
}

/*******************************************************************************
* Function Name  : mTimer1SetData(UINT16 dat)
* Description    : CH559Timer1 TH1和TL1赋值
* Input          : UINT16 dat;定时器赋值
* Output         : None
* Return         : None
*******************************************************************************/
void mTimer1SetData(UINT16 dat)
{
  UINT16 tmp;
  tmp = 65536 - dat;
  TL1 = tmp & 0xff;
  TH1 = (tmp>>8) & 0xff;
}


void mTimer1Interrupt( void ) interrupt INT_NO_TMR1                //timer1中断服务程序,使用寄存器组1
{    
    mTimer1SetData(0x9C40);
    timeCount++;
    switch(RGBMode){
        case Mode_0:
            BufferAddr = (UINT16)( &RGBdataBuffer[0] );            
            if(incre >= 127)  RGB_stauts = 1;
            if(incre <= -127) RGB_stauts = 0;
            LED_GRE_ADJ=RGB_stauts?(incre--):(incre++);                  
        break;
        case Mode_1:
            BufferAddr = (UINT16)( &RGBdataBuffer[0] );
        break;
        case Mode_2:
            BufferAddr = (UINT16)( &RGBdataBuffer1[0] );
        break;
        case Mode_3:
            if(timeCount>=127)RGB_stauts = 1;
            if(timeCount<127 )RGB_stauts = 0;
            BufferAddr =RGB_stauts?(UINT16)( &RGBdataBuffer1[0] ):(UINT16)( &RGBdataBuffer[0] );
        break;
        case Mode_4:
            BufferAddr =(UINT16)( &RGBdataBuffer1[0] );           
        break;
        default:
            RGBMode = 0;
            break;
    }
    
     
}
void init_Timer(void){
    /////////////////开启定时器，用作随机数输入以及灯效计时器 
  mTimer1Clk12DivFsys( );                                                    //时钟选择Fsys定时器方式
  mTimer1ModSetup(1);	                                                     //方式1，16位定时器                                                      
  mTimer1SetData(0x9C40);                                                    //定时器赋初值 10ms
  mTimer1RunCTL(1);                                                          //启动定时器
  ET1 = 1;                                                                   //使能定时计数器1中断

}