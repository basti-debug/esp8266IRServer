# ESP 8266 IR Server
These are two arduino projects where i used an esp8266, an IR LED and a BS170 MOSFET, to control two separate LED Lights, where i wanted to add the aftermarket function to control them with a website.
Both of them use different commands to Turn On, Turn off etc. 

Both of them use the [NEC protocol](https://www.sbprojects.net/knowledge/ir/nec.php)

I connected an esp8266 to a Megacard (a ATmega16 with some added features like an IR Diode and Receiver, build by my school) to read the codes. I used the IRrecvDumpv2 Script from the IRremoteESP8266 Library  [see here](https://github.com/basti-debug/esp8266IRServer/blob/main/IRrecvDumpV2/IRrecvDumpV2.ino)

**TLDR** i used the Dump, pressed the button which i wanted to record on the remote got this response:

```
Timestamp : 000017.212
Library   : v2.8.4

Protocol  : NEC
Code      : 0xFFB04F (32 Bits)
uint16_t rawData[67] = {9088, 4450,  616, 546,  588, 520,  616, 520,  614, 520,  614, 520,  614, 522,  614, 522,  614, 522,  612, 1630,  620, 1624,  612, 1632,  618, 1626,  622, 1622,  616, 1628,  620, 1624,  614, 1630,  618, 1626,  622, 514,  622, 1620,  618, 1628,  620, 542,  592, 542,  592, 516,  618, 516,  620, 544,  592, 1624,  614, 524,  622, 540,  596, 1620,  616, 1628,  622, 1622,  614, 1630,  618};  // NEC FFB04F
uint32_t address = 0x0;
uint32_t command = 0xD;
uint64_t data = 0xFFB04F;
```
*so i used the rawData, stored it and sent it with the following function*

```
irsend.sendRaw(rawData,67,38); 
```

Subsequently i noted the commands and their function, created a webserver on the esp and configured the needed send Commands to send the IR signals. 






