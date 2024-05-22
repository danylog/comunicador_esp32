#include <Adafruit_NeoPixel.h>

#define PIN 9               // Pin al que está conectada la tira NeoPixel
#define NUMPIXELS 64        // Número total de LEDs en la matriz (8x8)
#define BOTON_R 2           // Pin al que está conectado el botón derecha
#define BOTON_U 4           // Pin al que está conectado el botón arriba
#define BOTON_D 7           // Pin al que está conectado el botón abajo
#define BOTON_L 8           // Pin al que está conectado el botón izquierdo
#define BOTON_COLOR 12      // Pin al que está conectado el botón para cambiar el color

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int led_index = 0;                // Índice de la LED encendida actualmente
int leds_presionados[NUMPIXELS];  // Array para almacenar los LEDs presionados
int num_leds_presionados = 0;     // Número de LEDs presionados

void setup() {
  Serial.begin(9600);
  pixels.begin();
  pixels.clear();  // Apagar todos los LEDs al inicio
  pixels.show();   // Mostrar el apagado
  pixels.setBrightness(50);
  pinMode(BOTON_R, INPUT_PULLUP);
  pinMode(BOTON_U, INPUT_PULLUP);
  pinMode(BOTON_D, INPUT_PULLUP);
  pinMode(BOTON_L, INPUT_PULLUP);
  pinMode(BOTON_COLOR, INPUT_PULLUP);
}

void loop() {
  // Cambiar color del LED seleccionado
  if (digitalRead(BOTON_COLOR) == LOW) {
    cambiarColor();
  }

  // Mover el LED seleccionado
  if (digitalRead(BOTON_R) == LOW) moverDerecha();
  if (digitalRead(BOTON_U) == LOW) moverArriba();
  if (digitalRead(BOTON_D) == LOW) moverAbajo();
  if (digitalRead(BOTON_L) == LOW) moverIzquierda();

  // Encender los LEDs presionados en color rojo
  for (int i = 0; i < num_leds_presionados; i++) {
    pixels.setPixelColor(leds_presionados[i], pixels.Color(255, 30, 0));  // Color rojo
  }

  // Mantener el LED seleccionado en blanco
  pixels.setPixelColor(led_index, pixels.Color(50, 50, 50));  // Color blanco
  pixels.show();

  // Imprimir los números guardados en el array
  imprimirArray();
}

void cambiarColor() {
  leds_presionados[num_leds_presionados] = led_index;  // Guardar el LED presionado
  num_leds_presionados++;
  if (digitalRead(BOTON_COLOR) == LOW) {}  // Esperar a que se suelte el botón
  delay(200);  // Evitar rebotes
}

void moverDerecha() {
  led_index++;
  if (led_index >= NUMPIXELS) led_index = 0;  // Volver al principio si alcanzamos el final
  delay(200);  // Evitar rebotes
  pixels.clear();
}

void moverArriba() {
  led_index += 8;
  if (led_index >= NUMPIXELS) led_index = 0;  // Volver al principio si alcanzamos el final
  delay(200);  // Evitar rebotes
  pixels.clear();
}

void moverAbajo() {
  led_index -= 8;
  if (led_index < 0) led_index = NUMPIXELS - 1;  // Volver al final si vamos más allá del principio
  delay(200);  // Evitar rebotes
  pixels.clear();
}

void moverIzquierda() {
  led_index--;
  if (led_index < 0) led_index = NUMPIXELS - 1;  // Volver al final si vamos más allá del principio
  delay(200);  // Evitar rebotes
  pixels.clear();
}

void imprimirArray() {
  Serial.print("LEDs presionados: ");
  for (int i = 0; i < num_leds_presionados; i++) {
    Serial.print(leds_presionados[i]);
    if (i < num_leds_presionados - 1) {
      Serial.print(", ");
    }
  }
  Serial.println();
}

