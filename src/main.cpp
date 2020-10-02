#include <TinyGPS++.h>
#include <U8g2lib.h>

//The display
U8G2_SH1106_128X64_NONAME_F_4W_SW_SPI u8g2(U8G2_R0, /* clk =*/ 4, /* mosi=*/ 3, /* cs=*/ 0, /* dc=*/1 , /* reset=*/ 2);

// The TinyGPS++ object
TinyGPSPlus gps;

//Custom HDOP var to determine accuracy
TinyGPSCustom hdop(gps, "GNGGA", 8); // $GNGGA sentence, 16th element

//OLED display standard coords
int c1 = 0, c2 = 40; 
int lineHeight = 9;
int startHeight = 6;
int l1 = startHeight; 
int l2 = startHeight + lineHeight * 1; 
int l3 = startHeight + lineHeight * 2; 
int l4 = startHeight + lineHeight * 3; 
int l5 = startHeight + lineHeight * 4; 
int l6 = startHeight + lineHeight * 5;
int l7 = startHeight + lineHeight * 6;
int l8 = startHeight + lineHeight * 7;
int l9 = startHeight + lineHeight * 8;

void setup() 
{
  Serial.begin(9600);
  Serial1.begin(9600);

  u8g2.begin();
  u8g2.setFont(u8g2_font_5x8_mf); 
  
  u8g2.clearBuffer();
  u8g2.drawStr(0,6,"Initializing");
  u8g2.sendBuffer();
}

void displayData() {

  u8g2.clearBuffer();

  if (atof(hdop.value()) < 2 && gps.location.isValid() && gps.date.isValid() && gps.time.isValid()) {
    u8g2.setCursor(c1, l1); u8g2.print("GPS Status: READY");
  }

  else {
    u8g2.setCursor(c1, l1); u8g2.print("GPS Status: WAITING");
  }

  //Column 1
  u8g2.setCursor(c1, l3); u8g2.print("HDOP: ");
  u8g2.setCursor(c1, l4); u8g2.print("Lat:");
  u8g2.setCursor(c1, l5); u8g2.print("Long:");
  u8g2.setCursor(c1, l6); u8g2.print("Date:");
  u8g2.setCursor(c1, l7); u8g2.print("Time:");


  //Column 2

  //HDOP
  u8g2.setCursor(c2, l3); 
  u8g2.print(atof(hdop.value()) < 10 ? hdop.value() : "N/A");

  //Latitude
  u8g2.setCursor(c2, l4); 
  u8g2.print(gps.location.isValid() ? gps.location.lat() : "N/A");

  //Longitude
  if (gps.location.isValid()) {
    u8g2.setCursor(c2, l4); u8g2.print(gps.location.lat(), 6);
    u8g2.setCursor(c2, l5); u8g2.print(gps.location.lng(), 6);
  }

  else {
    u8g2.setCursor(c2, l4); u8g2.print("N/A");
    u8g2.setCursor(c2, l5); u8g2.print("N/A");
  }



  
  
  //Date
  if (gps.date.isValid()) {
    u8g2.setCursor(c2, l6); u8g2.print("29/09/2020");
  }

  else {
    u8g2.setCursor(c2, l6); u8g2.print("N/A");
  }
  
  
  //Time
  u8g2.setCursor(c2, l7); 
  u8g2.print(gps.time.isValid() ? "12:15 UTC" : "N/A");
  
  u8g2.sendBuffer();
  
}

void loop() {

  displayData();

  while (Serial1.available() > 0) {
    gps.encode(Serial1.read());
    
  }
  
  delay(1000);


  // Every time anything is updated, print everything.
  //if (atof(hdop.value()) < 2 && gps.location.isValid() && gps.date.isValid() && gps.time.isValid()) {

    // u8g2.clearBuffer();

    // u8g2.setCursor(c1, l1); u8g2.print("Wait for GPS...");

    // u8g2.setCursor(c1, l3); u8g2.print("HDOP: ");
    // u8g2.setCursor(c2, l3); u8g2.print("0.885");

    // u8g2.setCursor(c1, l4); u8g2.print("Lat:");
    // u8g2.setCursor(c2, l4); u8g2.print(gps.location.lat(), 6);

    // u8g2.setCursor(c1, l5); u8g2.print("Long:");
    // u8g2.setCursor(c2, l5); u8g2.print(gps.location.lng(), 6);

    // u8g2.setCursor(c1, l6); u8g2.print("Date Time:");
    // u8g2.setCursor(c2, l6); u8g2.print("29/09/2020 12:15 UTC");
    
    // u8g2.sendBuffer();


    
    // Serial.println("Accurate GPS position lock, see data below");
    
    // Serial.print(F("  HDOP=")); 
    // Serial.println(hdop.value()); 
    
    // Serial.print(F("  Location: "));
    // Serial.print(gps.location.lat(), 6);
    // Serial.print(F(","));
    // Serial.println(gps.location.lng(), 6);
    
    // Serial.print(F("  Date/Time: "));
    // Serial.print(gps.date.month());
    // Serial.print(F("/"));
    // Serial.print(gps.date.day());
    // Serial.print(F("/"));
    // Serial.print(gps.date.year());
    
    // Serial.print(F(" "));


    // if (gps.time.hour() < 10) Serial.print(F("0"));
    // Serial.print(gps.time.hour());
    // Serial.print(F(":"));
    // if (gps.time.minute() < 10) Serial.print(F("0"));
    // Serial.print(gps.time.minute());
    // Serial.print(F(":"));
    // if (gps.time.second() < 10) Serial.print(F("0"));
    // Serial.print(gps.time.second());
    // Serial.print(F("."));
    // if (gps.time.centisecond() < 10) Serial.print(F("0"));
    // Serial.print(gps.time.centisecond());
    
    // Serial.println((" "));
    // Serial.println((" "));

    

  //   delay(1000);
    
  // }
  
  // else {
  //   Serial.println("Waiting for accurate GPS pos lock...");
    
  //   Serial.print("  HDOP Value: ");
  //   Serial.println(hdop.value());
    
  //   Serial.print("  GPS Position Valid: ");
  //   Serial.println(gps.location.isValid());
    
  //   Serial.print("  GPS Date Valid: ");
  //   Serial.println(gps.date.isValid());
    
  //   Serial.print("  GPS Time Valid: ");
  //   Serial.println(gps.time.isValid());
    
  //   Serial.println("");
  //   Serial.println("");


  //   u8g2.clearBuffer();
  //   u8g2.drawStr(0,6,"Waiting for Accurate GPS");
  //   u8g2.sendBuffer();

    

  //   delay(1000);
  // }

  
}