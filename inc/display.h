#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>
#include <stdbool.h>
#include "ssd1306_i2c.h"
#include "ssd1306.h"


void display_init();

void display_clear();

void display_render();

void test_display_pixels();

void print_text_display(char *text[], uint count);

void print_image_display(uint8_t bitmap_128x64[]);

// Função para desenhar um retângulo
void draw_rectangle(int x0, int y0, int x1, int y1, bool filled, bool set);

// Função para desenhar um círculo
void draw_circle(int x0, int y0, int radius, bool set);

// Função para desenhar um número
void draw_number(uint8_t *ssd, int16_t x, int16_t y, int number);


#endif // SSD1306_EXTENDED_H