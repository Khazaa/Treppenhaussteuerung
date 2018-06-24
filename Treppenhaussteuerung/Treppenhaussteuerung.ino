

//Nicht verändern!
#include <PString.h>
#include <RCSwitch.h>
RCSwitch mySwitch = RCSwitch();
#include <ESP8266WiFi.h>
WiFiClient net;
#define seconds() (millis()/1000)
#define RC433On 1234
#define RC433Off 2345
#include <MQTT.h>
MQTTClient client;
#include <DigitalSensor.h>


//DEBUG 0 = OFF, 1 = ON
int debug = 1;

//POWER 0 = OFF, 1 = ON
int POWER = 1;

//WLAN Settings
const char* ssid = "xxx";
const char* password = "xxxx";

//MQTT Settings
const char* MQTT_Broker = "1.2.3.4";
int MQTT_Port = 1883;
const char* MQTT_Username = "xxx";
const char* MQTT_Password = "xxx";

//Globale Variablen deklarieren
int V_Licht;
int V_Licht_alt;
int V_DAUER_LICHT_SEK;
int V_LICHT_TIMEOUT;
int V_Sec_Check;

//PINs zuordnen
int P_RFTRANSMITTER = 12;  // Digital pin D6
// Create digital PIR sensor instance on D2 pin
DigitalSensor P_BEWEGUNG1(5); //int P_BEWEGUNG1 = 5;  // Digital pin D1

// Create digital PIR sensor instance on D2 pin
DigitalSensor P_BEWEGUNG2(13); //int P_BEWEGUNG2 = 14;  // Digital pin D5 // int P_BEWEGUNG2 = 13;  // Digital pin D7 // int P_BEWEGUNG2 = 0;  // Digital pin D3 DANACH TESTEN

// Create digital PIR sensor instance on D2 pin
DigitalSensor P_HELLIGKEIT(4); //int P_HELLIGKEIT = 4;  // Digital pin D2


char converttimetostringhelperM[2];
char converttimetostringhelperH[2];
char converttimetostringhelperT[4];
String stringhelperM;
String stringhelperH;
String stringhelperT;
int min_1_check = 0;
unsigned long gesamt_minuten = 0;
unsigned long gesamt_stunden = 0;
unsigned long gesamt_tage = 0;
unsigned long gesamt_sekunden = 0;
//char cstr[2];

//NTP TIME
#include <TimeLib.h> 
#include <WiFiUdp.h>
// NTP Servers:
IPAddress timeServer(192, 53, 103, 108); // ptbtime1.ptb.de
//IPAddress timeServer(192, 53, 103, 104); // ptbtime2.ptb.de
//IPAddress timeServer(192, 53, 103, 103); // ptbtime3.ptb.de
const int timeZone = 1;     // Central European Time

WiFiUDP Udp;
unsigned int localPort = 8888;  // local port to listen for UDP packets
time_t prevDisplay = 0; // when the digital clock was displayed
/////


void setup() 
{
  Serial.begin(9600);
  delay(200);
  mySwitch.enableTransmit(P_RFTRANSMITTER);
  
  //Variablen initialisieren und setzen
  V_Licht = 0;
  V_Licht_alt = 0;
  V_Licht_alt = 0;
  V_DAUER_LICHT_SEK = 30;
  V_LICHT_TIMEOUT = 0;
  V_Sec_Check = seconds();
  WiFi.begin(ssid, password);
  client.begin(MQTT_Broker, MQTT_Port, net);
  client.onMessage(messageReceived);
  
  client.setOptions(10, true,2000);
  
  ConnectWiFi();
  delay(1000);
  ConnectMQTT();
  
  StartUDP();
  setSyncProvider(getNtpTime);


  char myNewCombinedArray[24];
  PString str2(myNewCombinedArray, sizeof(myNewCombinedArray));
  str2 = "";
  str2 += leadZero(day());
  str2 += ".";
  str2 += leadZero(month());
  str2 += ".";
  str2 += year();
  str2 += " ";
  str2 += leadZero(hour());
  str2 += ":";
  str2 += leadZero(minute());
  str2 += ":";
  str2 += leadZero(second());
  
  Serial.println(myNewCombinedArray);
  client.publish("/Treppenhaus_LED/INFO/UPTIME", myNewCombinedArray);
}
