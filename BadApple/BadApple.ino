#include "Arduino.h"
#include "LittleFS.h"
#include "lvgl.h"
#include "TFT_eSPI.h"

// Adjust to your needs
#define WIDTH 80
#define HEIGHT 160
#define GIF_NAME "bad_apple_full.gif"

// Initialize lvgl buffers
static const uint16_t screenWidth = WIDTH;
static const uint16_t screenHeight = HEIGHT;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[screenHeight * screenWidth / 10];

// Initialize TFT Display
TFT_eSPI tft = TFT_eSPI(WIDTH, HEIGHT);

#define LV_DELAY(x) \
  do { \
    uint32_t t = x; \
    while (t--) { \
      lv_timer_handler(); \
      delay(1); \
    } \
  } while (0);

// Setup LittleFS callbacks
static void * fs_open(lv_fs_drv_t * drv, const char * path, lv_fs_mode_t mode) {
    const char * flags = (mode == LV_FS_MODE_WR) ? "w" : "r";
    String fs_path = "/" + String(path); 
    
    File f = LittleFS.open(fs_path, flags);
    if (!f || f.isDirectory()) {
        return NULL;
    }
    return (void *)new File(f);
}

static lv_fs_res_t fs_close(lv_fs_drv_t * drv, void * file_p) {
    File * fp = (File *)file_p;
    fp->close();
    delete fp;
    return LV_FS_RES_OK;
}

static lv_fs_res_t fs_read(lv_fs_drv_t * drv, void * file_p, void * buf, uint32_t btr, uint32_t * br) {
    File * fp = (File *)file_p;
    *br = fp->read((uint8_t *)buf, btr);
    return LV_FS_RES_OK;
}

static lv_fs_res_t fs_seek(lv_fs_drv_t * drv, void * file_p, uint32_t pos, lv_fs_whence_t whence) {
    File * fp = (File *)file_p;
    SeekMode mode = SeekSet;
    if (whence == LV_FS_SEEK_CUR) mode = SeekCur;
    else if (whence == LV_FS_SEEK_END) mode = SeekEnd;
    
    if (fp->seek(pos, mode)) {
        return LV_FS_RES_OK;
    }
    return LV_FS_RES_UNKNOWN;
}

static lv_fs_res_t fs_tell(lv_fs_drv_t * drv, void * file_p, uint32_t * pos_p) {
    File * fp = (File *)file_p;
    *pos_p = fp->position();
    return LV_FS_RES_OK;
}

// Setup lvgl callbacks
void disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p) {
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);

  tft.startWrite();
  tft.setAddrWindow(area->x1, area->y1, w, h);
  tft.pushColors((uint16_t *)color_p, w * h, true);
  tft.endWrite();

  lv_disp_flush_ready(disp);
}

// Main
void setup(){
  Serial.begin(115200);
  delay(1000);

  // Initialize LittleFS
  if (!LittleFS.begin(false)) {
    Serial.println(F("[!] LittleFS Mount Failed! Check partition scheme settings"));
    return;
  }
  Serial.println(F("[*] LittleFS Mounted Successfully"));

  // Check for gif file
  if (LittleFS.exists("/"GIF_NAME)) {
    Serial.println(F("[*] Found "GIF_NAME" asset on storage layer"));
  } else {
    Serial.println(F("[!] "GIF_NAME" NOT found in file system roots"));
  }

  //Initialize lvgl
  lv_init();
  tft.begin();
  tft.setRotation(1); // Rotate the screen to match the ESP32S3-Pocket-Dongle-S3 display

  // Initialize the display buffer
  lv_disp_draw_buf_init(&draw_buf, buf, NULL, screenHeight * screenWidth / 10);

  // Initialize the display driver
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);

  disp_drv.hor_res = HEIGHT;
  disp_drv.ver_res = WIDTH;
  disp_drv.flush_cb = disp_flush;
  disp_drv.draw_buf = &draw_buf;  
  lv_disp_drv_register(&disp_drv);

  // Initialize the LittleFS driver
  static lv_fs_drv_t fs_drv;
  lv_fs_drv_init(&fs_drv);
  fs_drv.letter = 'F';
  fs_drv.open_cb = fs_open;
  fs_drv.close_cb = fs_close;
  fs_drv.read_cb = fs_read;
  fs_drv.seek_cb = fs_seek;
  fs_drv.tell_cb = fs_tell;
  lv_fs_drv_register(&fs_drv);

  // Prepare the style
  static lv_style_t style;  
  lv_style_init(&style);
  lv_style_set_bg_color(&style, lv_color_black());
  lv_obj_add_style(lv_scr_act(), &style, 0);

  // Load the gif
  lv_obj_t *img = lv_gif_create(lv_scr_act());
  lv_obj_center(img);
  lv_gif_set_src(img, "F:/"GIF_NAME);
  delay(10);
  Serial.println(F("[*] Loading "GIF_NAME));

  // Have fun! シ
}

void loop() {
    // Keep the animation running
    lv_timer_handler();
    delay(1);
}
