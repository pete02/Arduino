void outinit(){
  tft.setCursor(130,30,2);
  tft.print("out");
  tft.setCursor(10,80,1);
  tft.print("ylin:");
  tft.setCursor(10,100,1);
  tft.print("alin:");
   tft.setCursor(10,60,1);
  tft.print("temp:");
  tft.setCursor(155,60,1);
  tft.print("hum:");
  tft.setCursor(155,100,1);
  tft.print("puuskat:");
  tft.setCursor(155,80,1);
  tft.print("tuulee:");
}
int prev=-1;
 float prev_Current_in=-1;
float prev_Current_out =-1;
float prev_in_hum = -1;
float prev_out_hum = -1;
float prev_wind_avg = -1;
float prev_wind_highest = -1;
float prev_Highest = -1;
float prev_Lowest = -1;

void temp_reset(){
  fisrd=0;
  prev=-1;
  prev_Current_in=-1;
  prev_Current_out =-1;
  prev_in_hum = -1;
  prev_out_hum = -1;
  prev_wind_avg = -1;
  prev_wind_highest = -1;
  prev_Highest = -1;
  prev_Lowest = -1;
}
void out(){
 if(prev_Current_out!=Current_out){
  prev_Current_out=Current_out;
  tft.setCursor(70,60,1);
  tft.print("      ");
  tft.setCursor(70,60,1);
  tft.print(Current_out,1);
  tft.print("C");
 }
 
 if(prev_out_hum!=out_hum){
  prev_out_hum=out_hum;
  tft.setCursor(205,60,1);
  tft.print("     ");
  tft.setCursor(205,60,1);
  tft.print(out_hum,1);
  tft.print("%");
 }
 
  if(prev_Highest!=Highest){
    prev_Highest=Highest;
    tft.setCursor(70,80,1);
    tft.print("      ");
    tft.setCursor(70,80,1);
    tft.print(Highest,1);
    tft.print("C");
  }
  
  if(prev_wind_avg!=wind_avg){
    prev_wind_avg=wind_avg;
    tft.setCursor(245,80,1);
    tft.print("       ");
    tft.setCursor(245,80,1);
    tft.print(wind_avg,1);
    tft.print("m/s");
  }
  if(prev_Lowest!=Lowest){
    prev_Lowest=Lowest;
    tft.setCursor(70,100,1);
    tft.print("      ");
    tft.setCursor(70,100,1);
    tft.print(Lowest,1);
    tft.print("C");
  }
  if(prev_wind_highest!=wind_highest){
    prev_wind_highest=wind_highest;
    tft.setCursor(255,100,1);
    tft.print("       ");
    tft.setCursor(255,100,1);
    tft.print(wind_highest,1);
    tft.print("m/s");
  }
}

void in(){
  tft.setCursor(360,30,2);
  tft.print("in");
  tft.setCursor(340,60,1);
  tft.print("temp:");
  tft.print(Current_in,1);
  tft.print("C");
  tft.setCursor(340,80,1);
  tft.print("hum:");
  tft.print(in_hum,1);
  tft.print("%");
}

void pred(){
  if(prev!=ennuste[0].tim){
    prev=ennuste[0].tim;
  for(int i=0;i<6;i++){
    tft.setCursor((80*i+10),140,1);
    tft.print(pv[ennuste[i].d]);  
    tft.setCursor((80*i+10),170,1);
    if(ennuste[i].tim<10){
      tft.print("0");
      tft.print(ennuste[i].tim);
      tft.print(":00");
    }else{
      tft.print(ennuste[i].tim);
      tft.print(":00");
    }
    tft.setCursor((80*i+10),200,1);
    tft.print("    ");
    tft.setCursor((80*i+10),200,1);
    tft.print(ennuste[i].temp);
    tft.print("C");
    tft.setCursor((80*i+10),220,1);
    tft.print("  ");
    tft.setCursor((80*i+10),220,1);
    tft.print(ennuste[i].rain_p);
    tft.print("%");
    tft.setCursor((80*i+10),240,1);
    tft.print("    ");
    tft.setCursor((80*i+10),240,1);
    tft.print(ennuste[i].rain_a);
    tft.print("mm");
  }
  }
}
