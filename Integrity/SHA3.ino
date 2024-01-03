#include <Crypto.h>
#include <SHA3.h>

void setup() {
  Serial.begin(9600);
  
  while (!Serial) {
    ; // Wait for serial port to connect
  }
}

void loop() {
  Serial.print("Your message: ");
  while (Serial.available() == 0) {}
    SHA3_256 sha3;
    String message = Serial.readString();
    Serial.print(message);
    unsigned int len = message.length();
    
    char* charArray = (char*) malloc((len + 1) * sizeof(char));
    message.toCharArray(charArray, len + 1);
    
    sha3.update(charArray, len);
    
    uint8_t hash[32];
    sha3.finalize(hash, sizeof(hash));
    
    Serial.print("\nMessage in SHA-3: ");
    for (int i = 0; i < 32; i++) {
      Serial.print(hash[i], HEX);
    }
    Serial.println();
  
  free(charArray);
}