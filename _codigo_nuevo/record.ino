void record() {
  display.clearDisplay();  // Limpiar la pantalla antes de mostrar el mensaje
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Grabando audio");
  display.display();  // Mostrar el mensaje en la pantalla
  delay(1000);        // Breve retardo para que el mensaje sea visible

  while (b_record.holding()) {
    for (int i = 0; i < 8; i++) {
      for (int a = 0; a < 8; a++) {
        int red = random(2) * 200;
        matrix.drawPixel(i, a, matrix.Color(255, 0, 0));
      }
    }
    matrix.show();
    delay(200);
    b_record.tick();
  }
  if (b_record.releaseHold()) {
    matrix.fillScreen(0);
    matrix.show();
    display.clearDisplay();  // Limpiar la pantalla después de la animación
    display.display();
    state = PATTERN_STATE;
  }
}