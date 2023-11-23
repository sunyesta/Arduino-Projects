// code partially sourced from example:
// https://github.com/knolleary/pubsubclient/blob/master/examples/mqtt_esp8266/mqtt_esp8266.ino

#include <Arduino.h>

#ifndef MQTT_CLIENT_HPP
#define MQTT_CLIENT_HPP

#include <ESP8266WiFi.h>
#include <PubSubclient.h>
#include <string.h>

#include "../AppEnv.hpp"
#include "../Devices/LightSensor.hpp"
#include "../Devices/MoistureSensor.hpp"
#include "../Devices/PressureTempSensor.hpp"
#include "../Devices/oled.hpp"
#include "../Modules/Debounce.hpp"
#include "../Modules/Loopable.hpp"
#include "./MyServo.hpp"

#define MSG_BUFFER_SIZE (50)
class MqttClient;

bool testBool = false;

class MyWifiClient;

static void MqttClient_callback(char* topic, byte* payload,
                                unsigned int length);

static bool stringSame(char* str0, char* str1) {
    return strcmp(str0, str1) == 0;
}

class MqttClient : public Loopable {
   private:
    char topicBuff[100];
    char payloadBuff[100];
    // Update these with values suitable for your network.
    const char* prefix = "infob3it/039/plant/";
    const char* mqtt_server = "mqtt.uu.nl";
    bool testBool = false;
    unsigned long lastMsg = 0;

    char msg[MSG_BUFFER_SIZE];
    int value = 0;

    void publishInternal(char* outTopic, char* payload) {
        sprintf(topicBuff, "%s%s%s", prefix, "out/", outTopic);
        // Serial.print("topicBuff = ");
        // Serial.println(topicBuff);
        // TODO: make payload send out that the arduino is the one making the
        // changes so that we don't have to overwrite anything
        sprintf(payloadBuff, "%s", payload);
        client->publish(topicBuff, payloadBuff);
    }

   public:
    PubSubClient* client;
    MqttClient(WiFiClient* wifiClient) : Loopable() {
        client = new PubSubClient(*wifiClient);
        client->setServer(mqtt_server, 1883);
        client->setCallback(MqttClient_callback);
    }

    void loop() { client->loop(); }

    char* getFullTopic(char* topic) {
        sprintf(topicBuff, "%s%s", prefix, topic);
        return topicBuff;
    }
    bool sameTopic(char* topic, char* incommingTopic) {
        return strcmp(getFullTopic(topic), incommingTopic) == 0;
    }

    void publish(char* outTopic, char* payload) {
        publishInternal(outTopic, payload);
    }

    void publish(char* outTopic, int payload) {
        publishInternal(outTopic, (char*)String(payload).c_str());
    }

    void publish(char* outTopic, bool payload) {
        if (payload) {
            publishInternal(outTopic, (char*)"true");
        } else {
            publishInternal(outTopic, (char*)"false");
        }
    }

    void subscribeAll() { client->subscribe("infob3it/039/plant/in/#"); }
};

static void MqttClient_callback(char* topic, byte* payload,
                                unsigned int length) {
    MqttClient* mqttClient = appEnv->devices->mqttClient;

    // set payload to char* format
    char payload_string[length + 1];
    const char* prefix = "{\"data\":";
    for (int i = 0; i < length; i++) {
        payload_string[i] = (char)payload[i];
    }
    payload_string[length] = '\0';

    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");

    if (strcmp(topic, "infob3it/039/plant/test") == 0) {
        appEnv->data->setWateringNow(true);
        testBool = !testBool;

    } else if (mqttClient->sameTopic("in/waterNow", topic)) {
        appEnv->data->setWateringNow(true);
    } else if (mqttClient->sameTopic("in/setAutomatic", topic)) {
        // TODO automatic can be set in the arduino but then the server can go
        // in and change the value if it is delayed enough
        bool automatic = stringSame(payload_string, "true");
        appEnv->data->setIsAutomatic(automatic);
    } else if (mqttClient->sameTopic("in/updateAll", topic)) {
        appEnv->devices->lightSensor->update();
        appEnv->devices->pressureTempSensor->update();
        appEnv->devices->moistureSensor->update();
        appEnv->devices->oled->runPopupScreen("updating all data");
    }
}

#endif /* MQTT_CLIENT_HPP */