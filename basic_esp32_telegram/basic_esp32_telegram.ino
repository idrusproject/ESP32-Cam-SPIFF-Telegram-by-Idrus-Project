#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
#include "esp_camera.h"
#include <UniversalTelegramBot.h>  //1.3.0
#include <ArduinoJson.h>           //6.15.2
#include "FS.h"
#include "SPIFFS.h"
#include <HTTPClient.h>

//ESP32 CAM AI Thinker Camera Pinout
#define PWDN_GPIO_NUM 32
#define RESET_GPIO_NUM -1
#define XCLK_GPIO_NUM 0
#define SIOD_GPIO_NUM 26
#define SIOC_GPIO_NUM 27

#define Y9_GPIO_NUM 35
#define Y8_GPIO_NUM 34
#define Y7_GPIO_NUM 39
#define Y6_GPIO_NUM 36
#define Y5_GPIO_NUM 21
#define Y4_GPIO_NUM 19
#define Y3_GPIO_NUM 18
#define Y2_GPIO_NUM 5
#define VSYNC_GPIO_NUM 25
#define HREF_GPIO_NUM 23
#define PCLK_GPIO_NUM 22

#define FLASH_LED_PIN 4

const char* ssid = "golitestore.id";
const char* password = "golitestore.id240722";

String BOT_TOKEN = "7275147013:AAFW6bDN9tnYk-eS587lisu51CDJMuu1zg8";
String CHAT_ID = "6571702337";

WiFiClientSecure clientTCP;
UniversalTelegramBot bot(BOT_TOKEN, clientTCP);

unsigned long botRequestsMillis;
bool sendPhoto, flashState = 0;

void setup() {
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
  Serial.begin(115200);
  cameraConfig();
  wifiConfig();
  if (!SPIFFS.begin(true)) {
    Serial.println("SPIFFS Mount Failed");
    return;
  }
  pinMode(FLASH_LED_PIN, OUTPUT);
  digitalWrite(FLASH_LED_PIN, flashState);
}

void loop() {
  if (sendPhoto) {
    Serial.println("\nPreparing photo");
    String response = sendPhotoTelegramSpiff();
    response.trim();
    if (response == "NOK") {
      sendPhoto = 1;
    } else {
      sendPhoto = 0;
    }
  }

  if (millis() > botRequestsMillis + 1000UL) {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    while (numNewMessages) {
      Serial.println("\nGot Response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    botRequestsMillis = millis();
  }
}