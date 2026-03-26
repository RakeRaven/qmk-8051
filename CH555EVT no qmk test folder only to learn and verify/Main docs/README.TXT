
南京沁恒微电子股份有限公司 2021.08
最新资料请到我们的网站上查询
http://wch.cn


文件目录EVT
  |
  |-- README.TXT：目录文件说明
  | 
  |-- EXAM: C例程
  |     |--CH555.uvproj:CH555 keil4工程文件
  |     |--Public：
  |     |      |--CH555.H：CH555 C语言头文件，SFR定义
  |     |      |--CH555.INC：CH555汇编头文件，SFR定义
  |     |      |--Debug.C&H：UART0&1初始化、常用延时函数、软复位函数、UART0&1数据收发子函数,看门狗初始化
  |     |--ADC：
  |     |      |-- MAIN.C：ADC使用示例
  |     |      |-- ADC.C&H：ADC初始化，采样时钟设定，通道变化和电压比较功能函数定义
  |     |      |-- ADC.hex
  |     |--DATAFLASH：
  |     |      |-- MAIN.C：DataFlash使用示例
  |     |      |-- Flash.C&H：Flash读写函数定义
  |     |      |-- DataFlash.hex
  |     |--GPIO：
  |     |      |-- MAIN.C：GPIO使用示例
  |     |      |-- GPIO.C&H：GPIO设置函数定义
  |     |      |-- GPIO.hex
  |     |--I2C：
  |     |      |-- IICHost：  
  |     |      |      |-- main.C：IIC模拟主机使用示例
  |     |      |      |-- IICHost.C&H：  IIC信号模拟示例
  |     |      |      |-- IICHost.hex
  |     |      |-- IICSlave：  
  |     |      |      |-- IICSlave：  IIC从机FLASH模拟EEPROM使用示例
  |     |      |      |-- Flash.C&H：Flash读写函数定义
  |     |      |      |-- IICSlave.hex
  |     |--RGB：
  |     |      |-- MAIN.C：RGB使用示例
  |     |      |-- RGB.C&H：RGB初始化函数定义
  |     |      |-- RGBLOAD.ASM：RGB中断服务函数 
  |     |      |-- RGB.hex   
  |     |--SPI：
  |     |      |-- SPI_MASTER：  
  |     |      |      |-- MAINMASTER.C：SPI主模式使用示例
  |     |      |      |-- MAINMASTER.hex
  |     |      |-- SPI_SLAVE：  
  |     |      |      |-- MAINSLAVE.C：SPI从模式使用示例
  |     |      |      |-- MAINSLAVE.hex
  |     |      |-- SPI.C&H：SPI主从设置和收发函数定义  
  |     |--TIMER：
  |     |      |-- MAIN.C：Timer0&1&2定时，计数设置和捕捉功能使用示例
  |     |      |-- TIMER.C&H：Timer0&1&2定时，计数设置和捕捉函数定义
  |     |      |-- TIMER.hex  
  |     |--UART：
  |     |      |-- MAIN.C：串口查询、中断演示  
  |     |      |-- UART.C&H：串口收发函数与初始化
  |     |      |-- UART.hex 
  |     |--USB：
  |     |      |-- Device：
  |     |      |      |-- CompatibilityHID.C：模拟HID兼容设备，支持中断上下传
  |     |      |      |-- CompatibilityHID.hex    
  |     |      |      |-- CompositeKM.C：模拟键鼠例程，支持部分类命令
  |     |      |      |-- CompositeKM.hex 
  |     |      |      |-- VendorDefinedDev.C：模拟厂商自定义设备，需要安装CH372驱动，可以通过372test.exe调试(批量数据收发)
  |     |      |      |-- VendorDefinedDev.hex  
  |- PUB：评估板说明
  |     |-- CH555EVT.PDF：评估板说明
  |     |-- CH555SCH.PDF：评估板原理图