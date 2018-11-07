#include <IRsend.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <WiFiUDP.h>
#include <WakeOnLan.h>
#include <Syslog.h>

IRsend irsend(D1);

// Id para OTA
char *app="mando";
extern char *ver;

ESP8266WebServer server(80);
extern Syslog syslog;
HTTPClient http;

// Orden IR a la tele
void irnec(unsigned int code) { irsend.sendNEC(code,32); }

// Orden al webserver de EventGhost en el PC
void evghost(String cmd) { http.begin("http://192.168.0.6:1111/?"+cmd); http.GET(); }

void tvon()    { irnec(0x20DF23DC); }
void tvoff()   { irnec(0x20DFA35C); }
void tvmas()   { irnec(0x20DF40BF); }
void tvmenos() { irnec(0x20DFC03F); }
void tvhdmi1() { irnec(0x20DF738C); }
void tvok()    { irnec(0x20DF22DD); }

void kodi()    { evghost("kodi");   }
void wmc()     { evghost("wmc");    }
void duerme()  { evghost("duerme"); }
void monon()   { evghost("monon");  }

void wol() {
  WiFiUDP UDP;
  IPAddress computer_ip(255,255,255,255); 
  byte mac[]={0x00,0x1E,0x0B,0xB4,0xBA,0xE9}; // SALON
  WakeOnLan::sendWOL(computer_ip,UDP,mac,sizeof mac);
}

void on() { wol(); tvon(); }

void setup() { 
  inicia();
  syslog.log("Listo!");
  irsend.begin();
  server.on("/act",act);
  server.on("/",act);
  server.begin();
}

void loop() {
  server.handleClient();
}

void act() {
  String cmd=server.arg("cmd");
  server.send(200,"text/plain",cmd);  
  if (cmd=="tvon")    tvon()      ; else
  if (cmd=="tvoff")   tvoff()     ; else
  if (cmd=="tvmas")   tvmas()     ; else
  if (cmd=="tvmenos") tvmenos()   ; else
  if (cmd=="tvhdmi1") tvhdmi1()   ; else
  if (cmd=="tvhdmi1") tvhdmi1()   ; else
  if (cmd=="tvok")    tvok()      ; else
  if (cmd=="on")      { on();         delay(7e3); monon(); } else
  if (cmd=="wmc")     { on(); wmc() ; delay(7e3); wmc() ;  } else
  if (cmd=="kodi")    { on(); kodi(); delay(7e3); kodi();  } else
  if (cmd=="sleep")   { duerme();     delay(2e1); tvoff(); } else
  if (cmd=="reset")   { delay(5e3); ESP.reset(); } 
}


