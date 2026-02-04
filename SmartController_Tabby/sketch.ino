#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// --- Hardware Pins ---
const int PIN_ESTOP = 2;   // Interrupt Pin
const int PIN_PULSE = 3;   // Interrupt Pin
const int PIN_TGT   = A0;  // Rotary Pot
const int PIN_ACT   = A1;  // Slide Pot

// --- Global Variables (Volatile is for Interrupts) ---
volatile bool isEmergency = false;
volatile unsigned long productCount = 0;
LiquidCrystal_I2C lcd(0x27, 16, 2);

// --- Interrupt Service Routines (ISRs) ---
void handleEStop() {
  isEmergency = true; // Set flag immediately
}

void handlePulse() {
  if (!isEmergency) {
    productCount++; // Only count if system is safe
  }
}

void setup() {
  Serial.begin(9600);
  
  // Initialize LCD
  lcd.init();          
  lcd.backlight();     
  
  // Configure Buttons with Internal Pullups
  pinMode(PIN_ESTOP, INPUT_PULLUP);
  pinMode(PIN_PULSE, INPUT_PULLUP);

  // Attach Hardware Interrupts
  attachInterrupt(digitalPinToInterrupt(PIN_ESTOP), handleEStop, FALLING);
  attachInterrupt(digitalPinToInterrupt(PIN_PULSE), handlePulse, FALLING);

  lcd.print("CORE INITIALIZED");
  delay(1000);
  lcd.clear();
}

void loop() {
  // 1. SAFETY CHECK (State Machine Logic)
  if (isEmergency) {
    displayEmergency();
    return; // Stop the rest of the loop from running
  }

  // 2. READ DATA
  int target = analogRead(PIN_TGT);
  int actual = analogRead(PIN_ACT);

  // 3. TELEMETRY (Serial Monitor)
  Serial.print("T:"); Serial.print(target);
  Serial.print(" A:"); Serial.print(actual);
  Serial.print(" Count:"); Serial.println(productCount);

  // 4. UPDATE DASHBOARD (Non-blocking timing example)
  updateLCD(target, actual);
  
  delay(150); // Small delay for screen readability
}

void updateLCD(int t, int a) {
  // Top Row: Target and the Counter
  lcd.setCursor(0, 0);
  lcd.print("T:"); lcd.print(t);
  lcd.print(" Cnt:"); lcd.print(productCount);
  lcd.print("   "); // Clear trailing characters

  // Bottom Row: Actual and Error
  lcd.setCursor(0, 1);
  lcd.print("A:"); lcd.print(a);
  lcd.print(" Err:"); lcd.print(t - a);
  lcd.print("   ");
}

void displayEmergency() {
  static bool blink = false;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("!!! E-STOP !!!");
  lcd.setCursor(0, 1);
  lcd.print("RESET REQUIRED");
  
  Serial.println("ALARM: EMERGENCY STOP ACTIVE");
  
  while(isEmergency) {
    // In a real system, you'd need a physical reset 
    // In Wokwi, just restart the simulation to clear
    delay(500); 
  }
}