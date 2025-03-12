#include "display.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#define WIDTH 128 // Largura do display
#define HEIGHT 64 // Altura do display

const uint I2C_SDA = 14;
const uint I2C_SCL = 15;

uint8_t ssd[ssd1306_buffer_length];
ssd1306_t ssd_bm;

// Preparar área de renderização para o display (ssd1306_width pixels por ssd1306_n_pages páginas)
struct render_area frame_area = {
    start_column : 0,
    end_column : ssd1306_width - 1,
    start_page : 0,
    end_page : ssd1306_n_pages - 1
};

void display_init()
{
    stdio_init_all(); // Inicializa os tipos stdio padrão presentes ligados ao binário

    // Inicialização do i2c
    i2c_init(i2c1, ssd1306_i2c_clock * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    // Processo de inicialização completo do OLED SSD1306
    ssd1306_init();

    calculate_render_area_buffer_length(&frame_area);
}

void display_clear()
{
    // zera o display inteiro
    memset(ssd, 0, ssd1306_buffer_length);
    render_on_display(ssd, &frame_area);
}

void display_render()
{
    render_on_display(ssd, &frame_area);
}

// Função para desenhar um retângulo
void draw_rectangle(int x0, int y0, int x1, int y1, bool filled, bool set)
{
    if (filled)
    {
        // Preenche o retângulo
        for (int y = y0; y <= y1; y++)
        {
            for (int x = x0; x <= x1; x++)
            {
                ssd1306_set_pixel(ssd, x, y, set);
            }
        }
    }
    else
    {
        // Desenha apenas o contorno
        ssd1306_draw_line(ssd, x0, y0, x1, y0, set); // Linha superior
        ssd1306_draw_line(ssd, x0, y1, x1, y1, set); // Linha inferior
        ssd1306_draw_line(ssd, x0, y0, x0, y1, set); // Linha esquerda
        ssd1306_draw_line(ssd, x1, y0, x1, y1, set); // Linha direita
    }

}

void test_display_pixels()
{
    // Matriz para representar as posições dos pixels
    int matrix[HEIGHT][WIDTH];

    // Itera por todas as posições do display
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            // Liga o pixel no display
            ssd1306_set_pixel(ssd, x, y, true);

            display_render();
            // Marca a posição na matriz
            matrix[y][x] = 1;
        }
    }

    // Exibir a matriz no console (depende do ambiente suportar prints)
    for (int y = 0; y < HEIGHT; y++)
    {
        printf("%i",y);
        for (int x = 0; x < WIDTH; x++)
        {
            printf(matrix[y][x] ? "#" : ".");
        }
        printf("\n "); // Nova linha para cada linha do display
    }
}

void print_text_display(char *text[], uint count)
{
    display_clear();
    int y = 0;
    for (uint i = 0; i < count; i++)
    {
        ssd1306_draw_string(ssd, 5, y, text[i]);
        y += 8;
        display_render();
    }
}

void print_image_display(uint8_t bitmap_128x64[])
{
    ssd1306_draw_bitmap(&ssd_bm, bitmap_128x64);
}

// Função para desenhar um círculo
void draw_circle(int x0, int y0, int radius, bool set)
{

    display_clear();
    int x = radius;
    int y = 0;
    int err = 0;

    while (x >= y)
    {
        ssd1306_set_pixel(ssd, x0 + x, y0 + y, set);
        ssd1306_set_pixel(ssd, x0 + y, y0 + x, set);
        ssd1306_set_pixel(ssd, x0 - y, y0 + x, set);
        ssd1306_set_pixel(ssd, x0 - x, y0 + y, set);
        ssd1306_set_pixel(ssd, x0 - x, y0 - y, set);
        ssd1306_set_pixel(ssd, x0 - y, y0 - x, set);
        ssd1306_set_pixel(ssd, x0 + y, y0 - x, set);
        ssd1306_set_pixel(ssd, x0 + x, y0 - y, set);

        if (err <= 0)
        {
            y += 1;
            err += 2 * y + 1;
        }
        if (err > 0)
        {
            x -= 1;
            err -= 2 * x + 1;
        }
    }

    display_render();
}

// Função para desenhar um número
void draw_number(uint8_t *ssd, int16_t x, int16_t y, int number)
{
    char buffer[12];                                // Buffer para armazenar o número como string
    snprintf(buffer, sizeof(buffer), "%d", number); // Converte o número para string
    ssd1306_draw_string(ssd, x, y, buffer);         // Desenha a string no display
}

