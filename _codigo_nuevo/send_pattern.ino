void send_data() {
  display.setCursor(0, 0);
  display.print("Enviando...");
  display.display();
  while (1) {
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&pattern_selected, sizeof(pattern_selected));
    if (result == ESP_OK) {
      Serial.println("Sent with success");
      display.print("Enviado");

      break;
    } else {
      Serial.println("Error sending the data");
      display.print("Error al enviar");
    }
  }
  display.display();
  for (int i = 0; i < 15; i++) {
    matrix.fillScreen(0);
    matrix.drawBitmap(0, 0, gif_2[i], 8, 8, matrix.Color(255, 0, 255));
    matrix.show();
    delay(200);
  }
  matrix.fillScreen(0);

  matrix.show();
  state = PAUSE_STATE;
  delay(1000);
}