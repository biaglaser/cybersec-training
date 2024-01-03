#include "base64.hpp"


void setup() {
   // put your setup code here, to run once:
  Serial.begin(9600);
   
}

void loop() {  

  Serial.print("\nType 1 to encode and 2 to decode.");
  while (Serial.available() == 0) {}
  int command = Serial.parseInt();

  int base64_length;

  if (command == 1) { // encrypt message
    Serial.print("\nType your normal message: ");
    while (Serial.available() == 0) {}
    String msg = Serial.readString();
    Serial.print(msg);

    unsigned char* msg_char = (unsigned char*) msg.c_str();

    unsigned char encoded_char[20];
    
    base64_length = encode_base64(msg_char,12,encoded_char);
    Serial.print("\nBase64 Text: ");Serial.println((char *) encoded_char);
  }
  else if (command == 2) { // decrypt message
    Serial.print("\nType your encrypted message: ");
    while (Serial.available() == 0) {}
    String e_msg = Serial.readString();
    Serial.print(e_msg);

    unsigned char* e_msg_char = (unsigned char*) e_msg.c_str();
    
    unsigned char decoded_char[20];
    
    base64_length = decode_base64(e_msg_char,decoded_char);
    Serial.print("\nDecoded Text: ");Serial.println((char *) decoded_char);
  }
  else {
    Serial.print("\nIncorrect command.");
  }
}
