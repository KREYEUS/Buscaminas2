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
        cout << "Has ganado. " << endl;
    }
    else if (mina_explotada(juego) == true) {

        cout << "Has perdido. " << endl;
    }
    else
    {
        cout << "Has abandonado el juego. " << endl;
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
        arch.close();
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

bool cargar_juegos(tListaJuegos& lista_juegos) {
    bool exito = false;
    ifstream arch;
    string fichero;

    int num_juegos;

    cout << "Introduce el nombre del fichero donde cargar los juegos: ";
    cin >> fichero;

    arch.open(fichero);

    if (!arch.is_open()) {
        cout << "No se pudo abrir el fichero." << endl;
    }
    else {
        arch >> num_juegos;
        for (int i = 0; i < num_juegos; i++) {
            tJuego juego;
            int filaj, colj, num_minas, filMin, ColMin;
            arch >> filaj >> colj;

            inicializar(juego, filaj, colj);

            arch >> num_minas;

            for (int i = 0; i < num_minas; i++) {
                arch >> filMin >> ColMin;
                poner_mina(juego, filMin, ColMin);
            }

            int pos = insertar(lista_juegos, juego);
        }
        exito = true;

        arch.close();
    }    
    return exito;
}

bool guardar_juegos(const tListaJuegos& lista_juegos) {
    bool exito;
    string archDest;
    ofstream arch;

    cout << "Introduce el nombre del fichero donde guardar los juegos: ";
    cin >> archDest;

    arch.open(archDest);
    if (!arch.is_open()) {
        cout << "No se pudo abrir el fichero." << endl;
        exito = false;
    }
    else {
        exito = true;
        int n_jueg = numero_juegos(lista_juegos);
        
        arch << n_jueg << endl;

        for (int i = 0; i < n_jueg; i++) {
            tJuego juego = dame_juego(lista_juegos, i);

            int filas = dame_num_filas(juego);
            int columnas = dame_num_columnas(juego);
            int minas = dame_num_minas(juego);

            arch << filas << ' ' << columnas << '\n';
            arch << minas << '\n';

            for (int k = 0; k < filas; k++) {
                for (int j = 0; j < columnas; j++) {
                    if (contiene_mina(juego, k, j)) {
                        arch << k << ' ' << j << '\n';
                    }
                }
            }
        }
        arch.close();
    }    
    return exito;
}

void mostrar_juegos(const tListaJuegos& lista_juegos) {
    cout << "Mostrando lista de juegos por orden de dificultad... " << endl;
    for (int i = 0; i < numero_juegos(lista_juegos); i++) {
        tJuego juego = dame_juego(lista_juegos, i);
        int filas = dame_num_filas(juego);
        int columnas = dame_num_columnas(juego);
        int minas = dame_num_minas(juego);
        int nivel = calcula_nivel(juego);

        cout << "Juego " << i << ": " << endl
            << "   Dimension: " << filas << " x " << columnas << endl
            << "   Minas: " << minas << endl
            << "   Nivel: " << nivel << endl;
    }
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

    if (!es_visible(celda) && !esta_marcada(celda)) {
        cout << BG_GRAY << GRAY << setw(huecos) << setfill(' ') << ' ' << RESET;
    }
    else {
        cout << BG_BLACK << BLACK;
        if (!esta_marcada(celda)) { 
            if (es_mina(celda)) {
                cout << RED << setw(huecos) << setfill(' ') << CHAR_MINA << RESET;
            }
            else {
                if (esta_vacia(celda)) {
                    cout << setw(huecos) << setfill(' ') << ' ' << RESET;
                }
                else {
                    if (contiene_numero(celda)) {
                        int numero = dame_numero(celda);
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