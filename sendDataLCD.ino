// Function to send data to the LCD display
void sendataLCD() {
  // Display light intensity (lux) with proper formatting based on its value
  if (lux < 10) {
    lcd.setCursor(3, 0);
    lcd.print("   "); // Clear previous value
    lcd.setCursor(6, 0);
    lcd.print(lux); // Display new value
  }
  if ((lux > 9) && (lux < 100)) {
    lcd.setCursor(3, 0);
    lcd.print("  "); // Clear previous value
    lcd.setCursor(5, 0);
    lcd.print(lux); // Display new value
  }
  if ((lux > 99) && (lux < 1000)) {
    lcd.setCursor(3, 0);
    lcd.print(" "); // Clear previous value
    lcd.setCursor(4, 0);
    lcd.print(lux); // Display new value
  }
  if ((lux > 999) && (lux < 10000)) {
    lcd.setCursor(3, 0);
    lcd.print(lux); // Display new value
  }

  // Display temperature
  lcd.setCursor(3, 1);
  lcd.print(gt_nhietdo);
  lcd.setCursor(7, 1);
  lcd.print(" ");

  // Display soil moisture with proper formatting based on its value
  if (gt_doamdat < 10) {
    lcd.setCursor(14, 0);
    lcd.print("  "); // Clear previous value
    lcd.setCursor(16, 0);
    lcd.print(gt_doamdat); // Display new value
  }
  if (gt_doamdat > 9 && gt_doamdat < 100) {
    lcd.setCursor(14, 0);
    lcd.print(" "); // Clear previous value
    lcd.setCursor(15, 0);
    lcd.print(gt_doamdat); // Display new value
  }
  if (gt_doamdat == 100) {
    lcd.setCursor(14, 0);
    lcd.print(gt_doamdat); // Display new value
  }

  // Display air humidity
  lcd.setCursor(15, 1);
  lcd.print(gt_doam);

  // Display pump status
  if (vl_bom == 1) {
    lcd.setCursor(6, 2);
    lcd.print("ON ");
  } else {
    lcd.setCursor(6, 2);
    lcd.print("OFF");
  }

  // Display light status
  if (vl_den == 1) {
    lcd.setCursor(17, 2);
    lcd.print("ON ");
  } else {
    lcd.setCursor(17, 2);
    lcd.print("OFF");
  }

  // Display mist status
  if (bt3_temp == 1) {
    lcd.setCursor(6, 3);
    lcd.print("ON ");
  } else {
    lcd.setCursor(6, 3);
    lcd.print("OFF");
  }

  // Display roof status
  if (mai == 1) {
    lcd.setCursor(17, 3);
    lcd.print("ON ");
  } else {
    lcd.setCursor(17, 3);
    lcd.print("OFF");
  }
}
