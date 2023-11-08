

#ifndef SPI_H_
#define SPI_H_


typedef enum {
	SLAVE,
	MASTER
}SPI_Mode_type;

void SPI_Init (SPI_Mode_type mode);

u8 SPI_SendReceive(u8 data);

void SPI_SendNoBlock(u8 data);

void SPI_SendString (u8* data_send);
u8 SPI_ReceivePeriodic(u8 *pdata);
u8 SPI_ReceiveString(u8 *data_recieve);



#endif /* SPI_H_ */