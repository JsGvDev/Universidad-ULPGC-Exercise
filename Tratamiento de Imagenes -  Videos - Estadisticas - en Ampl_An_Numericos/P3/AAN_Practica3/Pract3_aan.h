#ifndef PRACT3_AAN_H_
#define PRACT3_AAN_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// dP/dt = a*P - b*P*C - d*P^2  (Presa(P))
// dC/dt = -e*C + f*P*C       (Cazador(C))
// P0 y C0 --> poblaciones iniciales
// a,b,d   --> factores que influyen en las presas
// e,f     --> factores que influyen en los cazadores
void Lotka_Volterra (float a, float b, float d, float e, float f, float P0, float C0,
					 float *Presa, float *Cazador, float dt, int NIter){

	int i;
	
	Presa[0] = P0;
	Cazador[0] = C0;
	for (i=1; i<NIter; i++){
		Presa[i] = Presa[i-1] + dt*((a*Presa[i-1])-(b*Presa[i-1]*Cazador[i-1])-(d*(Presa[i-1]*Presa[i-1])));
		Cazador[i] = Cazador[i-1] + dt*((-e*Cazador[i-1])+(f*Presa[i-1]*Cazador[i-1]));
		
		//redondeo
		if (Presa[i]  < 0.5) Presa[i] = 0;		
		if (Cazador[i] < 0.5) Cazador[i] = 0;
				
	}
	return;
}

#endif /*PRACT3_AAN_H_*/
