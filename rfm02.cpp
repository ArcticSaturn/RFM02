

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
	writeRegister(0xCC,0x00);	// read status
	writeRegister(0x90,0x82);	// 868MHz Band +/- 90kHz Bandbreite
	writeRegister(0xA6,0x86);	// 868.35 MHz
	//writeRegister(0xD0,0x40);	// RATE/2
	writeRegister(0xC8,0x47);	// 4.8kbps
	writeRegister(0xC2,0x20);	// Bit Sync active
	writeRegister(0xB3,0x00);	// 0dBm output power
	writeRegister(0xC0,0x01);	// disable TX
	
}

// Data via FSK
/******************************************************************************/
/*         Sending data via the FSK-Pin as Input-Pin                          */
/*                                                                            */                
/*         After the PowerAmplifier has turned on ( ea=1 ) from rfm02-module  */
/*         comes a clock corresponding to the data-rate set before on nIRQ.   */
/*         The data to be transmitted is bitwise set on the FSK-Pin of the    */
/*         module, after the falling edge of nIRQ. With the following edge    */
/*         of nIRQ this bit is read in and sent out.                          */
/*         nSEL must be high, SCK low, both all the time                      */
/*                                                                            */                
/*                                                                            */                
/* TESTED: 28.09.2014 with Deviation +/- 90kHz and 435.000 MHz                */                
/*                  up to 115.000BPS                                          */                
/*                                                                            */                
/* Support & Copyright: tigarus.programming@web.de                            */                
/******************************************************************************/
void RFM02::RFM02_TX_DataByte_FSK(uint8_t DataByte){
uint8_t i=8;
// PowerAmplifier is here already enabled, impulses on nIRQ corresponding to the 
// set data-rate, nSEL is high, SCK is low

      while(i){            // do 8 times..., (any number of bit's will do, also 9 or 121)
        i=i-1;
		digitalWrite(_pinFSK, LOW); //OUT_PORT_REG &= ~FSK; // first set Bitx as '0'
        if( DataByte & BIT7 )   // if not '0' write over with '1' 
			//OUT_PORT_REG |= FSK;  // ...write '1' if most significant bit is '1'
			digitalWrite(_pinFSK, HIGH); // ...write '1' if most significant bit is '1'
        //while(!(IN_PORT_REG & nIRQ));  // wait for the 0-1-edge of nIRQ, reading in the data
        //while(IN_PORT_REG & nIRQ);    // wait for 1-0-edge to send the last bit
		while(!(digitalRead(_pinNIRQ))); // wait for the 0-1-edge of nIRQ, reading in the data
		while((digitalRead(_pinNIRQ)));  // wait for the 0-1-edge of nIRQ, reading in the data
		
        DataByte <<= 1;         // shift DataByte one bit left to write the next bit
      }
}

/*
void SendDataSPI(uint8_t data){
	digitalWrite(_pinChipSelect,LOW);
	SPI.transfer(0xC6);
	
	 while(i){  // any no of bit's will do, also 9 or 121
        i=i-1;
          
        SDI_low();                  // already set SDI-Port '0' again for next loop or
        if( data & BIT7 )          // now nIRQ is just been low, if MSB is '1'
            SDI_high();               // set SDI-Port '1' 

        while(!(IN_PORT_REG & nIRQ));  // wait for the next high-pulse, data is read by 
        while(IN_PORT_REG & nIRQ);     // now, wait for the falling edge

        data <<= 1;          // shift left ( next bit as most significant bit ...)

      } // end while(...)
   digitalWrite(_pinChipSelect,HIGH);
*/
