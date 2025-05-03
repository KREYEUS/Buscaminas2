// Nombres de los integrantes del grupo: Senbo Zhou Pan y Ximena Pizarro

#include "Tablero.h"

void inicializar(tTablero& tablero) {
	tablero.nCols = 0;
	tablero.nFils = 0;
}

void inicializar_tablero(tTablero& tablero, int nfils, int ncols) {
	tablero.nFils = nfils;
	tablero.nCols = ncols;
	tCelda celda;
	for (int i = 0; i < nfils; i++) {
		for (int j = 0; j < ncols; j++) {
			celda = dame_celda(tablero, i, j);
			inicializar(celda);
			poner_celda(tablero, i, j, celda);
		}
	}
}

int num_filas(const tTablero& tablero)
{
	return tablero.nFils;
}

int num_columnas(const tTablero& tablero)
{
	return tablero.nCols;
}

tCelda dame_celda(const tTablero& tablero, int fila, int columna) {
	return tablero.datos[fila][columna];
}

bool es_valida(const tTablero& tablero, int fila, int columna) {
	bool validez = false;
	if (fila >= 0 && fila < tablero.nFils && columna >= 0 && columna < tablero.nCols) {
		validez = true;
	}
	return validez;
}

void poner_celda(tTablero& tablero, int fila, int columna, const tCelda& celda)
{
	tablero.datos[fila][columna] = celda;
}