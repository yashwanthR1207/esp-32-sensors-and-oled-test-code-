#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

// ========== OLED SETTINGS ==========
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define OLED_ADDR 0x3C

Adafruit_SSD1306 display(
  SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET
);

// ========== SENSOR PINS ==========
#define DHT_PIN 27
#define DHT_TYPE DHT11

#define WATER_PIN 34
#define FLAME_AO 33
#define FLAME_DO 32

DHT dht(DHT_PIN, DHT_TYPE);

// Most flame modules have LOW as active
#define FLAME_ACTIVE LOW

// ========== SENSOR VARIABLES ==========
float temperature = NAN;
float humidity = NAN;

int waterValue = 0;
int flameValue = 0;

bool fireDetected = false;

// ========== TIMERS ==========
unsigned long lastDHT = 0;
unsigned long lastDisplay = 0;
unsigned long lastSerial = 0;

// ========== SETUP ==========
void setup() {

  Serial.begin(115200);

  // Initialize I2C (SDA = GPIO 25, SCL = GPIO 26)
  Wire.begin(25, 26);
  Wire.setClock(100000);

  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println("OLED ERROR");
    while (true) {
      delay(1000);
    }
  }

  // Initialize sensors
  dht.begin();

  pinMode(FLAME_DO, INPUT_PULLUP);

  analogReadResolution(12);

  // Show monitoring screen immediately
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);

  display.setCursor(0, 0);
  display.println("FLOOD & FIRE MONITOR");

  display.drawLine(0, 11, 127, 11, SSD1306_WHITE);

  display.setCursor(0, 19);
  display.println("TEMP: WAITING...");

  display.setCursor(0, 30);
  display.println("HUMID: WAITING...");

  display.setCursor(0, 41);
  display.println("WATER: READING...");

  display.setCursor(0, 52);
  display.println("FIRE: CHECKING...");

  display.display();

  Serial.println("MONITORING SYSTEM STARTED");
}

// ========== MAIN LOOP ==========
void loop() {

  unsigned long currentMillis = millis();

  // Read DHT11 every 2 seconds
  if (currentMillis - lastDHT >= 2000) {

    lastDHT = currentMillis;

    float newTemperature = dht.readTemperature();
    float newHumidity = dht.readHumidity();

    if (!isnan(newTemperature)) {
      temperature = newTemperature;
    }

    if (!isnan(newHumidity)) {
      humidity = newHumidity;
    }
  }

  // Read water sensor
  waterValue = analogRead(WATER_PIN);

  // Read flame sensor
  flameValue = analogRead(FLAME_AO);

  int flameDigital = digitalRead(FLAME_DO);

  fireDetected = (flameDigital == FLAME_ACTIVE);

  // Update OLED every 500 milliseconds
  if (currentMillis - lastDisplay >= 500) {

    lastDisplay = currentMillis;

    display.clearDisplay();

    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);

    // HEADER
    display.setCursor(0, 0);
    display.println("FLOOD & FIRE MONITOR");

    display.drawLine(0, 11, 127, 11, SSD1306_WHITE);

    // TEMPERATURE
    display.setCursor(0, 16);
    display.print("TEMP : ");

    if (isnan(temperature)) {
      display.println("-- C");
    } else {
      display.print(temperature, 1);
      display.println(" C");
    }

    // HUMIDITY
    display.setCursor(0, 27);
    display.print("HUMID: ");

    if (isnan(humidity)) {
      display.println("-- %");
    } else {
      display.print(humidity, 1);
      display.println(" %");
    }

    // WATER
    display.setCursor(0, 38);
    display.print("WATER: ");
    display.println(waterValue);

    // FIRE
    display.setCursor(0, 49);
    display.print("FIRE : ");

    if (fireDetected) {
      display.println("DETECTED!");
    } else {
      display.println("SAFE");
    }

    display.display();
  }

  // SERIAL MONITOR
  if (currentMillis - lastSerial >= 2000) {

    lastSerial = currentMillis;

    Serial.println("----- LIVE SENSOR DATA -----");

    Serial.print("Temperature: ");
    Serial.println(temperature);

    Serial.print("Humidity: ");
    Serial.println(humidity);

    Serial.print("Water ADC: ");
    Serial.println(waterValue);

    Serial.print("Flame Analog: ");
    Serial.println(flameValue);

    Serial.print("Flame Digital: ");
    Serial.println(flameDigital);

    Serial.print("Fire Status: ");
    Serial.println(fireDetected ? "DETECTED" : "SAFE");
  }
}
