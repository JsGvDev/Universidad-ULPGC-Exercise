#include <stdlib.h>
#include <string.h>
#include "Pract5_aan.h"

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

int prueba_predeterminada(float dt, int Niter){
	
	struct canales_float Canf1,Canf_out;
	char *imagenes[]={"ruido1.bmp","ruido2.bmp","colores2.bmp","colores1.bmp","planta1.bmp","planta2.bmp","planta3.bmp"};
		
	int i,j;
	printf("\n\n\nPruebas Predeterminadas:\n\n");
	
	int op=0;
	float A = 0.0001;
	float T0[3];
	float T1[3];
	float T2[3];
	
	printf("\n\nElija una OPCION valida: \n");
	printf("    1. VALORES POR DEFECTO: T0=0  T1=128  T2=255 \n");
	printf("    2. VALORES DE LA MEDIANA \n");
	printf("    3. VALORES MEDIOS\n\n");
	scanf("%d",&op);
	fflush (stdin);
	while ((op < 1) || (op > 3)){
		printf("\n\nElija una opcion valida: ");
		scanf("%d",&op);
		fflush (stdin);
	}
	
	for (i=0; i<7; i++){
		
		if (op == 1) {
			for(j=0;j<3;j++){
				T0[j]=0;
				T1[j]=128;
				T2[j]=255;			
			}		
		} else {
			if (op == 2) {
				mediana_imagen(imagenes[i],T0,T1,T2);
				printf("\n\n  MEDIANA:  Canal Rojo  - T0=%4.2f    T1=%4.2f    T2=%4.2f\n", T0[0],T1[0],T2[0]);
				printf("            Canal Verde - T0=%4.2f    T1=%4.2f    T2=%4.2f\n", T0[1],T1[1],T2[1]);
				printf("            Canal Azul  - T0=%4.2f    T1=%4.2f    T2=%4.2f\n\n\n", T0[2],T1[2],T2[2]);
			} else {
				media_imagen(imagenes[i],T0,T1,T2);
				printf("\n\n  MEDIA:  Canal Rojo  - T0=%4.2f    T1=%4.2f    T2=%4.2f\n", T0[0],T1[0],T2[0]);
				printf("          Canal Verde - T0=%4.2f    T1=%4.2f    T2=%4.2f\n", T0[1],T1[1],T2[1]);
				printf("          Canal Azul  - T0=%4.2f    T1=%4.2f    T2=%4.2f\n\n\n", T0[2],T1[2],T2[2]);
			}
		}
		
		if (!Leer_imagen(imagenes[i],&Canf1.red,&Canf1.green,&Canf1.blue,&Canf1.width,&Canf1.height)){
			return 0;
		}
		
		aan_ecuacion_calor(Canf1.red,Canf1.green,Canf1.blue,Canf_out.red,Canf_out.green,Canf_out.blue,Canf1.width,Canf1.height,dt,Niter,A,T0,T1,T2);
		
		free(Canf1.red);
		free(Canf1.green);
		free(Canf1.blue);
		if (op == 1){
			switch (i){
				case 0: system("ruido_1.avi");
						break;
				case 1: system("ruido_2.avi");
						break;
				case 2: system("colores_1.avi");
						break;
				case 3: system("colores_2.avi");
						break;
				case 4: system("planta_1.avi");
						break;
				case 5: system("planta_2.avi");
						break;
				case 6: system("planta_3.avi");
						break;
			}
		} else {
			printf("\n\nComprueba las imagenes para proseguir\n\n");
			system("imagen_100000.bmp");			
		}
	}
	return 1;
}

int tus_pruebas(float dt, int Niter){
	
	struct canales_float Canf1, Canf_out;
	char name[200];
	int i;
	
	//Leer Imagen:
	printf("\n\n\nElija imagen: ");
	fgets(name, 200, stdin);
   	fflush (stdin);
    for (i=strlen(name); (i>=0) && (name[i-1]=='\n'); i--){
    	name[i-1]=name[i];
    }
    printf("\n\nImagen --> %s\n\n", name);
    
    int op=0;
	float A = 0.0001;
	float T0[3];
	float T1[3];
	float T2[3];
	
	printf("\n\nElija una OPCION valida: \n");
	printf("    1. VALORES POR DEFECTO: T0=0  T1=128  T2=255 \n");
	printf("    2. VALORES DE LA MEDIANA DE LA IMAGEN: %s \n",name);
	printf("    3. VALORES MEDIOS DE LA IMAGEN: %s \n\n",name);
	scanf("%d",&op);
	fflush (stdin);
	while ((op < 1) || (op > 3)){
		printf("\n\nElija una opcion valida: ");
		scanf("%d",&op);
		fflush (stdin);
	}

    if (!Leer_imagen(name,&Canf1.red,&Canf1.green,&Canf1.blue,&Canf1.width,&Canf1.height)){
			return 0;
	}

	printf("\n\nObteniendo las imagenes:\n\n");

	if (op == 1) {
		for(i=0;i<3;i++){
			T0[i]=0;
			T1[i]=128;
			T2[i]=255;			
		}		
	} else {
		if (op == 2) {
			mediana_imagen(name,T0,T1,T2);
			printf("\n\n  MEDIANA:  Canal Rojo  - T0=%4.2f    T1=%4.2f    T2=%4.2f\n", T0[0],T1[0],T2[0]);
			printf("            Canal Verde - T0=%4.2f    T1=%4.2f    T2=%4.2f\n", T0[1],T1[1],T2[1]);
			printf("            Canal Azul  - T0=%4.2f    T1=%4.2f    T2=%4.2f\n\n\n", T0[2],T1[2],T2[2]);
		} else {
			media_imagen(name,T0,T1,T2);
			printf("\n\n  MEDIA:  Canal Rojo  - T0=%4.2f    T1=%4.2f    T2=%4.2f\n", T0[0],T1[0],T2[0]);
			printf("          Canal Verde - T0=%4.2f    T1=%4.2f    T2=%4.2f\n", T0[1],T1[1],T2[1]);
			printf("          Canal Azul  - T0=%4.2f    T1=%4.2f    T2=%4.2f\n\n\n", T0[2],T1[2],T2[2]);
		}
	}
	
	aan_ecuacion_calor(Canf1.red,Canf1.green,Canf1.blue,Canf_out.red,Canf_out.green,Canf_out.blue,Canf1.width,Canf1.height,dt,Niter,A,T0,T1,T2);
		
	free(Canf1.red);
	free(Canf1.green);
	free(Canf1.blue);
	
	printf("\n\nComprueba las imagenes para proseguir\n\n");
	system("imagen_100000.bmp");
	return 1;
}

//Programa Principal:
int main(){
	
	printf("******************MENU*********************\n");
	printf("*                                         *\n");
	printf("*        ECUACION DEL CALOR CON           *\n");
	printf("*          UN TERMINO EXTERNO             *\n");
	printf("*                                         *\n");
	printf("* Elija pruebas:                          *\n");
	printf("*                                         *\n");
	printf("*       1. PRUEBAS PREDETERMINADAS        *\n");
	printf("*                                         *\n");
	printf("*       2. TUS PRUEBAS                    *\n");
	printf("*                                         *\n");
	printf("*       0. SALIR                          *\n");
	printf("*                                         *\n");
	printf("* Opciones:  1. Nt=100     dt=1/4         *\n"); 
	printf("*            2. Nt=200     dt=1/8         *\n");
	printf("*            3. Nt=400     dt=1/16        *\n");
	printf("*            4. Nt=800     dt=1/32        *\n");
	printf("*            5. Nt=50      dt=1/2         *\n");
	printf("*                                         *\n");
	printf("*     Nt --> numero iteraciones           *\n");
	printf("*     dt --> incremento temporal          *\n");	
	printf("*******************************************\n");
	
	int op,op_tp,cont,Niter;
	float dt;
	op = -1;
	op_tp = -1;
	cont = 0;
	while (op != 0){
		printf("\n\nMENU Opcion: ");
		scanf("%d",&op);
		fflush (stdin);
		if (op > 0 && op < 3){
			printf("\n\nElija Nt(numero iteraciones) y dt(incremento temporal), [1-5] --> ");
			scanf("%d",&op_tp);
			fflush (stdin);
			while ((op_tp < 1) || (op_tp > 5)){
				printf("\n\nElija una respuesta valida: ");
				scanf("%d",&op_tp);
				fflush (stdin);
			}
			switch (op_tp){
				case 1: dt=1./4; Niter=100;
						break;
				case 2: dt=1./8; Niter=200;
						break;
				case 3: dt=1./16; Niter=400;
						break;
				case 4: dt=1./32; Niter=800;
						break;
				case 5: dt=1./2; Niter=50;
						break;
			}
		}
		switch (op){
			case 0: op = 0;
					break;
			case 1: printf("\n\nEsta prueba se ejecuta una sola vez,\n");
					printf("y finaliza su ejecucion.\n");
					printf("Desea continuar: 1. SI   2.NO\n");
					scanf("%d",&cont);
					fflush (stdin);
					while ((cont < 1) || (cont > 2)){
						printf("\n\nElija una respuesta valida: ");
						scanf("%d",&cont);
						fflush (stdin);
					}
					if (cont == 1){
						prueba_predeterminada(dt,Niter);
						op = 0;
					}
					break;
			case 2: printf("\n\nTUS PRUEBAS: ");
					tus_pruebas(dt,Niter);
					break;
			default:
					printf("\n\nElija una opcion valida\n");
					break;
		}
	}
		
	printf("\n\n\nFIN\n\n");
	system("PAUSE");
	return 0;
}
