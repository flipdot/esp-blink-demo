#define FASTLED_ALLOW_INTERRUPTS 0

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <FastLED.h>

#define NUM_LEDS 300
#define NUM_DOTS 5
#define TAIL_LENGTH 10
#define DATA_PIN D3
#define PIN D3
#define BAUDRATE 115200

#include <ESP8266WiFi.h>

int state;
int currentLED;
int dots[NUM_DOTS];

// Adafruit_NeoPixel strip = Adafruit_NeoPixel(280, PIN, NEO_GRB + NEO_KHZ800);
CHSV hsvs[NUM_LEDS];
CRGB leds[NUM_LEDS];

void animation() {
    static uint8_t k = 0;

    for (int i=0; i<NUM_LEDS; i++) {
        leds[i] = CHSV(0, 0, 0);
    }


    for (int i=0; i<NUM_DOTS; i++) {
        int pos = dots[i];
        int dot_color = int((float(i) / float(NUM_DOTS)) * 255);
        for (int j=0; j<TAIL_LENGTH; j++) {
            int brightness = 255 - (j * (255 / TAIL_LENGTH));
            int tail_pos = pos - j;
            if (tail_pos < 0) {
                break;
            }
            leds[tail_pos] = CHSV(dot_color, 255, brightness);
        }
    }

    k++;
    //delay(50);
}

void setup() {
    currentLED = 0;
    for (int i=0; i<NUM_DOTS; i++) {
        dots[i] = random(0, NUM_LEDS - 1);
    }
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
    Serial.begin(BAUDRATE);
    delay(10);
}

void loop() {
    animation();
    FastLED.show();

    for (int i=0; i<NUM_DOTS; i++) {
        if (random(0, 100) < 40) {
            dots[i] += 1;
            dots[i] %= NUM_LEDS;
        }
    }
    //currentLED += 1;
    //currentLED %= NUM_LEDS;
    delay(20);
}
