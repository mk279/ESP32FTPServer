#include <WiFi.h>
#include <WiFiClient.h>
#include <SD_MMC.h>
#include "ESP32FtpServer.h"

const char* ssid = "blablabla..."; //WiFi SSID
const char* password = "blablabla..."; //WiFi Password
 
FtpServer ftpSrv;   //set #define FTP_DEBUG in ESP32FtpServer.h to see ftp verbose on serial

void setup(void){
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

  // FTP Setup, ensure SD is started before ftp

  // start SD using the SPI bus
  SPI.begin(14, 2, 15, 13);    
  if (SD.begin(13)) {
      Serial.println("SD opened in SPI mode!");
      ftpSrv.begin("esp32","esp32");    //username, password for ftp.  set ports in ESP32FtpServer.h  (default 21, 50009 for PASV)
  }  

/*
  // start SD using the SD_MMC mode (1Bit mode)
  pinMode(2, INPUT_PULLUP); // hardware pullup might be necessary, see https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/sd_pullup_requirements.html
  if (SD_MMC.begin("/sdcard", true)) {
      Serial.println("SD opened in MMC mode (1 Bit)!"); 
      ftpSrv.begin(SD_MMC, "esp32","esp32");    //username, password for ftp.  set ports in ESP32FtpServer.h  (default 21, 50009 for PASV)
  }  
*/

 /*
  // start SD using the SD_MMC mode (4Bit mode)
  if (SD_MMC.begin()) {
      Serial.println("SD opened in MMC mode (4 Bit)!"); 
      ftpSrv.begin(SD_MMC, "esp32","esp32");    //username, password for ftp.  set ports in ESP32FtpServer.h  (default 21, 50009 for PASV)
  }  
*/
}

void loop(void){
  ftpSrv.handleFTP();        //make sure in loop you call handleFTP()!!   
}
