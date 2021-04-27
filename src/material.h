/*************************************************************************/
/*                                                                       */
/*   material.h												                                   */
/*   Rev. 2.0  01/01/2002   AUTORES: O. Belmonte, M. Chover, J. Ribelles */
/*                                                                       */
/*************************************************************************/


#ifndef MATERIAL_H
#define MATERIAL_H


/*********************** DECLARACION DE CONSTANTES ***********************/

#define anchoTextura 256
#define altoTextura  256
#define numTextura	 16

/***************** DECLARACION DE LA VARIABLES GLOBALES  *****************/


GLubyte textura[numTextura][anchoTextura][altoTextura][3];

/* Inicia OpenGL para poder definir las propiedades de los materiales */
void IniciaMaterial(void);

/* Define las propiedades del material cobre */
void Cobre(void);

/* Lee una imagen de textura en formato tga */
void leerTextura(char* fichero, int num);

/* Textura de cielo */
void initTexturaCielo(void);
void texturaCielo(void);

/* Textura de bosque */
void initTexturaBosque(void);
void texturaBosque(void);

/* Textura de hierba */
void initTexturaHierba(void);
void texturaHierba(void);

/* Textura de 
*/
void initTexturaAgua(void);
void texturaAgua(void);

/* Textura de camino */
void initTexturaCamino(void);
void texturaCamino(void);

/* Textura de cesped */
void initTexturaCesped(void);
void texturaCesped(void);

/* Textura de baldosa */
void initTexturaBaldosa(void);
void texturaBaldosa(void);

/* Textura de tronco */
void initTexturaTronco(void);
void texturaTronco(void);

/* Textura de hojas */
void initTexturaHojas(void);
void texturaHojas(void);

/* Textura de columna */
void initTexturaColumna(void);
void texturaColumna(void);

/* Textura de madera */
void initTexturaMadera(void);
void texturaMadera(void);

/* Textura de baldosa invertida */
void initTexturaBaldosaF(void);
void texturaBaldosaF(void);

/* Textura de tejado */
void initTexturaTejado(void);
void texturaTejado(void);

/* Textura de mortero */
void initTexturaMortero(void);
void texturaMortero(void);

/* Textura de cemento */
void initTexturaCemento(void);
void texturaCemento(void);

/* Textura de acero */
void initTexturaAcero(void);
void texturaAcero(void);
#endif