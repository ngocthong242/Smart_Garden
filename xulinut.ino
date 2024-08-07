// Function to handle button presses and control devices
void xulinut() {
  // Handle pump button
  if (gt_in2 == 0) { // If button 2 is pressed
    if (bt2_state == HIGH) { // If pump button state is high
      digitalWrite(bom, !digitalRead(bom)); // Toggle pump state
      Blynk.virtualWrite(V5, digitalRead(bom)); // Update Blynk virtual pin
      bt2_state = LOW; // Update button state
      delay(200); // Debounce delay
    }
  } else {
    bt2_state = HIGH; // Reset button state
  }

  // Handle light button
  if (gt_in3 == 0) { // If button 3 is pressed
    if (bt3_state == HIGH) { // If light button state is high
      digitalWrite(den, !digitalRead(den)); // Toggle light state
      Blynk.virtualWrite(V7, digitalRead(den)); // Update Blynk virtual pin
      bt3_state = LOW; // Update button state
      delay(200); // Debounce delay
    }
  } else {
    bt3_state = HIGH; // Reset button state
  }

  // Handle roof control
  if (gt_in6 == 0) { // If button 6 is pressed
    if (mai == 0) { // If roof is closed
      if (bt6_state == HIGH) { // If roof button state is high
        mai = 1; // Set roof state to open
        Blynk.virtualWrite(V8, mai); // Update Blynk virtual pin
        for (pos = 130; pos >= 90; pos--) { // Move servo to open roof
          myservo.write(pos);
          delay(15);
        }
        delay(100); // Delay for servo movement
        bt6_state = LOW; // Update button state
      }
    } else {
      bt6_state = HIGH; // Reset button state
    }
    if (mai == 1) { // If roof is open
      if (bt6_state == HIGH) { // If roof button state is high
        mai = 0; // Set roof state to closed
        Blynk.virtualWrite(V8, mai); // Update Blynk virtual pin
        for (pos = 90; pos <= 130; pos++) { // Move servo to close roof
          myservo.write(pos);
          delay(15);
        }
        delay(100); // Delay for servo movement
        bt6_state = LOW; // Update button state
      }
    } else {
      bt6_state = HIGH; // Reset button state
    }
  }

  // Handle mist control button
  if (gt_in4 == 0) { // If button 4 is pressed
    if (bt3_temp == 1) { // If mist is on
      if (bt4_state == HIGH) { // If mist button state is high
        digitalWrite(nguon, 1); // Turn off mist
        delay(500); // Delay for mist to turn off
        digitalWrite(nguon, 0); // Ensure mist is off
        bt3_temp = 0; // Update mist state
        Blynk.virtualWrite(V6, bt3_temp); // Update Blynk virtual pin
        bt4_state = LOW; // Update button state
      }
    } else {
      bt4_state = HIGH; // Reset button state
    }
    if (bt3_temp == 0) { // If mist is off
      if (bt4_state == HIGH) { // If mist button state is high
        digitalWrite(suong, 1); // Turn on mist
        delay(500); // Delay for mist to turn on
        digitalWrite(suong, 0); // Ensure mist is on
        bt3_temp = 1; // Update mist state
        Blynk.virtualWrite(V6, bt3_temp); // Update Blynk virtual pin
        bt4_state = LOW; // Update button state
      }
    } else {
      bt4_state = HIGH; // Reset button state
    }
  }

  // Handle auto mode button
  if (gt_in7 == 0) { // If button 7 is pressed
    if (auto_mode == 1) { // If auto mode is on
      if (bt7_state == HIGH) { // If auto mode button state is high
        auto_mode = 0; // Turn off auto mode
        Blynk.virtualWrite(V9, 0); // Update Blynk virtual pin
        bt7_state = LOW; // Update button state
      }
    } else {
      bt7_state = HIGH; // Reset button state
    }
    if (auto_mode == 0) { // If auto mode is off
      if (bt7_state == HIGH) { // If auto mode button state is high
        auto_mode = 1; // Turn on auto mode
        Blynk.virtualWrite(V9, 1); // Update Blynk virtual pin
        bt7_state = LOW; // Update button state
      }
    } else {
      bt7_state = HIGH; // Reset button state
    }
  }
}
