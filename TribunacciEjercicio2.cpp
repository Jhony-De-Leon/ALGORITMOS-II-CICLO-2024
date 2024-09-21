#include <iostream>
#include <locale.h>

using namespace std;

int main (){
	setlocale(LC_CTYPE, "Spanish");
	int numeros[100], Num, Punteo=0;
	
	cout <<"Por favor decidir Cuantos Numeros agrera y fijarse bien que sean enteros para sabes su puntuacion: ";
	cin>>Num; cout<<endl;
	
	for(int i=0;i < Num; i++){
		cout<<"Por favor Ingrese un dígito: ";
		cin>>numeros[i];
		
		if (numeros[i]==5){
			Punteo += 5;
		}
		else if(numeros[i] %2 == 0){
			Punteo +=1;
		}
		else{
			Punteo += 3;
		}
	}
	
	cout<<"\nEl Punteo obtenido de los " <<Num <<" números agregados es: " <<Punteo;
	return 0;
}
