void handleNewMessages(int numNewMessages) {
  Serial.print("Handle New Messages: ");
  Serial.println(numNewMessages);

  for (int i = 0; i < numNewMessages; i++) {
    String chat_id = String(bot.messages[i].chat_id);
    if (chat_id != chat_id) {
      bot.sendMessage(chat_id, "Unauthorized user", "");
      continue;
    }

    // Print the received message
    String text = bot.messages[i].text;
    Serial.println(text);

    String from_name = bot.messages[i].from_name;
    if (text == "/start") {
      String welcome = "Welcome , " + from_name + "\n";
      welcome += "Berikut adalah perintah yang dapat digunakan : \n";
      welcome += "/photo : Mengambil foto baru\n";
      welcome += "/flash : Menyalakan dan mematikan lampu flash \n";
      bot.sendMessage(CHAT_ID, welcome, "");
    } else if (text == "/photo") {
      Serial.println("New photo request");
      sendPhoto = 1;
    } else if (text == "/flash") {
      Serial.println("Change flash LED state");
      flashState = !flashState;
      digitalWrite(FLASH_LED_PIN, flashState);
    }else if (text == "/remove"){
      deleteAllFilesInSPIFFS();
    }
  }
}