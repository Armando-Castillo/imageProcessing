#include "header.h"

//Estructura para cabecera de imagen
typedef struct {
  int size;        						  // Tamaño del archivo 
  uint16_t caracteristicaAdicional;       // Información reservada de la imagen
  uint16_t reservadoCopia;            //Se incrementa por cada copia  
  int offset;      		                  // Valor donde empieza el pixel partiendo desde el inicio del archivo
} Header; //12 bytes							  // variable que almacena la estructura de la cabecer

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


//Función para iniciar
void iniciar(char *nombre){
    printf("%s", nombre);

}


//Funcion para fragmentar
void fragmentarImagen(){

}

//Funcion para sumar
void sumarImagenes(){

}


//Función para multiplicar
void multiImagenes(){

}


//Función para guardar
void guardarPNG(){

}


//FUnción para medir tiempo
void tiempo(){

}