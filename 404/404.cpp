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
	//leo el numero de nodos y aristas de mi array del grafo
	cin >> nNodos;
	//compruebo que la entrada es correcta
	if (nNodos < 0 ){
		cerr << "Numero de nodos no valido";
		return NULL;
	}else{
		
		costesCaminoD = new int[nNodos+1]; 
		nodosDePasoP = new int[nNodos+1];
		nodosEscogidosS = new int[nNodos+1];
		int **matrizAdyacencia = new int*[nNodos+1];
		for (int i = 0; i <= nNodos; i++) 
   			matrizAdyacencia[i] = new int[nNodos+1];
		
		for (int i = 0; i <= nNodos; ++i){
			for (int j = 0; j <= nNodos; ++j){
				matrizAdyacencia[i][j] = -1;
			}
		}
		//inicializo las aristas correctamente
		cin >> nAristas;
		cin >> nodoInicial >> nodoFinal >> nodoIntermedio;
		int n1, n2, peso;
		for(int i = 1; i <= nAristas; i++){
			cin >> n1 >> n2 >> peso;
			matrizAdyacencia[n1][n2] = peso;
			matrizAdyacencia[n2][n1] = peso;
			
		}
		return matrizAdyacencia;
	}

}


void inicializacionEstructurasDij(int nodoInicial, int **matrizAdyacencia){

	for(int i = 1; i <= nNodos; ++i){
		
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
	for (int i = 1; i <= nNodos; ++i){	// recorrido para coger el ultimo nodo que es valido para ser el minimo, la implementacion meduante un bucle while puede provocar errores y bucles infinitos
		if (!nodosEscogidosS[i] && costesCaminoD[i] >= 0){ // si es un nodo candidato a ser el minimo lo guardamos
			minimo = costesCaminoD[i];
			nodo = i;
		}
	}
	for (int i = 1; i <= nNodos; ++i){	// recorremos de nuevo la matriz de costes para determinar si hay otro que no es el ultimo y cuyo valor es menor 
		if ( costesCaminoD[i] < minimo && costesCaminoD[i] != -1 && !nodosEscogidosS[i] ){
			minimo = costesCaminoD[i];				
			nodo = i;
		}
	}
	return nodo;
}

int algoritmoD(int nodoInicial,int nodoFinal, int **matrizAdyacencia){ // devuelve un entero, que indica si ha terminado antes de llegar al ultimo nodo o si ha llegado al ultimo y aun no ha terminado
	inicializacionEstructurasDij(nodoInicial, matrizAdyacencia); // inicializamos las matrices
	int contador = 0;
	while(!nodosEscogidosS[nodoFinal]){	// paramos cuando el nodo que buscamos esta en la solucion
		int v = nodoMinimo(nodoInicial);
		nodosEscogidosS[v] = 1;
		for (int w = 1; w <= nNodos; ++w){
			if (matrizAdyacencia[v][w] != -1 )
				if((!nodosEscogidosS[w]) &&
				 ( (costesCaminoD[w] == -1 ) // esta condicion es analoga a que haya un infinito
					||( costesCaminoD[v] + matrizAdyacencia[v][w] < costesCaminoD[w]) ) ){
					costesCaminoD[w] = costesCaminoD[v] + matrizAdyacencia[v][w];
					nodosDePasoP[w] = v;
				}
		}
		
	if (contador > nNodos) return contador;	// si ha pasado el ultimo nodo quiere decir que no hay solucion
	contador++;
	}
	return contador;
}


int main(int argc, char const *argv[]){
	
	int casos;
	cin >> casos;
	int **array;
	int peso;
	// bucle en el que se realiza el ejercicio
	for (int i = 0; i < casos; ++i){
			array = leerGrafo();
			int contador = algoritmoD(nodoInicial, nodoIntermedio, array);
			if(contador <= nNodos){
				peso = costesCaminoD[nodoIntermedio];
				contador = algoritmoD(nodoIntermedio, nodoFinal, array);
				if( contador <= nNodos){
					peso += costesCaminoD[nodoFinal];
					cout << peso << endl;
				}else cout << "IMPOSIBLE" << endl;
			}else cout << "IMPOSIBLE" << endl;
	for (int i = 0; i <= nNodos; ++i)
		delete [] array[i];
	delete [] array;
	}
		
	delete [] costesCaminoD;
	delete [] nodosEscogidosS;
	delete [] nodosDePasoP;
	
}
