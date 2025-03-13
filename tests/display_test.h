#ifndef DISPLAY_TEST_H
#define DISPLAY_TEST_H

#include "../inc/display.h"
#include <ctype.h>
#include <string.h>       // Biblioteca para manipulação de strings
#include <stdio.h>        // Biblioteca para entrada e saída de dados
#include <stdlib.h>       // Biblioteca para funções padrão, como alocação de memória
#include <math.h>         // Biblioteca para funções matemáticas

// Declaração das funções de teste
void test_draw_rectangle(int x0, int y0, int x1, int y1, bool filled, bool set);
void test_print_text_display(char *text[], uint count);
void test_draw_circle(int x0, int y0, int radius, bool set);
void all_test_run();

#endif 