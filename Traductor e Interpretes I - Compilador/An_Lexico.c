////////////////////////TABLA DE CODIGOS////////////////////////////////
/*     BEGIN     1             L                  8                   */
/*     CODE      2             MEM                9                   */
/*     DAT       3             STAT               10                  */
/*     END       4             STR                11                  */
/*     FIL       5             RX                 12                  */
/*     GT        6             RRX                13                  */
/*     IF        7                                                    */
/*                 TIPO DE DATO DE DAT(d,c,w)                         */
/*     P         14             U                  15                 */
/*     S         16             I                  17                 */
/*     J         18             F                  19                 */
/*     D         20             E                  21                 */
/*         NUMEROS OCTALES, REALES, HEXADECIMALES Y ENTEROS           */
/*     Nºoctal   22             NºDouble           23                 */
/*     NºEntero  24             NºHexadecimal      25                 */
/*                      Secuencias de escape                          */
/*     \\        26              \"                27                 */
/*     \'        28              \?                29                 */
/*     \a        30              \b                31                 */
/*     \f        32              \n                33                 */
/*     \r        34              \t                35                 */
/*     \v        36              \Hex              25                 */
/*     \Oct      22                                                   */
/*                         Tipos datos ristra/char                    */
/*     Char      39              String            40                 */
/*                         Resto de tokens                            */
/*     <=        41              >=                42                 */
/*     !=        43              ==                44                 */
/*     &&        45              ||                46                 */
/*     <         47              >                 48                 */
/*     !         49              =                 50                 */
/*     &         51              |                 52                 */
/*     ;         53              (                 54                 */
/*     )         55              +                 56                 */
/*     -         57              ~                 58                 */
/*     *         59              /                 60                 */
/*     %         61              <<                62                 */
/*     >>        63              ,                 64                 */
/*     ^         65              :                 66                 */
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <ctype.h>



FILE *ff;

// Token devuelto por el analizador lexico.
int token;
// Numero de la linea tratada, para indicar donde se producen los errores.
int num_linea;
// Caracter a analizar.
char c;
// Siguiente carácter.
void sig_c() {
	c = fgetc(ff);
}




/******************************************************************************/
/************* QUITA CARACTERES NO SIGNIFICATIVOS PARA EL CODIGO **************/
/******************************************************************************/

int limpiar() {
    if (c == ' ' || c == '\t') {
        return 1;
    }
    if ((c =='\n') || (c == '\0') ) {   //Final de línea.
        num_linea++;
	return 1;
    }
    return 0;
}

/******************************************************************************/
/************* COMPROBAMOS QUE SEA UN BEGIN ***********************************/
/******************************************************************************/

int esBegin() {
	char *begin = "BEGIN";
	int i = 0;
	while (begin[i] != '\0') {
		if (c != begin[i]) return 0;
		sig_c();
		i++;
	}
	// Si efectivamente el es el token BEGIN sale con actual apuntando al siguiente caracter despues del token.
	// En caso de que no, sale con actual apuntando al primer caracter que no coincide con el de la palabra BEGIN.
	return 1;
}

/******************************************************************************/
/************* COMPROBAMOS QUE SEA UN CODE ************************************/
/******************************************************************************/
int esCode() {
	char *code = "CODE";
	int i = 0;
	while (code[i] != '\0') {
		if (c != code[i]) return 0;
		sig_c();
		i++;
	}
	return 1;
}

/******************************************************************************/
/************* COMPROBAMOS QUE SEA UN NÚMERO **********************************/
/******************************************************************************/
int esDigitoOctal(char c) {
	if (isdigit(c) && (c < 56)) return 1;
	return 0;
}

int esDigitoHex(char c) {
        if (isdigit(c)) return 1;
        switch (c) {
            case 'a':
            case 'b':
            case 'c':
            case 'd':
            case 'e':
            case 'f':
            case 'A':
            case 'B':
            case 'C':
            case 'D':
            case 'E':
            case 'F':
                return 1;
                break;
            default:
                return 0;
        }
}

int tipoNumero() {
	if (c == '0') {
            sig_c();
            if (isdigit(c)) {
                while (esDigitoOctal(c)) sig_c();
		if (isdigit(c)) {
		    error(7);
		    return -1;
                }
		return 22;
            } else {
                if (c=='X' || c == 'x') {
                    sig_c();
		    if (esDigitoHex(c)) {
                        sig_c();
			while (esDigitoHex(c)) sig_c();
                        return 25;
                    } else {
		        error(2);
			return -1;
                    }
                } else {
		    if (c == '.') { // Puede ser un 0 con decimales
		        sig_c();
			while (isdigit(c)) sig_c();
                        return 23;
                    } else return 22; // 0 entero
                }
            }
	} else {
	    while(isdigit(c)) sig_c();
                if (c == '.') {
		    sig_c();
                    while(isdigit(c)) sig_c();
                    return 23;
		} else return 22;
	}
	return -1;
}
 ////////Falta esto
int esNum(char c) {
        if (isdigit(c)) {
            int tipo = tipoNumero();
			// Si es entero o real, comprobamos si no le sigue la parte exponencial.
			if ((tipo==22) || (tipo==23)) {
				if ((caracter=='E') || (caracter == 'e')) {
					// Primero avanzamos si encontramos un signo + o -
					siguienteCaracter();
					if ((caracter=='+') || caracter=='-') siguienteCaracter();
					if (!isdigit(caracter)) {
						error(3);
						return -1;
					}
					// Tenemos un digito despuŽs de E o e
					int tipoExp = tipoNumero();
					if ((tipoExp != 22)) {
						error(3);
						return -1;
					}
					return 23; // Si hay exponencial y est‡ bien formada, el numero es real.
				}
			}
			return tipo; // Si no hay parte exponencial devolvemos el tipo del numero base.
		}

		// . de decimal sin cifras previas, debe tener cifras despuŽs
		if (caracter == '.') {
			siguienteCaracter();
			if (isdigit(caracter)) {
				siguienteCaracter();
				while (isdigit(caracter)) siguienteCaracter();
				if ((caracter=='E') || (caracter=='e')) {
					// Avanzamos si encontramos signo + o -
					siguienteCaracter();
					if ((caracter=='+') || caracter=='-') siguienteCaracter();
					if (!isdigit(caracter)) {
						error(3);
						return -1;
					}
					// Tenemos un digito despuŽs de E o e
					int tipoExp = tipoNumero();
					if ((tipoExp != 22)) {
						error(3);
						return -1;
					}
				}
				return 23;
			} else {
				error(3);
				return -1;
			}
		}



 //////////////hasta aquí




int analizadorLexico () {
    while (!feof(ff)) {
        // Blancos, tabulaciones y dem‡s caracteres de formato que no son del código.
       	// Avanzamos mientras no aparezca algún caracter del código propiamente dicho.
      	while (limpiar()) sig_c();
       	    // Si tras salir del bucle es el fin de fichero salimos del bucle para retornar.
	    if (feof(ff)){
                cout << "Final de fichero alcanzado" << endl;
	        break;
            }
            // Descartamos comentarios
            if (c=='#') {
	        while ((c != '\n') && !feof(ff)){
		    sig_c();
                }
                //return 0;
            }
            switch (c){
                 case 'B':
                 // Si es B ha de ser BEGIN
		     if (esBegin()) return 1;
		     error(1);
		     return -1;
                     break;
                 case 'C':
                 // CODE
    	             if (esCode()) return 2;
                     error(1);
		     return -1;
                     break;
                 case 'D':
                     sig_c();
                     if (c == 'A') {
		         sig_c();
			 if (c == 'T') {
			     sig_c();
			     return 3;
                         } else {
			     error(1);
			     return -1;
                         }
                     } else return 20;
		     break;
                 case 'E':
                     sig_c();
                     if (c == 'N') {
		         sig_c();
			 if (c == 'D') {
			     sig_c();
			     return 4;
                         } else {
			     error(1);
			     return -1;
                         }
                     } else return 21;
		     break;
                 case 'F':
                     sig_c();
                     if (c == 'I') {
		         sig_c();
			 if (c == 'L') {
			     sig_c();
			     return 5;
                         } else {
			     error(1);
			     return -1;
                         }
                     } else return 19;
		     break;
                 case 'G':
                     sig_c();
		     if (c == 'T') {
		         sig_c();
			 return 6;
                     }
		     else {
		         error(1);
			 return -1;
                     }
                     break;
                 case 'I':
                     sig_c();
                     if (c == 'F') {
		         sig_c();
			 return 7;
                     } else {
                         return 17;
                     }
		     break;
                 case 'J':
                        sig_c();
			return 18;
                        break;
                 case 'L':
                        sig_c();
			return 8;
                        break;
                 case 'M':
                     sig_c();
                     if (c == 'E') {
		         sig_c();
			 if (c == 'M') {
			     sig_c();
			     return 9;
                         } else {
			     error(1);
			     return -1;
                         }
                     } else {
                         error(1);
                         return -1;
                     }
		     break;
                 case 'P':
                        sig_c();
			return 14;
                        break;
                 case 'S':
                        sig_c();
			if (c == 'T') {
                            sig_c();
			    if (c=='R') {
			        sig_c();
				return 11;
                            } else {
			        char *stat = "AT";
			        int i=0;
			        while (stat[i] != '\0') {
			            if (stat[i] != c) {
				        error(1);
				        return -1;
                                    }
				    sig_c();
				    i++;
			        }
			        return 10;
			    }
			} else return 16;
                        break;
                 case 'U':
                        sig_c();
			return 15;
                        break;
                 case 'R':
                        sig_c();
			if (c == 'R') {
			    sig_c();
                            if (isdigit(c)) {
                                if (c > 52) {    //Se comprueba con el valor ASCII
                                    error(1222);
                                    return -1;
                                } else {
                                    sig_c();
                                    return 13;
                                }
                            } else {
			        error(4);
				return -1;
                            }
			} else {
                            if (isdigit(c)) {
			        if (c > 56) {    //Se comprueba con el valor ASCII
                                    error(1222);
                                    return -1;
                                } else {
                                    sig_c();
                                    return 12;
                                }
                            } else {
			        error(4);
				return -1;
                            }
                        }
                        break;
                 case ';':
                        sig_c();
			return 53;
                        break;
                 case '(':
                        sig_c();
			return 54;
                        break;
                 case ')':
                        sig_c();
			return 55;
                        break;
                 case '+':
                        sig_c();
			return 56;
                        break;
                 case '-':
                        sig_c();
			return 57;
                        break;
                 case '~':
                        sig_c();
			return 58;
                        break;
                 case '*':
                        sig_c();
			return 59;
                        break;
                 case '/':
                        sig_c();
			return 60;
                        break;
                 case '%':
                        sig_c();
			return 61;
                        break;
                 case ',':
                        sig_c();
			return 64;
                        break;
                 case '^':
                        sig_c();
			return 65;
                        break;
                 case ':':
                        sig_c();
			return 66;
                        break;
                 case '!':
                        sig_c();
		        if (c == '=') {
                            sig_c();
			    return 43;
                        } else {
                            return 49;
                        }
                        break;
                 case '&':
                        sig_c();
		        if (c == '&') {
                            sig_c();
			    return 45;
                        } else {
                            return 51;
                        }
                        break;
                 case '=':
                        sig_c();
		        if (c == '=') {
                            sig_c();
			    return 44;
                        } else {
                            return 50;
                        }
                        break;
                 case '|':
                        sig_c();
		        if (c == '|') {
                            sig_c();
			    return 46;
                        } else {
                            return 52;
                        }
                        break;
                 case '<':
                     sig_c();
                     if (c == '=') {
		         sig_c();
                         return 41;
                     } else if ( c == '<' {
		         sig_c();
                         return 62;
                     } else {
                         return 47;
                     }
		     break;
                 case '>':
                     sig_c();
                     if (c == '=') {
		         sig_c();
                         return 42;
                     } else if ( c == '>' {
		         sig_c();
                         return 63;
                     } else {
                         return 48;
                     }
		     break;
                 case '0':
                 case '1':
                 case '2':
                 case '3':
                 case '4':
                 case '5':
                 case '6':
                 case '7':
                 case '8':
                 case '9':
                     esNum();




            }
    }
}
