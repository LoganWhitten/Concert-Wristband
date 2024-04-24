/*
Example, transmit all received ArtNet messages (Op-Code DMX) out of the
serial port in plain text.
Function pointer with the C++11 function-object "std::function".

Stephan Ruloff 2019
https://github.com/rstephan/ArtnetWifi
*/
#include <ArtnetWifi.h>
#include <Arduino.h>


WiFiUDP UdpSend;
ArtnetWifi artnet;

const int RED = 5;
const int GREEN = 4;
const int BLUE = 0;

const bool LEADER = false;

// connect to wifi – returns true if successful or false if not
bool ConnectWifi(void)
{
  bool state = true;
  int i = 0;

  Serial.println("");
  Serial.println("Connecting to WiFi");
}
  // Wait for connection
void setup()
{
  Serial.begin(115200);
    meshSetup();
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

  // this will be called for each packet received
  artnet.setArtDmxFunc([](DMX_FUNC_PARAM){
    bool tail = false;

    Serial.print("DMX: Univ: ");
    Serial.print(universe, DEC);
    Serial.print(", Seq: ");
    Serial.print(sequence, DEC);
    Serial.print(", Data (");
    Serial.print(length, DEC);
    Serial.print("): ");

    if (length > 16) {
      length = 16;
      tail = false;
    }
    // send out the buffer
    for (int i = 0; i < length; i++) {
      //Serial.print(data[i]);
      Serial.print(" ");
      if(i == 0) {
        Serial.print('red: ');
        Serial.print(data[i]);
        analogWrite(RED, data[i]);
      } else if (i == 1) {
        Serial.print('green: ');
        Serial.print(data[i]);
        analogWrite(GREEN, data[i]);
      } else if (i == 2) {
        Serial.print('blue: ');
        Serial.print(data[i]);
        analogWrite(BLUE, data[i]);
      }
    }
    if (tail) {
      Serial.print("...");
    }
    Serial.println();
  });
  artnet.begin();
}

void loop()
{
  // we call the read function inside the loop
  meshLoop();
  artnet.read();
}