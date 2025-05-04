// Nombres de los integrantes del grupo: Senbo Zhou Pan y Ximena Pizarro

#include "Juego.h"
using namespace std;

const int TAM = 8;

typedef int tArrayDirX[TAM];
const tArrayDirX DirX = { -1, -1, -1, 0, 1, 1, 1, 0 };
const tArrayDirX DirY = { -1, 0, 1, 1, 1, 0, -1, -1 };

void inicializar(tJuego& juego)
{
	juego.num_jugadas = 0;

	juego.num_minas = 0;

	juego.num_descubiertas = 0;

	juego.mina_explotada = false;

	inicializar(juego.tablero);
}

void inicializar(tJuego& juego, int nfils, int ncols) {
	inicializar(juego);
	inicializar_tablero(juego.tablero, nfils, ncols);
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
	bool mina = false;
	tCelda celda = dame_celda(juego.tablero, fila, columna);
	if (esMina(celda) == true) {
		mina = true;
	}
	return mina;
}

bool es_visible(const tJuego& juego, int fila, int columna) {
	bool visible = false;
	tCelda celda = dame_celda(juego.tablero, fila, columna);
	if (esVisible(celda) == true) {
		visible = true;
	}
	return visible;
}

bool esta_marcada(const tJuego& juego, int fila, int columna) {
	bool marcada = false;
	tCelda celda = dame_celda(juego.tablero, fila, columna);
	if (estaMarcada(celda) == true) {
		marcada = true;
	}
	return marcada;
}

bool esta_vacia(const tJuego& juego, int fila, int columna) {
	bool vacio = false;
	tCelda celda = dame_celda(juego.tablero, fila, columna);
	if (estaVacia(celda) == true) {
		vacio = true;
	}
	return vacio;
}

bool contiene_numero(const tJuego& juego, int fila, int columna) {
	bool contiene = false;
	tCelda celda = dame_celda(juego.tablero, fila, columna);
	if (contieneNumero(celda) == true) {
		contiene = true;
	}
	return contiene;
}

int dame_numero(const tJuego& juego, int fila, int columna)
{
	tCelda celda = dame_celda(juego.tablero, fila, columna);

	int numero = dameNumero(celda);

	return numero;
}

bool esta_completo(const tJuego& juego) {
	bool completo = false;
	int fila = num_filas(juego.tablero), columna = num_columnas(juego.tablero);
	if (juego.num_descubiertas == (fila * columna) - juego.num_minas) {
		completo = true;
	}
	return completo;
}

bool mina_explotada(const tJuego& juego) {
	return juego.mina_explotada;
}

bool esta_terminado(const tJuego& juego) {
	bool terminado = false;
	if (esta_completo(juego) || mina_explotada(juego)) {
		terminado = true;
	}
	return terminado;
}

void poner_mina(tJuego& juego, int fila, int columna) {
	tCelda celda = dame_celda(juego.tablero, fila, columna);

	if (es_valida(juego.tablero, fila, columna) && celda.estado != MINA) {
		poner_mina(celda);
		poner_celda(juego.tablero, fila, columna, celda);

		juego.num_minas++;

		for (int i = 0; i < TAM; i++) {
			int filaSig = fila + DirX[i], ColSig = columna + DirY[i];
			if (es_valida(juego.tablero, filaSig, ColSig)) {
				tCelda celdaAd = dame_celda(juego.tablero, filaSig, ColSig);
				int numAd;

				if (estaVacia(celdaAd)) {
					poner_numero(celdaAd, 0);
				}
				numAd = dameNumero(celdaAd);

				poner_numero(celdaAd, numAd + 1);

				poner_celda(juego.tablero, filaSig, ColSig, celdaAd);
			}
		}
	}
}

void marcar_desmarcar(tJuego& juego, int fila, int columna)
{
	tCelda celda = dame_celda(juego.tablero, fila, columna);

	if (es_valida(juego.tablero, fila, columna) && estaMarcada(celda))
	{
		celda.marcada = false;
		poner_celda(juego.tablero, fila, columna, celda);
	}
	else if (es_valida(juego.tablero, fila, columna) && !estaMarcada(celda))
	{
		celda.marcada = true;
		poner_celda(juego.tablero, fila, columna, celda);
	}
	else
	{
		cout << "Posicion invalida. " << endl;
	}
}

void ocultar(tJuego& juego, int fila, int columna) {
	tCelda celda = dame_celda(juego.tablero, fila, columna);

	if (es_valida(juego.tablero, fila, columna) && esVisible(celda)) {
		ocultarCelda(celda);
	}
	juego.num_descubiertas--;
	poner_celda(juego.tablero, fila, columna, celda);
}

void juega(tJuego& juego, int fila, int columna, tListaPosiciones& lista_pos) {
	if (es_valida(juego.tablero, fila, columna)) {
		tCelda celda = dame_celda(juego.tablero, fila, columna);
		if (!esVisible(celda) && !estaMarcada(celda)) {

			descubrir_celda(celda);
			juego.num_descubiertas++;
			poner_celda(juego.tablero, fila, columna, celda);
			insertar_final(lista_pos, fila, columna);
			juego.num_jugadas++;

			descubrir_alrededores(juego, fila, columna, celda, lista_pos);
			
			if (esMina(celda)) {
				juego.mina_explotada = true;
			}
		}
	}
}

void descubrir_alrededores(tJuego& juego, int fila, int columna, const tCelda& celda, tListaPosiciones& lista_pos) {
	int numCel = dameNumero(celda);
	if (!esMina(celda) && numCel <= 0) {
		for (int i = 0; i < TAM; i++) {
			int filaSig = fila + DirX[i], ColSig = columna + DirY[i];

			tCelda celdaAd = dame_celda(juego.tablero, filaSig, ColSig);
			if (!estaMarcada(celdaAd) && !esVisible(celdaAd) && es_valida(juego.tablero, filaSig, ColSig)) {
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
	int nivel = (nFil * nCol) / nMin; // Podría nMin ser 0?

	return nivel;
}

/*
void crear_juego(int num_fils, int num_cols, int num_minas) {


}
*/


int dame_num_descubiertas(const tJuego& juego) {
	return juego.num_descubiertas;
}