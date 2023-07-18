#include <ESPAsyncWebServer.h>
#include "esp_camera.h"
#include "camera_index.h"
#include "Arduino.h"


#include <SPI.h>
#include <TFT_eSPI.h>
TFT_eSPI tft = TFT_eSPI();
#include <TFT_eFEX.h>
TFT_eFEX  fex = TFT_eFEX(&tft);



String filelist;
camera_fb_t * fb = NULL;
String incoming;
long current_millis;
long last_capture_millis = 0;
static esp_err_t cam_err;
static esp_err_t card_err;
char strftime_buf[64];


 #define CAMERA_MODEL_AI_THINKER
#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27
#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22



void setup() {
  Serial.begin(115200);
  

  tft.begin();
  tft.setRotation(3); 
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(5,30);
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(1);
   tft.println("        Welcome to");
  tft.setCursor(5,45);
   tft.setTextColor(TFT_BLUE);
  tft.println(" BASIS SOFT EXPO 2023");
   tft.setCursor(5,60);
    tft.setTextColor(TFT_YELLOW);
   tft.println("Smart CAR PARKING SYSTEM");
   tft.setCursor(5,80);
     tft.setTextColor(TFT_WHITE);
   tft.println("     Presented By");
   tft.setCursor(5,95);
   tft.setTextSize(1.5);
   tft.setTextColor(TFT_YELLOW);
    tft.println("BRIGHT SOLUTION LIMITED");
  delay(10000);

  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
  //init with high specs to pre-allocate larger buffers
  if (psramFound()) {
    config.frame_size = FRAMESIZE_UXGA;
    config.jpeg_quality = 10;
    config.fb_count = 2;
  } else {
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  }

  // camera init
  cam_err = esp_camera_init(&config);
  if (cam_err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", cam_err);
    return;
  }

  sensor_t * s = esp_camera_sensor_get();
  s->set_framesize(s, FRAMESIZE_QQVGA);
  s->set_vflip(s, 1);




}


void loop()
{


    fb = esp_camera_fb_get();
    fex.drawJpg((const uint8_t*)fb->buf, fb->len, 0, 6);
    esp_camera_fb_return(fb);
    fb = NULL;
  
}
