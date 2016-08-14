#include "Pract3_aan.h"

int main(){
		
	float *Presa;
	float *Cazador;
	float a,b,d,e,f,Pi,Ci,dt;
	int Niter, i,j;
	
	FILE *fich;
	char caso[]={"caso_00.txt"};
	
	for (i=1; i<7; i++){
		switch(i){
			//oscilen hasta una situación de equilibrio
			case 1: a=0.2; b=0.00015; d=0.0001; 
					e=0.1; f=0.00015; dt=0.1;
					Pi=1000; Ci=200; Niter=1000;
					caso[6] = '1';					
					break;
			//depredadores se extingan y sobrevivan las presas
			case 2: a=0.5; b=0.0005; d=0.001; 
					e=0.2; f=0.0002; dt=0.1;
					Pi=1000; Ci=200; Niter=600;
					caso[6] = '2';
					break;
			//desaparezcan ambas
			case 3: a=0.5; b=0.005; d=0.0001; 
					e=0.2; f=0.002; dt=0.1;
					Pi=1000; Ci=200; Niter=400;
					caso[6] = '3';
					break;
			//valores grandes de incremento temporal		
			case 4: a=0.2; b=0.00015; d=0.0001; 
					e=0.1; f=0.00015; dt=5;
					Pi=1000; Ci=200; Niter=1000;
					caso[5] = '4';
					caso[6] = 'a';
					break;
			
			case 5: a=0.5; b=0.0005; d=0.001; 
					e=0.2; f=0.0002; dt=1.7;
					Pi=1000; Ci=200; Niter=50;
					caso[5] = '4';
					caso[6] = 'b';
					break;
			
			case 6: a=0.5; b=0.005; d=0.0001; 
					e=0.2; f=0.002; dt=1;
					Pi=1000; Ci=200; Niter=50;
					caso[5] = '4';
					caso[6] = 'c';
					break;
		}
		Presa = (float *) malloc (Niter*sizeof(float));
		Cazador = (float *) malloc (Niter*sizeof(float));
		
		if ((Presa == NULL) || (Cazador == NULL)){
			printf("Problemas con la memoria(memoria no disponible)/n");
			return 0;
		}
		
		Lotka_Volterra(a,b,d,e,f,Pi,Ci,Presa,Cazador,dt,Niter);
		
		fich = fopen(caso, "w");
		if(!fich) {
			printf("El fichero %s no puede ser creado.\n", caso);
			return 0;
		}
		fprintf (fich, "Presa   Cazador\n");
		for (j=0; j<Niter; j++){
			fprintf (fich, "%0.f       %0.f\n", Presa[j], Cazador[j]);
		}
		free(Presa);
		free(Cazador);
		fclose(fich);		
	}	
	
	//Interactividad
	int cont;
	printf("¿ Desea ver las graficas ? 1. SI   2.NO\n");
	scanf("%d",&cont);
	fflush (stdin);
	while ((cont < 1) || (cont > 2)){
			printf("\n\nElija una respuesta valida: ");
			scanf("%d",&cont);
			fflush (stdin);
	}
	if (cont == 1) {
		system("caso_01.jpg");
		system("caso_02.jpg");
		system("caso_03.jpg");
		system("caso_4a.jpg");
		system("caso_4b.jpg");
		system("caso_4c.jpg");
	}
	
	printf("\n\n\nFIN\n\n");
	system("PAUSE");
	return 0;
}
