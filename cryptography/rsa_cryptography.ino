#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

int p1, p2, n, t, flag;
long int m[50], j, e[50], d[50], temp[50], en[50];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  
  Serial.print("\nType 1 to encode and 2 to decode.");
  while (Serial.available() == 0) {}
  int command = Serial.parseInt();

  // get prime numbers
  Serial.print("\nEnter a prime number: ");
  while (Serial.available() == 0) {}
  p1 = Serial.parseInt();
  Serial.print(p1);

  Serial.print("\nEnter a second prime number: ");
  while (Serial.available() == 0) {}
  p2 = Serial.parseInt();
  Serial.print(p2);

  n = p1 * p2;
  t = (p1-1) * (p2-1);

  //create encryption key
  create_key();

  String msg;

  if (command == 1) { // encrypt message
    Serial.print("\nType your normal message: ");
    while (Serial.available() == 0) {}
    msg = Serial.readString();
    Serial.print(msg);

    for(int i = 0; msg[i] != NULL; i++) {
      m[i] = msg[i];
    }

    encrypt(msg);
  }
  else if (command == 2) { // decrypt message
    Serial.print("\nType your encrypted message: ");
    while (Serial.available() == 0) {}
    String e_msg = Serial.readString();
    Serial.print(e_msg);

    for(int i = 0; e_msg[i] != NULL; i++) {
      m[i] = e_msg[i];
    }

    decrypt(e_msg);
  }
  else {
    Serial.print("\nIncorrect command.");
  }
}

int is_prime(long int num) {
  int i;
  j = sqrt(num);
  for(i = 2; i <= j; i++)
  {
   if(num % i == 0)
     return 0;
  }
  return 1;
}

long int cd(long int num) {
  long int k = 1;
  while(1)
  {
    k = k + t;
    if(k % num == 0)
      return(k / num);
  }
}

void create_key() {
  int x = 0;

  for (int i = 2; i < t; i++) {
    if (t % i == 0) {
      continue;
    }

    flag = is_prime(i);
    if (flag == 1 && i != p1 && i != p2) {
        e[x] = i;
        flag = cd(e[x]);

        if (flag > 0) {
          d[x] = flag;
          x++;
        }

        if (x == 99) break;
    }
  }
}

void encrypt(String msg) {

  long int p, c, key = e[0], x;
  int i = 0;
  long int len = strlen(msg.c_str());

  while (i != len) {
    p = m[i];
    p = p - 96;
    x = 1;

    for (j = 0; j < key; j++) {
      x = x * p;
      x = x % n;
    }

    temp[i] = x;
    c = x + 96;
    en[i] = c;
    i++;
  }

  en[i] = -1;

  Serial.print("\nThe encrypted message is: ");
  for (i = 0; en[i] != -1; i++) {
    Serial.print(en[i]);
  }
  Serial.print("\n");
}

void decrypt(String msg) {
  
  long int p, c, key = d[0], x;
  int i = 0; 

  while (en[i] != -1) {
    c = temp[i];
    x = 1;

    for (j = 0; j < key; j++) {
      x = x * c;
      x = x % n;
    }

    p = x + 96;
    m[i] = p;
    i++;
  }

  m[i] = -1;

  Serial.print("\nThe decrypted message is: ");
  for (i = 0; m[i] != -1; i++) {
    Serial.write(m[i]);
  }
  Serial.print("\n");
}


