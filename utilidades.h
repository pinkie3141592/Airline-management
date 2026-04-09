#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "datos.h"

bool confirmar_existencia_platillos(int id);
Platillo info_platillo(int id);
int calcular_elementos(FILE *, long);
void quitar_salto(char *);
bool validar_usuario(FILE *, char *, char *);
int comparar_fechas(Fecha a, Fecha b);
Fecha fecha_actual();
Hora hora_actual();
void imprimir_pedido(Pedido envase);
Fecha solicitar_fecha(int ano_min, int ano_max);
int existencia_platillos();
int existencia_pedidos();



#endif