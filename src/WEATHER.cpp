#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "02_project.h"

String _web_api;
void (*_fn_weather_cb)(String response);

void WEATHER::GET(uint32_t interval, String web_api, void (*fn)(String response)){
  _web_api = web_api;
  _fn_weather_cb = fn;

  static SoftTimer timer;
  timer.setInterval(interval, [](){
    if(!WiFi.isConnected()) return;

    std::unique_ptr<WiFiClientSecure>client (new WiFiClientSecure);
    if(client) {
      client->setInsecure();  // สำหรับ WiFiClientSecure  443 แบบไม่ต้องเช็ค secure
      {
        HTTPClient https;
        https.begin(*client, _web_api);
        Serial.print("[HTTPClient] GET : "); Serial.println(_web_api);
        int http_code = https.GET();
        // Serial.println(http_code);
        if( http_code == 200) {
          String payload = https.getString();
          _fn_weather_cb(payload);
        }
      }
    }else{
      Serial.println("[HTTPClient] เม็มไม่พอจอง");
    }
  }, true);  // true คือเริ่มทำงานเลยแต่แรก ของ timer
}
