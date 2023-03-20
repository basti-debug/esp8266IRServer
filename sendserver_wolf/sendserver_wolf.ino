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
uint16_t rawDataON[71] = {9066, 4458,  620, 514,  620, 514,  620, 514,  620, 514,  620, 514,  620, 514,  620, 514,  620, 514,  620, 1624,  614, 1632,  616, 1628,  620, 1624,  614, 1632,  618, 1626,  622, 1622,  614, 1630,  618, 1626,  612, 524,  610, 1634,  616, 1628,  620, 516,  620, 516,  620, 516,  620, 516,  620, 516,  618, 1626,  612, 524,  612, 522,  612, 1632,  616, 1630,  620, 1624,  612, 1632,  616, 39802,  9070, 2210,  616};  // NEC FFB04F
uint16_t rawDataOFF[71] = {9068, 4454,  612, 550,  586, 548,  586, 548,  586, 548,  588, 546,  588, 546,  590, 546,  590, 544,  590, 1626,  624, 1620,  618, 1626,  622, 1620,  618, 1626,  624, 1620,  618, 1626,  622, 1620,  618, 1626,  622, 1622,  616, 1626,  622, 1620,  618, 1626,  622, 540,  596, 538,  596, 538,  596, 538,  586, 548,  586, 548,  588, 546,  590, 544,  590, 1628,  622, 1622,  616, 1628,  620, 39774,  9076, 2200,  616};  // NEC FFF807

// Second Row
uint16_t rawDataRED[71] = {9078, 4446,  622, 512,  622, 512,  612, 522,  612, 522,  614, 520,  614, 520,  616, 518,  616, 518,  618, 1626,  612, 1632,  618, 1626,  614, 1630,  620, 1624,  616, 1628,  620, 1624,  616, 1626,  612, 1632,  618, 516,  618, 516,  620, 1622,  616, 1628,  620, 514,  610, 524,  612, 522,  612, 520,  616, 1630,  620, 1622,  616, 518,  618, 516,  618, 1624,  614, 1630,  620, 1624,  614, 39774,  9068, 2208,  622};  // NEC FF9867
uint16_t rawDataGREEN[71] = {9066, 4456,  612, 522,  612, 550,  586, 550,  586, 522,  614, 522,  614, 522,  614, 522,  614, 520,  616, 1630,  620, 1626,  612, 1632,  618, 1628,  612, 1632,  616, 1628,  622, 1622,  616, 1628,  620, 1624,  614, 1630,  618, 516,  620, 1624,  614, 1630,  618, 518,  618, 516,  620, 516,  618, 516,  620, 514,  620, 1626,  614, 520,  614, 520,  616, 1630,  620, 1624,  614, 1630,  620, 39792,  9074, 2204,  614};  // NEC FFD827
uint16_t rawDataBLUE[71] = {9086, 4448,  620, 516,  620, 516,  620, 542,  594, 514,  620, 542,  594, 542,  594, 540,  594, 542,  594, 1622,  614, 1630,  620, 1624,  614, 1632,  616, 1628,  622, 1622,  616, 1630,  620, 1626,  614, 1630,  620, 518,  618, 518,  618, 518,  618, 1626,  612, 522,  612, 522,  614, 522,  614, 522,  614, 1632,  618, 1626,  612, 1632,  618, 518,  618, 1626,  614, 1632,  618, 1626,  612, 39794,  9076, 2208,  622};  // NEC FF8877
uint16_t rawDataWHITE[67] = {9076, 4450,  618, 518,  616, 520,  616, 518,  618, 518,  618, 518,  618, 518,  618, 518,  618, 516,  618, 1626,  612, 1632,  618, 1626,  624, 1648,  590, 1654,  596, 1650,  588, 1630,  618, 1626,  622, 1622,  616, 520,  616, 1628,  620, 516,  620, 1624,  614, 520,  614, 522,  614, 522,  614, 520,  614, 1630,  620, 516,  620, 1624,  614, 520,  614, 1630,  620, 1624,  614, 1630,  618};  // NEC FFA857


uint16_t rawDataORANGE[71] = {9092, 4426,  642, 492,  642, 492,  642, 492,  644, 492,  644, 490,  646, 490,  646, 488,  648, 486,  614, 1630,  642, 1602,  648, 1596,  642, 1602,  648, 1594,  644, 1600,  648, 1596,  642, 1600,  650, 1594,  644, 1598,  650, 1592,  646, 488,  646, 1596,  642, 492,  644, 490,  644, 490,  646, 490,  646, 488,  646, 488,  648, 1594,  644, 492,  644, 1598,  650, 1592,  646, 1598,  652, 39742,  9102, 2176,  642};  // NEC FFE817
uint16_t rawDataLGREEN[71] = {9072, 4460,  618, 516,  620, 516,  618, 516,  618, 518,  618, 544,  592, 544,  592, 544,  590, 544,  590, 1654,  586, 1634,  616, 1630,  620, 1624,  614, 1632,  616, 1628,  620, 1624,  616, 1630,  620, 544,  592, 1626,  612, 524,  612, 524,  612, 1634,  616, 546,  590, 546,  588, 520,  616, 1630,  620, 516,  620, 1624,  614, 1632,  618, 518,  618, 1652,  586, 1632,  616, 1630,  620, 39808,  9082, 2206,  622};  // NEC FF48B7
uint16_t rawDataLBLUE[71] = {9080, 4456,  612, 524,  612, 524,  622, 514,  622, 514,  622, 514,  622, 514,  620, 514,  620, 542,  594, 1626,  614, 1632,  618, 1628,  620, 1626,  612, 1632,  616, 1628,  622, 1624,  614, 1632,  618, 518,  616, 1628,  620, 1626,  614, 522,  612, 1632,  618, 518,  616, 520,  614, 522,  614, 1632,  618, 518,  618, 518,  618, 1628,  622, 514,  620, 1624,  614, 1632,  616, 1628,  620, 39808,  9080, 2208,  622};  // NEC FF6897
uint16_t rawDataTORU[71] = {9066, 4458,  620, 514,  620, 514,  622, 540,  596, 514,  610, 524,  610, 552,  584, 552,  584, 550,  584, 1632,  616, 1628,  622, 1622,  616, 1628,  620, 1624,  614, 1630,  620, 1624,  614, 1632,  618, 518,  616, 518,  616, 1628,  610, 1634,  616, 520,  616, 520,  616, 1628,  620, 514,  622, 1622,  616, 1628,  622, 514,  622, 514,  622, 1622,  614, 1656,  594, 516,  620, 1624,  612, 39804,  9070, 2210,  618};  // NEC FF32CD
uint16_t rawDataVIOLET[71] = {9068, 4452,  614, 520,  616, 520,  616, 518,  616, 544,  590, 518,  616, 518,  618, 516,  618, 516,  620, 1624,  614, 1630,  618, 1626,  612, 1632,  616, 1628,  622, 1622,  616, 1628,  620, 1624,  612, 522,  614, 522,  614, 1630,  620, 516,  620, 516,  620, 516,  620, 514,  620, 514,  620, 1624,  614, 1630,  620, 514,  620, 1624,  614, 1630,  620, 1624,  614, 1632,  618, 1626,  622, 39784,  9066, 2212,  618};  // NEC FF20DF
uint16_t rawDataPINK[67] = {9110, 4422,  646, 490,  646, 490,  646, 490,  646, 490,  646, 490,  646, 488,  648, 488,  648, 488,  646, 1598,  652, 1592,  646, 1598,  650, 1594,  644, 1600,  650, 1594,  642, 1602,  648, 1596,  642, 1602,  646, 1598,  652, 1592,  646, 1598,  650, 484,  618, 518,  650, 484,  618, 518,  618, 514,  620, 514,  620, 514,  622, 514,  610, 1632,  616, 1628,  622, 1624,  614, 1628,  620};  // NEC FFF00F
uint16_t rawDataYELLOW[71] = {9070, 4456,  612, 522,  612, 522,  614, 520,  614, 522,  614, 520,  616, 518,  616, 518,  618, 516,  618, 1624,  614, 1630,  620, 1624,  614, 1630,  618, 1624,  614, 1628,  620, 1622,  616, 1628,  622, 514,  622, 512,  612, 1632,  616, 1626,  612, 1632,  618, 516,  618, 516,  620, 514,  622, 1622,  616, 1628,  620, 514,  610, 524,  612, 524,  612, 1630,  620, 1624,  612, 1630,  620, 39776,  9062, 2206,  622};  // NEC FF38C7


// Functions
uint16_t rawDataFLASH[71] = {9072, 4454,  612, 524,  612, 524,  612, 522,  612, 522,  614, 522,  614, 522,  614, 520,  616, 520,  616, 1628,  622, 1622,  616, 1628,  620, 1624,  614, 1632,  618, 1626,  612, 1634,  616, 1630,  620, 1624,  614, 522,  614, 1630,  618, 516,  620, 1626,  612, 522,  614, 520,  614, 520,  614, 520,  614, 1630,  620, 514,  620, 1624,  614, 520,  614, 1630,  620, 1626,  612, 1632,  618, 39790,  9070, 2208,  620};  // NEC FFA857
uint16_t rawDataSTROBE[71] = {9096, 4424,  642, 492,  642, 492,  642, 492,  644, 492,  644, 492,  644, 492,  644, 490,  644, 490,  644, 1600,  650, 1594,  642, 1602,  648, 1596,  642, 1602,  646, 1598,  650, 1596,  642, 1600,  648, 488,  648, 488,  648, 486,  648, 486,  650, 486,  650, 486,  650, 486,  650, 486,  650, 1594,  644, 1600,  650, 1594,  644, 1600,  648, 1594,  642, 1600,  648, 1596,  642, 1600,  648, 39746,  9102, 2176,  652};  // NEC FF00FF
uint16_t rawDataFADE[71] = {9104, 4416,  650, 484,  618, 516,  618, 516,  618, 516,  620, 514,  620, 514,  644, 492,  644, 490,  644, 1598,  650, 1592,  646, 1596,  642, 1602,  646, 1596,  642, 1602,  648, 1596,  642, 1602,  646, 488,  646, 1596,  642, 494,  642, 1602,  648, 1596,  642, 492,  644, 490,  644, 490,  644, 1598,  650, 486,  650, 1592,  612, 522,  612, 524,  612, 1632,  650, 1592,  644, 1598,  650, 39742,  9096, 2182,  646};  // NEC FF58A7
uint16_t rawDataSMOOTH[71] = {9068, 4452,  616, 518,  616, 518,  618, 518,  618, 516,  652, 482,  618, 516,  642, 492,  620, 516,  620, 1624,  614, 1630,  642, 1602,  614, 1630,  642, 1602,  646, 1598,  650, 1594,  646, 1598,  650, 486,  650, 484,  616, 1626,  644, 1600,  616, 520,  616, 520,  616, 518,  650, 484,  650, 1594,  644, 1598,  616, 518,  616, 518,  616, 1628,  612, 1632,  616, 1626,  622, 1624,  614, 39778,  9102, 2178,  650};  // NEC FF30CF



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
  
  website = website + generateButton("col-xs-4", "red", "Red","red");
  website = website + generateButton("col-xs-4", "green", "Green","green");
  website = website + generateButton("col-xs-4", "blue", "Blue","blue");
  website = website + generateButton("col-xs-4", "white", "White","white");
  
  website = website + generateButton("col-xs-4", "orange", "Orange","orange");
  website = website + generateButton("col-xs-4", "lgreen", "Light Green","lgreen");
  website = website + generateButton("col-xs-4", "lblue", "Light Blue","lblue");
  website = website + generateButton("col-xs-4", "toru", "Tourquise","toru");
  website = website + generateButton("col-xs-4", "violet", "Violet","violet");
  website = website + generateButton("col-xs-4", "pink", "Pink","pink");
  website = website + generateButton("col-xs-4", "yellow", "Yellow","yellow");

  website = website + generateButton("col-xs-4", "flash", "Flash","flash");  
  website = website + generateButton("col-xs-4", "strobe", "Strobe","strobe");
  website = website + generateButton("col-xs-4", "fade", "Fade","fade");
  website = website + generateButton("col-xs-4", "smooth", "Smooth","smooth");



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


  server.on("/red", [](){
    Serial.println("Client -- Red");
    irsend.sendRaw(rawDataRED,67,38); 
    server.send(200, "text/plain", "Red");
  });

  server.on("/green", [](){
    Serial.println("Client -- green");
    irsend.sendRaw(rawDataGREEN,67,38); 
    server.send(200, "text/plain", "green");
  });

  server.on("/blue", [](){
    Serial.println("Client -- Blue");
    irsend.sendRaw(rawDataBLUE,67,38); 
    server.send(200, "text/plain", "Blue");
  });

  server.on("/white", [](){
    Serial.println("Client -- White");
    irsend.sendRaw(rawDataWHITE,67,38); 
    server.send(200, "text/plain", "White");
  });

  server.on("/orange", [](){
    Serial.println("Client -- Orange");
    irsend.sendRaw(rawDataORANGE,67,38); 
    server.send(200, "text/plain", "Orange");
  });
  
  server.on("/lgreen", [](){
    Serial.println("Client -- Light Green");
    irsend.sendRaw(rawDataLGREEN,67,38); 
    server.send(200, "text/plain", "Lgreen");
  });


  server.on("/lblue", [](){
    Serial.println("Client -- Light Blue");
    irsend.sendRaw(rawDataLBLUE,67,38); 
    server.send(200, "text/plain", "lblue");
  });

  server.on("/toru", [](){
    Serial.println("Client -- toru");
    irsend.sendRaw(rawDataTORU,67,38); 
    server.send(200, "text/plain", "TORU");
  });

  server.on("/violet", [](){
    Serial.println("Client -- violet");
    irsend.sendRaw(rawDataVIOLET,67,38); 
    server.send(200, "text/plain", "violet");
  });

  server.on("/pink", [](){
    Serial.println("Client -- pink");
    irsend.sendRaw(rawDataPINK,67,38); 
    server.send(200, "text/plain", "pink");
  });

  server.on("/yellow", [](){
    Serial.println("Client -- yellow");
    irsend.sendRaw(rawDataYELLOW,67,38); 
    server.send(200, "text/plain", "yellow");
  });  

  server.on("/flash", [](){
    Serial.println("Client -- flash");
    irsend.sendRaw(rawDataFLASH,67,38); 
    server.send(200, "text/plain", "flash");
  });

  server.on("/strobe", [](){
    Serial.println("Client -- strobe");
    irsend.sendRaw(rawDataSTROBE,67,38); 
    server.send(200, "text/plain", "strobe");
  });

  server.on("/fade", [](){
    Serial.println("Client -- fade");
    irsend.sendRaw(rawDataFADE,67,38); 
    server.send(200, "text/plain", "fade");
  });

  server.on("/smooth", [](){
    Serial.println("Client -- smooth");
    irsend.sendRaw(rawDataSMOOTH,67,38); 
    server.send(200, "text/plain", "smooth");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP Server started");
}

void loop() {
  server.handleClient();
}
