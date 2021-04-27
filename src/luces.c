/*************************************************************************/
/*                                                                       */
/*   luces.c		                                                     */
/*   Rev. 2.0  01/01/2002   AUTORES: O. Belmonte, M. Chover, J. Ribelles */
/*                                                                       */
/*************************************************************************/

/***************** INCLUDES DE LAS LIBRERIAS NECESARIAS ******************/


#include "glut.h"

/********************** RUTINA DE INICIO *************************/

/******************************************************************************************/
/* Inicia los parametros de iluminacion de OpenGL                                         */
/* Parametros: Ninguno                                                                    */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void IniciaLuces(void)
{
	GLfloat lmodel_ambient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	
	glEnable(GL_DEPTH_TEST); // Eliminación de superficies ocultas
	glFrontFace(GL_CCW); // Los polígonos en sentido antihorario están orientados hacia afuera

	/* Par�metros del modelo de iluminaci�n */
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

	/* Activa la iluminaci�n de la escena */
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
}


/*********************** DEFINICION DE LUCES ****************************/

/******************************************************************************************/
/* Define y activa la luz 0                                                               */
/* Parametros: Ninguno                                                                    */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void Luz0(void)
{
	float luz_posicion[] = {180.0f, 50.0f, 150.0f, 0.0f};
	float luz_ambiente[] = { 1.0f, 1.0f, 1.0f, 1.0f};
	float luz_difusa[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	float luz_especular[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	float luz_direccion[] = { 150.0f, 50.0f, 180.0f};

	glLightfv(GL_LIGHT0, GL_POSITION, luz_posicion);
	glLightfv(GL_LIGHT0, GL_AMBIENT, luz_ambiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luz_difusa);
	glLightfv(GL_LIGHT0, GL_SPECULAR, luz_especular);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, luz_direccion);

	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 90);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 128.0f);

	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHT0);
}

/******************************************************************************************/
/* Define y activa la luz 1                                                               */
/* Parametros: Ninguno                                                                    */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void Luz1(void)
{
	float luz1_posicion[] = { 180.0f, 150.0f, 150.0f, 1.0f };
	float luz1_ambiente[] = { 0.6f, 0.6f, 0.6f, 0.0f };
	float luz1_difusa[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	float luz1_especular[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	float luz1_direccion[] = { 50.0f, 150.0f, 180.0f };

	glLightfv(GL_LIGHT1, GL_POSITION, luz1_posicion);
	glLightfv(GL_LIGHT1, GL_AMBIENT, luz1_ambiente);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, luz1_difusa);
	glLightfv(GL_LIGHT1, GL_SPECULAR, luz1_especular);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, luz1_direccion);

	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHT1);
}
