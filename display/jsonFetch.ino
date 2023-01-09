void JsonFetch() {
  Serial.print("[HTTP] begin...\n");
  if (http.begin(clinet, "http://192.168.0.100:1880/tieto")) {  // HTTP


    // start connection and send HTTP header
    int httpCode = http.GET();

    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled


      // file found at server
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
        String payload = http.getString();
        StaticJsonDocument<6144> doc;

        DeserializationError error = deserializeJson(doc, payload);

        if (error) {
          Serial.print(F("deserializeJson() failed: "));
          Serial.println(error.f_str());

          return;
        }
        int i=0;
        for (JsonPair ennuste_item : doc["ennuste"].as<JsonObject>()) {
          const char* ennuste_item_key = ennuste_item.key().c_str(); // "0", "1", "2", "3", "4", "5", "6", "7", ...
          
          int ennuste_item_value_day = ennuste_item.value()["day"]; // 0, 0, 1, 1, 1, 1, 1, 1, 1, 1
          int ennuste_item_value_time = ennuste_item.value()["time"]; // 18, 21, 0, 3, 6, 9, 12, 15, 18, 21
          const char* ennuste_item_value_temp = ennuste_item.value()["temp"]; // "11.94", "9.56", "6.92", "5.33", ...
          const char* ennuste_item_value_sadetod = ennuste_item.value()["sadetod"]; // "0.0", "0.0", "0.0", "0.0", ...
          const char* ennuste_item_value_sadem = ennuste_item.value()["sadem"]; // "0.0", "0.0", "0.0", "0.0", ...
          ennuste[i].d=ennuste_item_value_day;
          ennuste[i].tim=ennuste_item_value_time;
          ennuste[i].temp=ennuste_item_value_temp;
          ennuste[i].rain_p=ennuste_item_value_sadetod;
          ennuste[i].rain_a=ennuste_item_value_sadem;
          i++;


        }


        Current_in = doc["Current_in"];
        Current_out = doc["Current_out"];
        in_hum = doc["in_hum"];
        out_hum = doc["out_hum"];
        wind_avg = doc["wind_avg"];
        wind_highest = doc["wind_highest"];
        Highest = doc["Highest"];
        Lowest = doc["Lowest"];
        onn = doc["on"];;
      }
    } else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  } else {
    Serial.printf("[HTTP} Unable to connect\n");
  }
}


void sleepfetch(){
  if (http.begin(clinet, "http://192.168.0.100:1880/server")) {  // HTTP


    // start connection and send HTTP header
    int httpCode = http.GET();

    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled

      // file found at server
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
        String payload = http.getString();
        StaticJsonDocument<6144> doc;

        DeserializationError error = deserializeJson(doc, payload);

        if (error) {
          Serial.print(F("deserializeJson() failed: "));
          Serial.println(error.f_str());

          return;
        }

        onn = doc["on"];
      }
    } else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  } else {
    Serial.printf("[HTTP} Unable to connect\n");
  }
}

void serverfetch(){
  Serial.print("[HTTP] begin...\n");
  if (http.begin(clinet, "http://192.168.0.100:1880/server")) {  // HTTP


    // start connection and send HTTP header
    int httpCode = http.GET();

    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled

      // file found at server
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
        String payload = http.getString();
        StaticJsonDocument<6144> doc;

        DeserializationError error = deserializeJson(doc, payload);

        if (error) {
          Serial.print(F("deserializeJson() failed: "));
          Serial.println(error.f_str());

          return;
        }

        server.cpu = doc["cpu"];
        server.temp = doc["temp"];
        server.mem = doc["memus"];
        server.disk = doc["disk"];
        server.portainer = doc["portainer"];
        server.traefik = doc["traefik"];
        server.kirja_b = doc["kirja_b"];
        server.kirja_f = doc["kirja_f"];
        server.selenium=doc["selenium"];
        server.codes=doc["codes"];
        server.jellyfin=doc["jellyfin"];
        server.homeassistant=doc["homeassistant"];
        server.prometheus=doc["prometheus"];
        server.influxdb=doc["influxdb"];
        server.zigbee=doc["zigbee"];
        server.watchtower=doc["watchtower"];
        server.grafana=doc["grafana"];
        onn = doc["on"];
      }
    } else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  } else {
    Serial.printf("[HTTP} Unable to connect\n");
  }
}


void change(){
  if (http.begin(clinet, "http://192.168.0.100:1880/change")) {  // HTTP
  Serial.println("changing");
    // start connection and send HTTP header
    int httpCode = http.GET();

    // httpCode will be negative on error
    if (httpCode > 0) {
      http.end();
    }
  }
}
