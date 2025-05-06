#include "Juego.h"
#include <cstdlib>
#include <ctime>

using namespace std;

const int TAM = 8;

typedef int tArrayDirX[2][TAM];
const tArrayDirX Dir = { -1, -1, -1, 0, 1, 1, 1, 0,
 -1, 0, 1, 1, 1, 0, -1, -1 };

void inicializar(tJuego& juego)
{
	juego.num_jugadas = 0;

	juego.num_minas = 0;

	juego.num_descubiertas = 0;

	juego.mina_explotada = false;

	inicializar(juego.tablero);
}

void inicializar(tJuego& juego, int nfils, int ncols) {
	inicializar(juego.tablero, nfils, ncols);
}

int dame_num_jugadas(const tJuego& juego)
{
	return juego.num_jugadas;
}

int dame_num_filas(const tJuego& juego)
{
	int fila = num_filas(juego.tablero);

	return fila;
}

int dame_num_columnas(const tJuego& juego)
{
	int columna = num_columnas(juego.tablero);

	return columna;
}

int dame_num_minas(const tJuego& juego)
{
	return juego.num_minas;
}

bool contiene_mina(const tJuego& juego, int fila, int columna) {
	tCelda celda = dame_celda(juego.tablero, fila, columna);
	
	return es_mina(celda);
}

bool es_visible(const tJuego& juego, int fila, int columna) {
	tCelda celda = dame_celda(juego.tablero, fila, columna);
	
	return es_visible(celda);
}

bool esta_marcada(const tJuego& juego, int fila, int columna) {
	tCelda celda = dame_celda(juego.tablero, fila, columna);

	return esta_marcada(celda);
}

bool esta_vacia(const tJuego& juego, int fila, int columna) {
	tCelda celda = dame_celda(juego.tablero, fila, columna);
	
	return esta_vacia(celda);
}

bool contiene_numero(const tJuego& juego, int fila, int columna) {
	tCelda celda = dame_celda(juego.tablero, fila, columna);
	
	return contiene_numero(celda);
}

int dame_numero(const tJuego& juego, int fila, int columna)
{
	tCelda celda = dame_celda(juego.tablero, fila, columna);

	int numero = dame_numero(celda);

	return numero;
}

bool esta_completo(const tJuego& juego) {
	int fila = num_filas(juego.tablero), columna = num_columnas(juego.tablero);

	return juego.num_descubiertas == (fila * columna) - juego.num_minas;
}

bool mina_explotada(const tJuego& juego) {
	return juego.mina_explotada;
}

bool esta_terminado(const tJuego& juego) {
	return esta_completo(juego) || mina_explotada(juego);
}

void poner_mina(tJuego& juego, int fila, int columna) {
	tCelda celda = dame_celda(juego.tablero, fila, columna);

	if (es_valida(juego.tablero, fila, columna) && !es_mina(celda)) {
		poner_mina(celda);
		poner_celda(juego.tablero, fila, columna, celda);

		juego.num_minas++;

		for (int i = 0; i < TAM; i++) {
			int filaSig = fila + Dir[0][i], ColSig = columna + Dir[1][i];
			if (es_valida(juego.tablero, filaSig, ColSig)) {
				tCelda celdaAd = dame_celda(juego.tablero, filaSig, ColSig);
				int numAd = dame_numero(celdaAd);

				poner_numero(celdaAd, numAd + 1);

				poner_celda(juego.tablero, filaSig, ColSig, celdaAd);
			}
		}
	}
}

void marcar_desmarcar(tJuego& juego, int fila, int columna)
{
	tCelda celda = dame_celda(juego.tablero, fila, columna);

	if (es_valida(juego.tablero, fila, columna) && esta_marcada(celda))
	{
		desmarcar_celda(celda);
		poner_celda(juego.tablero, fila, columna, celda);
	}
	else if (es_valida(juego.tablero, fila, columna) && !esta_marcada(celda))
	{
		marcar_celda(celda);
		poner_celda(juego.tablero, fila, columna, celda);
	}
}

void ocultar(tJuego& juego, int fila, int columna) {
	tCelda celda = dame_celda(juego.tablero, fila, columna);

	if (es_valida(juego.tablero, fila, columna) && es_visible(celda)) {
		ocultar_celda(celda);
	}
	juego.num_descubiertas--;
	poner_celda(juego.tablero, fila, columna, celda);
}

void juega(tJuego& juego, int fila, int columna, tListaPosiciones& lista_pos) {
	if (es_valida(juego.tablero, fila, columna)) {
		tCelda celda = dame_celda(juego.tablero, fila, columna);
		if (!es_visible(celda) && !esta_marcada(celda)) {

			descubrir_celda(celda);
			juego.num_descubiertas++;
			poner_celda(juego.tablero, fila, columna, celda);
			insertar_final(lista_pos, fila, columna);
			juego.num_jugadas++;

			descubrir_alrededores(juego, fila, columna, celda, lista_pos);
			
			if (es_mina(celda)) {
				juego.mina_explotada = true;
			}
		}
	}
}

void descubrir_alrededores(tJuego& juego, int fila, int columna, const tCelda& celda, tListaPosiciones& lista_pos) {
	int numCel = dame_numero(celda);
	if (!es_mina(celda) && numCel <= 0) {
		for (int i = 0; i < TAM; i++) {
			int filaSig = fila + Dir[0][i], ColSig = columna + Dir[1][i];

			tCelda celdaAd = dame_celda(juego.tablero, filaSig, ColSig);
			if (!esta_marcada(celdaAd) && !es_visible(celdaAd) && es_valida(juego.tablero, filaSig, ColSig)) {
				descubrir_celda(celdaAd);
				juego.num_descubiertas++;
				poner_celda(juego.tablero, filaSig, ColSig, celdaAd);
				insertar_final(lista_pos, filaSig, ColSig);
				
				descubrir_alrededores(juego, filaSig, ColSig, celdaAd, lista_pos);
			}
		}
	}
}

int calcula_nivel(const tJuego& juego) {
	int nFil = dame_num_filas(juego), nCol = dame_num_columnas(juego), nMin = dame_num_minas(juego);
	int nivel = 0; 
	if (nMin != 0) {
		nivel = nivel = (nFil * nCol) / nMin;
	}	
	return nivel;
}

tJuego crear_juego(int num_fils, int num_cols, int num_minas) {
	bool terminado = false;
	tJuego juego;
	inicializar(juego, num_fils, num_cols);

	srand(time(nullptr));

	while (!terminado) {
		// Sumo 1 para alcanzar el valor máximo
		int fila = rand() % (num_fils + 1);
		int col = rand() % (num_cols + 1); 

		if (!contiene_mina(juego, fila, col)) {
			poner_mina(juego, fila, col);
		}

		int n_minasj = dame_num_minas(juego);

		if (n_minasj == num_minas) {
			terminado = true;
		}
	}
	return juego;
}

int dame_num_descubiertas(const tJuego& juego) {
	return juego.num_descubiertas;
}