#include <iostream>
#include <string.h>
#include <cmath>
using namespace std;




int componenteX;
int componenteY;
int veneno;
int maximo;
int ** matrizBaldosas;
int ** matrizBaldosasVisitadas;

// funcion que lee el grafo
int **leerMatriz(){
	int dato;
	if(componenteX < 1 || componenteY > 1000){
		exit(0);
	}
	int **matrizBaldosas = new int*[componenteX+1];

	for (int i = 0; i <= componenteX; i++) {
   		matrizBaldosas[i] = new int[componenteY+1];
   		
   	}
   	maximo = 0;
	for (int i = 1; i <= componenteX; ++i){
		for (int j = 1; j <= componenteY; ++j){
			cin >> dato;
			if( dato > maximo) maximo = dato;
			matrizBaldosas[i][j] = dato;
		
		}
		
	}
	return matrizBaldosas;
}

// crea el array de matrices visitadas
int **leerMatrizVisitadas(){
		int ** matrizBaldosasVisitadas = new int*[componenteX+1];
		for (int j = 0; j <= componenteX; ++j)
			matrizBaldosasVisitadas[j] = new int[componenteY+1];
		
		for (int i = 1; i <= componenteX; ++i){
			for (int j = 1; j <= componenteY; ++j)
				matrizBaldosasVisitadas[i][j] = 0;
		
		
	}
	return matrizBaldosasVisitadas;
}
// funcion que reinicializa las matrices
void renovarMatricesVisitadas(){
		for (int i = 1; i <= componenteX; ++i){
			for (int j = 1; j <= componenteY; ++j)
				matrizBaldosasVisitadas[i][j] = 0;
	}
}

void mostrarMatriz(int ** matrizBaldosas){
	for (int i = 1; i <= componenteX; ++i){
		for (int j = 1; j <= componenteY; ++j)
			cout << matrizBaldosas[i][j] << ' ';
		cout << endl;
	}
}

// funcion recursiva que realiza el recorrido sobre la matriz
void recorridoRecursivo(int posX, int posY){

	if(posX == componenteX && posY == componenteY && veneno <= matrizBaldosas[posX][posY])
		matrizBaldosasVisitadas[posX][posY] = 1;

	if(posX < componenteX || posY < componenteY){

		matrizBaldosasVisitadas[posX][posY] = 1;

		if(posX + 1 <= componenteX)
			if(1 >= abs((matrizBaldosas[posX][posY])-matrizBaldosas[posX+1][posY]) && !matrizBaldosasVisitadas[posX+1][posY] && veneno <= matrizBaldosas[posX][posY] )
				recorridoRecursivo(posX+1, posY);
		
		if(posX - 1 >= 1)
			if(1 >= abs((matrizBaldosas[posX][posY])-matrizBaldosas[posX-1][posY]) && !matrizBaldosasVisitadas[posX-1][posY] && veneno <= matrizBaldosas[posX][posY] )
				recorridoRecursivo(posX-1, posY);
		
		if(posY + 1 <= componenteY)
			if(1 >= abs((matrizBaldosas[posX][posY])-matrizBaldosas[posX][posY+1]) && !matrizBaldosasVisitadas[posX][posY+1] && veneno <= matrizBaldosas[posX][posY] )
				recorridoRecursivo(posX, posY+1);

		if(posY - 1 >= 1)
			if(1 >= abs((matrizBaldosas[posX][posY])-matrizBaldosas[posX][posY-1]) && !matrizBaldosasVisitadas[posX][posY-1] && veneno <= matrizBaldosas[posX][posY] )
				recorridoRecursivo(posX, posY-1);

	}
}

// funcion que lanza recorridos sobre la matriz y que aumenta la altura del veneno
void recorrido(int posX, int posY){
	veneno = 0;
	
	recorridoRecursivo(posX, posY);
	int encerrado = 0;
	if(veneno == 0 && !matrizBaldosasVisitadas[componenteX][componenteY] )
		encerrado = 1;
	while(matrizBaldosasVisitadas[componenteX][componenteY] && !encerrado){
		veneno+=1;
		renovarMatricesVisitadas();
		recorridoRecursivo(posX, posY);		
	}
	if (encerrado) veneno  =  0;

}

int main(int argc, char const *argv[]){
	int casos;
	cin >> casos;

	for (int i = 0; i < casos; ++i){
		int posX = 1;
		int posY = 1;
		cin >> componenteX >> componenteY;
		matrizBaldosasVisitadas = leerMatrizVisitadas();
		matrizBaldosas = leerMatriz();
		recorrido(posX, posY); 
		cout << "Caso #" << i+1 << ": " << veneno << endl;
	}
	for (int j = 0; j <= componenteX; ++j){
			delete [] matrizBaldosasVisitadas[j];
			delete [] matrizBaldosas[j];
		}
	delete [] matrizBaldosas;
	delete [] matrizBaldosasVisitadas;
 }

	
