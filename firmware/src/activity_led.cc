#include "activity_led.h"
#include <bsp/board_api.h>
#include <hardware/timer.h>
#include <Adafruit_NeoPixel.h>

// Define NeoPixel pin and number of pixels
#define NEOPIXEL_PIN 16
#define NUM_PIXELS 1

// Create NeoPixel instance
Adafruit_NeoPixel pixels(NUM_PIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

static bool led_state = false;
static uint64_t turn_led_off_after = 0;

void setup() {
    // Initialize NeoPixel
    pixels.begin();
    pixels.show(); // Initialize all pixels to 'off'
}

void activity_led_on() {
    led_state = true;
    pixels.setPixelColor(0, pixels.Color(255, 0, 0)); // Set the first pixel to red
    pixels.show();
    turn_led_off_after = time_us_64() + 50000;
}

void activity_led_off_maybe() {
    if (led_state && (time_us_64() > turn_led_off_after)) {
        led_state = false;
        pixels.setPixelColor(0, pixels.Color(0, 0, 0)); // Turn off the pixel
        pixels.show();
    }
}
