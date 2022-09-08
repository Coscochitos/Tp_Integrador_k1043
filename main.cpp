#include <iostream>
#include <fstream>
using namespace std;

void orden_vec(float valor[],int VecCod[], int dim){ // funcion para ordenar dos vectores
    float aux;

        for(int i = 1; i < dim; i++){
            if(valor[i] < valor[i-1]){
                swap(valor[i],valor[i-1]);
                swap(VecCod[i],VecCod[i-1]);
            }
        }

}


int main()
{
 	int const dimCliente  {8};
	int const dimProducto {5};
	float Kilos[dimCliente ][dimProducto] {}; //Punto 1: carga de datos Kilos
	float Kilometros[dimCliente ][dimProducto] {}; // Punto 1: carga de datos Kilometro

	int entregas[dimProducto] {};  //punto 3: suma cantidad de entregas

	string nombre[dimCliente];
	string producto[dimProducto];


	ifstream archilec;
	archilec.open("Nombres.txt");
	if(!archilec){
		return 1;
	}


	for (int i = 0; i < dimCliente  && archilec >> nombre[i]; ++i); //carga de nombres
	for (int i = 0; i <  dimProducto && archilec >> producto[i]; ++i); //carga de productos

    archilec.close();

	archilec.open("Datos.txt");

    int  CodCliente;
    int CodProducto;
    float CantKg, CantKil;

	while(archilec >> CodCliente >> CodProducto >> CantKg >> CantKil){// carga de los valores en los archivos
        Kilos[CodCliente][CodProducto] += CantKg;
        Kilometros[CodCliente][CodProducto] += CantKil;
        entregas[CodProducto]++;

	}

    archilec.close();

    int contador  = 0; // Punto 2: cuenta la cantidad de producto que pasan los 13000 kg por cliente
    int auxcontador = 0; // Punto 2: reserva el valor anterior de veces que un producto supero los 1300kg
    int mayCliProd = 0; // Punto 2: Toma el cod. del cliente con mayor cantidad tipos de productos que hayan superado 13000 kg
    int VecCodP[dimProducto] {0,1,2,3,4};//punto 2: Vcetor con codigos auxiliar
    float KilometrosAux[dimProducto];//punto 2: vector que guarda los kilometros de un cliente

    cout << "Punto 1 " << endl;
    cout << "====================\n\n" << endl;
    for(int ContFila = 0; ContFila < dimCliente; ContFila++){//bucle de recorrido
        cout << nombre[ContFila] << " : " ;
        for(int ContColuma = 0; ContColuma < dimProducto;ContColuma++){

            if(Kilos[ContFila][ContColuma] > 13000){// verficacion que supere el minimo

                 cout << producto[ContColuma] << "  ";
                 contador++;//contador de cantidad de productos
            }
        }
        cout << endl;

        if(contador > auxcontador){ // comparacion de la cantida de productos del cliente antrio y actual
            auxcontador = contador; // intecambio de los nuevos valores
            mayCliProd = ContFila;
        }
        contador = 0;// reseteo del contador

    }

    cout << "\n\nPunto 2" << endl;

    for(int i = 0; i < dimProducto;i++){// carga del vector aux con los valores correspondientes al cliente encontrado en el recorrido anterior
        KilometrosAux[i] = Kilometros[mayCliProd][i];
    }

    cout << "====================\n\n" << endl;
    for(int i = dimProducto; i > 0; i--){//oredenamiento de vectores
        orden_vec(KilometrosAux,VecCodP,dimProducto);
    }

    for(int i = 0; i < dimProducto; i++){//mustra del vector
        cout << producto[VecCodP[i]] << ": " << KilometrosAux[i] << endl;
    }

    cout << "\n\nPunto 3" << endl;
    cout << "====================" << endl;

    cout << "\n\nCantidad de entregas para el tipo de producto " << producto[VecCodP[4]] << ": " << entregas[VecCodP[4]] << endl;//ultiliza valores anteriores para mostar los datos solisitados

    return 0;
}
