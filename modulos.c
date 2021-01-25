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
	uint32_t type; 

    //Abrir imagen en lectura
    fileImagen = fopen(nombre, "r");
	if (!fileImagen){
        puts("Imagen no se abrio correctamente");  
    }  
    fread(&type, sizeof(uint16_t), 1, fileImagen);
    if(type != 0x4D42){
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

    //Leer la imagen (datos/pixeles); reservamos e primer lugar memoria dinámica para la matriz de datos
    imgdata=(unsigned char*)malloc((matriz->ancho)*(matriz->alto));
    if(imgdata==NULL){
		puts("La memoria no es suficiente");
		fclose(fileImagen);
		return;
    }
    //Mover el cursor al punto especifico donde inician los datos
    fseek(fileImagen, infoImg.offset, SEEK_SET);

    //Leer los datos de manera lineal
    fread(imgdata,(matriz->ancho)*(matriz->alto),1,fileImagen);

    //fwrite() para resguardar la información

    //cerrar el archivo de la imagen
    fclose(fileImagen);

    //info
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

    //nuevoArchivo
    FILE *fragmento1 = NULL;
    fragmento1 = fopen("fragmento1.txt", "w");
    FILE *fragmento2 = NULL;
    fragmento2 = fopen("fragmento2.txt", "w");
    FILE *fragmento3 = NULL;
    fragmento3 = fopen("fragmento3.txt", "w");
    FILE *fragmento4 = NULL;
    fragmento4 = fopen("fragmento4.txt", "w");
    int ejeX = matriz->alto/2;
    int ejeY = matriz->ancho/2;
    int posicionX = 0;
    int posicionY = 0;

    for(ejeY=matriz->alto/2; ejeY>=0; ejeY--){
		for(ejeX=0; ejeX<=matriz->ancho/2; ejeX++){
            printf("%d\t", imgdata[ejeX+ejeY*(matriz->ancho/2)]);
            fprintf(fragmento1, "%d\t", imgdata[ejeX+ejeY*(matriz->ancho/2)]);
            posicionX++;
        }
        posicionY++;
        fprintf(fragmento1,"\n");
    }

    printf("FRAGMENTO 2");
    for(ejeY=matriz->alto/2; ejeY>=0; ejeY--){
		for(ejeX=matriz->ancho/2; ejeX<=matriz->ancho; ejeX++){
            printf("%d\t",imgdata[ejeX+ejeY*(matriz->ancho/2)]);
            fprintf(fragmento2, "%d\t",imgdata[ejeX+ejeY*(matriz->ancho/2)]);
            posicionX++;
        }
        posicionY++;
        fprintf(fragmento2,"\n");
    }

    printf("FRAGMENTO 3");
    for(ejeY=matriz->alto; ejeY>=matriz->alto/2; ejeY--){
		for(ejeX=0; ejeX<=matriz->ancho/2; ejeX++){
            printf("%d\t",imgdata[ejeX+ejeY*(matriz->ancho/2)]);
            fprintf(fragmento3, "%d\t", imgdata[ejeX+ejeY*(matriz->ancho/2)]);
            posicionX++;
        }
        posicionY++;
        fprintf(fragmento3,"\n");
    }

    printf("FRAGMENTO 4");
    for(ejeY=matriz->alto; ejeY>=matriz->alto/2; ejeY--){
		for(ejeX=matriz->ancho/2; ejeX<=matriz->ancho; ejeX++){
            printf("%d\t", imgdata[ejeX+ejeY*(matriz->ancho/2)]);
            fprintf(fragmento4, "%d\t",imgdata[ejeX+ejeY*(matriz->ancho/2)]);
            posicionX++;
        }
        posicionY++;
        fprintf(fragmento4,"\n");
    }
    fwrite(imgdata,(matriz->ancho/2)*(matriz->alto/2),1, fragmento1);
    fclose(fragmento1);
    fclose(fragmento2);
    fclose(fragmento3);
    fclose(fragmento4);
    free(imgdata);
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