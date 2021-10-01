#ifndef FICHA_H_INCLUDED
#define FICHA_H_INCLUDED
#include <bitset>
#include "Shell.cpp"

using namespace std;

COLORREF alpha=RGB(34,177,76);
bitset<2> Vacio(0),Blanco(1),Negro(2);

typedef struct
{
	bitset<2> estado; //0 corresponde a ninguna ficha, 1 corresponde a
	char libertades;
} ficha;

class Tablero
{
public:
    Tablero *next;
    Tablero *anterior;
    ficha tablero[19][19];
    int turno, capturas_blancas, capturas_negras;

    Tablero(Tablero *padre=NULL, Tablero *hijo=NULL);
	bool poner_ficha(int x, int y);
    bool vida_grupo(int x, int y);
    bool checavida(int x,int y);
    void turno_activo(COLORREF **pantalla,COLORREF **B1,COLORREF **N1,COLORREF **B2,COLORREF **N2); //ya esta
    void mapeo(COLORREF **pant,COLORREF **B,COLORREF **N,COLORREF **aux,COLORREF alpha);
    int captura(int x,int y);
};

class Partida
{
public:
    Tablero* inicio;
    int pasar;
	Partida();
    void guardar_partida(char *nombre);
    void abrir_partida(char *nombre,Tablero *actual);
};

#endif // FICHA_H_INCLUDED
