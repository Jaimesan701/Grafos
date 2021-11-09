#include <iostream>
#include <string.h>
#include <list>
using namespace std;


int nNodos;
int nAristas;
int * costesCaminoD;
int * nodosDePasoP;
int * nodosEscogidosS;
int nodoInicial;
int nodoFinal;
int nodoIntermedio; 

int **leerGrafo(){
	//compruebo que la entrada es correcta
	if (nNodos < 0 ){
		cerr << "Numero de nodos no valido";
		return NULL;
	}else{
		
		costesCaminoD = new int[nNodos]; 
		nodosDePasoP = new int[nNodos];
		nodosEscogidosS = new int[nNodos];
		int **matrizAdyacencia = new int*[nNodos];
		for (int i = 0; i < nNodos; i++) 
   			matrizAdyacencia[i] = new int[nNodos];
		
		for (int i = 0; i < nNodos; ++i){
			for (int j = 0; j < nNodos; ++j){
				matrizAdyacencia[i][j] = -1;
			}
		}
		int p1, p2, UA;
		for(int i = 0; i < nAristas; i++){
			cin >> p1 >> p2 >> UA;
			matrizAdyacencia[p1][p2] = UA;
			matrizAdyacencia[p2][p1] = UA;
		
		}
		return matrizAdyacencia;
	}

}


void inicializacionEstructurasDij(int nodoInicial, int ** matrizAdyacencia){

	for(int i = 0; i < nNodos; ++i){
		costesCaminoD[i] = matrizAdyacencia[nodoInicial][i]; // inicializacion costes del camino. Al principio solo se inicializan aquellos que tienen una arista directa con el nodo inicial
		nodosDePasoP[i] = nodoInicial; // al principio los nodos de paso son solo el nodo inicial
		if(nodoInicial == i)		// al principio ningun nodo es escogido para pasar por el, solo el inicial
			nodosEscogidosS[i] = 1;
		else nodosEscogidosS[i] = 0;
	}
	
}

int nodoMinimo(int nodoInicial){
	int minimo = 0;
	int nodo = 0;
	for (int i = 0; i < nNodos; ++i){	// recorrido para coger el ultimo nodo que es valido para ser el minimo, la implementacion meduante un bucle while puede provocar errores y bucles infinitos
		if (!nodosEscogidosS[i] && costesCaminoD[i] >= 0){ // si es un nodo candidato a ser el minimo lo guardamos
			minimo = costesCaminoD[i];
			nodo = i;
		}
	}
	for (int i = 0; i < nNodos; ++i){	// recorremos de nuevo la matriz de costes para determinar si hay otro que no es el ultimo y cuyo valor es menor 
		if ( costesCaminoD[i] < minimo && costesCaminoD[i] != -1 && !nodosEscogidosS[i] ){
			minimo = costesCaminoD[i];				
			nodo = i;
		}
	}
	return nodo;
}

void algoritmoD(int nodoInicial,int nodoFinal, int **matrizAdyacencia){ 
	inicializacionEstructurasDij(nodoInicial, matrizAdyacencia); // inicializamos las matrices
	while(!nodosEscogidosS[nodoFinal]){	// paramos cuando el nodo que buscamos esta en la solucion
		int v = nodoMinimo(nodoInicial);
		nodosEscogidosS[v] = 1;
		for (int w = 0; w < nNodos; ++w){
			if (matrizAdyacencia[v][w] != -1 ){
				int tanquesMinimos = costesCaminoD[v];
				if(matrizAdyacencia[v][w] >= tanquesMinimos && !nodosEscogidosS[w])
					tanquesMinimos = matrizAdyacencia[v][w];
				if((!nodosEscogidosS[w]) &&
					 ( (costesCaminoD[w] == -1 ) // esta condicion es analoga a que haya un infinito
						||( tanquesMinimos <= costesCaminoD[w]) ) ){
						costesCaminoD[w] = tanquesMinimos;
						nodosDePasoP[w] = v;				
				}
			}
		}
	}
}

int main(int argc, char const *argv[]){
	nNodos = 1;
	nAristas = 1;
	int casos;
	int ** matrizAdyacencia;
	int planetaInicial, planetaFinal;
	
	cin >> nNodos >> nAristas;
	while(nNodos != 0 && nAristas != 0 ){
		
	
		matrizAdyacencia = leerGrafo();
		cin >> casos;

		for (int i = 0; i < casos ; ++i){
			cin >> planetaInicial >> planetaFinal;
			algoritmoD(planetaInicial, planetaFinal, matrizAdyacencia);
			cout << costesCaminoD[planetaFinal] << endl;
		}
		cin >> nNodos >> nAristas;
		if (nNodos != 0 && nAristas != 0)
			cout << endl;
		for (int i = 0; i < nNodos; ++i)
				delete [] matrizAdyacencia[i];
		delete [] matrizAdyacencia;
		}
	

	delete [] costesCaminoD;
	delete [] nodosEscogidosS;
	delete [] nodosDePasoP;
}
	