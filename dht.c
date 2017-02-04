#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define MAXTIMINGS 85 
#define DHTPIN	7

const int MAX_REPIAT=300;
int dht_dat[5] = { 0, 0, 0, 0, 0 };
int try_counter = 0;
 
char *read_dht11() {

	if ( wiringPiSetup() == -1 ) exit( 1 );

	uint8_t laststate	= HIGH;
	uint8_t counter		= 0;
	uint8_t j		= 0, i;
	float	f; 
 
	dht_dat[0] = dht_dat[1] = dht_dat[2] = dht_dat[3] = dht_dat[4] = try_counter = 0;
 
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
		  dht_dat[j / 8] <<= 1;
		  
            if ( counter > 16 )
		    dht_dat[j / 8] |= 1;
		    j++;
	    }
	}

	if ( (j >= 40) && (dht_dat[4] == ( (dht_dat[0] + dht_dat[1] + dht_dat[2] + dht_dat[3]) & 0xFF) ) )	{

	   f = dht_dat[2] * 9. / 5. + 32;
	   char *data = malloc(36);
	   sprintf(data, "Hum: %d.%d %% Temp: %d.%d C (%.1f F)\n", dht_dat[0], dht_dat[1], dht_dat[2], dht_dat[3], f);
	   return data;

	} else {
           
           ++try_counter;
	   
           if (try_counter>MAX_REPIAT) {
           	return "wrong data \0";
           }
	   
           return read_dht11();
    }
}

char *read_dht22() {

	if ( wiringPiSetup() == -1 ) exit( 1 );

	uint8_t laststate	= HIGH;
	uint8_t counter		= 0;
	uint8_t j		= 0, i;
	float	f; 
 
	dht_dat[0] = dht_dat[1] = dht_dat[2] = dht_dat[3] = dht_dat[4] = try_counter = 0;
 
	pinMode(DHTPIN, OUTPUT);
	
	digitalWrite(DHTPIN, HIGH);
	delay(10);
	
	digitalWrite(DHTPIN, LOW);
	delay(18);
	
	digitalWrite(DHTPIN, HIGH);
	delayMicroseconds(40);
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
		    dht_dat[j / 8] <<= 1;
		  
            if ( counter > 16 )
		    dht_dat[j / 8] |= 1;
		    j++;
	    }
	}

	if ( (j >= 40) && (dht_dat[4] == ( (dht_dat[0] + dht_dat[1] + dht_dat[2] + dht_dat[3]) & 0xFF) ) )	{

	   	float t, h;
        h = (float)dht_dat[0] * 256 + (float)dht_dat[1];
        h /= 10;
        t = (float)(dht_dat[2] & 0x7F)* 256 + (float)dht_dat[3];
        t /= 10.0;
        if ((dht_dat[2] & 0x80) != 0)  t *= -1;

	   f = t * 9. / 5. + 32;
	   
	   char *data = malloc(36);
	   
	   sprintf(data, "Hum: %.2f %% Temp: %.2f C (%.2f F) \n", h, t, f);
	   
	   return data;

	} else {
           
           ++try_counter;
	   
           if (try_counter>MAX_REPIAT) {
           	return "wrong data \0";
           }
	   
           return read_dht22();
    }
}

