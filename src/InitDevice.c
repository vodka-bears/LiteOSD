#include <SI_EFM8BB2_Register_Enums.h>
#include "InitDevice.h"
        

void CLOCK_Init(void) 
{
	SFRPAGE = 0x00;
	PFE0CN = 0x30;
	CLKSEL = CLKSEL_CLKSL__HFOSC0 | CLKSEL_CLKDIV__SYSCLK_DIV_1;
	CLKSEL = CLKSEL_CLKSL__HFOSC0 | CLKSEL_CLKDIV__SYSCLK_DIV_1;
	while(CLKSEL & CLKSEL_DIVRDY__BMASK == CLKSEL_DIVRDY__NOT_READY);
	

	CLKSEL = CLKSEL_CLKSL__HFOSC1 | 0x07;
	CLKSEL = CLKSEL_CLKSL__HFOSC1| 0x07;
	while(CLKSEL & CLKSEL_DIVRDY__BMASK == CLKSEL_DIVRDY__NOT_READY);
}

/*外部中断初始化*/
void EX0_Init(void)
{
	XBR2 = 0x40;
	IT01CF = 0x0A;      
	IE |= 0x05;         
}

/*定时器0初始化*/
void Timer0_Init()
{
	CKCON0 |= 0x05;      //24.5MHz  1/24.5 us   
	TMOD |= 0x01;     
	TL0 = 0x00;
	TH0 = 0x00;
	TCON |= 0x10;  
}


/*SPI0 初始化*/
void SPI0_Init()
{
	P0MDOUT = 0x40;     //P0.6 SPI MOSI
	P0SKIP = 0x3F;
	P1MDOUT = 0x13;

	SFRPAGE = 0x00;
	XBR2 = 0x40;
	XBR0 = 0x02;        //SPI
	
	//SPI0CKR = (0x17 << SPI0CKR_SPI0CKR__SHIFT);
	SPI0CKR = 1;
	
	SPI0CFG |= SPI0CFG_MSTEN__MASTER_ENABLED;
	SPI0CN0 |= SPI0CN0_SPIEN__ENABLED | SPI0CN0_NSSMD__4_WIRE_MASTER_NSS_HIGH;
}
