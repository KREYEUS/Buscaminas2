// Nombres de los integrantes del grupo: Senbo Zhou Pan y Ximena Pizarro

#include "listaPosiciones.h"

void inicializar(tListaPosiciones& lista_pos)
{
	lista_pos.cont = 0;

	lista_pos.lista[lista_pos.cont].posx = 0;
	lista_pos.lista[lista_pos.cont].posy = 0;
}

void insertar_final(tListaPosiciones& lista_pos, int x, int y) {
	if (lista_pos.cont < MAX_LISTA)
	{
		lista_pos.lista[lista_pos.cont].posx = x;

		lista_pos.lista[lista_pos.cont].posy = y;

		lista_pos.cont++;
	}
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