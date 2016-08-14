#include <stdlib.h>
#include <string.h>
#include "Pract6_aan.h"

int prueba_predeterminada(float *e){
	
	char *imagenes[]={"clara1.bmp","oscura1.bmp","oscura2.bmp","oscura3.bmp",
					  "pla1.bmp","porto7.bmp","pp1.bmp","roja1.bmp","roja2.bmp"};
	int i;
	printf("\n\n\nPruebas Predeterminadas:\n\n");
	
	for (i=0; i<9; i++){
		aan_ecualizador(imagenes[i],e);
		system("Imagen_Ecualizada.bmp");
	}
	return 1;
}

int tus_pruebas(float *e){
	
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
    
    if (aan_ecualizador(name,e)){
    	system("Imagen_Ecualizada.bmp");
    } else {
    	printf("\n\nERROR en el ecualizado de una imagen\n\n");
    }
	return 1;
}

//Programa Principal:
int main(){
	
	printf("******************MENU*********************\n");
	printf("*                                         *\n");
	printf("*           ECUALIZACION DE               *\n");
	printf("*             HISTOGRAMAS                 *\n");
	printf("*                                         *\n");
	printf("* Elija pruebas:                          *\n");
	printf("*                                         *\n");
	printf("*       1. PRUEBAS PREDETERMINADAS        *\n");
	printf("*                                         *\n");
	printf("*       2. TUS PRUEBAS                    *\n");
	printf("*                                         *\n");
	printf("*       0. SALIR                          *\n");
	printf("*                                         *\n");
	printf("* Opciones:  1. e[i] = 1./256             *\n"); 
	printf("*            2. e[i] =                    *\n");
	printf("*         [0..127]  --> (1/512)..(1/128)  *\n");
	printf("*         [128..255]--> (1/128)..(1/512)  *\n");
	printf("*                                         *\n");
	printf("*******************************************\n");
	
	int op,op_tp,cont,i;
	float e[256];
	op = -1;
	op_tp = -1;
	cont = 0;
	while (op != 0){
		printf("\n\nMENU Opcion: ");
		scanf("%d",&op);
		fflush (stdin);
		if (op > 0 && op < 3){
			printf("\n\nElija opciones, [1-2] --> ");
			scanf("%d",&op_tp);
			fflush (stdin);
			while ((op_tp < 1) || (op_tp > 2)){
				printf("\n\nElija una respuesta valida: ");
				scanf("%d",&op_tp);
				fflush (stdin);
			}
			switch (op_tp){
				case 1: //opcion 1:
						for (i=0; i<256; i++){
							e[i] = 1.0/256.0;
						}
						break;
				case 2: //opcion 2:
						for (i=0; i<127; i++){
							e[i] = 1.0/512.0 + (1.0/128.0 - 1.0/512.0)*i/127.0;
						}
						for (i=0; i<127; i++){
							e[128+i] = e[127-i];
						}
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
						prueba_predeterminada(e);
						op = 0;
					}
					break;
			case 2: printf("\n\nTUS PRUEBAS: ");
					tus_pruebas(e);
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
