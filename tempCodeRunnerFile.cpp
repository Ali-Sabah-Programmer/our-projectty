#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
#define ldrPin A0
#define ledGreenToCard 3
#define ledRedToCard 4
#define ledRedToPhotoScell 5
#define PazerToPhotoScell 6

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance.

int threshold = 900;

void setup()
{
    Serial.begin(9600); // Initiate a serial communication
    SPI.begin();        // Initiate SPI bus
    mfrc522.PCD_Init(); // Initiate MFRC522
    pinMode(ldrPin, INPUT);
    pinMode(ledGreenToCard, OUTPUT);
    pinMode(ledRedToCard, OUTPUT);
    pinMode(PazerToPhotoScell, OUTPUT);
    pinMode(ledRedToPhotoScell, OUTPUT);
    Serial.println("Approximate your card to the reader...");
    Serial.println();
}

void loop()
{
    // Look for new cards
    if (!mfrc522.PICC_IsNewCardPresent())
    {
        int lightLevel = readLDR();
        Serial.println(lightLevel);
        if (lightLevel < threshold)
        {
            digitalWrite(ledRedToPhotoScell, LOW);
            digitalWrite(PazerToPhotoScell, LOW);
        }
        else
        {
            digitalWrite(ledRedToPhotoScell, HIGH);
            digitalWrite(PazerToPhotoScell, HIGH);
            delay(10000);
        }
        delay(10);
        return;
    }
    // Select one of the cards
    if (!mfrc522.PICC_ReadCardSerial())
    {
        return;
    }
    // Show UID on serial monitor
    Serial.print("UID tag :");
    String content = "";
    byte letter;
    for (byte i = 0; i < mfrc522.uid.size; i++)
    {
        Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
        Serial.print(mfrc522.uid.uidByte[i], HEX);
        content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
        content.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    Serial.println();
    Serial.print("Message : ");
    content.toUpperCase();
    if (content.substring(1) == "8A 55 57 B4")
    { // Change the UID of the card/cards that you want to give access
        Serial.println("Authorized access");
        Serial.println();
        digitalWrite(ledGreenToCard, HIGH); // Turn on green LED
        digitalWrite(ledRedToCard, LOW);    // Turn off green LED
        delay(60000);
    }
    else if (content.substring(1) == "EC 07 BC 16")
    {
        Serial.println("Authorized access");
        Serial.println();
        digitalWrite(ledGreenToCard, HIGH); // Turn on green LED
        digitalWrite(ledRedToCard, LOW);    // Turn off green LED
        delay(60000);
    }
    else
    {
        Serial.println(" Access denied");
        Serial.println();
        digitalWrite(ledGreenToCard, LOW); // Turn off green LED
        digitalWrite(ledRedToCard, HIGH);  // Turn off green LED
        digitalWrite(ldrPin, LOW);         // Turn on red LED
        delay(2000);
    }
    delay(1000);
    digitalWrite(ledGreenToCard, LOW); // Turn off green LED
    digitalWrite(ledRedToCard, LOW);   // Turn off green LED
}

int readLDR()
{
    int rawData = analogRead(ldrPin);
    return rawData;
}