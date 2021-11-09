#include <iostream>
#include <string.h>
#include <cmath>
using namespace std;



int numColonias;
int **matrizAdyacencia;
int *matrizCostesMinimos;
int *matrizMasCercano;
int *matrizVisitados;

struct coordendas{
	int X;
	int Y;
};

coordendas *matrizCoordenadas;

void leerGrafo(){
	matrizCoordenadas = new coordendas[numColonias];
	coordendas posicionCiudad;
	int x;
	int y;
	// inicializo matriz con las coordenadas de cada ciudad (nodo)
	for (int i = 0; i < numColonias; ++i){
		cin >> x >> y;
		if (x > 1000 || x < -1000 || y > 1000 || y < -1000){
			delete [] matrizCoordenadas;
	 		exit(0);
		}
		posicionCiudad.X = x;
		posicionCiudad.Y = y;
		matrizCoordenadas[i] = posicionCiudad;
	}

	// inicializo matriz de adyacencia
	matrizAdyacencia = new int*[numColonias];
	for (int i = 0; i < numColonias; ++i){
		matrizAdyacencia[i] = new int[numColonias]; 
	}
	
	// asigno los valores coorrespondientes a cada matriz
	int valor;
	for (int i = 0; i < numColonias; ++i){
		for (int j = 0; j < numColonias; ++j){
			valor = trunc(pow(pow(matrizCoordenadas[i].X - matrizCoordenadas[j].X,2) + pow(matrizCoordenadas[i].Y - matrizCoordenadas[j].Y,2),0.5));
			matrizAdyacencia[i][j] =  valor;
			matrizAdyacencia[j][i] =  valor;
		}
	}
	
}

void inicializacionPrim(){
	// incializacion de las estructuras de Prim
	for (int i = 0; i <numColonias ; ++i){
		matrizVisitados[i] = 0;
		matrizMasCercano[i] = 0;
		if (i != 0){
			matrizCostesMinimos[i] = matrizAdyacencia[0][i];
		}
	}
	matrizVisitados[0] = 1;
}

int minimoPrim(){
	int nodo = 0;
	int minimo = 0;
	// cojo el ultimo nodo que puede ser valido
	for (int i = 1; i < numColonias; ++i){
			if (matrizVisitados[i] == 0){
				nodo = i;
				minimo = matrizCostesMinimos[i];
			}
			
	}
	// busco en la matriz de adyaciencialas aristas del nodo con menor coste y que ademas aun no haya sido visitado
	for (int i = 1; i < numColonias; ++i)
			if(matrizVisitados[i] == 0 && matrizCostesMinimos[i] < minimo){
				nodo = i;
				minimo = matrizCostesMinimos[i];
			}
		
	return nodo;	
}

int prim(){
	matrizCostesMinimos = new int[numColonias];
	matrizMasCercano = new int[numColonias];
	matrizVisitados = new int[numColonias];
	// lo primero que hago es inicializar las matrices que usare en el algoritmo de Prim
	// siempre empiezo en el nodo 1 (0)
	inicializacionPrim();
	// comienzo el algortimo
	for (int i = 1; i < numColonias ; ++i){
		int minimo = minimoPrim();
		matrizVisitados[minimo] = 1;
		// para cada nodo del minimo, comprobamos si hay alguno que puede cambiar la matriz de costes
		for (int w = 0; w < numColonias; ++w){
			if(w != minimo){
				if(matrizVisitados[w] == 0 && matrizAdyacencia[minimo][w] < matrizCostesMinimos[w] ){
					matrizCostesMinimos[w] = matrizAdyacencia[minimo][w];
					matrizMasCercano[w] = minimo;
				}
			}
		}
	}
	// calculamos la solucion
	int solucion = 0;
	for (int i = 1; i < numColonias; ++i){
		solucion+=matrizCostesMinimos[i];
	}
	return solucion;
}




int main(int argc, char const *argv[]){
	int casos;
	int cableTotal;
	cin >> casos;
	for (int i = 0; i < casos; ++i){
		cin >> numColonias;
		leerGrafo();
		cableTotal = prim();
		cout << cableTotal << endl;
		for (int i = 0; i < numColonias; ++i)
			delete [] matrizAdyacencia[i];
		delete matrizVisitados;
		delete matrizCoordenadas;
		delete matrizCostesMinimos;
		delete matrizMasCercano;
	}
	
}