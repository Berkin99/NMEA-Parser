/** example.c
 *
 *  Created on: Dec 16, 2023
 *      Author: BerkN
 *
 *  NMEA 0183 Protocol Parser for Ublox GNSS Receivers.
 *	Easy to use for all NMEA applications / Extendable NMEA message ID library.
 *  
 *  All valid messages are from UBLOX receiver description manual. 
 *  	 
 */

#include <stdio.h>
#include "nmea.h"

char* test_msg = "$GNGGA,092725.00,4717.11399,N,00833.91590,E,1,08,1.01,499.6,M,48.0,M,,*5B";

NMEA_Message_t temp;
NMEA_Payload_GGA_t frame_gga;

void print_gga(const NMEA_Payload_GGA_t* frame);

int main(void) {
	NMEA_Pack(&temp, test_msg);
	NMEA_GGA_Parse(&frame_gga, &temp);

	printf("TESTING MSG : %s \n\n", test_msg);
	print_gga(&frame_gga);
}

void print_gga(const NMEA_Payload_GGA_t* frame) {
	printf("- PAYLOAD GGA -\n");

	printf("HOUR : %d\n", frame->time.hour);
	printf("MIN : %d\n", frame->time.min);
	printf("SEC : %d\n", frame->time.sec);
	printf("LATITUDE : %d\n", frame->location.latitude);
	printf("L_NORTH : %d\n", frame->location.ns_d);
	printf("LONGITUDE : %d\n", frame->location.longitude);
	printf("L_EAST : %d\n", frame->location.ew_d);
	printf("QUALITY : %d\n", frame->quality);
	printf("SATELLITE N : %d\n", frame->satellite_n);
}