/*************************************************************************/
/*                                                                       */
/*   material.c                                                          */
/*   Rev. 2.0  01/01/2002   AUTORES: O. Belmonte, M. Chover, J. Ribelles */
/*                                                                       */
/*************************************************************************/

/***************** INCLUDES DE LAS LIBRERIAS NECESARIAS ******************/

#include "glut.h"
#include "material.h"

#include <stdio.h>

/********************** RUTINA DE INICIO **************************************************/

/******************************************************************************************/
/* Inicia OpenGL para poder definir las propiedades de los materiales                     */
/* Parametros: Ninguno                                                                    */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void IniciaMaterial(void)
{
  /* Se modificara las propiedades de color de material ambiente y difusa */
  glColorMaterial(GL_FRONT, GL_DIFFUSE);

  /* Se permite el cambio de la propiedad de material con glColor */
  glEnable(GL_COLOR_MATERIAL);
}

/*********************** DEFINICION DE MATERIALES *****************************************/

/******************************************************************************************/
/* Define las propiedades del material cobre                                              */
/* Parametros: Ninguno                                                                    */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void Cobre(void)
{
  glColor3f(1, 1, 1);
}


/*********************** ESPECIFICACI�N DE TEXTURAS****************************************/

/******************************************************************************************/
/* Lee una imagen de textura en formato tga                                               */
/* Parametros --> char *fichero : Cadena de caracteres con el nombre del fichero          */
/*				  int num: Numero que identifica la textura                               */
/* Salido --> Ninguna                                                                     */
/******************************************************************************************/
void leerTextura(char* fichero, int num)
{
  int   i, j;
  char  r, g, b, c;
  FILE* tga;

  /* Apertura del fichero TGA */
  if ((tga = fopen(fichero, "rb")) == NULL)
    printf("Error abriendo el fichero: %s\n", fichero);
  else
  {
    /* Lee los 18 primeros caracteres de la cabecera */
    for (j = 1; j <= 18; j++)
      fscanf(tga, "%c", &c);

    /* Lee la imagen */
    for (j = altoTextura - 1; j >= 0; j--)
    {
      for (i = anchoTextura - 1; i >= 0; i--)
      {
        fscanf(tga, "%c%c%c", &b, &g, &r);
        textura[num][j][i][0] = (GLubyte)r;
        textura[num][j][i][1] = (GLubyte)g;
        textura[num][j][i][2] = (GLubyte)b;
      }
    }
    fclose(tga);   /* Cierre del fichero TGA */
  }
}

/*********************** RUTINA DE CARGA Y ACTIVACION DE TEXTURAS *************************/

/******************************************************************************************/
/*									TEXTURA CIELO                                         */
/******************************************************************************************/
void initTexturaCielo() {
  leerTextura("./resources/cielo.tga", 0);
}
void texturaCielo(void)
{
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexImage2D(GL_TEXTURE_2D, 0, 3, anchoTextura, altoTextura, 0, GL_RGB, GL_UNSIGNED_BYTE, textura[0]);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  glEnable(GL_TEXTURE_2D);
}

/******************************************************************************************/
/*									TEXTURA BOSQUE                                        */
/******************************************************************************************/
void initTexturaBosque() {
  leerTextura("./resources/bosque.tga", 1);
}
void texturaBosque(void)
{
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexImage2D(GL_TEXTURE_2D, 0, 3, anchoTextura, altoTextura, 0, GL_RGB, GL_UNSIGNED_BYTE, textura[1]);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  glEnable(GL_TEXTURE_2D);
}

/******************************************************************************************/
/*									TEXTURA HIERBA                                        */
/******************************************************************************************/
void initTexturaHierba() {
  leerTextura("./resources/hierba.tga", 2);
}
void texturaHierba(void)
{
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexImage2D(GL_TEXTURE_2D, 0, 3, anchoTextura, altoTextura, 0, GL_RGB, GL_UNSIGNED_BYTE, textura[2]);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  glEnable(GL_TEXTURE_2D);

}

/******************************************************************************************/
/*									TEXTURA AGUA                                          */
/******************************************************************************************/
void initTexturaAgua() {
  leerTextura("./resources/agua2.tga", 3);
}
void texturaAgua(void)
{
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexImage2D(GL_TEXTURE_2D, 0, 3, anchoTextura, altoTextura, 0, GL_RGB, GL_UNSIGNED_BYTE, textura[3]);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  glEnable(GL_TEXTURE_2D);

}

/******************************************************************************************/
/*									TEXTURA CAMINO                                        */
/******************************************************************************************/
void initTexturaCamino() {
  leerTextura("./resources/camino.tga", 4);
}
void texturaCamino(void)
{
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexImage2D(GL_TEXTURE_2D, 0, 3, anchoTextura, altoTextura, 0, GL_RGB, GL_UNSIGNED_BYTE, textura[4]);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  glEnable(GL_TEXTURE_2D);

}

/******************************************************************************************/
/*									TEXTURA CESPED										  */
/******************************************************************************************/
void initTexturaCesped() {
  leerTextura("./resources/cesped.tga", 5);
}
void texturaCesped(void)
{
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexImage2D(GL_TEXTURE_2D, 0, 3, anchoTextura, altoTextura, 0, GL_RGB, GL_UNSIGNED_BYTE, textura[5]);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  glEnable(GL_TEXTURE_2D);
}


///========================================================================================
///========================================================================================
///========================================================================================
///========================================================================================


/******************************************************************************************/
/*									TEXTURA BALDOSA										  */
/******************************************************************************************/
void initTexturaBaldosa() {
  leerTextura("./resources/baldosamini.tga", 6);
}
void texturaBaldosa(void)
{
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexImage2D(GL_TEXTURE_2D, 0, 3, anchoTextura, altoTextura, 0, GL_RGB, GL_UNSIGNED_BYTE, textura[6]);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  glEnable(GL_TEXTURE_2D);
}

/******************************************************************************************/
/*									TEXTURA TRONCO										  */
/******************************************************************************************/
void initTexturaTronco() {
  leerTextura("./resources/tronco.tga", 7);
}
void texturaTronco(void)
{
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexImage2D(GL_TEXTURE_2D, 0, 3, anchoTextura, altoTextura, 0, GL_RGB, GL_UNSIGNED_BYTE, textura[7]);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  glEnable(GL_TEXTURE_2D);
}


/******************************************************************************************/
/*									TEXTURA HOJAS										  */
/******************************************************************************************/
void initTexturaHojas() {
  leerTextura("./resources/hojas.tga", 8);
}
void texturaHojas(void)
{
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexImage2D(GL_TEXTURE_2D, 0, 3, anchoTextura, altoTextura, 0, GL_RGB, GL_UNSIGNED_BYTE, textura[8]);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  glEnable(GL_TEXTURE_2D);
}


/******************************************************************************************/
/*									TEXTURA COLUMNA										  */
/******************************************************************************************/
void initTexturaColumna() {
  leerTextura("./resources/piedrecillas.tga", 9);
}
void texturaColumna(void)
{
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexImage2D(GL_TEXTURE_2D, 0, 3, anchoTextura, altoTextura, 0, GL_RGB, GL_UNSIGNED_BYTE, textura[9]);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  glEnable(GL_TEXTURE_2D);
}

/******************************************************************************************/
/*									TEXTURA MADERA										  */
/******************************************************************************************/
void initTexturaMadera(void) {
  leerTextura("./resources/madera.tga", 10);
}
void texturaMadera(void) {
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexImage2D(GL_TEXTURE_2D, 0, 3, anchoTextura, altoTextura, 0, GL_RGB, GL_UNSIGNED_BYTE, textura[10]);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  glEnable(GL_TEXTURE_2D);
}

/******************************************************************************************/
/*									TEXTURA BALDOSA FRONTAL						          */
/******************************************************************************************/
void initTexturaBaldosaF(void) {
  leerTextura("./resources/baldosa_frontal.tga", 11);
}
void texturaBaldosaF(void) {
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexImage2D(GL_TEXTURE_2D, 0, 3, anchoTextura, altoTextura, 0, GL_RGB, GL_UNSIGNED_BYTE, textura[11]);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  glEnable(GL_TEXTURE_2D);
}

/******************************************************************************************/
/*									TEXTURA TEJADO        						          */
/******************************************************************************************/
void initTexturaTejado(void) {
  leerTextura("./resources/tejado.tga", 12);
}
void texturaTejado(void) {
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexImage2D(GL_TEXTURE_2D, 0, 3, anchoTextura, altoTextura, 0, GL_RGB, GL_UNSIGNED_BYTE, textura[12]);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  glEnable(GL_TEXTURE_2D);
}

/******************************************************************************************/
/*									TEXTURA MORTERO        						          */
/******************************************************************************************/
void initTexturaMortero(void) {
  leerTextura("./resources/mortero.tga", 13);
}
void texturaMortero(void) {
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexImage2D(GL_TEXTURE_2D, 0, 3, anchoTextura, altoTextura, 0, GL_RGB, GL_UNSIGNED_BYTE, textura[13]);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  glEnable(GL_TEXTURE_2D);
}

/******************************************************************************************/
/*									TEXTURA CEMENTO        						          */
/******************************************************************************************/
void initTexturaCemento(void) {
  leerTextura("./resources/cemento.tga", 14);
}
void texturaCemento(void) {
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexImage2D(GL_TEXTURE_2D, 0, 3, anchoTextura, altoTextura, 0, GL_RGB, GL_UNSIGNED_BYTE, textura[14]);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  glEnable(GL_TEXTURE_2D);
}

/******************************************************************************************/
/*									TEXTURA ACERO          						          */
/******************************************************************************************/
void initTexturaAcero(void){
  leerTextura("./resources/acero.tga", 15);
}
void texturaAcero(void) {
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexImage2D(GL_TEXTURE_2D, 0, 3, anchoTextura, altoTextura, 0, GL_RGB, GL_UNSIGNED_BYTE, textura[15]);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  glEnable(GL_TEXTURE_2D);
}