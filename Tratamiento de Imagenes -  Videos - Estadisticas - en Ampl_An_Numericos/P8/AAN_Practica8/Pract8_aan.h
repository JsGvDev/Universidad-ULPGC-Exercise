#ifndef PRACT8_AAN_H_
#define PRACT8_AAN_H_

#include "Pract2_aan.h"

//funcion para leer los datos de una imagen:
int Leer_imagen(char *nombre, float **red, float **green, float **blue,
				 int *width, int *height){
	
	struct canales Can1;
	printf("DATOS EXTERNOS:\n\n");
	if (ami_read_bmp(nombre,&Can1.red,&Can1.green,&Can1.blue,&Can1.width,&Can1.height)){
			printf ("Error abriendo la Imagen: %s\n\n", nombre);
			return 0;
	}
	
	*width = Can1.width;
	*height = Can1.height;
	
	long size;
	size = (3*(*width) + (*width)%4)*(*height);
	
	*red =(float*) malloc(size*sizeof(float));
	*green =(float*) malloc(size*sizeof(float));
	*blue =(float*) malloc(size*sizeof(float));
	
	if ((*red==NULL) || (*green==NULL) || (*blue==NULL)){
		printf("Problemas con la memoria(memoria no disponible)\n\n");
		return 0;
	}
	
	int i;
	for (i=0; i<size; i++){
		(*red)[i] = (float) Can1.red[i];
		(*green)[i] = (float) Can1.green[i];
		(*blue)[i] = (float) Can1.blue[i];
	}
	free(Can1.red);
	free(Can1.green);
	free(Can1.blue);
	return 1;
}

//ECUACION DE ONDAS:
void aan_ecuacion_ondas_metodo_explicito(float *red_act, float *green_act, float *blue_act, 
										 float *red_ant, float *green_ant, float *blue_ant,
										 int width, int height, float dt, int Niter){
	
	//Laplaciano
	float *red_lap =(float*) malloc((width*height)*sizeof(float));
	float *green_lap =(float*) malloc((width*height)*sizeof(float));
	float *blue_lap =(float*) malloc((width*height)*sizeof(float));
	
	if ((red_lap==NULL) || (green_lap==NULL) || (blue_lap==NULL)){
		printf("Problemas con la memoria(memoria no disponible)/n");
		return;
	}
	
	//Imagen anterior
	red_ant =(float*) malloc((width*height)*sizeof(float));
	green_ant =(float*) malloc((width*height)*sizeof(float));
	blue_ant =(float*) malloc((width*height)*sizeof(float));
	
	if ((red_ant==NULL) || (green_ant==NULL) || (blue_ant==NULL)){
		printf("Problemas con la memoria(memoria no disponible)/n");
		return;
	}
		
	int i,j;
	char name[200];
	//necesario para el ami_write
	unsigned char *wr_red;
	unsigned char *wr_green;
	unsigned char *wr_blue;
	wr_red =(unsigned char*) malloc((width*height)*sizeof(unsigned char));
	wr_green =(unsigned char*) malloc((width*height)*sizeof(unsigned char));
	wr_blue =(unsigned char*) malloc((width*height)*sizeof(unsigned char));
	
	//U1 = U0
	for(i=0; i<(width*height); i++){
		red_ant[i] = red_act[i];
		green_ant[i] = green_act[i];
		blue_ant[i] = blue_act[i];
	}
	float red,green,blue; //valores temporales
	for(i=0; i<Niter; i++){
		
		aan_mascara_imagen(red_act,green_act,blue_act,red_lap,green_lap,blue_lap,width,height,m_lap);
		
		for(j=1; j<(width*height); j++){
		//ecuacion de onda
			red = 2*red_act[j] - red_ant[j] + dt*dt*red_lap[j];
			green = 2*green_act[j] - green_ant[j] + dt*dt*green_lap[j];
			blue = 2*blue_act[j] - blue_ant[j] + dt*dt*blue_lap[j];
		//niveles de gris no deben superar 255 o ser inferior a 0
			if (red > 255){
				red = 255;
			} else {
				if (red < 0){
					red = 0;
				}
			}
			if (green > 255){
				green = 255;
			} else {
				if (green < 0){
					green = 0;
				}
			}
			if (blue > 255){
				blue = 255;
			} else {
				if (blue < 0){
					blue = 0;
				}
			}
		//imagen anterior = imagen actual
			red_ant[j] = red_act[j];
			green_ant[j] = green_act[j];
			blue_ant[j] = blue_act[j];
			
		//imagen actual =  imagen siguiente
			red_act[j] = red;
			green_act[j] = green;
			blue_act[j] = blue;
		
		//se transforma a unsigned char los canales	
			wr_red[j] = (unsigned char) red_act[j];
			wr_green[j] = (unsigned char) green_act[j];
			wr_blue[j] = (unsigned char) blue_act[j];
		}
		//crea el string name deseado
		sprintf(name,"imagen_%d.bmp",100000+i);
		if (ami_write_bmp(name,wr_red,wr_green,wr_blue,width,height)){
			printf ("Error creando la Imagen: %s para la ecuacion de onda\n\n", name);
			return;
		}		
	}
	
	free(wr_red);
	free(wr_green);
	free(wr_blue);
	free(red_ant);
	free(green_ant);
	free(blue_ant);
	free(red_lap);
	free(green_lap);
	free(blue_lap);
		
	return;										 	
}

//Crea las imagenes para la ecuacion de ondas:
int aan_ecuacion_ondas(char *imagen, float dt, int Niter) {
	
	struct canales_float Canf1, Canf_out;
	
	if (!Leer_imagen(imagen,&Canf1.red,&Canf1.green,&Canf1.blue,&Canf1.width,&Canf1.height)){
			return 0;
	}
	
	aan_ecuacion_ondas_metodo_explicito(Canf1.red,Canf1.green,Canf1.blue,
									    Canf_out.red,Canf_out.green,Canf_out.blue,
									    Canf1.width,Canf1.height,dt,Niter);
	
	free(Canf1.red);
	free(Canf1.green);
	free(Canf1.blue);	
	
	return 1;
}
#endif /*PRACT8_AAN_H_*/
