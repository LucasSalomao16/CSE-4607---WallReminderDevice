#include "canvas.h"

// sets the whole canvas to one color 
void Canvas::clear(uint32_t color) {
    for(int i = 0; i < DISPLAY_HEIGHT * DISPLAY_WIDTH; i++) {
        pixels[i] = color;
    }
}

// sets one pixel to the color passed in 
void Canvas::setPixel(int row, int col, uint32_t color) {
    // bounds check 
    if(row < 0 || row >= DISPLAY_HEIGHT || col < 0 || col >= DISPLAY_WIDTH) {
        return;
    }

    pixels[row * DISPLAY_WIDTH + col] = color;
}

// gets the value of a single pixel 
uint32_t Canvas::getPixel(int row, int col) const {
    // bounds check 
    if(row < 0 || row >= DISPLAY_HEIGHT || col < 0 || col >= DISPLAY_WIDTH) {
        return 0;
    }

    return pixels[row * DISPLAY_WIDTH + col];
}