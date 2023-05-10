void printValoresBME(){
  char t = 'T';
  char u = 'U';
  char m = 'M'; //pressão

  unsigned long pressao = bme.readPressure() / 100.0F;
  
  espSerial.println(String(t) + bme.readTemperature());
  Serial.print(" Temperatura = ");
  Serial.print(bme.readTemperature());
  Serial.println(" °C");
  espSerial.println(String(u) + bme.readHumidity());
  Serial.print(" Umidade = ");
  Serial.print(bme.readHumidity());
  Serial.println(" %");
  espSerial.println(String(m) + pressao);
  Serial.print(" Pressao = ");
  Serial.print(pressao);
  Serial.println(" hPa");
  Serial.println(" ");
  
}
