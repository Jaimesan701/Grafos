#include <sstream>
#include <iostream>
#include <string.h>
#include <list>
using namespace std;

#define MAX_NODOS 20000
#define MAX_ARISTAS 10

int n_nodos;
int n_aristas;
int matriz_visitados[MAX_NODOS];
list<int> cola_nodos;
list<int> nodos_recorrido;
bool encontrado;

list<int> * leerGrafo(){
	//leo el numero de nodos y aristas de mi array del grafo
	string n_nodos_str;
	getline(cin,n_nodos_str);
	n_nodos = stoi(n_nodos_str);
	//compruebo que la entrada es correcta
	if (n_nodos < 0 || n_nodos > MAX_NODOS){
		cerr << "Numero de nodos no valido";
		return NULL;
	}else{
		list<int> * array_nodos = new list<int>[n_nodos];
		//inicializo las aristas correctamente
		int aristas;
		for(int i = 0; i < n_nodos; i++){
			aristas = 0;
    		string palabra;
    		string cadena;
    		getline(cin,cadena);
    		istringstream palabras(cadena);	
    		while(palabras >> palabra && aristas < MAX_ARISTAS){
    			int valor = stoi(palabra);
    			array_nodos[i].push_back(valor);
    			aristas++;
	    	}
		}
		return array_nodos;
	}
}
	
void buscar_salida_recursivo(list<int> lista_adyacentes, list<int> * array_nodos, int indice){
	list<int>::iterator it = lista_adyacentes.begin();
	matriz_visitados[indice] = 1;
	int vueltas = 0;	// variable local que uso para saber cuantas veces he pasado por un nodo
	while( it != lista_adyacentes.end() && !encontrado){	// mientas me queden nodos y no haya encontrado la salida sigo buscando
		
		if(*it == n_nodos){		// comprobacion para saber si mi nodo actual es la salida
			matriz_visitados[*it-1] = 1;
			nodos_recorrido.push_back(n_nodos);	//meto el nodo que representa a la salida en mi lista de nodos recorridos
			encontrado = true;	// actualizo variable de control
			return;
		}else{
			if ( matriz_visitados[*it-1] == 0 ){	// comprobacion para saber si he visitado un nodo
				matriz_visitados[*it-1] = 1;	// actualizo la visita al nodo
				nodos_recorrido.push_back(*it);	// meto el nodo en la lista de nodos recorridos
				++vueltas;	// actualizo mi contador de veces que he pasado por este nodo ( asi puede saber si estoy volviendo atras o no)
				buscar_salida_recursivo(array_nodos[*it-1], array_nodos, *it-1); // recorrido en profundidad
				if(vueltas > 0 && !encontrado)	// si ya he pasado por aqui ( vueltas > 0 ) y aun no he encontrado la salida, entonces inserto el nodo actual en mi recorrido
					nodos_recorrido.push_back(indice+1);
			}
			++it;
		}
	}	
}


void buscar_salida(list<int> * array_nodos){
	encontrado=false;
	memset(matriz_visitados, 0, sizeof(matriz_visitados));
	nodos_recorrido.clear();
	buscar_salida_recursivo(array_nodos[0],array_nodos, 0); // inicio la busqueda de la salida desde el primer nodo, si no hay salida desde aqui estamos encerrados
	list<int>::iterator it = array_nodos[0].begin();
	int contador = 0;
	it = nodos_recorrido.begin();
	while( *it != n_nodos && it != nodos_recorrido.end() ){
		contador++;		// cuento el numero total de nodos que he recorrido
		++it;
	}
	if( *it == n_nodos){	// condicion necesaeria para saber si hemos llegado a la salida
		list<int>::iterator it2 =  nodos_recorrido.begin();
		cout << contador+2<< endl;	// le sumo 2 por la primera y ultima posicion
		cout << '1'<< endl;	
		while( *it2 <n_nodos ){
			cout << *it2 << endl;	// imprimo mi recorrido
			++it2;
		}
		cout << n_nodos<< endl;
		delete []array_nodos;
	}else{
		cout << "INFINITO" << endl;		// si la condicion anterior no se cumple, estamos encerrados
		delete []array_nodos;
	}
}


int main(int argc, char const *argv[]){
	int casos;
	string casos_str;
	getline(cin,casos_str);
	casos = stoi(casos_str);
	list<int> * array;
	for (int i = 0; i < casos; ++i){
		cout << "Caso " << i+1 << endl;
		array = leerGrafo();
		buscar_salida(array);
	}
}