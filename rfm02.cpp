

#include "rfm02.h"

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


static const uint8_t P_CS   = 11;
static const uint8_t P_FSK  = 9;
static const uint8_t P_NIRQ = 10;

/*
static const uint8_t P_CS   = 4;
static const uint8_t P_FSK  = 3;
static const uint8_t P_NIRQ = 18;
*/
// empty constructor
RFM02::RFM02() {
	RFM02(P_CS, P_FSK, P_NIRQ);
}

// constructor with variables
RFM02::RFM02(uint8_t pinChipSelect, uint8_t pinFSK, uint8_t pinNIRQ)
{
	_pinChipSelect = pinChipSelect;
	_pinFSK = pinFSK;
	_pinNIRQ = pinNIRQ;
}

void RFM02::begin() {
	digitalWrite(_pinChipSelect, HIGH);  	// set chip select high
	pinMode(_pinChipSelect, OUTPUT);     	// set chip select as output
    
	digitalWrite(_pinFSK, LOW);		// set FSK to low
	pinMode(_pinFSK, OUTPUT);		// set FSK pin as output
    
	pinMode(P_NIRQ, INPUT);			// set nIRQ pin as input
	
	configureDeviceSettings();		// configure RFM01	
	
	//pinMode(RED_LED, OUTPUT);		// set red led as output
	//digitalWrite(RED_LED, HIGH);		// blink red led 50 ms 
						// to indicate setup ready
	//delay(50);
	//digitalWrite(RED_LED, LOW);
}

void RFM02::writeRegister(uint8_t HighByte, uint8_t LowByte) {
	digitalWrite(_pinChipSelect,LOW);
	SPI.transfer(HighByte);
	SPI.transfer(LowByte);
	digitalWrite(_pinChipSelect,HIGH);
}



void RFM02::configureDeviceSettings() {
	writeRegister(0xCC,0x00);	// read status
	writeRegister(0x93,0x82);	// 868MHz Band +/- 90kHz Bandbreite
	writeRegister(0xA6,0x86);	// 868.35 MHz
	writeRegister(0xD0,0x40);	// RATE/2
	writeRegister(0xC8,0x23);	// 38.4/2 = 19.2kbps
	writeRegister(0xC2,0x20);	// Bit Sync active
	writeRegister(0xC0,0x01);	// disable TX
	writeRegister(0xD2,0x40);	// PLL 25%
	writeRegister(0xB0,0x00);	// 0 db
	writeRegister(0xE0,0x00);	// 'disable wakeup timer
	
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
	
	digitalWrite(_pinChipSelect,HIGH);	
	while(i){            // do 8 times 
        	i=i-1;
		 // wait for the 0-1-edge of nIRQ, reading in the data
		while(!(digitalRead(_pinNIRQ)));
		// wait for 1-0-edge to send the last bit	
		while((digitalRead(_pinNIRQ)));   
		// if not '0' write over with '1' 
		if( DataByte & BIT7 )  
			digitalWrite(_pinFSK, HIGH); // write '1' if most significant bit is '1'
        	else 
			digitalWrite(_pinFSK, LOW); //OUT_PORT_REG &= ~FSK; // first set Bitx as '0'
		// shift DataByte one bit left to write the next bit
		DataByte <<= 1;
      }
}


void RFM02::sendMessage(uint8_t *txData, uint8_t size)
{

   //digitalWrite(_pinChipSelect, LOW); // CS LOW
   writeRegister(0xC0,0x39); // enable TX
   //digitalWrite(_pinChipSelect, HIGH); // CS HIGH
   delayMicroseconds(2000);
   RFM02_TX_DataByte_FSK(0xAA); // preamble
   RFM02_TX_DataByte_FSK(0xAA); // preamble
   RFM02_TX_DataByte_FSK(0xAA); // preamble
   
   RFM02_TX_DataByte_FSK(0x2D); // sync word high
   RFM02_TX_DataByte_FSK(0xD4); // sync word low
   
   for(int myLoop=0;myLoop<MESSAGELENGTH;myLoop++)
 {
   RFM02_TX_DataByte_FSK(txData[myLoop]); // sync word lowtxData[myLoop] = myLoop;
 }
   
   /*
   RFM02_TX_DataByte_FSK('H'); // data
   RFM02_TX_DataByte_FSK('E'); // data
   RFM02_TX_DataByte_FSK('L'); // data
   RFM02_TX_DataByte_FSK('L'); // data
   RFM02_TX_DataByte_FSK('O'); // data
   
   RFM02_TX_DataByte_FSK(1); // data
   RFM02_TX_DataByte_FSK(2); // data
   RFM02_TX_DataByte_FSK(3); // data
   RFM02_TX_DataByte_FSK(4); // data
   
   RFM02_TX_DataByte_FSK(0xA5); // ende zeichen
   */
   //delayMicroseconds(2410); // delay until carrier turn off 
   //digitalWrite(_pinFSK, HIGH); 
   
   // while((digitalRead(_pinNIRQ)));
    //while(!(digitalRead(_pinNIRQ)));

    //while((digitalRead(_pinNIRQ)));
   // while(!(digitalRead(_pinNIRQ)));
 //__delay_cycles(1500);
   delayMicroseconds(1000);
   
   
   //digitalWrite(_pinChipSelect, LOW); // CS LOW
   writeRegister(0xC0,0x01); // disable TX
   //digitalWrite(_pinChipSelect, HIGH); // CS HIGH

}
