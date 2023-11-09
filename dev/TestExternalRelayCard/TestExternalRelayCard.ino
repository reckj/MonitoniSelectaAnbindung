#include <ShiftRegister74HC595_NonTemplate.h>

///////////////////////------ definitions ------///////////////////////

#define I2C_SDA 16
#define I2C_SCL 17
#define RTC_IRQ 15

// PINS OUT
#define DATA_PIN 7
#define CLOCK_PIN 5
#define LATCH_PIN 6

#define ADDRESS_AMOUNT 21

#define Item_1_CH 14
#define Item_2_CH 19
#define Item_3_CH 15
#define Item_4_CH 4
#define Item_5_CH 3
#define Item_6_CH 9
#define Item_7_CH 11
#define Item_8_CH 13
#define Item_9_CH 21
#define Item_10_CH 47

String command = "GO";



ShiftRegister74HC595_NonTemplate *control;


void setup() {
  Serial.begin(9600);
  Serial.println("Type GO to cascade through the connected relays.");

  control = new ShiftRegister74HC595_NonTemplate(24, DATA_PIN, CLOCK_PIN, LATCH_PIN);
  assert(control);
  control->setAllLow();
  delay(1000);

  pinMode(Item_1_CH, OUTPUT);
  pinMode(Item_2_CH, OUTPUT);
  pinMode(Item_3_CH, OUTPUT);
  pinMode(Item_4_CH, OUTPUT);
  pinMode(Item_5_CH, OUTPUT);
  pinMode(Item_6_CH, OUTPUT);
  pinMode(Item_7_CH, OUTPUT);
  pinMode(Item_8_CH, OUTPUT);
  pinMode(Item_9_CH, OUTPUT);
  pinMode(Item_10_CH, OUTPUT);  
}

void loop() {
  char inputBuffer[21];
  int pinNumber = 0;
  //control->set(13, HIGH);

  // Check if data is available to read from the serial port
  if (Serial.available()) {
    delay(10); // Small delay for the entire message to arrive
    int size = Serial.readBytesUntil('\n', inputBuffer, sizeof(inputBuffer) - 1);

    // Null terminate the string
    inputBuffer[size] = '\0';

    String inputString = String(inputBuffer);
    
    if (inputString == command) {
      Serial.println("letsgo");
      digitalWrite(Item_1_CH, LOW);
      //control->set(13,LOW);
      delay(3000);
      digitalWrite(Item_1_CH, HIGH);

      delay(2000);
      digitalWrite(Item_2_CH, LOW);
      //control->set(13,LOW);
      delay(3000);
      digitalWrite(Item_2_CH, HIGH);

      delay(2000);
      digitalWrite(Item_3_CH, LOW);
      //control->set(13,LOW);
      delay(3000);
      digitalWrite(Item_3_CH, HIGH);

      delay(2000);
      digitalWrite(Item_4_CH, LOW);
      //control->set(13,LOW);
      delay(3000);
      digitalWrite(Item_4_CH, HIGH);

      delay(2000);
      digitalWrite(Item_5_CH, LOW);
      //control->set(13,LOW);
      delay(3000);
      digitalWrite(Item_5_CH, HIGH);

      delay(2000);
      digitalWrite(Item_6_CH, LOW);
      //control->set(13,LOW);
      delay(3000);
      digitalWrite(Item_6_CH, HIGH);

      delay(2000);
      digitalWrite(Item_7_CH, LOW);
      //control->set(13,LOW);
      delay(3000);
      digitalWrite(Item_7_CH, HIGH);

      delay(2000);
      digitalWrite(Item_8_CH, LOW);
      //control->set(13,LOW);
      delay(3000);
      digitalWrite(Item_8_CH, HIGH);

      delay(2000);
      digitalWrite(Item_9_CH, LOW);
      //control->set(13,LOW);
      delay(3000);
      digitalWrite(Item_9_CH, LOW);

      delay(2000);
      digitalWrite(Item_10_CH, LOW);
      //control->set(13,LOW);
      delay(3000);
      digitalWrite(Item_10_CH, LOW);
      delay(2000);
    }
    
    else {
      Serial.println("Invalid format. Use 'GO'.");
    }
  }
  
}
