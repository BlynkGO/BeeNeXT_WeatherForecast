#include <BlynkGOv3.h>
#include "02_project.h"

// BlynkGO Emma-II ให้เปิด 
//   #define BLYNKGO_USE_BEENEXT   1 
// ใน blynkgo_config.h ด้วย

// เปลี่ยน WEATHER_API ได้ที่ https://open-meteo.com/en/docs  10,000 API ต่อวัน (นาที นึง ยิงได้ราว 6 ครั้ง)

#define WEATHER_API   "https://api.open-meteo.com/v1/forecast?latitude=%.7f&longitude=%.7f&hourly=temperature_2m,relative_humidity_2m&timezone=Asia%%2FBangkok&forecast_days=1"
#define LATITUDE      13.7278956
#define LONGITUDE     100.5241235


GWiFiManager wifi_manager;

void setup() {
  Serial.begin(9600); Serial.println();
  BlynkGO.begin();

  wifi_manager.align(ALIGN_TOP_RIGHT,-10);
}

void loop() {
  BlynkGO.update();
}

WIFI_CONNECTED(){
  String web_api = StringX::printf( WEATHER_API, LATITUDE, LONGITUDE);
  WEATHER::GET(10000, web_api, [](String json){
    Serial.println(json);
  });
}
