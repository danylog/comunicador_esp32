void pause_screen() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  if (unreadMessages == 0) {
    display.print("No hay mensajes nuevos, pulsa ");
    display.write(0xe1);
    if (b_send.click()) {
      state = SELECT_STATE;
    }
  } else {
    display.print(unreadMessages);
    display.print(" Mensajes no leidos, pulsa ");
    display.write(0xf1);
    if (b_paint.click()) {
      state = SHOW_PATTERN_STATE;
    }
  }
  display.display();
}