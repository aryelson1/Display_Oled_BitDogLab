#ifndef DISPLAY_H
#define DISPLAY_H

// Evita múltiplas inclusões do mesmo arquivo de cabeçalho
// Garante que o conteúdo do arquivo seja incluído apenas uma vez durante a compilação

#include <stdint.h>  // Inclui definições de tipos inteiros, como uint8_t, uint16_t, etc.
#include <stdbool.h> // Inclui definições para tipos booleanos (true/false)
#include "ssd1306_i2c.h" // Inclui o cabeçalho para comunicação I2C com o display SSD1306
#include "ssd1306.h"     // Inclui o cabeçalho para manipulação do display SSD1306

// Função para inicializar o display
void display_init();

// Função para limpar o display (apagar todo o conteúdo)
void display_clear();

// Função para renderizar o conteúdo no display (atualizar a tela)
void display_render();

// Função para testar a exibição de pixels no display
void test_display_pixels();

// Função para imprimir texto no display
// Recebe um array de strings (text) e o número de strings (count)
void print_text_display(char *text[], uint count);

// Função para exibir uma imagem no display
// Recebe um bitmap de 128x64 pixels (bitmap_128x64)
void print_image_display(uint8_t bitmap_128x64[]);

// Função para desenhar um retângulo no display
// Parâmetros:
// - x0, y0: Coordenadas do canto superior esquerdo
// - x1, y1: Coordenadas do canto inferior direito
// - filled: Define se o retângulo será preenchido (true) ou apenas o contorno (false)
// - set: Define se o retângulo será desenhado (true) ou apagado (false)
void draw_rectangle(int x0, int y0, int x1, int y1, bool filled, bool set);

// Função para desenhar um círculo no display
// Parâmetros:
// - x0, y0: Coordenadas do centro do círculo
// - radius: Raio do círculo
// - set: Define se o círculo será desenhado (true) ou apagado (false)
void draw_circle(int x0, int y0, int radius, bool set);

#endif // Fim da definição do cabeçalho DISPLAY_H