#include "AppEnv.hpp"

#include <Arduino.h>

AppEnv *appEnv = new AppEnv();

#include "./Devices/AMUX.hpp"
#include "./Devices/LightSensor.hpp"
#include "./Devices/MoistureSensor.hpp"
#include "./Devices/MqttClient.hpp"
#include "./Devices/MyServo.hpp"
#include "./Devices/MyWifiClient.hpp"
#include "./Devices/OLED.hpp"
#include "./Devices/PressureTempSensor.hpp"

// #include "./Devices/Servo.hpp"

AppEnv::Data::Data() {}

int AppEnv::Data::lightLevel() { return _lightlevel; }
int AppEnv::Data::pressure() { return _pressure; }
int AppEnv::Data::temperature() { return _temperature; }
int AppEnv::Data::soilMoisture() { return _soilMoisture; }
bool AppEnv::Data::wateringNow() { return _wateringNow; }
bool AppEnv::Data::isAutomatic() { return _isAutomatic; }

void AppEnv::Data::setLightLevel(const int _lightlevel) {
    this->_lightlevel = _lightlevel;
    // Serial.println("light level!!!!!!!!!!!!!");
    appEnv->devices->mqttClient->publish((char *)"lightLevel", _lightlevel);
}
void AppEnv::Data::setPressure(const int _pressure) {
    this->_pressure = _pressure;
    appEnv->devices->mqttClient->publish((char *)"pressure", _pressure);
}
void AppEnv::Data::setTemperature(const int _temperature) {
    this->_temperature = _temperature;
    appEnv->devices->mqttClient->publish((char *)"temperature", _temperature);
}
void AppEnv::Data::setSoilMoisture(const int _soilMoisture) {
    this->_soilMoisture = _soilMoisture;
    appEnv->devices->mqttClient->publish((char *)"soilMoisture", _soilMoisture);

    appEnv->devices->servo->onNewMoistureLevel(_soilMoisture);
}
void AppEnv::Data::setWateringNow(bool _wateringNow) {
    Serial.println("setting watering");
    this->_wateringNow = _wateringNow;
    // TODO don't make this a bool
    if (_wateringNow) {
        appEnv->devices->servo->onWateringNowTrue();
        appEnv->devices->oled->runPopupScreen("watering now");
        appEnv->devices->oled->onWateringNowTrue();
    }

    appEnv->devices->mqttClient->publish((char *)"wateringNow", _wateringNow);
}
void AppEnv::Data::setIsAutomatic(bool _isAutomatic) {
    Serial.println("setting auto");
    this->_isAutomatic = _isAutomatic;
    appEnv->devices->mqttClient->publish((char *)"isAutomatic", false);
}

AppEnv ::Apps::Apps() {}

AppEnv ::Btns::Btns() {}

AppEnv ::Devices::Devices() {
    amux = new AMUX(D0, A0);
    moistureSensor = new MoistureSensor(amux, AMUX_mode::SOIL);
    lightSensor = new LightSensor(amux, AMUX_mode::LDR);
    oled = new OLED(D5, D6);
    servo = new MyServo(D4);
    pressureTempSensor = new PressureTempSensor();
    MyWifiClient *wifiClient = new MyWifiClient();
    mqttClient = new MqttClient(wifiClient->wificlient);
}

AppEnv ::Funcs::Funcs() {}

AppEnv::AppEnv() {}

void AppEnv ::setup() {
    this->config = new Config();
    this->data = new Data();
    this->apps = new Apps();
    this->btns = new Btns();
    this->devices = new Devices();
    this->funcs = new Funcs();
}
