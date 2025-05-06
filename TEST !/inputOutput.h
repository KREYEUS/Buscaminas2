#pragma once

#include "listaJuegos.h"
#include "colors.h"
#include <iomanip>
#include <string>
#include <fstream>
#include <iostream>

void mostrar_cabecera();
void pedir_pos(int& fila, int& columna);
void mostrar_resultado(const tJuego& juego);
void mostrar_juego_consola(const tJuego& juego);
bool carga_juego(tJuego& juego);
std::istream& operator>> (std::istream& in, tJuego& juego);

bool cargar_juegos(tListaJuegos& lista_juegos);
bool guardar_juegos(const tListaJuegos& lista_juegos);
void mostrar_juegos(const tListaJuegos& lista_juegos);

const int N_HUECOS = 2; // huecos a dejar en el formato de las celdas.

void mostrar_juego(const tJuego& juego);
void colorNumero(int numero);
void mostrarCoutSeparadorMat(int huecoCelda, const tJuego& juego);
void mostrarCeldaConsola(const tJuego& juego, int fila, int columna, int huecos);
void mostrar_juego(const tJuego& juego);


//RECORDATORIO; Hay que mirar si hay que poner "const" o "&" en las declaraciones de variables de las funciones