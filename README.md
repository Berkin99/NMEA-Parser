# NMEA-Parser

### NMEA Parser for GNSS module data

NMEA 0183 Protocol Parser for Ublox GNSS Receivers.
Compatable for other NMEA applications / Extendable NMEA message ID library. 
Embedded system optimization.  

### References: 
 
*  [0] The National Marine Electronics Association (NMEA) 0183. Manual Klaus Betke, May 2000. Revised August 2001.
*  [1] u-blox8-M8_ReceiverDescrProtSpec_(UBX-13003221)
 
### Supported Payload ID

* Supported NMEA message types based on UBLOX DescrProtSpec [1] to parse.

* _GBS_
* _GGA_
* _GLL_
* _GST_
* _GSA_
* _GSV_
* _RMC_
* _VTG_
* _ZDA_

### Usage

To fill empty "NMEA Message t" type structure, the raw message line is fed to the "NMEA Pack" function.
Control the NMEA_Message_t type structure Payload ID value for select related function to use.
There is a parse function for each supported Payload ID. Parse the message with correct function and get 
the data to related Payload struct.

Example :
```c

#include <stdio.h>
#include "nmea.h"

char* test_msg = "$GNGGA,092725.00,4717.11399,N,00833.91590,E,1,08,1.01,499.6,M,48.0,M,,*5B";

NMEA_Message_t temp;
NMEA_Payload_GGA_t frame_gga;

void print_gga(const NMEA_Payload_GGA_t* frame);

int main(void) {
	NMEA_Pack(&temp, test_msg);

	if( temp.payloadId == NMEA_MSG_GGA ){
		NMEA_GGA_Parse(&frame_gga, &temp);
		printf("TESTING MSG : %s \n\n", test_msg);
		print_gga(&frame_gga);
	}
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

```
