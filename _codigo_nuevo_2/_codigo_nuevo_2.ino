/*
Copyright © 2024, Danylo Galytskyy
ALL RIGHTS RESERVED
*/

#include <esp_now.h>
#include <WiFi.h>
#include <esp_task_wdt.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>
#include <Adafruit_NeoMatrix.h>
#include <EncButton.h>
#include <ESP32Encoder.h>
//D4:8A:FC:A2:E9:AC
//A8:42:E3:AB:26:C4
//uint8_t broadcastAddress[] = { 0xD4, 0x8A, 0xFC, 0xA2, 0xE9, 0xAC };
uint8_t broadcastAddress[] = { 0xA8, 0x42, 0xE3, 0xAB, 0x26, 0xC4 };
int flag = 0;
Button b_up(4);
Button b_down(0);
Button b_left(2);
Button b_right(15);
Button b_ok(32);
Button b_record(14);
Button b_power(25);
Button b_paint(26);
Button b_send(27);

ESP32Encoder encoder;

uint8_t dp[8] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
};

long newPos, oldPos;

#define SELECT_STATE 0
#define SHOW_PATTERN_STATE 5
#define PRE_RECORD_STATE 1
#define RECORD_STATE 2
#define PATTERN_STATE 3
#define PAUSE_STATE 4
#define SENDING_STATE 6
#define DRAW_PATTERN_STATE 7
#define CORRECT_PATTERN_STATE 8
#define WRONG_PATTERN_STATE 9
#define ENCRYPTED_MESSAGE_STATE 10

Adafruit_SH1106 display(21, 22);

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, 23,
                                               NEO_MATRIX_TOP + NEO_MATRIX_RIGHT + NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
                                               NEO_GRB + NEO_KHZ800);

int state = PAUSE_STATE;
int fraseIndex = 0;

int x, y;
int po;
bool painted;
bool active = false;
byte unreadMessages = 0;
byte incomingReadings = 0;
byte incomingMessage;

byte pattern_selected;

const int numFrases = 22;
const char *frases[numFrases] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22"};

String success;
esp_now_peer_info_t peerInfo;

static const uint8_t PROGMEM gif_1[][8] = {
{
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
},{
  B10000001,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B10000001
},{
  B10000001,
  B01000010,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B01000010,
  B10000001
},{
  B00000000,
  B01000010,
  B00100100,
  B00000000,
  B00000000,
  B00100100,
  B01000010,
  B00000000
},{
  B00000000,
  B01000010,
  B00100100,
  B00000000,
  B00000000,
  B00100100,
  B01000010,
  B00000000
},{
  B00000000,
  B00000000,
  B00100100,
  B00011000,
  B00011000,
  B00100100,
  B00000000,
  B00000000
},{
  B00000000,
  B00000000,
  B00000000,
  B00011000,
  B00011000,
  B00000000,
  B00000000,
  B00000000
},{
  B00000000,
  B00000000,
  B00100100,
  B00011000,
  B00011000,
  B00100100,
  B00000000,
  B00000000
},{
  B00000000,
  B01000010,
  B00100100,
  B00000000,
  B00000000,
  B00100100,
  B01000010,
  B00000000
},{
  B10000001,
  B01000010,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B01000010,
  B10000001
},{
  B10000001,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B10000001
}};

static const uint8_t PROGMEM gif_2[][8] = {
{
  B01111110,
  B11111111,
  B11111111,
  B11111111,
  B11111111,
  B11111111,
  B11111111,
  B01111110
},{
  B00111100,
  B01111110,
  B11111111,
  B11111111,
  B11111111,
  B11111111,
  B01111110,
  B00111100
},{
  B00011000,
  B00111100,
  B01111110,
  B11111111,
  B11111111,
  B01111110,
  B00111100,
  B00011000
},{
  B00000000,
  B00111100,
  B01111110,
  B01111110,
  B01111110,
  B01111110,
  B00111100,
  B00000000
},{
  B00000000,
  B00011000,
  B00111100,
  B01111110,
  B01111110,
  B00111100,
  B00011000,
  B00000000
},{
  B00000000,
  B00000000,
  B00111100,
  B00111100,
  B00111100,
  B00111100,
  B00000000,
  B00000000
},{
  B00000000,
  B00000000,
  B00011000,
  B00111100,
  B00111100,
  B00011000,
  B00000000,
  B00000000
},{
  B00000000,
  B00000000,
  B00000000,
  B00011000,
  B00011000,
  B00000000,
  B00000000,
  B00000000
},{
  B00000000,
  B00000000,
  B00000000,
  B00010000,
  B00011000,
  B00000000,
  B00000000,
  B00000000
},{
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00011000,
  B00000000,
  B00000000,
  B00000000
},{
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00001100,
  B00000000,
  B00000000,
  B00000000
},{
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000110,
  B00000000,
  B00000000,
  B00000000
},{
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000011,
  B00000000,
  B00000000,
  B00000000
},{
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000001,
  B00000000,
  B00000000,
  B00000000
},{
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
}};


void setup() {

  encoder.attachHalfQuad(18, 19);
  encoder.setCount(0);

  WiFi.mode(WIFI_STA);
  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);

  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  // Add peer
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
  // Register for a callback function that will be called when data is received
  esp_now_register_recv_cb(OnDataRecv);

pinMode(5, OUTPUT);

  Serial.begin(9600);
  esp_task_wdt_init(20, true);
  Wire.begin();
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  display.setTextSize(4);
  display.setTextColor(WHITE);
  //display.print("helo");
  display.display();

  matrix.begin();
  matrix.fillScreen(0);
  matrix.setBrightness(20);
  //matrix.drawPixel(0, 0, matrix.Color(255, 0, 255));  // Encender la LED inicialmente
  matrix.show();
}

void loop() {
  esp_task_wdt_reset();
  ticks();

  

  if (b_power.click()) {
    active = !active;
    display.clearDisplay();
    display.display();
    state = PAUSE_STATE;
      for (int i = 0; i < 11; i++) {
        matrix.fillScreen(0);
        matrix.drawBitmap(0, 0, gif_1[i], 8, 8, matrix.Color(255, 0, 255));
        matrix.show();
        delay(50);
      }
      matrix.fillScreen(0);
  matrix.show();
  }

  if (active) {
    switch (state) {
      case PAUSE_STATE:
        pause_screen();
        break;
      case SHOW_PATTERN_STATE:
        show_pattern();
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

      case SENDING_STATE:
        send_data();  // Ejecutar juego en el estado de juego
        break;
      case DRAW_PATTERN_STATE:
        draw_pattern();  // Ejecutar juego en el estado de juego
        break;
     case CORRECT_PATTERN_STATE:
        correct_pattern();  // Ejecutar juego en el estado de juego
        break;
      case WRONG_PATTERN_STATE:
        wrong_pattern();  // Ejecutar juego en el estado de juego
        break;
    
          case ENCRYPTED_MESSAGE_STATE:
        encrypted_message();  // Ejecutar juego en el estado de juego
        break;
    }
  }else{
    matrix.fillScreen(0);
    matrix.show();
  }
}
//Serial.println(state);








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
