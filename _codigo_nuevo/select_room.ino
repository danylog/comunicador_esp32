void select_room() {
  int pos = encoder.getCount() / 2;

  if (pos == po and flag == 0) {
    display.setCursor(0, 0);
    display.clearDisplay();
    display.print("Gira el encoder para seleccionar          habitacion");
    display.display();

  } else {
    flag = 1;
    if (pos <= -1) {
      encoder.setCount(42);
      pos = 21;
    }
    if (pos>= 22) {
      encoder.setCount(0);
      pos = 0;
    }


    display.clearDisplay();
    int16_t x1, y1;
    uint16_t w, h;
    display.setTextSize(4);
    display.getTextBounds(frases[pos], 0, 0, &x1, &y1, &w, &h);
    int16_t x = (128 - w) / 2;
    int16_t y = (64 - h) / 2;
    display.setCursor(x, y);
    display.println(frases[pos]);
    display.display();

    if (b_ok.click()) state = PRE_RECORD_STATE;
  }
}