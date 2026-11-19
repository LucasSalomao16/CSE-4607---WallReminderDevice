#include "draw_text.h"
#include "font5x7.h"

void drawChar(Canvas& canvas, int row, int col, char c, uint32_t color) {
    const uint8_t* columns = charColumns(c);

    for(int x = 0; x < FONT_WIDTH; x++) {
        for(int y = 0; y < FONT_HEIGHT; y++) {
            if(columns[x] & (1 << y)) {
                canvas.setPixel(row + y, col + x, color);
            }
        }
    }
}

void drawString(Canvas& canvas, int row, int col, const char* text, uint32_t color) {
    if(text == nullptr) {
        return;
    }

    for(int i = 0; text[i] != '\0'; i++) {
        drawChar(canvas, row, col + i * (FONT_WIDTH + 1), text[i], color);
    }
}