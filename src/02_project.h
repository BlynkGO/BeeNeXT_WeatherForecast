#pragma once

#include <BlynkGOv3.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>


namespace WEATHER {
  void GET(uint32_t interval, String web_api, void (*fn)(String response));
}
