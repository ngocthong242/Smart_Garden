// Function to read sensor data
void docCamBien() {
  lux = lightMeter.readLightLevel(); // Read light level from BH1750 sensor
  if (lux >= 10000) {
    lux = 9999; // Cap the light level to 9999 if it exceeds 10000
  }
  gt_mua = digitalRead(mua); // Read rain sensor
  gt_doam = dht.readHumidity(); // Read humidity from DHT11 sensor
  gt_nhietdo = dht.readTemperature(); // Read temperature from DHT11 sensor

  // Read digital inputs
  gt_in1 = digitalRead(in1);
  gt_in2 = digitalRead(in2);
  gt_in3 = digitalRead(in3);
  gt_in4 = digitalRead(in4);
  gt_in5 = digitalRead(in5);
  gt_in6 = digitalRead(in6);
  gt_in7 = digitalRead(in7);

  // Serial output for debugging (commented out)
  // Serial.print(F("Humidity: "));
  // Serial.print(gt_doam);
  // Serial.println("\n");
  // Serial.print(F("%  Temperature: "));
  Serial.println(gt_mua); // Print rain sensor value to serial monitor
  // Serial.print(F("°C "));
  // Serial.println("\n");
  // Serial.print("Light: ");
  // Serial.print(lux);
  // Serial.println(" lx");
  // Serial.println("\n");
  // Serial.print(gt_in1);
  // Serial.print(gt_in2);
  // Serial.print(gt_in3);
  // Serial.print(gt_in4);
  // Serial.print(gt_in5);
  // Serial.print(gt_in6);
  // Serial.println(gt_in7);

  // Read soil moisture value and map it to a percentage
  value = analogRead(doamdat);
  gt_doamdat = map(value, 0, 4095, 200, 0);
  //Serial.println(percent);

  // Send sensor data to Blynk virtual pins
  Blynk.virtualWrite(V1, gt_nhietdo);
  Blynk.virtualWrite(V2, gt_doam);
  Blynk.virtualWrite(V3, gt_doamdat);
  Blynk.virtualWrite(V4, lux);
}
