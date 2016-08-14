#include <stdlib.h>
#include <string.h>
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

int prueba_predeterminada(){
	
	struct canales_float Canf1;
	char *imagenes[]={"azul1.bmp","bordes1.bmp","bordes3.bmp","bordes2.bmp","Neg_Blanc.bmp"};
		
	int i;
	printf("\n\n\nPruebas Predeterminadas:\n\n");
	for (i=0; i<5; i++){
		
		if (!Leer_imagen(imagenes[i],&Canf1.red,&Canf1.green,&Canf1.blue,&Canf1.width,&Canf1.height)){
			return 0;
		}
		aan_mascara(Canf1.red,Canf1.green,Canf1.blue,Canf1.width,Canf1.height);
		aan_mascara_combinada(Canf1.red,Canf1.green,Canf1.blue,Canf1.width,Canf1.height);
		if (i > 2) {
			aan_mascara_prueba_negblanc(Canf1.red,Canf1.green,Canf1.blue,Canf1.width,Canf1.height);
		}
		
		free(Canf1.red);
		free(Canf1.green);
		free(Canf1.blue);
		printf("\n\nComprueba la imagen para proseguir\n\n");
		system("Derivada_Horizontal.bmp");
		system("Derivada_Vertical.bmp");
		system("Laplaciano.bmp");
		system("Mascara_Combinada.bmp");
		if (i > 2) {
			system("Mascara_prueba_negblanc.bmp");
		}
	}
		
	return 1;
}

int tus_pruebas(int op_tp){
	
	struct canales_float Canf1;
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
        
    if (!Leer_imagen(name,&Canf1.red,&Canf1.green,&Canf1.blue,&Canf1.width,&Canf1.height)){
			return 0;
	}
	
	switch(op_tp){
		case 1: //Derivadas Horizontal, Vertical, y Laplaciano:
				aan_mascara(Canf1.red,Canf1.green,Canf1.blue,Canf1.width,Canf1.height);
				printf("\n\nComprueba la imagen para proseguir\n\n");
				system("Derivada_Horizontal.bmp");
				system("Derivada_Vertical.bmp");
				system("Laplaciano.bmp");
				break;
		case 2: //Mascara Combinada:
				aan_mascara_combinada(Canf1.red,Canf1.green,Canf1.blue,Canf1.width,Canf1.height);
				printf("\n\nComprueba la imagen para proseguir\n\n");
				system("Mascara_Combinada.bmp");
				break;
		case 3: //Prueba Imagen Mascara blanco y negro:
				aan_mascara_prueba_negblanc(Canf1.red,Canf1.green,Canf1.blue,Canf1.width,Canf1.height);
				printf("\n\nComprueba la imagen para proseguir\n\n");
				system("Mascara_prueba_negblanc.bmp");
				break;
	}
	
	free(Canf1.red);
	free(Canf1.green);
	free(Canf1.blue);
	
	return 1;
}

//Programa Principal:
int main(){
	
	printf("******************MENU*********************\n");
	printf("*                                         *\n");
	printf("* Opciones: 1. PRUEBAS PREDETERMINADAS    *\n");
	printf("*                                         *\n");
	printf("*           2. TUS PRUEBAS:               *\n");
	printf("*              1. Derivada Horizontal     *\n");
	printf("*                 Derivada Vertical       *\n");
	printf("*                 y Laplaciano            *\n");
	printf("*                                         *\n");
	printf("*              2. Mascara Combianada      *\n");
	printf("*              3. Mascara Negro y Blanco  *\n");
	printf("*                                         *\n");
	printf("*           0. SALIR                      *\n");
	printf("*******************************************\n");
	
	int op,op_tp,cont;
	op = -1;
	while (op != 0){
		printf("\nMENU Opcion: ");
		scanf("%d",&op);
		fflush (stdin);
		switch (op){
			case 0: op = 0;
					break;
			case 1: printf("\n\nEsta prueba se ejecuta una sola vez,\n");
					printf("y finaliza su ejecucion.\n");
					printf("Desea continuar: 1. SI   2.NO\n");
					scanf("%d",&cont);
					while ((cont < 1) || (cont > 2)){
						printf("\n\nElija una respuesta valida: ");
						scanf("%d",&cont);
					}
					if (cont == 1){
						prueba_predeterminada();
						op = 0;
					}
					break;
			case 2: printf("\n\nTUS PRUEBAS: (elija un metodo) --> ");
					scanf("%d",&op_tp);
					while ((op_tp < 1) || (op_tp > 3)){
						printf("\n\nelija un metodo valido --> ");
						scanf("%d",&op_tp);
					}
					fflush (stdin);
					tus_pruebas(op_tp);
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
