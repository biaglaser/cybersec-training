#include "MD5.h"

void setup() {
  Serial.begin(9600);

  while (!Serial) {
    ; // Wait for serial port to connect
  }

}

void loop() {

  Serial.print("Type in your message: ");
  while (Serial.available() == 0) {}
  String s = Serial.readString();
  int s_len = s.length();

  Serial.println(s);

  char* char_msg = new char[s_len + 1];
  strcpy(char_msg, s.c_str());


  unsigned char* h = MD5::make_hash(char_msg);

  char *md5_s = MD5::make_digest(h, 16);
  free(h);

  Serial.print("Your message after MD5: ");
  Serial.println(md5_s);
  Serial.println();

  free(md5_s);
  
}
