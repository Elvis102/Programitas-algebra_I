
/* Implementaci�n del algoritmo de Euclides en C 

Calcula el m�ximo com�n divisor de dos n�meros a y b, y los coeficientes 
que permiten escribirlo como una combinaci�n lineal de ambos.

Este programa tiene solamente prop�sitos did�cticos (es para mis alumnos
de Algebra I).

Ha sido desarrollado sobre el sistema GNU/Linux pero deber�a funcionar
sobre cualquier sistema compatible con el standard POSIX, dado que 
s�lo utiliza llamnadas a la librer�a C est�ndar.

(C) 2007  Pablo De N�poli <pdenapo@dm.uba.ar>

Este programa es software libre, y usted puede redistribuirlo o 
modificarlo libremente bajo los t�rminos de la 
GNU General Public Licence (Licencia P�blica General), versi�n 2
o cualquier versi�n posterior, 
publicada por la Free Software Foundation. Vea:

http://www.gnu.org/copyleft/gpl.html

*/

#include <stdio.h>
#include <stdlib.h>

/* Funci�n que imprime un mensaje de error y termina el programa si 
algo falla al leer los argumentos */


/* Programa Principal */

int main(int argc , char* argv[] )
{
  
  long a,b;
  long a0,b0;
  long alpha,beta,alpha_prime, beta_prime, alpha_anterior,beta_anterior; 
  /*  variables usadas para calcular los coeficientes 
      de la combinaci�n lineal */
  ldiv_t resultado; /* almacena los resultados de la division */
  long aux;        /* variable auxiliar para intercanbio */
  
  /* Parsea los argumentos */
  
  if (argc != 3)
  {
    fprintf(stderr,"Este programa calcula el m�ximo com�n divisor mediante el algoritmo de Euclides.\n"); 
    fprintf(stderr,"Requiere exactamente dos argumentos, dados en la linea de comandos, por ejemplo: \n");
    fprintf(stderr,"euclides 21 31 \n");
    exit(1);
 }
  
  a=strtol(argv[1],NULL,0);
  b=strtol(argv[2],NULL,0);
  
  printf("C�lculo del m�ximo com�n divisor entre %li y %li \nutilizando el algoritmo de Euclides: \n \n",a,b);
  
  /* Si a<b, los intercambiamos (Este paso no es realmente necesario)*/
  if (a<b)
  {
   aux=a;
   a=b;
   b=aux;
  };

  /* Guardamos una copia de los valores iniciales de a y  b */
  
  a0=a;
  b0=b;
      
  /* Los valores iniciales de alpha,beta,alpha_prime,beta_prime, se
 eligen de modo que los invariantes:
   
    alpha * a0 + beta * b0 = b
    alpha_prime * a0 + beta_prime* b0 = a 
   
sean v�lidos al comienzo del ciclo */
 
  alpha=0;
  beta=1;
    
  alpha_prime=1;
  beta_prime=0;
  
  while (b !=0)
    {
     
     /* hacemos la divisi�n entera: result es una estructura con dos componentes:
     r.quot es el cociente y r.rem es el resto */
     resultado = ldiv(a,b); 
     
     /* lo mostramos en pantalla */
     printf("%li = %li * %li + %li \t",a,resultado.quot,b,resultado.rem);
     
     /* el nuevo valor de a es el b anterior, el nuevo valor de b 
     es el resto que obtuvimos. 
     Durante todo el algoritmo se cumple que mcd(a,b)=mcd(a_0,b_0) 
     (invariante del ciclo)  */   
     
     a = b;
     b = resultado.rem;
     
     /* Calculamos los nuevos coeficientes de la combinaci�n lineal:
     
    alpha, beta , alpha_prime, beta_prime 
    
    se calculan de modo que se cumple

    alpha * a0 + beta * b0 = b
    alpha_prime * a0 + beta_prime* b0 = a 
  
    durante todo el algoritmo (invariante del ciclo) 
    
    */ 
   
     alpha_anterior = alpha;
     beta_anterior= beta;
     
     alpha = alpha_prime - resultado.quot * alpha;
     beta  = beta_prime  - resultado.quot *  beta;
     
     alpha_prime = alpha_anterior;
     beta_prime  = beta_anterior;
     
     /* Mostramos como se escribe b como combinanci�n lineal de a0 y b0 */
     
     printf("%li = %li* %li + %li * %li \n",b,alpha,a0,beta,b0);
     
    };
    
    /* a la salida a es el m�ximo com�n divisor de a0 y b0 */
    /* y alpha y beta son los coeficientes que permiten escribirlo  
   como combinaci�n lineal de a0 y b0 */  
  
   printf("\n Resultado:");
   printf("M�ximo com�n divisor = %li\n",a);
   printf("Escritura como combinaci�n lineal de %li  y %li \n",a0,b0);
   printf("%li = %li* %li + %li * %li \n",a,alpha_prime,a0,beta_prime,b0);
 
  exit(0);
}
