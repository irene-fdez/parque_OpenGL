/*************************************************************************/
/*                                                                       */
/*   examinar.c                                                          */
/*   Rev. 3.0  01/09/2012   Universidad Jaume I de Castellón             */
/*                                                                       */
/*************************************************************************/

/***************** INCLUDES DE LAS LIBRERIAS NECESARIAS ******************/

#include "examinar.h"
#include "glig.h"
#include "material.h"
#include "luces.h"

#include <stdio.h>
#include <math.h>


/******************************************************************************************/
/* Establece el area visible y el tipo de proyeccion                                      */
/* Parametros: int ancho --> Ancho del area visible                                       */
/*             int alto --> Alto del area visible                                         */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void TamanyoVentana(GLsizei ancho, GLsizei alto)
{
	//Definicion del viewport
	glViewport(0, 0, ancho, alto);

	//Definicion de la vista
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	gluPerspective(50, (GLdouble)alto / (GLdouble)ancho, 1.0, 1000.0);
}

/******************************************************************************************/
/* Abre una ventana OpenGL                                                                */
/* Parametros: int numeroArgumentos --> El numero de argumentos en la llamada al programa */
/*             char ** listaArgumentos --> Vector de cadenas con cada argumento           */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void AbreVentana(int numeroArgumentos, char** listaArgumentos)
{
	glutInit(&numeroArgumentos, listaArgumentos);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(VentanaAncho, VentanaAlto);
	glutInitWindowPosition(VentanaX, VentanaY);
	glutCreateWindow(listaArgumentos[0]);
	glutDisplayFunc(Dibuja);
	glutReshapeFunc(TamanyoVentana);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //Establece el color de borrado
	glClear(GL_COLOR_BUFFER_BIT); //Borra el buffer de color
}


/******************************************************************************************/
/* Define las acciones tras una pulsacion del teclado                                     */
/* Parametros: unsigned char key --> Codigo de la tecla pulsada                           */
/*             int x --> Coordenada x del cursor en el momento de pulsar la tecla         */
/*             int y --> Coordenada y del cursor en el momento de pulsar la tecla         */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void Teclado(unsigned char tecla, int x, int y)
{
	switch (tecla)
	{
	case 27: //Codigo de la tecla de Escape
		exit(0);
		break;

	case 'w':
		modo = WALK;
		printf("Modo = WALK      \r");
		break;

	case 'W':
		modo = WALK;
		printf("Modo = WALK      \r");
		break;

	case 'e':
		modo = EXAMINAR;
		printf("Modo = EXAMINAR    \r");
		break;

	case 'E':
		modo = EXAMINAR;
		printf("Modo = EXAMINAR    \r");
		break;

	case 'f':
		modo = FLY;
		printf("Modo = FLY      \r");
		break;

	case 'F':
		modo = FLY;
		printf("Modo = FLY      \r");
		break;

	case 'r':
		ox = MiddleX, oy = 20, oz = MiddleZ * 0.15; //Posicion del observador
		ix = MiddleX, iy = 20, iz = MiddleZ * 0.35 - PASO; //Posicion del punto de interes
		printf("Restablecer posicion de camara      \r");
		glutPostRedisplay();
		break;

	case 'R':
		ox = MiddleX, oy = 20, oz = MiddleZ * 0.15; //Posicion del observador
		ix = MiddleX, iy = 20, iz = MiddleZ * 0.35 - PASO; //Posicion del punto de interes
		printf("Restablecer posicion de camara      \r");
		glutPostRedisplay();
		break;
	}
}


/******************************************************************************************/
/* Define las acciones tras una pulsacion del teclado ampliado                            */
/* Parametros: unsigned char key --> Codigo de la tecla pulsada                           */
/*             int x --> Coordenada x del cursor en el momento de pulsar la tecla         */
/*             int y --> Coordenada y del cursor en el momento de pulsar la tecla         */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void TecladoAmpliado(int tecla, int x, int y) {
	switch (tecla) {
	case GLUT_KEY_PAGE_UP:
		if (modo == FLY) {
			beta = beta + 1.50;
			if (beta > 360.0) beta = beta - 360.0;
			iy = oy + PASO * sin(grad2rad(beta));
		}
		break;
	case GLUT_KEY_UP: //Pulsacion cursor arriba del teclado ampliado
		if (modo == WALK || modo == FLY) {
			ox = ix;
			oz = iz;
			ix = ox + PASO * sin(grad2rad(alfa));
			iz = oz - PASO * cos(grad2rad(alfa));
			if (modo == FLY) {
				oy = iy;
				iy = iy + PASO * sin(grad2rad(beta));
			}
		}
		else if (modo == EXAMINAR) {
			beta = beta - 1.50;
			if (beta < 0.0) beta = beta + 360.0;
			iy = oy + PASO * sin(grad2rad(beta));
		}
		break;

	case GLUT_KEY_PAGE_DOWN:
		if (modo == FLY) {
			beta = beta - 1.50;
			if (beta > 360.0) beta = beta - 360.0;
			iy = oy + PASO * sin(grad2rad(beta));
		}
		break;
	case GLUT_KEY_DOWN: //Pulsacion cursor abajo del teclado ampliado
		if (modo == WALK || modo == FLY) {
			ox = ox - (ix - ox);
			oz = oz - (iz - oz);
			ix = ox + PASO * sin(grad2rad(alfa));
			iz = oz - PASO * cos(grad2rad(alfa));
			if (modo == FLY) {
				iy = oy;
				oy = oy - PASO * sin(grad2rad(beta));
			}
		}
		else if (modo == EXAMINAR) {
			beta = beta + 1.50;
			if (beta > 360.0) beta = beta - 360.0;
			iy = oy + PASO * sin(grad2rad(beta));
		}
		break;

	case GLUT_KEY_RIGHT: //Pulsacion cursor derecha del teclado ampliado
		alfa = alfa + 15.0;
		if (alfa > 360.0) alfa = alfa - 360.0;
		ix = ox + PASO * sin(grad2rad(alfa));
		iz = oz - PASO * cos(grad2rad(alfa));
		break;

	case GLUT_KEY_LEFT: //Pulsacion cursor izquierda del teclado ampliado
		alfa = alfa - 15.0;
		if (alfa < 0.0) alfa = alfa + 360.0;
		ix = ox + PASO * sin(grad2rad(alfa));
		iz = oz - PASO * cos(grad2rad(alfa));
		break;
	}
	glutPostRedisplay();
}


//Rutina de definición de eventos 
/******************************************************************************************/
/* Inicia las funciones de callback                                                       */
/* Parametros: Ninguno                                                                    */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void IniciaFuncionesCallback(void) {
	glutKeyboardFunc(Teclado);
	glutSpecialFunc(TecladoAmpliado);
}


/******************************************************************************************/
/* Funcion de dibujado                                                                    */
/* Parametros: Ninguno                                                                    */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void Dibuja(void) {
	//Transformacion de la camara
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(ox, oy, oz, ix, iy, iz, 0, 1, 0);

	/* Defino y activo las luces */
	Luz0();
	Luz1 ();

	//Llamadas a las display lists
	DibujaEscena();

	glFlush();
}
/******************************************************************************************/
/* Inicializa propiedades de la visualizacion OpenGL                                      */
/* Parametros: Ninguno.                                                                   */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void IniciaOpenGL() {

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); /* Establece el color de borrado */

	/* Especifica el tipo de la comparación en el Z-buffer */
	glDepthFunc(GL_LEQUAL);

	/* Activa el Z-buffer */
	glEnable(GL_DEPTH_TEST);

	/* Elige las caras a eliminar y define que se va a pintar en sentido horario*/
	glFrontFace(GL_CW);

	/* Inicia las luces */
	IniciaLuces();

	glEnable(GL_TEXTURE_2D);
}

/******************************************************************************************/
/* Funcion para iniciar las texturas                                                      */
/* Parametros: Ninguno                                                                    */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void IniciaTexturas() {
	initTexturaCielo();
	initTexturaBosque();
	initTexturaHierba();
	initTexturaAgua();
	initTexturaCamino();
	initTexturaCesped();
	initTexturaBaldosa();
	initTexturaMadera();
	initTexturaColumna();
	initTexturaBaldosaF();
	initTexturaHojas();
	initTexturaTejado();
	initTexturaMortero();
	initTexturaAcero();
}

/******************************************************************************************/
/* Funcion para incicar las intrucciones de inspección de la escena						  */
/* Parametros: Ninguno                                                                    */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void Instrucciones() {
	printf("INTRUCCIONES: \n\t Restablecer la posicion de la camara: [ R | r ] \
						\n\t Cambiar a modo FLY: [ F | f ] \
						\n\t Cambiar a modo WALK: [ W | w ] \
						\n\t Cambiar a modo EXAMINAR: [ E | e ]\n\n");
}

/******************************************************************************************/
/* Funcion principal                                                                      */
/* Parametros: int numeroArgumentos --> El numero de argumentos en la llamada al programa */
/*             char ** listaArgumentos --> Vector de cadenas con cada argumento           */
/* Salida: Un entero que se devuelve al sistema al acabar la ejecucion del programa       */
/******************************************************************************************/
int main(int numArgumentos, char** listaArgumentos) {
	//Creación de la ventana de la aplicación
	AbreVentana(numArgumentos, listaArgumentos);

	//establece las propiedades de visualizacion de OpenGL
	IniciaOpenGL();

	//Rutinas para el control de eventos
	IniciaFuncionesCallback();

	//Inicia las texturas que se utilizaran
	IniciaTexturas();

	//Crea las display list de cada cuadrica
	IniciaDisplayLists();

	//Muestra las intrucciones de uso de las opciones de desplazamiento por la escena
	Instrucciones();
	printf("Modo = EXAMINAR\r");

	//A la espera de eventos....
	glutMainLoop();

	return (0);
}