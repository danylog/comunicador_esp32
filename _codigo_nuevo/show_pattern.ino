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
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Dibuja el patron");
  display.display();
}