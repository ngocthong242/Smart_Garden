#define BLYNK_AUTH_TOKEN "pOfYa1YR4ikGypOH2lWl2Nr91d1RPkeN" // Auth token for Blynk
#define BLYNK_PRINT Serial
#define doamdat 36 // Pin for soil moisture sensor
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include <BH1750.h>
#include <ESP32Servo.h>
Servo myservo;

BH1750 lightMeter(0x23); // Address of the BH1750 sensor
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4); // LCD display setup
#include <Adafruit_Sensor.h>
#include "DHT.h"
#define DHTTYPE DHT11 // DHT sensor type
#define DHTPIN 23 // Pin for DHT sensor
DHT dht(DHTPIN, DHTTYPE);

#define mua 4 // Pin for rain sensor

// Pin definitions for various inputs and outputs
#define in1 15
#define in2 35
#define in3 33
#define in4 26
#define in5 27
#define in6 32
#define in7 25
#define bom 19 // Pump control pin
#define den 18 // Light control pin (relay)
#define suong 17 // Mist control pin
#define nguon 16 // Power control pin

unsigned long times = 0;
float gt_nhietdo; // Temperature value
int gt_doam; // Humidity value
int gt_doamdat; // Soil moisture value
int gt_mua; // Rain detection value
int lux; // Light intensity value

// Button states
boolean bt2_state = HIGH, bt4_state = HIGH, bt3_state_1 = HIGH, bt3_state_2 = HIGH, bt3_state = HIGH, bt6_state = HIGH, bt7_state = HIGH;
int bt3_temp; // Counter for button presses
int dem = 0;
int gt_in1 = 1, gt_in2 = 1, gt_in3 = 1, gt_in4 = 1, gt_in5 = 1, gt_in6 = 1, gt_in7 = 1;
int value;
int mai; // Variable for roof control
int vl_bom; // Variable for pump state
int vl_den; // Variable for light state
int auto_mode; // Auto mode flag

// Servo control
int get_air, get_light, get_soil;
int pos = 130;

// Custom characters for progress bar on LCD
byte zero[] = {B00000, B00000, B00000, B00000, B00000, B00000, B00000, B00000};
byte one[] = {B10000, B10000, B10000, B10000, B10000, B10000, B10000, B10000};
byte two[] = {B11000, B11000, B11000, B11000, B11000, B11000, B11000, B11000};
byte three[] = {B11100, B11100, B11100, B11100, B11100, B11100, B11100, B11100};
byte four[] = {B11110, B11110, B11110, B11110, B11110, B11110, B11110, B11110};
byte five[] = {B11111, B11111, B11111, B11111, B11111, B11111, B11111, B11111};

char ssid[] = "SONY"; // WiFi SSID
char pass[] = "1234567890"; // WiFi password
WidgetLED ledconect(V0); // LED widget for Blynk connection status

BlynkTimer timer;

// Function to blink the LED widget
void blinkLedWidget() {
  if (ledconect.getValue()) {
    ledconect.off();
    Serial.println("ledconect: off");
  } else {
    ledconect.on();
    Serial.println("ledconect: on");
  }
}

void setup() {
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, IPAddress(43, 229, 135, 169), 8080);
  timer.setInterval(1000L, blinkLedWidget);

  Wire.begin();
  dht.begin();
  lightMeter.begin();

  lcd.init();
  lcd.backlight();
  pinMode(mua, INPUT);

  pinMode(in1, INPUT);
  pinMode(in2, INPUT);
  pinMode(in3, INPUT);
  pinMode(in4, INPUT);
  pinMode(in5, INPUT);
  pinMode(in6, INPUT);
  pinMode(in7, INPUT);

  pinMode(bom, OUTPUT);
  pinMode(suong, OUTPUT);
  pinMode(den, OUTPUT);
  pinMode(nguon, OUTPUT);
  myservo.attach(27);

  // Create custom characters for progress bar
  lcd.createChar(0, zero);
  lcd.createChar(1, one);
  lcd.createChar(2, two);
  lcd.createChar(3, three);
  lcd.createChar(4, four);
  lcd.createChar(5, five);
  
  lcd.setCursor(0, 0);
  lcd.print("Loading...");
  
  for (int i = 0; i <= 100; i++) {
    updateProgressBar(i, 100, 1);
    delay(50);
  }
  
  delay(1000);
  lcd.clear();
  manhinh();
}

// Function to update the progress bar on LCD
void updateProgressBar(unsigned long count, unsigned long totalCount, int lineToPrintOn) {
  double factor = totalCount / 99.5; // Scaling factor
  int percent = (count + 1) / factor;
  int number = percent / 5;
  int remainder = percent % 5;
  if (number > 0) {
    lcd.setCursor(number - 1, lineToPrintOn);
    lcd.write(5);
  }

  lcd.setCursor(number, lineToPrintOn);
  lcd.write(remainder);
}

void loop() {
  Blynk.run();
  timer.run();
  docCamBien();
  xulinut();
  sendataLCD();
  autoMode();
}

// Function to set up the LCD screen
void manhinh() {
  lcd.setCursor(0, 0);
  lcd.print("L:"); // Light
  lcd.setCursor(8, 0);
  lcd.print("lx");
  lcd.setCursor(11, 0);
  lcd.print("S:"); // Soil moisture
  lcd.setCursor(19, 0);
  lcd.print("%");
  lcd.setCursor(0, 1);
  lcd.print("T:"); // Temperature
  lcd.setCursor(8, 1);
  lcd.print("*C");
  lcd.setCursor(11, 1);
  lcd.print("H:"); // Humidity
  lcd.setCursor(19, 1);
  lcd.print("%");

  lcd.setCursor(0, 2);
  lcd.print("PUMP:");
  lcd.setCursor(11, 2);
  lcd.print("LED :");
  lcd.setCursor(0, 3);
  lcd.print("PEW :");
  lcd.setCursor(11, 3);
  lcd.print("ROOF:");
}

// Blynk virtual pin write functions for controlling devices
BLYNK_WRITE(V5) {
  int A = param.asInt();
  digitalWrite(bom, A); // Control pump
  if (A == 1) vl_bom = 1;
  if (A == 0) vl_bom = 0;
}

BLYNK_WRITE(V6) {
  int A = param.asInt();
  if (A == 1) {
    digitalWrite(suong, 1); // Control mist
    delay(500);
    digitalWrite(suong, 0);
    bt3_temp = 1;
  } else {
    if (A == 0) {
      digitalWrite(nguon, 1); // Control power
      delay(500);
      digitalWrite(nguon, 0);
      bt3_temp = 0;
    }
  }
}

BLYNK_WRITE(V7) {
  int A = param.asInt();
  digitalWrite(den, A); // Control light
  if (A == 1) vl_den = 1;
  if (A == 0) vl_den = 0;
}

BLYNK_WRITE(V8) {
  int A = param.asInt();

  if (A == 0) {
    mai = 0; // Close roof
    for (pos = 130; pos >= 90; pos--) {
      myservo.write(pos);
      delay(15);
    }
  }
  if (A == 1) {
    mai = 1; // Open roof
    for (pos = 90; pos <= 130; pos++) {
      myservo.write(pos);
      delay(15);
    }
  }
}

BLYNK_WRITE(V9) {
  int A = param.asInt();
  if (A == 1) {
    auto_mode = 1; // Enable auto mode
  }
  if (A == 0) {
    auto_mode = 0; // Disable auto mode
  }
}

BLYNK_WRITE(V11) {
  get_air = param.asInt(); // Get air humidity value
}
BLY

NK_WRITE(V12) {
  get_light = param.asInt(); // Get light intensity value
}
BLYNK_WRITE(V13) {
  get_soil = param.asInt(); // Get soil moisture value
}
