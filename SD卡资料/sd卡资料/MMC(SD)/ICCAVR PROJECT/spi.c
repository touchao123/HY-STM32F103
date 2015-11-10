/* INCLUDE参数  */
#include <iom162v.h>

/************************************
*          SPI初始化
************************************/
void spi_init(void)
{
    DDRB|=(1<<PB4);                               /* SS端设置为输出 */
    DDRB|=(1<<PB5);                               /* MOSI端口设置为输出 */
    DDRB&=~(1<<PB6);                              /* MISO端口设置为输入 */
    DDRB|=(1<<PB7);                               /* SCK端口设置为输出 */
    SPCR|=(1<<SPE)|(1<<MSTR)|(1<<SPR1)|(1<<SPR0); /* SPI ENABLE,MASTER MODE,Fsoc/16 */
	PORTB|=(1<<PB4);                              /* SS=1 */
}

/************************************
*        SPI转入高速模式
************************************/
void SPIHiSPD(void)
{
    SPCR|=(0<<SPR1)|(0<<SPR0);                    /* SPI ENABLE,MASTER MODE,Fsoc/16 */
	SPSR|=(1<<SPI2X); 
}

/************************************
*           SPI发送数据
************************************/
unsigned char spi_send(unsigned char data)
{
    unsigned char temp;
	SPDR = data;
    while(!(SPSR & (1<<SPIF)))
	{
	    asm("nop");
	}
	temp = SPDR;
	return temp;
}