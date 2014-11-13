
#ifndef MESSAGELENGTH
#define MESSAGELENGTH	10// expect 10 bytes to receive
#endif

#ifndef RFM02_h
#define RFM02_h

#include <SPI.h>
#include "rfm02_defines.h"

// defaults
//#define DEVADDR	0x00
//#define CHANNEL	0x00
//#define GDO0	13	// P2.6 on MSP430F2274 on RF2500T	

class RFM02 {
public:
	RFM02();
	RFM02(uint8_t pinChipSelect, uint8_t pinFSK, uint8_t pinNIRQ);
	void begin();
	void sendMessage(uint8_t *txData, uint8_t size);
	
private:
	void writeRegister(uint8_t HighByte, uint8_t LowByte);
	void configureDeviceSettings();
	void RFM02_TX_DataByte_FSK(uint8_t DataByte);
	
	
};

#endif
