#include <LiquidCrystal.h>

// SIGNAL CLASS
class Signal {
   private:
      public:
    Graph();
    void addMovie(string movie, vector<string> movieActors);
    string getShortestPathBetweenActors(string actor1Name, string actor2Name);
    void printActors();
};

/////////////////

// distance sensor
const int DIS_TRIG = 9, DIS_ECHO = 10;

// LCD display
const int LCD_RS = 13, LCD_E = 12, LCD_DB4 = 4, LCD_DB5 = 5, LCD_DB6 = 6,
          LCD_DB7 = 7;

const int AIR_FRESH_OUT = 8;

// motion sensor
const int MOT_TRIG = 2;

LiquidCrystal lcd(LCD_RS, LCD_E, LCD_DB4, LCD_DB5, LCD_DB6, LCD_DB7);

long duration;      // Duration of sound wave travel
int distance_cm;    // distance in centimeters
int distance_inch;  // distance in inches

void setup() {
    Serial.begin(9600);  // establish serial communication

    lcd.begin(16, 2);
    lcd.print("HAHA ");

    pinMode(DIS_TRIG, OUTPUT);
    pinMode(DIS_ECHO, INPUT);

    pinMode(AIR_FRESH_OUT, OUTPUT);

    pinMode(MOT_TRIG, INPUT);
}
void loop() {
    Serial.println("out");
    lcd.setCursor(0, 1);
    lcd.print(millis() / 1000);

    // Generate a waveform in trigPin
    digitalWrite(DIS_TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(DIS_TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(DIS_TRIG, LOW);

    duration = pulseIn(DIS_ECHO, HIGH);
    distance_cm = duration * 0.034 / 2;
    distance_inch = duration * 0.0133 / 2;

    bool hasMotion = false;
    int motion_out = digitalRead(MOT_TRIG);
    if (motion_out == 1) {
        hasMotion = true;
    }

    if (hasMotion) {
        digitalWrite(AIR_FRESH_OUT, HIGH);
    } else {
        digitalWrite(AIR_FRESH_OUT, LOW);
    }

    // Display the OUTPUT in LCD Display
    lcd.setCursor(0, 0);
    lcd.print("Distance: ");
    lcd.print(distance_cm);
    lcd.println(" cm");
    lcd.setCursor(0, 1);
    lcd.print("Distance: ");
    lcd.print(distance_inch);
    lcd.println(" inch");
}