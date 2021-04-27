/*************************************************************************/
/*                                                                       */
/*   modelado.h                                                          */
/*   Rev. 3.0  01/09/2012   Universidad Jaume I de Castellón             */
/*                                                                       */
/*************************************************************************/

#ifndef MODELADO_H
#define MODELADO_H

#include <stdlib.h>
#include <math.h>
#include "glut.h"

#define SizeX 200 //Tamaño del terreno en X
#define SizeZ 200 //Tamaño del terreno en Z
#define MiddleX (SizeX/2)
#define MiddleZ (SizeZ/2)
#define numRegiones 9

typedef struct  Region { int id; int inicio_i; int inicio_j; float porcent_i; float porcent_j; int fin_i; int fin_j; } Region;

/* Identificadores de las display lists */
GLuint cielo, escena, terreno, abeto, arco, puente, cupula, columna, arbol, fuente, fuente2, banco, abeto, arbusto, valla;

/* Funciones de modelado */
/* Crea las distintas display lists */
void IniciaDisplayLists(void);

/* Dibuja la escena */
void DibujaEscena(void);

/* Crea una display list para el cielo */
void CreaCielo(void);

/* Crea una display list para el abeto */
void CreaAbeto(void);

/* Crea una display list para el arbol */
void CreaArbol(void);

/* Crea una display list para el arco */
void CreaArco(void);

/* Crea una display list para el terreno */
void CreaTerreno(void);

/*  Crea una display list para toda la escena */
void CreaEscena(void);

/* Crea una celda a partir de dos posiciones y su altura */
void CreaCelda(int i, int j, Region region);

/* Establece las texturas para cada region */
void TexturaPorRegion(int numRegion);

/*Funcion para pintar el suelo por region*/
void PintaRegion(int i, int j, Region region);

/* Define las regiones a pintar */
void DefineRegiones(void);

/* Crea una columna de la cupula */
void CreaColumna(void);

/* Crea una puente */
void CreaPuente();

/* Crea una cupula */
void CreaCupula();

/* Crea las fuente */
void CreaFuente();

/* Crea las fuente 2 */
void CreaFuente2();

/* Crea los bancos */
void CreaBanco();

/* Crea la valla */
void CreaValla();

/* Crea el arbusto */
void CreaArbusto();

/* Crea la region con un solo rectangulo */
void CreaRegion(Region region);
void CreaRegionGenerica(Region region);
void CreaRegionAgua(Region region);
void CreaRegionBaldosa(Region region);

/* Crea las distintas figuras que hay en la escena*/
void ColocaAbetos(Region region);
void ColocaArboles(Region region);
void ColocaJardineras(Region region);
void ColocaVallas();
void CreaCilindroExterior(float posx, float posy, float posz, float size, float altura);
void CreaCilindroInterior(float posx, float posy, float posz, float size, float altura);
void CreaCilindroInterior2(float posx, float posy, float posz, float size1, float size2, float altura);
void CreaCilindroExterior2(float posx, float posy, float posz, float size1, float size2, float altura);
#endif