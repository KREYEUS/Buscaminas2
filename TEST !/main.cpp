// Nombres de los integrantes del grupo: Senbo Zhou Pan y Ximena Pizarro

#include "inputOutput.h"
#include "listaUndo.h"
#include <iostream>

using namespace std;

void juega(tJuego& juego, int fila, int columna, tListaUndo& lista_undo);
void undo(tJuego& juego, tListaPosiciones lista_pos);

void juego_aleatorio(tJuego& juego, tListaUndo& lista_undo, tListaJuegos& lista_juegos);
void jugarPartida(tJuego& juego, tListaUndo& lista_undo);

int main() {
	tJuego juego;
	tListaJuegos lista_juegos;
	tListaUndo lista_undo;

	inicializar(juego);
	inicializar(lista_undo);
	inicializar(lista_juegos);

	if (cargar_juegos(lista_juegos)) {
		mostrar_juegos(lista_juegos);
		int num_jueg = numero_juegos(lista_juegos);
		if (num_jueg == 0) {
			cout << "El fichero no contiene ningún juego. " << endl
				<< "A continuación se generará un juego aleatorio. ";
			juego_aleatorio(juego, lista_undo, lista_juegos);
		}
		else {
			int opcion;
			cout << "Cargado con exito, elija opcion. " << endl
				<< "Opcion 1: Jugar un nuevo juego. " << endl
				<< "Opcion 2: Jugar un juego existente. " << endl
				<< "Opcion: ";
			cin >> opcion;

			switch (opcion) {
			case 1: {
				juego_aleatorio(juego, lista_undo, lista_juegos);
				break;
			}
			case 2: {
				int num;
				mostrar_juegos(lista_juegos);

				cout << "Inserte el juego que quiere jugar: ";
				cin >> num;
				if(num >= 0 && num < num_jueg){
					juego = dame_juego(lista_juegos, num);
					jugarPartida(juego, lista_undo);
				
				}
				break;
			}
			}
		}
		mostrar_juegos(lista_juegos);

		if (guardar_juegos(lista_juegos)) {
			cout << "Lista guardada con exito. " << endl;
		}

		destruye(lista_juegos);
		destruye(lista_undo);
	}
	else {
		if (carga_juego(juego)) {
			jugarPartida(juego, lista_undo);
		}
	}
	return 0;
}

void juega(tJuego& juego, int fila, int columna, tListaUndo& lista_undo) {
	tListaPosiciones lista_pos;
	inicializar(lista_pos);

	juega(juego, fila, columna, lista_pos);
	insertar_final(lista_undo, lista_pos);

	inicializar(lista_pos);
}

void undo(tJuego& juego, tListaPosiciones lista_pos) {
	int posX, posY;
	int tamano = longitud(lista_pos);
	for (int i = 0; i < tamano; i++) {
		posX = dame_posX(lista_pos, i);
		posY = dame_posY(lista_pos, i);
		ocultar(juego, posX, posY);
	}
}

void juego_aleatorio(tJuego& juego, tListaUndo& lista_undo, tListaJuegos& lista_juegos) { // Que tan aleatorea?
	int num_fils = 0, num_cols = 0, num_minas = 0;
	inicializar(juego);

	cout << "Introduzca dimensiones y datos: " << endl
		<< "Numero de filas: ";
	cin >> num_fils;

	cout << "Numero de columnas: ";
	cin >> num_cols;

	cout << "Numero de minas: ";
	cin >> num_minas;

	juego = crear_juego(num_fils, num_cols, num_minas);
	insertar(lista_juegos, juego);

	mostrar_juegos(lista_juegos);

	jugarPartida(juego, lista_undo);
}

void jugarPartida(tJuego& juego, tListaUndo& lista_undo) {
	int fila = 0, columna = 0, num_jug = 0;
	bool final = false;
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
