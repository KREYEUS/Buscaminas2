// Nombres de los integrantes del grupo: Senbo Zhou Pan y Ximena Pizarro

#include "inputOutput.h"
using namespace std;

void mostrar_cabecera() {
    cout << "Buscaminas" << endl
        << "--------" << endl;
}

void pedir_pos(int& fila, int& columna) {
    cout << "Introduzca una fila y una columna: ";
    cin >> fila >> columna;
}

void mostrar_resultado(const tJuego& juego) {
    int num_jug = dame_num_jugadas(juego);
    if (esta_completo(juego) == true) {
        cout << "Has ganado. " << endl
            << "El numero de jugadas que ha realizado es:" << num_jug << endl;
    }
    else if (mina_explotada(juego) == true) {

        cout << "Has perdido. " << endl
            << "GAME OVER" << endl
            << "El numero de jugadas que ha realizado es:" << endl
            << num_jug << endl;
    }
    else
    {
        cout << "Has abandonado el juego. " << endl
            << "El numero de jugadas totales que ha realizado es:" << num_jug << endl;
    }
}

void mostrar_juego_consola(const tJuego& juego) {
    mostrar_juego(juego);
}

bool carga_juego(tJuego& juego) {
    bool exito;
    ifstream arch;
    string fichero;

    cout << "Introduzca nombre del fichero para ejecutar nuevo juego: ";
    cin >> fichero;

    arch.open(fichero);

    if (arch.is_open()) {
        arch >> juego;
        exito = true;
    }
    else {
        cout << "No se pudo abrir el archivo. ";
        exito = false;
    }
    return exito;
}

istream& operator>> (istream& in, tJuego& juego) {
    int fila, columna, num_minas, filMin, ColMin;
    in >> fila >> columna;

    inicializar(juego, fila, columna);

    in >> num_minas;

    for (int i = 0; i < num_minas; i++) {
        in >> filMin >> ColMin;
        poner_mina(juego, filMin, ColMin);
    }

    return in;
}

const char CHAR_MINA = '*';     // Mina



void colorNumero(int numero) {
    switch (numero)
    {
    case 1: cout << BLUE; break;
    case 2: cout << GREEN; break;
    case 3: cout << RED; break;
    case 4: cout << DBLUE; break;
    case 5: cout << DGREEN; break;
    case 6: cout << DRED; break;
    default:
        break;
    }
}


void mostrarCoutSeparadorMat(int huecoCelda, const tJuego& juego) {
    int columnas = dame_num_columnas(juego);
    cout << "\t -+";
    for (int col = 0; col < columnas; ++col) {
        cout << setw(huecoCelda + 1) << setfill('-') << '+' << setfill(' ');
    }
    cout << endl;
}


void mostrarCeldaConsola(const tJuego& juego, int fila, int columna, int huecos) {
    tCelda celda = dame_celda(juego.tablero, fila, columna);

    if (!celda.visible && !celda.marcada) {
        cout << BG_GRAY << GRAY << setw(huecos) << setfill(' ') << ' ' << RESET;
    }
    else {
        cout << BG_BLACK << BLACK;
        if (!celda.marcada) {
            if (celda.estado == MINA) {
                cout << RED << setw(huecos) << setfill(' ') << CHAR_MINA << RESET;
            }
            else {
                if (celda.estado == VACIA) {
                    cout << setw(huecos) << setfill(' ') << ' ' << RESET;
                }
                else {
                    if (celda.estado == NUMERO) {
                        int numero = celda.numero;
                        colorNumero(numero);
                        cout << setw(huecos) << setfill(' ') << numero << RESET;
                    }
                    else {
                        cout << BG_RED << RED << setw(huecos) << setfill(' ') << ' ' << RESET;
                    }
                }
            }
        }
        else {
            cout << BG_ORANGE << ORANGE << setw(huecos) << setfill(' ') << ' ' << RESET;
        }
    }
}


void mostrar_juego(const tJuego& juego) {
    int filas = dame_num_filas(juego), columnas = dame_num_columnas(juego);
    // mostrar cabecera
    cout << "\t  |";
    for (int col = 0; col < columnas; col++) {
        cout << LBLUE << setw(N_HUECOS) << col << RESET << '|';
    }
    cout << endl;

    // mostrar separador
    mostrarCoutSeparadorMat(N_HUECOS, juego);

    // mostrar tablero

    for (int f = 0; f < filas; f++) {
        // mostrar numero de fila
        cout << "\t" << LBLUE << setw(2) << f << RESET << '|';
        // mostrar la fila
        for (int c = 0; c < columnas; c++) {
            mostrarCeldaConsola(juego, f, c, N_HUECOS);
            cout << '|';
        }
        cout << endl;

        mostrarCoutSeparadorMat(N_HUECOS, juego);
    }
    cout << endl;
}