#include "Ficha.h"

bool Tablero::poner_ficha(int x, int y)
{
    if(tablero[x][y].estado==Vacio) //que no este ocupado el lugar
	{
        next=new Tablero(*this);
        *this=*this->next;
        bitset<2> aux(turno%2+1);
		tablero[x][y].estado=aux;
		tablero[x][y].libertades=4;
		if(x==0 || x==18) tablero[x][y].libertades--;
		if(y==0 || y==18) tablero[x][y].libertades--;
		if(y<18 && tablero[x][y+1].estado!=Vacio)
		{
			tablero[x][y].libertades--;
			tablero[x][y+1].libertades--;
		}
		if(y>0 && tablero[x][y-1].estado!=Vacio)
		{
			tablero[x][y].libertades--;
			tablero[x][y-1].libertades--;
		}
		if(x<18 && tablero[x+1][y].estado!=Vacio)
		{
			tablero[x][y].libertades--;
			tablero[x+1][y].libertades--;
		}
		if(x>0 && tablero[x-1][y].estado!=Vacio)
		{
			tablero[x][y].libertades--;
			tablero[x-1][y].libertades--;

		}
		if(x>0 && tablero[x-1][y].estado!=aux && tablero[x-1][y].estado!=Vacio)
        {
            if(checavida(x-1,y)==0)//un grupo hacia la izquierda esta muerto
            {
                if(turno%2)capturas_blancas+=captura(x-1,y);
                else capturas_negras+=captura(x-1, y);
            }
        }
        if(x<18 && tablero[x+1][y].estado!=aux && tablero[x+1][y].estado!=Vacio)
        {
            if(checavida(x+1,y)==0)//un grupo hacia la derecha esta muerto
            {
                if(turno%2) capturas_blancas+=captura(x+1,y);
                else capturas_negras+=captura(x+1,y);
            }
        }
        if(y>0 && tablero[x][y-1].estado!=aux && tablero[x][y-1].estado!=Vacio)
        {
            if(checavida(x,y-1)==0)//un grupo hacia arriba esta muerto
            {
                if(turno%2)capturas_blancas+=captura(x,y-1);
                else capturas_negras+=captura(x,y-1);
            }
        }
        if(y<18 && tablero[x][y+1].estado!=aux && tablero[x][y+1].estado!=Vacio)
        {
            if(checavida(x,y+1)==0)//un grupo hacia abajo esta muerto
            {
                if(turno%2)capturas_blancas+=captura(x,y+1);
                else capturas_negras+=captura( x, y+1);
            }
        }
        if(checavida(x,y)==0) //si no capturo nada, entonces se trata como suicidio
        {
            if(turno%2)capturas_negras+=captura(x,y);
            else capturas_blancas+=captura(x,y);
        }
        turno++;
		return 1;
	}
	return 0;
}

bool Tablero::vida_grupo(int x, int y)
{
    if(tablero[x][y].libertades>0)return 1;
	if(x>0)
	{
		if(tablero[x-1][y].estado==tablero[x][y].estado && vida_grupo(x-1,y)==1)return 1;
	}
	if(y>0)
	{
		if(tablero[x][y-1].estado==tablero[x][y].estado && vida_grupo(x,y-1)==1)return 1;
	}
	if(x<18)
	{
		if(tablero[x+1][y].estado==tablero[x][y].estado && vida_grupo(x+1,y)==1)return 1;
	}
	if(y<18)
	{
		if(tablero[x][y+1].estado==tablero[x][y].estado && vida_grupo(x,y+1)==1)return 1;
	}
	return 0;
}

int Tablero::captura(int x,int y)
{
	int numero_cap=0;
	if(tablero[x][y].estado!=Vacio)
	{
        bitset<2> aux(tablero[x][y].estado);
		if(tablero[x][y].libertades==0)
		{
			tablero[x][y].estado=Vacio;
			
			numero_cap++;
			if(x>0)
			{
	            if(tablero[x-1][y].estado==aux)
	            {
	                numero_cap+=captura(x-1,y);
	            }
	            else
	            {
	                tablero[x-1][y].libertades++;
	            }
			}
			if(y>0)
			{
				if(tablero[x][y-1].estado==aux)
	            {
	                numero_cap+=captura(x,y-1);
	            }
	            else
	            {
	                tablero[x][y-1].libertades++;
	            }
			}
			if(x<18)
			{
				if(tablero[x+1][y].estado==aux)
	            {
	                numero_cap+=captura(x+1,y);
	            }
	            else
	            {
	                tablero[x+1][y].libertades++;
	            }
			}
			if(y<18)
			{
				if(tablero[x][y+1].estado==aux)
	            {
	                numero_cap+=captura(x,y+1);
	            }
	            else
	            {
	                tablero[x][y+1].libertades++;
	            }
			}
		}
	}
	return numero_cap;
}

bool Tablero::checavida(int x,int y)
{
	if(vida_grupo(x,y)==0)
	{
		bitset<2> aux(tablero[x][y].estado);
		if(x>0)
		{
			if(tablero[x-1][y].estado!=Vacio && tablero[x-1][y].estado!=aux)
			{
				if(vida_grupo(x-1,y)==0)return 1;
			}
		}
		if(x<18)
		{
			if(tablero[x+1][y].estado!=Vacio && tablero[x+1][y].estado!=aux)
			{
				if(vida_grupo(x+1,y)==0)return 1;
			}
		}
		if(y>0)
		{
			if(tablero[x][y-1].estado!=Vacio && tablero[x][y-1].estado!=aux)
			{
				if(vida_grupo(x,y-1)==0)return 1;
			}
		}
		if(y<18)
		{
			if(tablero[x][y+1].estado!=Vacio && tablero[x][y+1].estado!=aux)
			{
				if(vida_grupo(x,y+1)==0)return 1;
			}
		}
		return 0;
	}
	return 1;
}

Tablero::Tablero(Tablero *padre, Tablero *hijo)
{
    if(padre==NULL)
    {
        for(int i=0;i<19;i++)
            for(int j=0;j<19;j++)
            {
                tablero[i][j].estado=0;
                tablero[i][j].libertades=4;
                if(i==0 || i==18) tablero[i][j].libertades--;
                if(j==0 || j==18) tablero[i][j].libertades--;
            }
        turno=0;
        capturas_blancas=0;
        capturas_negras=0;
    }
    else
    {
        for(int i=0;i<19;i++)
            for(int j=0;j<19;j++)
            {
                tablero[i][j].estado=padre->tablero[i][j].estado;
                tablero[i][j].libertades=padre->tablero[i][j].libertades;
                if(i==0 || i==18) tablero[i][j].libertades--;
                if(j==0 || j==18) tablero[i][j].libertades--;
            }
        turno=padre->turno;
        capturas_blancas=padre->capturas_blancas;
        capturas_negras=padre->capturas_negras;
    }
    next=hijo;
}

void Tablero::mapeo(COLORREF **pant,COLORREF **B,COLORREF **N,COLORREF **aux,COLORREF alpha)
{
	int i,j,n,m;
	for(i=0;i<19;i++)for(j=0;j<19;j++)
	{
		if(tablero[i][j].estado==1)
		{
			for(n=0;n<32;n++)for(m=0;m<32;m++)
			{
				if(N[n][m]!=alpha) pant[26+i*32+n][26+32*j+m]=N[n][m];
			}
		}
		if(tablero[i][j].estado==2)
		{
			for(n=0;n<32;n++)for(m=0;m<32;m++)
			{
				if(B[n][m]!=alpha)pant[26+i*32+n][26+32*j+m]=B[n][m];
			}
		}
		if(tablero[i][j].estado==0)
		{
			for(n=0;n<32;n++)for(m=0;m<32;m++)
			{
				pant[26+i*32+n][26+32*j+m]=aux[26+i*32+n][26+32*j+m];
			}
		}
	}
}

void Tablero::turno_activo(COLORREF **pantalla,COLORREF **B1,COLORREF **N1,COLORREF **B2,COLORREF **N2)
{
    int i,j;
	if(turno%2==0)
	{
		for(i=0;i<157;i++)for(j=0;j<189;j++)
		{
			pantalla[i+263][j+712]=B2[i][j];
			pantalla[i+450][j+712]=N1[i][j];
		}
	}
	else
	{
		for(i=0;i<157;i++)for(j=0;j<189;j++)
		{
			pantalla[i+263][j+712]=B1[i][j];
			pantalla[i+450][j+712]=N2[i][j];
		}
	}
}

Partida::Partida()
{
	inicio=new Tablero();
	pasar=0;
}

void Partida::guardar_partida(char *nombre)
{
	FILE *arch;
    arch=fopen(nombre,"wb");
    Tablero *aux=inicio;
    while(aux!=NULL)
    {
        for(int i=0;i<19;i++)
            for(int j=0;j<19;j++)
                fwrite(&(aux->tablero[i][j]),sizeof(ficha),1,arch);
        aux=aux->next;
    }
    fclose(arch);
}

void Partida::abrir_partida(char *nombre,Tablero *actual)
{
	FILE *arch;
    arch=fopen(nombre,"rb");
    Tablero *aux=inicio;
    long Size;
    fseek(arch, 0, SEEK_END);
    Size=ftell(arch);
    for(long k=0;k<Size;k++)
    {
        for(int i=0;i<19;i++)
            for(int j=0;j<19;j++)
                fread(&(aux->tablero[i][j]),sizeof(ficha),1,arch);
        aux->turno=k;
        aux->next=new Tablero(aux);
        aux=aux->next;
    }
    actual=aux;
    fclose(arch);
}
