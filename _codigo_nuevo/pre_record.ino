void pre_record() {
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println("Pulsa el boton rojo para grabar audio...");
    display.display();
    // Aquí pondrías tu función de grabar pantalla
    delay(1000);          // Simulación de grabación, sustitúyelo por tu lógica de grabación real
    state = SELECT_STATE;  // Vuelve al estado inicial después de grabar
  if(b_record.press()) state=RECORD_STATE;
}