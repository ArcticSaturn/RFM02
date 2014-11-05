

#include "RFM02.h"

uint8_t _pinFSK;
uint8_t _pinNIRQ;
uint8_t _pinSOMI;
uint8_t _pinSIMO;
uint8_t _pinChipSelect;
uint8_t _pinSerialClock;

// Booster Pack Pins FR5969
    //  7 - P2.2 for SPI_CLK mode
    // 15 - P1.6 for SPI_SIMO mode
	// 14 - P1.7 for SPI_SOMI mode
	//  5 - P2.5 output pin for SPI_CS
    // 18 - P3.0 nIRQ for sending data
    //  3 - P2.6 as FSK input data
    // Set display's VCC and DISP pins to high


static const uint8_t P_CS   = 4;
static const uint8_t P_FSK  = 3;
static const uint8_t P_NIRQ = 18;

// empty constructor
RFM02::RFM02() {
	RFM02(P_CS, P_FSK, P_NIRQ);
}

// constructor with variables
RFM02::RFM02(uint8_t pinChipSelect, uint8_t pinFSK, uint8_t pinNIRQ){
	_pinChipSelect = pinChipSelect;
	_pinFSK = pinFSK;
	_pinNIRQ = pinNIRQ;
}


/*
RFM02::RFM02(uint8_t deviceAddress) {
	RFM02(deviceAddress, CHANNEL);
}
RFM02::RFM02(uint8_t deviceAddress, uint8_t channel) {
	_deviceAddress = deviceAddress;
	_channel = channel;
	_gdo0 = GDO0;	
}

*/

void RFM02::begin() {
	digitalWrite(_pinChipSelect, HIGH);
	pinMode(_pinChipSelect, OUTPUT);
    
	digitalWrite(_pinFSK, HIGH);
	pinMode(_pinFSK, OUTPUT);
    
	pinMode(P_NIRQ, INPUT);
	
	pinMode(26, OUTPUT);
	digitalWrite(26, HIGH);
	delay(2000);
	digitalWrite(26, LOW);
	
	
	//digitalWrite(SS,HIGH);
	//pinMode(SS,OUTPUT);

	//resetDevice();
	
	configureDeviceSettings();
	//execStrobeCommand(RFM02_CMD_SRX);
}

void RFM02::writeRegister(uint8_t HighByte, uint8_t LowByte) {
	digitalWrite(_pinChipSelect,LOW);
	SPI.transfer(HighByte);
	SPI.transfer(LowByte);
	digitalWrite(_pinChipSelect,HIGH);
}



void RFM02::configureDeviceSettings() {
	//digitalWrite(_pinChipSelect,LOW);
	writeRegister(0xCC,0x00);	// read status
	writeRegister(0x90,0x8A);	// 868MHz Band +/- 90kHz Bandbreite
	writeRegister(0xA6,0x86);	// 868 MHz
	writeRegister(0xD0,0x40);	// RATE/2
	writeRegister(0xC8,0x23);	// 4.8kbps
	writeRegister(0xC2,0x20);	// Bit Sync active
	writeRegister(0xB0,0x00);	// 0dBm output power
	writeRegister(0xC0,0x01);	// disable TX
	//digitalWrite(_pinChipSelect,HIGH);
	
	
	Serial.println("2");


}
