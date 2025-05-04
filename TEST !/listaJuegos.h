#pragma once

#include "Juego.h"

const int MAX_JUEGOS = 1;

typedef tJuego* tPtrJuego;

typedef struct {
	tPtrJuego* lista;
	int cont;
	int capacidad;
} tListaJuegos;

void inicializar(tListaJuegos& lista_juegos);
void destruye(tListaJuegos& lista_juegos);

/*

 
 insertar(lista_juegos, juego);
 numero_juegos(lista_juegos);
 es_vacia(lista_juegos);
 dame_juego(lista_juegos, pos);
 eliminar(lista_juegos, pos);
*/