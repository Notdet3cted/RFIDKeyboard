#include <SPI.h>
#include <MFRC522.h>
#include <Keyboard.h>

#define SS_PIN    10
#define RST_PIN    9 
#define MISO_PIN  14
#define MOSI_PIN  16
#define SCK_PIN   15 

MFRC522 mfrc522(SS_PIN, RST_PIN);
String content;
void setup() {
  Keyboard.begin();
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  mfrc522.PCD_DumpVersionToSerial();
  Serial.println();
}

void loop() {
    if ( ! mfrc522.PICC_IsNewCardPresent())
    {
      return;
    }
    if ( ! mfrc522.PICC_ReadCardSerial())
    {
      return;
    }
    Serial.print(" UID tag :");
    content = "";
    byte letter;

    for (byte i = 0; i < mfrc522.uid.size; i++)
    {
      Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
      Serial.print(mfrc522.uid.uidByte[i], HEX);
      content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : ""));
      content.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    content.toUpperCase();
    Serial.println();
    Keyboard.print(content);
    Keyboard.press(176);
    Keyboard.release(176);
    delay(2000);
  }
