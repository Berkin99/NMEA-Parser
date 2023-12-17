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

char rawMessageLine [] = ""




```
