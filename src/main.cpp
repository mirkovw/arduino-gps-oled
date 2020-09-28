#include <TinyGPS++.h>
#include <U8g2lib.h>

//The display
U8G2_SH1106_128X64_NONAME_F_4W_SW_SPI u8g2(U8G2_R0, /* clk =*/ 4, /* mosi=*/ 3, /* cs=*/ 0, /* dc=*/1 , /* reset=*/ 2);

// The TinyGPS++ object
TinyGPSPlus gps;

//Custom HDOP var to determine accuracy
TinyGPSCustom hdop(gps, "GPGGA", 8); // $GNGGA sentence, 16th element

void setup() 
{
  Serial.begin(9600);
  Serial1.begin(9600);

  
  u8g2.begin();
  u8g2.setFont(u8g2_font_profont10_mf); 
  
  u8g2.clearBuffer();
  u8g2.drawStr(0,6,"Initializing"); // write something to the internal memory
  u8g2.sendBuffer();
}

void loop() 
{
  
  // Every time anything is updated, print everything.
  if (atof(hdop.value()) < 2 && gps.location.isValid() && gps.date.isValid() && gps.time.isValid()) {
    Serial.println("Accurate GPS position lock, see data below");
    
    Serial.print(F("  HDOP=")); 
    Serial.println(hdop.value()); 
    
    Serial.print(F("  Location: "));
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.println(gps.location.lng(), 6);
    
    Serial.print(F("  Date/Time: "));
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
    
    Serial.print(F(" "));
    
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(F(":"));
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(F(":"));
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(F("."));
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.print(gps.time.centisecond());
    
    Serial.println((" "));
    Serial.println((" "));

    //char* longitude = char*(gps.location.lat());
    //const char[] = 
    
    u8g2.clearBuffer();
    u8g2.drawStr(0,6,"Accurate GPS position");
    //u8g2.drawStr(0,12, gps.location.lat());
    //u8g2.drawStr(0,12, String(gps.location.lat(), 6)); 
    //u8g2.drawStr(0,18, String(gps.location.lng(), 6));
    u8g2.sendBuffer();

    delay(1000);
    
  }
  
  else {
    Serial.println("Waiting for accurate GPS pos lock...");
    
    Serial.print("  HDOP Value: ");
    Serial.println(hdop.value());
    
    Serial.print("  GPS Position Valid: ");
    Serial.println(gps.location.isValid());
    
    Serial.print("  GPS Date Valid: ");
    Serial.println(gps.date.isValid());
    
    Serial.print("  GPS Time Valid: ");
    Serial.println(gps.time.isValid());
    
    Serial.println("");
    Serial.println("");


    u8g2.clearBuffer();
    u8g2.drawStr(0,6,"Waiting for Accurate GPS");
    u8g2.sendBuffer();

    

    delay(1000);
  }

  while (Serial1.available() > 0) {
    gps.encode(Serial1.read());
  }
}