#include <fstream>
#include <vector>
#include <iostream>
#include <limits>
using namespace std;
const long MENOS_INF = numeric_limits<long>::min(); // -infinito
struct DatosProblema{
	vector<long> t, v, m;
	long T, n;
};
struct Solucion{
	vector<long> x;
	long valorAcumulado, tiempoAcumulado;
};
bool leerFichero(string fileName, DatosProblema &dp){
	bool leido = false;
	ifstream fich;
	long aux;
	fich.open(fileName.c_str());
	if(fich.is_open()){
		leido = true;
		fich >> dp.n >> dp.T;
		for(int i = 1; i <= dp.n; i++){
			fich >> aux;
			dp.t.push_back(aux);	
		}
		for(int i = 1; i <= dp.n; i++){
			fich >> aux;
			dp.v.push_back(aux);
		}
		for(int i = 1; i <= dp.n; i++){
			fich >> aux;
			dp.m.push_back(aux);
		}
	}
	return leido;
}
void imprimirSolucion(const Solucion &solucion){
	/*for(int x : solucion.x){
		cout << x << " ";
	}*/
	cout /*<< " => " */<< solucion.valorAcumulado << endl;
}





bool procesarArgumentos(int argc, char *argv[], bool &t, bool &iact, string &f){
	bool correctos, mostrado;

	correctos = true;
	f = "";
	iact = false;
	t = false;
	if(argc == 1){
		correctos = false;
		cout << "ERROR: missing filename."<< endl;
		cout << "Usage: potter [-t] [--ignore-naive] -f file" << endl;
	}
	else{
		mostrado = false;
		for(int i = 1; i < argc && correctos; i++){
			string s = argv[i]; // guarda el string en una cadena para no usar strcmp.
			if(s == "--ignore-naive"){
				iact = true;
			}
			else{
				if(s == "-t"){
					t = true;
				}
				else{
					if(s == "-f"){
						if(i + 1 < argc){
							f = argv[i + 1];
							i++; // me salto el nombre
						}
						else{
							correctos = false;
						}
					}
					else{
						cout << "ERROR: unkown option " << s << endl;
						cout << "Usage: potter [-t] [--ignore-naive] -f file" << endl;
						mostrado = true;
						correctos = false;
					}
				}
			}
		}
		if(!mostrado && f == ""){
			cout << "ERROR: missing filename."<< endl;
			cout << "Usage: potter [-t] [--ignore-naive] -f file" << endl;	
		}
	}
	return correctos;
}
/*
	n elemento por el que voy
	T tiempo que me queda.
*/
long potter(const DatosProblema &dp, int n, long T){
	long r, rmejor;
	if(n == -1 || T == 0){
		rmejor = 0;
	}
	else{
		rmejor = MENOS_INF;
		for(int i = 0; i <= dp.m[n] && i * dp.t[n] <= T; i++){
			r =  potter(dp, n-1, T - i * dp.t[n]) + dp.v[n] * i;
			if(r > rmejor){
				rmejor = r;
			}
		}
	}
	return rmejor;
}

void imprimirAlmacen(const vector< vector<long> > &almacen){
	for(int i = 0; i < almacen.size(); i++){
		for(int j = 0; j < almacen[i].size(); j++){
			if(almacen[i][j] == -1){
				cout << "- ";
			}
			else{
				cout << almacen[i][j] << " ";
			}
		}
		cout << endl;
	}
}

DatosProblema dp;
vector< vector<long> > almacen;

long potterAlmacen( int n, long T){
	long r, rmejor;
	
	if(n == -1){
		return 0;
	}
	else{
		if(almacen[n][T] == -1){
			rmejor = MENOS_INF;
			// for(int i = 0; i <= dp.m[n] && i * dp.t[n] <= T; i++){
			for(int i = dp.m[n]; i >= 0; i--){
				if(i * dp.t[n] <= T){				
					r =  potterAlmacen(n - 1, T - i * dp.t[n]) + dp.v[n] * i;
					if(r > rmejor){
						rmejor = r;
					}
				}
			}
			almacen[n][T] = rmejor;
		}
		return almacen[n][T];
	}
} 
/*
	--ignore-naive => no se muestra el ingenua.		(i)
	-t => muestra las tablas (memoizacion/iterativa)	(t)
	-f => nombre del fichero				(f)
*/
int main(int argc, char *argv[]){
	bool leido, ok, i, t;
	string nombrefichero;
	long solucionNaive = MENOS_INF;
	long solucionAlmacen = MENOS_INF;
	
	ok = procesarArgumentos(argc, argv, t, i, nombrefichero);
	if(ok){	
		leido = leerFichero(nombrefichero, dp);
		
		if(leido == true){
			if(i == false){	// si activa -i no se pone la naive.
				solucionNaive = potter(dp, dp.n - 1, dp.T);
				cout << solucionNaive << " ";
			}
			else{
				cout << "? ";
			}
			almacen = vector<vector<long> >(dp.n, vector<long>(dp.T+1, -1));
			
			solucionAlmacen = potterAlmacen(dp.n-1, dp.T);		
			cout << solucionAlmacen;	// recursiva con almacen.
			cout << " ";
			cout << "?";
			cout << " ";	// Iterativo sin tabla mejorada
			cout << "?";	// Iterativo con tabla mejorada
			cout << endl;
			if(t == true){
				cout << "Memoization matrix: " << endl;
				imprimirAlmacen(almacen);
			}
		}
		else{
			cout << "ERROR: can't open you ass: " << nombrefichero << endl;
		}
	}
	return 0;
}
/*
	--ignore-naive => no se muestra el ingenua.		(i)
	-t => muestra las tablas (memoizacion/iterativa)	(t)
	-f => nombre del fichero				(f)
*/
/*
// k es el elemento para el que voy a decidir.
// actual se pasa por valor para que cada rama tenga su propia solucion
// solMejor se pasa por referencia, es como una variable global a la que acceden
// las llamadas que llegan al ultimo nivel de decision.
void potterBT(const DatosProblema &dp, Solucion actual, int k, Solucion &solMejor){
	// tomamos todas las posibles decisiones para el nivel k.

	// esta linea es la muy particular	
	actual.x.push_back(0); // añado un elemento al vector
	for(int i = 0; i <= dp.m[k]; i++){  // i es la cantidad de veces que lo hago.
		actual.x[k] = i; // para el elmento k (tomo todas las decisiones)
		actual.tiempoAcumulado += dp.t[k] * i;
		actual.valorAcumulado += dp.v[k] * i;
		if(actual.tiempoAcumulado <= dp.T){ //if(factible(actual, dp)){
			// imprimirSolucion(actual);
				
			if(actual.x.size() == dp.n){
				// mejora la mejor solucion encontrada hasta el momento
				if(actual.valorAcumulado > solMejor.valorAcumulado){
					solMejor = actual;
				}
			}
			else{
				// paso al siguiente nivel de decision.
				potterNaive(dp, actual, k+1, solMejor);
			}
		}
		// si lo añado en el bucle, antes de pasar al siguiente
		// elemento tienes que quitar el ultimo valor añadido para
		// que se quede con el siguiente
		actual.tiempoAcumulado -= dp.t[k] * i;
		actual.valorAcumulado -= dp.v[k] * i;
	}		
}
int main(int argc, char *argv[]){
	bool leido, ok, i, t;
	DatosProblema dp;
	string nombrefichero;
	Solucion solMejor, solActual;	// mejor solucion encontrada hasta el momento.
	solActual.tiempoAcumulado = 0;	
	solActual.valorAcumulado = 0;
	solMejor.valorAcumulado = MENOS_INF;
	ok = procesarArgumentos(argc, argv, i, t, nombrefichero);
	if(ok){	
		leido = leerFichero(nombrefichero, dp);
		if(leido == true){
			if(i == false){	// si activa -i no se pone la naive.
				// potterBT(dp, solActual, 0, solMejor);
				cout << solMejor.valorAcumulado << " ";
			}
			cout << "?";	// recursiva con almacen.
			cout << " ";
			cout << "?";
			cout << " ";	// Iterativo sin tabla mejorada
			cout << "?";	// Iterativo con tabla mejorada
			cout << endl;
			imprimirSolucion(solMejor);
			cout << solMejor.tiempoAcumulado << endl;
		}
		else{
			cout << "ERROR: can't open you ass: " << nombrefichero << endl;
		}
	}
	return 0;
}
*/
