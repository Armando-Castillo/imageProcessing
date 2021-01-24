#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


typedef struct {
  int size;        						  // Tamaño del archivo 
  uint16_t caracteristicaAdicional;       // Información reservada de la imagen
  uint16_t reservadoCopia;            //Se incrementa por cada copia  
  int offset;      		                  // Valor donde empieza el pixel partiendo desde el inicio del archivo
} CabeceraImg; //12 bytes							  // variable que almacena la estructura de la cabecer

typedef struct{
    unsigned char PNGSignature[8];
    size_t nb;
    unsigned char ImageHeader[4];
    size_t width;
    size_t height;
    unsigned char bitDepth;
    unsigned char colorType;
    unsigned char compressionMethod;
    unsigned char filterMethod;
    unsigned char interlaceMethod;
    int tamCabecera;  	// Tamaño de la cabecera 
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
} PNG_HEADER;


unsigned char *cargaImagenFile(char *filename, PNG_HEADER *matrizImagen){
	FILE *fileImagen;
	CabeceraImg infoImg;     // cabecera 
	unsigned char *imgdata;   // datos de imagen (es una matriz que se lee de forma lineal y continua)
	uint16_t type;        // 2 bytes identificativos 

	//Lectura de imagen en modo lectura
	  fileImagen=fopen (filename, "r");
	if (!fileImagen){
    puts("Imagen no se abrio correctamente");
		return NULL;   
  }    
	// Leemos los dos primeros bytes para comprobar el tipo de imagen BMP
	fread(&type, sizeof(uint16_t), 1, fileImagen);
  printf("%d", type);
	if (type != 20617) {        //BMP   //PNG -->5D40  y palabra PNG 
		puts("Tipo de imagen incorrecto");
    fclose(fileImagen);
		return NULL;
	}
  // Leer la cabecera( 2 secciones)
  fread(&infoImg,sizeof(CabeceraImg),1,fileImagen);
  fread(matrizImagen,sizeof(PNG_HEADER),1,fileImagen);


  printf("El tamaño del archivo: %d\n",infoImg.size);
  printf("Eloffset %d\n",infoImg.offset);



  //Leer la imagen (datos/pixeles); reservamos e primer lugar memoria dinámica para la matriz de datos
  imgdata=(unsigned char*)malloc((matrizImagen->ancho)*(matrizImagen->alto));
  if(imgdata==NULL){
		puts("La memoria no es suficiente");
		fclose(fileImagen);
		return NULL;
  }
  //Mover el cursor al punto especifico donde inician los datos
  fseek(fileImagen, infoImg.offset, SEEK_SET);

  //Leer los datos de manera lineal
  fread(imgdata,(matrizImagen->ancho)*(matrizImagen->alto),1,fileImagen);

  //fwrite() para resguardar la información

  //cerrar el archivo de la imagen
  fclose(fileImagen);
  return imgdata;
}

int imprimePixelesEnArchivo(PNG_HEADER *cabeceraContenidoImagen, unsigned char *pixeles){
  printf("El tamaño de la cabecera: %u\n",cabeceraContenidoImagen->tamCabecera);
  printf("El ancho es de %d\n",cabeceraContenidoImagen->ancho);
  printf("El alto es de %d\n",cabeceraContenidoImagen->alto);
  printf("Cantidad de planos: %d\n",cabeceraContenidoImagen->planes);
  printf("La cantidad de bits por pixel(bpp): %d\n",cabeceraContenidoImagen->bpp);
  printf("El tamaño de la imagen: %u\n",cabeceraContenidoImagen->imgsize);  
  printf("El rango de colores: %d\n",cabeceraContenidoImagen->coloresR);  
  printf("Compresion: %d\n",cabeceraContenidoImagen->compresion); 
  printf("La resX es de %d\n",cabeceraContenidoImagen->resX);
  printf("La resY es de %d\n",cabeceraContenidoImagen->resY);
  printf("El imx es de %d\n",cabeceraContenidoImagen->imxtcolors);
  FILE *archivoCopia = NULL;
  FILE *archivoCopiaOrden = NULL;
  archivoCopia=fopen("Img.txt","wb");
  archivoCopiaOrden=fopen("ImgOrg.txt","w");
  if(archivoCopia==NULL || archivoCopiaOrden==NULL){
    perror("Ocurrio un error al abrir el archivo Img.txt");
    return 1;
  } 
  int ejeX, ejeY, posicionX=0, posicionY=0;
  //Operación que recorre a los pixeles y los rota en el eje Y (alto de la imagen)
	for(ejeY=cabeceraContenidoImagen->alto; ejeY>0; ejeY--){
		for(ejeX=0; ejeX<cabeceraContenidoImagen->ancho; ejeX++){
      printf("[%d][%d]=[%d]\t",ejeY, ejeX, pixeles[ejeX+ejeY*(cabeceraContenidoImagen->ancho)]);
      fprintf(archivoCopia, "[%d][%d]=[%d]\t",ejeY, ejeX, pixeles[ejeX+ejeY*(cabeceraContenidoImagen->ancho)]);
      fprintf(archivoCopiaOrden, "[%d][%d]=[%d]\t",posicionY, posicionX, pixeles[ejeX+ejeY*(cabeceraContenidoImagen->ancho)]);
      posicionX++;
    }
    posicionY++;
    fprintf(archivoCopia,"\n");
    fprintf(archivoCopiaOrden,"\n");
  }
  fwrite(pixeles,(cabeceraContenidoImagen->ancho)*(cabeceraContenidoImagen->alto),1,archivoCopia);
  fclose(archivoCopia);
  fclose(archivoCopiaOrden);
  free(pixeles);
  return 0;
}

void main(){
  PNG_HEADER estructuraImg;
  unsigned char *img=cargaImagenFile("imagen.png", &estructuraImg);
	if(img==NULL){
		puts("Ocurrio un error al cargar la imagen original");
		exit(1);
	}
	if(imprimePixelesEnArchivo(&estructuraImg, img)==1){
		puts("Ocurrio un error");
		exit(1);
	}
}