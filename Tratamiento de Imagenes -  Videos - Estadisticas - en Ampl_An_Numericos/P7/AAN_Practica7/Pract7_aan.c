#include <stdlib.h>
#include <string.h>
#include "Pract7_aan.h"

int prueba_predeterminada(float dt, int Niter, float k, float M, int op){
	
	printf("\n\n\nPrueba Predeterminada:\n\n");
	
	aan_propagacion_frentes("canarias.bmp",dt,Niter,k,M,op);
	printf("\n\nComprueba las imagenes para proseguir\n\n");
	system("imagen_100000.bmp");
	
	return 1;
}

int tus_pruebas(float dt, int Niter, float k, float M, int op){
	
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
    
    if (aan_propagacion_frentes(name,dt,Niter,k,M,op)){
    	printf("\n\nComprueba las imagenes para proseguir\n\n");
    	system("imagen_100000.bmp");
    } else {
    	printf("\n\nERROR en la propagacion de frentes\n\n");
    }
    
	return 1;
}

//Programa Principal:
int main(){
	
	printf("******************MENU*********************\n");
	printf("*                                         *\n");
	printf("*           PROPAGACION DE                *\n");
	printf("*              FRENTES                    *\n");
	printf("*                                         *\n");
	printf("* Elija pruebas:                          *\n");
	printf("*                                         *\n");
	printf("*       1. PRUEBA PREDETERMINADA          *\n");
	printf("*       2. TUS PRUEBAS                    *\n");
	printf("*       0. SALIR                          *\n");
	printf("*                                         *\n");
	printf("* Opciones:                               *\n");
	printf("*                                         *\n"); 
	printf("*     Prueba1 - velocidad inversa a la    *\n");
    printf("*               magnitud de un canal:     *\n");
    printf("*                 F = k(255-V)/255        *\n");
    printf("*                                         *\n");
	printf("*     Prueba2 - velocidad inversa a la    *\n");
	printf("*               magnitud del gradiente    *\n");
	printf("*                  F = k(1-V)             *\n");
	printf("*                  V = min(1,grad/M)      *\n");
	printf("*                                         *\n");
	printf("*******************************************\n");
	
	int op,op_tp,ed,cont,Niter;
	float dt,k,M;
			
	op = -1;
	op_tp = -1;
	cont = 0;
	while (op != 0){
		printf("\n\nMENU Opcion: ");
		scanf("%d",&op);
		fflush (stdin);
		if (op > 0 && op < 3){
			printf("\n\nElija opciones, [Prueba1-Prueba2] --> ");
			scanf("%d",&op_tp);
			fflush (stdin);
			while ((op_tp < 1) || (op_tp > 2)){
				printf("\n\nElija una respuesta valida: ");
				scanf("%d",&op_tp);
				fflush (stdin);
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
					printf("\nk (controla lo rapida que es la propagacion) --> ");
					scanf("%f",&k);
					printf("\nM (frena completamente la propagacion) --> ");
					scanf("%f",&M);
				} else {
					Niter = 300;
					dt = 0.5;
					k = 2.0;
					M = 25.0;
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
						prueba_predeterminada(dt,Niter,k,M,op_tp);
						op = 0;
					}
					break;
			case 2: printf("\n\nTUS PRUEBAS: ");
					fflush (stdin);
					tus_pruebas(dt,Niter,k,M,op_tp);
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
