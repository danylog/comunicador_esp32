void pre_record() {
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println("Manten pulsado el    boton rojo para      grabar audio");
    display.display();
    // Aquí pondrías tu función de grabar pantalla

    
  if(b_record.holding()) state=RECORD_STATE;
}