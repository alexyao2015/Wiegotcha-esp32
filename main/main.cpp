extern "C"
{
#include "wiegotcha.h"
}

#include "wifi.hh"
#include "fs.hh"
#include "http.hh"

#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"

#include <esp_task_wdt.h>

TaskHandle_t main_task_handle = nullptr;

void main_task(void *pv_params) {
  wiegotcha_main();
}

void setup() {
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); // disable brownout detector
  setupFS();
  wifi_init_ap_station();
  start_webserver();
}

extern "C" void app_main()
{
  setup();
  xTaskCreate(main_task, "mainTask", 8192, nullptr, 1, &main_task_handle);
}
