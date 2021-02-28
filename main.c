#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// LEONARDO MARTIN
// 14-10628

double g (double );
double cuadGauss (double , double , double (*) (double));
double cuadAdaptativa (double (*)(double), double , double , double , int );
double a, b, integral, tol, recursion;

int main(int argc, char *argv[]) {
	
	printf("\n\t\t\t\tCuadratura Gaussiana Adaptativa\n");
	
	printf("\n Intervalo:\n");
	printf("\n Ingrese extremo izquierdo: ");
	scanf("%lf", &a);
	printf("\n Ingrese extremo derecho: ");
	scanf("%lf", &b);

	printf("\n\n Tolerancia:\n");
	printf("\n Ingrese la tolerancia: ");
	scanf("%lf", &tol);
	
	printf("\n\n Cantidad de recursiones:\n");
	printf("\n Ingrese el criterio de repeticiones: ");
	scanf("%lf", &recursion);
	
	// invocamos a la funcion cuadAdaptativa
	integral = cuadAdaptativa(g, a, b, tol, recursion);

	printf("\n\n Resultado:\n");
	printf("\n Valor aproximado de la integral es: %12.16lf\n", integral);
	
	
	printf("\n\n");
	system("PAUSE");
	return 0;
}


// -------------------------------------- Funcion a integrar

double g (double x) {
	//return sin(x);
	return (100*sin(10/x))/x;      // funcion a integrar segun el ejercicio #4
}



//  ------------------------------------ Funcion de cuadratura gaussiana

double cuadGauss (double a, double b, double (*fun)(double)) {
	
	double a0 = 0.5 * (b+a);
	double a1 = 0.5 * (b-a);
	double f1, f2, t1, t2, constante;
	
	// constantes y raices de Legendre
	const int c = 1;
	const double r1 = -0.5773502692, r2 = 0.5773502692;
	
	// Haciendo la transformacion (b-a)/2 * integral(f[(b-a)t_k + (b+a)]/2) cuando a ó b son diferentes de -1 ó 1
	if (a != -1 || b != 1) {
		constante = (b-a)/2;
		t1 = (b-a);
		t2 = (b+a);
		
		// entonces la funcion nos quedaria evaluada en 
		f1 = constante * (*fun)((t1*r1+t2)/2);
		f2 = constante * (*fun)((t1*r2+t2)/2);
		
		return (c*f1 + c*f2);
		
	} 
	else {
		// en este caso no hay que realizar la transformacion pues a = -1 y b = 1
		t1 = a0 + a1*r1;
		t2 = a0 + a1*r2;
		f1 = (*fun)(t1);
		f2 = (*fun)(t2);
		return (c*f1 + c*f2);
	}

}




// ------------------------------------------ Funcion Cuadratura Adaptativa Gaussiana

double cuadAdaptativa (double (*fun)(double), double a, double b, double tol, int recursion) {
	
	double ptmedio, integralCompleta, integralIzq, integralDer;
	double errorEst;
	int N = 2, p = 2*N-1;  // N = 2 ya que estamos trabajando con 2 nodos
	
	ptmedio = (a+b)/2;  // se toma la mitad de intervalo
	
	integralCompleta = cuadGauss(a, b, fun);
	integralIzq = cuadGauss(a, ptmedio, fun);
	integralDer = cuadGauss(ptmedio, b, fun);
	
	errorEst = fabs(integralIzq + integralDer - integralCompleta) / (pow(2,p+1) - 1);   // formula del error cometido
	//printf("\n Error cometido: %12.8lf\n", errorEst);
	
	if (errorEst < tol || recursion <= 0) {
		// se cumplio la convergencia, salida, devolvemos el valor aproximado de la integral
		return (integralIzq + integralDer);
	}
	else {
		// no hay convergencia, volvemos a llamar a la funcion cuadAdaptativa
		// disminuimos el valor del contador "recursion" y repetimos el proceso
		recursion--;
		integralIzq = cuadAdaptativa(fun, a, ptmedio, tol/2, recursion);    // subintervalos del lado izquierdo
		integralDer = cuadAdaptativa(fun, ptmedio, b, tol/2, recursion);    // subintervalos del lado derecho
		
		return (integralIzq + integralDer);
	}
	
}



