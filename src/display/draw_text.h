#pragma once
#include <cstdint>
#include "canvas.h"


void drawChar(Canvas& canvas, int row, int col, char c, uint32_t color);

void drawString(Canvas& canvas, int row, int col, const char* text, uint32_t color);