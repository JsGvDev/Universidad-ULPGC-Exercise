#include <stdlib.h>
#include <string.h>
#include "Pract9_aan.h"

int prueba_predeterminada(float dt, int Niter, float lamb){
	
	printf("\n\n\nPrueba Predeterminada:\n\n");
	
	printf("\n\nPrueba 1: ruido1.bmp\n\n");	
	aan_perona_malik("ruido1.bmp",dt,Niter,lamb);
	printf("\n\nComprueba las imagenes para proseguir\n\n");
	system("imagen_100000.bmp");
	
	printf("\n\nPrueba 2: ruido2.bmp\n\n");
	aan_perona_malik("ruido2.bmp",dt,Niter,lamb);
	printf("\n\nComprueba las imagenes para proseguir\n\n");
	system("imagen_100000.bmp");
	
	printf("\n\nPrueba 3: ruido3.bmp\n\n");
	aan_perona_malik("ruido3.bmp",dt,Niter,lamb);
	printf("\n\nComprueba las imagenes para proseguir\n\n");
	system("imagen_100000.bmp");
	
	printf("\n\nPrueba 4: ruido5.bmp\n\n");
	aan_perona_malik("ruido5.bmp",dt,Niter,lamb);
	printf("\n\nComprueba las imagenes para proseguir\n\n");
	system("imagen_100000.bmp");
	
	return 1;
}

int tus_pruebas(float dt, int Niter, float lamb){
	
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
    
    if(aan_perona_malik(name,dt,Niter,lamb)){
    	printf("\n\nComprueba las imagenes para proseguir\n\n");
    	system("imagen_100000.bmp");
    } else {
    	printf("\n\nERROR en la ecuacion de PERONA-MALIK\n\n");
    }
    
	return 1;
}

//Programa Principal:
int main(){
	
	printf("******************MENU*********************\n");
	printf("*                                         *\n");
	printf("*       ECUACION DE PERONA-MALIK          *\n");
	printf("*                                         *\n");
	printf("* Elija pruebas:                          *\n");
	printf("*                                         *\n");
	printf("*       1. PRUEBA PREDETERMINADA          *\n");
	printf("*       2. TUS PRUEBAS                    *\n");
	printf("*       0. SALIR                          *\n");
	printf("*                                         *\n");
	printf("* Op: 100 iterac. y 0.1 dt (por defecto)  *\n");
	printf("*           1. lambda = 0.01              *\n");
	printf("*           2. lambda = 0.001             *\n");
	printf("*           3. lambda = 0.0001            *\n");
	printf("*******************************************\n");
	
	int op,op_tp,ed,cont,Niter;
	float dt,lamb;
			
	op = -1;
	op_tp = -1;
	ed = -1;
	cont = 0;	
	while (op != 0){
		printf("\n\nMENU Opcion: ");
		scanf("%d",&op);
		fflush (stdin);
		if (op > 0 && op < 3){
			printf("\n\nElija lambda, [1-3] --> ");
			scanf("%d",&op_tp);
			fflush (stdin);
			while ((op_tp < 1) || (op_tp > 3)){
				printf("\n\nElija una respuesta valida: ");
				scanf("%d",&op_tp);
				fflush (stdin);
			}
			if (op_tp == 1){
				lamb = 0.01;
			} else {
				if (op_tp == 2){
					lamb = 0.001;
				} else lamb = 0.0001;
			}
			if (op_tp > 0 && op_tp < 3){
				printf("\n\n ENTRADA DE DATOS: [1.Manual - 2.Por Defecto] -->");
				scanf("%d",&ed);
				fflush (stdin);
				while ((ed < 1) || (ed > 2)){
					printf("\n\nElija una respuesta valida: ");
					scanf("%d",&ed);
					fflush (stdin);
				}
				if (ed == 1){
					printf("\n\nMANUAL: ");
					printf("\nNumero de iteraciones --> ");
					scanf("%d",&Niter);
					printf("\nIncremento temporal --> ");
					scanf("%f",&dt);					
				} else {
					Niter = 100;
					dt = 0.1;
				}
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
						prueba_predeterminada(dt,Niter,lamb);
						op = 0;
					}
					break;
			case 2: printf("\n\nTUS PRUEBAS: ");
					fflush (stdin);
					tus_pruebas(dt,Niter,lamb);
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
