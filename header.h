#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#define PNGFORMATO 0x5D40
#define FRAGMENTO 64
#define TAMANO 128
//#define IMAGEN "imagen128.png"

//Estructura para cabecera de imagen
typedef struct {
  int size;        						  // Tamaño del archivo 
  uint16_t caracteristicaAdicional;       // Información reservada de la imagen
  uint16_t reservadoCopia;            //Se incrementa por cada copia  
  int offset;      		                  // Valor donde empieza el pixel partiendo desde el inicio del archivo
} HEADER; //12 bytes							  // variable que almacena la estructura de la cabecer

//Estructura para cuerpo de imagen
typedef struct{
    int ancho;       		// Ancho de la imagen
    int alto;      		// Alto de la imagen
    uint16_t planes;      // Planos de color 
    uint16_t bpp;         // bits por pixel
    int compresion;   	// Información sobre la compresión utilizada
    int imgsize;     		// tamaño de los datos de imagen 
    int resX;        		// Resolución X
    int resY;        		// Resolución Y 
    int coloresR;      	// Rango de colores (2^bpp)
    int imxtcolors; 
} IMAGEN;


void iniciar(char *nombre1, char *nombre2);
unsigned char *cargaImagen(char *filename, IMAGEN *matriz);
unsigned char *fragmentarImagen(IMAGEN *contenido, unsigned char *pixeles);
unsigned char *sumarImagenes(unsigned char *pixeles, unsigned char *info);
unsigned char *multiImagenes(unsigned char *pixeles, unsigned char *data);
void guardarBMP(char *filename, IMAGEN *info, unsigned char *imgdata);
void tiempo();




