#pragma once
#include <cstdint>

constexpr int DISPLAY_WIDTH = 64;
constexpr int DISPLAY_HEIGHT = 32;

class Canvas {
    public: 
        void clear(uint32_t color);
        void setPixel(int row, int col, uint32_t color);
        uint32_t getPixel(int row, int col) const;
    private: 
        uint32_t pixels[DISPLAY_HEIGHT * DISPLAY_WIDTH] = {};
};