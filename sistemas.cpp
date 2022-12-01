#include <iostream>
#include <math.h>
#include <iomanip>
#include <Eigen/Dense>

#define ROWS 2
#define COLS 2
#define E 0.001
#define L 100
#define P 5

using namespace std;
using namespace Eigen;

void jacobi(MatrixXd m, VectorXd v, VectorXd x);
void gauss_siedel(MatrixXd m, VectorXd v, VectorXd x);
MatrixXd getLower(MatrixXd m);
MatrixXd getUpper(MatrixXd m);
double abs_vec(VectorXd v);

int main() {
    MatrixXd m(ROWS, COLS);
    VectorXd v(COLS), x(COLS);

    cout << setprecision(P);

// MATRIZ
    m << 
        2, -1,
        1, 5
    ;
// m.
    //setIdentity(); // setConstant();  // setZeros();  // setOnes();   // setRandom();

// VETOR
    v <<
        1,
        3
    ;
//v.    //setIdentity(); // setConstant();  // setZeros();  // setOnes();   // setRandom();

    x <<
        1,
        2
    ;

    cout << "m: "<< endl << m << endl;
    cout << "v: " << endl << v << endl;
    cout << "x: " << endl << x << endl;

// DETERMINANTE = 0
    if(!m.determinant()) {
        cout << endl << "det = 0" << endl;
        return 0;
    }

    jacobi(m, v, x);

    gauss_siedel(m, v, x);

    return 0;
}

double abs_vec(VectorXd v) {
    return sqrt(v.transpose() * v);
}

void jacobi(MatrixXd m, VectorXd v, VectorXd x) {
    int k=0;
    double crit[2], temp;

    MatrixXd mI(ROWS, COLS);
    VectorXd xn(COLS);
    mI.setIdentity();
    
    cout << endl << "-- JACOBI --" << endl;
    cout << "m: "<< endl << m << endl;
    cout << "v: " << endl << v << endl;
   
    cout << "\nIt: " << k << endl;
    cout << "x: " << endl << x << endl;

    crit[0] = abs_vec(xn - x);
    crit[1] = abs_vec((m*x)-v);

    while (((crit[0]>E && crit[0]>0) && (crit[1]>E && crit[1]>0))) {
        k++;

//        xn = (v-((m-mI)*x));
        for(int i=0; i<COLS; i++){
            temp = v[i];
            for(int j=0; j<COLS; j++){
                if(i!=j)
                    temp -= m(i,j)*x[j];    
            }
            xn[i] = temp/m(i,i);
        }

        cout << "\nIt: " << k << endl;
        cout << "x: " << endl << xn << endl;

        if(k==L)
            break;

        crit[0] = abs_vec(xn - x);
        crit[1] = abs_vec((m*x)-v);

        x = xn;
    }

    cout << "\nIteracoes: " << k << endl;
    cout << "Reposta:\n" << x << endl;
}

MatrixXd getLower(MatrixXd m) {
    for(int i=0; i<ROWS; i++){
        for(int j=0; j<COLS; j++){
            if(i<=j)
                m(i,j) = 0;
        }
    }

    return m;
}

MatrixXd getUpper(MatrixXd m) {
    for(int i=0; i<ROWS; i++){
        for(int j=0; j<COLS; j++){
            if(i>=j)
                m(i,j) = 0;
        }
    }

    return m;
}

void gauss_siedel(MatrixXd m, VectorXd v, VectorXd x) {
    int k=0;
    double crit = abs_vec((m*x)-v), temp;

//   MatrixXd mL(ROWS, COLS), mD(ROWS, COLS), mU(ROWS, COLS);
//    mL = getLower(m);
//    mU = getUpper(m);
//    mD.setIdentity();
//    VectorXd xn(COLS);

    cout << endl << "-- GAUSS-SIEDEL --" << endl;
    cout << "m: "<< endl << m << endl;
    cout << "v: " << endl << v << endl;
    
    cout << "\nIt: " << k << endl;
    cout << "x: " << endl << x << endl;

     while (crit>E && crit>0) {
        k++;

//        xn = (mL+mD).inverse() * (v-(mU*x));
        for(int i=0; i<COLS; i++){
            temp = v[i];
            for(int j=0; j<COLS; j++){
                if(i!=j)
                    temp -= m(i,j)*x[j];    
            }
            x[i] = temp/m(i,i);
        }

        cout << "\nIt: " << k << endl;
        cout << "x: " << endl << x << endl;

        if(k==L)
            break;
        
        crit = abs_vec((m*x)-v);
    }

    cout << "\nIteracoes: " << k << endl;
    cout << "Reposta:\n" << x << endl;
}