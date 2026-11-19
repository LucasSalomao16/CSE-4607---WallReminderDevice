#include "draw_text.h"
#include "font5x7.h"

// draws a single character column by column 
void drawChar(Canvas& canvas, int row, int col, char c, uint32_t color) {
    const uint8_t* columns = charColumns(c);

    for(int x = 0; x < FONT_WIDTH; x++) {
        for(int y = 0; y < FONT_HEIGHT; y++) {
            // columns[x] is a bit mask with 1s in the rows that should be lit 
            // "AND-ing" with 1 << y checks if the pixel in row "y" should be lit 
            if(columns[x] & (1 << y)) {
                canvas.setPixel(row + y, col + x, color);
            }
        }
    }
}

// draws a string letter by letter 
void drawString(Canvas& canvas, int row, int col, const char* text, uint32_t color) {
    if(text == nullptr) {
        return;
    }

    for(int i = 0; text[i] != '\0'; i++) {
        // draws characters leaving one blank column between each character 
        drawChar(canvas, row, col + i * (FONT_WIDTH + 1), text[i], color);
    }
}