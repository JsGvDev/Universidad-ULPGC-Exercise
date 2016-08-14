#ifndef PRACT7_AAN_H_
#define PRACT7_AAN_H_

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

//PROPAGACION DE FRENTES:
void aan_ecuacion_propagacion_frentes(float *red_input, float *green_input, float *blue_input, 
									  float *red_output, float *green_output, float *blue_output, 
									  int width, int height, float dt, int Niter, float *F) {
	
	float *red_ux =(float*) malloc((width*height)*sizeof(float));
	float *red_uy =(float*) malloc((width*height)*sizeof(float));
	float grad;
	int i,j;
	
	//Necesario para la funcion ami write, hacer un cast de float a unsigned char *
	char name[200];
	unsigned char *wr_red;
	unsigned char *wr_green;
	unsigned char *wr_blue;
	wr_red =(unsigned char*) malloc((width*height)*sizeof(unsigned char));
	wr_green =(unsigned char*) malloc((width*height)*sizeof(unsigned char));
	wr_blue =(unsigned char*) malloc((width*height)*sizeof(unsigned char));
	
	
	for(i=0; i<Niter; i++){
		
		aan_mascara_canal(red_input,red_ux,width,height,mfx);
		aan_mascara_canal(red_input,red_uy,width,height,mfy);
		for (j=0; j<(width*height); j++){
			
			grad = sqrt((red_ux[j]*red_ux[j])+(red_uy[j]*red_uy[j]));
			red_input[j] = red_input[j] + F[j]*dt*grad;
			if (red_input[j]> 255){
				red_input[j] = 255;
			}
			red_output[j] = red_input[j];
			green_output[j] = green_input[j];  
			blue_output[j] = blue_input[j];
			
			//se transforma a unsigned char los canales	
			wr_red[j] = (unsigned char) red_output[j];
			wr_green[j] = (unsigned char) green_output[j];
			wr_blue[j] = (unsigned char) blue_output[j];
		}
		
		//crea el string name deseado
		sprintf(name,"imagen_%d.bmp",100000+i);
		if (ami_write_bmp(name,wr_red,wr_green,wr_blue,width,height)){
			printf ("Error creando la Imagen: %s para la propagacion de frentes\n\n", name);
			return;
		}
	}
	
	free(red_ux);
	free(red_uy);
	free(wr_red);
	free(wr_green);
	free(wr_blue);
	free(red_output);
	free(green_output);
	free(blue_output);
	
	return;
}
//Crea las imagenes para la propagacion de frentes
//canal rojo --> frente (du = F*dt*grad)
//canal verde --> velocidad (F)
int aan_propagacion_frentes(char *imagen, float dt, int Niter, float k, float M, int op) {
	
	struct canales_float Canf1, Canf_out;
	
	if (!Leer_imagen(imagen,&Canf1.red,&Canf1.green,&Canf1.blue,&Canf1.width,&Canf1.height)){
			return 0;
	}
	
	Canf_out.red =(float*) malloc((Canf1.width*Canf1.height)*sizeof(float));
	Canf_out.green =(float*) malloc((Canf1.width*Canf1.height)*sizeof(float));
	Canf_out.blue =(float*) malloc((Canf1.width*Canf1.height)*sizeof(float));
	
	Canf_out.width = Canf1.width;
	Canf_out.height = Canf1.height;
	
	if ((Canf_out.red==NULL) || (Canf_out.green==NULL) || (Canf_out.blue==NULL)){
		printf("Problemas con la memoria(memoria no disponible)/n");
		return 0;
	}
	float F[Canf1.width*Canf1.height];
	int i;
	
	float *green_ux =(float*) malloc((Canf1.width*Canf1.height)*sizeof(float));
	float *green_uy =(float*) malloc((Canf1.width*Canf1.height)*sizeof(float));
	float V;
	
	if (op == 1){ //opcion1: velocidad inversa a la magnitud de un canal.
		for (i=0; i<(Canf1.width*Canf1.height); i++){
			F[i] = k*(255 - Canf1.green[i])/255;
		}
	} else { //opcion2: velocidad inversa a la magnitud del gradiente.
		aan_mascara_canal(Canf1.green,green_ux,Canf1.width,Canf1.height,mfx);
		aan_mascara_canal(Canf1.green,green_uy,Canf1.width,Canf1.height,mfy);
		for (i=0; i<(Canf1.width*Canf1.height); i++){
			V = sqrt((green_ux[i]*green_ux[i])+(green_uy[i]*green_uy[i]));
			V = V/M;		
			if (1 < V){
				V = 1;
			}
			F[i] = k*(1-V);
		}
	}
	
	free(green_ux);
	free(green_uy);
	
	aan_ecuacion_propagacion_frentes(Canf1.red,Canf1.green,Canf1.blue,
									 Canf_out.red,Canf_out.green,Canf_out.blue,
									 Canf1.width,Canf1.height,dt,Niter,F);
	
	free(Canf1.red);
	free(Canf1.green);
	free(Canf1.blue);	
	
	return 1;
}
#endif /*PRACT7_AAN_H_*/
