#ifndef PRACT10_AAN_H_
#define PRACT10_AAN_H_

#include "Pract2_aan.h"

#define valido(i,max) ((i > 0) ? ((i < max) ? i : max-1) : 0);

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

//CORRELACION:
void aan_correlacion(float *red1_input, float *green1_input, float *blue1_input,
					 float *red2_input, float *green2_input, float *blue2_input,
					 int width, int height, int R1, int R2, float umbr_corr, float umbr_grad, int interv){
	
	float *ux =(float*) malloc((width*height)*sizeof(float));
	float *uy =(float*) malloc((width*height)*sizeof(float));
		
	if ((ux==NULL) || (uy==NULL)){
		printf("Problemas con la memoria(memoria no disponible)/n");
		return;
	}	
	//Gradiente
	float *red1_ux =(float*) malloc((width*height)*sizeof(float));
	float *red1_uy =(float*) malloc((width*height)*sizeof(float));
		
	if ((red1_ux==NULL) || (red1_uy==NULL)){
		printf("Problemas con la memoria(memoria no disponible)/n");
		return;
	}
				
	int i,k,x,y,j,l,ind_x,ind_y,ind_a,ind_b;
	float suma1,suma2,suma3,c,max_corr;
	float *grad =(float*) malloc((width*height)*sizeof(float));
	
	aan_mascara_canal(red1_input,red1_ux,width,height,mfx);
	aan_mascara_canal(red1_input,red1_uy,width,height,mfy);
	
	for(j=0; j<(width*height); j++){
		grad[j] = sqrt((red1_ux[j]*red1_ux[j])+(red1_uy[j]*red1_uy[j]));
	}
	aan_normalizar_canal_float(grad,grad,width,height);
	for(i=0; i<height; i+=interv){		
		printf("Progreso: %.2f por ciento.\n",((float)(100*i)/height));
		for(k=0; k<width; k+=interv){
			if ((grad[i*width+k] > 0) && ((grad[i*width+k]/255.0) >= umbr_grad)){
				suma2=0;
				max_corr=0;
				for(x=-R1; x<=R1; x++){
					for(y=-R1; y<=R1; y++){
						ind_x=valido((i+x),height);
						ind_y=valido((k+y),width);
						suma2+=(red1_input[ind_x*width+ind_y]*red1_input[ind_x*width+ind_y]);
					}
				}
				for(j=i-R2+R1; j<i+R2-R1; j++){
					for(l=k-R2+R1; l<k+R2-R1; l++){
						suma1=0;
						suma3=0;
						if((j>=R1)||(j<=k-R1)||(l>=R1)||(l<=k-R1-1)){
							for(x=-R1; x<=R1; x++){
								for(y=-R1; y<=R1; y++){
									ind_x=valido((i+x),height);
									ind_y=valido((k+y),width);									
									ind_a=valido((j+x),height);
									ind_b=valido((l+y),width);
									suma1+=(red1_input[ind_x*width+ind_y]*red2_input[ind_a*width+ind_b]);
									suma3+=(red2_input[ind_a*width+ind_b]*red2_input[ind_a*width+ind_b]);
								}
							}
							c = suma1/(sqrt(suma2)*sqrt(suma3));
							if (c > max_corr){
								max_corr = c;
								ux[i*width+k]=j-i;
								uy[i*width+k]=l-k;
							}
						} else {
							ux[i*width+k]=0;
							uy[i*width+k]=0;
						}
					}
				}
				if (max_corr<umbr_corr){
					ux[i*width+k]=0;
					uy[i*width+k]=0;
				}
			} else {
				ux[i*width+k]=0;
				uy[i*width+k]=0;
			}
		}
	}
				
	//Unir canales:
	struct canales_float Can_out;
	
	aan_normalizar_canal_float(ux,ux,width,height);
	aan_normalizar_canal_float(uy,uy,width,height);
	aan_unir_canales_float(ux,uy,&Can_out.red,width,height);
	aan_unir_canales_float(ux,uy,&Can_out.green,width,height);
	aan_unir_canales_float(ux,uy,&Can_out.blue,width,height);
	Can_out.width = width*2+4;
	Can_out.height = height;
	
	//Necesario para la funcion ami write, hacer un cast de float a unsigned char
	unsigned char *wr_red;
	unsigned char *wr_green;
	unsigned char *wr_blue;
	
	wr_red =(unsigned char*) malloc((Can_out.width*Can_out.height)*sizeof(unsigned char));
	wr_green =(unsigned char*) malloc((Can_out.width*Can_out.height)*sizeof(unsigned char));
	wr_blue =(unsigned char*) malloc((Can_out.width*Can_out.height)*sizeof(unsigned char));
	
	for (i=0; i<(Can_out.width*Can_out.height); i++){
		wr_red[i] = (unsigned char) Can_out.red[i];
		wr_green[i] = (unsigned char) Can_out.green[i];
		wr_blue[i] = (unsigned char) Can_out.blue[i];
	}
		
	if (ami_write_bmp("Imagen_Final.bmp",wr_red,wr_green,wr_blue,Can_out.width,Can_out.height)){
		printf ("Error creando la Imagen_Final");
	}
	
	free(wr_red);
	free(wr_green);
	free(wr_blue);
	free(Can_out.red);
	free(Can_out.green);
	free(Can_out.blue);		
	free(grad);
	free(red1_ux);
	free(red1_uy);
	free(ux);
	free(uy);
	
	return;									 	
}

//Crea las imagenes para la deteccion de movimiento:
int aan_deteccion_movimiento(char *imagen1, char *imagen2, int R1, int R2, float umbr_corr, float umbr_grad, int interv) {
	
	struct canales_float Canf1,Canf2;
	
	if (!Leer_imagen(imagen1,&Canf1.red,&Canf1.green,&Canf1.blue,&Canf1.width,&Canf1.height)){
			return 0;
	}
	if (!Leer_imagen(imagen2,&Canf2.red,&Canf2.green,&Canf2.blue,&Canf2.width,&Canf2.height)){
			return 0;
	}
	montar_imagen(Canf1.red,Canf1.green,Canf1.blue,Canf1.width,Canf1.height,Canf2.red,Canf2.green,Canf2.blue,"Imagen_Inicial.bmp");
	aan_correlacion(Canf1.red,Canf2.red,Canf1.green,Canf2.green,Canf1.blue,Canf2.blue,
					Canf1.width,Canf1.height,R1,R2,umbr_corr,umbr_grad,interv);
	
	free(Canf2.red);
	free(Canf2.green);
	free(Canf2.blue);
	free(Canf1.red);
	free(Canf1.green);
	free(Canf1.blue);	
	
	return 1;
}
#endif /*PRACT10_AAN_H_*/
