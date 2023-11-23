#include <Arduino.h>

#ifndef WIFI_HPP
#define WIFI_HPP

#include <ESP8266WiFi.h>

#include "../AppEnv.hpp"
#include "../Modules/Debounce.hpp"
#include "../Modules/Loopable.hpp"
#include "./MqttClient.hpp"
class MyWifiClient : public Loopable {
   private:
    const char* ssid = "Party time at home";
    const char* password = "studiomary";

    void setup_wifi() {
        delay(10);
        // We start by connecting to a WiFi network
        Serial.println();
        Serial.print("Connecting to ");
        Serial.println(ssid);

        WiFi.mode(WIFI_STA);
        WiFi.begin(ssid, password);

        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");
        }

        randomSeed(micros());

        Serial.println("");
        Serial.println("WiFi connected");
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());
    }

    boolean reconnect() {
        Serial.print("Attempting MQTT connection...");
        // Create a random wificlient ID
        String clientId = "ESP8266Client-";
        clientId += String(random(0xffff), HEX);
        if (appEnv->devices->mqttClient->client->connect(clientId.c_str(),
                                                         "*****", "*****")) {
            // Once connected, publish an announcement...
            // wificlient->publish("outTopic", "hello world");
            // // ... and resubscribe
            // wificlient->subscribe("infob3it/039/plant/test");
            appEnv->devices->mqttClient->subscribeAll();
        }
        return wificlient->connected();
    }
    void handleConnection() {
        static Debounce* dt = new Debounce(5000);
        if (!wificlient->connected()) {
            if (dt->isValidOnce()) {
                // Attempt to reconnect
                if (reconnect()) {
                    Serial.println("connected");
                } else {
                    Serial.println("failed to connect!");
                }
                dt->start();
            }
        }
    }

   public:
    WiFiClient* wificlient;
    MyWifiClient() {
        wificlient = new WiFiClient();
        setup_wifi();
    }
    void loop() { handleConnection(); }
};

#endif /* WIFI_HPP */