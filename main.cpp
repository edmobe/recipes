#include "listas.h"
#include <typeinfo>

int main(int argc, char *argv[])
{
	BaseDeDatos * bd = new BaseDeDatos();
	int opcion;
	while (opcion != 8)
	{
		cout << "---------BASE DE DATOS DE RECETAS---------" << endl;
		cout << endl;
		cout << "Digite el numero de la opcion que desee: "<< endl;
		cout << "1: Agregar receta." << endl;
		cout << "2: Buscar receta." << endl;
		cout << "3: Borrar receta." << endl;
		cout << "4: Imprimir base de datos." << endl;
		cout << "5: Cambiar nombre a receta." << endl;
		cout << "6: Cambiar cantidad de un ingrediente." << endl;
		cout << "7: Agregar un ingrediente." << endl;
		cout << "8: Salir" << endl;
		cout << "Opcion que desea: ";
		cin >> opcion;
		cin.ignore();
		if (opcion == 1)
		{
			cout << "---------------------------" << endl;
			bd->agregarReceta();
			cout << endl;
		}
		else if (opcion == 2)
		{
			cout << "---------------------------" << endl;
			bd->buscarReceta();
			cout << endl;
		}
		else if (opcion == 3)
		{
			cout << "---------------------------" << endl;
			bd->borrarReceta();
			cout << endl;
		}
		else if (opcion == 4)
		{
			cout << "---------------------------" << endl;
			bd->imprimir();
			cout << endl;
		}
		else if (opcion == 5)
		{
			cout << "---------------------------" << endl;
			bd->nombreReceta();
			cout << endl;
		}
		else if (opcion == 6)
		{
			cout << "---------------------------" << endl;
			bd->cantidadIngrediente();
			cout << endl;
		}
		else if (opcion == 7)
		{
			cout << "---------------------------" << endl;
			bd->agregarIngrediente();
			cout << endl;
		}
		else if (opcion != 8)
		{
			cout << "---------------------------" << endl;
			cout << "La opcion digitada no es valida, intentelo de nuevo."<< endl;
			cout << endl;
		}
	}

    system("PAUSE");
    return EXIT_SUCCESS;
}

// Hecho por Eduardo Moya y Diego Mora.
