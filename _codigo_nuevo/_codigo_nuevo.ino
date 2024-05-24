/*
Copyright © 2024, Danylo Galytskyy
ALL RIGHTS RESERVED
*/
#include <esp_task_wdt.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>
#include <Adafruit_NeoMatrix.h>
#include <EncButton.h>

Button b_up(34);
Button b_down(35);
Button b_left(36);
Button b_right(39);
Button b_ok(32);
Button b_record(33);
Button b_power(25);
Button b_paint(26);

EncButton enc(5, 18, 19);

#define SELECT_STATE 0
#define PRE_RECORD_STATE 1
#define RECORD_STATE 2
#define PATTERN_STATE 3
#define PAUSE_STATE 4

Adafruit_SH1106 display(21,22);

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, 23,
  NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800);

int state = PAUSE_STATE;
int fraseIndex = 0;

bool active = false;

const int numFrases = 10;
const char *frases[numFrases] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10" };

void setup() {
  Serial.begin(9600);
   esp_task_wdt_init(20, true);
  Wire.begin();
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  
  display.setTextSize(4);
  display.setTextColor(WHITE);
  display.print("helo");
display.display();

  matrix.begin();  
  matrix.fillScreen(0);
  matrix.setBrightness(20);
  matrix.drawPixel(0,0, matrix.Color(255, 0, 255));  // Encender la LED inicialmente
  matrix.show();
}

void loop() {
  esp_task_wdt_reset();
ticks();

  if (b_power.click()) {
    active = !active;
    delay(250);
    state = PAUSE_STATE;

  }

  if (active) {
    switch (state) {
      case PAUSE_STATE:
        pause_screen();
        break;
      case SELECT_STATE:
        select_room();
        break;
      case PRE_RECORD_STATE:
        pre_record();
        break;
      case RECORD_STATE:
        record();  // Llama a la función de animación cuando está en el estado de animación
        break;
      case PATTERN_STATE:
        pattern_select();  // Ejecutar juego en el estado de juego
        break;
    }
  }

}







/*
void Juego() {
  if (digitalRead(BOTON_COLOR) == LOW) {
    if (num_led_presses < MAX_LED_PRESSES) {
      led_presses[num_led_presses++] = led_index;
      // Enciende la LED actual
      pixels.drawPixel(led_index, pixels.Color(255, 0, 0));  // Rojo
      pixels.show();
      delay(200);  // Breve retardo para evitar rebotes

    }
  }
  pixels.drawPixel(led_index, pixels.Color(50, 50, 50));  // Encender la LED 0 en color blanco
  pixels.show();

  if (digitalRead(BOTON_R) == LOW) moverDerecha();
  if (digitalRead(BOTON_U) == LOW) moverArriba();
  if (digitalRead(BOTON_D) == LOW) moverAbajo();
  if (digitalRead(BOTON_L) == LOW) moverIzquierda();
}

void moverDerecha() {
  led_index++;
  if (led_index >= NUMPIXELS) led_index = 0;  // Volver al principio si alcanzamos el final
  delay(200);                                 // Evitar rebotes
  pixels.clear();
}

void moverArriba() {
  led_index += 8;
  if (led_index >= NUMPIXELS) led_index = 0;  // Volver al principio si alcanzamos el final
  delay(200);                                 // Evitar rebotes
  pixels.clear();
}

void moverAbajo() {
  led_index -= 8;
  if (led_index < 0) led_index = NUMPIXELS - 1;  // Volver al final si vamos más allá del principio
  delay(200);                                    // Evitar rebotes
  pixels.clear();
}

void moverIzquierda() {
  led_index--;
  if (led_index < 0) led_index = NUMPIXELS - 1;  // Volver al final si vamos más allá del principio
  delay(200);                                    // Evitar rebotes
  pixels.clear();
}*/
