/*
	Nombres:
		De la Cruz Martinez Jorge Luis
		González Mendoza Aarón Abdiel
		Lemus Vallarta Yarazeth Amayrani
		Verduzco Lozano Iván Antonio
	Grupo: 1AM1
	Carrera: Licenciatura en Ciencia de Datos
	Fecha: 21/01/2020 
*/
#include "cabecera.h"

void inicio(int cuantos, char **datos){

	clock_t inicioTiempo, finalTiempo;

	inicioTiempo = clock();

	printf("|--------Proyecto para Licenciatura en Ciencia de Datos--------|\n\n");

	registrarDatos(cuantos, datos);

	imprimirHasta_n(1);
	imprimirHasta_n(2);
	imprimirHasta_n(3);

	imprimirConvergencia(1);
	imprimirConvergencia(2);
	imprimirConvergencia(3);

	generadorDeSuma(1);
	generadorDeSuma(2);
	generadorDeSuma(3);

	generarImagen(1);
	generarImagen(2);
	generarImagen(3);

	finalTiempo = clock();

	especificarTiempo(inicioTiempo, finalTiempo);

}

void registrarDatos(int cuantos, char **datos){
	for (int i = 0; i < (cuantos - 1); i++){
		if(i < 3)
			series[0].valoresSerie[i] = atof(datos[i+1]);
		else
			if(i > 5)
				series[2].valoresSerie[i-6] = atof(datos[i+1]);
			else
				series[1].valoresSerie[i-3] = atof(datos[i+1]);
	}
}

void imprimirHasta_n(int serie){
	double k, h, n;
	double An = 0;

	switch(serie){

		case 1:// ⅀ k/i*h
		
			k = series[0].valoresSerie[0]; 
			h = series[0].valoresSerie[1]; 
			n = series[0].valoresSerie[2];

			if(h != 0){
				for (int i = 1; i <= n; i++)
					An += k/(i*h);
				printf("La serie 1 desde 1 hasta %d resulta: %f\n",(int) n, An);
				series[0].seIndetermina = 0;
			}
			else{
				printf("ERROR, Indeterminacion porque h = 0 en la serie 1.\n");
				series[0].seIndetermina = 1;
			}
		break;
		case 2:// ⅀ (k/h)^i

			k = series[1].valoresSerie[0]; 
			h = series[1].valoresSerie[1]; 
			n = series[1].valoresSerie[2];

			if(h != 0){
				for (int i = 0; i <= n; i++)
					An += pow((k/h), i);
				printf("La serie 2 desde 0 hasta %d resulta: %f\n",(int) n, An);
				series[1].seIndetermina = 0;
			}
			else{
				printf("ERROR, Indeterminacion porque h = 0, en la serie 2.\n");
				series[1].seIndetermina = 1;
			}
		break;
		case 3:// ⅀ (-1)^i * k^i *h^i
			
			k = series[2].valoresSerie[0]; 
			h = series[2].valoresSerie[1]; 
			n = series[2].valoresSerie[2];
			double a_x_b;

			for (int i = 0; i <= n; i++){
				a_x_b = pow(-1, i) * pow(k, i);
				An += a_x_b * pow(h, i);
			}
			printf("La serie 3 desde 0 hasta %d resulta: %f\n", (int) n, An);
			series[2].seIndetermina = 0;
		break;
		default:
			puts("No existe la serie :C");
		break;
	}

}

void imprimirConvergencia(int serie){

	switch(serie){
		case 1:
			puts("La serie 1 no Converge");
		break;
		case 2:
			if((series[1].valoresSerie[0] / series[1].valoresSerie[1]) < 1){
				puts("La serie 2 Converge");
				series[1].converge = 1;
			}
			else{
				puts("La serie 2 no Converge");
				series[1].converge = 0;
			}
		break;
		case 3:
			if((series[2].valoresSerie[0] * series[2].valoresSerie[1]) <= 1){
				puts("La serie 3 Converge.");
				series[2].converge = 1;
			}
			else{
				puts("La serie 3 no Converge.\n");
				series[2].converge = 0;
			}
		break;
		default:
			puts("No existe la serie :C");
		break;
	}
}

void generadorDeSuma(int serie){
	double k, h, n;
	double An = 0;
	int x = 0, y = 0;

	switch(serie){
		case 1:
			k = series[0].valoresSerie[0]; 
			h = series[0].valoresSerie[1]; 
			n = series[0].valoresSerie[2];

			if(!series[0].seIndetermina){
				for (int i = 1; i <= IMAGEN; i++){
					An += k/(i*h);
					series[0].arregloImagen[x][y] = An; 
					x++;
					if(x % 128 == 0){
						y++;
						x = 0;
					}
				}
			}

		break;
		case 2:
			k = series[1].valoresSerie[0]; 
			h = series[1].valoresSerie[1]; 
			n = series[1].valoresSerie[2];

			if(!series[1].seIndetermina){
				for (int i = 0; i <= IMAGEN; i++){
					An += pow((k/h), i);
					series[1].arregloImagen[x][y] = An; 
					x++;
					if(x % 128 == 0){
						y++;
						x = 0;
					}
				}
			}	
		break;
		case 3:
			k = series[2].valoresSerie[0]; 
			h = series[2].valoresSerie[1]; 
			n = series[2].valoresSerie[2];
			double a_x_b;

			for (int i = 0; i <= IMAGEN; i++){
				a_x_b = pow(-1, i) * pow(k, i);
				An += a_x_b * pow(h, i);
				series[2].arregloImagen[x][y] = An; 
				x++;
				if(x % 128 == 0){
					y++;
					x = 0;
				}
			}
		break;
		default:
			puts("No existe la serie :C");
		break;
	}

}

void especificarTiempo(clock_t inicioTiempo, clock_t finalTiempo){

	clock_t tiempoTotal;

	tiempoTotal = (double) (finalTiempo - inicioTiempo)/CLOCKS_PER_SEC;

	printf("Tiempo total de evaluacion: %ld\n", tiempoTotal);

}
int round4(int x) {
    return x % 4 == 0 ? x : x - x % 4 + 4;
}

void write_bmp(char *filename, char rgb[], int length, int width) {
    int height = (length / 3) / width;

    // Pad the width of the destination to a multiple of 4
    int padded_width = round4(width * 3);
    
    int bitmap_size = height * padded_width * 3;
    char *bitmap = (char *) malloc(bitmap_size * sizeof(char));
    for (int i = 0; i < bitmap_size; i++) bitmap[i] = 0;

    // For each pixel in the RGB image...
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            
            // For R, G, and B...
            for (int color = 0; color < 3; color++) {

                // Get the index of the destination image
                int index = row * padded_width + col * 3 + color;

                // Set the destination to the value of the src at row, col.
                bitmap[index] = rgb[3*(row * width + col) + (2 - color)];
            }
        }
    }

    char tag[] = { 'B', 'M' };
    int header[] = {
        0, 0, 0x36, 0x28, width, height, 0x180001, 
        0, 0, 0x002e23, 0x002e23, 0, 0
    };
    header[0] = sizeof(tag) + sizeof(header) + bitmap_size;
    FILE *fp = fopen(filename, "w+");
    fwrite(&tag, sizeof(tag), 1, fp);
    fwrite(&header, sizeof(header), 1, fp);
    fwrite(bitmap, bitmap_size * sizeof(char), 1, fp);
    fclose(fp);
    free(bitmap);
}

void generarImagen(int serie){

	switch(serie){
		case 1:
			puts("No se genero la imagen de la serie 1, la serie no converge.");
		break;
		case 2:
			if(series[1].converge && !series[1].seIndetermina){

				char *imagen = (char*) malloc(128 * 128* sizeof(char) * 3);
	    		for (int i = 0; i < 128; i++) {
	        		for (int j = 0; j < 128; j++) {
	        			printf("%f\n", series[1].arregloImagen[i][j]);
	        			if(series[1].arregloImagen[i][j] < 10){
	        				int dividido = series[1].arregloImagen[i][j]*100;
	        				printf("%d\n", dividido);
	        				imagen[3 * (i * 128 + j)] = dividido;
	            			imagen[3 * (i * 128 + j)+1] = dividido - i;
	            			imagen[3 * (i * 128 + j)+2] = dividido - j;
	        			}else{
		        			if(series[1].arregloImagen[i][j] > 766){
		        				imagen[3 * (i * 128 + j)] = 255;
		            			imagen[3 * (i * 128 + j)+1] = 255;
		            			imagen[3 * (i * 128 + j)+2] = 255;
		        			}else{
		        				int dividido = (int)series[1].arregloImagen[i][j];
		        				printf("%d\n", dividido);
		        				imagen[3 * (i * 128 + j)] = dividido;
		            			imagen[3 * (i * 128 + j)+1] = dividido;
		            			imagen[3 * (i * 128 + j)+2] = dividido;
		        			}
	        			}
	        		}
	    		}
	    		write_bmp("serie2.bmp", imagen, 49152, 128);

			}
			else 
				puts("No se genero la imagen de la serie 2, la serie no converge.");
		break;
		case 3:
			if(series[2].converge && !series[2].seIndetermina){
				char *imagen = (char*) malloc(128 * 128* sizeof(char) * 3);
	    		for (int i = 0; i < 128; i++) {
	        		for (int j = 0; j < 128; j+= 3) {
	        			if(series[2].arregloImagen[i][j] < 1){
	        				imagen[3 * (i * 128 + j)] = 0;
	            			imagen[3 * (i * 128 + j)+1] = 0;
	            			imagen[3 * (i * 128 + j)+2] = 0;
	        			}else
	        			if(series[2].arregloImagen[i][j] > 766){
	        				imagen[3 * (i * 128 + j)] = 255;
	            			imagen[3 * (i * 128 + j)+1] = 255;
	            			imagen[3 * (i * 128 + j)+2] = 255;
	        			}else{
	        				int dividido = (int) series[2].arregloImagen[i][j]/3;
	        				imagen[3 * (i * 128 + j)] = dividido;
	            			imagen[3 * (i * 128 + j)+1] = dividido;
	            			imagen[3 * (i * 128 + j)+2] = dividido;
	        			}
	        		}
	    		}
	    		write_bmp("serie3.bmp", imagen, 49152, 128);
			}
			else
				puts("No se genero la imagen de la serie 3, la serie no converge.");
		break;
		default:
			puts("No existe la serie :C");
		break;
	}
}