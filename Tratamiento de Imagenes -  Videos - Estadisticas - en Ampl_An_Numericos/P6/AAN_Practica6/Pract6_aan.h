#ifndef PRACT6_AAN_H_
#define PRACT6_AAN_H_

#include "Pract1_aan.h"

//HISTOGRAMA:
void aan_histograma_canal (unsigned char *canal_input, int *histograma, int width, int height){
	int i;
	for (i=0; i<(width*height); i++){
		histograma[canal_input[i]]+=1;
	}
	return;
}
void aan_histograma_normalizar (int *histograma, float *Hist, int width, int height){
	int i;
	for (i=0; i<256; i++){
		Hist[i]= (float)histograma[i]/(float)(width*height);
	}
	return;
}

//funcion para leer los datos de una imagen:
int Leer_imagen(char *nombre, float **red, float **green, float **blue,
				 int *width, int *height, int *hist_r, int *hist_g, int *hist_b){
	
	struct canales Can1;
	printf("DATOS EXTERNOS:\n\n");
	if (ami_read_bmp(nombre,&Can1.red,&Can1.green,&Can1.blue,&Can1.width,&Can1.height)){
			printf ("Error abriendo la Imagen: %s\n\n", nombre);
			return 0;
	}
	
	aan_histograma_canal(Can1.red,hist_r,Can1.width,Can1.height);
	aan_histograma_canal(Can1.green,hist_g,Can1.width,Can1.height);
	aan_histograma_canal(Can1.blue,hist_b,Can1.width,Can1.height);
	
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

//ECUALIZADOR: 
void aan_ecualizar_histograma (float *h, float *e, int *f){
	
	int i;
	float acum_h = 0;
	float acum_e = e[0];
	int ind = 0;
	
	for (i=0; i<256; i++){
		acum_h+=h[i];
		f[i] = ind;
		while ((acum_h>=acum_e) && (ind<256)){
			ind++;
			acum_e+=e[ind];
		}
	}		 
	return;
}

void aan_ecualizar_histograma_canal (float *canal_input, float *canal_output, 
									 int width, int height, int *f){
	int i;
	for (i=0; i<(width*height); i++){
		canal_output[i] = f[(int)canal_input[i]];
	}
	return;
}

int aan_ecualizador(char *imagen, float *e){
	
	struct canales_float Canf1, Canf_out;
	
	int *hist_r;
	int *hist_g;
	int *hist_b;
	hist_r =(int*) calloc(256,sizeof(int));
	hist_g =(int*) calloc(256,sizeof(int));
	hist_b =(int*) calloc(256,sizeof(int));
	
	if (!Leer_imagen(imagen,&Canf1.red,&Canf1.green,&Canf1.blue,&Canf1.width,&Canf1.height,hist_r,hist_g,hist_b)){
			return 0;
	}
	
	float H_r[256];
	float H_g[256];
	float H_b[256];
	
	aan_histograma_normalizar(hist_r,H_r,Canf1.width,Canf1.height);
	aan_histograma_normalizar(hist_g,H_g,Canf1.width,Canf1.height);
	aan_histograma_normalizar(hist_b,H_b,Canf1.width,Canf1.height);
		
	free(hist_r);
	free(hist_g);
	free(hist_b);
	
	int f_r[256];
	int f_g[256];
	int f_b[256];
	
	aan_ecualizar_histograma(H_r,e,f_r);
	aan_ecualizar_histograma(H_g,e,f_g);
	aan_ecualizar_histograma(H_b,e,f_b);
	
	Canf_out.red =(float*) malloc((Canf1.width*Canf1.height)*sizeof(float));
	Canf_out.green =(float*) malloc((Canf1.width*Canf1.height)*sizeof(float));
	Canf_out.blue =(float*) malloc((Canf1.width*Canf1.height)*sizeof(float));
	
	Canf_out.width = Canf1.width;
	Canf_out.height = Canf1.height;
	
	if ((Canf_out.red==NULL) || (Canf_out.green==NULL) || (Canf_out.blue==NULL)){
		printf("Problemas con la memoria(memoria no disponible)/n");
		return 0;
	}
	
	aan_ecualizar_histograma_canal(Canf1.red,Canf_out.red,Canf_out.width,Canf_out.height,f_r);
	aan_ecualizar_histograma_canal(Canf1.green,Canf_out.green,Canf_out.width,Canf_out.height,f_g);
	aan_ecualizar_histograma_canal(Canf1.blue,Canf_out.blue,Canf_out.width,Canf_out.height,f_b);
	
	//Unir canales:
	struct canales_float Can_out;
	
	aan_unir_canales_float(Canf1.red,Canf_out.red,&Can_out.red,Canf_out.width,Canf_out.height);
	aan_unir_canales_float(Canf1.green,Canf_out.green,&Can_out.green,Canf_out.width,Canf_out.height);
	aan_unir_canales_float(Canf1.blue,Canf_out.blue,&Can_out.blue,Canf_out.width,Canf_out.height);
	Can_out.width = Canf_out.width*2+4;
	Can_out.height = Canf_out.height;
	
	//Necesario para la funcion ami write, hacer un cast de float a unsigned char
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
		
	if (ami_write_bmp("Imagen_Ecualizada.bmp",wr_red,wr_green,wr_blue,Can_out.width,Can_out.height)){
		printf ("Error creando la Imagen_Ecualizada");
	}
	
	free(Canf1.red);
	free(Canf1.green);
	free(Canf1.blue);
	free(Canf_out.red);
	free(Canf_out.green);
	free(Canf_out.blue);
	free(wr_red);
	free(wr_green);
	free(wr_blue);
	free(Can_out.red);
	free(Can_out.green);
	free(Can_out.blue);
	
	return 1;
}
	

#endif /*PRACT6_AAN_H_*/
