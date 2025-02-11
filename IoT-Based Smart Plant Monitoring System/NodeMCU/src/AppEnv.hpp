

#ifndef APP_ENV_HPP
#define APP_ENV_HPP

#include <Arduino.h>

#define Pin uint8_t

class MoistureSensor;
class PressureTempSensor;
class OLED;
class MyServo;
class AMUX;
class LightSensor;
class MqttClient;

class AppEnv {
   public:
    // everything in here should be static const
    class Config {
       public:
    };
    class Data {
       private:
        int _lightlevel = -1;
        int _pressure = -1;
        int _temperature = -1;
        int _soilMoisture = -1;
        bool _wateringNow = false;
        bool _isAutomatic = true;

       public:
        Data();
        int lightLevel();
        int pressure();
        int soilMoisture();
        int temperature();
        bool wateringNow();
        bool isAutomatic();

        void setLightLevel(int);
        void setPressure(int);
        void setTemperature(int);
        void setSoilMoisture(int);
        void setWateringNow(bool);
        void setIsAutomatic(bool);
    };

    class Apps {
       public:
        Apps();
    };

    class Devices {
       public:
        Devices();
        AMUX *amux;
        MoistureSensor *moistureSensor;
        PressureTempSensor *pressureTempSensor;
        OLED *oled;
        MyServo *servo;
        LightSensor *lightSensor;
        MqttClient *mqttClient;
    };

    class Btns {
       public:
        Btns();
    };

    class Funcs {
       public:
        Funcs();
    };

    AppEnv();
    void setup();

    Config *config;
    Data *data;
    Apps *apps;
    Btns *btns;
    Devices *devices;
    Funcs *funcs;
};

extern AppEnv *appEnv;

#endif /* APP_ENV_HPP */
