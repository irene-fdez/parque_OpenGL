/*************************************************************************/
/*                                                                       */
/*   examinar.h                                                          */
/*   Rev. 3.0  01/09/2012   Universidad Jaume I de Castellón             */
/*                                                                       */
/*************************************************************************/

#ifndef EXAMINAR_H
#define EXAMINAR_H

#include <stdlib.h>
#include "glut.h"
#include "modelado.h"

//Funcion de conversion de grados a radianes
#define  grad2rad(x)  ((float) (3.14159 * x) / 180.0)
#define PASO -0.5 //Definicion del paso para el movimiento del observador

#define WALK 1
#define EXAMINAR 2
#define FLY 3

//Variables Globales del modulo
int VentanaAncho = 1000, VentanaAlto = 1000; //Tamanyo de la ventana
int VentanaX = 100, VentanaY = 100; //Posicion de la ventana
GLdouble  alfa = 0.0, beta = 0.0, gamma = 0.0, z = 0.0;
GLuint cuadrica;
double ox = MiddleX, oy =  20, oz = MiddleZ*0.20; //Posicion del observador
double ix = MiddleX, iy =  20, iz = MiddleZ * 0.35 - PASO; //Posicion del punto de interes
int w = 1, a = 1;
int modo = EXAMINAR;

//Abre una ventana OpenGL
void AbreVentana(int numeroArgumentos, char** listaArgumentos);

//Inicia parametros de la OpenGL
void IniciaOpenGL(void);

//Funcion de dibujado
void Dibuja(void);

//Establece el area visible
void TamanyoVentana(GLsizei ancho, GLsizei alto);

//Inicia las funciones de Callback
void IniciaFuncionesCallback(void);

//Define las acciones tras una pulsacion del teclado
void Teclado(unsigned char tecla, int x, int y);

//Inicializa las texturas
void IniciaTexturas();

//Imprime las distintas opciones de inspeccion de la escena
void Instrucciones();
#endif