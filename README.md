# Bad Apple on ESP32S3-Pocket-Dongle-S3

From the [official repository]() of the ESP32S3-Pocket-Dongle-S3, which you can [buy it here](https://aliexpress.com/item/1005009024098181.html), I displayed on the 0.96 inch display the famous TouHou video "Bad Apple".

# Table of Contents

- [Prerequisites](#Prerequisites)
- [Setup](#Setup)
  - [Setting up Arduino IDE](#Setting-up-Arduino-IDE)
  - [Preparing the Scketch](Preparing-the-Sketch)
  - [Uploading-the-files-to-the-memory](#Uploading-the-files-to-the-memory)

# Prerequisites

- Arduino IDE >= 2.3.2
- LittleFS == 2.0.0
- FS == 2.0.0
- lvgl == 8.3.7
- TFT_eSPI == 2.5.0
- SPI == 2.0.0
- SPIFFS == 2.0.0

> [!WARNING]
> Do **not in any case** update the libraries upon opening the ArduinoIDE. They will mess up the whole project. Stick with the version described up here.

# Setup

## Setting up Arduino IDE

You can set them up by copying the `Arduino/libraries` folder into your Arduino libraries. If you do not know where is located, look it up online.

Next, you have to install the esp32 module board for ArduinoIDE.

1. Go to `File` -> `Preferences`
2. Add `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json` to _Additional Board Manager URLs_
3. Go to `Tools` -> `Board` -> `Boards Manager`
4. Search for "esp32" and install the version `2.0.14`

We also need the LittleFS Uploader so we can flash our file to the ESP32S3 memory.

1. Go to [this link](https://github.com/earlephilhower/arduino-littlefs-upload) and download the `.vsix` file from the Releases
2. Go to your home folder and inside `.arduinoIDE` (eg. /home/User/.arduinoIDE), put the `.vsix` file in the plugins folder. If missing, create it.

## Preparing the Scketch

After installing the libraries, we need to set up the sketch.

1. On the toolbar on the top left, go to `Tools` -> `Board` -> `esp32` -> `ESP32S3 Dev Module`
2. Go to `Tools` and now we need to set some values:
   - `USB CDC On Boot`: "Enabled"
   - `Flash Mode`: "DIO 80MHz"
   - `Flash Size`: "16MB (128Mb)"
   - `Partition Scheme`: "16MB Flash (3MB APP/9.9MB FATFS)"
   - `PSRAM`: "OPI PSRAM"
   - `Upload Speed`: "115200"

## Uploading the files to the memory

Open the command palette with `Ctrl` + `Shift` + `P` and search for `Upload Little FS to Pico/ESP8266/ESP32`.
Once it finishes, you can compile the scketch and flash it to the ESP.

# Sources

- Original [ESP32S3-Pocket-Dongle-S3 repo](https://github.com/ronenkr/Pocket-Dongle-S3)
- Aliexpress [link to the module](https://aliexpress.com/item/1005009024098181.html)
- LittleFS Uploader [repo](https://github.com/earlephilhower/arduino-littlefs-upload)
- Tutorial on installing ArduinoIDE plugins, [link](https://randomnerdtutorials.com/arduino-ide-2-install-esp32-littlefs/#introduction)
