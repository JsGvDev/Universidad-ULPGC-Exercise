#ifndef PRACT9_AAN_H_
#define PRACT9_AAN_H_

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

//Aplicacion de una mascara a un canal de perona-malik:
void aan_mascara_canal_P_M(float *canal_input, float *canal_output, int width, int height,
					   	   float *k, float dt){
	int i,j;
	float aux;
	float m[3][3];
	m[0][0] = 0;
	m[0][2] = 0;
	m[2][0] = 0;
	m[2][2] = 0;
	//i*(width) + j
	//Calculo de la mascara en un canal:
	for (i=0; i<height; i++){
		for (j=0; j<width; j++){
			aux = 0;
			//Calculo de la mascara en las 4 esquinas:
				//Izq_Sup:			
			if ((i==0)&&(j==0)){
				m[0][1] = k[i*(width) + j]+k[i*(width) + (j+1)];
				m[1][0] = 2*k[i*(width) + j];
				m[1][1] = -k[(i+1)*(width) + j]-k[i*(width) + j]-4*k[i*(width) + j]-k[i*(width) + (j+1)]-k[i*(width) + j];
				m[1][2] = k[i*(width) + j]+k[(i+1)*(width) + j];
				m[2][1] = 2*k[i*(width) + j];
				aux+= canal_input[0]*(m[0][0]+ m[0][1]+ m[1][0]+ m[1][1]);
				aux+= canal_input[1]*(m[0][2]+ m[1][2]);
				aux+= canal_input[width]*(m[2][0]+ m[2][1]);
				aux+= canal_input[width+1]* m[2][2];
			}
				//Dch_Sup:
			if ((i==0)&&(j==width-1)){
				m[0][1] = 2*k[i*(width) + j];
				m[1][0] = 2*k[i*(width) + j];
				m[1][1] = -k[(i+1)*(width) + j]-k[i*(width) + j]-4*k[i*(width) + j]-k[i*(width) + j]-k[i*(width) + (j-1)];
				m[1][2] = k[i*(width) + j]+k[(i+1)*(width) + j];
				m[2][1] = k[i*(width) + j]+k[i*(width) + (j-1)];
				aux+= canal_input[width-1]*(m[0][1]+ m[0][2]+ m[1][1]+ m[1][2]);
				aux+= canal_input[width-2]*(m[0][0]+ m[1][0]);
				aux+= canal_input[2*width-1]*(m[2][1]+ m[2][2]);
				aux+= canal_input[2*width-2]* m[2][0];
			}
				//Izq_Inf:
			if ((i==height-1)&&(j==0)){
				m[0][1] = k[i*(width) + j]+k[i*(width) + (j+1)];
				m[1][0] = k[i*(width) + j]+k[(i-1)*(width) + j];
				m[1][1] = -k[i*(width) + j]-k[(i-1)*(width) + j]-4*k[i*(width) + j]-k[i*(width) + (j+1)]-k[i*(width) + j];
				m[1][2] = 2*k[i*(width) + j];
				m[2][1] = 2*k[i*(width) + j];
				aux+= canal_input[(height-1)*width]*(m[1][0]+ m[1][1]+ m[2][0]+ m[2][1]);
				aux+= canal_input[(height-2)*width]*(m[0][0]+ m[0][1]);
				aux+= canal_input[(height-1)*width+1]*(m[1][2]+ m[2][2]);
				aux+= canal_input[(height-2)*width+1]* m[0][2];				
			}
				//Dch_Inf:
			if ((i==height-1)&&(j==height*width-1)){
				m[0][1] = 2*k[i*(width) + j];
				m[1][0] = k[i*(width) + j]+k[(i-1)*(width) + j];
				m[1][1] = -k[i*(width) + j]-k[(i-1)*(width) + j]-4*k[i*(width) + j]-k[i*(width) + j]-k[i*(width) + (j-1)];
				m[1][2] = 2*k[i*(width) + j];
				m[2][1] = k[i*(width) + j]+k[i*(width) + (j-1)];
				aux+= canal_input[width*height-1]*(m[1][1]+ m[1][2]+ m[2][1]+ m[2][2]);
				aux+= canal_input[(height-1)*width-1]*(m[0][1]+ m[0][2]);
				aux+= canal_input[width*height-2]*(m[1][0]+ m[2][0]);
				aux+= canal_input[(height-1)*width-2]* m[0][0];				
			}
			//Calculo de la mascara en el interior:
			if ((i>0)&&(j>0)&&(i<height-1)&&(j<width-1)){
				m[0][1] = k[i*(width) + j]+k[i*(width) + (j+1)];
				m[1][0] = k[i*(width) + j]+k[(i-1)*(width) + j];
				m[1][1] = -k[(i+1)*(width) + j]-k[(i-1)*(width) + j]-4*k[i*(width) + j]-k[i*(width) + (j+1)]-k[i*(width) + (j-1)];
				m[1][2] = k[i*(width) + j]+k[(i+1)*(width) + j];
				m[2][1] = k[i*(width) + j]+k[i*(width) + (j-1)];
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
					m[0][1] = k[i*(width) + j]+k[i*(width) + (j+1)];
					m[1][0] = k[i*(width) + j]+k[(i-1)*(width) + j];
					m[1][1] = -k[(i+1)*(width) + j]-k[(i-1)*(width) + j]-4*k[i*(width) + j]-k[i*(width) + (j+1)]-k[i*(width) + j];
					m[1][2] = k[i*(width) + j]+k[(i+1)*(width) + j];
					m[2][1] = 2*k[i*(width) + j];
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
					m[0][1] = 2*k[i*(width) + j];
					m[1][0] = k[i*(width) + j]+k[(i-1)*(width) + j];
					m[1][1] = -k[(i+1)*(width) + j]-k[(i-1)*(width) + j]-4*k[i*(width) + j]-k[i*(width) + j]-k[i*(width) + (j-1)];
					m[1][2] = k[i*(width) + j]+k[(i+1)*(width) + j];
					m[2][1] = k[i*(width) + j]+k[i*(width) + (j-1)];
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
					m[0][1] = k[i*(width) + j]+k[i*(width) + (j+1)];
					m[1][0] = 2*k[i*(width) + j];
					m[1][1] = -k[(i+1)*(width) + j]-k[i*(width) + j]-4*k[i*(width) + j]-k[i*(width) + (j+1)]-k[i*(width) + (j-1)];
					m[1][2] = k[i*(width) + j]+k[(i+1)*(width) + j];
					m[2][1] = k[i*(width) + j]+k[i*(width) + (j-1)];
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
					m[0][1] = k[i*(width) + j]+k[i*(width) + (j+1)];
					m[1][0] = k[i*(width) + j]+k[(i-1)*(width) + j];
					m[1][1] = -k[i*(width) + j]-k[(i-1)*(width) + j]-4*k[i*(width) + j]-k[i*(width) + (j+1)]-k[i*(width) + (j-1)];
					m[1][2] = 2*k[i*(width) + j];
					m[2][1] = k[i*(width) + j]+k[i*(width) + (j-1)];
					aux+= canal_input[(height-1)*width+j-1]*(m[1][0]+ m[2][0]);
					aux+= canal_input[(height-1)*width+j]*(m[1][1]+ m[2][1]);
					aux+= canal_input[(height-1)*width+j+1]*(m[1][2]+ m[2][2]);
					aux+= canal_input[(height-2)*width+j-1]* m[0][0];
					aux+= canal_input[(height-2)*width+j]* m[0][1];
					aux+= canal_input[(height-2)*width+j+1]* m[0][2];
				}
			}
			canal_output[i*(width) + j] = canal_input[i*(width) + j]+((dt/2.0)*aux);
		}
	}
	return;
}

//ECUACION DE PERONA-MALIK:
void aan_ecuacion_perona_malik(float *red_input, float *green_input, float *blue_input, 
							   int width, int height, float dt, int Niter, float lamb){
	
	float *red_output =(float*) malloc((width*height)*sizeof(float));
	float *green_output =(float*) malloc((width*height)*sizeof(float));
	float *blue_output =(float*) malloc((width*height)*sizeof(float));
	
	if ((red_output==NULL) || (green_output==NULL) || (blue_output==NULL)){
		printf("Problemas con la memoria(memoria no disponible)/n");
		return;
	}	
	//Gradiente
	float *red_ux =(float*) malloc((width*height)*sizeof(float));
	float *red_uy =(float*) malloc((width*height)*sizeof(float));
	float *green_ux =(float*) malloc((width*height)*sizeof(float));
	float *green_uy =(float*) malloc((width*height)*sizeof(float));
	float *blue_ux =(float*) malloc((width*height)*sizeof(float));
	float *blue_uy =(float*) malloc((width*height)*sizeof(float));
	
	if ((red_ux==NULL) || (green_ux==NULL) || (blue_ux==NULL)){
		printf("Problemas con la memoria(memoria no disponible)/n");
		return;
	}
	if ((red_uy==NULL) || (green_uy==NULL) || (blue_uy==NULL)){
		printf("Problemas con la memoria(memoria no disponible)/n");
		return;
	}
	//Ki,j
	float *k_red =(float*) malloc((width*height)*sizeof(float));
	float *k_green =(float*) malloc((width*height)*sizeof(float));
	float *k_blue =(float*) malloc((width*height)*sizeof(float));
	
	if ((k_red==NULL) || (k_green==NULL) || (k_blue==NULL)){
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
	
	float grad; //valores temporales
	for(i=0; i<Niter; i++){
		
		aan_mascara_imagen(red_input,green_input,blue_input,red_ux,green_ux,blue_ux,width,height,mfx);
		aan_mascara_imagen(red_input,green_input,blue_input,red_uy,green_uy,blue_uy,width,height,mfy);
		
		for(j=0; j<(width*height); j++){
			grad = sqrt((red_ux[j]*red_ux[j])+(red_uy[j]*red_uy[j]));
			k_red[j] = exp(-lamb*grad);			
			grad = sqrt((green_ux[j]*green_ux[j])+(green_uy[j]*green_uy[j]));
			k_green[j] = exp(-lamb*grad);			
			grad = sqrt((blue_ux[j]*blue_ux[j])+(blue_uy[j]*blue_uy[j]));
			k_blue[j] = exp(-lamb*grad);		
		}
		
		aan_mascara_canal_P_M(red_input,red_output,width,height,k_red,dt);
		aan_mascara_canal_P_M(green_input,green_output,width,height,k_green,dt);
		aan_mascara_canal_P_M(blue_input,blue_output,width,height,k_blue,dt);
		
		for(j=0; j<(width*height); j++){
			red_input[j] = red_output[j]; 
			green_input[j] = green_output[j];  
			blue_input[j] = blue_output[j];
			
			//se transforma a unsigned char los canales	
			wr_red[j] = (unsigned char) red_output[j];
			wr_green[j] = (unsigned char) green_output[j];
			wr_blue[j] = (unsigned char) blue_output[j];		
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
	free(k_red);
	free(k_green);
	free(k_blue);
	free(red_ux);
	free(green_ux);
	free(blue_ux);
	free(red_uy);
	free(green_uy);
	free(blue_uy);
	free(red_output);
	free(green_output);
	free(blue_output);
		
	return;									 	
}

//Crea las imagenes para la ecuacion de perona-malik:
int aan_perona_malik(char *imagen, float dt, int Niter, float lamb) {
	
	struct canales_float Canf1;
	
	if (!Leer_imagen(imagen,&Canf1.red,&Canf1.green,&Canf1.blue,&Canf1.width,&Canf1.height)){
			return 0;
	}
	
	aan_ecuacion_perona_malik(Canf1.red,Canf1.green,Canf1.blue,
							  Canf1.width,Canf1.height,dt,Niter,lamb);
	
	free(Canf1.red);
	free(Canf1.green);
	free(Canf1.blue);	
	
	return 1;
}
#endif /*PRACT9_AAN_H_*/
