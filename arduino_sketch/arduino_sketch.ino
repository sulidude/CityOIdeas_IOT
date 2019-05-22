#include <SPI.h>
#include <LoRa.h>
#define BUTTON 5
#define LED 4
#define DEVICE_ID "69"

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
 Serial.println("Setup LoRa shield...");
  if (!LoRa.begin(866000000)) {
    Serial.println("Starting LoRa failed!");
    while(1);
  }
  LoRa.setSyncWord(0x34);
  Serial.println("LoRa shield initialized");
 pinMode(LED,OUTPUT);
 pinMode(BUTTON,INPUT);
 Serial.println("Signalling ready by flashing LED 3 times");

  for(int i=0; i<3; i++) {
    digitalWrite(LED, HIGH);
    delay(200);
    digitalWrite(LED, LOW);
    delay(400);
  }
  Serial.println("Ready!");
}
int count = 0;
void sendClick() {
  Serial.print("Sending packet ");
  Serial.print(count);
  Serial.println("... ");
  int status = LoRa.beginPacket();
  if (status) {
    LoRa.print("<");
    LoRa.print(DEVICE_ID);
    LoRa.print(">");
    unsigned long m = millis();
    LoRa.print(m);
    LoRa.print(",");
    LoRa.print(count++);
    LoRa.print(", Fuckboys");
    LoRa.endPacket();
    Serial.println("Packet sent");
  } else {
    Serial.println("Error sending packet");
  }
}
void loop() {
  // put your main code here, to run repeatedly:
  int input = digitalRead(4);
  
  //Serial.println(input);
   
  
  if(input)
  {
    digitalWrite(5,HIGH);
      sendClick();
      delay(250);
      
  }else{
    digitalWrite(5,LOW);
    delay(250);
  }
  
  /*
  digitalWrite(8,HIGH);
  delay(100);
  digitalWrite(8,LOW);
  delay(100);
  */
 
}
