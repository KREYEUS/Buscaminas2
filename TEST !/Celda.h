// Nombres de los integrantes del grupo: Senbo Zhou Pan y Ximena Pizarro

#pragma once

typedef enum { NUMERO, VACIA, MINA } tEstado;

typedef struct {
	bool visible;
	tEstado estado;
	int numero;
	bool marcada;
} tCelda;

void inicializar(tCelda& celda);
tEstado dameEstado(const tCelda& celda);
int dameNumero(const tCelda& celda);
bool esVisible(const tCelda& celda);
bool  esMina(const tCelda& celda);
bool estaVacia(const tCelda& celda);
bool contieneNumero(const tCelda& celda);
bool estaMarcada(const tCelda& celda);
void  descubrir_celda(tCelda& celda);
void ocultarCelda(tCelda& celda);
void  poner_mina(tCelda& celda);
void  marcar_celda(tCelda& celda);
void  desmarcar_celda(tCelda& celda);
void poner_numero(tCelda& celda, int num);
