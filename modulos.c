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


    printf("El tamaño del archivo: %d\n",infoImg.size);
    printf("Eloffset %d\n",infoImg.offset);
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