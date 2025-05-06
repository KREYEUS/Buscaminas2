#include "listaPosiciones.h"

void inicializar(tListaPosiciones& lista_pos)
{
	lista_pos.cont = 0;
	lista_pos.capacidad = MAX_LISTA;

	lista_pos.lista = new tPosicion[lista_pos.capacidad];
}

void insertar_final(tListaPosiciones& lista_pos, int x, int y) {
	redimensionamiento(lista_pos);
	
	lista_pos.lista[lista_pos.cont].posx = x;
	lista_pos.lista[lista_pos.cont].posy = y;
	lista_pos.cont++;
}

int longitud(const tListaPosiciones& lista_pos) {
	return lista_pos.cont;
}

int dame_posX(const tListaPosiciones& lista_pos, int i) {
	return lista_pos.lista[i].posx;
}

int dame_posY(const tListaPosiciones& lista_pos, int i) {
	return lista_pos.lista[i].posy;
}

void destruye(tListaPosiciones& lista_posiciones) {
	delete[] lista_posiciones.lista;

	lista_posiciones.lista = nullptr;
	lista_posiciones.cont = 0;

}

void redimensionamiento(tListaPosiciones& lista_pos) {
	if (lista_pos.cont >= lista_pos.capacidad) {
		int newSize = lista_pos.capacidad * 2;
		tPosicion* vaux = new tPosicion[newSize];

		for (int i = 0; i < lista_pos.cont; i++) {
			vaux[i] = lista_pos.lista[i];
		}

		lista_pos.capacidad = newSize;
		delete[] lista_pos.lista;
		lista_pos.lista = vaux;
	}
}