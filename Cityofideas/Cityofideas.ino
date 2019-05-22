#include <SPI.h>
#include <LoRa.h>
#define BUTTON 5
#define LED 4
#define DEVICE_ID "69"
#define QuestionId "1"
#define PosAnsId "7"
#define IOTDevice "IOT123"


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
  LoRa.print("{\"");
  LoRa.print("DeviceId\": \"");
  LoRa.print(IOTDevice);
  LoRa.print("\" ,"); 
  LoRa.print("\"QuestionId\" : "); 
  LoRa.print(QuestionId);
  LoRa.print(",");
  LoRa.print("\"PossibleAnswerId\" :"); 
  LoRa.print(PosAnsId);
  LoRa.print("}");
 // unsigned long m = millis();
 // LoRa.print(m);
 // LoRa.print(",");
 // LoRa.print(count++);
 count++;
  LoRa.endPacket();
Serial.println("Packet sent");
  } else {
    Serial.println("Error sending packet");
  }
}
void loop() {
  // put your main code here, to run repeatedly:
  int input = digitalRead(BUTTON);
  
  //Serial.println(input);
   
  
  if(input)
  {
      digitalWrite(LED,HIGH);
      sendClick();
      delay(250);
      
  }else{
    digitalWrite(LED,LOW);
    delay(250);
  }
  
  /*
  digitalWrite(8,HIGH);
  delay(100);
  digitalWrite(8,LOW);
  delay(100);
  */
 
}
