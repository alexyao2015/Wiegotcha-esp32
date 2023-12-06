extern "C"
{
#include "wiegotcha.h"
}

#include "wifi.hh"
#include "fs.hh"
#include "http.hh"

extern "C" void app_main()
{
  setupFS();
  wifi_init_ap_station();
  start_webserver();
  wiegotcha_main();
}