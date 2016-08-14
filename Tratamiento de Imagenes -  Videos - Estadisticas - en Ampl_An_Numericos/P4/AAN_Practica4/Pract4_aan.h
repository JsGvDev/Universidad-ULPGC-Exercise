#ifndef PRACT4_AAN_H_
#define PRACT4_AAN_H_

#include "Pract2_aan.h"

void aan_ecuacion_calor_metodo_explicito(float *red_input, float *green_input, float*blue_input, 
										 float *red_output, float *green_output, float *blue_output,
										 int width, int height, float dt, int Niter){
	
	red_output =(float*) malloc((width*height)*sizeof(float));
	green_output =(float*) malloc((width*height)*sizeof(float));
	blue_output =(float*) malloc((width*height)*sizeof(float));
	
	if ((red_output==NULL) || (green_output==NULL) || (blue_output==NULL)){
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
	
	for(i=0; i<Niter; i++){
		aan_mascara_imagen(red_input,green_input,blue_input,red_output,green_output,blue_output,width,height,m_lap);
		for(j=0; j<(width*height); j++){
			red_input[j] = red_input[j] + (dt*red_output[j]);
			green_input[j] = green_input[j] + (dt*green_output[j]);
			blue_input[j] = blue_input[j] + (dt*blue_output[j]);
		//se transforma a unsigned char los canales	
			wr_red[j] = (unsigned char) red_input[j];
			wr_green[j] = (unsigned char) green_input[j];
			wr_blue[j] = (unsigned char) blue_input[j];
		}
	//crea el string name deseado
		sprintf(name,"imagen_%d.bmp",100000+i);
		if (ami_write_bmp(name,wr_red,wr_green,wr_blue,width,height)){
			printf ("Error creando la Imagen: %s para la ecuacion del calor\n\n", name);
			return;
		}
	}
	free(wr_red);
	free(wr_green);
	free(wr_blue);
	free(red_output);
	free(green_output);
	free(blue_output);
	
	return;
}

#endif /*PRACT4_AAN_H_*/
