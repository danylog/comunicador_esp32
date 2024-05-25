void select_room() {
  if (enc.right()) {
    fraseIndex = (fraseIndex + 1) % numFrases;
  } else if (enc.left()) {
    fraseIndex = (fraseIndex - 1 + numFrases) % numFrases;
  }
  display.clearDisplay();
  int16_t x1, y1;
  uint16_t w, h;
  display.getTextBounds(frases[fraseIndex], 0, 0, &x1, &y1, &w, &h);
  int16_t x = (128 - w) / 2;
  int16_t y = (64 - h) / 2;
  display.setCursor(x, y);
  display.println(frases[fraseIndex]);
  display.display();

if (b_ok.click()) state = PRE_RECORD_STATE;
}