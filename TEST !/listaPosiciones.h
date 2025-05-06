#pragma once

const int MAX_LISTA = 100;

typedef struct {
	int posx;
	int posy;
} tPosicion;

typedef struct {
	tPosicion* lista;
	int cont;
	int capacidad;
} tListaPosiciones;

void inicializar(tListaPosiciones& lista_pos);
void insertar_final(tListaPosiciones& lista_pos, int x, int y);
int longitud(const tListaPosiciones& lista_pos);
int dame_posX(const tListaPosiciones& lista_pos, int i);
int dame_posY(const tListaPosiciones& lista_pos, int i);

void destruye(tListaPosiciones& lista_posiciones);

void redimensionamiento(tListaPosiciones& lista_pos);