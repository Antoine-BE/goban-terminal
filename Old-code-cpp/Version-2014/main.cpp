#include "Tablero.cpp"

Window W("Tablero", 958,648);

int main()
{
	int i,j,p,t,x,y,k,capb,capn,nc,nr,nraux,ncaux;

	int nr0,nc0,nc1,nr1,nc2,nr2,nc3,nr3,nc4,nr4,nc5,nr5,nc6,nr6,nc7,nr7,nc8,nr8,nc9,nr9,nc10,nr10,nc11,nr11;
	char *c;
	Partida activa;

	COLORREF **Pa,**P1,**Gu,**G1,**Bl,**B1,**Ne,**N1,**pant,**N,**B,**Adelante,**Atras,**Aux;
	DimensionesBmp("atras.bmp",&nr0,&nc0);
	DimensionesBmp("adelante.bmp",&nr1,&nc1);
	DimensionesBmp("capB.bmp",&nr2,&nc2);
	DimensionesBmp("capB2.bmp",&nr3,&nc3);
	DimensionesBmp("capN.bmp",&nr4,&nc4);
	DimensionesBmp("capN2.bmp",&nr5,&nc5);
	DimensionesBmp("guardar1.bmp",&nr6,&nc6);
	DimensionesBmp("guardar2.bmp",&nr7,&nc7);
	DimensionesBmp("pasar1.bmp",&nr8,&nc8);
	DimensionesBmp("pasar2.bmp",&nr9,&nc9);
	DimensionesBmp("PN.bmp",&nr10,&nc10);
	DimensionesBmp("PB.bmp",&nr11,&nc11);
	DimensionesBmp("tablero.bmp",&nraux,&ncaux);

	Atras=(COLORREF **)malloc(nr0*sizeof(COLORREF *));
	Adelante=(COLORREF **)malloc(nr1*sizeof(COLORREF *));
	Bl=(COLORREF **)malloc(nr2*sizeof(COLORREF *));
	B1=(COLORREF **)malloc(nr3*sizeof(COLORREF *));
	Ne=(COLORREF **)malloc(nr4*sizeof(COLORREF *));
	N1=(COLORREF **)malloc(nr5*sizeof(COLORREF *));
	Gu=(COLORREF **)malloc(nr6*sizeof(COLORREF *));
	G1=(COLORREF **)malloc(nr7*sizeof(COLORREF *));
	Pa=(COLORREF **)malloc(nr8*sizeof(COLORREF *));
	P1=(COLORREF **)malloc(nr9*sizeof(COLORREF *));
	N=(COLORREF **)malloc(nr10*sizeof(COLORREF *));
	B=(COLORREF **)malloc(nr11*sizeof(COLORREF *));
	Aux=(COLORREF **)malloc(nraux*sizeof(COLORREF *));

	for(i=0;i<nr0;i++)Atras[i]=(COLORREF *)malloc(nc0*sizeof(COLORREF));
	for(i=0;i<nr1;i++)Adelante[i]=(COLORREF *)malloc(nc1*sizeof(COLORREF));
	for(i=0;i<nr2;i++)Bl[i]=(COLORREF *)malloc(nc2*sizeof(COLORREF));
	for(i=0;i<nr3;i++)B1[i]=(COLORREF *)malloc(nc3*sizeof(COLORREF));
	for(i=0;i<nr4;i++)Ne[i]=(COLORREF *)malloc(nc4*sizeof(COLORREF));
	for(i=0;i<nr5;i++)N1[i]=(COLORREF *)malloc(nc5*sizeof(COLORREF));
	for(i=0;i<nr6;i++)Gu[i]=(COLORREF *)malloc(nc6*sizeof(COLORREF));
	for(i=0;i<nr7;i++)G1[i]=(COLORREF *)malloc(nc7*sizeof(COLORREF));
	for(i=0;i<nr8;i++)Pa[i]=(COLORREF *)malloc(nc8*sizeof(COLORREF));
	for(i=0;i<nr9;i++)P1[i]=(COLORREF *)malloc(nc9*sizeof(COLORREF));
	for(i=0;i<nr10;i++)N[i]=(COLORREF *)malloc(nc10*sizeof(COLORREF));
	for(i=0;i<nr11;i++)B[i]=(COLORREF *)malloc(nc11*sizeof(COLORREF));
	for(i=0;i<nraux;i++)Aux[i]=(COLORREF *)malloc(ncaux*sizeof(COLORREF));

	DimensionesBmp("pant.bmp",&nr,&nc);
	pant=(COLORREF **)malloc(nr*sizeof(COLORREF *));
	for(i=0;i<nr;i++)pant[i]=(COLORREF *)malloc(nc*sizeof(COLORREF));


	LeeBmpColor(Bl,"capB.bmp");
	LeeBmpColor(B1,"capB2.bmp");
	LeeBmpColor(Ne,"capN.bmp");
	LeeBmpColor(N1,"capN2.bmp");
	LeeBmpColor(Gu,"guardar1.bmp");
	LeeBmpColor(G1,"guardar2.bmp");
	LeeBmpColor(Pa,"pasar1.bmp");
	LeeBmpColor(P1,"pasar2.bmp");
	LeeBmpColor(N,"PN.bmp");
	LeeBmpColor(B,"PB.bmp");
	LeeBmpColor(pant,"pant.bmp");
	LeeBmpColor(Aux,"tablero.bmp");

    Tablero *actual=activa.inicio;
	while(activa.pasar<2)
	{
		k=MouseHit(&x,&y);
		if(k==1)
		{
			if(x<659 && y<659) //esta en tablero
			{
				for(p=0;p<19;p++)
				{
					if(y-26>p*32 && y-26<(p+1)*32)i=p;
					if(x-26>p*32 && x-26<(p+1)*32)j=p;
				}
				if(actual->poner_ficha(i,j))
				{
					if(activa.pasar==1)
					{
						activa.pasar=0;
						for(p=0;p<46;p++) for(t=0;t<187;t++)
                            pant[713+p][39+t]=Pa[p][t];
					}
                    actual->mapeo(pant,B,N,Aux,alpha);
                    actual->turno_activo(pant,Bl,Ne,B1,N1);
				}
			}
			else if(x>713 && y>39 && x<900 && y<85)//boton para pasar
			{
				if(activa.pasar==0)for(i=0;i<46;i++) for(j=0;j<187;j++) pant[39+i][713+j]=P1[i][j];
				else for(i=0;i<46;i++) for(j=0;j<187;j++) pant[713+i][39+j]=Pa[i][j];
				activa.pasar++;
				actual->turno++;
				actual->turno_activo(pant,Bl,Ne,B1,N1);
			}
			else if(x>712 && y>169 && x<899 && y<247)//boton para abrir
			{
				while(1)
				{
					c=InDialog("¿Qué archivo desea abrir?");
					activa.abrir_partida(c,actual);
					actual->mapeo(pant,B,N,Aux,alpha);
					actual->turno_activo(pant,Bl,Ne,B1,N1);
					W.PlotCBitmap(pant,nr,nc,0,0,1);
					if(MessageYesNo("Â¿Es el archivo que querÃ­a?"))break;
				}

			}
			else if(x>713 && y>113 && x<900 && y<159)//boton para guardar
			{
				for(i=0;i<46;i++) for(j=0;j<187;j++) pant[113+i][j+713]=G1[i][j];
				W.PlotCBitmap(pant,nr,nc,0,0,1);
				c=InDialog("¿Dónde quiere guardar?");

				if(MessageYesNo("¿Desea continuar?")==0)return 0;
				for(i=0;i<46;i++) for(j=0;j<187;j++) pant[113+i][j+713]=Gu[i][j];
			}
		}
		W.PlotCBitmap(pant,nr,nc,0,0,1);
	}
	MessageOk("Seleccione las piezas negras \"muertas\" y luego presione \"pasar\"");
	while(activa.pasar<3)
	{
		k=MouseHit(&x,&y);
		if(k==1)
		{
			if(x<659 && y<659)
			{
				for(p=0;p<19;p++)
				{
					if(y-26>p*32 && y-26<(p+1)*32)i=p;
					if(x-26>p*32 && x-26<(p+1)*32)j=p;
				}
				if(actual->tablero[i][j].estado==Negro)actual->capturas_blancas+=actual->captura(i,j);
			}
			else if(x>713 && y>39 && x<900 && y<85)//boton para pasar
			{
				for(i=0;i<46;i++) for(j=0;j<187;j++) pant[713+i][39+j]=Pa[i][j];
				activa.pasar++;
			}
		}
		actual->mapeo(pant,B,N,Aux,alpha);
		W.PlotCBitmap(pant,nr,nc,0,0,1);
	}
	MessageOk("Seleccione las piezas blancass \"muertas\" y luego presione \"pasar\"");
	while(activa.pasar<4)
	{
		k=MouseHit(&x,&y);
		if(k==1)
		{
			if(x<659 && y<659)
			{
				for(p=0;p<19;p++)
				{
					if(y-26>p*32 && y-26<(p+1)*32)i=p;
					if(x-26>p*32 && x-26<(p+1)*32)j=p;
				}
				if(actual->tablero[i][j].estado==Blanco)actual->capturas_negras+=actual->captura(i,j);
			}
			else if(x>713 && y>39 && x<900 && y<85)//boton para pasar
			{
				for(i=0;i<46;i++) for(j=0;j<187;j++) pant[39+i][713+j]=P1[i][j];
				activa.pasar++;
			}
		}
		actual->mapeo(pant,B,N,Aux,alpha);
		W.PlotCBitmap(pant,nr,nc,0,0,1);
	}
	char *ese;
	if(actual->capturas_negras>actual->capturas_blancas)
	{
		sprintf(ese,"Negro gana por %d",capn-capb);
		MessageOk(ese);
	}
	if(actual->capturas_negras<actual->capturas_blancas)
	{
		sprintf(ese,"Blanco gana por %d",capb-capn);
		MessageOk(ese);
	}
	if(actual->capturas_negras==actual->capturas_blancas)
	{
		MessageOk("Empate");
	}
	for(i=0;i<nr0;i++)free(Atras[i]);
	for(i=0;i<nr1;i++)free(Adelante[i]);
	for(i=0;i<nr2;i++)free(Bl[i]);
	for(i=0;i<nr3;i++)free(B1[i]);
	for(i=0;i<nr4;i++)free(Ne[i]);
	for(i=0;i<nr5;i++)free(N1[i]);
	for(i=0;i<nr6;i++)free(Gu[i]);
	for(i=0;i<nr7;i++)free(G1[i]);
	for(i=0;i<nr8;i++)free(Pa[i]);
	for(i=0;i<nr9;i++)free(P1[i]);
	for(i=0;i<nr10;i++)free(N[i]);
	for(i=0;i<nr11;i++)free(B[i]);
	free(Bl);
	free(B1);
	free(Ne);
	free(N1);
	free(Adelante);
	free(Atras);
	free(Gu);
	free(G1);
	free(Pa);
	free(P1);
	free(N);
	free(B);
	free(pant);
}
