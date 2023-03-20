#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <IRsend.h>
#include <IRremoteESP8266.h>

#define IR_SEND_PIN 14

IRsend irsend(IR_SEND_PIN);



// Network DATA
const char* ssid = "matebook";      //Network Name
const char* password = "A0]7346r";  //Network Password

ESP8266WebServer server(80);

const int led = BUILTIN_LED;


// First Row
uint16_t rawDataON[71] = {9150, 4484,  592, 520,  614, 526,  598, 542,  594, 520,  616, 526,  598, 542,  594, 520,  682, 460,  598, 1650,  620, 1654,  594, 1654,  594, 1654,  616, 1658,  590, 1658,  592, 1658,  624, 1654,  594, 1652,  598, 542,  592, 1656,  592, 548,  588, 526,  620, 520,  594, 1656,  616, 524,  588, 552,  594, 1654,  594, 546,  588, 1662,  598, 1650,  620, 1654,  594, 520,  614, 1660,  588, 39964,  9132, 2206,  620};  // NEC FFA25D
uint16_t rawDataOFF[71] = {9152, 4482,  594, 520,  626, 542,  570, 572,  562, 526,  620, 520,  592, 548,  598, 518,  618, 524,  588, 1660,  622, 1656,  592, 1660,  590, 1660,  622, 1656,  592, 1658,  592, 1660,  622, 1654,  596, 1656,  592, 1658,  624, 1654,  596, 520,  616, 554,  570, 570,  564, 1658,  590, 552,  594, 522,  614, 554,  572, 542,  592, 1658,  590, 1662,  620, 1658,  590, 552,  594, 1656,  594, 39992,  9158, 2208,  620};  // NEC FFE21D

// Second Row
uint16_t rawDataCOMB[71] = {9146, 4484,  594, 548,  596, 518,  618, 524,  588, 552,  594, 520,  626, 516,  596, 544,  592, 524,  622, 1654,  594, 1656,  592, 1658,  624, 1654,  594, 1654,  594, 1656,  626, 1650,  598, 1652,  596, 546,  588, 524,  622, 1656,  592, 522,  624, 516,  596, 544,  590, 1658,  590, 552,  594, 1656,  594, 1656,  614, 526,  598, 1652,  620, 1658,  590, 1658,  590, 550,  594, 1654,  594, 39978,  9138, 2238,  590};  // NEC FF22DD
uint16_t rawDataSTON[71] = {9152, 4458,  620, 520,  592, 548,  598, 516,  620, 520,  592, 548,  598, 516,  618, 522,  592, 550,  596, 1654,  594, 1656,  614, 1662,  598, 1654,  596, 1656,  614, 1664,  596, 1654,  594, 1658,  624, 1652,  596, 1654,  594, 548,  588, 526,  620, 520,  592, 548,  598, 1654,  594, 546,  590, 524,  622, 518,  594, 1656,  626, 1652,  596, 1656,  594, 1658,  624, 518,  596, 1656,  616, 40004,  9148, 2216,  590};  // NEC FFC23D
uint16_t rawDataPULS[71] = {9142, 4494,  594, 548,  596, 520,  594, 548,  596, 520,  616, 526,  596, 546,  590, 526,  620, 550,  562, 1664,  618, 1664,  596, 1658,  590, 1664,  618, 1662,  598, 1656,  592, 1662,  620, 1660,  600, 1654,  594, 1660,  622, 1658,  592, 552,  594, 548,  564, 578,  568, 548,  588, 554,  570, 572,  562, 552,  594, 548,  564, 1662,  620, 1660,  588, 1664,  596, 1658,  624, 1656,  592, 40066,  9142, 2242,  596};  // NEC FFE01F
uint16_t rawDataWAVE[71] = {9114, 4496,  592, 548,  588, 526,  620, 520,  592, 548,  586, 526,  620, 520,  592, 548,  586, 528,  620, 1658,  590, 1662,  586, 1666,  616, 1662,  588, 1664,  596, 1656,  614, 1664,  596, 1656,  592, 1660,  622, 518,  596, 546,  590, 1662,  598, 544,  592, 522,  624, 516,  596, 544,  590, 524,  622, 1656,  592, 1658,  590, 550,  596, 1656,  592, 1660,  622, 1658,  592, 1660,  588, 40066,  9118, 2246,  592};  // NEC FF906F
uint16_t rawDataSWGLO[71] = {9212, 4462,  624, 548,  566, 580,  566, 552,  594, 550,  564, 580,  566, 552,  594, 552,  572, 574,  572, 1656,  592, 1666,  616, 1666,  594, 1664,  596, 1660,  622, 1662,  598, 1658,  602, 1654,  628, 544,  568, 1660,  622, 1662,  600, 546,  598, 1656,  592, 554,  592, 552,  572, 574,  572, 1656,  592, 578,  568, 550,  598, 1656,  592, 526,  620, 1660,  600, 1654,  594, 1662,  620, 40026,  9182, 2218,  598};  // NEC FF6897
uint16_t rawDataFLASH[71] = {9128, 4484,  592, 522,  624, 516,  596, 544,  590, 524,  624, 516,  596, 546,  590, 524,  622, 520,  592, 1658,  624, 1654,  596, 1656,  594, 1658,  624, 1654,  594, 1656,  592, 1658,  624, 1654,  594, 1656,  592, 548,  588, 1664,  596, 1656,  616, 524,  588, 552,  594, 520,  614, 526,  598, 542,  592, 1658,  590, 550,  596, 518,  616, 1660,  588, 1664,  596, 1656,  614, 1662,  598, 40030,  9110, 2216,  624};  // NEC FFB04F
uint16_t rawDataSEQ[71] = {9130, 4482,  596, 572,  562, 552,  594, 546,  568, 572,  562, 550,  596, 546,  568, 572,  564, 550,  596, 1680,  568, 1656,  592, 1660,  622, 1656,  592, 1660,  588, 1664,  618, 1660,  598, 1654,  594, 576,  570, 546,  590, 1688,  570, 1656,  594, 576,  570, 546,  590, 552,  572, 570,  564, 1686,  562, 1662,  618, 550,  564, 578,  566, 1684,  564, 1660,  620, 1658,  592, 1660,  588, 40028,  9124, 2268,  570};  // NEC FF30CF
uint16_t rawDataOFSEQ[71] = {9206, 4458,  620, 522,  592, 548,  596, 518,  616, 524,  588, 552,  594, 520,  626, 516,  596, 544,  592, 1660,  590, 1662,  620, 1658,  590, 1660,  600, 1652,  618, 1660,  598, 1652,  596, 1656,  626, 516,  596, 1654,  616, 1662,  596, 1654,  594, 1658,  624, 516,  596, 1656,  616, 526,  598, 1652,  620, 522,  590, 550,  598, 516,  620, 522,  590, 1660,  622, 518,  594, 1656,  614, 39996,  9144, 2208,  598};  // NEC FF7A85


// Functions
uint16_t rawDataDIM[71] = {9176, 4488,  600, 516,  618, 524,  654, 488,  592, 524,  678, 466,  592, 550,  596, 520,  626, 516,  596, 1656,  626, 1652,  596, 1656,  592, 1660,  622, 1656,  592, 1660,  600, 1654,  616, 1662,  598, 518,  616, 526,  598, 546,  590, 1662,  596, 546,  656, 460,  674, 468,  656, 488,  646, 1606,  600, 1652,  618, 1662,  598, 518,  618, 1660,  598, 1652,  596, 1656,  626, 1652,  596, 40004,  9156, 2208,  620};  // NEC FF10EF
uint16_t rawDataBRIG[71] = {9120, 4484,  594, 572,  562, 550,  598, 542,  570, 568,  566, 546,  588, 552,  562, 576,  570, 544,  592, 1656,  592, 1658,  590, 1658,  624, 1652,  598, 1652,  596, 1654,  618, 1658,  590, 1660,  590, 550,  596, 1652,  596, 542,  592, 1658,  592, 1658,  624, 516,  596, 1652,  620, 520,  592, 1656,  624, 516,  598, 1650,  620, 520,  592, 546,  588, 1660,  588, 552,  594, 1654,  594, 40002,  9116, 2240,  588};  // NEC FF5AA5


String generateButton(String colSize, String id, String text, String url) {

  return  "<div class=\"" + colSize + "\" style=\"text-align: center\">\n" +
          "    <button id=\"" + id + "\" type=\"button\" class=\"btn btn-default\" style=\"width: 100%\" onclick='makeAjaxCall(\"" + url + "\")'>" + text + "</button>\n" +
          "</div>\n";
}

String rowDiv = "    <div class=\"row\" style=\"padding-bottom:1em\">\n";
String endDiv = "    </div>\n";

void handleRoot(){
  digitalWrite(led,0);
  String website = "<!DOCTYPE html>\n";
  website = website + "<html>\n";
  website = website + "<head>\n";
  website = website + "<title>Burtschers Lampen Steuerung</title>\n";
  website = website + "<style>\n";
  website = website + "body{\n";
  website = website + "background-color: black;\n";
  website = website + "width: 30%;\n";
  website = website + "}\n";
  website = website + "button{\n";
  website = website + "font-family: 'Gill Sans', 'Gill Sans MT', Calibri, 'Trebuchet MS', sans-serif;\n";
  website = website + "color: red;\n";
  website = website + "}\n";
  website = website + "</style>\n";
  website = website + "</head>\n";
  website = website + "<body>\n";
  website = website + "<h1>IR LED Controller</h1>\n";
  
  website = website + generateButton("col-xs-4", "on", "Turn LED on","turnon");
  website = website + generateButton("col-xs-4", "off", "Turn LED off","turnoff");
  
  website = website + generateButton("col-xs-4", "comb", "Combination","comb");
  website = website + generateButton("col-xs-4", "ston", "Steady on","ston");
  website = website + generateButton("col-xs-4", "puls", "Puls","puls");
  website = website + generateButton("col-xs-4", "wave", "Waves","wave");
  website = website + generateButton("col-xs-4", "swglo", "Slow Glow","swglo");
  website = website + generateButton("col-xs-4", "flash", "Flash","flash");
  website = website + generateButton("col-xs-4", "seq", "Slo Glo","seq");
  website = website + generateButton("col-xs-4", "ofseq", "Twinkle Flash","toru");
  
  website = website + generateButton("col-xs-4", "dim", "Dim the lights","dim");
  website = website + generateButton("col-xs-4", "brig", "Brighter","brig");



  website = website + "    <script src=\"https://ajax.googleapis.com/ajax/libs/jquery/1.12.4/jquery.min.js\"></script>\n";
  website = website + "    <script> function makeAjaxCall(url){$.ajax({\"url\": url})}</script>\n";

  website = website + "</body>\n";
  website = website + "</html>\n";

  server.send(200, "text/html", website);
  digitalWrite(led, 1);
}

void handleNotFound(){
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 1);
}

void setup(void) {
  
  irsend.begin(); // Start IR Function

  pinMode(led, OUTPUT);
  digitalWrite(led, 1);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");  

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS Responder Started");
  }

  server.on("/", handleRoot);

  server.on("/turnon", [](){
    Serial.println("Client -- Turned on");
    irsend.sendRaw(rawDataON,67,38); 
    server.send(200, "text/plain", "Turned On");

  });

  server.on("/turnoff", [](){
    Serial.println("Client -- Turned off");
    irsend.sendRaw(rawDataOFF,67,38); 
    server.send(200, "text/plain", "Turned Off");
  });


  server.on("/comb", [](){
    Serial.println("Client -- combo");
    irsend.sendRaw(rawDataCOMB,67,38); 
    server.send(200, "text/plain", "COMBO");
  });

  server.on("/ston", [](){
    Serial.println("Client -- ston");
    irsend.sendRaw(rawDataSTON,67,38); 
    server.send(200, "text/plain", "ston");
  });

  server.on("/puls", [](){
    Serial.println("Client -- puls");
    irsend.sendRaw(rawDataPULS,67,38); 
    server.send(200, "text/plain", "Puls");
  });

  server.on("/wave", [](){
    Serial.println("Client -- wave");
    irsend.sendRaw(rawDataWAVE,67,38); 
    server.send(200, "text/plain", "wave");
  });

  server.on("/swglo", [](){
    Serial.println("Client -- swglo");
    irsend.sendRaw(rawDataSWGLO,67,38); 
    server.send(200, "text/plain", "swglo");
  });
  
  server.on("/flash", [](){
    Serial.println("Client -- flash");
    irsend.sendRaw(rawDataFLASH,67,38); 
    server.send(200, "text/plain", "flash");
  });


  server.on("/seq", [](){
    Serial.println("Client -- seq");
    irsend.sendRaw(rawDataSEQ,67,38); 
    server.send(200, "text/plain", "seq");
  });

  server.on("/ofseq", [](){
    Serial.println("Client -- ofseq");
    irsend.sendRaw(rawDataOFSEQ,67,38); 
    server.send(200, "text/plain", "ofseq");
  });

  server.on("/dim", [](){
    Serial.println("Client -- dim");
    irsend.sendRaw(rawDataDIM,67,38); 
    server.send(200, "text/plain", "dim");
  });

  server.on("/brig", [](){
    Serial.println("Client -- brig");
    irsend.sendRaw(rawDataBRIG,67,38); 
    server.send(200, "text/plain", "brig");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP Server started");
}

void loop() {
  server.handleClient();
}
