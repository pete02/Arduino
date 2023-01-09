#ifndef netti_h
#define netti_h

#if (ARDUINO >= 100)
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#include <ESP8266WiFi.h>
#pragma once

class netti_{
    //constructor
    private:
        netti_()=default;
    public:
        static netti_ &getInstance();

        netti_(const netti_ &)=delete;
        netti_ &operator=(const netti_ &)=delete;
    public:
    //methods
    void SetupWifi();
    void ReconnectWifi();
    void SetupMobile();
    void ReconnectMobile();
    void write(char* w);
    void ReconnectMqtt(char* sub);
    void mqttpublish(char* sub, char* msg);
    void Mqttsub(char* sub);
    void TestWifi();
    WiFiClient retClient();
    std::unordered_map<char* ,byte*> payloadret();
};
extern netti_ &netti;
#endif