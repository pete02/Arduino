
void seconddisp(){

  pinger.OnReceive([](const PingerResponse& response)
  {
    if (response.ReceivedResponse)
    {
      server_on=1;
      Serial.printf(
        "Reply from %s: time=%lums TTL=%d\n",
        response.DestIPAddress.toString().c_str(),
        response.ResponseTime,
        response.TimeToLive);
    }
    else
    {
      server_on=0;
      Serial.printf("Request timed out.\n");
    }

    // Return true to continue the ping sequence.
    // If current event returns false, the ping sequence is interrupted.
    return false;
  });

  if(tft.getTouch(&x, &y)){
    Serial.println("touched");
    Serial.println(x);
      if(x<200 &&page==1){
        page++;
      }else{
        if(x>200 && page==2){
        page--;
        }
      }
    }
  if(secdisp==0){
    tft.fillScreen(darkblue);
   tft.setCursor(20, 0, 2);
    tft.setTextColor(TFT_RED,darkblue);  tft.setTextSize(2);
    secdisp++;
  }
  
  if(millis()-no2>=1000){
    if(pinger.Ping(IPAddress(192,168,1,49)) == true){
      Serial.println("second screen");
      serverfetch();
      princontainers();
      server_data();
      no2=millis();
    }else server_on=0;
  }
}


void server_data(){
  if(server_on==1){
    tft.setTextColor(TFT_GREEN);
  }else tft.setTextColor(TFT_RED);
  tft.setCursor(180,10,2);
  tft.print("Server");
  tft.setTextColor(TFT_WHITE,darkblue);
  tft.setCursor(10,40,1);
  tft.print("CPU:");
  tft.print(server.cpu,1);
  tft.print("%");
  tft.setCursor(10,60,1);
  tft.print("CPU temps:");
  tft.print(server.temp,1);
  tft.print("C");
  
  tft.setCursor(220,40,1);
  tft.print("Memory usage:");
  tft.print(server.mem);
  tft.print("%");
  tft.setCursor(220,60,1);
  tft.print("Disk:");
  tft.print(server.disk,1);
  tft.print("%");
}




void princontainers(){
  if(server.portainer==0){
    tft.setTextColor(TFT_RED);
  }else tft.setTextColor(TFT_GREEN);
   tft.setCursor(10,110,1);
   tft.print("portainer");
   
   if(server.traefik==0){
    tft.setTextColor(TFT_RED);
  }else tft.setTextColor(TFT_GREEN);
   tft.setCursor(150,110,1);
   tft.print("traefik");
   
   if(server.kirja_b==0 or server.kirja_f==0){
    tft.setTextColor(TFT_RED);
  }else tft.setTextColor(TFT_GREEN);
   tft.setCursor(270,110,1);
   tft.print("bookraider");
   
  if(server.codes==0){
    tft.setTextColor(TFT_RED);
  }else tft.setTextColor(TFT_GREEN);
   tft.setCursor(10,130,1);
   tft.print("codeserver");
  
   tft.setCursor(150,130,1);
   if(server.jellyfin==0){
    tft.setTextColor(TFT_RED);
  }else tft.setTextColor(TFT_GREEN);
   tft.print("jellyfin");

   if(server.grafana==0){
    tft.setTextColor(TFT_RED);
  }else tft.setTextColor(TFT_GREEN);
   tft.setCursor(280,130,1);
   tft.print("grafana");
   
  if(server.selenium==0){
    tft.setTextColor(TFT_RED);
  }else tft.setTextColor(TFT_GREEN);
   tft.setCursor(10,150,1);
   tft.print("selenium");
   
   if(server.prometheus==0){
    tft.setTextColor(TFT_RED);
  }else tft.setTextColor(TFT_GREEN);
   tft.setCursor(150,150,1);
   tft.print("prometheus");
   
   if(server.homeassistant==0){
    tft.setTextColor(TFT_RED);
  }else tft.setTextColor(TFT_GREEN);
   tft.setCursor(280,150,1);
   tft.print("homeassistant");
   
  if(server.zigbee==0){
    tft.setTextColor(TFT_RED);
  }else tft.setTextColor(TFT_GREEN);
   tft.setCursor(10,170,1);
   tft.print("zigbee");
   
   if(server.influxdb==0){
    tft.setTextColor(TFT_RED);
  }else tft.setTextColor(TFT_GREEN);
   tft.setCursor(150,170,1);
   tft.print("influxdb");
   
   if(server.watchtower==0){
    tft.setTextColor(TFT_RED);
  }else tft.setTextColor(TFT_GREEN);
   tft.setCursor(280,170,1);
   tft.print("watchtower");
}
