#include <SPI.h>

// Pin definitions
#define MOSI_PIN 11
#define MISO_PIN 12
#define SCLK_PIN 13
#define WAIT_PIN 14  // Pin to wait until HIGH
#define RESET_PIN 15 // RST line

// SPI Settings
const SPISettings spiSettings(1000000, LSBFIRST, SPI_MODE3);

// Frames data
uint8_t frames[][11] = {
    {0x1, 0x00, 0x00, 0x00, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x2, 0x00, 0x00, 0x00, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x3, 0x00, 0x00, 0x00, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x4, 0x00, 0x00, 0x00, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x5, 0x00, 0x00, 0x00, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x6, 0x00, 0x00, 0x00, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x7, 0x00, 0x00, 0x00, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x8, 0x00, 0x00, 0x00, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00}, 
    {0xA, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0xB, 0x00, 0x00, 0x00, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0xC, 0x00, 0x00, 0x00, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
}; //Turn all LEDs on

// Function to calculate CRC (simple XOR)
uint8_t calculateCRC(const uint8_t* data, size_t length) {
  uint16_t crc = 0;
  for (size_t i = 0; i < length; i++) {
    crc += data[i];
  }
  return crc%256;
}



void printFrame(const char* label, const uint8_t* data, size_t length) {
  Serial.print(label);
  for (size_t i = 0; i < length; i++) {
    Serial.printf(" 0x%02X", data[i]);
  }
  Serial.println();
}


/////////

void setup() {
  pinMode(WAIT_PIN, INPUT);
  pinMode(RESET_PIN, OUTPUT);
  pinMode(MOSI_PIN, OUTPUT);
  pinMode(MISO_PIN, INPUT);
  pinMode(SCLK_PIN, OUTPUT);

  digitalWriteFast(MOSI_PIN, HIGH);
  digitalWriteFast(SCLK_PIN, HIGH);
  digitalWriteFast(RESET_PIN, HIGH);
  Serial.begin(115200);
  Serial.println("Initializing...");

 
  

  
  // Handle reset linedelay
  digitalWrite(RESET_PIN, LOW);
  delay(100);
  digitalWrite(RESET_PIN, HIGH);
  Serial.println("Setup Complete!");
  delay(500);
  while (digitalRead(WAIT_PIN) == LOW);
  // Initialize SPI
  SPI.begin();
}

void loop() {
  //while (digitalReadFast(WAIT_PIN) == LOW);
  Serial.println("----------------Start sequence-----------------");
  Serial.println("");
  
  for (size_t frameIndex = 0; frameIndex < sizeof(frames) / sizeof(frames[0]); frameIndex++) {
    uint8_t frame[12];
    uint8_t rxBuffer[12];

    // Copy frame data and calculate CRC
    memcpy(frame, frames[frameIndex], 11);
    frame[11] = calculateCRC(frame, 11);


    // Send the frame byte by byte
    SPI.beginTransaction(spiSettings);
    for (size_t i = 0; i < 12; i++) {
      //Wait for WAIT_PIN to go HIGH
      
      while (digitalReadFast(WAIT_PIN) == LOW);
      
      rxBuffer[i] = SPI.transfer(frame[i]); // Send byte and store the received byte
      
      delayMicroseconds(200);
      
      
    }
    
    

    // Print the received frame
  //if(frameIndex==0){
    printFrame("Received Frame:", rxBuffer, 12);
  //}

   // Delay between frames
    SPI.endTransaction();
    delayMicroseconds(3000);
  }
  Serial.println("");
  Serial.println("----------------End sequence-----------------");
 
}