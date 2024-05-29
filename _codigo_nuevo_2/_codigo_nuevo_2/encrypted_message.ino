void encrypted_message(){
  display.setCursor(0,0);
  display.clearDisplay();
  display.print("Mensaje encriptado,  pulsa OK para        desencripar");
  display.display();
  if(b_ok.click())state=SHOW_PATTERN_STATE;
}