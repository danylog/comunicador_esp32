void pattern_select(){
    for (int a; a < 10; a++) {
    for (int i; i < 6; i++) {
      matrix.drawBitmap(0, 0, patterns[i], 8, 8, matrix.Color(255, 0, 255));
      matrix.show();
      delay(100);
    }
  }
  byte pattern_selected = random(6);
  matrix.drawBitmap(0, 0, patterns[pattern_selected], 8, 8, matrix.Color(255, 0, 255));
  matrix.show();
  delay(2000);
}