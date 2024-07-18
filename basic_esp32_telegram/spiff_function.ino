void captureAndSavePhoto() {
  // Remove Previous Picture
  camera_fb_t *fb = esp_camera_fb_get();
  esp_camera_fb_return(fb);

  // Get New Picture
  digitalWrite(FLASH_LED_PIN, 1);
  fb = esp_camera_fb_get();
  delay(150);
  digitalWrite(FLASH_LED_PIN, 0);

  if (!fb) {
    Serial.println("Camera capture failed");
    return;
  }

  // Save Picture To SPIFF
  File file = SPIFFS.open("/idrusproject.jpg", FILE_WRITE);
  if (!file) {
    Serial.println("Failed to open file for writing");
    esp_camera_fb_return(fb);
    return;
  }

  file.write(fb->buf, fb->len);
  file.close();
  esp_camera_fb_return(fb);

  Serial.println("Photo saved to SPIFFS");
}

String sendPhotoTelegramSpiff() {
  String serverPath = "https://api.telegram.org/bot" + String(BOT_TOKEN) + "/sendPhoto";
  captureAndSavePhoto();

  if (WiFi.status() == WL_CONNECTED) {
    WiFiClientSecure client;
    HTTPClient http;
    client.setInsecure();  // SSL Not Verified Yet

    // Start Server Connection
    http.begin(client, serverPath);

    // Open Picture From SPIFFS
    File file = SPIFFS.open("/idrusproject.jpg", "r");
    if (!file) {
      Serial.println("Failed to open file for reading");
      return "Failed to open file for reading";
    }

    // Cek ukuran file
    size_t fileSize = file.size();
    if (fileSize == 0) {
      Serial.println("File is empty");
      file.close();
      return "NOK";
    }

    // Siapkan body permintaan
    String boundary = "IdrusProject";
    String bodyHead = "--" + boundary + "\r\nContent-Disposition: form-data; name=\"chat_id\"\r\n\r\n" + String(CHAT_ID) + "\r\n--" + boundary + "\r\nContent-Disposition: form-data; name=\"photo\"; filename=\"photo.jpg\"\r\nContent-Type: image/jpeg\r\n\r\n";
    String bodyTail = "\r\n--" + boundary + "--\r\n";

    int bodyLength = bodyHead.length() + bodyTail.length() + file.size();
    uint8_t *body = (uint8_t *)malloc(bodyLength);

    if (body == NULL) {
      Serial.println("Failed to allocate memory for body");
      file.close();
      http.end();
      return "Failed to allocate memory for body";
    }

    // Copy head to body
    memcpy(body, bodyHead.c_str(), bodyHead.length());

    // Copy file content to body
    file.readBytes((char *)body + bodyHead.length(), file.size());

    // Copy tail to body
    memcpy(body + bodyHead.length() + file.size(), bodyTail.c_str(), bodyTail.length());

    http.addHeader("Content-Type", "multipart/form-data; boundary=" + boundary);

    int httpResponseCode = http.POST(body, bodyLength);
    Serial.print("HTTP Response code: ");
    if (httpResponseCode > 0) {
      String payload = http.getString();
      Serial.println(httpResponseCode);
      Serial.println("Response payload: " + payload);

      free(body);
      http.end();
      file.close();
      return payload;
    }else {
      Serial.println(httpResponseCode);
      return "NOK";
    }
  } else {
    Serial.println("WiFi Disconnected");
    return "WiFi Disconnected";
  }
}