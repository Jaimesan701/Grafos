#include <iostream>
#include <string.h>
#include <list>
using namespace std;
#define MAX_NODOS 26

int n_nodos;
int n_aristas;
int matriz_nodos[MAX_NODOS][MAX_NODOS];
int matriz_visitados[MAX_NODOS];
list<int> cola_nodos;


void leerGrafo(){
	//leo el numero de nodos y aristas de mi array del grafo
	cin >> n_nodos >> n_aristas;
	//compruebo que la entrada es correcta
	if (n_nodos < 0 || n_nodos > MAX_NODOS){
		cerr << "Numero de nodos no valido";
	}else{
		memset(matriz_nodos, 0, sizeof(matriz_nodos));
		//inicializo las aristas correctamente
		char c1, c2;
		for(int i = 0; i < n_aristas; i++){
			cin >> c1 >> c2;
			matriz_nodos[c1-'A'][c2-'A']=1;
		}
	}

}

// Procedimiento recursivo de la busqueda primero en anchura
//   v - primer nodo visitado en la bpa
void bpa(int v){
  matriz_visitados[v]= 1;
  cola_nodos.push_back(v);
  while(!cola_nodos.empty()){
  	int  x = cola_nodos.front();
  	 cout << char(x+'A');
  	cola_nodos.pop_front();
  	for (int w= 0; w<n_nodos; w++){
  		if (matriz_nodos[x][w]) // si <x,w> = cierto 
  			if (!matriz_visitados[w]){ // si no esta visitado debemos insertarlo en la cola de vertices
  				matriz_visitados[w] = 1; // hemos visitado el nodo
  				cola_nodos.push_back(w);	
  			}
  		}
    }
}

// Procedimiento principal de la busqueda en profundidad
void busquedaPA (void){
  memset(matriz_visitados, 0, sizeof(matriz_visitados));
  for (int v= 0; v<n_nodos; v++)
    if (!matriz_visitados[v])
     	bpa(v);
  cout << endl;
}



int main(int argc, char const *argv[]){
	int casos;
	cin >> casos;
	for (int i = 0; i < casos; ++i){
		leerGrafo();
		busquedaPA();
	}
}