#include <stdlib.h>
#include <string.h>
#include "Pract10_aan.h"

int prueba_predeterminada(int R1, int R2, float umbr_corr, float umbr_grad, int interv){
	
	printf("**** Prueba Predeterminada ****************\n");
	printf("*                                         *\n");
	printf("*   1. Prueba Lenta: mas de 30 minutos.   *\n");
	printf("*   2. Prueba Media: menos de 5 minutos.  *\n");
	printf("*   3. Prueba Rapida: menos de 1 minutos. *\n");
	printf("*                                         *\n");
	printf("*******************************************\n");
	
	int op = -1;
		
	while (op!=0){
		printf("\n\nMENU Opcion: ");
		scanf("%d",&op);
		fflush (stdin);
		switch (op){
			case 1: aan_deteccion_movimiento("2.bmp","9.bmp",5,25,0.5,0,1);
					op = 0;
					break;
			case 2: aan_deteccion_movimiento("2.bmp","9.bmp",5,25,0.5,0.2,1);
					op = 0;
					break;
			case 3: aan_deteccion_movimiento("2.bmp","9.bmp",5,20,0.7,0.4,1);
					op = 0;
					break;
			default:
					printf("\n\nElija una opcion valida\n");
					break;
		}
	}			
		
			
	printf("\n\nComprueba las imagenes para proseguir\n\n");
    system("Imagen_Inicial.bmp");
    system("Imagen_Final.bmp");
	
	return 1;
}

int tus_pruebas(int R1, int R2, float umbr_corr, float umbr_grad, int interv){
	
	char name1[200],name2[200];
	int i;
	
	//Leer Imagen:
	printf("\n\n\nElija imagen Inicial: ");
	fgets(name1, 200, stdin);
   	fflush (stdin);
    for (i=strlen(name1); (i>=0) && (name1[i-1]=='\n'); i--){
    	name1[i-1]=name1[i];
    }
    printf("\n\nImagen Inicial --> %s", name1);
    
    printf("\n\n\nElija imagen Final: ");
	fgets(name2, 200, stdin);
   	fflush (stdin);
    for (i=strlen(name2); (i>=0) && (name2[i-1]=='\n'); i--){
    	name2[i-1]=name2[i];
    }
    printf("\n\nImagen Final --> %s\n\n", name2);
    
    if(aan_deteccion_movimiento(name1,name2,R1,R2,umbr_corr,umbr_grad,interv)){
    	printf("\n\nComprueba las imagenes para proseguir\n\n");
    	system("Imagen_Inicial.bmp");
    	system("Imagen_Final.bmp");
    } else {
    	printf("\n\nERROR en la deteccion de movimiento\n\n");
    }
    
	return 1;
}

//MENU:
void menu(){
	printf("******************MENU*********************\n");
	printf("*                                         *\n");
	printf("*        DETECCION DE MOVIMIENTO          *\n");
	printf("*                                         *\n");
	printf("* Elija pruebas:                          *\n");
	printf("*                                         *\n");
	printf("*       1. PRUEBA PREDETERMINADA          *\n");
	printf("*       2. TUS PRUEBAS                    *\n");
	printf("*       0. SALIR                          *\n");
	printf("*                                         *\n");
	printf("* Valores por defecto:                    *\n");
	printf("*   Tam. Ventana ->   R1=5   R2=25        *\n");
	printf("*   Umbrales     -> Correlacion = 0.5     *\n");
	printf("*                   Gradiente   = 0.2     *\n");
	printf("* Op. Intervalos:                         *\n");
	printf("*   1. 1 en 1   2. 3 en 3   3. 5 en 5     *\n");
	printf("*******************************************\n");
	return;
}

//Programa Principal:
int main(){
		
	int op,op_grad,op_inter,ed,cont,R1,R2,interv;
	float umbr_corr,umbr_grad;
			
	op = -1;
	op_grad = -1;
	op_inter = -1;
	ed = -1;
	cont = 0;	
	while (op != 0){
		
		menu();
		
		printf("\n\nMENU Opcion: ");
		scanf("%d",&op);
		fflush (stdin);		
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
						prueba_predeterminada(R1,R2,umbr_corr,umbr_grad,interv);
						op = 0;
					}
					break;
			case 2: printf("\n\nTUS PRUEBAS: ");
					fflush (stdin);
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
						printf("\nTam.Ventana R1 --> ");
						scanf("%d",&R1);
						printf("\nTam.Ventana R2 --> ");
						scanf("%d",&R2);
						printf("\nUmbral Correlacion --> ");
						scanf("%f",&umbr_corr);
						printf("\n\n Quiere introducir un umbral para el modulo del Gradiente (agiliza el proceso): [1.Si - 2.No] -->");
						scanf("%d",&op_grad);
						fflush (stdin);
						while ((op_grad < 1) || (op_grad > 2)){
							printf("\n\nElija una respuesta valida: ");
							scanf("%d",&op_grad);
							fflush (stdin);
						}
						if (op_grad == 1){
							printf("\nUmbral Gradiente --> ");
							scanf("%f",&umbr_grad);
						} else umbr_grad = -1;
					} else {
						R1 = 5;
						R2 = 25;
						umbr_corr = 0.5;
						umbr_grad = 0.2;
					}
					printf("\n\nElija Op.Intervalo [1-3] --> ");
					scanf("%d",&op_inter);
					fflush (stdin);
					while ((op_inter < 1) || (op_inter > 3)){
						printf("\n\nElija una respuesta valida: ");
						scanf("%d",&op_inter);
						fflush (stdin);
					}
					if (op_inter == 1){
						interv = 1;
					} else {
						if (op_inter == 2){
							interv = 3;
						} else interv = 5;
					}
					tus_pruebas(R1,R2,umbr_corr,umbr_grad,interv);
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
