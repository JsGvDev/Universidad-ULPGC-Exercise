#ifndef PRACT5_AAN_H_
#define PRACT5_AAN_H_

#include "Pract2_aan.h"

//HISTOGRAMA:
void aan_histograma_canal (unsigned char *canal_input, int *histograma, int width, int height){
	int i;
	for (i=0; i<(width*height); i++){
		histograma[canal_input[i]]+=1;
	}
	return;
}
//MEDIANA:
void aan_mediana_canal (unsigned char *canal, int width, int height, float *T0, float *T1, float *T2){
	
	int *histograma;
	histograma =(int*) calloc(256,sizeof(int));
	aan_histograma_canal(canal,histograma,width,height);
	
	float med0,med1,med2;
	float med0b,med1b,med2b;
	int i;
	int Ni=0;//frecuencias absolutas acumuladas
	int ObtenidoT0=0,ObtenidoT1=0;
	int Obtenidomed0=0,Obtenidomed1=0,Obtenidomed2=0;
	//IMPAR:
	if ((width*height)%2 != 0){
		med0 = (width*height+1)/4;
		med1 = (width*height+1)/2;
		med2 = (3*width*height+1)/4;
			
		for(i=0; i<256;i++){
			Ni+=histograma[i];
			if((Ni>med0) && (!ObtenidoT0)){
				*T0=i;
				ObtenidoT0= 1;
			}
			if((Ni>med1) && (!ObtenidoT1)){
				*T1=i;
				ObtenidoT1= 1;
			}
			if(Ni>med2){
				*T2=i;
				break;
			}
		}
	} else {
	//PAR:
		med0 = (width*height)/4;
		med0b = med0+1;
		med1 = (width*height)/2;
		med1b = med1+1;
		med2 = (3*width*height)/4;
		med2b = med2+1;
		for(i=0; i<256;i++){
			Ni+=histograma[i];
			//T0
			if((Ni>med0) && (!Obtenidomed0)){
				med0=i;
				Obtenidomed0= 1;
			}
			if((Ni>med0b) && (!ObtenidoT0)){
				*T0=(i+med0)/2;
				ObtenidoT0= 1;
			}
			//T1
			if((Ni>med1) && (!Obtenidomed1)){
				med1=i;
				Obtenidomed1= 1;
			}
			if((Ni>med1b) && (!ObtenidoT1)){
				*T1=(i+med1)/2;
				ObtenidoT1= 1;
			}
			//T2
			if((Ni>med2) && (!Obtenidomed2)){
				med2=i;
				Obtenidomed2= 1;
			}
			if(Ni>med2b){
				*T2=(i+med2)/2;
				break;
			}
		}
	}
	
	free(histograma);
	return;
}
//funcion para hacer mediana:
int mediana_imagen (char *nombre, float T0[3], float T1[3], float T2[3]){
	
	unsigned char *red;
	unsigned char *green;
	unsigned char *blue;
	int width,height;
	
	if (ami_read_bmp(nombre,&red,&green,&blue,&width,&height)){
			printf ("Error abriendo la Imagen: %s\n\n", nombre);
			return 0;
	}
	
	float T_ini;
	float T_med;
	float T_fin;
	
	aan_mediana_canal(red,width,height,&T_ini,&T_med,&T_fin);
	T0[0]=T_ini; T1[0]=T_med; T2[0]=T_fin;
	aan_mediana_canal(green,width,height,&T_ini,&T_med,&T_fin);
	T0[1]=T_ini; T1[1]=T_med; T2[1]=T_fin;
	aan_mediana_canal(blue,width,height,&T_ini,&T_med,&T_fin);
	T0[2]=T_ini; T1[2]=T_med; T2[2]=T_fin;
	
	free(red);
	free(green);
	free(blue);
	
	return 1;	
}
//MEDIA:
void aan_media_canal (unsigned char *canal, int width, int height, float *T0, float *T1, float *T2){
	
	int *histograma;
	histograma =(int*) calloc(256,sizeof(int));
	aan_histograma_canal(canal,histograma,width,height);
	//T1:
	int i;
	float media=0,media0=0,media2=0;
	for (i=0; i<256;i++){
		media = media + (i*histograma[i]);
	}
	*T1 = media/(width*height);
	//T0:
	int cont = 0;	
	for (i=0; i<(int)*T1;i++){
		media0 = media0 + (i*histograma[i]);
		cont = cont + histograma[i];
	}
	*T0 = media0/cont;
	//T2:	
	cont=0;
	for (i=(int)*T1; i<256;i++){
		media2 = media2 + (i*histograma[i]);
		cont = cont + histograma[i];
	}
	*T2 = media2/cont;
	
	free(histograma);
	return;
}
//funcion para hacer la media:
int media_imagen (char *nombre, float T0[3], float T1[3], float T2[3]){
	
	unsigned char *red;
	unsigned char *green;
	unsigned char *blue;
	int width,height;
	
	if (ami_read_bmp(nombre,&red,&green,&blue,&width,&height)){
			printf ("Error abriendo la Imagen: %s\n\n", nombre);
			return 0;
	}
	
	float T_ini;
	float T_med;
	float T_fin;
	
	aan_media_canal(red,width,height,&T_ini,&T_med,&T_fin);
	T0[0]=T_ini; T1[0]=T_med; T2[0]=T_fin;
	aan_media_canal(green,width,height,&T_ini,&T_med,&T_fin);
	T0[1]=T_ini; T1[1]=T_med; T2[1]=T_fin;
	aan_media_canal(blue,width,height,&T_ini,&T_med,&T_fin);
	T0[2]=T_ini; T1[2]=T_med; T2[2]=T_fin;
	
	free(red);
	free(green);
	free(blue);
	
	return 1;	
}
//ECUACION DEL CALOR:
void aan_ecuacion_calor_fuerza_externa_metodo_explicito(
			float *canal_input, float *canal_output, int width, int height,
			float dt, int Niter,float A, float T0, float T1, float T2){
	int j;	
	for(j=0; j<(width*height); j++){
		canal_input[j] = canal_input[j] + (dt*canal_output[j]) - (A*dt*(canal_input[j]-T0)*(canal_input[j]-T1)*(canal_input[j]-T2));
	}
	return;
}

void aan_ecuacion_calor(float *red_input, float *green_input, float*blue_input,
						float *red_output, float *green_output, float *blue_output,
						int width, int height, float dt, int Niter,
						float A, float T0[3], float T1[3], float T2[3]){
	
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

		aan_ecuacion_calor_fuerza_externa_metodo_explicito(red_input,red_output,width,height,dt,Niter,A,T0[0],T1[0],T2[0]);
		aan_ecuacion_calor_fuerza_externa_metodo_explicito(green_input,green_output,width,height,dt,Niter,A,T0[1],T1[1],T2[1]);
		aan_ecuacion_calor_fuerza_externa_metodo_explicito(blue_input,blue_output,width,height,dt,Niter,A,T0[2],T1[2],T2[2]);
	
		for(j=0; j<(width*height); j++){
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
#endif /*PRACT5_AAN_H_*/
