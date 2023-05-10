void voc(){
  float analogValue = 0.0;
  float gain = 1.08;
  float a_reference = 2.56;
  char v = 'V';

  for(byte i = 0; i < 100; i++){
    analogValue += analogRead(A0);
    delay(1);
  }
  analogValue = ((analogValue / 100.0) * a_reference) / (1024.0 * gain);

  Serial.print(" VOC = "); Serial.println(analogValue);
  espSerial.println(String(v) + analogValue);

  
}
