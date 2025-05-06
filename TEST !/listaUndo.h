// Nombres de los integrantes del grupo: Senbo Zhou Pan y Ximena Pizarro

#pragma once

#include "listaPosiciones.h" // A?ado este cabecero, provisional

const int MAX_UNDO = 2;

typedef struct {
	int cont;
	tListaPosiciones* lista[MAX_UNDO];
} tListaUndo;


void inicializar(tListaUndo& lista_undo);
void insertar_final(tListaUndo& lista_undo, tListaPosiciones& lista_pos);
tListaPosiciones ultimos_movimientos(tListaUndo& lista_undo);

void eliminar_ultimo(tListaUndo& lista_undo);
void destruye(tListaUndo& lista_undo);

