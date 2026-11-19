#include <cassert>
#include <cstdio>
#include "canvas.h"
#include "draw_text.h"

const uint32_t WHITE = 0x00FFFFFF;

// Counts how many pixels on the canvas are lit.
int countLit(const Canvas& canvas) {
    int count = 0;
    for (int row = 0; row < DISPLAY_HEIGHT; row++) {
        for (int col = 0; col < DISPLAY_WIDTH; col++) {
            if (canvas.getPixel(row, col) != 0) count++;
        }
    }
    return count;
}

void testCharAAtOrigin() {
    Canvas canvas;
    canvas.clear(0);
    drawChar(canvas, 0, 0, 'A', WHITE);

    assert(canvas.getPixel(0, 2) != 0);   // tip of the A
    assert(canvas.getPixel(0, 0) == 0);   // top-left corner is dark

    assert(canvas.getPixel(4,1) != 0);

    assert(countLit(canvas) == 16);
}

int main() {
    testCharAAtOrigin();
    printf("draw_text tests passed\n");
    return 0;
}