// Nombres de los integrantes del grupo: Senbo Zhou Pan y Ximena Pizarro

#include "Celda.h"
using namespace std;

void inicializar(tCelda& celda)
{
	celda.visible = false;
	celda.estado = VACIA;
	celda.numero = 0;
	celda.marcada = false;
}

tEstado dameEstado(const tCelda& celda)
{
	return celda.estado;
}

int dameNumero(const tCelda& celda)
{
	return celda.numero;
}

bool esVisible(const tCelda& celda)
{
	return celda.visible;
}

bool  esMina(const tCelda& celda)
{
	return celda.estado == MINA;
}

bool estaVacia(const tCelda& celda)
{
	return celda.estado == VACIA;
}

bool contieneNumero(const tCelda& celda)
{
	return celda.estado == NUMERO;
}

bool estaMarcada(const tCelda& celda)
{
	return celda.marcada;
}

void  descubrir_celda(tCelda& celda)
{
	celda.visible = true;
}

void ocultarCelda(tCelda& celda)
{
	celda.visible = false;
}

void  poner_mina(tCelda& celda) {
	celda.estado = MINA;
}

void  marcar_celda(tCelda& celda)
{
	celda.marcada = true;
}

void  desmarcar_celda(tCelda& celda)
{
	celda.marcada = false;
}

void poner_numero(tCelda& celda, int num) {
	celda.numero = num;

	if (celda.estado == VACIA) {
		celda.estado = NUMERO;
	}
}