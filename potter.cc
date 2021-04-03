//Guillermo Jiménez Martínez 71721984A

#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <limits.h>
#include <limits>

using namespace std;

vector<long> v;
vector<long> t;
vector<long> m;
vector <vector <long> > valmacen;
long n, T;

bool args(int argc, char *argv[], string &nombrefich, bool &t, bool &ignaive) {
	bool ok = true;
	if (argc == 1){
		ok = false;
		cout << "ERROR: missing filename." << endl;
		cout << "Usage: " << endl;
		cout << "potter [-t] [--ignore-naive] -f file" << endl;
	} else {
		int i = 1;
		while (i < argc && ok){
			string s = argv[i];
			if(s == "--ignore-naive"){
				ignaive = true;
			} else if (s == "-t"){
				t = true;
			} else if(s == "-f"){
				if(i + 1 < argc){
					nombrefich = argv[i + 1];
					i++;
				} else{
					ok = false;
				}
			} else{
				cout << "ERROR: unknown option " << s << endl;
				cout << "Usage: " << endl;
				cout << "potter [-t] [--ignore-naive] -f file" << endl;
				ok = false;
			}
			i++;
		}
		if (nombrefich == ""){
			cout << "ERROR: missing filename." << endl;
		}
	}
	return ok;
}

bool leerFichero(string fileName, long na, long Ta){
	bool leido = false;
	ifstream fich;
	long aux;
	fich.open(fileName.c_str());
	if(fich.is_open()){
		leido = true;
		fich >> na >> Ta;
		
		for(int i = 1; i <= na; i++){
			fich >> aux;
			t.push_back(aux);	
		}
		for(int i = 1; i <= na; i++){
			fich >> aux;
			v.push_back(aux);
		}
		for(int i = 1; i <= na; i++){
			fich >> aux;
			m.push_back(aux);
		}
	}

	n = na;
	T = Ta;
	return leido;
}


long harryPotter (int na, long T){
	long albus, dumbledore;
	
	if (na == -1 || T == 0){
		dumbledore = 0;
	} else {
		dumbledore = -1;
		for (int i = 0; i <= m[na] && i * t[na] <= T; i++){
				albus = harryPotter(na - 1, T - i * t[na]) + v[na] * i;
				if (albus > dumbledore){
					dumbledore = albus;
				
			}
		}
		
	}
	return dumbledore;
}

void matrixAlmacen (const vector < vector <long> > &almacen){
	for (int i = 0; i < almacen.size(); i++){
		for (int j = 0; j < almacen[i].size(); j++){
			if (almacen[i][j] != -1){
				cout << almacen[i][j] << " ";
			} else {
				cout << "- ";
			}
		}
		cout << endl;
	}
}

long harryPotterAlmacen(int ron, long T){
	long albus, dumbledore;
	if (ron == -1){
		return 0;
	} else {
		if (valmacen[ron][T] == -1){
			dumbledore = -1;
			for (int i = 0; i <= m[ron] && i * t[ron] <= T; i++){
				albus = harryPotterAlmacen(ron - 1, T - i * t[ron]) + v[ron] * i;
				if (albus > dumbledore){
					dumbledore = albus;
				}
			}
			valmacen[ron][T] = dumbledore;
		}

	}		
	return valmacen[ron][T];
}

int main(int argc, char *argv[]){
	bool leido, ok, ignaive, t;
	string nfich;
	ok = args(argc, argv, nfich, t, ignaive);
	if (ok){
		leido = leerFichero(nfich, n, T);
		if (leido){
			if (!ignaive){
				long hp = 0;
				cout << harryPotter(n - 1, T) << " ";
			} else {
				cout << "? ";
			}
			valmacen = vector <vector <long> > (n, vector<long>(T + 1, -1));
			cout << harryPotterAlmacen(n - 1, T);
			cout << " " << "?" << " " << "?" << endl;
			if (t){
				cout << "Memoization matrix: " << endl;
				matrixAlmacen(valmacen);
			}
		} else {cout << "ERROR: cant open file: " << nfich << endl;}
	}
}


