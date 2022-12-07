#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

void lagrange(vector<vector<double>> pontos, double x);

double dd_rec(vector<vector<double>> pontos, int i, int n);

void dd(vector<vector<double>> pontos, double x);

int fact(int n);

double df_rec(vector<vector<double>> pontos, int i, int n);

void df(vector<vector<double>> pontos, double x, double h);

int main() {
    double x = 2.2;
    double h = 1;
    vector<vector<double>> pontos = {{1,6}, {2,3}, {3,2}};

    cout << setprecision(3);
    
    cout << "PONTOS:\n";
    for(int i=0; i<pontos.size(); i++)
        cout << "P"<< i <<"(" << pontos[i][0] << ", " << pontos[i][1] << ((i==pontos.size()-1) ? ")" : "); ");
    cout <<  endl;

    lagrange(pontos, x);

    dd(pontos, x);

    df(pontos, x, h);


    return 0;
}

void lagrange(vector<vector<double>> pontos, double x) {
    double pol=0, sum;

    cout << "\n\t--- LAGRANGE ---\n";
    cout << "P" << pontos.size() << "(" << x << ") = \n";

    for(int i=0; i<pontos.size(); i++) {
        sum = pontos[i][1];
        cout << sum << " * ";
        for(int j=0; j<pontos.size(); j++) {
            if(i!=j) {
                sum *= (x - pontos[j][0])/(pontos[i][0] - pontos[j][0]);
                cout << "((" << x << "-" << pontos[j][0] << ") / (" << pontos[i][0] << "-" << pontos[j][0] << ")) * ";
            }
        }
        pol += sum;
        cout << ((i==pontos.size()-1) ? " " : "\n+") << endl;
    }
    
    cout << "\nP" << pontos.size() << "(" << x << ") = " << pol << endl; 
}

double dd_rec(vector<vector<double>> pontos, int i, int n) {

    if(n==0)
        return pontos[i][1];

    return (dd_rec(pontos, i+1, n-1) - dd_rec(pontos, i, n-1)) / (pontos[i+n][0]-pontos[i][0]);
}

void dd(vector<vector<double>> pontos, double x) {
    double pol, sum;

    cout << "\n\t--- DIFERENCAS DIVIDIDAS ---\n";
    cout << "P" << pontos.size() << "(" << x << ") = \n";

    pol = pontos[0][1];
    cout << pol << " +\n";
    for(int i=1; i<pontos.size(); i++) {
        sum = dd_rec(pontos, 0, i);
        cout << sum << " * ";
        for(int j=0; j<i; j++) {
            sum *= x - pontos[j][0];
            cout << "(" << x << " - " << pontos[j][0] << ") * ";
        }
        pol += sum;
        cout << ((i==pontos.size()-1) ? " " : "\n+") << endl;
    }
    
    cout << "\nP" << pontos.size() << "(" << x << ") = " << pol << endl;
}

int fact(int n) {

     return (n==0) || (n==1) ? 1 : n* fact(n-1);
}

double df_rec(vector<vector<double>> pontos, int i, int n) {

    if(n==0)
        return pontos[i][1];

    return (df_rec(pontos, i+1, n-1) - df_rec(pontos, i, n-1));
}

void df(vector<vector<double>> pontos, double x, double h) {
    double pol, sum, z;

    cout << "\n\t--- DIFERENCAS FINITAS ---\n";

    double deltah = pontos[1][0] - pontos[0][0];
    for(int i=1; i<pontos.size(); i++) {
        if(deltah!=(pontos[i][0] - pontos[i-1][0])) {
            cout << "\nDiferenca entre pontos nao constante!\n";
            return;
        }
    }
    
    z = (x - pontos[0][0]) / h;

    cout << "P" << pontos.size() << "(" << x << ") = \n";

    pol = pontos[0][1];
    cout << pol << " +\n";
    for(int i=1; i<pontos.size(); i++) {
        sum = (df_rec(pontos, 0, i) / (fact(i) * h));
        cout << "(" << sum << "/ " << i << "! * " << h << ") * ";
        for(int j=0; j<i; j++) {
            sum *= z - j;
            cout << "(" << z << " - " << j << ") * ";
        }
        pol += sum;
        cout << ((i==pontos.size()-1) ? " " : "\n+") << endl;
    }
    
    cout << "\nP" << pontos.size() << "(" << x << ") = " << pol << endl;
}
