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
	printf("LATITUDE : %f\n", frame->latitude);
	printf("L_NORTH : %d\n", frame->l_north);
	printf("LONGITUDE : %f\n", frame->longitude);
	printf("L_EAST : %d\n", frame->l_east);
	printf("QUALITY : %d\n", frame->quality);
	printf("SATELLITE N : %d\n", frame->satellite_n);

}