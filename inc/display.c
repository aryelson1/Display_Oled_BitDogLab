#include "display.h" // Inclui o cabeçalho para manipulação do display
#include <string.h>  // Biblioteca para manipulação de strings
#include <stdio.h>   // Biblioteca para entrada e saída de dados
#include <stdlib.h>  // Biblioteca para funções padrão, como alocação de memória
#include <math.h>    // Biblioteca para funções matemáticas
#include "pico/stdlib.h" // Biblioteca para uso da Raspberry Pi Pico
#include "hardware/i2c.h" // Biblioteca para comunicação I2C

#define WIDTH 128 // Define a largura do display como 128 pixels
#define HEIGHT 64 // Define a altura do display como 64 pixels

const uint I2C_SDA = 14; // Define o pino de dados SDA do I2C
const uint I2C_SCL = 15; // Define o pino de clock SCL do I2C

uint8_t ssd[ssd1306_buffer_length]; // Buffer de dados para o display
ssd1306_t ssd_bm; // Estrutura para armazenar dados do display

// Estrutura que define a área de renderização do display
struct render_area frame_area = {
    start_column : 0,
    end_column : ssd1306_width - 1,
    start_page : 0,
    end_page : ssd1306_n_pages - 1
};

// Inicializa o display e a comunicação I2C
void display_init()
{
    stdio_init_all(); // Inicializa o sistema padrão de entrada e saída

    i2c_init(i2c1, ssd1306_i2c_clock * 1000); // Inicializa o I2C na frequência especificada
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C); // Configura o pino SDA para função I2C
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C); // Configura o pino SCL para função I2C
    gpio_pull_up(I2C_SDA); // Ativa pull-up no pino SDA
    gpio_pull_up(I2C_SCL); // Ativa pull-up no pino SCL

    ssd1306_init(); // Inicializa o display OLED SSD1306
    calculate_render_area_buffer_length(&frame_area); // Calcula o tamanho do buffer da área de renderização
}

// Limpa o display preenchendo o buffer com zeros
void display_clear()
{
    memset(ssd, 0, ssd1306_buffer_length); // Zera todos os pixels do buffer
    render_on_display(ssd, &frame_area); // Atualiza o display
}

// Renderiza o buffer atual no display
void display_render()
{
    render_on_display(ssd, &frame_area); // Atualiza o display com o buffer de pixels
}

// Desenha um retângulo na tela, podendo ser preenchido ou apenas o contorno
void draw_rectangle(int x0, int y0, int x1, int y1, bool filled, bool set)
{
    if (filled)
    {
        for (int y = y0; y <= y1; y++) // Percorre a altura
        {
            for (int x = x0; x <= x1; x++) // Percorre a largura
            {
                ssd1306_set_pixel(ssd, x, y, set); // Define cada pixel dentro do retângulo
            }
        }
    }
    else
    {
        ssd1306_draw_line(ssd, x0, y0, x1, y0, set); // Linha superior
        ssd1306_draw_line(ssd, x0, y1, x1, y1, set); // Linha inferior
        ssd1306_draw_line(ssd, x0, y0, x0, y1, set); // Linha esquerda
        ssd1306_draw_line(ssd, x1, y0, x1, y1, set); // Linha direita
    }
}

// Testa a exibição de pixels no display
void test_display_pixels()
{
    int matrix[HEIGHT][WIDTH]; // Matriz de pixels do display

    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            ssd1306_set_pixel(ssd, x, y, true); // Acende cada pixel
            display_render(); // Atualiza o display
            matrix[y][x] = 1; // Marca pixel na matriz
        }
    }

    for (int y = 0; y < HEIGHT; y++)
    {
        printf("%i", y);
        for (int x = 0; x < WIDTH; x++)
        {
            printf(matrix[y][x] ? "#" : "."); // Exibe matriz no console
        }
        printf("\n");
    }
}

// Exibe um array de strings no display
void print_text_display(char *text[], uint count)
{
    int y = 0;
    for (uint i = 0; i < count; i++)
    {
        ssd1306_draw_string(ssd, 5, y, text[i]); // Escreve cada linha de texto
        y += 10; // Avança a posição vertical
        display_render(); // Atualiza o display
    }
}

// Exibe uma imagem no display
void print_image_display(uint8_t bitmap_128x64[])
{
    ssd1306_draw_bitmap(&ssd_bm, bitmap_128x64); // Renderiza o bitmap na tela
}

// Desenha um círculo usando o algoritmo de Bresenham
void draw_circle(int x0, int y0, int radius, bool set)
{
    int x = radius; // Inicializa x com o valor do raio
    int y = 0;      // Inicializa y com 0
    int err = 0;    // Inicializa o erro com 0

    // Loop enquanto x for maior ou igual a y
    while (x >= y)
    {
        // Desenha 8 pixels simétricos para formar o círculo
        ssd1306_set_pixel(ssd, x0 + x, y0 + y, set); // Quadrante 1
        ssd1306_set_pixel(ssd, x0 + y, y0 + x, set); // Quadrante 2
        ssd1306_set_pixel(ssd, x0 - y, y0 + x, set); // Quadrante 3
        ssd1306_set_pixel(ssd, x0 - x, y0 + y, set); // Quadrante 4
        ssd1306_set_pixel(ssd, x0 - x, y0 - y, set); // Quadrante 5
        ssd1306_set_pixel(ssd, x0 - y, y0 - x, set); // Quadrante 6
        ssd1306_set_pixel(ssd, x0 + y, y0 - x, set); // Quadrante 7
        ssd1306_set_pixel(ssd, x0 + x, y0 - y, set); // Quadrante 8

        // Atualiza o erro e as coordenadas x e y
        if (err <= 0)
        {
            y += 1;              // Incrementa y
            err += 2 * y + 1;    // Atualiza o erro
        }
        if (err > 0)
        {
            x -= 1;              // Decrementa x
            err -= 2 * x + 1;    // Atualiza o erro
        }
    }
}

