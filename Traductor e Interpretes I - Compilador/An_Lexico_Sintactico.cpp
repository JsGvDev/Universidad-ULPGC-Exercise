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
/*     \v        36              \Hex              37                 */
/*     \Oct      38                                                   */
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
#include <iostream>

using namespace std;


char *tokens[] = {"#","BEGIN","CODE","DAT","END","FIL","GT","IF","L","MEM","STAT","STR","RX","RRX",
				  "P","U","S","I","J","F","D","E",
				  "Numero Octal", "Numero Double", "Numero Entero o Hexadecimal u Octal", "Numero Hexadecimal",
				  "ESC: \\","ESC: \"","ESC: \'","ESC: \?","ESC: \a","ESC: \b","ESC: \f","ESC: \n","ESC: \r","ESC: \t","ESC: \v","ESC: Hex","ESC: Oct",
				  "Char","String",
				  "<=",">=","!=","==","&&","||","<",">","!","=","&","|",";","(",")","+","-","~","*","/","%","<<",">>",",","^",":"};


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
/******************************** ERRORES *************************************/
/******************************************************************************/

void error (int n) {
	switch (n) {
		case 0:
			cout << "Error de sinxtaxis, linea --> " << num_linea << endl;
			break;
		case 1:
			cout << "Error: Palabra desconocida, linea --> "  << num_linea << endl;
			break;
		case 2:
			cout << "Error: Numero Hexadecimal mal formado, linea --> " << num_linea << endl;
			break;
		case 3:
			cout << "Error: Numero Real mal formado, linea --> " << num_linea << endl;
			break;
		case 4:
			cout << "Error: Imposible identificar el registro, linea --> " << num_linea << endl;
			break;
		case 5:
			cout << "Char invalido, linea --> " << num_linea << endl;
			break;
		case 6:
			cout << "String mal formada, linea --> " << num_linea << endl;
			break;
		case 7:
			cout << "Error: Numero Octal incorrecto, linea --> " << num_linea << endl;
			break;
		case 8:
			cout << "Error: Numero de registro incorrecto, linea --> " << num_linea << endl;
			break;
		default:
			cout << "Error desconocido, linea --> " << num_linea << endl;
			break;
	}			
}

/******************************************************************************/
/************* QUITA CARACTERES NO SIGNIFICATIVOS PARA EL CODIGO **************/
/******************************************************************************/

int limpiar() {
    if (c == ' ' || c == '\t') {	// espacio o tabulador
        return 1;
    }
    if ((c =='\n') || (c == '\0') ) {   //Salto de linea o Final de línea.
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

/******************************************************************************/
/************* COMPROBAMOS TIPO DE NÚMERO *************************************/
/******************************************************************************/

int tipoNumero() {
	int tipo = -1;
	if (c == '0') {
		sig_c();
		if (isdigit(c)) {
			while (esDigitoOctal(c)) sig_c();
			if (isdigit(c)) {
				error(7);
				return -1;
            }
            return 22;//Octal
        } else {
        	if (c=='X' || c == 'x') {
        		sig_c();
        		if (esDigitoHex(c)) {
        			sig_c();
        			while (esDigitoHex(c)) sig_c();
        		} else {
        			error(2);
		        	return -1;
        		} 
                return 25;//Hexadecimal
            } else {
            	if (c == '.') { // Puede ser un 0 con decimales
            		sig_c();
            		while (isdigit(c)) sig_c();
            		tipo = 23;//double
            	} else tipo = 24; // 0 entero
            }
        }
    } else {
	    while(isdigit(c)) sig_c();
	    if (c == '.') {
	    	sig_c();
	    	while(isdigit(c)) sig_c();
	    	tipo = 23;//double
		} else tipo = 24; //Entero
	}
// Si es entero o double, comprobamos si no le sigue la parte exponencial.
	if ((tipo==24) || (tipo==23)) {
	   	if ((c == 'E') || (c == 'e')) {
	// Primero avanzamos si encontramos un signo + o -
	   		sig_c();
	   		if ((c == '+') || c == '-') sig_c();
	   		if (!isdigit(c)) {
	   			error(3);
	   			return -1;
	   		}
	// Tenemos un digito despues de E o e
			while (isdigit(c)) sig_c();
			return 23; // Si hay exponencial y esta bien formada, el numero es double.
       	}
	}
    return tipo;
}

/******************************************************************************/
/************* COMPROBAMOS QUE ES UN NUMERO CORRECTO **************************/
/******************************************************************************/

int esNum(char c) {
    if (isdigit(c) || (c == '.')) {
        int tipo = tipoNumero();
        if ((tipo == 22) || (tipo == 25)){ //token Entero para Hexadecimal u Octal
    		return 24;
    	}
    	return tipo; // Si no hay parte exponencial devolvemos el tipo del numero base.
	}
	return -1;
}

/******************************************************************************/
/************* COMPROBAMOS ESCAPES VALIDOS ************************************/
/******************************************************************************/

int escapeValido() {
    // Devuelve verdadero si existe:
    // secuencias de escape octal
    // secuencias de escape hexadecimal
    // secuencias de escape simple
    if (esDigitoOctal(c)) {
    	sig_c();
    	if (esDigitoOctal(c)) {
    		sig_c();
    		if (esDigitoOctal(c)) {
    			sig_c();
    			return 1;
    		} else {
    			return 1;
    		}
    	} else {
    		return 1;
    	}
    } else {
    	if ((c == 'x') || (c == 'X')) { // Hexadecimal
    		sig_c();
    		if (esDigitoHex(c)) {
    			sig_c();
    			if (esDigitoHex(c)) {
    				sig_c();
    				return 1;
    			} else {
    				return 1;
    			}
    		} else {
    			return 0;
    		}
    	} else {
    	// Escape simple
    		if ((c == '"') || (c == '?') || (c == 't') || (c == 'a')
    		 || (c == 'b') || (c == 'f') || (c == 'r') || (c == 'v')
    		 || (c == '\'') || (c == '\\') || (c == 'n')) {
    		 	sig_c();
    		 	return 1;
    		 } else {
    		 	return 0;
    		 }
    	}
    }
}

/******************************************************************************/
/*********************** ANALIZADOR LEXICO ************************************/
/******************************************************************************/

int analizadorLexico () {
	Inicio:
    // Limpiamos Blancos, tabulaciones y demas caracteres de formato que no son del código.
    	while (limpiar()) sig_c();
    // Si fin de fichero mandamos mensaje de aviso.
	    if (feof(ff)){
	    	cout << "Final de fichero alcanzado" << endl;
        }
    // Descartamos comentarios
    	if (c=='#'){
    		while ((c != '\n') && !feof(ff)){
	        	sig_c();
	        }
	        goto Inicio;
	    } 
        switch (c){
        	case 'B':
        	// BEGIN
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
            // D, DAT
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
            // E, END
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
            // F, FIL
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
            // GT
                sig_c();
                if (c == 'T') {
                	sig_c();
                	return 6;
                } else {
                	error(1);
                	return -1;
                }
                break;
            case 'I':
            // I, IF
                sig_c();
                if (c == 'F') {
                	sig_c();
                	return 7;
                } else {
                	return 17;
                }
		        break;
            case 'J':
            // J
                sig_c();
		        return 18;
                break;
            case 'L':
            // L
                sig_c();
		        return 8;
                break;
            case 'M':
            // MEM
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
            // P
                sig_c();
		        return 14;
                break;
            case 'S':
            // S, STR, STAT
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
            // U
                sig_c();
		        return 15;
                break;
            case 'R':
            // R, RR
                sig_c();
                if (c == 'R') {
                	sig_c();
                	if (isdigit(c)) {
                		if (c > 52) {    //Se comprueba con el valor ASCII
                			error(8);
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
                			error(8);
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
                if (c=='/'){
                	sig_c();
	    			while ((c != '\n') && !feof(ff)){
	    				sig_c();
	    			}
	    			goto Inicio; // Descartamos comentarios con //loquesea
	    		}
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
                } else if ( c == '<' ) {
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
                } else if ( c == '>' ) {
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
            case '.':
                return esNum(c);
                break;
            // Char
		 	case '\'':
		 		sig_c();
                if (c == '\\') {//es una secuencia de escape
                	sig_c();
                	if (!escapeValido()) {
                		error(5);
                		return -1;
                	}
                	if (c == '\'') { // debe ser comilla de cierre
                		sig_c();
                		return 39;
                	} else {
                		error(5);
                		return -1;
                	} 
                } else {
                	if (c == '\'') {
                		error(5);
                		return -1;
                	} else {
                		sig_c(); // debe ser comilla de cierre
                		if (c == '\'') {
                			sig_c();
                			return 39;
                		} else {
                			error(5);
                			return -1;
                		}
                     }
                }
                break;
             // String
             case '"':
             	char c_ant = c;
                sig_c();
                while (!feof(ff)) {
                	 if (c == '"') {
                	 	if (c_ant != '\\'){
                 			sig_c();
                 			return 40;
                 		}
                 	 }
                 	 c_ant = c;
                 	 sig_c();
                }
                error(6);
                return -1;
                break;
        }
        error (10); //Error inesperado
        return -1;  //Fin del Analizador Lexico
}

/******************************************************************************/
/*********************** ANALIZADOR SINTACTICO ********************************/
/******************************************************************************/


/******************************************************************************/
/******************************* STAT *****************************************/
/******************************************************************************/

int STAT(){
	if (token == 10){
		token = analizadorLexico();
		if (token == 54) {
			token = analizadorLexico();
			if (token == 24) {
				token = analizadorLexico();
				if (token == 55) {
					token = analizadorLexico();
					return 1;
				} else {
					error(0);
					cout << "Falta cierre parentesis" << endl;
					return 0;
				}
			} else {
				error(0);
				cout << "Falta Entero" << endl;
				return 0;
			}
		} else {
			error(0);
			cout << "Falta abre parentesis" << endl;
			return 0;
		}
	} else {
		error(0);
		cout << "Falta Stat" << endl;
		return 0;
	}
}

/******************************************************************************/
/******************************* CODE *****************************************/
/******************************************************************************/

int CODE(){
	if (token == 2){
		token = analizadorLexico();
		if (token == 54) {
			token = analizadorLexico();
			if (token == 24) {
				token = analizadorLexico();
				if (token == 55) {
					token = analizadorLexico();
					return 1;
				} else {
					error(0);
					cout << "Falta cierre parentesis" << endl;
					return 0;
				}
			} else {
				error(0);
				cout << "Falta Entero" << endl;
				return 0;
			}
		} else {
			error(0);
			cout << "Falta abre parentesis" << endl;
			return 0;
		}
	} else {
		error(0);
		cout << "Falta Code" << endl;
		return 0;
	}
}

/******************************************************************************/
/***************************** ETIQUETAS **************************************/
/******************************************************************************/

int ETIQUETAS(){
	if (token == 8){
		token = analizadorLexico();
		if (token == 24) {
			token = analizadorLexico();
			if (token == 66) {
				token = analizadorLexico();
				return 1;
			} else {
				error(0);
				cout << "Falta :" << endl;
				return 0;
			}
		} else {
			error(0);
			cout << "Falta Entero" << endl;
			return 0;
		}
	} else {
		error(0);
		cout << "Falta L" << endl;
		return 0;
	}
}

/******************************************************************************/
/***************************** REGISTROS **************************************/
/******************************************************************************/

int REG(){
	if ((token == 12) || (token == 13)){
		token = analizadorLexico();
		return 1;
	} else {
		return 0; //Registro no valido
	}
}

/******************************************************************************/
/***************************** OP. UNARIO *************************************/
/******************************************************************************/

int OP_UNA(){
	if ((token == 49) || ((token >= 56) && (token <= 58))){
		token = analizadorLexico();
		return 1;
	} else {
		return 0; //no es un operador unario valido
	}
}

/******************************************************************************/
/**************************** OPERADOR BINARIO ********************************/
/******************************************************************************/

int OP_BIN(){
	if (((token >= 41) && (token <= 48)) || ((token >= 59) && (token <= 63))
		|| (token == 51) || (token == 52) || (token == 56) || (token == 57)
		|| (token == 65)) {
		token = analizadorLexico();
		return 1;
	} else {
		return 0; //no es un operador binario valido
	}
}

/******************************************************************************/
/*********************************** CONST ************************************/
/******************************************************************************/

int CONST(){
	if (token == 57){
		token = analizadorLexico();
		if ((token == 23) || (token == 24)){ //Double o Entero
			token = analizadorLexico();
			return 1;
		} else {
			error(0);
			cout << "Numero no valido" << endl;
			return 0;
		}
	} else {
		if ((token == 23) || (token == 24)){ //Double o Entero
			token = analizadorLexico();
			return 1;
		} else {
			if (token == 39){ // Char
				token = analizadorLexico();
				return 1;
			} else {
				error(0);
				cout << "Numero o Char o String no validos" << endl;
				return 0;
			}
		}
	}
}

/******************************************************************************/
/************************************ MEM *************************************/
/******************************************************************************/

int MEM(){
	if ((token >= 14) && (token <= 21)){
		token = analizadorLexico();
		return 1;
	} else {
		error(0);
		cout << "Dato de memoria no valido" << endl;
		return 0;
	}
}

/******************************************************************************/
/*********************************      V      ********************************/
/******************************************************************************/

int V(){
	if (REG()){
		return 1;
	} else {
		if (CONST()){
			return 1;
		} else {
			error(0);
			cout << "Registro o Const no valido" << endl;
			return 0;
		}
	}
}

/******************************************************************************/
/*********************************** EXP **************************************/
/******************************************************************************/

int EXP(){
	if ((token == 49) || (token == 56) || (token == 58)){
		OP_UNA();
		if (V()){
			return 1;
		} else {
			cout << "Expresion mal formada" << endl;
			return 0;
		}
	} else {
		if ((token == 12) || (token == 13) || (token == 23)
			|| (token == 24) || (token == 39)){
				V();
				if (OP_BIN()){
					if(V()){
						return 1;
					} else {
						cout << "Expresion mal formada" << endl;
						return 0;
					}
				}
				return 1;
		} else {
			if (token == 57){
				token = analizadorLexico();
				if (token == 57){
					if (V()){
						return 1;
					} else {
						cout << "Expresion mal formada" << endl;
						return 0;
					}
				} else {
					if ((token == 12) || (token == 13) || (token == 23)
						|| (token == 24) || (token == 39)){
						V();
						if (OP_BIN()){
							if(V()){
								return 1;
							} else {
								cout << "Expresion mal formada" << endl;
								return 0;
							}
						}
						return 1;
					} else {
						error(0);
						cout << "Expresion mal formada" << endl;
						return 0;
					}
				}
			} else {
				error(0);
				cout << "Expresion mal formada" << endl;
				return 0;
			}
		}	
	}
}

/******************************************************************************/
/***************************** DATOS ESTATICOS ********************************/
/******************************************************************************/

int DAT_EST(){
	while ((token == 9) || (token == 5) || (token == 3) || (token == 11)){
		switch (token){
			//MEM
			case 9:
				token = analizadorLexico();
				if (token == 54){
					token = analizadorLexico();
					if (token == 24){
						token = analizadorLexico();
						if (token == 64){
							token = analizadorLexico();
							if (token == 24){
								token = analizadorLexico();
								if (token == 55){
									token = analizadorLexico();
								} else {
									error(0);
									cout << "DAT_EST: Falta cierra parentesis" << endl;
									return 0;
								}
							} else {
								error(0);
								cout << "DAT_EST: Entero no valido" << endl;
								return 0;
							}
						} else {
							error(0);
							cout << "DAT_EST: Falta coma" << endl;
							return 0;
						}
					} else {
						error(0);
						cout << "DAT_EST: Direccion no valida" << endl;
						return 0;
					}
				} else {
					error(0);
					cout << "DAT_EST: Falta abre parentesis" << endl;
					return 0;
				}
				break;
			//FIL
			case 5:
				token = analizadorLexico();
				if (token == 54){
					token = analizadorLexico();
					if (token == 24){
						token = analizadorLexico();
						if (token == 64){
							token = analizadorLexico();
							if (token == 24){
								token = analizadorLexico();
								if (token == 64){
									token = analizadorLexico();
									if ((token == 24) || (token == 39)){
										token = analizadorLexico();
										if (token == 55){
											token = analizadorLexico();
										} else {
											error(0);
											cout << "DAT_EST: Falta cierra parentesis" << endl;
											return 0;
										}
									} else {
										error(0);
										cout << "DAT_EST: Char o Entero no valido" << endl;
										return 0;
									}
								} else {
									error(0);
									cout << "DAT_EST: Falta coma" << endl;
									return 0;
								}
							} else {
								error(0);
								cout << "DAT_EST: Entero no valido" << endl;
								return 0;
							}
						} else {
							error(0);
							cout << "DAT_EST: Falta coma" << endl;
							return 0;
						}
					} else {
						error(0);
						cout << "DAT_EST: Direccion no valida" << endl;
						return 0;
					}
				} else {
					error(0);
					cout << "DAT_EST: Falta abre parentesis" << endl;
					return 0;
				}
				break;
			//DAT
			case 3:
				token = analizadorLexico();
				if (token == 54){
					token = analizadorLexico();
					if (token == 24){
						token = analizadorLexico();
						if (token == 64){
							token = analizadorLexico();
							if (MEM()){
								if (token == 64){
									token = analizadorLexico();
									if (CONST()){
										if (token == 55){
											token = analizadorLexico();
										} else {
											error(0);
											cout << "DAT_EST: Falta cierra parentesis" << endl;
											return 0;
										}
									} else {
										error(0);
										cout << "DAT_EST: Const no valido" << endl;
										return 0;
									}
								} else {
									error(0);
									cout << "DAT_EST: Falta coma" << endl;
									return 0;
								}
							} else {
								cout << "DAT_EST: MEM mal formada" << endl;
								return 0;
							}
						} else {
							error(0);
							cout << "DAT_EST: Falta coma" << endl;
							return 0;
						}
					} else {
						error(0);
						cout << "DAT_EST: Direccion no valida" << endl;
						return 0;
					}
				} else {
					error(0);
					cout << "DAT_EST: Falta abre parentesis" << endl;
					return 0;
				}
				break;
			//STR
			case 11:
				token = analizadorLexico();
				if (token == 54){
					token = analizadorLexico();
					if (token == 24){
						token = analizadorLexico();
						if (token == 64){
							token = analizadorLexico();
							if (token == 40){
								token = analizadorLexico();
								if (token == 55){
									token = analizadorLexico();
								} else {
									error(0);
									cout << "DAT_EST: Falta cierra parentesis" << endl;
									return 0;
								}
							} else {
								error(0);
								cout << "DAT_EST: String no valida" << endl;
								return 0;
							}
						} else {
							error(0);
							cout << "DAT_EST: Falta coma" << endl;
							return 0;
						}
					} else {
						error(0);
						cout << "DAT_EST: Direccion no valida" << endl;
						return 0;
					}
				} else {
					error(0);
					cout << "DAT_EST: Falta abre parentesis" << endl;
					return 0;
				}
				break;
		}
		if (token == 53){
			token = analizadorLexico();
		} else {
			error(0);
			cout << "DAT_EST: Falta ; " << endl;
			return 0;
		}
	}
	return 1;
}

/******************************************************************************/
/***************************** INSTRUCCIONES **********************************/
/******************************************************************************/

int INSTR(){
	switch(token){
		case 7:
			token = analizadorLexico();
			if (token == 54){
				token = analizadorLexico();
				if (EXP()){
					if (token == 55){
						token = analizadorLexico();
						if (token == 6){
							token = analizadorLexico();
							if (token == 54){
								token = analizadorLexico();
								if (V()){
									if (token == 55){
										token = analizadorLexico();
									} else {
										error(0);
										cout << "Falta cierra parentesis" << endl;
										return 0;
									}
								} else {
									cout << "Instruccion mal formada" << endl;
									return 0;
								}
							} else {
								error(0);
								cout << "Falta abre parentesis" << endl;
								return 0;
							}
						} else {
							error(0);
							cout << "Falta GT" << endl;
							return 0;
						}
					} else {
						error(0);
						cout << "Falta cierra parentesis" << endl;
						return 0;
					}
				} else {
					error(0);
					cout << "Instruccion mal formada" << endl;
					return 0;
				}
			} else {
				error(0);
				cout << "Falta abre parentesis" << endl;
				return 0;
			}
			break;
		case 6:
			if (token == 6){
				token = analizadorLexico();
				if (token == 54){
					token = analizadorLexico();
					if (V()){
						if (token == 55){
							token = analizadorLexico();
						} else {
							error(0);
							cout << "Falta cierra parentesis" << endl;
							return 0;
						}
					} else {
						cout << "Instruccion mal formada" << endl;
						return 0;
					}
				} else {
					error(0);
					cout << "Falta abre parentesis" << endl;
					return 0;
				}
			} else {
				error(0);
				cout << "Falta GT" << endl;
				return 0;
			}
			break;
		case 14:
		case 15:
		case 16:
		case 17:
		case 18:
		case 19:
		case 20:
		case 21:
			if (MEM()){
				if (token == 54){
					token = analizadorLexico();
					if (EXP()){
						if (token == 55){
							token = analizadorLexico();
							if (token == 50){
								token = analizadorLexico();
								if(!V()){
									cout << "Instruccion mal formada" << endl;
									return 0;
								}
							} else {
								error(0);
								cout << "Falta signo = " << endl;
								return 0;
							}
						} else {
							error(0);
							cout << "Falta cierra parentesis" << endl;
							return 0;
						}
					} else {
						cout << "Instruccion mal formada" << endl;
						return 0;
					}
				} else {
					error(0);
					cout << "Falta abre parentesis" << endl;
					return 0;
				}
			} else {
				cout << "Instruccion mal formada" << endl;
				return 0;
			}
			break;
		case 12:
		case 13:
			if (REG()){
				if(token == 50){
					token = analizadorLexico();
					if ((token >= 14) && (token <= 21)){
						token = analizadorLexico();
						if (token == 54){
							token = analizadorLexico();
							if (EXP()){
								if (token == 55){
									token = analizadorLexico();
								} else {
									error(0);
									cout << "Falta cierra parentesis" << endl;
									return 0;
								}
							} else {
								cout << "Instruccion mal formada" << endl;
								return 0;
							}
						} else {
							error(0);
							cout << "Falta abre parentesis" << endl;
							return 0;
						}
					} else {
						if(!EXP()){
							cout << "Instruccion mal formada" << endl;
							return 0;
						}
					}
				} else {
					error(0);
					cout << "Falta signo = " << endl;
					return 0;
				}
			} else {
				error(0);
				cout << "Instruccion mal formada" << endl;
				cout << "Registro no valido" << endl;
				return 0;
			}
			break;
	}
	if (token == 53){
		token = analizadorLexico();
		return 1;
	} else {
		error(0);
		cout << "Instruccion mal formada" << endl;
		cout << "Falta signo ; " << endl;
		return 0;
	}
}

/******************************************************************************/
/*********************** ETIQUETAS E INSTRUCCIONES ****************************/
/******************************************************************************/

int ETIQ_e_INST(){
	while (((token >= 6) && (token <= 8)) || (token == 12) || 
		   (token == 13) || ((token >= 14) && (token <= 21))){
		if (token == 8){
			if (!ETIQUETAS()){
				cout << "Etiqueta mal formada" << endl;
				return 0;
			}
		} else {
			if (!INSTR()){
				cout << "Llamada a instruccion erronea" << endl;
				return 0;
			}
		}
	}
	return 1;
}

/******************************************************************************/
/***************************** PROGRAMA EN Q **********************************/
/******************************************************************************/

int PROG_Q(){ // arreglar la entrada y salida del programa principal.
	if (token == 1){
		token = analizadorLexico();
		do {
			if (ETIQ_e_INST()){
				if (token == 4){
					break;
				} else {
					if (STAT()){
						if(DAT_EST()){
							if (token == 4){
								break;
							} else {
								if(!CODE()){
									cout << "Programa con fallos en Code" << endl;
									return 0;
								}
							}
						} else {
							cout << "Programa con fallos en Datos Estaticos" << endl;
							return 0;
						}
					} else {
						cout << "Programa con fallos en Stat" << endl;
						return 0;
					}
				}
			} else {
				cout << "Programa con fallos en Etiquetas e Instrucciones" << endl;
				return 0;
			}
		} while (1); //verdadero
		return 1;
	} else {
		error(0);
		cout << "Programa con fallos, falta BEGIN al comenzar" << endl;
		return 0;
	}
}

// *********************************************************************

int main () {
// Abrimos el fichero fuente
	ff = fopen("fuente.txt", "r");

	if (ff == NULL) {
		cout << "Se ha producido un error al abrir el fichero fuente. " << endl;
		return 0;
	}
	
// se inicializan las variables
	num_linea = 1;
	sig_c();
	token = analizadorLexico();
	if (PROG_Q()){
		cout << endl << "FIN DEL ANALISIS LEXICO_SINTACTICO" << endl;
	} else {
		cout << endl << "PROGRAMA CON ERRORES" << endl;
	}
		
	system("Pause");
	return 0;
}
