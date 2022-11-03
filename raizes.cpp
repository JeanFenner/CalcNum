#include <iostream>
#include <math.h>
#include <iomanip>

#define E 0.01
#define F "e^x + x -3"
#define D "e^x + 1"
#define Dd "e^x"
#define P 10

using namespace std;

// FUNÇAO
double f(double x) {
    double y = (exp(x) + x -3);
    return y;
}

// DERIVADA DA FUNÇAO
double f_d(double x) {
    double y = (exp(x) + 1);
    return y;
}

// DERIVADA SEGUNDA DA FUNÇAO
double f_dd(double x) {
    double y = (exp(x));
    return y;
}


// METODO DA BISSECÇAO
void bisseccao(double a, double b) {
    cout << "\n\n\t----- METODO DA BISSECCAO -----\n";
  
    cout << setprecision(P);

    int i = 0;
    double x;

    do{
        cout << "\nI = " << i << endl;
        cout << "INTERVALO = (" << a << ", " << b << ")" << endl;
    
        x = (a + b)/2;
        cout << "X("<< i <<") = " << x << endl;
        cout << "f(" << x << ") = " << f(x) << endl;

        if(f(x)*f(b)<0)
            a = x;
        else
            b = x;

        i++;
    }while(abs(f(x))>E);

    cout << "\t--------------------\nBISSECCAO:" << endl;
    cout << "RAIZ EM X = " << x << "\nITERACOES: " << i << endl;
}

// METODO DAS CORDAS
void cordas(double a, double b) {
    cout << "\n\n\t ----- METODO DAS CORDAS -----\n";

    cout << setprecision(P);

    int i = 0;
    double x;

    do{
        cout << "\nI = " << i << endl;
        cout << "INTERVALO = (" << a << ", " << b << ")" << endl;

        x = ((a*f(b) - b*f(a)) / (f(b)- f(a)));

        cout << "X("<< i <<") = " << x << endl;
        cout << "f(" << x << ") = " << f(x) << endl;

        if(f(x)*f(a)<0)
            b = x;
        else
            a = x;

        i++;
    }while(abs(f(x))>E);

    cout << "\t--------------------\nCORDAS:" << endl;
    cout << "RAIZ EM X = " << x << "\nITERACOES: " << i << endl;
}

// METODO DE NEWTON
void newton(double a, double b) {
    cout << "\n\n\t ----- METODO DE NEWTON -----\n";
    
    cout << setprecision(P);

    int i = 0;
    double x;

    do{
        cout << "\nI = " << i << endl;
        cout << "INTERVALO = (" << a << ", " << b << ")" << endl;

        if(f_d(a)*f_dd(a)<0)
            x = a - f(a) / f_d(a);
        else
            x = b - f(b) / f_d(b);

        cout << "X("<< i <<") = " << x << endl;
        cout << "f(" << x << ") = " << f(x) << endl;

        if(f_d(x)*f_dd(x)<0)
            a = x;
        else
            b = x;

        i++;
    }while(abs(f(x))>E);

    cout << "\t--------------------\nNEWTON" << endl;
    cout << "RAIZ EM X = " << x << "\nITERACOES: " << i << endl;
}

int main() {
    double A, B;                    // INTERVALO INICIAL
    cin >> A >> B;
    
    cout << setprecision(P);

    cout << "Intervalo Inicial: ("<< A << ", " << B <<")" << endl;
    cout << "f(x) = " << F << endl;
    cout << "f'(x) = " << D << endl;

    if(f(A)*f(B)>0) {
        cout << "SEM RAIZ" << endl;
        return 0;
    }

    bisseccao(A, B);

    cordas(A, B);

    newton(A, B);

    return 0;
}