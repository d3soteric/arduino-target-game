#include <TM1637Display.h>

// Pin definitions for TM1637 4-digit, 7-segment display
const int CLK = 6;
const int DIO = 7;
TM1637Display display(CLK, DIO);

// Pin definitions for the three limit switches
const int switchPin1 = 2;  // First switch on pin 2
const int switchPin2 = 3;  // Second switch on pin 3
const int switchPin3 = 4;  // Third switch on pin 4

int score = 0;

void setup() {
  Serial.begin(9600);  // Initialize Serial Monitor for debugging
  display.setBrightness(0x0F);  // Maximum brightness
  display.showNumberDec(0);     // Initialize display to show '0'

  // Set up the switch pins with internal pull-up resistors
  pinMode(switchPin1, INPUT_PULLUP);
  pinMode(switchPin2, INPUT_PULLUP);
  pinMode(switchPin3, INPUT_PULLUP);
}

void loop() {
  // Check all three switches with debounce
  if (isSwitchPressed(switchPin1) || isSwitchPressed(switchPin2) || isSwitchPressed(switchPin3)) {
    score++;
    updateDisplay();
    Serial.println("Switch pressed.");  // Debugging output
  }
  delay(50);  // Add a short delay to stabilize loop
}

// Debounce function to confirm a valid press
bool isSwitchPressed(int pin) {
  if (digitalRead(pin) == LOW) {      // Initial press detection
    delay(20);                        // Short delay for debounce
    if (digitalRead(pin) == LOW) {    // Confirm button still pressed
      while (digitalRead(pin) == LOW);  // Wait for release
      return true;
    }
  }
  return false;
}

// Function to update the 4-digit, 7-segment display with the current score
void updateDisplay() {
  if (score > 9999) score = 0;  // Reset to 0 if score exceeds 9999
  display.showNumberDec(score, true);  // Display the score
}