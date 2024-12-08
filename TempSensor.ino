#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <DHT.h>

// DHT11 settings
#define DHTPIN 2     // DHT11 data pin connected to pin 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// OLED display settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  // Initialize serial monitor
  Serial.begin(9600);
  
  // Initialize DHT sensor
  dht.begin();
  Serial.println("DHT11 initialized");

  // Initialize OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Check the OLED I2C address (default is 0x3C)
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.display();
}

void loop() {
  // Read temperature and humidity
  float temperature = dht.readTemperature();    // Temperature in Celsius
  float humidity = dht.readHumidity();

  // Check if readings are valid
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Display temperature and humidity on OLED
  display.clearDisplay();
  
  // Temperature
  display.setTextSize(2); // Reduced text size for better fit
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print(F("Temp: "));
  display.print(temperature, 1); // Show one decimal place
  display.print(F("C"));

  // Humidity
  display.setCursor(0, 32); // Position for the second line
  display.print(F("Hum:  "));
  display.print(humidity, 1); // Show one decimal place
  display.print(F("%"));

  display.display();

  // Print to serial monitor
  Serial.print(F("Temperature: "));
  Serial.print(temperature, 1);
  Serial.println(F("C"));
  Serial.print(F("Humidity: "));
  Serial.print(humidity, 1);
  Serial.println(F("%"));

  // Wait before next update
  delay(1000);
}