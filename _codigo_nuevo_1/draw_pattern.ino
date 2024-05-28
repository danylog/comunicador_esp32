void draw_pattern() {


matrix.fillScreen(0);
  matrix.drawBitmap(0, 0, dp, 8, 8, matrix.Color(255, 0, 255));
  matrix.drawPixel(x, y, matrix.Color(255, 255, 255));
  matrix.show();
  if (b_up.click() || b_down.click() || b_right.click() || b_left.click()) {


    matrix.drawPixel(x, y, matrix.Color(painted * 255, 0, painted * 255));
    painted = 0;

    if (b_up.click()) {
      //Serial.println("up");
      y = (y + 1) % 8;
    } else if (b_down.click()) {
      //Serial.println("down");
      y = (y - 1 + 8) % 8;
    } else if (b_right.click()) {
      //Serial.println("right");
      x = (x + 1) % 8;
    } else if (b_left.click()) {
      //Serial.println("left");
      x = (x - 1 + 8) % 8;
    }

    //Serial.print(x);
    //Serial.println(y);


    matrix.show();
  }

  if (b_ok.click()) {
    painted = !painted;
    setBit(dp, 7 - x, y, !getBit(dp, 7 - x, y));
    matrix.fillScreen(0);
  }

  if (b_paint.click()) {

    matrix.fillScreen(0);
    matrix.show();
    if (comparePattern(patterns[0], dp)) {
      state = CORRECT_PATTERN_STATE;
      unreadMessages--;
    } else {
      state = WRONG_PATTERN_STATE;
      matrix.show();
    }      
  }
}
