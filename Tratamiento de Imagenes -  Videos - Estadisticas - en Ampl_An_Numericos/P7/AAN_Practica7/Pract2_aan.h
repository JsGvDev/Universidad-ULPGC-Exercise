#ifndef PRACT2_AAN_H_
#define PRACT2_AAN_H_

#include <math.h>
#include "Pract1_aan.h"

//Definimos las distintas mascaras:
#define exp1 ((float)(2-sqrt(2))/4)
#define exp2 ((float)(2*(sqrt(2)-1))/4)
	//Para la Derivada horizontal
	float mfx[3][3] = {{-exp1,0,exp1},{-exp2,0,exp2},{-exp1,0,exp1}};
	//Para la Derivada vertical
	float mfy[3][3] = {{-exp1,-exp2,-exp1},{0,0,0},{exp1,exp2,exp1}};
	//Para el laplacianod
	float m_lap[3][3] = {{1./3,1./3,1./3},{1./3,-8./3,1./3},{1./3,1./3,1./3}};

//Aplicacion de una mascara a un canal:
void aan_mascara_canal(float *canal_input, float *canal_output, int width, int height,
					   float m[3][3]){
	int i,j;
	int aux;
	
	//Calculo de la mascara en un canal:
	for (i=0; i<height; i++){
		for (j=0; j<width; j++){
			aux = 0;
			//Calculo de la mascara en las 4 esquinas:
				//Izq_Sup:			
			if ((i==0)&&(j==0)){
				aux+= canal_input[0]*(m[0][0]+ m[0][1]+ m[1][0]+ m[1][1]);
				aux+= canal_input[1]*(m[0][2]+ m[1][2]);
				aux+= canal_input[width]*(m[2][0]+ m[2][1]);
				aux+= canal_input[width+1]* m[2][2];
			}
				//Dch_Sup:
			if ((i==0)&&(j==width-1)){
				aux+= canal_input[width-1]*(m[0][1]+ m[0][2]+ m[1][1]+ m[1][2]);
				aux+= canal_input[width-2]*(m[0][0]+ m[1][0]);
				aux+= canal_input[2*width-1]*(m[2][1]+ m[2][2]);
				aux+= canal_input[2*width-2]* m[2][0];
			}
				//Izq_Inf:
			if ((i==height-1)&&(j==0)){
				aux+= canal_input[(height-1)*width]*(m[1][0]+ m[1][1]+ m[2][0]+ m[2][1]);
				aux+= canal_input[(height-2)*width]*(m[0][0]+ m[0][1]);
				aux+= canal_input[(height-1)*width+1]*(m[1][2]+ m[2][2]);
				aux+= canal_input[(height-2)*width+1]* m[0][2];				
			}
				//Dch_Inf:
			if ((i==height-1)&&(j==height*width-1)){
				aux+= canal_input[width*height-1]*(m[1][1]+ m[1][2]+ m[2][1]+ m[2][2]);
				aux+= canal_input[(height-1)*width-1]*(m[0][1]+ m[0][2]);
				aux+= canal_input[width*height-2]*(m[1][0]+ m[2][0]);
				aux+= canal_input[(height-1)*width-2]* m[0][0];				
			}
			//Calculo de la mascara en el interior:
			if ((i>0)&&(j>0)&&(i<height-1)&&(j<width-1)){
				aux+= m[0][0]*canal_input[(i-1)*width+(j-1)];
				aux+= m[0][1]*canal_input[(i-1)*width+j];
				aux+= m[0][2]*canal_input[(i-1)*width+(j+1)];
				aux+= m[1][0]*canal_input[i*width+(j-1)];
				aux+= m[1][1]*canal_input[i*width+j];
				aux+= m[1][2]*canal_input[i*width+(j+1)];
				aux+= m[2][0]*canal_input[(i+1)*width+(j-1)];
				aux+= m[2][1]*canal_input[(i+1)*width+j];
				aux+= m[2][2]*canal_input[(i+1)*width+(j+1)];
			}
			//Calculo de la mascara en los 4 bordes:
				//Izquierdo:			
			if (j==0){
				if ((i>0)&&(i<height-1)){
					aux+= canal_input[(i-1)*width]*(m[0][0]+ m[0][1]);
					aux+= canal_input[i*width]*(m[1][0]+ m[1][1]);
					aux+= canal_input[(i+1)*width]*(m[2][0]+ m[2][1]);
					aux+= canal_input[(i-1)*width+1]* m[0][2];
					aux+= canal_input[i*width+1]* m[1][2];
					aux+= canal_input[(i+1)*width+1]* m[2][2];
				}
			}
				//Derecho:
			if (j==width-1){
				if ((i>0)&&(i<height-1)){
					aux+= canal_input[i*width-1]*(m[0][1]+ m[0][2]);
					aux+= canal_input[(i*width)+width-1]*(m[1][1]+ m[1][2]);
					aux+= canal_input[((i+1)*width)+width-1]*(m[2][1]+ m[2][2]);
					aux+= canal_input[i*width-2]* m[0][0];
					aux+= canal_input[(i*width)+width-2]* m[1][0];
					aux+= canal_input[((i+1)*width)+width-2]* m[2][0];
				}
			}
				//Arriba:
			if (i==0){
				if ((j>0)&&(j<width-1)){
					aux+= canal_input[j-1]*(m[0][0]+ m[1][0]);
					aux+= canal_input[j]*(m[0][1]+ m[1][1]);
					aux+= canal_input[j+1]*(m[0][2]+ m[1][2]);
					aux+= canal_input[(j-1)+width]* m[2][0];
					aux+= canal_input[j+width]* m[2][1];
					aux+= canal_input[(j+1)+width]* m[2][2];
				}
			}
				//Abajo:
			if (i==height-1){
				if ((j>0)&&(j<width-1)){
					aux+= canal_input[(height-1)*width+j-1]*(m[1][0]+ m[2][0]);
					aux+= canal_input[(height-1)*width+j]*(m[1][1]+ m[2][1]);
					aux+= canal_input[(height-1)*width+j+1]*(m[1][2]+ m[2][2]);
					aux+= canal_input[(height-2)*width+j-1]* m[0][0];
					aux+= canal_input[(height-2)*width+j]* m[0][1];
					aux+= canal_input[(height-2)*width+j+1]* m[0][2];
				}
			}
			canal_output[i*(width) + j] = aux;
		}
	}
	return;
}

//Aplicacion de una mascara a una imagen:
void aan_mascara_imagen( float *red_input, float *green_input, float *blue_input,
						 float *red_output, float *green_output, float *blue_output,
						 int width, int height, float m[3][3]){
	aan_mascara_canal(red_input,red_output,width,height,m);
	aan_mascara_canal(green_input,green_output,width,height,m);
	aan_mascara_canal(blue_input,blue_output,width,height,m);
	return;
}

//Procedimiento para montar las imagenes de una mascara:
void montar_imagen(float *red_input,float *green_input,float *blue_input,int width, int height,
				   float *red_out,float *green_out,float *blue_out, char *nombre){

	struct canales_float Can_out;
	
	aan_normalizar_canal_float(red_out,red_out,width,height);
	aan_normalizar_canal_float(green_out,green_out,width,height);
	aan_normalizar_canal_float(blue_out,blue_out,width,height);
	
	aan_unir_canales_float(red_input,red_out,&Can_out.red,width,height);
	aan_unir_canales_float(green_input,green_out,&Can_out.green,width,height);
	aan_unir_canales_float(blue_input,blue_out,&Can_out.blue,width,height);
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
		
	if (ami_write_bmp(nombre,wr_red,wr_green,wr_blue,Can_out.width,Can_out.height)){
		printf ("Error creando la Imagen: %s para una mascara\n\n", nombre);
	}
		
	free(wr_red);
	free(wr_green);
	free(wr_blue);
	free(Can_out.red);
	free(Can_out.green);
	free(Can_out.blue);
}

//Crear imagenes con mascara:
void aan_mascara (float *red_input, float *green_input, float *blue_input,
				  int width, int height){
	
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
	
	aan_mascara_imagen(red_input,green_input,blue_input,red_out,green_out,blue_out,width,height,mfx);
	montar_imagen(red_input,green_input,blue_input,width,height,red_out,green_out,blue_out,"Derivada_Horizontal.bmp");
	
	aan_mascara_imagen(red_input,green_input,blue_input,red_out,green_out,blue_out,width,height,mfy);
	montar_imagen(red_input,green_input,blue_input,width,height,red_out,green_out,blue_out,"Derivada_Vertical.bmp");
	
	aan_mascara_imagen(red_input,green_input,blue_input,red_out,green_out,blue_out,width,height,m_lap);
	montar_imagen(red_input,green_input,blue_input,width,height,red_out,green_out,blue_out,"Laplaciano.bmp");
	
	free(red_out);
	free(green_out);
	free(blue_out);
			
	return;
}

//Mascaras Combinadas fx y fy:
void aan_mascara_combinada(float *red_input, float *green_input, float *blue_input,
				  		   int width, int height){
	float *red_ux;
	float *green_ux;
	float *blue_ux;
	float *red_uy;
	float *green_uy;
	float *blue_uy;
	float *red_out;
	float *green_out;
	float *blue_out;
	
	red_ux =(float*) malloc((width*height)*sizeof(float));
	green_ux =(float*) malloc((width*height)*sizeof(float));
	blue_ux =(float*) malloc((width*height)*sizeof(float));
	red_uy =(float*) malloc((width*height)*sizeof(float));
	green_uy =(float*) malloc((width*height)*sizeof(float));
	blue_uy =(float*) malloc((width*height)*sizeof(float));
	red_out =(float*) malloc((width*height)*sizeof(float));
	green_out =(float*) malloc((width*height)*sizeof(float));
	blue_out =(float*) malloc((width*height)*sizeof(float));
	
	if ((red_out==NULL) || (green_out==NULL) || (blue_out==NULL)){
		printf("Problemas con la memoria(memoria no disponible)/n");
		return;
	}
	
	aan_mascara_imagen(red_input,green_input,blue_input,red_ux,green_ux,blue_ux,width,height,mfx);
	aan_mascara_imagen(red_input,green_input,blue_input,red_uy,green_uy,blue_uy,width,height,mfy);
	
	int i;
	for(i=0; i<(width*height); i++){
		red_out[i] = sqrt((red_ux[i]*red_ux[i])+(red_uy[i]*red_uy[i]));
		green_out[i] = sqrt((green_ux[i]*green_ux[i])+(green_uy[i]*green_uy[i]));
		blue_out[i] = sqrt((blue_ux[i]*blue_ux[i])+(blue_uy[i]*blue_uy[i]));
	}
	
	montar_imagen(red_input,green_input,blue_input,width,height,red_out,green_out,blue_out,"Mascara_Combinada.bmp");
	
	free(red_ux);
	free(green_ux);
	free(blue_ux);
	free(red_uy);
	free(green_uy);
	free(blue_uy);
	free(red_out);
	free(green_out);
	free(blue_out);
			
	return;
}


//Prueba para imagenes blanco negro:
void aan_mascara_prueba_negblanc(float *red_input, float *green_input, float *blue_input,
				  				 int width, int height){
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
	
	aan_mascara_canal(red_input,red_out,width,height,mfy);
	aan_mascara_canal(green_input,green_out,width,height,mfx);
	
	int i;
	for(i=0; i<(width*height); i++){
		blue_out[i] = 128;
	}
	
	montar_imagen(red_input,green_input,blue_input,width,height,red_out,green_out,blue_out,"Mascara_prueba_negblanc.bmp");
	
	free(red_out);
	free(green_out);
	free(blue_out);
			
	return;
}

#endif /*PRACT2_AAN_H_*/
