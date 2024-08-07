// Function to enable automatic mode
void autoMode() {
  if (auto_mode == 1) {
    auto_light(); // Call the function to control light automatically
    auto_soil();  // Call the function to control soil moisture automatically
    auto_roof();  // Call the function to control roof automatically
  }
}

// Function to control light automatically based on light intensity
void auto_light() {
  if (lux < get_light) { // If current light intensity is less than the threshold
    if (bt3_state == HIGH) { // If the light is currently off
      digitalWrite(den, HIGH); // Turn on the light
      Blynk.virtualWrite(V7, 1); // Update Blynk virtual pin
      bt3_state = LOW; // Update the button state
      delay(200); // Delay to debounce the button
    }
  } else {
    bt3_state = HIGH; // Reset button state
  }
  if (lux > get_light + 100) { // If current light intensity is more than the threshold + 100
    if (bt3_state == HIGH) { // If the light is currently on
      digitalWrite(den, LOW); // Turn off the light
      Blynk.virtualWrite(V7, 0); // Update Blynk virtual pin
      bt3_state = LOW; // Update the button state
      delay(200); // Delay to debounce the button
    }
  } else {
    bt3_state = HIGH; // Reset button state
  }
}

// Function to control soil moisture automatically based on soil moisture level
void auto_soil() {
  if (gt_doamdat < get_soil) { // If current soil moisture is less than the threshold
    if (bt2_state == HIGH) { // If the pump is currently off
      digitalWrite(bom, HIGH); // Turn on the pump
      Blynk.virtualWrite(V5, 1); // Update Blynk virtual pin
      bt2_state = LOW; // Update the button state
      delay(200); // Delay to debounce the button
    }
  } else {
    bt2_state = HIGH; // Reset button state
  }
  if (gt_doamdat > get_soil + 10) { // If current soil moisture is more than the threshold + 10
    if (bt2_state == HIGH) { // If the pump is currently on
      digitalWrite(bom, LOW); // Turn off the pump
      Blynk.virtualWrite(V5, 0); // Update Blynk virtual pin
      bt2_state = LOW; // Update the button state
      delay(200); // Delay to debounce the button
    }
  } else {
    bt2_state = HIGH; // Reset button state
  }
}

// Function to control the roof automatically based on rain detection
void auto_roof() {
  if (gt_mua == 0) { // If there is no rain
    mai = 0; // Set roof state to closed
    Blynk.virtualWrite(V8, mai); // Update Blynk virtual pin
    for (pos = 130; pos >= 90; pos--) { // Move the servo to close the roof
      myservo.write(pos);
    }
  } else {
    bt6_state = HIGH; // Reset button state
  }

  if (gt_mua == 1) { // If it is raining
    mai = 1; // Set roof state to open
    Blynk.virtualWrite(V8, mai); // Update Blynk virtual pin
    for (pos = 90; pos <= 130; pos++) { // Move the servo to open the roof
      myservo.write(pos);
    }
  } else {
    bt6_state = HIGH; // Reset button state
  }
}
