#include "fstream.h"

// Alfabetos para el mensaje
  char alfabetom[]="ABCDEFGHIJKLMNÑOPQRSTUVWXYZ";
  char alfabetoc[]="                           ";
  char alfabetov[]="ABCDEFGHIJKLMNÑOPQRSTUVWXYZabcdefghijklmnñopqrstuvwxyzáéíóúÁÉÝÓÚ";
  char alfabetol[]="ABCDEFGHIJKLMNÑOPQRSTUVWXYZABCDEFGHIJKLMNÑOPQRSTUVWXYZAEIOUAEIOU";
  char criptograma[3000];
  char *mensaje;
  char mat_playfair[5][5];
  bool okk;
  int primos[100];
  int pares[100];
  int resto[100];

// Declaración de funciones

  char* Men_prep(char* Mensaje_entrada);
  void alfabeto_c(char *alfabeto, int decimacion, int desplazamiento, int modulo);
  int valor(char letra, char* alfabeto);
  void cifrar(char* alfam,char *alfac,char *mensaje,char *criptograma);
  int mcd(int a, int b);
  void cifra_Vig(char *clave,char* mensaje,char* criptograma, int modulo,int Conmut);
  char* Veri_clave(char* clave);
  void cifra_Beauf(char *clave, char *mensaje, char *criptograma, int modulo, int Conmut);
  void cifra_play(char *clave, char *mensaje, int control);
  bool transposicion_grupo(char *clave,char* mensaje,char* criptograma,bool encriptar);
  void transposicion_series (char* mensaje,char* criptograma,int factor);
  void calcula_resto(int p, int CantPrim, int CantPar);
  int calcula_pares(int p);
  int calcula_primos(int p);
  void transposicion_filas (char* mensaje,char* criptograma,int filas,int factor);
  void transposicion_columnas (char* mensaje,char* criptograma,int columnas,int factor);
  bool encriptaarchivo(char* alfam, char *alfac,char* archivoin,char* archivoout,
  char * clave,int tipo);
  int LongitudCadena (char *cadena);
  char* to_mayus(char* str);



// Fución que nos devuelve el mensaje sin carácteres extraños y nos lo
// separa en grupos de cinco.
  char* Men_prep(char* Mensaje_entrada){
      char *str=Mensaje_entrada;
      char *criptos;
      criptos = new char[3000];
      int i=0;
      int j=0;

        while (str[i] != '\0'){
                if (((str[i] >= 'A') && (str[i] <= 'Z')) || (str [i] == 'Ñ')){
			criptos[j] = str[i];
                        j++;

		} else if (str [i] == 'Á'){
                        criptos[j] = 'A';
                        j++;

                } else if (str [i] == 'É'){
                        criptos[j] = 'E';
                        j++;

                } else if (str [i] == 'Í'){
                        criptos[j] = 'I';
                        j++;

                } else if (str [i] == 'Ó'){
                        criptos[j] = 'O';
                        j++;

                } else if (str [i] == 'Ú'){
                        criptos[j] = 'U';
                        j++;

                } else if (str [i] == 'Ä'){
                        criptos[j] = 'A';
                        j++;

                } else if (str [i] == 'Ë'){
                        criptos[j] = 'E';
                        j++;

                } else if (str [i] == 'Ï'){
                        criptos[j] = 'I';
                        j++;

                } else if (str [i] == 'Ö'){
                        criptos[j] = 'O';
                        j++;

                } else if (str [i] == 'Ü'){
                        criptos[j] = 'U';
                        j++;

                }
		i++;
        }
        criptos[j]= '\0';
  return criptos;
  }

// Verifica la clave.
  char* Veri_clave(char* clave){
      char *str=clave;
      char *pass;
      pass = new char[500];
      int i=0;
      int j=0;

        while (str[i] != '\0'){
                if (((str[i] >= 'A') && (str[i] <= 'Z')) || (str [i] == 'Ñ')){
			pass[j] = str[i];
                        j++;

		} else if (str [i] == 'Á'){
                        pass[j] = 'A';
                        j++;

                } else if (str [i] == 'É'){
                        pass[j] = 'E';
                        j++;

                } else if (str [i] == 'Í'){
                        pass[j] = 'I';
                        j++;

                } else if (str [i] == 'Ó'){
                        pass[j] = 'O';
                        j++;

                } else if (str [i] == 'Ú'){
                        pass[j] = 'U';
                        j++;

                } else if (str [i] == 'Ä'){
                        pass[j] = 'A';
                        j++;

                } else if (str [i] == 'Ë'){
                        pass[j] = 'E';
                        j++;

                } else if (str [i] == 'Ï'){
                        pass[j] = 'I';
                        j++;

                } else if (str [i] == 'Ö'){
                        pass[j] = 'O';
                        j++;

                } else if (str [i] == 'Ü'){
                        pass[j] = 'U';
                        j++;

                } else if ((str [i] >= '0') && (str [i] <= '9')){
                        pass[j] = str[i];
                        j++;
                }

		i++;
        }
        pass[j]= '\0';
  return pass;
  }


// Construye el alfabeto en el que se va a generar el criptograma.
  void alfabeto_c(char *alfabeto, int decimacion, int desplazamiento, int modulo){
    int aux;
    for(int i=0;i<28;i++)
    {
        aux=valor(alfabetom[i],alfabetom);
        aux=((aux*decimacion)+ desplazamiento);
            /* Se calcula el módulo 27 teniendo en cuenta si el número es
                positivo o negativo                                    */
        if(aux<0)
        {
            aux=modulo-(aux*-1)%modulo;
        }
        else
        {
            aux=aux%modulo;
        }
        alfabeto[i]=alfabetom[aux];
    }
}

// Devuelve el código numérico de la letra pasada como parámetro, en el
// alfabeto pasado como parámetro
int valor(char letra, char* alfabeto)
{
    int i=0;
    while(alfabeto[i]!=letra)
    {
        i++;
        if(i>26) break;
    }
    return i;
}

//  Sirve tanto para crifrar como para descrifrar un mensaje con el método
//  de sustitución afín.
void cifrar(char* alfam,char *alfac,char *mensaje,char *criptograma)
{
    int i=0;
    int j=0;
    int aux;
    while(mensaje[i]!=0){               // Hasta eñ final de la cadena
        aux=valor(mensaje[i],alfam);
        if(aux<27){                     // Si el caracter pertenece al alfabeto
            criptograma[j]=alfac[aux];  // Se traduce de un alfabeto a otro
            j++;
            if((j+1)%6==0)
            {
                criptograma[j]=' ';
                j++;
            }
        }
        i++;
    }
    criptograma[j]='\0';
}

//------------------------------------------------------------------------------
// Calcula el máximo común divisor de dos números
//------------------------------------------------------------------------------

int mcd(int a, int b) {
    if(a < b) return mcd(b,a);
    if(b==0) return a;
    return mcd(b, a % b);
}

//---------------------------------------------------------------------------
// Cifrado por el método de Vigenere
// Conmut se ustiliza para indicar si se va a cifrar o descifrar.
//       1.- Cifrado
//       -1.- Descifrado
//---------------------------------------------------------------------------
void cifra_Vig(char *clave,char* mensaje,char* criptograma, int modulo,int Conmut)
{
    char *cl;
    // Tanto la clave como el mensaje en claro ya se han limpiado antes de
    // invocar a esta función
    // En primer lugar se cuentan los caracteres de la clave y se almacenan en lon
    int i=0;
    int lon=0;
    cl = clave;
    while(cl[i]!='\0')
    {
        i++;
    }
    lon = i;
    // Vector de enteros que contenga los distintos valores de ci a restar a mi
    int* valores = new int[lon];
    for(i=0;i<lon;i++) valores[i]=valor(cl[i],alfabetom)*Conmut;
    // Se procesa el mensaje
    int aux;
    int j=0;
    int k=0;
    i=0;
    while(mensaje[i]!=0)       // Hasta el final de la cadena
    {
        aux=(valor(mensaje[i],alfabetom)+ valores[k%lon]);
        if(aux<0)
        {
            aux=modulo-(aux*-1)%modulo; // MODULO NEGATIVO
        }
        else
        {
            aux=aux%modulo;             // MODULO POSITIVO
        }
        criptograma[j]=alfabetom[aux];
        j++;
        k++;
        if((j+1)%6==0)
        {
            criptograma[j]=' ';
            j++;
        }
        i++;
        if (mensaje[i] == ' '){
                i++;
                }

    }
    criptograma[j]='\0';
    delete [] valores;
}
       
//---------------------------------------------------------------------------
// Cifrado por el método de Beaufort
// Conmut se ustiliza para indicar si se va a cifrar o descifrar.
//       1.- Cifrado y Descifrado
//---------------------------------------------------------------------------
void cifra_Beauf(char *clavebeauf,char* mensaje,char* criptograma, int modulo,int Conmut)
{
    char *cl;
    // Tanto la clave como el mensaje en claro ya se han limpiado antes de
    // invocar a esta función
    // En primer lugar se cuentan los caracteres de la clave y se almacenan en lon
    int i=0;
    int lon=0;
    cl = clavebeauf;
    while(cl[i]!='\0')
    {
        i++;
    }
    lon = i;
    // Vector de enteros con los distintos valores de ci a restar a mi
    int* valores = new int[lon];
    for(i=0;i<lon;i++)
    {
        valores[i]=valor(cl[i],alfabetom)*Conmut;
    }
    // Se procesa el mensaje
    int aux;
    int j=0;
    int k=0;
    i=0;
    while(mensaje[i]!=0)     // Hasta el final de la cadena
    {
        aux=(valores[k%lon] - valor(mensaje[i],alfabetom));
        if(aux<0)
        {
            aux=modulo-(aux*-1)%modulo; // MODULO NEGATIVO
        }
        else
        {
            aux=aux%modulo;             // MODULO POSITIVO
        }
        criptograma[j]=alfabetom[aux];
        j++;
        k++;
        if((j+1)%6==0){
            criptograma[j]=' ';
            j++;
        }
        i++;
        if (mensaje[i] == ' '){
            i++;
        }
    }
    criptograma[j]='\0';
    delete [] valores;
}


//---------------------------------------------------------------------------
// Cifrado por el método de Playfair
// Control se ustiliza para indicar si se va a cifrar o descifrar.
//       1.- Cifrado
//       2.- Descifrado
//---------------------------------------------------------------------------
void cifra_play(char *claveplay, char *msg, int control)
{

    AnsiString passplay = claveplay;
    int tampass = passplay.Length (); //metodo que te dice el tamaño de una cadena
    char* cl = new char[tampass+1]; //  creas tu variable char
    strcpy (cl, passplay.c_str ());  // pasamos de AnsiString a char *

    int m;
    int i=0;
    int j;
    int contad=1;
    bool repet;

    while(msg[i]!='\0')
    {
        i++;
    }
    char* m_aux = new char[i+1];
    char* m_aux1 = new char[i+1];
    char cl_aux1[25];   // Vector para almacenar la clave mas el alfabeto
    i=0;
    while(cl[i]!='\0')
    {
        i++;
    }
    m = i;
    if((cl[0] != 'J') & (cl[0] != 'Ñ'))
        cl_aux1[0] = cl[0];
    else
    {
        if(cl[0] == 'J') cl_aux1[0] = 'I';
        else cl_aux1[0] = 'N';
    }

    i = 1;
    while(i < m)  //Se recorre toda la clave original
    {
        repet = false;
        if(cl[i] == 'J') cl[i] == 'I';
        if(cl[i] == 'Ñ') cl[i] == 'N';
        for(j=i-1;j>=0;j--)  // Se compara el carcter actual con los ya almacenados
        {
            if(cl[i]==cl_aux1[j]) repet = true;
        }
        if(repet == false)   // Si dicho caracter no está, no se añade
        {
            cl_aux1[contad] = cl[i];
            contad++;
        }
        i++;
    }
    for(int n = 0;n<27;n++)  //Se recorre el alfabeto
    {
        if((alfabetom[n] != 'J') & (alfabetom[n] != 'Ñ'))
        {
            repet = false;
            for(j = contad-1;j >= 0;j--)
            {
                if(alfabetom[n] == cl_aux1[j])
                {
                    repet=true;
                }
            }
            if(repet == false)   // Si dicho caracter no está, se añade
            {
                cl_aux1[contad] = alfabetom[n];
                contad++;
            }
        }
    }
    cl_aux1[contad] = '\0';
    //Ahora se genera la tabla de Playfair
    int i1 = 0;
    int i2 = 0;
    contad = 0;
    while(cl_aux1[contad] != '\0')
    {
        for(contad = 0;contad < 25;contad++)
        {
            mat_playfair[i1][i2] = cl_aux1[contad];
            if(i2 == 4)
            {
                i2=0;
                i1++;
            }
            else
                i2++;
        }
    }

    i = 0;
    j = 0;
    while(msg[i] != '\0')
    {
        if((msg[i] != msg[i+1]) &  (msg[i+1] != '\0')) // Dos caracteres distintos
        {
            m_aux[j] = msg[i];     //Los copia
            m_aux[j+1] = msg[i+1];
            i = i + 2;
            j = j + 2;
        }
        else
        {
            if(msg[i+1] != '\0')     //Si son iguales
            {
                m_aux[j] = msg[i];   //Copia el primero
                m_aux[j+1] = 'X';    //Introduce una 'X' en el siguiente
                j = j + 2;
            }
            else
            {
                m_aux[j] = msg[i];   //Si es el último, lo copia
                j = j + 1;
                if(i%2 != 1)
                {
                    m_aux[j] = 'X';  //Si el nº de caracteres no es par, se añade una 'X'
                    j = j + 1;
                }
            }
            i++;                      
        }                             
    }
    int x1 = 0;
    int x2 = 0;
    int y1 = 0;
    int y2 = 0;
    int k=0;
    bool sig1 = true;
    bool sig2 = true;
    m_aux1[0] = ' '; 
    //El siguiente bucle captura las coordenadas de cada letra en la tabla
    for (m = 0; m < j;m+=2)
    {
        for(i = 0;i < 5; i++)
        {
            for(k = 0;k < 5; k++)
            {
                if((mat_playfair[i][k] == m_aux[m]) & sig1)
                {
                    x1 = i;
                    y1 = k;
                    sig1 = false;
                }
                if((mat_playfair[i][k] == m_aux[m+1]) & sig2)
                {
                    x2 = i;
                    y2 = k;
                    sig2 = false;
                }   
            }
        }
        sig1 = true;
        sig2 = true;
        if (control == 1) //Codificación
        {
            if((x1 == x2) |	(y1 == y2))
            {
                if(x1 == x2)
                {
                    if(y1 <4)
                        m_aux1[m] = mat_playfair[x1][y1+1];
                    else
                        m_aux1[m] = mat_playfair[x1][0];
                    if(y2 <4)
                        m_aux1[m+1] = mat_playfair[x1][y2+1];
                    else
                        m_aux1[m+1] = mat_playfair[x1][0];
                }
                else
                {
                    if(x1 <4)
                        m_aux1[m] = mat_playfair[x1+1][y1];
                    else
                        m_aux1[m] = mat_playfair[0][y1];
                    if(x2 <4)
                        m_aux1[m+1] = mat_playfair[x2+1][y1];
                    else
                        m_aux1[m+1] = mat_playfair[0][y1];
                }
            }
            else
            {
                m_aux1[m] = mat_playfair[x1][y2];
                m_aux1[m+1] = mat_playfair[x2][y1];
            }
        }
        else  //Decodificación
        {
            if((x1 == x2) |	(y1 == y2))
            {
                if(x1 == x2)
                {
                    if(y1 > 0)
                        m_aux1[m] = mat_playfair[x1][y1-1];
                    else
                        m_aux1[m] = mat_playfair[x1][4];
                    if(y2 > 0)
                        m_aux1[m+1] = mat_playfair[x1][y2-1];
                    else
                        m_aux1[m+1] = mat_playfair[x1][4];
                }
                else
                {
                    if(x1 > 0)
                        m_aux1[m] = mat_playfair[x1-1][y1];
                    else
                        m_aux1[m] = mat_playfair[4][y1];
                    if(x2 > 0)
                        m_aux1[m+1] = mat_playfair[x2-1][y1];
                    else
                        m_aux1[m+1] = mat_playfair[4][y1];
                }
            }
            else
            {
                m_aux1[m] = mat_playfair[x1][y2];
                m_aux1[m+1] = mat_playfair[x2][y1];
            }
        }
    }
    
    m_aux1[m] = '\0';
    i = 1;
    k = 1;
    criptograma[0] = m_aux1[0];
    while(m_aux1[i] != '\0')
    {
        if(i%5 ==0)
        {
            criptograma[k] = ' ';
            k++;
        }
        criptograma[k] = m_aux1[i];
        k++;
        i++;
    }
    criptograma[k]='\0';
}

//---------------------------------------------------------------------------
// Cifrado por el método de Transposición por grupos
//---------------------------------------------------------------------------
bool transposicion_grupo(char *clave,char* mensaje,char* criptograma,bool encriptar)
{
    int i=0,k=0;
    int j,pos;
    j=0;
    int aux;
    int claveaux[100];
    int claveaux2[100];
    int ncaracteres=0;

    //Se procesa la clave para verificar que sus valores son los correctos
    while(clave[i]!='\0')
    {
        if (clave[i]!=',')
        {

            claveaux[j]=clave[i]-48;
            j++; //j es el número de elementos válidos de la clave
            i++;
            continue;
        }
        i++;
    }
    //Se verifica que no haya numeros repetidos en la clave
    int repetido=0;
    for (int a=0;a<j;a++)
    {
        for (int e=a+1;e<j;e++)
        {
            if (claveaux[a]==claveaux[e])
            repetido=1;
        }
    }
    //Se lanza un mensaje de error si en la clave hay elementos repetidos
    if (repetido==1)
    {
        Application->MessageBox("LA CLAVE CONTIENE ELEMENTOS REPETIDOS","ERROR",0);
        return false;
    }
    //Se comprueba que los números de la clave sean los correctos
    int novale=0;
    for (int a=0;a<j;a++)
    {
        if (claveaux[a]>j || claveaux[a]<1)
        novale=1;
    }
    if (novale==1)
    {
        Application->MessageBox("LOS ELEMENTOS DE LA CLAVE NO SON VALIDOS (SÓLO NÚMEROS)","ERROR",0);
        return false;
    }
    //Se cambia la clave dependiendo si se encripta o se desencripta
    if (encriptar)
    {
        for (int i=0;i<j;i++)
        {
            claveaux2[claveaux[i]-1]=i+1;
        }
        for (int i=0;i<j;i++)
        {
            claveaux[i]=claveaux2[i];
        }
    }

    i=0;
    //Se cuentaN los caracteres del mensaje en claro
    while(mensaje[i]!='\0')
        i++;
    //Si el nº de caracteres del mensaje no es múltiplo del de la clave, se
    //rellena con 'X' hasta completar el múltiplo
    k=0;
    if (i%j!=0)
    {
        aux = j-(i%j);
        for (int a=0;a<aux;a++)
        {
            mensaje[i]='X';
            i++;
        }
    }
    mensaje[i]='\0';
    ncaracteres=0;
    //Se encripta o desencripta
    while(mensaje[k]!=0)
    {
        for (i=0;i<j;i++)
        {
            pos=claveaux[i];
            criptograma[ncaracteres]=mensaje[pos+k-1];
            ncaracteres++;
            if((ncaracteres+1)%6==0)
            {
                criptograma[ncaracteres]=' ';
                ncaracteres++;
            }
        }

        k=j+k;
     }
    criptograma[ncaracteres]='\0';
    return true;
}

//---------------------------------------------------------------------------
// Cifrado por el método de Transposición por series
//---------------------------------------------------------------------------
void transposicion_series (char* mensaje,char* criptograma,int factor)
{
    int i = 0;
    int ncaracteres = 0;
    int contad = 0;
    int cant1, cant2;
    int serie[300];
    char aux[3000];
    //Se cuenta el Nº de caracteres del mensaje
    while(mensaje[ncaracteres] != '\0')
        ncaracteres++;
    //Se generan las series
    cant1 = calcula_primos(ncaracteres);
    cant2 = calcula_pares(ncaracteres);
    calcula_resto(ncaracteres,cant1,cant2);
    if(factor ==0)    //Codifica
    {
        while(primos[i] != 0)
        {
            aux[contad] = mensaje[primos[i]-1];
            i++;
            contad++;
        }
        i = 0;
        while(pares[i] != 0)
        {
            aux[contad] = mensaje[pares[i]-1];
            i++;
            contad++;
        }
        i = 0;
        while(resto[i] != 0)
        {
            aux[contad] = mensaje[resto[i]-1];
            i++;
            contad++;
        }
        aux[contad] = '\0';
    }
    else    //Decodifica
    {
        i = 0;
        contad = 0;
        //Se forma una sola serie con las 3 iniciales
        while(primos[i] != 0)
        {
            serie[contad] = primos[i];
            i++;
            contad++;
        }
        i = 0;
        while(pares[i] != 0)
        {
            serie[contad] = pares[i];
            i++;
            contad++;
        }
        i = 0;
        while(resto[i] != 0)
        {
            serie[contad] = resto[i];
            i++;
            contad++;
        }
        serie[contad] = '\0';
        i = 0;
        contad = 0;
        //Se extrae el mensaje original
        for(i = 0;i < ncaracteres;i++)
        {
            for(contad = 0;contad < ncaracteres;contad++)
            {
                if(serie[contad] == i+1)
                {
                    aux[i] = mensaje[contad];
                    break;
                }
            }
        }
        aux[i] = '\0';
    }
    //Se forman bloques de 5 caracteres
    i = 0;
    contad = 0;
    while(aux[contad] != '\0')
    {
        criptograma[i] = aux[contad];
        contad++;
        i++;
        if((i+1)%6 ==0)
        {
            criptograma[i] = ' ';
            i++;
        }
    }
}

//---------------------------------------------------------------------------
// Función para calcular números primos hasta 'p'
// Se utiliza para encriptar por el método de Transposición por series
//---------------------------------------------------------------------------
int calcula_primos(int p)
{
    primos[0] = 1;
    primos[1] = 2;
    int contad = 2;
    bool n_primo;
    for(int i = 3; i<=p; i++){
        n_primo = true;
        for(int j = 2; i>j; j++){
            if(i%j == 0){
                n_primo = false;
                break;
            }
        }
        if (n_primo == true){
            primos[contad]= i;
            contad++;
        }
    }
    primos[contad]= 0;
    return contad;
}
//---------------------------------------------------------------------------
// Función para calcular números pares hasta 'p'
// Se utiliza para encriptar por el método de Transposición por series
//---------------------------------------------------------------------------
int calcula_pares(int p)
{
    int contad = 0;
    for(int i = 3; i<= p; i++){
        if (i%2 == 0){
            pares[contad] = i;
            contad++;
        }
    }
    pares[contad]= 0;
    return contad;
}
//---------------------------------------------------------------------------
// Función para calcular el resto de números que no sean primos ni pares hasta 'p'
// Se utiliza para encriptar por el método de Transposición por series
//---------------------------------------------------------------------------
void calcula_resto(int p, int CantPrim, int CantPar)
{
    bool esta;
    int contad = 0;
    for(int i = 9; i <= p; i++){
        esta = false;
        for (int aux = 0; aux <= CantPrim; aux++){
            if (i == primos[aux]){
                esta = true;
                break;
            }
        }
        if (esta != true){
            for (int aux = 0; aux <= CantPar; aux++){
                if (i == pares[aux]){
                    esta = true;
                    break;
                }
            }
        }
        if(!(esta)){
            resto[contad] = i;
            contad++;
        }
    }
    resto[contad]= 0;
}

//---------------------------------------------------------------------------
// Cifrado por el método de Transposición por filas
//---------------------------------------------------------------------------
void transposicion_filas (char* mensaje,char* criptograma,int filas,int factor)
{
    int i=0;
    int j=0;
    int pos=0;
    int ncaracteres=0;
    int fil_inv;
    char matriz[20][20];
    if(filas < 1)
    {
        Application->MessageBox("NUMERO DE FILAS NO VALIDO","",0);
        okk = false;
        return;
    }
    // Se cuenta el nº de caracteres del mensaje
    while(mensaje[i]!='\0')
        i++;
    ncaracteres=i;
    //Se inicializa la matriz dinámica
    fil_inv=int(ncaracteres/filas);
    if ((fil_inv*filas)!=ncaracteres)
        fil_inv+=1;
    i=0;
    //Se coloca en la matriz el mensaje a encriptar y, si no está completa, se rellena con 'X'
    //El encriptado o desencriptado se controla con la variable 'factor'.
    if (factor==0)  //Codifica
    {
        while (pos<ncaracteres)
        {
            for (j=0;j<filas;j++)
            {
                if (pos<ncaracteres)
                {
                    matriz[j][i]=mensaje[pos];
                    pos++;
                    continue;
                }
                matriz[j][i]='X';
            }
            i++;
        }
        pos=0;
        int k;
        for (j=0;j<filas;j++)
        {
            for (k=0;k<i;k++)
            {
                criptograma[pos]=matriz[j][k];
                pos++;
                if ((pos+1)%6==0)
                {
                    criptograma[pos]=' '; //Se forman bloques de 5 caracteres
                    pos++;
                }
            }
        }
    }

    if (factor==1)  //Decodifica
    {
        while (pos<ncaracteres)
        {
            for (j=0;j<fil_inv;j++) //j es el número de la fila
            {
                if (pos<ncaracteres)
                {
                    matriz[j][i]=mensaje[pos];
                    pos++;
                    continue;
                }
                matriz[i][j]='X';
            }
            i++;
        }
        pos=0;
        int k;
        for (j=0;j<fil_inv;j++)
        {
            for (k=0;k<i;k++)
            {
                criptograma[pos]=matriz[j][k];
                pos++;

                if ((pos+1)%6==0)
                {
                    criptograma[pos]=' ';
                    pos++;
                }
            }
        }
    }
    criptograma[pos]='\0';
}

//---------------------------------------------------------------------------
// Cifrado por el método de Transposición por columnas
//---------------------------------------------------------------------------
void transposicion_columnas (char* mensaje,char* criptograma,int columnas,int factor)
{
    int i=0;
    int j=0;
    int pos=0;
    int ncaracteres=0;
    char matriz[20][20];
    int colum_inv;
    //Cuenta Nº de caracteres del mensaje
    while(mensaje[ncaracteres]!='\0')
        ncaracteres++;
    mensaje[ncaracteres]='\0';
    //Se inicializa la matriz dinámica
    colum_inv=int(ncaracteres/columnas);
    if ((ncaracteres%columnas)!=0)colum_inv+=1;
    i=0;
    //Se coloca en la matriz el mensaje a encriptar y, si no está completa, se rellena con 'X'
    //El encriptado o desencriptado se controla con la variable 'factor'.
    if (factor==0)  //Encripta
    {
        while (pos<ncaracteres)
        {
            for (j=0;j<columnas;j++)
            {
                if (pos<ncaracteres)
                {
                    matriz[i][j]=mensaje[pos];
                    pos++;
                    continue;
                }
                matriz[i][j]='X';
            }
            i++;
        }
        pos=0;
        int k;
        //Se lee la matriz por columnas
        for (j=0;j<columnas;j++)
        {
            for (k=0;k<i;k++)
            {
                criptograma[pos]=matriz[k][j];
                pos++;
                if ((pos+1)%6==0)
                {
                    criptograma[pos]=' ';
                    pos++;
                }
            }
        }
    }
    if (factor==1)  //Se desencripta
    {
        while (pos<ncaracteres)
        {
            for (j=0;j<colum_inv;j++)
            {
                if (pos<ncaracteres)
                {
                    matriz[i][j]=mensaje[pos];
                    pos++;
                    continue;
                }
                matriz[i][j]='X';
            }
            i++;
        }
        pos=0;
        int k;
        for (j=0;j<colum_inv;j++)
        {
            for (k=0;k<i;k++)
            {
                criptograma[pos]=matriz[k][j];
                pos++;
                if ((pos+1)%6==0)
                {
                    criptograma[pos]=' ';
                    pos++;
                }
            }
        }
    }
    criptograma[pos]='\0';
}

//--------------------------------------------------------------------------
// Calcula la longitud de la una cadena
//--------------------------------------------------------------------------

    int LongitudCadena (char *cadena) {
    int j=0;
    while (cadena[j] != '\0') {
        j++;
    }
    return j;
    }
//--------------------------------------------------------------------------
// Convierte a mayúscula una ristra de un fichero
//--------------------------------------------------------------------------

    char* to_mayus(char* str){
    char* res;
    res = new char [3000];
    for (int i=0; str[i] != '\0';i++){
    	if ((str[i] >= 'a') && (str[i] <= 'z')){
    		res[i] = str[i] - 32;
		} else if (str [i] == 'ñ'){
			res[i] = 'Ñ';
		} else if ((str [i] == 'á') || (str [i] == 'ä')){
			res[i] = 'A';
		} else if ((str [i] == 'é') || (str [i] == 'ë')){
			res[i] = 'E';
		} else if ((str [i] == 'í') || (str [i] == 'ï')){
			res[i] = 'I';
		} else if ((str [i] == 'ó') || (str [i] == 'ö')){
			res[i] = 'O';
		} else if ((str [i] == 'ú') || (str [i] == 'ü')){
			res[i] = 'U';
		} else res[i] = str[i];
	}
	return res;
}



//--------------------------------------------------------------------------
// Rrealiza el proceso de encriptar el fichero por distintos métodos
//--------------------------------------------------------------------------
bool encriptaarchivo(char* alfam, char *alfac,char* archivoin,
    char* archivoout, char * clave,int tipo)
{
    okk = true;
    char buffer[2];
    char* buffer1;
    char buffer2[3000];

    fstream filein;
    fstream fileout;
    filein.open(archivoin,ios::in);
    int i = 0;
    while(filein.read(buffer,1))
    {
        buffer2[i] = buffer[0];
        i++;
    }
    buffer2[i]='\0';
    buffer1 = to_mayus(buffer2);

    switch(tipo)
    {
        case 0:   // Sustitución afín
        {
            cifrar(alfam,alfac,Men_prep(buffer1),criptograma);
            break;
        }
        case 1:   // Vigenere (codifica)
        {

            cifra_Vig(clave,Men_prep(buffer1),criptograma,27,1);
            break;
        }
        case 2:   // Vigenere (decodifica)
        {

            cifra_Vig(clave,Men_prep(buffer1),criptograma,27,-1);
            break;
            }
        case 3:   // Beaufort (codifica)
        {

            cifra_Beauf(clave,Men_prep(buffer1),criptograma,27,1);
            break;
        }
        case 4:   // Beaufort (decodifica)
        {

            cifra_Beauf(clave,Men_prep(buffer1),criptograma,27,-1);
            break;
        }
        case 5:   //Playfair (Codifica)
        {

            cifra_play(clave,Men_prep(buffer1),1);
            break;
        }
        case 6:   //Playfair (Decodifica)
        {

            cifra_play(clave,Men_prep(buffer1),2);
            break;
        }
        case 7:   //Transposición por grupos (Codifica)
        {

            okk = transposicion_grupo(clave, Men_prep(buffer1),criptograma,false);
            break;
        }
        case 8:   //Transposición por grupos (Decodifica)
        {

            okk = transposicion_grupo(clave, Men_prep(buffer1),criptograma,true);
            break;
        }
        case 9:   //Transposición por Series (Codifica)
        {
            transposicion_series (Men_prep(buffer1),criptograma,0);
            break;
        }
        case 10:   //Transposición por Series (Decodifica)
        {
            transposicion_series (Men_prep(buffer1),criptograma,1);
            break;
        }
        case 11:   //Transposición por Filas (Codifica)
        {
            transposicion_filas(Men_prep(buffer1),criptograma,atoi(clave),0);
            break;
        }
        case 12:   //Transposición por Filas (Decodifica)
        {
            transposicion_filas(Men_prep(buffer1),criptograma,atoi(clave),1);
            break;
        }
        case 13:   //Transposición por Columnas (Codifica)
        {
            transposicion_columnas (Men_prep(buffer1),criptograma,atoi(clave),0);
            break;
        }
        case 14:   //Transposición por Columnas (Decodifica)
        {
            transposicion_columnas (Men_prep(buffer1),criptograma,atoi(clave),1);
            break;
        }
    }

    if (okk == true)
    {
        fileout.open(archivoout,ios::out);
        fileout.write(criptograma,LongitudCadena(criptograma));
        fileout.close();
    }
    filein.close();
    return okk;
}



