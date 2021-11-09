#include <iostream>
#include <string>
using namespace std;

#define INFINITO 9999999
#define MAX_NODOS 200

int numNodos; 
int **matrizCostesC;			
int **matrizCostesMinimosD;
string *arrayCiudades ; 	
int excentricidad;
int centro; 


void leeGrafo() {
	cin >> numNodos;
	string stringg;
	getline(cin ,stringg);
	if (numNodos < 0 || numNodos > MAX_NODOS) {
		cerr << "Numero de nodos no valido " << endl;
		exit(0);
	}
	// array de ciudades
	string ciudad;
	arrayCiudades = new string[numNodos];
	for(int i =0; i < numNodos; i++){
		getline(cin, ciudad);
		arrayCiudades[i] = ciudad;
	}
	// reserva array de costes
	matrizCostesC = new int * [numNodos];
	for (int i = 0; i < numNodos; i++){
		matrizCostesC[i] = new int [numNodos];
	}

	for (int i = 0; i < numNodos; i++)
		for (int j = 0; j < numNodos; j++)
			matrizCostesC[i][j] = INFINITO;
	// inicializacion array de costes
	int c1, c2, distancia;
	cin >> c1 >> c2 >> distancia;
	while (c1 != 0 || c2 != 0 || distancia != 0 ) {
		matrizCostesC[c1][c2] = distancia;
		matrizCostesC[c2][c1] = distancia;
		cin >> c1 >> c2 >> distancia;
	}

}




void inicializacionFloyd(){
	matrizCostesMinimosD = new int * [numNodos];
	for (int i = 0; i < numNodos; i++){
		matrizCostesMinimosD[i] = new int [numNodos];
	}
	
	for (int i = 0; i < numNodos; ++i){
		for (int j = 0; j < numNodos; ++j){
			matrizCostesMinimosD[i][j] = matrizCostesC[i][j];
		}
		matrizCostesMinimosD[i][i] = 0;
	}

}

void floyd(){
	inicializacionFloyd();
	// realizo el algoritmo
	for (int k = 0; k < numNodos; ++k){
		for (int i = 0; i < numNodos; ++i){
			for (int j = 0; j < numNodos; ++j){
				if(matrizCostesMinimosD[i][k] + matrizCostesMinimosD[k][j] < matrizCostesMinimosD[i][j])
					matrizCostesMinimosD[i][j] = matrizCostesMinimosD[i][k] + matrizCostesMinimosD[k][j]; 
			}
		}	
	}		
}


void cuentaExcentricidad(){
	excentricidad = INFINITO;
	int excentricidadAux = 0;
	centro = 0;
		for (int i = 0; i < numNodos; ++i){
			for (int j = 0; j < numNodos; ++j){
				if(matrizCostesMinimosD[i][j] > excentricidadAux)
					excentricidadAux = matrizCostesMinimosD[i][j]; 	
			}
			if (excentricidadAux < excentricidad){ // seleccioono la excentricidad mas baja
				excentricidad = excentricidadAux;
				centro = i;
			}else if( excentricidadAux == excentricidad) // si son iguales elijo en funcion del orden alfabetico
				if(arrayCiudades[i] < arrayCiudades[centro]){
					centro = i;
					excentricidad = excentricidadAux;
				}
			excentricidadAux = 0;
		}	
	cout << arrayCiudades[centro] << endl;
	cout << excentricidad << endl;
}


int main(int argc, char const *argv[]){
	int casos;
	cin >> casos;
	for (int i = 0; i < casos; ++i){
		leeGrafo();
		floyd();
		cuentaExcentricidad();
		for (int i = 0; i < numNodos; i++) {
			delete [] matrizCostesMinimosD[i];
			delete [] matrizCostesC[i];
		}
		delete [] matrizCostesC;
		delete [] matrizCostesMinimosD;
		delete [] arrayCiudades;
	}
	
}