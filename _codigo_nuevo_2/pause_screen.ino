void pause_screen() {

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  if (unreadMessages == 0) {
    display.print("No hay mensajes      nuevos, pulsa ");
    display.write(0x1e);
    if (b_send.click()) {
      po = encoder.getCount() / 2;
      flag = 0;
      state = SELECT_STATE;
    }
  } else {
    display.print(unreadMessages);
    display.print(" Mensaje nuevo de lahabitacion 17,       pulsa ");
    display.write(0x1f);
    if (b_paint.click()) {
      state = ENCRYPTED_MESSAGE_STATE;
    }
  }
  display.display();
}