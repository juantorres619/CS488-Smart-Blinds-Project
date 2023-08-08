/**
* Smart Blinds Project Sketch for Arduino Nano 33 BLE Sense
*/

// Libraries: Stepper, Arduino_APDS9960, Arduino_LPS22HB,  
//#include <ArduinoBLE.h> // BLE control
#include <Arduino_APDS9960.h> // light intensity
#include <Arduino_LPS22HB.h> // temperature sensor
//#include <Stepper.h> // for stepper control

// Global variables
constexpr int SERIAL_SPEED = 9600;
const int LED = LED_BUILTIN;

bool failed_sensor = false;

enum BlindsState {
  BLINDS_CLOSED,
  BLINDS_OPEN
};

enum OperationMode {
  MANUAL,
  AUTOMATIC
};

BlindsState currentState = BLINDS_CLOSED;

// Functions
void setup() {
  Serial.begin(SERIAL_SPEED);

  While(!Serial);

  if (!APDS.begin()) {
    Serial.println("Failed to initialize APDS9960 sensor!");
    failed_sensor = true;
  }

  if (!BARO.begin()) {
    Serial.println("Failed to initialize pressure sensor!");
    failed_sensor = true;
  }

  if(failed_sensor) {
    Serial.println("Status: FAILED");
    Serial.println("One or more sensors failed to initialize!");
    while (1);
  } else {
    Serial.println("Status: OK");
    Serial.println("All sensors ready to go...");
  }

  pinMode(LED, OUTPUT);

  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);

  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDG, HIGH);
  digitalWrite(LEDB, HIGH);
}

void loop() {

  

  delay(1000);
}