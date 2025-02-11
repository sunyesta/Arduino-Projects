
#define BMP_SCK (13)
#define BMP_MISO (12)
#define BMP_MOSI (11)
#define BMP_CS (10)

#ifndef PRESSURE_TEMP_SENSOR_HPP
#define PRESSURE_TEMP_SENSOR_HPP

#include <Adafruit_BMP280.h>
#include <SPI.h>
#include <Wire.h>

Adafruit_BMP280 *bmp = new Adafruit_BMP280();  // I2C
unsigned status = bmp->begin(BMP280_ADDRESS_ALT, BMP280_CHIPID);
// Adafruit_BMP280 bmp;

#include "../Modules/Debounce.hpp"
#include "../Modules/Loopable.hpp"

class PressureTempSensor : public Loopable {
   private:
    DebounceTime dt = 1000;
    Debounce *deb = new Debounce(&dt);

   public:
    PressureTempSensor() : Loopable() {
        // while (!Serial) delay(100);   // wait for native usb

        Serial.println(F("BMP280 test"));

        if (!status) {
            Serial.println(
                F("Could not find a valid BMP280 sensor, check wiring or "
                  "try a different address!"));
            Serial.print("SensorID was: 0x");
            Serial.println(bmp->sensorID(), 16);
            Serial.print(
                "        ID of 0xFF probably means a bad address, a BMP 180 or "
                "BMP "
                "085\n");
            Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
            Serial.print("        ID of 0x60 represents a BME 280.\n");
            Serial.print("        ID of 0x61 represents a BME 680.\n");
            while (1) delay(10);
        }

        /* Default settings from datasheet. */
        bmp->setSampling(
            Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
            Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
            Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
            Adafruit_BMP280::FILTER_X16,      /* Filtering. */
            Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
    }

    void loop() {
        if (deb->isValidRestart()) {
            update();
            // Serial.print(F("Temperature = "));
            // Serial.print(_temperature_C);
            // Serial.println(" *C");

            // Serial.print(F("Pressure = "));
            // Serial.print(_pressure_Pa);
            // Serial.println(" Pa");
        }
    }

    void update() {
        int tempC = bmp->readTemperature();
        int pressurePa = bmp->readPressure();
        appEnv->data->setTemperature(tempC);
        appEnv->data->setPressure(pressurePa);
    }
};

#endif /* PRESSURE_TEMP_SENSOR_HPP */