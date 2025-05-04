// Nombres de los integrantes del grupo: Senbo Zhou Pan y Ximena Pizarro

#pragma once

#include "Tablero.h"
#include <iostream>
#include "listaPosiciones.h"

typedef struct {
	tTablero tablero;
	int num_jugadas;
	bool mina_explotada;
	int num_minas;
	int num_descubiertas;
} tJuego;

void inicializar(tJuego& juego);
void inicializar(tJuego& juego, int nfils, int ncols);
int dame_num_jugadas(const tJuego& juego);
int dame_num_filas(const tJuego& juego);
int dame_num_columnas(const tJuego& juego);
int dame_num_minas(const tJuego& juego);
bool contiene_mina(const tJuego& juego, int fila, int columna);
bool es_visible(const tJuego& juego, int fila, int columna);
bool esta_marcada(const tJuego& juego, int fila, int columna);
bool esta_vacia(const tJuego& juego, int fila, int columna);
bool contiene_numero(const tJuego& juego, int fila, int columna);
int dame_numero(const tJuego& juego, int fila, int columna);
bool esta_completo(const tJuego& juego);
bool mina_explotada(const tJuego& juego);
bool esta_terminado(const tJuego& juego);
void poner_mina(tJuego& juego, int fila, int columna);
void marcar_desmarcar(tJuego& juego, int fila, int columna);
void ocultar(tJuego& juego, int fila, int columna);
void juega(tJuego& juego, int fila, int columna, tListaPosiciones& lista_pos);

void descubrir_alrededores(tJuego& juego, int fila, int columna, const tCelda& celda, tListaPosiciones& lista_pos);

int calcula_nivel(const tJuego& juego);

// void crear_juego(int num_fils, int num_cols, int num_minas);
// Como añado minas aleatorias?

int dame_num_descubiertas(const tJuego& juego);