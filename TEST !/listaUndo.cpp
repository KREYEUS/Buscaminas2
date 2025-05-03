// Nombres de los integrantes del grupo: Senbo Zhou Pan y Ximena Pizarro

#include "listaUndo.h"

void inicializar(tListaUndo& lista_undo) {
	lista_undo.cont = 0;
}

void insertar_final(tListaUndo& lista_undo, const tListaPosiciones& lista_pos) {
	if (lista_undo.cont < MAX_UNDO)
	{
		lista_undo.lista[lista_undo.cont] = lista_pos;

		lista_undo.cont++;
	}
	else {
		for (int i = 1; i < MAX_UNDO; i++) {
			lista_undo.lista[i - 1] = lista_undo.lista[i];
		}
		lista_undo.lista[MAX_UNDO - 1] = lista_pos;
	}

}

tListaPosiciones ultimos_movimientos(tListaUndo& lista_undo) {
	tListaPosiciones lista_pos;
	inicializar(lista_pos);
	if (lista_undo.cont > 0) {
		lista_undo.cont--;
		lista_pos = lista_undo.lista[lista_undo.cont];
	}

	return lista_pos;
}