#include <sstream>
#include <iostream>
#include <string.h>
#include <list>
using namespace std;

int nNodos;
int nAristas;
int *matrizVisitados;
list<int> *nodos;
int *matrizIslas;
int isla;

void leerGrafo(){
	//leo el numero de nodos y aristas de mi array del grafo
	cin >> nNodos >> nAristas; 
	//compruebo que la entrada es correcta
	if (nNodos < 0 ){
		cerr << "Numero de nodos no valido";
		return;
	}else{
		nodos = new list<int>[nNodos + 1];
		matrizVisitados = new int[nNodos + 1];
		matrizIslas = new int[nNodos + 1];
		//inicializo las aristas correctamente
		int persona1, persona2;
		for(int i = 0; i < nAristas; i++){
			cin >> persona1 >> persona2;
				nodos[persona1].push_back(persona2);
				nodos[persona2].push_back(persona1);		
	    	}
		}
	}


void bpp(int nodoInicial){
	matrizVisitados[nodoInicial] = 1;
	list<int>::iterator it = nodos[nodoInicial].begin();
	while(it != nodos[nodoInicial].end()){
		if(matrizVisitados[*it] == 0){
			matrizVisitados[*it] = 1;
			matrizIslas[*it] = isla;
			bpp(*it);
		}
		it++;
	}
}

void busquedaPP(){
	for (int i = 1; i <= nNodos; ++i){
			matrizIslas[i] = 0;
			matrizVisitados[i] = 0;
		}
	isla = 1;
	for (int i = 1; i <= nNodos; ++i){
		if (matrizVisitados[i] == 0){
			matrizIslas[i] = isla;
			bpp(i);
			++isla;
		}	
	}
}


int main(int argc, char const *argv[]){
	int casos;
	cin >> casos;
	for (int i = 0; i < casos; ++i){
		leerGrafo();
		busquedaPP();
		cout << "Caso " <<i+1 << endl;
		cout << isla-1 << endl;
		for (int i = 1; i <= nNodos ; ++i){
			cout << matrizIslas[i] << endl;
		}
		delete [] matrizIslas;
		delete [] matrizVisitados;
		delete [] nodos; 
	}
	
}