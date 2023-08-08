/**
* Smart Blinds Project Sketch for Arduino Nano 33 BLE Sense
*/

// Libraries: Stepper, Arduino_APDS9960, Arduino_LPS22HB,  
#include <ArduinoBLE.h> // BLE control
#include <Arduino_APDS9960.h> // light intensity
#include <Arduino_LPS22HB.h> // temperature sensor
//#include <Stepper.h> // for stepper control

// Enums
enum BlindsState { // Track blinds open/close state
  BLINDS_CLOSED,
  BLINDS_OPEN
};

enum OperationMode { // Track whether automated control or manual via BLE
  MANUAL,
  AUTOMATIC
};

// Global variables
BLEService blindsService("180A");
BLEByteCharacteristic switchCharacteristic("2A57", BLERead | BLEWrite);

constexpr int SERIAL_SPEED = 9600;
const int LED = LED_BUILTIN;

bool failed_sensor = false;

BlindsState currentState = BLINDS_CLOSED;
OperationMode mode = AUTOMATIC;

// Functions
void setup() {
  Serial.begin(SERIAL_SPEED);

  While(!Serial);

  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
  pinMode(LED, OUTPUT);

  digitalWrite(LED, LOW);
  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDG, HIGH);
  digitalWrite(LEDB, HIGH);

  if (!APDS.begin()) {
    Serial.println("Failed to initialize APDS9960 sensor!");
    failed_sensor = true;
  }

  if (!BARO.begin()) {
    Serial.println("Failed to initialize pressure sensor!");
    failed_sensor = true;
  }

  if (!BLE.begin()) {
    Serial.println("Failed to start BLE module!");
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

  BLE.setLocalName("Nano 33 BLE Sense: Blinds");
  BLE.setAdvertisedService(blindsService);

  blindsService.addCharacteristic(switchCharacteristic);
  BLE.addService(blindsService);

  BLE.advertise();

  Serial.println("BLE Service started...");
}

void loop() {

  BLEDevice central = BLE.central();

  if(central) {
    Serial.print("Connected: ");
    Serial.println(central.address());
    digitalWrite(LED, HIGH);

    mode = MANUAL;

    // **** Start BLE logic


    // **** On Disconnection
    mode = AUTOMATIC;
  }

  if(mode == AUTOMATIC) {
    Serial.println("Running in Automatic control mode");

    switch(currentState) {
      case BLINDS_CLOSE:
        Serial.println("Blinds are currently closed");
        break;
      case BLINDS_OPEN:
        Serial.println("BLinds are currently open");
        break;
    }

  }

  delay(1000);
}