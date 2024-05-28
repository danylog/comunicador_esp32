void setBit(uint8_t* arr, int x, int y, bool value) {
  if (x < 0 || x > 7 || y < 0 || y > 7) {
    Serial.println("Invalid coordinates");
    return;
  }
  if (value) {
    arr[y] |= (1 << x);
  } else {
    arr[y] &= ~(1 << x);
  }
}
bool getBit(uint8_t* arr, int x, int y) {
  if (x < 0 || x > 7 || y < 0 || y > 7) {
    Serial.println("Invalid coordinates");
    return false;
  }
  return arr[y] & (1 << x);
}
bool comparePattern(const uint8_t pattern[8], const uint8_t* d) {
  for (int i = 0; i < 8; i++) {
    
    if (pgm_read_byte(&(pattern[i])) != d[i]) {
      
      return false;
    }
    
  }
  return true;
}
void correct_pattern(){
    display.clearDisplay();
display.setCursor(0,0);
display.println("Patron correcto!");
display.println("Reproduciendo mensaje...");

display.display();
delay(5000);
state=PAUSE_STATE;
}
void wrong_pattern(){

display.clearDisplay();
display.setCursor(0,0);
display.println("Patron incorrecto!");
display.println("OK para volver a     intentar");
display.println("");
display.write(0x1f);
display.print(" para volver al     inicio");
display.display();

if(b_ok.click())state=SHOW_PATTERN_STATE;
if(b_paint.click())state=PAUSE_STATE;
}