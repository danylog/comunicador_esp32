void pattern_select() {
display.clearDisplay();
display.setCursor(0,0);
display.print("Encriptando mensaje");
display.display();
  for (int i = 0; i < 36; i++) {

    matrix.drawBitmap(0, 0, patterns[i % 6], 8, 8, matrix.Color(255, 0, 255));
    Serial.print(i);
    Serial.print(" ");
    matrix.show();
    delay(50);
    matrix.fillScreen(0);
  }
  pattern_selected = random(6);
  Serial.println(pattern_selected);

  matrix.drawBitmap(0, 0, patterns[pattern_selected], 8, 8, matrix.Color(255, 0, 255));
  matrix.show();
  
      display.clearDisplay();  // Limpiar la pantalla antes de mostrar el mensaje
  while (!(b_send.click())){

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("Pulsa ");
  display.write(0x1e);
  display.println(" para enviar");
  display.print("el mensaje");
  b_send.tick();
display.display();
  }  matrix.fillScreen(0);
matrix.show();
   display.clearDisplay();
  state = SENDING_STATE;
}