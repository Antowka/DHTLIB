#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#define MAXTIMINGS 85 
#define DHTPIN	7

const int MAX_REPIAT=300;
int dht11_dat[5] = { 0, 0, 0, 0, 0 };
int counter = 0;
 
char *read_dht11() {

	if ( wiringPiSetup() == -1 ) exit( 1 );

	uint8_t laststate	= HIGH;
	uint8_t counter		= 0;
	uint8_t j		= 0, i;
	float	f; 
 
	dht11_dat[0] = dht11_dat[1] = dht11_dat[2] = dht11_dat[3] = dht11_dat[4] = counter = 0;
 
	pinMode(DHTPIN, OUTPUT);
	digitalWrite(DHTPIN, LOW);
	delay(18);
	digitalWrite(DHTPIN, HIGH);
	delayMicroseconds(30);
	pinMode(DHTPIN, INPUT);
 
	for ( i = 0; i < MAXTIMINGS; i++ ) {

		counter = 0;
		while ( digitalRead(DHTPIN) == laststate ) {
			counter++;
			delayMicroseconds(1);
			if ( counter == 255 ) {
				break;
			}
		}

		laststate = digitalRead(DHTPIN);
 
		if (counter == 255) break;
 
		if ((i >= 4) && (i % 2 == 0))	{
		  dht11_dat[j / 8] <<= 1;
		  
                  if ( counter > 16 )
		    dht11_dat[j / 8] |= 1;
		    j++;
	          }
	}

	if ( (j >= 40) && (dht11_dat[4] == ( (dht11_dat[0] + dht11_dat[1] + dht11_dat[2] + dht11_dat[3]) & 0xFF) ) )	{

	   f = dht11_dat[2] * 9. / 5. + 32;
	   char *data = malloc(36);
           char resultStr[35];		
	   sprintf(resultStr, "Hum: %d.%d %% Temp: %d.%d C (%.1f F)\n", dht11_dat[0], dht11_dat[1], dht11_dat[2], dht11_dat[3], f);
           strcpy(data, resultStr);
	   return data;

	} else {
           
           ++counter;
	   
           if (counter>MAX_REPIAT) {
           	return "wrong data \0";
           }
	   
           return read_dht11();
        }
}
