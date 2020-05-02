#include<iostream>
#include<fstream>
#include "WzSerialPort.h"
#include<stdio.h>
using namespace std;
#define IF 0.137
#define two24 16777216
#define CRYSTAL 21.250
	 char txfreq[6];
     char rxfreq[6];
	 char slove[512];
    float fr;
    char sente[6]={0X00,0X00,0X00,0X00,0X00,0X00};
    char freqinfo[8];
    
 char HIGHBYTE(short int bi)//Get higer 8 bit
	 {
		 unsigned char highER ;
		 highER=bi>>8;
		 return highER;
	 }
 char 	LOWBYTE(short int bi)//Get lower 8 bit
	 {
		 unsigned char lowER;
		 lowER=bi&0xff;
		 return lowER;
	 }
 short int HIGHBYTE16( int bi)//Get higer 8 bit
	 {
		 short int highER;
		 highER=bi>>16;
		 return highER;
	 }
 short int 	LOWBYTE16( int bi)//Get lower 8 bit
	 {
		 short int lowER;
		 lowER=bi&0xffff;
		 return lowER;
	 }
	 
void calc(float freq)
{
    unsigned long rx,tx;
	short int rxh,rxl,txh,txl;
	float ndiv;
	CAL:
	if(freq<=512&&freq>=384)
	{
	 txfreq[5]=0x00;
	 rxfreq[5]=0x00;
	 txfreq[4]=0x00;
	 rxfreq[4]=0x00;
	 ndiv=4;
    }
	if(freq<=170&&freq>=128)
	{
	 txfreq[4]=0x20;
	 rxfreq[4]=0x20;
	 txfreq[5]=0x02;
	 rxfreq[5]=0x02;
	 ndiv=12;
    }
	if(freq<=57&&freq>=43)
	{
	 txfreq[4]=0x80;
	 rxfreq[4]=0x80;
	 txfreq[5]=0x08;
	 rxfreq[5]=0x08;
	 ndiv=36;
	}
	if(freq<=46&&freq>=35)
	{
	 txfreq[4]=0xa0;
	 rxfreq[4]=0xa0;
	 txfreq[5]=0x0a;
	 rxfreq[5]=0x0a;
	 ndiv=44;
    }
	if(freq<=32&&freq>=24)
	{
	 txfreq[4]=0xc0;
	 rxfreq[4]=0xc0;
	 txfreq[5]=0x0f;
	 rxfreq[5]=0x0f;
	 ndiv=64;
    }
	else if(freq<24||freq>512)
	{
	 cout<<"error: Frequency is out of range! re-key in"<<endl;	
	 goto CAL;
	}
	rx=((freq-IF*1)*ndiv*two24)/CRYSTAL;
	tx=(freq*ndiv*two24)/CRYSTAL;
	cout<<hex<<tx<<endl;
	cout<<hex<<rx<<endl;
	txh=HIGHBYTE16(tx);
	txl=LOWBYTE16(tx);
	
	rxh=HIGHBYTE16(rx);
	rxl=LOWBYTE16(rx);
	
	txfreq[0]=HIGHBYTE(txh);
	txfreq[1]=LOWBYTE(txh);
	txfreq[2]=HIGHBYTE(txl);
	txfreq[3]=LOWBYTE(txl);
	
	rxfreq[0]=HIGHBYTE(rxh);
	rxfreq[1]=LOWBYTE(rxh);
	rxfreq[2]=HIGHBYTE(rxl);
	rxfreq[3]=LOWBYTE(rxl);

}


int main(int argc, char** argv)
{
    int s=0;
    char wt=0;
    char tmp;
	ofstream ofs;
	ifstream ifs;
	WzSerialPort w;
	cout<<"Designed by BG7QKU. 12,APR 2020"<<endl;
	cout<<"press 0 and ENTER to calc and write to chip. Or press other count to direct write 16channelset.BIN documents to chip"<<endl;
	cout<<"请按数字0键并按ENTER开始设置新的频率，如果之前在D盘跟目录下已经创建了16channelset.BIN文件，也可以直接按其他数字键并且按ENTER后不更改频率直接写入设备(先用设备管理器查看可用串口号）。"<<endl; 
	
	cin>>wt;
	
  if(wt==0X30)
  {
	 ofs.open("D:\\16channelset.BIN",ios::out|ios::binary);
	cout<<"strat. please key in 16 channels frequency(MHz)"<<endl;
	cout<<"开始依次输入每个频道的频率(单位MHz)，一共16个。"<<endl;
	if(ofs)
	{
		for(int i=0;i<16;i++)
		{
		    cout<<dec<<"Key in channel 请输入第 "<<i+1<<"个频道频率，然后按ENTER键:"<<endl;
		  	cin>>fr;
		  	calc(fr);
		  	cout<<"write this channel freq is: 刚刚输入的频率是"<<fr<<endl;

		  for(int k=1;k<=6;k++)
		  {
		  	slove[s]=txfreq[k-1];
		  	s++;
		  }
		slove[s]=0x00;
		s++;
		slove[s]=0x00;
		s++;
		for(int j=1;j<=6;j++)
		  {
		  	slove[s]=rxfreq[j-1];
		  	s++;
		  }
		  slove[s]=0x00;
		s++;
		slove[s]=0x00;
        s++;
        sprintf(freqinfo,"%8.4f",fr);
        for(char e=0;e<8;e++)
        {
        	slove[s]=freqinfo[e];
        	s++;
        }
        for(char m=0;m<8;m++)
        {
        	slove[s]=0x00;
        	s++;
        }
     }
	    
	    
         ofs.write(slove,512);
         
          cout<<dec<<s<<endl;
          
   } 
   ofs.close();
  }
  else
  {
    if(ofs)
    {
  	 ifs.open("D:\\16channelset.BIN",ios::in|ios::binary);
  	 ifs.read(slove,512);
  	 ifs.close();
    }
    else
    cout<<"open file failed!"<<endl;
  }
  
   cout<<"Have write file finish!,please go to D:\\ to see 16channelset.BIN to write to device"<<endl;
   cout<<"Do you want to write to device? key in COM name e.g COM2."<<endl; 
   cout<<"现在已经在D盘根目录下创建了文件16channelset.BIN.是否写入设备？,先以“COM2”类似的格式输入之前设备管理器上看到可用的COM口编号，回车后执行写入"<<endl;
   cin>>sente;
   
   
	if (w.open(sente, 9600, 0, 8, 1))
	{
		
	
			w.send(slove, 512);
		
		
		cout << "send demo finished... 写入设备完成";
	}
	else
	{
		cout << "open serial port failed...串口打开失败";
	}

	if (w.open(sente, 9600, 0, 8, 1))
	{
		char buf[512];
		while (true)
		{
			
			w.receive(buf, 512);
			cout << buf;
		}
	}
    
   system("pause");
   w.close();
   return 0;
}
