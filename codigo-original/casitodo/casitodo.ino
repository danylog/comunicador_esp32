#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSH1106.h>
#include <Adafruit_NeoPixel.h>
#include <Adafuit_NeoMatrix.h>

#define MAX_LED_PRESSES 10         // Número máximo de LEDs que se pueden encender al presionar BOTON_COLOR
int led_presses[MAX_LED_PRESSES];  // Array para almacenar las posiciones de las LEDs donde se ha presionado el botón
int num_led_presses = 0;           // Número actual de LEDs presionados


#define RESET_STATE 0
#define SCREEN_STATE 1
#define ANIM_STATE 2
#define GAME_STATE 3

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

#define ROTARY_PIN1 A2  // Pin de señal A del encoder rotativo
#define ROTARY_PIN2 A3  // Pin de señal B del encoder rotativo
#define ON_OFF_PIN 1    // Pin para activar/desactivar

Adafruit_SSH1106 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800);

int led_index = 0;  // Reiniciar el índice de la LED
int state = RESET_STATE;
int fraseIndex = 0;

bool active = false;
int lastState = LOW;


const int numFrases = 10;
const char *frases[numFrases] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10" };

void setup() {
  Serial.begin(9600);
  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  display.clearDisplay();
  display.display();
  display.setTextSize(4);
  display.setTextColor(SSD1306_WHITE);
  pinMode(ON_OFF_PIN, INPUT_PULLUP);
  pinMode(SELECTION_PIN, INPUT_PULLUP);
  pinMode(BOTON_ANIMACION, INPUT_PULLUP);  // Configura el pin del botón de animación como entrada con pull-up
  pinMode(BOTON_R, INPUT_PULLUP);
  pinMode(BOTON_U, INPUT_PULLUP);
  pinMode(BOTON_D, INPUT_PULLUP);
  pinMode(BOTON_L, INPUT_PULLUP);
  pinMode(BOTON_COLOR, INPUT_PULLUP);
  pixels.begin();
  pixels.clear();
  pixels.setPixelColor(led_index, pixels.Color(0, 0, 0));  // Encender la LED inicialmente
  pixels.show();
  pixels.setBrightness(20);
}

void loop() {
  int buttonState = digitalRead(ON_OFF_PIN);

  if (buttonState == LOW) {
    active = !active;
    delay(250);
    state = RESET_STATE;
  }

  if (active) {
    switch (state) {
      case RESET_STATE:
        Pantalla_Numeros();
        break;
      case SCREEN_STATE:
        Pantalla_Grabar();
        break;
      case ANIM_STATE:
        animacion();  // Llama a la función de animación cuando está en el estado de animación
        break;
      case GAME_STATE:
        Juego();  // Ejecutar juego en el estado de juego
        break;
    }
  }
 

  // Cambia al estado de grabación cuando se pulsa el botón del pin 3
  if (digitalRead(SELECTION_PIN) == LOW) {
    state = SCREEN_STATE;
  }

  // Cambia al estado de animación cuando se pulsa el botón del pin 13
  if (digitalRead(BOTON_ANIMACION) == LOW) {
    state = ANIM_STATE;
  }
}

void Pantalla_Numeros() {
  int state = digitalRead(ROTARY_PIN1);
  if (state != lastState) {
    if (digitalRead(ROTARY_PIN2) != state) {
      fraseIndex = (fraseIndex + 1) % numFrases;
    } else {
      fraseIndex = (fraseIndex - 1 + numFrases) % numFrases;
    }
    display.clearDisplay();
    int16_t x1, y1;
    uint16_t w, h;
    display.getTextBounds(frases[fraseIndex], 0, 0, &x1, &y1, &w, &h);
    int16_t x = (SCREEN_WIDTH - w) / 2;
    int16_t y = (SCREEN_HEIGHT - h) / 2;
    display.setCursor(x, y);
    display.println(frases[fraseIndex]);
    display.display();
    delay(100);
  }

  lastState = state;  // Actualiza el estado anterior
}

void Pantalla_Grabar() {
  if (digitalRead(SELECTION_PIN) == LOW) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println("Pulsa el boton rojo para grabar audio...");
    display.display();
    // Aquí pondrías tu función de grabar pantalla
    delay(1000);          // Simulación de grabación, sustitúyelo por tu lógica de grabación real
    state = RESET_STATE;  // Vuelve al estado inicial después de grabar
  }
}


void animacion() {
  display.clearDisplay();  // Limpiar la pantalla antes de mostrar el mensaje
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Grabando audio");
  display.display();  // Mostrar el mensaje en la pantalla
  delay(1000);        // Breve retardo para que el mensaje sea visible

  while (digitalRead(BOTON_ANIMACION) == LOW) {
    for (int i = 0; i < NUMPIXELS; i++) {
      int red = random(2) * 200;
      pixels.setPixelColor(i, pixels.Color(red, 0, 0));
    }
    pixels.show();
    delay(200);
  }

  // No se llama a pixels.clear() aquí
  pixels.clear();
  pixels.show();
  display.clearDisplay();  // Limpiar la pantalla después de la animación
  display.display();       // Actualizar la pantalla para eliminar el mensaje

  // Cambiar al estado de juego después de la animación
  state = GAME_STATE;
}

void Juego() {
  if (digitalRead(BOTON_COLOR) == LOW) {
    if (num_led_presses < MAX_LED_PRESSES) {
      // Guarda la posición de la LED actual en el array
      led_presses[num_led_presses++] = led_index;
      // Enciende la LED actual
      pixels.setPixelColor(led_index, pixels.Color(255, 0, 0));  // Rojo
      pixels.show();
      delay(200);  // Breve retardo para evitar rebotes

    }
  }
  pixels.setPixelColor(led_index, pixels.Color(50, 50, 50));  // Encender la LED 0 en color blanco
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
}
