#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>
#include <Syslog.h>
#include "wifikeys.h" // contiene WifiAPEntry wifis[]

/*
 * Conecta a WiFi
 * Configura syslog remoto.
 * Actualiza soft. si es necesario.
 */

extern char *app;
extern char *ver;
char chipId[20];

WiFiUDP udp;
Syslog syslog(udp);

bool inicia() {
  Serial.begin(74880);
  snprintf(chipId,sizeof(chipId),"%u",ESP.getChipId());
  syslog.server("syslog.rosich.es",514);
  syslog.deviceHostname(chipId);
  syslog.appName(app);
  syslog.defaultPriority(LOG_INFO);
  while (!wifota()) delay(60e3);
}

bool wifota() {
  WiFi.mode(WIFI_STA);
  ESP8266WiFiMulti wifiMulti;
  
  for(WifiAPEntry wifi:wifis) 
    wifiMulti.addAP(wifi.ssid,wifi.passphrase);

  Serial.println(WiFi.macAddress()+" conectando a wifi");
  
  for (int segs=1; segs<=15; segs++) {
    if (wifiMulti.run() == WL_CONNECTED) {
      Serial.println(WiFi.localIP()); 
      ESPhttpUpdate.update("ota.rosich.es",80,
        "/cgi/ota?ser="+(String)ESP.getChipId()+"&app="+app+"&ver="+ver);
      return(true);
    }
    delay(1000);
  }
  Serial.println("Fallo de conexion"); 
  return(false);
}
