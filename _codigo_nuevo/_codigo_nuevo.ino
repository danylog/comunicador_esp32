#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_NeoMatrix.h>
#include <GyverButton.h>

GButton b_up(4);
GButton b_down(7);
GButton b_left(8);
GButton b_right(2);
GButton b_ok(3);
GButton b_record(13);
GButton b_power(5);
GButton b_paint(12);

#define MAX_LED_PRESSES 10         // Número máximo de LEDs que se pueden encender al presionar BOTON_COLOR
int led_presses[MAX_LED_PRESSES];  // Array para almacenar las posiciones de las LEDs donde se ha presionado el botón
int num_led_presses = 0;           // Número actual de LEDs presionados


#define SELECT_STATE 0
#define PRE_RECORD_STATE 1
#define RECORD_STATE 2
#define PATTERN_STATE 3
#define PAUSE_STATE 4

#define SELECTION_PIN 3
#define PIN 9
#define NUMPIXELS 64        // Número total de LEDs en la matriz (8x8)
#define BOTON_ANIMACION 13  // Pin al que está conectado el botón para encender
#define BOTON_COLOR 12      // Pin al que está conectado el botón para cambiar el color de la LED


#define BOTON_R 2  // Pin al que está conectado el botón derecha
#define BOTON_U 4  // Pin al que está conectado el botón arriba
#define BOTON_D 7  // Pin al que está conectado el botón abajo
#define BOTON_L 8  // Pin al que está conectado el botón izquierdo

#define SCREEN_WIDTH 128     // Ancho de la pantalla OLED en píxeles
#define SCREEN_HEIGHT 64     // Alto de la pantalla OLED en píxeles
#define OLED_RESET -1        // Pin de reinicio (reset) no conectado
#define SCREEN_ADDRESS 0x3C  // Dirección I2C de la pantalla OLED (puede variar)

#define ROTARY_PIN1 14  // Pin de señal A del encoder rotativo
#define ROTARY_PIN2 15  // Pin de señal B del encoder rotativo
#define ON_OFF_PIN 5    // Pin para activar/desactivar

Adafruit_SH1106 display(21,23);

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800);

int led_index = 0;  // Reiniciar el índice de la LED
int state = SELECT_STATE;
int fraseIndex = 0;

bool active = false;
int lastState = LOW;


const int numFrases = 10;
const char *frases[numFrases] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10" };

void setup() {
  Serial.begin(9600);
  Wire.begin();
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();
  display.setTextSize(4);
  display.setTextColor(WHITE);
  pinMode(ON_OFF_PIN, INPUT_PULLUP);
  pinMode(SELECTION_PIN, INPUT_PULLUP);
  pinMode(BOTON_ANIMACION, INPUT_PULLUP);  // Configura el pin del botón de animación como entrada con pull-up
  pinMode(BOTON_R, INPUT_PULLUP);
  pinMode(BOTON_U, INPUT_PULLUP);
  pinMode(BOTON_D, INPUT_PULLUP);
  pinMode(BOTON_L, INPUT_PULLUP);
  pinMode(BOTON_COLOR, INPUT_PULLUP);

  matrix.begin();  
  matrix.fillScreen(0);
  matrix.setBrightness(20);
  matrix.drawPixel(0,0, matrix.Color(255, 255, 255));  // Encender la LED inicialmente
  matrix.show();
}

void loop() {
ticks();

  if (b_power.isClick()) {
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
