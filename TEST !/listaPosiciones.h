// Nombres de los integrantes del grupo: Senbo Zhou Pan y Ximena Pizarro

#pragma once

const int MAX_LISTA = 10;

typedef struct {
	int posx;
	int posy;
} tPosicion;
typedef struct {
	tPosicion lista[MAX_LISTA];
	int cont;
} tListaPosiciones;

void inicializar(tListaPosiciones& lista_pos);
void insertar_final(tListaPosiciones& lista_pos, int x, int y);
int longitud(const tListaPosiciones& lista_pos);
int dame_posX(const tListaPosiciones& lista_pos, int i);
int dame_posY(const tListaPosiciones& lista_pos, int i);