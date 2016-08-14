#ifndef PRACT1_AAN_H_
#define PRACT1_AAN_H_

#include "ami_bmp.h"
#include "ami.h"

struct canales {
	unsigned char *red;
	unsigned char *green;
	unsigned char *blue;
	int width,height;
};
struct canales_float {
	float *red;
	float *green;
	float *blue;
	int width,height;
};

//UNIR CANALES:
void aan_unir_canales_unsigned_char(unsigned char *canal1, unsigned char *canal2,
									unsigned char **canal_output, int width, int height){
	int width2 = width*2 + 4;
	int tam = width2*height;
	int i,j,k;
	
	*canal_output=(unsigned char*) malloc(tam*sizeof(unsigned char));
	if (*canal_output==NULL){
		printf("Problemas con la memoria(memoria no disponible)/n");
		return;
	}
	
	for (i=0; i<height; i++){
		for (j=0; j<width; j++){
			(*canal_output)[i*(width2) + j] = canal1[i*(width) + j];
			(*canal_output)[i*(width2) + width + 4 + j] = canal2 [i*(width) + j];			
		}
		for (k=0; k<4; k++){
			(*canal_output)[i*(width2) + width + k] = 0;
		}
	}
	
	return;	 
}

void aan_unir_canales_float(float *canal1, float *canal2, 
							float **canal_output, int width, int height){
	int width2 = width*2 + 4;
	int tam = width2*height;
	int i,j,k;
	
	*canal_output=(float*) malloc(tam*sizeof(float));
	if (*canal_output==NULL){
		printf("Problemas con la memoria(memoria no disponible)/n");
		return;
	}
	
	for (i=0; i<height; i++){
		for (j=0; j<width; j++){
			(*canal_output)[i*(width2) + j] = canal1[i*(width) + j];
			(*canal_output)[i*(width2) + width + 4 + j] = canal2 [i*(width) + j];			
		}
		for (k=0; k<4; k++){
			(*canal_output)[i*(width2) + width + k] = 0;
		}
	}
	
	return;		 
}
//FIN UNIR CANALES.

//NORMALIZAR CANALES:
void aan_normalizar_canal_unsigned_char(unsigned char *canal_input, 
										unsigned char *canal_output, int width, int height){
	int pos_max,max,pos_min,min,i;
	ami_max_vector(canal_input,pos_max,max,(width*height));
	ami_min_vector(canal_input,pos_min,min,(width*height));
	if (max!=min){
		for (i=0; i<(width*height); i++){
			canal_output[i]=255*(canal_input[i]-min)/(max-min);
		}
	}	
	return;
}

void aan_normalizar_canal_float(float *canal_input,	float *canal_output, int width, int height){
	
	int pos_max,max,pos_min,min,i;
	ami_max_vector(canal_input,pos_max,max,(width*height));
	ami_min_vector(canal_input,pos_min,min,(width*height));
	if (max!=min){
		for (i=0; i<(width*height); i++){
			canal_output[i]=255*(canal_input[i]-min)/(max-min);
		}
	}
	return;
}

void aan_normalizar_imagen_unsigned_char(unsigned char *red, unsigned char *green, 
										 unsigned char *blue, int width, int height){
	struct canales Can_out;
	unsigned char *red_out;
	unsigned char *green_out;
	unsigned char *blue_out;
	
	red_out =(unsigned char*) malloc((width*height)*sizeof(unsigned char));
	green_out =(unsigned char*) malloc((width*height)*sizeof(unsigned char));
	blue_out =(unsigned char*) malloc((width*height)*sizeof(unsigned char));
	
	if ((red_out==NULL) || (green_out==NULL) || (blue_out==NULL)){
		printf("Problemas con la memoria(memoria no disponible)/n");
		return;
	}
	
	aan_normalizar_canal_unsigned_char(red,red_out,width,height);
	aan_normalizar_canal_unsigned_char(green,green_out,width,height);
	aan_normalizar_canal_unsigned_char(blue,blue_out,width,height);
	
	aan_unir_canales_unsigned_char(red,red_out,&Can_out.red,width,height);
	aan_unir_canales_unsigned_char(green,green_out,&Can_out.green,width,height);
	aan_unir_canales_unsigned_char(blue,blue_out,&Can_out.blue,width,height);
	Can_out.width = width*2+4;
	Can_out.height = height;
	
	if (ami_write_bmp("Imagen_Normalizda.bmp",Can_out.red,Can_out.green,Can_out.blue,Can_out.width,Can_out.height)){
		printf ("Error creando la Imagen_Normalizada");
	}
	
	free(red_out);
	free(green_out);
	free(blue_out);
	free(Can_out.red);
	free(Can_out.green);
	free(Can_out.blue);
	
	return;
}

void aan_normalizar_imagen_float(float *red, float *green, float *blue, int width, int height){
	
	struct canales_float Can_out;
	float *red_out;
	float *green_out;
	float *blue_out;
	
	red_out =(float*) malloc((width*height)*sizeof(float));
	green_out =(float*) malloc((width*height)*sizeof(float));
	blue_out =(float*) malloc((width*height)*sizeof(float));
	
	if ((red_out==NULL) || (green_out==NULL) || (blue_out==NULL)){
		printf("Problemas con la memoria(memoria no disponible)/n");
		return;
	}
	
	aan_normalizar_canal_float(red,red_out,width,height);
	aan_normalizar_canal_float(green,green_out,width,height);
	aan_normalizar_canal_float(blue,blue_out,width,height);
	
	aan_unir_canales_float(red,red_out,&Can_out.red,width,height);
	aan_unir_canales_float(green,green_out,&Can_out.green,width,height);
	aan_unir_canales_float(blue,blue_out,&Can_out.blue,width,height);
	Can_out.width = width*2+4;
	Can_out.height = height;
	
	//Necesario para la funcion ami write, hacer un cast de float a unsigned char *
	unsigned char *wr_red;
	unsigned char *wr_green;
	unsigned char *wr_blue;
	
	wr_red =(unsigned char*) malloc((Can_out.width*Can_out.height)*sizeof(unsigned char));
	wr_green =(unsigned char*) malloc((Can_out.width*Can_out.height)*sizeof(unsigned char));
	wr_blue =(unsigned char*) malloc((Can_out.width*Can_out.height)*sizeof(unsigned char));
	
	int i;
	for (i=0; i<(Can_out.width*Can_out.height); i++){
		wr_red[i] = (unsigned char) Can_out.red[i];
		wr_green[i] = (unsigned char) Can_out.green[i];
		wr_blue[i] = (unsigned char) Can_out.blue[i];
	}
		
	if (ami_write_bmp("Imagen_Normalizada_Float.bmp",wr_red,wr_green,wr_blue,Can_out.width,Can_out.height)){
		printf ("Error creando la Imagen_Normalizada_Float");
	}
	
	free(red_out);
	free(green_out);
	free(blue_out);
	free(wr_red);
	free(wr_green);
	free(wr_blue);
	free(Can_out.red);
	free(Can_out.green);
	free(Can_out.blue);
	
	return;
}
//FIN NORMALIZAR CANALES.

//EXTRAER CANALES HSV:
void aan_extraer_canales_HSV(unsigned char *red, unsigned char *green, 
							 unsigned char *blue, int width, int height){
	
	struct canales Can_out;
	unsigned char *H;
	unsigned char *S;
	unsigned char *V;
	
	H =(unsigned char*) malloc((width*height)*sizeof(unsigned char));
	S =(unsigned char*) malloc((width*height)*sizeof(unsigned char));
	V =(unsigned char*) malloc((width*height)*sizeof(unsigned char));
	
	if ((H==NULL) || (S==NULL) || (V==NULL)){
		printf("Problemas con la memoria(memoria no disponible)/n");
		return;
	}
	
	int max,min,i;
	
	for (i=0; i<(width*height); i++){
		//Tono:
		//Minimo de RGB:
		if (red[i] < green[i]){
			if (red[i] < blue[i]){
				min = red[i];
			} else {
				min = blue[i];
			}
		} else {
			if (green[i] < blue[i]){
				min = green[i];
			} else {
				min = blue[i];
			}
		}
		//Maximo de RGB:
		if (red[i] > green[i]){
			if (red[i] > blue[i]){
				max = red[i];
				if(max==min){
					H[i] = 0;
				} else {
					H[i] = (43*(green[i]-blue[i])/(max-min))%256;
				}
			} else {
				max = blue[i];
				if(max==min){
					H[i] = 0;
				} else {
					H[i] = (43*(red[i]-green[i])/(max-min)) + 170;
				}
			}
		} else {
			if (green[i] > blue[i]){
				max = green[i];
				if(max==min){
					H[i] = 0;
				} else {
					H[i] = (43*(blue[i]-red[i])/(max-min)) + 85;
				}
			} else {
				max = blue[i];
				if(max==min){
					H[i] = 0;
				} else {
					H[i] = (43*(red[i]-green[i])/(max-min)) + 170;
				}
			}
		}
		//Valor/Brillo:
		V[i] = max;
		//Saturacion:
		if (max == 0){
			S[i] = 0;
		} else {
			S[i] = max-min;
		}
	}
	//Creamos las imagenes H,S,V con la original:
	//H:
	aan_unir_canales_unsigned_char(red,H,&Can_out.red,width,height);
	aan_unir_canales_unsigned_char(green,H,&Can_out.green,width,height);
	aan_unir_canales_unsigned_char(blue,H,&Can_out.blue,width,height);
	Can_out.width = width*2+4;
	Can_out.height = height;
	
	if (ami_write_bmp("Imagen_H_tono.bmp",Can_out.red,Can_out.green,Can_out.blue,Can_out.width,Can_out.height)){
		printf ("Error creando la Imagen H(Tono)");
	}
	//S:
	aan_unir_canales_unsigned_char(red,S,&Can_out.red,width,height);
	aan_unir_canales_unsigned_char(green,S,&Can_out.green,width,height);
	aan_unir_canales_unsigned_char(blue,S,&Can_out.blue,width,height);
	Can_out.width = width*2+4;
	Can_out.height = height;
	
	if (ami_write_bmp("Imagen_S_saturacion.bmp",Can_out.red,Can_out.green,Can_out.blue,Can_out.width,Can_out.height)){
		printf ("Error creando la Imagen S(Saturacion)");
	}
	
	//V:
	aan_unir_canales_unsigned_char(red,V,&Can_out.red,width,height);
	aan_unir_canales_unsigned_char(green,V,&Can_out.green,width,height);
	aan_unir_canales_unsigned_char(blue,V,&Can_out.blue,width,height);
	Can_out.width = width*2+4;
	Can_out.height = height;
	
	if (ami_write_bmp("Imagen_V_brillo.bmp",Can_out.red,Can_out.green,Can_out.blue,Can_out.width,Can_out.height)){
		printf ("Error creando la Imagen V(Brillo)");
	}
	
	free(H);
	free(S);
	free(V);
	free(Can_out.red);
	free(Can_out.green);
	free(Can_out.blue);
	
	return;		
}
//FIN EXTRAER CANALES HSV.
#endif /*PRACT1_AAN_H_*/
