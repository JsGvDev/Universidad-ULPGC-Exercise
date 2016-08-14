#include <stdlib.h>
#include <string.h>
#include "Pract8_aan.h"

int prueba_predeterminada(float dt, int Niter){
	
	printf("\n\n\nPrueba Predeterminada:\n\n");
	
	printf("\n\nPrueba 1: circulos1.bmp\n\n");	
	aan_ecuacion_ondas("circulos1.bmp",dt,Niter);
	printf("\n\nComprueba las imagenes para proseguir\n\n");
	system("imagen_100000.bmp");
	
	printf("\n\nPrueba 2: circulos2.bmp\n\n");
	aan_ecuacion_ondas("circulos2.bmp",dt,Niter);
	printf("\n\nComprueba las imagenes para proseguir\n\n");
	system("imagen_100000.bmp");
	
	printf("\n\nPrueba 3: circulos3.bmp\n\n");
	aan_ecuacion_ondas("circulos3.bmp",dt,Niter);
	printf("\n\nComprueba las imagenes para proseguir\n\n");
	system("imagen_100000.bmp");
	
	printf("\n\nPrueba 4: onda1.bmp\n\n");
	aan_ecuacion_ondas("onda1.bmp",dt,Niter);
	printf("\n\nComprueba las imagenes para proseguir\n\n");
	system("imagen_100000.bmp");
	
	return 1;
}

int tus_pruebas(float dt, int Niter){
	
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
    
    if(aan_ecuacion_ondas(name,dt,Niter)){
    	printf("\n\nComprueba las imagenes para proseguir\n\n");
    	system("imagen_100000.bmp");
    } else {
    	printf("\n\nERROR en la ecuacion de ondas\n\n");
    }
    
	return 1;
}

//Programa Principal:
int main(){
	
	printf("******************MENU*********************\n");
	printf("*                                         *\n");
	printf("*          ECUACION DE ONDAS              *\n");
	printf("*                                         *\n");
	printf("* Elija pruebas:                          *\n");
	printf("*                                         *\n");
	printf("*       1. PRUEBA PREDETERMINADA          *\n");
	printf("*       2. TUS PRUEBAS                    *\n");
	printf("*       0. SALIR                          *\n");
	printf("*                                         *\n");
	printf("* Opciones: 1000 iteraciones              *\n");
	printf("*              1. dt = 0.1                *\n");
	printf("*              2. dt = 0.01               *\n"); 
	printf("*******************************************\n");
	
	int op,op_tp,cont,Niter;
	float dt;
			
	op = -1;
	op_tp = -1;
	cont = 0;
	Niter = 1000;
	while (op != 0){
		printf("\n\nMENU Opcion: ");
		scanf("%d",&op);
		fflush (stdin);
		if (op > 0 && op < 3){
			printf("\n\nElija dt, [1-2] --> ");
			scanf("%d",&op_tp);
			fflush (stdin);
			while ((op_tp < 1) || (op_tp > 2)){
				printf("\n\nElija una respuesta valida: ");
				scanf("%d",&op_tp);
				fflush (stdin);
			}
			if (op_tp == 1){
				dt = 0.1;
			} else {
				dt = 0.01;
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
					fflush (stdin);
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
