//4 bands NFM transceiver whih Bluetooth control, MCU STC8F2K64S4 part, this is delay, bk4802p IIC & OLED Display function hander file.
//Authoir:BG7QKU (Amateur radio call sign) 
//Company:BNUZ
//E-mail:1027630917@qq.com
//Date:May 2, 2020
//Website: https://github.com/BG7QKU
#ifndef __IICANDDELAY_H_
#define __IICANDDELAY_H_

#include "STC8F.H"
#include "intrins.h"
#include "codetab.h"
// ------------------------------------------------------------
// OLED Using software IIC bus.
//note:All IIC BUS(CLK,SDA) must connect 3.3k-4.7k rersistor to 3.3V vcc.
// SCL->P1^6
// SDA->P1^7
// ------------------------------------------------------------
sbit SCL1=P1^6; //串行时钟
sbit SDA1=P1^7; //串行数据

//BK4802N using this ANOTHER software IIC:
sbit    SDA         =   P3^2;
sbit    SCL         =   P3^3;

//select WT for MCLK frequency ,here is select "IAP_CONTR = WT_6M;"
#define WT_30M          0x80
#define WT_24M          0x81
#define WT_20M          0x82
#define WT_12M          0x83
#define WT_6M           0x84//here is for MCLK 6MHz
#define WT_3M           0x85
#define WT_2M           0x86
#define WT_1M           0x87


bit busy;
#define high 1
#define low 0
#define	Brightness	0xCF 
#define X_WIDTH 	128
#define Y_WIDTH 	64

void IapIdle()
{
    IAP_CONTR = 0;                              //??IAP??
    IAP_CMD = 0;                                //???????
    IAP_TRIG = 0;                               //???????
    IAP_ADDRH = 0x80;                           //???????IAP??
    IAP_ADDRL = 0;
}

char IapRead(int addr)
{
    char dat;

    IAP_CONTR = WT_6M;                         //??IAP
    IAP_CMD = 1;                                //??IAP???
    IAP_ADDRL = addr;                           //??IAP???
    IAP_ADDRH = addr >> 8;                      //??IAP???
    IAP_TRIG = 0x5a;                            //?????(0x5a)
    IAP_TRIG = 0xa5;                            //?????(0xa5)
    _nop_();
    dat = IAP_DATA;                             //?IAP??
    IapIdle();                                  //??IAP??

    return dat;
}

void IapProgram(int addr, char dat)
{
    IAP_CONTR = WT_6M;                         //??IAP
    IAP_CMD = 2;                                //??IAP???
    IAP_ADDRL = addr;                           //??IAP???
    IAP_ADDRH = addr >> 8;                      //??IAP???
    IAP_DATA = dat;                             //?IAP??
    IAP_TRIG = 0x5a;                            //?????(0x5a)
    IAP_TRIG = 0xa5;                            //?????(0xa5)
    _nop_();
    IapIdle();                                  //??IAP??
}

void IapErase(int addr)
{
    IAP_CONTR = WT_6M;                         //??IAP
    IAP_CMD = 3;                                //??IAP????
    IAP_ADDRL = addr;                           //??IAP???
    IAP_ADDRH = addr >> 8;                      //??IAP???
    IAP_TRIG = 0x5a;                            //?????(0x5a)
    IAP_TRIG = 0xa5;                            //?????(0xa5)
    _nop_();                                    //
    IapIdle();                                  //??IAP??
}
char HIGHBYTE(int bi)//Get higer 8 bit
	 {
		 char highER ;
		 highER=bi>>8;
		 return highER;
	 }
char 	LOWBYTE(int bi)//Get lower 8 bit
	 {
		 char lowER;
		 lowER=bi&0xff;
		 return lowER;
	 }

void delay(unsigned int z)
{
	unsigned int x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}
void Delay50ms()		//@5.5296MHz
{
	unsigned char i, j, k;

	i = 4;
	j = 104;
	k = 12;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
void Delay30ms()		//actually 15ms
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 4;
	j = 175;
	k = 110;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
void Delay10ms()		//@6.000MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	i = 78;
	j = 233;
	do
	{
		while (--j);
	} while (--i);
}

void Delay10us()		//actually 20us
{
	unsigned char i;

	i = 35;
	while (--i);
}
/**********************************************
//IIC Start
**********************************************/
void IIC_Start()
{
   SCL1 = high;		
   SDA1 = high;
   SDA1 = low;
   SCL1 = low;
}

/**********************************************
//IIC Stop
**********************************************/
void IIC_Stop()
{
   SCL1 = low;
   SDA1 = low;
   SCL1 = high;
   SDA1 = high;
}

/**********************************************
// OLED 通过I2C总线写一个字节
**********************************************/
void Write_IIC_Byte(unsigned char IIC_Byte)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		if(IIC_Byte & 0x80)
			SDA1=high;
		else
			SDA1=low;
		SCL1=high;
		SCL1=low;
		IIC_Byte<<=1;
	}
	SDA1=1;
	SCL1=1;
	SCL1=0;
}
//bk4802n using a Hardware IIC!



void Start()
{
  SCL=1;
	
	SDA=1;
	
	SDA=0;
	
	SCL=0;
	
}
//   SCL = high;		
//   SDA = high;
//   SDA = low;
//   SCL = low;

void SendData(char IIC_Byte)
{
	unsigned char i;
    for(i=0;i<8;i++)
	{
		if(IIC_Byte & 0x80)
			SDA=1;
		else
			SDA=0;
		
		
		SCL=1;
		
		SCL=0;
		
		IIC_Byte<<=1;
	}
	SDA=1;
	
	SCL=1;
	
	SCL=0;

}


char RecvData()
{
  unsigned char s,i;
	for(i=0;i<8;i++)
	{
		SCL=1;

		s=s<<1;
		s=s|SDA;

		SCL=0;

	}
	SCL=1;
	SDA=1;
	
	return s;
}



void Stop()
{
  SCL=0;
	
  SDA=0;
	
	SCL=1;
	
  SDA=1;
}
//   SCL = low;
 //  SDA = low;
 //  SCL = high;
//   SDA= high;


void Delay()
{
    int i;

    for (i=0; i<3000; i++)
    {
        _nop_();
        _nop_();
        _nop_();
        _nop_();
    }
}

//bk4802 writing use 
void writing(char ICaddforwrite,char hadd,char hdata,char ldata)//WRITE TO  BK4802N
	 {
    
    Start();                                    //??????
    SendData(ICaddforwrite);                             //??????+???
    
    SendData(hadd);                             //?????????
    
    SendData(hdata);                             //?????????
    
    SendData(ldata);                             //?????1
    
    Stop();                                     //??????

    Delay();
	 }
int reading(char ICaddforwrite,char hadd)//WRITE TO  BK4802N
	 {
    char sh,sl;
		int recv;
    Start();                                    //??????
    SendData(ICaddforwrite);                             //??????+???
    SendData(hadd);                             //?????????
    Start(); 
    SendData(ICaddforwrite+1);                             //????????     
    sh=RecvData();                             //?????1
    sl=RecvData(); 
    Stop();                                     //??????
    Delay();
		 recv=sh;
		 recv=recv<<8|sl;
		 return  recv;
	 }
	 /*********************OLED写数据************************************/ 
void OLED_WrDat(unsigned char IIC_Data)
{
	IIC_Start();
	Write_IIC_Byte(0x78);
	Write_IIC_Byte(0x40);			//write data
	Write_IIC_Byte(IIC_Data);
	IIC_Stop();
}
/*********************OLED写命令************************************/
void OLED_WrCmd(unsigned char IIC_Command)
{
	IIC_Start();
	Write_IIC_Byte(0x78);            //Slave address,SA0=0
	Write_IIC_Byte(0x00);			//write command
	Write_IIC_Byte(IIC_Command);
	IIC_Stop();
}
/*********************OLED 设置坐标************************************/
void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 
	OLED_WrCmd(0xb0+y);
	OLED_WrCmd(((x&0xf0)>>4)|0x10);
	OLED_WrCmd((x&0x0f)|0x01);
} 
/*********************OLED全屏************************************/
void OLED_Fill(unsigned char bmp_dat) 
{
	unsigned char y,x;
	for(y=0;y<8;y++)
	{
		OLED_WrCmd(0xb0+y);
		OLED_WrCmd(0x01);
		OLED_WrCmd(0x10);
		for(x=0;x<X_WIDTH;x++)
		OLED_WrDat(bmp_dat);
	}
}
/*********************OLED复位************************************/
void OLED_CLS(void)
{
	unsigned char y,x;
	for(y=0;y<8;y++)
	{
		OLED_WrCmd(0xb0+y);
		OLED_WrCmd(0x01);
		OLED_WrCmd(0x10);
		for(x=0;x<X_WIDTH;x++)
		OLED_WrDat(0);
	}
}
/*********************OLED初始化************************************/
void OLED_Init(void)
{
	delay(500);//初始化之前的延时很重要！
	OLED_WrCmd(0xae);//--turn off oled panel
	OLED_WrCmd(0x00);//---set low column address
	OLED_WrCmd(0x10);//---set high column address
	OLED_WrCmd(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WrCmd(0x81);//--set contrast control register
	OLED_WrCmd(Brightness); // Set SEG Output Current Brightness
	OLED_WrCmd(0xa1);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
	OLED_WrCmd(0xc8);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
	OLED_WrCmd(0xa6);//--set normal display
	OLED_WrCmd(0xa8);//--set multiplex ratio(1 to 64)
	OLED_WrCmd(0x3f);//--1/64 duty
	OLED_WrCmd(0xd3);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_WrCmd(0x00);//-not offset
	OLED_WrCmd(0xd5);//--set display clock divide ratio/oscillator frequency
	OLED_WrCmd(0x80);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_WrCmd(0xd9);//--set pre-charge period
	OLED_WrCmd(0xf1);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_WrCmd(0xda);//--set com pins hardware configuration
	OLED_WrCmd(0x12);
	OLED_WrCmd(0xdb);//--set vcomh
	OLED_WrCmd(0x40);//Set VCOM Deselect Level
	OLED_WrCmd(0x20);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_WrCmd(0x02);//
	OLED_WrCmd(0x8d);//--set Charge Pump enable/disable
	OLED_WrCmd(0x14);//--set(0x10) disable
	OLED_WrCmd(0xa4);// Disable Entire Display On (0xa4/0xa5)
	OLED_WrCmd(0xa6);// Disable Inverse Display On (0xa6/a7) 
	OLED_WrCmd(0xaf);//--turn on oled panel
	OLED_Fill(0x00); //初始清屏
	OLED_Set_Pos(0,0);
} 
/***************功能描述：显示6*8一组标准ASCII字符串	显示的坐标（x,y），y为页范围0～7****************/
void OLED_P6x8Str(unsigned char x, y,unsigned char ch[])
{
	unsigned char c=0,i=0,j=0;
	while (ch[j]!='\0')
	{
		c =ch[j]-32;
		if(x>126){x=0;y++;}
		OLED_Set_Pos(x,y);
		for(i=0;i<6;i++)
		OLED_WrDat(F6x8[c][i]);
		x+=6;
		j++;
	}
}
/*******************功能描述：显示8*16一组标准ASCII字符串	 显示的坐标（x,y），y为页范围0～7****************/
void OLED_P8x16Str(unsigned char x, y,unsigned char ch[])
{
	unsigned char c=0,i=0,j=0;
	while (ch[j]!='\0')
	{
		c =ch[j]-32;
		if(x>120){x=0;y++;}
		OLED_Set_Pos(x,y);
		for(i=0;i<8;i++)
		OLED_WrDat(F8X16[c*16+i]);
		OLED_Set_Pos(x,y+1);
		for(i=0;i<8;i++)
		OLED_WrDat(F8X16[c*16+i+8]);
		x+=8;
		j++;
	}
}
/*****************功能描述：显示16*16点阵  显示的坐标（x,y），y为页范围0～7****************************/
void OLED_P16x16Ch(unsigned char x, y, N)
{
	unsigned char wm=0;
	unsigned int adder=32*N;
	OLED_Set_Pos(x , y);
	for(wm = 0;wm < 16;wm++)
	{
		OLED_WrDat(F16x16[adder]);
		adder += 1;
	}
	OLED_Set_Pos(x,y + 1);
	for(wm = 0;wm < 16;wm++)
	{
		OLED_WrDat(F16x16[adder]);
		adder += 1;
	} 	  	
}
/***********功能描述：显示显示BMP图片128×64起始点坐标(x,y),x的范围0～127，y为页的范围0～7*****************/
void Draw_BMP(unsigned char x0, y0,x1, y1,unsigned char BMP[])
{
	unsigned int j=0;
	unsigned char x,y;

  if(y1%8==0) y=y1/8;      
  else y=y1/8+1;
	for(y=y0;y<y1;y++)
	{
		OLED_Set_Pos(x0,y);
    for(x=x0;x<x1;x++)
	    {      
	    	OLED_WrDat(BMP[j++]);
	    }
	}
}

	 #endif
