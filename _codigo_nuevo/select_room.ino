void select_room() {
  int stat = digitalRead(ROTARY_PIN1);
  if (stat != lastState) {
    if (digitalRead(ROTARY_PIN2) != stat) {
      fraseIndex = (fraseIndex + 1) % numFrases;
    } else {
      fraseIndex = (fraseIndex - 1 + numFrases) % numFrases;
    }
    display.clearDisplay();
    int16_t x1, y1;
    uint16_t w, h;
    display.getTextBounds(frases[fraseIndex], 0, 0, &x1, &y1, &w, &h);
    int16_t x = (SCREEN_WIDTH - w) / 2;
    int16_t y = (SCREEN_HEIGHT - h) / 2;
    display.setCursor(x, y);
    display.println(frases[fraseIndex]);
    display.display();
    delay(100);
  }

  lastState = state;  // Actualiza el estado anterior
  if(b_ok.isClick()) state = PRE_RECORD_STATE;
}