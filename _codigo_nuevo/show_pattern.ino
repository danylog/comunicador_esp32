void show_pattern() {
  digitalWrite(5, 0);
  matrix.fillScreen(0);
matrix.drawBitmap(0, 0, patterns[incomingMessage], 8, 8, matrix.Color(255, 0, 255));
matrix.show();
for(int i=5; i>0;i--){
  display.clearDisplay();
display.setCursor(0,0);
display.setTextSize(1);
display.print("Recuerda el patron");
display.setCursor(54, 32);
display.setTextSize(4);
display.print(i);
display.display();
delay(1000);
}display.setTextSize(1);
matrix.fillScreen(0);
matrix.show();
state=DRAW_PATTERN_STATE;
    for(int a=0; a<8; a++){
    for (int i = 0; i < 8;i++) {
        setBit(dp, a, i, 0);
       }
    }
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Dibuja el patron.    Pulsa ");
      display.write(0x1f);
      display.print(" para validar");
  display.display();
}