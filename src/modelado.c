/*************************************************************************/
/*                                                                       */
/*   modelado.c                                                          */
/*   Rev. 3.0  01/09/2012   Universidad Jaume I de Castell�n             */
/*                                                                       */
/*************************************************************************/
#include "modelado.h"
#include <stdio.h>
#include "glig.h"
#include "material.h"
#include <limits.h>
#include <math.h>

struct Region regiones[numRegiones];

/******************************************************************************************/
/* Define las regiones del proyecto                                                       */
/* Parametros: Ninguno                                                                    */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void DefineRegiones(void) {
  int a, inicioReg_i, inicioReg_j, finRegAnt_i, finRegAnt_j;
  //array que define el porcentaje {i,j} de las regiones
  float porcentReg[numRegiones][2] = {
    {0.3,0.3},
    {0.1,0.3},
    {0.2,0.3},
    {0.4,0.3},
    {1,0.2},
    {0.4,0.2},
    {0.2,0.2},
    {0.4,0.2},
    {1,0.3}
  };

  // Inicializa los valores de las regiones
  for (a = 0; a < numRegiones; a++)
  {
    switch (a) {
    case 0:
      inicioReg_i = inicioReg_j = 0;
      break;
    case 1:
      inicioReg_i = regiones[0].fin_i;
      inicioReg_j = 0;
      break;
    case 2:
      inicioReg_i = regiones[1].fin_i;
      inicioReg_j = 0;
      break;
    case 3:
      inicioReg_i = regiones[2].fin_i;
      inicioReg_j = 0;
      break;
    case 4:
      inicioReg_i = 0;
      inicioReg_j = regiones[0].fin_j;
      break;
    case 5:
      inicioReg_i = 0;
      inicioReg_j = regiones[4].fin_j;
      break;
    case 6:
      inicioReg_i = regiones[5].fin_i;
      inicioReg_j = regiones[4].fin_j;
      break;
    case 7:
      inicioReg_i = regiones[6].fin_i;
      inicioReg_j = regiones[4].fin_j;
      break;
    case 8:
      inicioReg_i = 0;
      inicioReg_j = regiones[5].fin_j;
      break;
    }
    // Actualiza el array de regiones
    regiones[a].id = a;
    regiones[a].inicio_i = inicioReg_i;
    regiones[a].inicio_j = inicioReg_j;
    regiones[a].porcent_i = porcentReg[a][0];
    regiones[a].porcent_j = porcentReg[a][1];

    finRegAnt_i = SizeX * porcentReg[a][0] + inicioReg_i;
    finRegAnt_j = SizeZ * porcentReg[a][1] + inicioReg_j;

    regiones[a].fin_i = finRegAnt_i;
    regiones[a].fin_j = finRegAnt_j;

    //Visualizacion de la informacion de cada region
    //printf("\nregion %d, \n\tinicio i= %d, \n\tini j = %d, \n\tporcent i = %f, \n\tporcent j= %f,\n\tfin i= %d, \n\tfin j= %d \n", a, inicioReg_i, inicioReg_j, porcentReg[a][0], porcentReg[a][1], finRegAnt_i, finRegAnt_j);
  }
}

/******************************************************************************************/
/* Crea las distintas display lists                                                       */
/* Parametros: Ninguno                                                                    */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void IniciaDisplayLists(void) {
  CreaCielo();
  CreaColumna();
  CreaBanco();
  CreaValla();
  CreaArco();
  CreaAbeto();
  CreaArbol();
  CreaCupula();
  CreaFuente();
  CreaFuente2();
  CreaPuente();
  CreaAbeto();
  CreaArbusto();
  CreaTerreno();
  CreaEscena();
}

/******************************************************************************************/
/* Dibuja la escena                                                                       */
/* Parametros: Ninguno                                                                    */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void DibujaEscena(void) {
  glCallList(escena);
}

/******************************************************************************************/
/* Crea una display list para la fuente                                                   */
/* Parametros: Ninguno                                                                    */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void CreaFuente() {
  fuente = glGenLists(1);
  if (fuente != 0) {
    glNewList(fuente, GL_COMPILE);
    float posx = 0.855 * SizeX;
    float posz = 0.8 * SizeX;
    float posy = 0.015 * SizeX;
    float size1 = 0.08 * SizeX;
    float size2 = size1 / 6;
    float altura = 0.02 * SizeX;
    float altura2 = altura * 3;
    /* Cilindro exterior-exterior */
    glPushMatrix(); {
      glColor3f(0.75, 0.75, 0.75);
      texturaMortero();
      CreaCilindroExterior(posx, posy, posz, size1, altura);
      glColor3f(1, 1, 1);
    }glPopMatrix();
    /* Agua inferior */
    glPushMatrix(); {
      texturaAgua();
      CreaCilindroInterior(posx, posy, posz, size1 - 0.05, altura);
    }glPopMatrix();
    /* Pilar grueso */
    glPushMatrix(); {
      texturaAcero();
      CreaCilindroInterior(posx, posy, posz, size2, altura2);
    }glPopMatrix();

    posy = 0.04 * SizeX + altura;
    size1 = size1 / 2;
    size2 = size2 / 3;
    altura2 = altura2 / 2;
    float alturaSup = altura * 0.7;
    /* Cilindro exterior-superior */
    glPushMatrix(); {
      glColor3f(0.75, 0.75, 0.75);
      texturaMortero();
      CreaCilindroExterior(posx, posy, posz, size1, alturaSup);
      glColor3f(1, 1, 1);
    }glPopMatrix();
    /* Agua superior */
    glPushMatrix(); {
      texturaAgua();
      CreaCilindroInterior(posx, posy + 0.25, posz, size1 - 0.05, alturaSup);
    }glPopMatrix();
    /* Pilar superior delgado */
    glPushMatrix(); {
      texturaAcero();
      CreaCilindroInterior(posx, posy, posz, size2, altura2);
    }glPopMatrix();
    glEndList();
  }
  else puts("Se ha producido un error creando la display list para la fuente.");
}

/******************************************************************************************/
/* Crea una display list para la fuente 2                                                 */
/* Parametros: Ninguno                                                                    */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void CreaFuente2() {
  fuente2 = glGenLists(1);
  if (fuente2 != 0) {
    glNewList(fuente2, GL_COMPILE);
    float posx = 0.255 * SizeX;
    float posz = 0.6 * SizeX;
    float posy = 0;
    float size1 = 0.04 * SizeX;
    float size2 = size1 / 3;
    float altura = 0.01 * SizeX;
    glPushMatrix(); {
      texturaMortero();
      CreaCilindroExterior2(posx, posy, posz, size1 / 2, size2, altura);
      CreaCilindroExterior2(posx, posy + altura, posz, size2, size2, altura);
      CreaCilindroExterior2(posx, posy + altura * 2, posz, size2, size1, altura);
      texturaAgua();
      CreaCilindroInterior2(posx, posy + altura * 2, posz, size2 - 1, size1 - 1, altura);
    }glPopMatrix();
  }
  else puts("Se ha producido un error creando la display list para la fuente2.");
}

/******************************************************************************************/
/* Crea una display list para el abeto                                                    */
/* Parametros: Ninguno                                                                    */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void CreaAbeto(void) {
  abeto = glGenLists(1);
  if (abeto != 0) {
    glNewList(abeto, GL_COMPILE);
    glPushMatrix(); {
      glTranslatef(0.0, 0.06 * SizeZ, 0.0);
      glScalef(7, 8, 7);

      glPushMatrix(); {
        texturaHojas();
        glScalef(0.75, 1.0, 0.75);
        igSolidSphere(10, 10);	
        glScalef(0.75, 1.0, 0.75);
        glTranslatef(0.0, 0.9, 0.0);
        igSolidSphere(10, 10);	
        glScalef(0.75, 1.0, 0.75);
        glTranslatef(0.0, 0.8, 0.0);
        igSolidSphere(10, 10);	
      }glPopMatrix();

      //Tronco
      glPushMatrix(); {
        texturaMadera();
        glScalef(0.1, 2.0, 0.1);
        igSolidRulo(10, 10);	
      }glPopMatrix();
    }glPopMatrix();
    glEndList();
  }
  else puts("Se ha producido un error creando la display list para el abeto.");
}

/******************************************************************************************/
/* Crea una display list para el arbusto                                                  */
/* Parametros: Ninguno                                                                    */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void CreaArbusto(void) {
  arbusto = glGenLists(1);
  if (arbusto != 0) {
    glNewList(arbusto, GL_COMPILE);


    float posx = 0.76 * SizeX;
    float posy = 0.01 * SizeX;
    float posz = 0.67 * SizeZ;

    glPushMatrix(); {
      glTranslatef(posx, posy, posz);
      glScalef(7, 6, 7);

      glPushMatrix(); {
        texturaBosque();

        glPushMatrix(); {
          glScalef(0.5, 0.8, 0.5);
          igSolidSphere(10, 10);
        }glPopMatrix();

        glPushMatrix(); {
          glScalef(0.4, 0.8, 0.4);
          glTranslatef(0.0, 0.25, 0.0);
          igSolidSphere(10, 10);
        }glPopMatrix();

        glPushMatrix(); {
          glScalef(0.6, 0.8, 0.6);
          glTranslatef(0.0, 0.25, 0.0);
          igSolidSphere(10, 10);
        }glPopMatrix();

      }glPopMatrix();
    
    }glPopMatrix();
    glEndList();
  }
  else puts("Se ha producido un error creando la display list para el arbusto.");
}

/******************************************************************************************/
/* Crea una display list para el arbol                                                    */
/* Parametros: Ninguno                                                                    */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void CreaArbol(void) {
  arbol = glGenLists(1);
  if (arbol != 0) {
    glNewList(arbol, GL_COMPILE);

    glTranslatef(0.0, 0.06 * SizeZ, 0.0);
    glScalef(7, 8, 7);

    //Hojas
    glPushMatrix(); {
      texturaHojas();
      glScalef(0.75, 1.7, 0.75);
      glTranslatef(0.0, 0.7, 0.0);
      igSolidSphere(10, 10);	
    }glPopMatrix();

    //Tronco
    glPushMatrix(); {
      texturaMadera();
      glScalef(0.1, 2.0, 0.1);
      igSolidRulo(10, 10);	
    }glPopMatrix();
    glEndList();
  }
  else puts("Se ha producido un error creando la display list para el arbol.");
}

/******************************************************************************************/
/* Crea una display list para el arco                                                    */
/* Parametros: Ninguno                                                                    */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void CreaArco(void) {
  arco = glGenLists(1);
  if (arco != 0) {
    glNewList(arco, GL_COMPILE);
    glPushMatrix(); {
      glTranslatef(regiones[8].inicio_i + 0.15 * SizeX, 0, regiones[8].inicio_j + 0.05 * SizeX);
      glPushMatrix(); {
        glScalef(SizeX * 0.05, 1, SizeZ * 0.05);
        glPushMatrix(); {
          glColor3f(0.75, 0.75, 0.75);
          texturaMortero();
          for (int i = 0; i < 6; i++) {
            /* Columnas */
            glPushMatrix(); {
              glRotatef(i * 360 / 6, 0.0, 1.0, 0.0);
              glTranslatef(0.0, 0.0, -2.0);
              glScalef(0.5, 0.6, 0.5);
              glCallList(columna);
            }glPopMatrix();
          }
        }glPopMatrix();

        glColor3f(0.45, 0.45, 0.45); {
          /* Suelo */
          glPushMatrix(); {
            texturaMortero();
            glTranslatef(0, -3, 0);
            CreaCilindroInterior(0.0, 0.03 * SizeZ, 0.0, 2.5, 3);
          }glPopMatrix();

          glTranslatef(0.0, 4, 0.0);
          /* Techo */
          glPushMatrix(); {
            texturaMortero();
            CreaCilindroInterior(0.0, 20, 0.0, 2.5, 2);
          }glPopMatrix();
        }glPopMatrix();
      }glColor3f(1, 1, 1);

      glPushMatrix(); {

        glTranslatef(0.0, 4, 0.0);
        /* Cupula */
        glPushMatrix(); {
          texturaTejado();
          glTranslatef(0.0, 0.1 * SizeZ, 0.0);
          glScalef(SizeX * 0.115, 20, SizeZ * 0.115);
          igSolidSemiSphere(60, 60);
        }glPopMatrix();

        /* Mastil */
        glPushMatrix(); {
          texturaBaldosa();
          glTranslatef(0, 0.2 * SizeZ, 0);
          glScalef(0.35, 0.03 * SizeZ, 0.35);
          igSolidRulo(20, 20);	// Rulo
        }glPopMatrix();
      }glPopMatrix();
    }glPopMatrix();
    glEndList();
  }
  else puts("Se ha producido un error creando la display list para el arco.");
}

/******************************************************************************************/
/* Crea las columnas                                                                      */
/* Parametros: Ninguno                                                                    */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void CreaColumna(void) {
  columna = glGenLists(1);
  if (columna != 0) {
    glNewList(columna, GL_COMPILE);
    glPushMatrix(); {
      glTranslatef(0, 0, 0);
      igSolidCuboParedes(0.5, 40, 0.5);
    }glPopMatrix();
    glEndList();
  }
  else puts("Se ha producido un error creando la display list para el cielo.");
}

/******************************************************************************************/
/*  Crea una display list para el cielo		                                              */
/* Parametros: Ninguno                                                                    */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void CreaCielo() {
  cielo = glGenLists(1);
  if (cielo != 0) {
    glNewList(cielo, GL_COMPILE);
    glPushMatrix();
    texturaCielo();
    glColor3f(0.7f, 0.75f, 1.0f);
    glTranslatef(MiddleX, -2.25, MiddleZ);
    igSolidDadoRadio(10, 10, MiddleX + 1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glEndList();
  }
  else puts("Se ha producido un error creando la display list para el cielo.");
}

/******************************************************************************************/
/*  Crea una display list para toda la escena                                             */
/* Parametros: Ninguno                                                                    */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void CreaEscena(void) {
  escena = glGenLists(1);
  if (escena != 0) {
    glNewList(escena, GL_COMPILE);
    printf("Creando la escena... \n");
    glPushMatrix(); {
      glCallList(cielo);	//Crea cielo
      glCallList(terreno);	//Crea terreno
    }glPopMatrix();
    printf("La escena fue creada completamente\n\n");
    glEndList();
  }
  else puts("Se ha producido un error creando la display list de la escena.");
}

/******************************************************************************************/
/*  Crea una display list para el banco                                                   */
/* Parametros: Ninguno                                                                    */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void CreaBanco(void) {
  banco = glGenLists(1);
  if (banco != 0) {
    glNewList(banco, GL_COMPILE);

    float sizex = 0.015 * SizeX;
    float sizey = 0.075 * SizeZ;
    float sizez = 0.0025 * SizeX;
    float posx = 0.7 * SizeX;
    float posy = 0.01 * SizeX;
    float posz = 0.68 * SizeZ;
    glPushMatrix(); {
      glTranslatef(posx, posy, posz);
      texturaMadera();
      /* Respaldo */
      glPushMatrix(); {
        glTranslatef(0, sizez, 0);
        glRotatef(90, 1, 0, 0);
        glRotatef(90, 0, 0, 1);
        glRotatef(90, 0, 1, 0);
        igSolidCuboParedes(sizex - sizez, sizey, sizez);
      }glPopMatrix();

      /* Asiento */
      glPushMatrix(); {
        glTranslatef(0, sizez, 0);
        glRotatef(90, 1, 0, 0);
        glRotatef(90, 0, 0, 1);
        glTranslatef(-sizez * 5, 0, 0);
        igSolidCuboParedes(sizex, sizey, sizez);
      }glPopMatrix();

      /* Patas */
      glPushMatrix(); {
        glColor3f(0.65, 0.65, 0.65);
        texturaAcero();
        float sizexp = 0.003 * SizeX;
        float sizeyp = posy;
        float sizezp = 0.003 * SizeZ;
        glTranslatef(-sizexp, -sizeyp, -0.1);
        igSolidCuboParedes(sizexp, sizeyp, sizezp);
        glTranslatef(0, 0, -sizex + sizexp);
        igSolidCuboParedes(sizexp, sizeyp, sizezp);
        glTranslatef(-sizey + sizexp, 0, 0);
        igSolidCuboParedes(sizexp, sizeyp, sizezp);
        glTranslatef(0, 0, sizex - sizezp);
        igSolidCuboParedes(sizexp, sizeyp, sizezp);
        glColor3f(1, 1, 1);
      }glPopMatrix();
    }glPopMatrix();
    glEndList();
  }
  else puts("Se ha producido un error creando la display list del banco.");
}

/******************************************************************************************/
/* Crea el terreno con montañas                                                           */
/* Parametros: Ninguno                                                                    */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void CreaTerreno() {
  terreno = glGenLists(1);
  if (terreno != 0) {
    glNewList(terreno, GL_COMPILE);
    int i, j; //coordenadas
    int numRegion = 0; // Identificador de la region
    glPushMatrix(); {
      DefineRegiones();
      while (numRegion < numRegiones) {
        glPushMatrix(); {
          Region region = regiones[numRegion];
          TexturaPorRegion(numRegion); //Carga la textura correspondiene a la region
          if (numRegion != 4) {
            /* Bucles para pintar las celdas */
            for (i = 0; i < SizeX; i++) {
              for (j = 0; j < SizeZ; j++) {
                PintaRegion(i, j, region);
              }
            }
            glDisable(GL_TEXTURE_2D);
          }
          else CreaRegion(region); //pinta la region de agua con un solo rectangulo
          numRegion++; // Incrementa la region a pintar
        }glPopMatrix();
      }

      /* Completa la region de la baldosa para elevarla */
      glPushMatrix(); {
        int reg = 8; //Balosa
        TexturaPorRegion(reg); //Carga la textura correspondiene a la region
        CreaRegion(regiones[reg]);
        ColocaJardineras(regiones[reg]);
      }glPopMatrix();

      /* Inserta elementos en el terreno */
      {
        ColocaArboles(regiones[0]);
        glCallList(cupula);
        glCallList(puente);
        glCallList(fuente);
        glCallList(fuente2);

        /* bancos */
        glPushMatrix(); {
          glCallList(banco);
          glTranslatef(-0.33 * SizeX, 0, 0);
          glCallList(banco);
          glTranslatef(-0.20 * SizeX, 0, 0);
          glCallList(banco);
          glTranslatef(0.72 * SizeX, 0, 0);
          glCallList(banco);
        }glPopMatrix();

        /* arbustos */
        glPushMatrix(); {
          glCallList(arbusto);
          glTranslatef(0.175 * SizeX, 0, 0);
          glCallList(arbusto);
        }glPopMatrix();

        /* vallas */
        ColocaVallas();
      }
    }glPopMatrix();

    glEndList();
  }
  else puts("Se ha producido un error creando la display list del terreno.");
}

/******************************************************************************************/
/* Coloca los abetos en la region enviada                                                 */
/* Parametros: region = region de enviada                                                 */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void ColocaAbetos(Region region) {
  int i, j;
  int decr = 9; //Decremento de los bucles
  int init = 1;
  float x, z;
  glPushMatrix(); {
    for (i = region.fin_i - init; i > region.inicio_i; i -= decr) {
      x = i - 0.75;
      for (j = region.fin_j - init; j > region.inicio_j; j -= decr) {
        z = j - 0.75;
        glPushMatrix(); {
          glTranslatef(x, 0, z);
          glCallList(abeto); //Coloca abeto
        }glPopMatrix();
      }
    }
  }glPopMatrix();
}

/******************************************************************************************/
/* Coloca los arboles en la region enviada                                                */
/* Parametros: region = region de enviada                                                 */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void ColocaArboles(Region region) {
  int i, j;
  int decr = 16; //Decremento de los bucles
  int init = 2;
  float x, z;
  glPushMatrix(); {
    for (i = region.fin_i - init; i > region.inicio_i; i -= decr) {
      x = i - 0.5;
      for (j = region.fin_j - init; j > region.inicio_j; j -= decr) {
        z = j - 0.5;
            glPushMatrix(); {
            glTranslatef(x, 0, z);
            if (!(i == 10 && j == 10 || i == 10 && j == 26 || i == 26 && j == 10)) {
                glCallList(arbol); //Coloca arbol
            }
        }glPopMatrix();
      }
    }
  }glPopMatrix();
}

/******************************************************************************************/
/* Coloca la cupula con arco y columnas                                                   */
/* Parametros: Ninguno                                                                    */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void CreaCupula() {
  cupula = glGenLists(1);
  if (cupula != 0) {
    glNewList(cupula, GL_COMPILE);
    glPushMatrix(); {
      glTranslatef(SizeX * 0.35, 0, SizeZ * 0.8); //se coloca en el 30% de la posicion total de i y el 70% de la posicion total de j
      glCallList(arco);
    }glPopMatrix();
    glEndList();
  }
  else puts("Se ha producido un error creando la display list del cupula.");

}

/******************************************************************************************/
/* Establece la textura para una region												      */
/*			                                                                              */
/* Parametros: numRegion = Numero de region                                               */
/* Salida: Ninguna		                                                                  */
/******************************************************************************************/
void TexturaPorRegion(int numRegion) {

  if (numRegion == 0)	texturaBosque();
  else if (numRegion == 1) 	texturaHierba();
  else if (numRegion == 3 || numRegion == 5 || numRegion == 7) texturaCesped();
  else if (numRegion == 4)	texturaAgua();
  else if (numRegion == 2 || numRegion == 6) texturaCamino();
  else if (numRegion == 8) 	texturaBaldosa();
  else - 1;//glColor3f(0.0f, 1.0f, 1.0f);
}

/******************************************************************************************/
/* Crea el suelo por region                                                               */
/*			                                                                              */
/* Parametros: i = coordenada X, j  =  coordenada Z, region = Region actual               */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void PintaRegion(int i, int j, Region region) {
  if (i >= region.inicio_i && i <= region.fin_i
    && j >= region.inicio_j && j <= region.fin_j) {
    CreaCelda(i, j, region);
  }
}

/******************************************************************************************/
/* Crea un cuadrado mediante GL_QUADS												       */
/* Parametros: i = posicion en X, j = posicion en Z										  */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void CreaCelda(int i, int j, Region region) {
  float altura = region.id == 8 ? 0.015 * SizeX : 0;
  glBegin(GL_QUADS); {
    glTexCoord2f(0, 0);
    glVertex3f(i, altura, j);
    glTexCoord2f(0, 1);
    glVertex3f(i, altura, j + 1);
    glTexCoord2f(1, 1);
    glVertex3f(i + 1, altura, j + 1);
    glTexCoord2f(1, 0);
    glVertex3f(i + 1, altura, j);
  }glEnd();
}

/******************************************************************************************/
/* Crea la region con un solo rectuangulo                                                 */
/*			                                                                              */
/* Parametros: region = Region actual                                                     */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void CreaRegion(Region region) {
  if (region.id == 4) CreaRegionAgua(region);
  else if (region.id == 8) CreaRegionBaldosa(region);
  else CreaRegionGenerica(region);
}

/******************************************************************************************/
/* Crea la region con un solo rectuangulo                                                 */
/*			                                                                              */
/* Parametros: region = Region actual                                                     */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void CreaRegionGenerica(Region region) {
  int inicio_x = region.inicio_i;
  int inicio_z = region.inicio_j;
  int fin_x = region.fin_i;
  int fin_z = region.fin_j;

  glBegin(GL_QUADS); {
    glTexCoord2f(0, 0);
    glVertex3f(inicio_x, 0.0f, inicio_z);

    glTexCoord2f(0, region.porcent_j);
    glVertex3f(inicio_x, 0.0f, fin_z);

    glTexCoord2f(region.porcent_i, region.porcent_j);
    glVertex3f(fin_x, 0.0f, fin_z);

    glTexCoord2f(region.porcent_i, 0);
    glVertex3f(fin_x, 0.0f, inicio_z);
  }glEnd();
}

/******************************************************************************************/
/* Crea la region de agua con un solo rectangulo                                          */
/*			                                                                              */
/* Parametros: region = Region actual                                                     */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void CreaRegionAgua(Region region) {
  int inicio_x = region.inicio_i;
  int inicio_z = region.inicio_j + 1; // Empieza en la siguiente posicion para evitar solapamientos
  int fin_x = region.fin_i;
  int fin_z = region.fin_j;

  float mov_z = 0.015 * SizeZ;
  float mov_x = 0.05 * SizeX;
  float altura = -0.01 * SizeZ;

  /* Arena */
  glPushMatrix(); {

    texturaCamino();
    glBegin(GL_QUADS); {
      glTexCoord2f(0, 0);
      glVertex3f(inicio_x, 0.0f, inicio_z);
      glTexCoord2f(0, 0.15);
      glVertex3f(inicio_x, altura, inicio_z + mov_z);
      glTexCoord2f(1, 0.15);
      glVertex3f(inicio_x + mov_x, altura, inicio_z + mov_z);
      glTexCoord2f(1, 0);
      glVertex3f(inicio_x + mov_x, 0.0f, inicio_z);
    }glEnd();

    glBegin(GL_QUADS); {
      glTexCoord2f(0, 0);
      glVertex3f(inicio_x + mov_x, 0.0f, inicio_z);
      glTexCoord2f(0, 0.15);
      glVertex3f(inicio_x + mov_x, altura, inicio_z + mov_z);
      glTexCoord2f(1, 0.15);
      glVertex3f(fin_x, altura, inicio_z + mov_z);
      glTexCoord2f(1, 0);
      glVertex3f(fin_x, 0.0f, inicio_z);
    }glEnd();

    glBegin(GL_QUADS); {
      glTexCoord2f(0, 0);
      glVertex3f(inicio_x, altura, fin_z - mov_z);
      glTexCoord2f(0, 0.15);
      glVertex3f(inicio_x, 0.0f, fin_z);
      glTexCoord2f(1, 0.15);
      glVertex3f(inicio_x + mov_x, 0.0f, fin_z);
      glTexCoord2f(1, 0);
      glVertex3f(inicio_x + mov_x, altura, fin_z - mov_z);
    }glEnd();

    glBegin(GL_QUADS); {
      glTexCoord2f(0, 0);
      glVertex3f(inicio_x + mov_x, altura, fin_z - mov_z);
      glTexCoord2f(0, 0.15);
      glVertex3f(inicio_x + mov_x, 0.0f, fin_z);
      glTexCoord2f(1, 0.15);
      glVertex3f(fin_x, 0.0f, fin_z);
      glTexCoord2f(1, 0);
      glVertex3f(fin_x, altura, fin_z - mov_z);
    }glEnd();

  }glPopMatrix();

  /* Agua */
  inicio_z = inicio_z + mov_z;
  fin_z = fin_z - mov_z;
  glPushMatrix(); {
    texturaAgua();
    glBegin(GL_QUADS); {
      glTexCoord2f(0, 0);
      glVertex3f(inicio_x, altura, inicio_z);

      glTexCoord2f(0, region.porcent_j);
      glVertex3f(inicio_x, altura, fin_z);

      glTexCoord2f(region.porcent_i, region.porcent_j);
      glVertex3f(fin_x, altura, fin_z);

      glTexCoord2f(region.porcent_i, 0);
      glVertex3f(fin_x, altura, inicio_z);
    }glEnd();
  }glPopMatrix();

}

/******************************************************************************************/
/* Crea las escaleras y la parte frontal de la region baldosa                             */
/*			                                                                              */
/* Parametros: region = Region actual                                                     */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void CreaRegionBaldosa(Region region) {
  float inicio_x = region.inicio_i;
  float inicio_z = region.inicio_j;
  float fin_x = region.fin_i;
  float fin_z = region.fin_j;
  float altura = 0.015 * SizeZ;
  int i;

  // Frontal
  glBegin(GL_QUADS); {
    for (i = inicio_x; i < fin_x; i++) {
      glTexCoord2f(0, 0);
      glVertex3f(i, 0, inicio_z);
      glTexCoord2f(0, 1);
      glVertex3f(i, altura, inicio_z);
      glTexCoord2f(1, 1);
      glVertex3f(i + 1, altura, inicio_z);
      glTexCoord2f(1, 0);
      glVertex3f(i + 1, 0, inicio_z);
    }
  }glEnd();

  //Escaleras
  inicio_x = 0.45 * SizeX;
  fin_x = 0.55 * SizeX;
  inicio_z = 0.65 * SizeZ;
  fin_z = 0.7 * SizeZ;
  glPushMatrix(); {
    texturaBaldosa(); //Textura
    glTranslatef(inicio_x, altura, fin_z - altura);
    glRotatef(90, 0, 0, -1);
    igSolidCuboParedes(altura, fin_x - inicio_x, altura);
  }glPopMatrix();
  glPushMatrix(); {
    texturaBaldosa(); //Textura
    glTranslatef(inicio_x, altura / 2, fin_z - altura * 2);
    glRotatef(90, 0, 0, -1);
    igSolidCuboParedes(altura / 2, fin_x - inicio_x, altura);
  }glPopMatrix();

  //Rampa
  //glBegin(GL_QUADS); {
  //  glTexCoord2f(0, 0);
  //  glVertex3f(inicio_x, 0, inicio_z);
  //  glTexCoord2f(0, 0.25);
  //  glVertex3f(inicio_x, altura, fin_z);
  //  glTexCoord2f(1, 0.25);
  //  glVertex3f(fin_x, altura, fin_z);
  //  glTexCoord2f(1, 0);
  //  glVertex3f(fin_x, 0, inicio_z);
  //}glEnd();
}

/******************************************************************************************/
/* Crea el puente                                                                         */
/*			                                                                              */
/* Parametros: region = Region actual                                                     */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void CreaPuente() {
  int altura = 0.02 * SizeZ;
  float vertices[8][3] = {
    { 0.4 * SizeX,0,0.25 * SizeZ},
    { 0.4 * SizeX,altura,0.3 * SizeZ},
    { 0.4 * SizeX,altura,0.5 * SizeZ},
    { 0.4 * SizeX,0,0.55 * SizeZ},

    { 0.6 * SizeX,0,0.55 * SizeZ},
    { 0.6 * SizeX,altura,0.5 * SizeZ},
    { 0.6 * SizeX,altura,0.3 * SizeZ},
    { 0.6 * SizeX,0,0.25 * SizeZ}
  };

  puente = glGenLists(1);
  if (puente != 0) {
    glNewList(puente, GL_COMPILE);
    glPushMatrix(); {
      texturaMadera(); // textura
      glBegin(GL_QUADS); {
        glTexCoord2f(0, 0);
        glVertex3fv(vertices[0]);
        glTexCoord2f(0, 0.25);
        glVertex3fv(vertices[1]);
        glTexCoord2f(1, 0.25);
        glVertex3fv(vertices[6]);
        glTexCoord2f(1, 0);
        glVertex3fv(vertices[7]);
      }glEnd();

      glBegin(GL_QUADS); {
        glTexCoord2f(0, 0.25);
        glVertex3fv(vertices[1]);
        glTexCoord2f(0, 0.75);
        glVertex3fv(vertices[2]);
        glTexCoord2f(1, 0.75);
        glVertex3fv(vertices[5]);
        glTexCoord2f(1, 0.25);
        glVertex3fv(vertices[6]);
      }glEnd();

      glBegin(GL_QUADS); {
        glTexCoord2f(0, 0.75);
        glVertex3fv(vertices[2]);
        glTexCoord2f(0, 1);
        glVertex3fv(vertices[3]);
        glTexCoord2f(1, 1);
        glVertex3fv(vertices[4]);
        glTexCoord2f(1, 0.75);
        glVertex3fv(vertices[5]);
      }glEnd();
    }glPopMatrix();


    float positions[10][3] = {
    { vertices[0][0], vertices[0][1], vertices[0][2]},
    { vertices[1][0], vertices[1][1], vertices[1][2]},
    { vertices[0][0], vertices[1][1], 0.4 * SizeZ},
    { vertices[2][0], vertices[2][1], vertices[2][2]},
    { vertices[3][0], vertices[3][1], vertices[3][2] - 0.005 * SizeZ},

    { vertices[4][0] - 0.005 * SizeX, vertices[4][1], vertices[4][2] - 0.005 * SizeZ},
    { vertices[5][0] - 0.005 * SizeX, vertices[5][1], vertices[5][2] },
    { vertices[4][0] - 0.005 * SizeX, vertices[5][1], 0.4 * SizeZ},
    { vertices[6][0] - 0.005 * SizeX, vertices[6][1], vertices[6][2]},
    { vertices[7][0] - 0.005 * SizeX, vertices[7][1], vertices[7][2]}
    };

    int i;
    float sizex, sizey, sizez, middle, angle, sizey2, posx, posy, posz;

    /* Coloca columnas verticales en el puente */
    glPushMatrix(); {
      for (i = 0; i < 10; i++) {
        sizex = 0.005 * SizeX;
        sizey = 0.04 * SizeZ;
        sizez = 0.005 * SizeZ;
        glPushMatrix(); {
          posx = positions[i][0];
          posy = positions[i][1];
          posz = positions[i][2];
          if (posy > 0) {
            sizey += posy;
            posy = 0;
          }
          if (i == 2 || i == 7) { //columnas del medio del puente
            sizey += 0.01 * SizeZ;
            posy -= 0.01 * SizeZ;
          }
          glTranslatef(posx, posy, posz);
          igSolidCuboParedes(sizex, sizey, sizez);
        }glPopMatrix();
      }
    }glPopMatrix();

    /* Coloca columnas horizontales en el puente */
    glPushMatrix(); {
      middle = 0.02 * SizeZ;
      sizex = 0.005 * SizeX;
      sizey = 0.04 * SizeZ;
      sizez = 0.005 * SizeZ;
      angle;

      /* Lado 1 */
      for (i = 0; i < 4; i++) {
        sizey2 = (positions[i + 1][2] - positions[i][2]) + 0.005 * SizeZ;
        posx = positions[i][0];
        posy = positions[i][1] + sizey;
        posz = positions[i][2];

        glPushMatrix(); {
          if (i == 0) angle = 24;
          else if (i == 3) { angle = 65; posz += 0.005 * SizeZ; }
          else angle = 45;
          glTranslatef(posx, posy, posz);
          glRotatef(angle + 45, 1, 0, 0);
          igSolidCuboParedes(sizex, sizey2, sizez);
        }glPopMatrix();
      }

      /* Lado 2 */
      for (i = 9; i >= 6; i--) {
        sizey2 = (positions[i - 1][2] - positions[i][2]) + 0.005 * SizeZ;
        posx = positions[i][0];
        posy = positions[i][1] + sizey;
        posz = positions[i][2];
        glPushMatrix(); {
          if (i == 9) angle = 24;
          else if (i == 6) { angle = 65; sizey2 += 0.005 * SizeZ; }
          else angle = 45;
          glTranslatef(posx, posy, posz);
          glRotatef(angle + 45, 1, 0, 0);
          igSolidCuboParedes(sizex, sizey2, sizez);
        }glPopMatrix();
      }
    }glPopMatrix();
    glEndList();
  }
  else puts("Se ha producido un error creando la display list del puente.");
}

/******************************************************************************************/
/* Coloca las jardineras                                                                  */
/*			                                                                              */
/* Parametros: region = region actual                                                     */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void ColocaJardineras(Region region) {
  float radio = 0.035 * SizeX;
  float altura = 0.005 * SizeX;

  /* Jardinera 1 */
  {
    float posx = region.inicio_i + SizeX * 0.3;
    float posy = 0.015 * SizeZ;
    float posz = region.inicio_j + SizeZ * 0.15;
    glPushMatrix(); {
      texturaMadera();
      CreaCilindroExterior(posx, posy, posz, radio, altura);
      texturaCesped();
      CreaCilindroInterior(posx, posy, posz, radio - 0.05, altura);
      glTranslatef(posx, posy, posz);
      glCallList(abeto);
    }glPopMatrix();
  }

  /* Jardinera 2 */
  {
    float posx = region.inicio_i + SizeX * 0.7;
    float posy = 0.015 * SizeZ;
    float posz = region.inicio_j + SizeZ * 0.15;
    glPushMatrix(); {
      texturaMadera();
      CreaCilindroExterior(posx, posy, posz, radio, altura);
      texturaCesped();
      CreaCilindroInterior(posx, posy, posz, radio - 0.05, altura);
      glTranslatef(posx, posy, posz);
      glCallList(abeto);
    }glPopMatrix();
  }

}

/******************************************************************************************/
/* Crea un conjunto de cilindros huecos                                                   */
/*			                                                                              */
/* Parametros: posx=posicion en x, posy=posicion en y, posz=posicion en z,                */
/*   size=radio del cilindro, altura=altura del clindro                                   */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void CreaCilindroExterior(float posx, float posy, float posz, float size, float altura) {
  glPushMatrix(); {
    glTranslatef(posx, posy, posz);
    glRotatef(90, -1, 0, 0);
    float incr = 0.01;
    float sizeaux = size;
    int i;
    for (i = 0; i < 80; i++) {
      CreaCilindro(sizeaux, sizeaux, altura + 1, 40, 0);
      sizeaux += incr;
    }
    CreaCilindro(size, size, 0.25, 40, 1);
  }glPopMatrix();
}

/******************************************************************************************/
/* Crea un conjunto de cilindros huecos                                                   */
/*			                                                                              */
/* Parametros: posx=posicion en x, posy=posicion en y, posz=posicion en z,                */
/*   size=radio del cilindro, altura=altura del clindro                                   */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void CreaCilindroExterior2(float posx, float posy, float posz, float size1, float size2, float altura) {
  glPushMatrix(); {
    glTranslatef(posx, posy, posz);
    glRotatef(90, -1, 0, 0);
    float incr = 0.01;
    float sizeaux1 = size1;
    float sizeaux2 = size2;
    int i;
    for (i = 0; i < 80; i++) {
      CreaCilindro(sizeaux1, sizeaux2, altura + 1, 40, 0);
      sizeaux1 += incr; sizeaux2 += incr;
    }
    CreaCilindro(size1, size1, 0.25, 40, 1);
  }glPopMatrix();
}

/******************************************************************************************/
/* Crea un cilindro relleno                                                               */
/*			                                                                              */
/* Parametros: posx=posicion en x, posy=posicion en y, posz=posicion en z,                */
/*   size=radio del cilindro, altura=altura del clindro                                   */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void CreaCilindroInterior(float posx, float posy, float posz, float size, float altura) {
  glPushMatrix(); {
    glTranslatef(posx, posy, posz);
    glRotatef(90, -1, 0, 0);
    CreaCilindro(size, size, altura, 40, 1);
  }glPopMatrix();
}

/******************************************************************************************/
/* Crea un cilindro relleno  con distintos radios                                         */
/*			                                                                              */
/* Parametros: posx=posicion en x, posy=posicion en y, posz=posicion en z,                */
/*   size=radio del cilindro, altura=altura del clindro                                   */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void CreaCilindroInterior2(float posx, float posy, float posz, float size1, float size2, float altura) {
  glPushMatrix(); {
    glTranslatef(posx, posy, posz);
    glRotatef(90, -1, 0, 0);
    CreaCilindro(size1, size2, altura, 40, 1);
  }glPopMatrix();
}

/******************************************************************************************/
/*  Crea una display list para la valla                                                   */
/* Parametros: Ninguno                                                                    */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void CreaValla(void) {
  valla = glGenLists(1);
  if (valla != 0) {
    glNewList(valla, GL_COMPILE);

    float sizex = 0.0045 * SizeX;
    float sizey = 0.05 * SizeZ;
    float sizez = 0.0025 * SizeX;
    float posx = 0;
    float posy = 0;
    float posz = 0;
    glPushMatrix(); {
      glTranslatef(posx, posy, posz);
      texturaMadera();

      /* Respaldo */
      glPushMatrix(); {
        glRotatef(90, 1, 0, 0);
        glRotatef(90, 0, 0, 1);
        glRotatef(90, 0, 1, 0);
        glTranslatef(1.5, 0, 0);
        igSolidCuboParedes(sizex, sizey, sizez);
        glTranslatef(sizex * 2.5, 0, 0);
        igSolidCuboParedes(sizex, sizey, sizez);
      }glPopMatrix();

      /* Patas */
      glPushMatrix(); {
        float sizex2 = sizez;
        float sizey2 = 0.03 * SizeZ;
        float sizez2 = sizez;
        glTranslatef(0, -posy, 0);
        igSolidCuboParedes(sizex2, sizey2, sizez2);
        glTranslatef(-sizey, 0, 0);
        igSolidCuboParedes(sizex2, sizey2, sizez2);
      }glPopMatrix();
    }glPopMatrix();
    glEndList();
  }
  else puts("Se ha producido un error creando la display list de la valla.");
}

/******************************************************************************************/
/* Coloca las vallas en el terreno                                                        */
/* Parametros: Ninguno                                                                    */
/* Salida: Ninguna                                                                        */
/******************************************************************************************/
void ColocaVallas(void) {
  int i;
  Region reg;
  float margin = SizeX * 0.01;
  float disp = 0.05 * SizeZ;
  int num = 21;
  glPushMatrix(); {
    reg = regiones[0];
    glTranslatef(disp, 0, reg.fin_j);
    for (i = 0; i < num; i++) {
      if (i < 8 || i > 11)glCallList(valla);
      glTranslatef(disp, 0, 0);
    }
  }glPopMatrix();

  glPushMatrix(); {
    reg = regiones[4];
    glTranslatef(disp, 0, reg.fin_j);
    for (i = 0; i < num; i++) {
      if (i < 8 || i > 11)glCallList(valla);
      glTranslatef(disp, 0, 0);
    }
  }glPopMatrix();
}