#include <WiFi.h>
#include <WiFiUdp.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// --- Wi-Fi Credentials ---
const char* ssid = "wifi_name";
const char* password = "wifi_-password";

// --- UDP Settings ---
WiFiUDP udp;
unsigned int localUdpPort = 5005;
char incomingPacket[255];

// --- OLED Display Settings ---
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET    -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C // 0x3C is the standard I2C address for SSD1306

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(115200);
  
  // 1. Initialize OLED Display
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  
  // Show initial startup text
  display.clearDisplay();  //Wipes the previous number
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 25);  // Rough coordinates of the center
  display.println("Connecting WiFi...");
  display.display();

  // 2. Connect to Wi-Fi Hotspot
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println();
  Serial.print("Connected! Your ESP32 IP Address is: ");
  Serial.println(WiFi.localIP()); // COPY THIS TO YOUR PYTHON SCRIPT

  // Update OLED to show successful connection
  display.clearDisplay();
  display.setCursor(10, 25);
  display.println("WiFi Connected!");
  display.setCursor(10, 40);
  display.println(WiFi.localIP());
  display.display();
  delay(2000);

  // 3. Start listening for UDP packets
  udp.begin(localUdpPort);
  
  // Clear screen ready for numbers
  display.clearDisplay();
  display.display();
}

void loop() {
  // Check if a packet has been received
  int packetSize = udp.parsePacket();
  
  if (packetSize) {
    // Read the incoming packet into our buffer
    int len = udp.read(incomingPacket, 255);
    if (len > 0) {
      incomingPacket[len] = 0; // Null-terminate the string
    }
    
    // Convert string to integer
    int fingerCount = atoi(incomingPacket);
    
    // Print to Serial for debugging
    Serial.print("Fingers Detected: ");
    Serial.println(fingerCount);
    
    // --- Update the OLED Display ---
    display.clearDisplay();
    display.setTextSize(7);            // Huge text size
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(45, 10);         // Roughly center the number
    display.print(fingerCount);
    display.display();
  }
}