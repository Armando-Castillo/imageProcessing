#include "header.h"

unsigned char *cargaImagen(char *filename, IMAGEN *matriz){
	FILE *fileImagen;
	HEADER infoImg;     
	unsigned char *imgdata;   
	uint16_t type;        
	
    //Lectura de imagen
	fileImagen=fopen (filename, "r");
	if (!fileImagen){
    puts("Imagen no se abrio correctamente");
		return NULL;   
    }    

	//TIPO
	fread(&type, sizeof(uint16_t), 1, fileImagen);
	if (type !=0x4D42) {        
		puts("Tipo de imagen incorrecto");
        fclose(fileImagen);
		return NULL;
	} 
    // Leer la cabecera
    fread(&infoImg,sizeof(HEADER),1,fileImagen);
    fread(matriz,sizeof(IMAGEN),1,fileImagen);

    printf("El tamaño del archivo: %d\n",infoImg.size);
    printf("Eloffset %d\n",infoImg.offset);



    //Leer la imagen (datos/pixeles); reservamos e primer lugar memoria dinámica para la matriz de datos
    imgdata=(unsigned char*)malloc(matriz->imgsize);
    if(imgdata==NULL){
            puts("La memoria no es suficiente");
            fclose(fileImagen);
            return NULL;
    }
    //Mover el cursor al punto especifico donde inician los datos
    fseek(fileImagen, infoImg.offset, SEEK_SET);
    //fseek(newImage, infoImg.offset, SEEK_SET);
    //Leer los datos de manera lineal
    fread(imgdata,matriz->imgsize,1,fileImagen);
    //fwrite(imgdata,(matrizImagen->ancho)*(matrizImagen->alto),1,newImage);
    //fwrite() para resguardar la información
    //fwrite(&tipo, sizeof(uint16_t),1,newImage);
    //fwrite(&cabecera,sizeof(CabeceraImg),1,newImage);
    //fwrite(matrizImagen,sizeof(Imagen),1,newImage);
    //fseek(newImage, cabecera.offset, SEEK_SET);
    //fwrite(imgdata,(matrizImagen->ancho)*(matrizImagen->alto),1,newImage);
    //cerrar el archivo de la imagen
    fclose(fileImagen);
    //fclose(newImage);
    return imgdata;
}


//Funcion para fragmentar
unsigned char *fragmentarImagen(IMAGEN *contenido, unsigned char *pixeles){
    printf("Ancho: %d\n", contenido->ancho);
    printf("Alto: %d\n", contenido->alto);
    printf("Bpp: %d\n", contenido->bpp);
    printf("coloresR: %d\n", contenido->coloresR);
    printf("compresion: %d\n", contenido->compresion);
    printf("Imgsize: %d\n", contenido->imgsize);
    printf("Imxtcolors: %d\n", contenido->imxtcolors);
    printf("Planos: %d\n", contenido->planes);
    printf("resX: %d\n", contenido->resX);
    printf("resY: %d\n", contenido->resY);

    //nuevoArchivo
    FILE *fragmento1 = NULL;
    fragmento1 = fopen("fragmento1.txt", "wb");
    FILE *fragmento2 = NULL;
    fragmento2 = fopen("fragmento2.txt", "wb");
    FILE *fragmento3 = NULL;
    fragmento3 = fopen("fragmento3.txt", "wb");
    FILE *fragmento4 = NULL;
    fragmento4 = fopen("fragmento4.txt", "wb");
    int ejeX = contenido->alto/2;
    int ejeY = contenido->ancho/2;
    int posicionX = 0;
    int posicionY = 0;

    for(ejeY=contenido->alto/2; ejeY>=0; ejeY--){
		for(ejeX=0; ejeX<=contenido->ancho/2; ejeX++){
            char *buffer[5];
            //printf("%d\t", imgdata[ejeX+ejeY*(matriz->ancho/2)]);
            fprintf(fragmento1, "%i\t", pixeles[ejeX+ejeY*(contenido->ancho/2)]);
            posicionX++;
        }
        posicionY++;
        fprintf(fragmento1,"\n");
    }

    for(ejeY=contenido->alto/2; ejeY>=0; ejeY--){
		for(ejeX=contenido->ancho/2; ejeX<=contenido->ancho; ejeX++){
            //printf("%d\t",imgdata[ejeX+ejeY*(matriz->ancho/2)]);
            fprintf(fragmento2, "%d\t",pixeles[ejeX+ejeY*(contenido->ancho/2)]);
            posicionX++;
        }
        posicionY++;
        fprintf(fragmento2,"\n");
    }

    for(ejeY=contenido->alto; ejeY>=contenido->alto/2; ejeY--){
		for(ejeX=0; ejeX<=contenido->ancho/2; ejeX++){
            //printf("%d\t",imgdata[ejeX+ejeY*(matriz->ancho/2)]);
            fprintf(fragmento3, "%d\t", pixeles[ejeX+ejeY*(contenido->ancho/2)]);
            posicionX++;
        }
        posicionY++;
        fprintf(fragmento3,"\n");
    }

    for(ejeY=contenido->alto; ejeY>=contenido->alto/2; ejeY--){
		for(ejeX=contenido->ancho/2; ejeX<=contenido->ancho; ejeX++){
            //printf("%d\t", imgdata[ejeX+ejeY*(matriz->ancho/2)]);
            fprintf(fragmento4, "%d\t",pixeles[ejeX+ejeY*(contenido->ancho/2)]);
            posicionX++;
        }
        posicionY++;
        fprintf(fragmento4,"\n");
    }

    printf("Imagen fragmentada\n");
    fwrite(pixeles,(contenido->ancho/2)*(contenido->alto/2),1, fragmento1);
    fclose(fragmento1);
    fclose(fragmento2);
    fclose(fragmento3);
    fclose(fragmento4);
    free(pixeles);
}

//Funcion para sumar
unsigned char *sumarImagenes(unsigned char *pixeles, unsigned char *info){
    FILE *archivoSuma = NULL;
    archivoSuma = fopen("matrizSumada.txt","w");
    unsigned char *pixels;
    pixels=(unsigned char*)malloc(49152);
    int ejeX, ejeY, posicionX=0, posicionY=0;
    //Operación que recorre a los pixeles y los rota en el eje Y (alto de la imagen)
	for(ejeY=128; ejeY>0; ejeY--){
		for(ejeX=0; ejeX<128; ejeX++){
            pixels[ejeX+ejeY*(128)]=pixeles[ejeX+ejeY*(128)];
            fprintf(archivoSuma, "%d\t" ,pixels[ejeX+ejeY*(128)]);
            posicionX++;
    }
    posicionY++;
    fprintf(archivoSuma,"\n");
  }
  int i;
  for(i=0; i<49152; i++)
  {
    if(info[i]+pixeles[i]>255)
    {
      pixels[i]=255;
    }
    else if(info[i]+pixeles[i]==255)
    {
      pixels[i]=255;
    }
    else {
      pixels[i]=0;
    }

  }

  fclose(archivoSuma);
  free(pixeles);
  free(info);
  return pixels;
}


//Función para multiplicar
unsigned char *multiImagenes(unsigned char *pixeles, unsigned char *info){
    FILE *archivoMulti = NULL;
    archivoMulti = fopen("matrizMulti.txt","w");
    unsigned char *pixels;
    pixels=(unsigned char*)malloc(49152);
    int ejeX, ejeY, posicionX=0, posicionY=0;
    //Operación que recorre a los pixeles y los rota en el eje Y (alto de la imagen)
    for(ejeY=128; ejeY>0; ejeY--){
		for(ejeX=0; ejeX<128; ejeX++){
            pixels[ejeX+ejeY*(128)]=pixeles[ejeX+ejeY*(128)];
            fprintf(archivoMulti, "%d\t" ,pixels[ejeX+ejeY*(128)]);
            posicionX++;
    }
    posicionY++;
    fprintf(archivoMulti,"\n");
  }
  int i;
  for(i=0; i<49152; i++)
  {
    if(info[i]+pixeles[i]>255)
    {
      pixels[i]=255;
    }
    else if(info[i]+pixeles[i]==255)
    {
      pixels[i]=255;
    }
    else {
      pixels[i]=0;
    }

  }

  fclose(archivoMulti);
  free(pixeles);
  free(info);
  return pixels;
}


//Función para guardar
void guardarPNG(){

}

void guardarBMP(char *filename, IMAGEN *info, unsigned char *imgdata)
{
  HEADER header;
  FILE *f;
  uint16_t type;
 
  f=fopen(filename, "wb");
  header.size=49152+sizeof(HEADER)+sizeof(IMAGEN);

  /* El offset será el tamaño de las dos cabeceras + 2 (información de fichero)*/
  header.offset=sizeof(HEADER)+sizeof(IMAGEN)+2;

  /* Escribimos la identificación del archivo */
  type=0x4D42;
  fwrite(&type, sizeof(type),1,f);

  /* Escribimos la cabecera de fichero */
  fwrite(&header, sizeof(HEADER),1,f);

  /* Escribimos la información básica de la imagen */
  fwrite(info, sizeof(IMAGEN),1,f);

  /* Escribimos la imagen */
  fwrite(imgdata, 49152, 1, f);
  fclose(f);
}


//FUnción para medir tiempo
void tiempo(){

}

//Función para iniciar
void iniciar(char *nombre1, char *nombre2){
    IMAGEN matriz;
    unsigned char *imagen1 =cargaImagen(nombre1, &matriz);
    fragmentarImagen(&matriz, imagen1);

    IMAGEN matriz2;
    unsigned char *imagen2 =cargaImagen(nombre1, &matriz2);
    fragmentarImagen(&matriz, imagen2);

    unsigned char *multi;
    unsigned char *suma;
    multi=multiImagenes(imagen2,imagen1);
    suma=sumarImagenes(imagen2, imagen1);
    guardarBMP("matrizMulti.bmp", &matriz2, multi);
    guardarBMP("matrizSumada.bmp",&matriz2, suma);
}