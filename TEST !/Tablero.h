// Nombres de los integrantes del grupo: Senbo Zhou Pan y Ximena Pizarro

#pragma once

#include "Celda.h"

const int MAX_FILS = 30, MAX_COLS = 30;

typedef struct {
	int nFils, nCols;
	tCelda datos[MAX_FILS][MAX_COLS];
} tTablero;


void inicializar(tTablero& tablero);
void inicializar(tTablero& tablero, int nfils, int ncols);
int num_filas(const tTablero& tablero);
int num_columnas(const tTablero& tablero);
tCelda dame_celda(const tTablero& tablero, int fila, int columna);
bool es_valida(const tTablero& tablero, int fila, int columna);
void poner_celda(tTablero& tablero, int fila, int columna, const tCelda& celda);