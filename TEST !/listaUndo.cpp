// Nombres de los integrantes del grupo: Senbo Zhou Pan y Ximena Pizarro

#include "listaUndo.h"

void inicializar(tListaUndo& lista_undo) {
	lista_undo.cont = 0;
	for (int i = 0; i < MAX_UNDO; i++) {
		lista_undo.lista[i] = nullptr;
	}
}

void insertar_final(tListaUndo& lista_undo, tListaPosiciones& lista_pos) {
	if (lista_undo.cont < MAX_UNDO)
	{		
		lista_undo.lista[lista_undo.cont] = new tListaPosiciones(lista_pos);

		lista_undo.cont++;
	}
	else {
		destruye(*lista_undo.lista[0]);
		for (int i = 1; i < MAX_UNDO; i++) {
			lista_undo.lista[i - 1] = lista_undo.lista[i];
		}
		lista_undo.lista[MAX_UNDO - 1] = new tListaPosiciones(lista_pos);
	}
}

tListaPosiciones ultimos_movimientos(tListaUndo& lista_undo) {
	tListaPosiciones lista_pos;
	inicializar(lista_pos);
	if (lista_undo.cont > 0) {
		// Se copia manualmente
		int tamano = longitud(*lista_undo.lista[lista_undo.cont - 1]);
		for (int k = 0; k < tamano; k++) {
			int posX = dame_posX(*lista_undo.lista[lista_undo.cont - 1], k), 
				posY = dame_posY(*lista_undo.lista[lista_undo.cont - 1], k);
			insertar_final(lista_pos, posX, posY);
		}

		eliminar_ultimo(lista_undo);
	}
	return lista_pos;
}

void eliminar_ultimo(tListaUndo& lista_undo) {
	if (lista_undo.cont > 0) {
		lista_undo.cont--;
		destruye(*lista_undo.lista[lista_undo.cont]);
	}
}

void destruye(tListaUndo& lista_undo) {
	for (int i = 0; i < lista_undo.cont; i++) {
		delete lista_undo.lista[i];
		lista_undo.lista[i] = nullptr;
	}
	
	lista_undo.cont = 0;
}