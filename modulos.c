#include "header.h"

//Función para iniciar
void iniciar(char *nombre){
    IMAGEN matriz;
    fragmentarImagen(nombre, &matriz);
}


//Funcion para fragmentar
void fragmentarImagen(char *nombre, IMAGEN *matriz){
    FILE *fileImagen;
	HEADER infoImg;     
	unsigned char *imgdata;   
	uint16_t type; 

    //Abrir imagen en lectura
    fileImagen = fopen(nombre, "r");
	if (!fileImagen){
        puts("Imagen no se abrio correctamente");  
    }  
    fread(&type, sizeof(uint16_t), 1, fileImagen);
    if(type != 20617){
        printf("EL archivo '%s' no es png", nombre);
        fclose(fileImagen);
        return;
    }
    printf("Obteniendo info...\n");
    fread(&infoImg,sizeof(HEADER),1,fileImagen);
    fread(matriz,sizeof(IMAGEN),1,fileImagen);

    //tamaño y offset
    printf("El tamaño del archivo: %d\n",infoImg.size);
    printf("El offset %d\n",infoImg.offset);
    printf("Ancho: %i\n", matriz->ancho);
    printf("Alto: %i\n", matriz->alto);
    printf("Bpp: %i\n", matriz->bpp);
    printf("coloresR: %i\n", matriz->coloresR);
    printf("compresion: %i\n", matriz->compresion);
    printf("Imgsize: %i\n", matriz->imgsize);
    printf("Imxtcolors: %i\n", matriz->imxtcolors);
    printf("Planos: %i\n", matriz->planes);
    printf("resX: %i\n", matriz->resX);
    printf("resY: %i\n", matriz->resY);
    //Leer la imagen (datos/pixeles); reservamos e primer lugar memoria dinámica para la matriz de datos
    imgdata=(unsigned char*)malloc((matriz->ancho)*(matriz->alto));
    if(imgdata==NULL){
		puts("La memoria no es suficiente");
		fclose(fileImagen);
		return;
    }
    printf("data %s", imgdata);
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