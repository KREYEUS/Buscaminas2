// Nombres de los integrantes del grupo: Senbo Zhou Pan y Ximena Pizarro

#include "inputOutput.h"
#include "listaUndo.h"
#include <iostream>

using namespace std;

void juega(tJuego& juego, int fila, int columna, tListaUndo& lista_undo);
void undo(tJuego& juego, tListaPosiciones lista_pos);

int main() {
	tJuego juego;
	tListaUndo lista_undo;
	int fila = 0, columna = 0, num_jug = 0;
	bool final = false;

	inicializar(juego);
	inicializar(lista_undo);

	if (carga_juego(juego)) {
		mostrar_cabecera();
		mostrar_juego_consola(juego);
		while (!final) {
			pedir_pos(fila, columna);
			if (fila == -1 && columna == -1) {
				mostrar_resultado(juego);
				final = true;
			}
			else if (fila == -2 && columna == -2) {
				cout << "MARCAR/DESMARCAR mina:" << endl
					<< "Introduce la fila y la columna a marcar o desmarcar: ";
				cin >> fila >> columna;
				if (!es_visible(juego, fila, columna)) {
					marcar_desmarcar(juego, fila, columna);
				}
				else {
					cout << "Esta celda es visible, no es posible marcar. " << endl;
				}
			}
			else if (fila == -3 && columna == -3) {
				undo(juego, ultimos_movimientos(lista_undo));
				cout << "UNDO: realizar undo. " << endl;

			}
			else {
				juega(juego, fila, columna, lista_undo);
			}



			if (esta_completo(juego) || mina_explotada(juego)) {
				mostrar_resultado(juego);
				final = true;
			}
			num_jug = dame_num_jugadas(juego);
			cout << "Jugadas: " << num_jug << ". " << endl;
			mostrar_juego_consola(juego);

			int filaTotal = dame_num_filas(juego), columnaTotal = dame_num_columnas(juego);
			int num_minas = dame_num_minas(juego), num_des = dame_num_descubiertas(juego);
			int victoria = (filaTotal * columnaTotal) - num_minas;

			cout << "Numero de descubiertas: " << num_des << endl
				<< "Numero de minas: " << num_minas << endl
				<< "Dimensiones del tablero: " << filaTotal << " " << columnaTotal << endl
				<< "Victoria: " << victoria << endl
				<< "Ultimo movimiento: " << fila << " " << columna << endl;
		}
	}

	return 0;
}

void juega(tJuego& juego, int fila, int columna, tListaUndo& lista_undo) {
	tListaPosiciones lista_pos;
	inicializar(lista_pos);

	if (!es_visible(juego, fila, columna)) {
		juega(juego, fila, columna, lista_pos);
		insertar_final(lista_undo, lista_pos);
	}
	else {
		cout << "La celda seleccionada ya es visible. " << endl;
	}
	inicializar(lista_pos);
}

void undo(tJuego& juego, tListaPosiciones lista_pos) {
	int posX, posY;
	for (int i = 0; i < lista_pos.cont; i++) {
		posX = dame_posX(lista_pos, i);
		posY = dame_posY(lista_pos, i);
		ocultar(juego, posX, posY);
	}
}