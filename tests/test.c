/* *	tests.c
 *
 *  Created on: Dec 16, 2023
 *      Author: BerkN
 *
 *  NMEA 0183 Protocol Parser for Ublox GNSS Receivers.
 *	Easy to use for all NMEA applications / Extendable NMEA message ID library.
 *
 */


#include <stdio.h>
#include "nmea.h"

#define MESSAGE_LIST_LEN 10

char* valid_msg[] = { 
	"$GNGBS,170556.00,3.0,2.9,8.3,,,,*5C",
	"$GPGBS,235458.00,1.4,1.3,3.1,03,,-21.4,3.8,1,0*5B",
	"$GNGGA,092725.00,4717.11399,N,00833.91590,E,1,08,1.01,499.6,M,48.0,M,,*5B",
	"$GPGLL,4717.11364,N,00833.91565,E,092321.00,A,A*60",
	"$GPGSA,A,3,23,29,07,08,09,18,26,28,,,,,1.94,1.18,1.54,1*0D",
	"$GPGST,082356.00,1.8,,,,1.7,1.3,2.2*7E",
	"$GPGSV,1,1,03,12,,,42,24,,,47,32,,,37,5*66",
	"$GPRMC,083559.00,A,4717.11437,N,00833.91522,E,0.004,77.52,091202,,,A,V*57",
	"$GPVTG,77.52,T,,M,0.004,N,0.008,K,A*06",
	"$GPZDA,082710.00,16,09,2002,00,00*64",
};

char* corrupted_msg[] = {
	"GNGBS,170556.00,3.0,2.9,8.3,,,,*5C",
	"$GPGBB,235458.00,1.4,1.3,3.1,03,,-21.4,3.8,1,0*5B",
	"$GNGGA,P9PP2725.00,4717.11399,N,00833.91590,E,1,08,1.01,499.6,M,48.0,M,,*5B",
	"$GPGLL,4717.11364,N,00833.91565,60",
	"$GPGSA,A,3,23,29,07,08,09,18,26,",
	"\n$GPGST,082356.00,1.8,,,,1.7,1.3,2.2*7E",
	"$GPGSV122,1,03,12,,,42,24,,,47,32,,,37,5*66",
	"$GPRMC,083559.00,4717.11437,N,00833.91522,E,0.004,77.52,091202,",
	"$GPVTG",
	"$GPZDA,082710.00,16,09",
};

static char* test_msg = "$GNGGA,092725.00,4717.11399,N,00833.91590,E,1,08,1.01,499.6,M,48.0,M,,*5B";

static NMEA_Message_t temp;

static NMEA_Payload_GBS_t frame_gbs;
static NMEA_Payload_GGA_t frame_gga;
static NMEA_Payload_GLL_t frame_gll;
static NMEA_Payload_GSA_t frame_gsa;
static NMEA_Payload_GST_t frame_gst;
static NMEA_Payload_GSV_t frame_gsv;
static NMEA_Payload_RMC_t frame_rmc;
static NMEA_Payload_VTG_t frame_vtg;
static NMEA_Payload_ZDA_t frame_zda;

void nmea_tester(const NMEA_Message_t* test_);

void print_gbs(const NMEA_Payload_GBS_t* frame);
void print_gga(const NMEA_Payload_GGA_t* frame);
void print_gll(const NMEA_Payload_GLL_t* frame);
void print_gsa(const NMEA_Payload_GSA_t* frame);
void print_gst(const NMEA_Payload_GST_t* frame);
void print_gsv(const NMEA_Payload_GSV_t* frame);
void print_rmc(const NMEA_Payload_RMC_t* frame);
void print_vtg(const NMEA_Payload_VTG_t* frame);
void print_zda(const NMEA_Payload_ZDA_t* frame);

int main(void) {
	
	for (uint8_t i = 0; i <MESSAGE_LIST_LEN ; i++)
	{
		test_msg = valid_msg[i];
		printf("\nTESTING : %s \n", test_msg);
		if (test_msg) nmea_tester(test_msg);
	}

	return 0;
}


void nmea_tester(const NMEA_Message_t* test_) {
	printf("--- NMEA TESTING ---\n\n");
	if(!NMEA_Pack(&temp, test_msg)) printf("PACKING ERROR\n");

	switch (temp.payloadId) {
	case(NMEA_MSG_GBS): {
		if (!NMEA_GBS_Parse(&frame_gbs, &temp))printf("PARSE ERROR\n");
		else print_gbs(&frame_gbs);
	}break;
	case(NMEA_MSG_GGA): {
		if (!NMEA_GGA_Parse(&frame_gga, &temp))printf("PARSE ERROR\n");
		else print_gga(&frame_gga);
	}break;
	case(NMEA_MSG_GLL): {
		if (!NMEA_GLL_Parse(&frame_gll, &temp))printf("PARSE ERROR\n");
		else print_gll(&frame_gll);
	}break;
	case(NMEA_MSG_GSA): {
		if (!NMEA_GSA_Parse(&frame_gsa, &temp))printf("PARSE ERROR\n");
		else print_gsa(&frame_gsa);
	}break;
	case(NMEA_MSG_GST): {
		if (!NMEA_GST_Parse(&frame_gst, &temp))printf("PARSE ERROR\n");
		else print_gst(&frame_gst);
	}break;
	case(NMEA_MSG_GSV): {
		if (!NMEA_GSV_Parse(&frame_gsv, &temp))printf("PARSE ERROR\n");
		else print_gsv(&frame_gsv);
	}break;
	case(NMEA_MSG_RMC): {
		if (!NMEA_RMC_Parse(&frame_rmc, &temp))printf("PARSE ERROR\n");
		else print_rmc(&frame_rmc);
	}break;
	case(NMEA_MSG_VTG): {
		if (!NMEA_VTG_Parse(&frame_vtg, &temp))printf("PARSE ERROR\n");
		else print_vtg(&frame_vtg);
	}break;
	case(NMEA_MSG_ZDA): {
		if (!NMEA_ZDA_Parse(&frame_zda, &temp))printf("PARSE ERROR\n");
		else print_zda(&frame_zda);
	}break;
	default: {
		if (temp.payloadId != 0)printf("NOT SUPPORTED PAYLOAD ID : %d\n", temp.payloadId);
		else { printf("PAYLOAD ID ERROR.\n"); }
	}break;
	}
}


void print_gbs(const NMEA_Payload_GBS_t* frame) {

	printf("- PAYLOAD GBS -\n");

	printf("HOUR : %d\n", frame->time.hour);
	printf("MIN : %d\n", frame->time.min);
	printf("SEC : %d\n", frame->time.sec);
	printf("ERRLAT : %f\n", frame->errLat);
	printf("ERRLON : %f\n", frame->errLon);
	printf("ERRALT : %f\n", frame->errAlt);
	printf("SVID : %d\n", frame->svid);
	printf("PROB : %f\n", frame->prob);
	printf("BIAS : %f\n", frame->bias);
	printf("STDDEV : %f\n", frame->stddev);

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

void print_gll(const NMEA_Payload_GLL_t* frame) {

	printf("- PAYLOAD GLL -\n");

	printf("HOUR : %d\n", frame->time.hour);
	printf("MIN : %d\n", frame->time.min);
	printf("SEC : %d\n", frame->time.sec);
	printf("LATITUDE : %f\n", frame->latitude);
	printf("L_NORTH : %d\n", frame->l_north);
	printf("LONGITUDE : %f\n", frame->longitude);
	printf("L_EAST : %d\n", frame->l_east);
	printf("POSMODE : %c\n", frame->posMode);
	printf("STATUS : %c\n", frame->status);

}

void print_gst(const NMEA_Payload_GST_t* frame) {
	printf("- PAYLOAD GST -\n");

	printf("HOUR : %d\n", frame->time.hour);
	printf("MIN : %d\n", frame->time.min);
	printf("SEC : %d\n", frame->time.sec);
	printf("RANGE RMS : %f\n", frame->rangeRms);
	printf("STD MAJOR : %f\n", frame->stdMajor);
	printf("STD MINOR : %f\n", frame->stdMinor);
	printf("ORIENT : %f\n", frame->orient);
	printf("STD LAT : %f\n", frame->stdLat);
	printf("STD LON : %f\n", frame->stdLon);
	printf("STD ALT : %f\n", frame->stdAlt);
}


void print_gsa(const NMEA_Payload_GSA_t* frame) {
	printf("- PAYLOAD GSA -\n");

	printf("OP MODE : %c\n", frame->opMode);
	printf("NAV MODE : %d\n", frame->navMode);
	printf("FIX TYPE : %d\n", frame->fix_type);
	
	for (uint8_t i = 0; i < 12; i++)
	{
		printf("SAT%d ID : %d\n",i, frame->sats[i]);
	}

	printf("PDOP : %f\n", frame->pdop);
	printf("HDOP : %f\n", frame->hdop);
	printf("VDOP : %f\n", frame->vdop);
}

void print_gsv(const NMEA_Payload_GSV_t* frame) {
	
	printf("- PAYLOAD GSV -\n");

	printf("NUM MSG : %d\n", frame->numMsg);
	printf("MSG NUM : %d\n", frame->msgNum);
	printf("NUM SV : %d\n", frame->numSV);
	
	for (uint8_t i = 0; i < frame->numSV; i++) {
		printf("SATELLITE %d", i);
		printf("NR : %d\n", frame->sats[i].nr);
		printf("SNR : %d\n", frame->sats[i].snr);
		printf("ELEVATION : %d\n", frame->sats[i].elevation);
		printf("AZIMUTH : %d\n", frame->sats[i].azimuth);
	}
}


void print_rmc(const NMEA_Payload_RMC_t* frame) {
	printf("- PAYLOAD RMC -\n");

	printf("HOUR : %d\n", frame->time.hour);
	printf("MIN : %d\n", frame->time.min);
	printf("SEC : %d\n", frame->time.sec);

	printf("STATUS : %c\n", frame->status);

	printf("LATITUDE : %f\n", frame->latitude);
	printf("L_NORTH : %d\n", frame->l_north);
	printf("LONGITUDE : %f\n", frame->longitude);
	printf("L_EAST : %d\n", frame->l_east);
	
	printf("SPEED : %f\n", frame->speed);
	printf("COURSE : %f\n", frame->course);
	
	printf("DATE : %d : %d : %d \n", frame->date.day, frame->date.month, frame->date.year);

	printf("VARIATION : %f\n", frame->variation);
	printf("POSMODE : %c\n", frame->posMode);
	printf("NAVSTATUS : %c\n", frame->navStatus);
}

void print_vtg(const NMEA_Payload_VTG_t* frame) {
	printf("- PAYLOAD VTG -\n");

	printf("COTG : %f\n", frame->cogt);
	printf("COTM : %f\n", frame->cogm);
	printf("SOGN : %f\n", frame->sogn);
	printf("SOGK : %f\n", frame->sogk);
	printf("POSMODE : %c\n", frame->posMode);
}

void print_zda(const NMEA_Payload_ZDA_t* frame) {
	printf("- PAYLOAD ZDA -\n");

	printf("HOUR : %d\n", frame->time.hour);
	printf("MIN : %d\n", frame->time.min);
	printf("SEC : %d\n", frame->time.sec);

	printf("DATE : %d : %d : %d \n", frame->date.day, frame->date.month, frame->date.year);
}
