
void firstdisp(){
  if(fisrd==0){
    tft.fillScreen(darkblue);
   tft.setCursor(20, 0, 2);
    tft.setTextColor(TFT_WHITE,darkblue);  tft.setTextSize(2);
    outinit();
    clo();
    fisrd++;
  }
  if(millis()-no>=1000){
    clo();
    JsonFetch();
    out();
    in();
   pred();
    no=millis();
  }
}
