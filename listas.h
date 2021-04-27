#include <cstdlib>
#include <iostream>


using namespace std;

struct Ingrediente;
struct NodoIngrediente;
struct ListaIngredientes;
struct Receta;
struct Nodo;
struct BaseDeDatos;


struct Ingrediente{
   string nombre;
   int cantidad;
   string unidadDeMedida;    
   
   Ingrediente(string n, int c, string u)
   {
        nombre = n;
        cantidad = c;
        unidadDeMedida =  u;                
   }
   
   void imprimir()
   {
        cout <<"        Ingrediente: "<<nombre<<endl;
        cout <<"            Cantidad: "<<cantidad<<" "<<unidadDeMedida<<endl;
        
   }
};


struct NodoIngrediente{
   Ingrediente * ingrediente;     
   NodoIngrediente * siguiente;  

   NodoIngrediente(Ingrediente * i)
   {
        ingrediente = i;
        siguiente = NULL;                      
   }  

   void imprimir()
   {
        ingrediente->imprimir();            
   }
};


struct ListaIngredientes
{
   NodoIngrediente * primerNodo;
   
   ListaIngredientes()
   {
        primerNodo = NULL;                
   }
   
   void insertarAlInicio(Ingrediente * i)
   {
       if (primerNodo == NULL)
          primerNodo = new NodoIngrediente(i);
       else
       {
           NodoIngrediente * nuevo = new NodoIngrediente(i);
           nuevo->siguiente = primerNodo;
           primerNodo = nuevo;    
       }     
   }
   void imprimir()
   {
        NodoIngrediente * tmp = primerNodo;
        while (tmp != NULL)
        {
              tmp->imprimir();
              tmp = tmp->siguiente;     
        }     
   } 
   
   NodoIngrediente * buscar(string nombre)
   {
       NodoIngrediente * tmp = primerNodo;
        while (tmp != NULL)
        {
              if (tmp->ingrediente->nombre == nombre)
                 return tmp;

              tmp = tmp->siguiente;     
        }                 
        return NULL;
   }
};


struct Receta {
	string nombre;  
	int porciones;
	ListaIngredientes * ingredientes;
	
	Receta (string n, int p)
	{
	      nombre = n;
	      porciones = p;
	      ingredientes = new ListaIngredientes();
	}
	void imprimir()
	{
	   cout << "Receta: "<< nombre << endl;
	   cout << "    Cantidad de porciones: " << porciones <<endl;
	   cout << "    Lista de ingredientes: " << endl;
	   ingredientes->imprimir();
	}
};


struct Nodo {
   Receta * receta;
   Nodo * siguiente;
   
   Nodo (Receta * r)
   {
       receta = r;
       siguiente = NULL;     
   }
   
   void imprimir()
   { 
        receta->imprimir();
   }
};


struct BaseDeDatos {
       
   Nodo *primerNodo, *ultimoNodo;
   
   void ListaSimple()
   {
       primerNodo = ultimoNodo = NULL;
   }
   
   void insertarAlInicio (Receta * rec)
	{
		if (primerNodo == NULL)
		   primerNodo = new Nodo(rec);
		else
		{
		    Nodo * nuevo = new Nodo(rec);
		    nuevo -> siguiente = primerNodo;
		    primerNodo = nuevo;    
		}     
	}

	Nodo * buscar (string nombre)
	{
	    Nodo * tmp = primerNodo;
	    
	    while (tmp!=NULL)
	    {
	          if (tmp->receta->nombre == nombre)
	             return tmp;
	          
	          tmp = tmp->siguiente;      
	    }    
	    
	    return NULL;
	}

	void insertaIngrediente(string receta, string nombre, int cantidad, string unidadDeMedida)
	{
	      Nodo * buscado = buscar(receta);   
	      
	      if (buscado == NULL)
	         cout << "No encontrado." <<endl;
	      else
	      {
	          buscado->receta->ingredientes->insertarAlInicio(new Ingrediente(nombre, cantidad, unidadDeMedida));                  
	      }          
	}


	//métodos de la progra
	
	//1
	void agregarReceta()
	{
		bool correcto = false;
		Receta * nuevaReceta;
		int salir;
		while (correcto != true)
		{
			cout << "Digite el nombre de la receta: ";
			string nombreReceta;
			getline(cin, nombreReceta);
			if (buscar(nombreReceta) != NULL)
			{
				cout << "La receta ya existe, intentelo de nuevo." << endl;
				cout << endl;
			}
			else
			{
				cout << "Digite la cantidad de porciones: ";
				int cdp;
				cin >> cdp;
				cin.ignore();
				nuevaReceta = new Receta(nombreReceta, cdp);
				insertarAlInicio(nuevaReceta);
				correcto = true;
			}
		}
		correcto = false;
		while (correcto != true)
		{
			salir = 0;
			cout << "Digite un ingrediente: ";
			string nombreIngrediente;
			getline(cin, nombreIngrediente);
			if (nuevaReceta->ingredientes->buscar(nombreIngrediente) != NULL)
			{
				cout << "El ingrediente ya existe, intentelo de nuevo." << endl;
				cout << endl;
			}
			else
			{
				cout << "Digite la cantidad necesaria de ese ingrediente: ";
				int ci;
				cin >> ci;
				cin.ignore();
				cout << "Digite la unidad de medida de esa cantidad: ";
				string um;
				getline(cin, um);
				insertaIngrediente(nuevaReceta->nombre, nombreIngrediente, ci, um);
				while (salir != 2)
				{
					cout << "Digite '1' si desea agregar otro ingrediente o '2' para volver al menu principal: ";
					cin >> salir;
					cin.ignore();
					if (salir == 1)
					{
						correcto = false;
						salir = 2;
					}
					else if (salir != 1 and salir != 2)
					{
						cout << "El numero digitado debe ser '1' o '2'." << endl;
					}
					else
						correcto = true;
				}
			}
		}
	}
	
	// 2
	void buscarReceta()
	{
		cout << "Digite el nombre de la receta: ";
		string nombreReceta;
		getline(cin, nombreReceta);
		if (buscar(nombreReceta) == NULL)
		{
			cout << "---------------------------" << endl;
			cout << "La receta no existe." << endl;
			cout << endl;
		}
		else
		{
			cout << "---------------------------" << endl;
			buscar(nombreReceta)->receta->imprimir();
			cout << endl;
		}
	}
	
	//3
	void borrarReceta()
	{
		cout << "Digite el nombre de la receta que desea borrar: ";
		string nombreReceta;
		getline(cin, nombreReceta);
		if (buscar(nombreReceta) == NULL)
		{
			cout << "La receta no existe." << endl;
			cout << endl;
		}
		else
		{
			Nodo * tmp = buscar(nombreReceta);
			Nodo * tmp2 = primerNodo;
			if (tmp == primerNodo and tmp->siguiente == NULL)
			{
				primerNodo = NULL;
			}
			else if (tmp == primerNodo)
			{
				primerNodo = primerNodo->siguiente;
				tmp2->siguiente = NULL;
			}
			else if (tmp == ultimoNodo)
			{
				while (tmp2->siguiente->siguiente != NULL)
					tmp2 = tmp2->siguiente;
				Nodo * borrado = ultimoNodo;
				tmp2->siguiente = NULL;
				ultimoNodo = tmp;
			}
			else
			{
				while (tmp2->siguiente != tmp)
					tmp2 = tmp2->siguiente;
				tmp2->siguiente = tmp2->siguiente->siguiente;
				tmp = NULL;
			}
			cout << "Se ha borrado exitosamente la receta: " << nombreReceta << endl;
			cout << endl;
		}
	}
		 
	//4
	
	void imprimir()
	{
		Nodo * tmp = primerNodo;
		while(tmp!=NULL)
		{
		                
		   tmp->imprimir();
		   cout<< endl;
		   tmp = tmp->siguiente;                
		}     
	}
	//5
	void nombreReceta()
	{
	     cout << "Ingrese el nombre de la receta que desea modificar: ";
	     string nombreReceta;
	     getline(cin, nombreReceta);
	     cout<<endl;
	     if (buscar(nombreReceta) == NULL)
	     {
	        cout << "---------------------------" << endl;
		    cout << "La receta no existe." << endl;
		    cout << endl;
	     }
	     else
	     {
	        cout<< "Ingrese el nuevo nombre para la receta: ";
	        string nuevoNombre;
	        getline(cin, nuevoNombre);
	        cout << "---------------------------" << endl;
		    buscar(nombreReceta)->receta->nombre = nuevoNombre;
		    cout << endl;
	     }
	}
	
	//6
	void cantidadIngrediente()
	{
	     cout << "Ingrese el nombre de la receta: ";
	     string nombreReceta;
	     getline(cin, nombreReceta);
	     cout<<endl;
	     if (buscar(nombreReceta)!=NULL)
	     {
	         cout<< "Ingrese el ingrediente: ";
	         string ingrediente;
	         getline(cin, ingrediente);
	         if (buscar(nombreReceta)->receta->ingredientes->buscar(ingrediente) != NULL)
	         {
	             cout<< "Ingrese la nueva cantidad: ";
	             int nuevaCantidad;
	             cin >> nuevaCantidad;
	             cin.ignore();
	             buscar(nombreReceta)->receta->ingredientes->buscar(ingrediente)->ingrediente->cantidad=nuevaCantidad;
	         }
	         else
	         {
	             cout << "El ingrediente no existe."<<endl;
	             cout << endl;
	         }
	         
	     }
	     else
	     {
	        cout << "---------------------------" << endl;
		    cout << "La receta no existe." << endl;
		    cout << endl;
	     }
	     
	     
	}
	//7
	void agregarIngrediente()
	{
	     cout << "Ingrese el nombre de la receta: ";
	     string nombreReceta;
	     getline(cin, nombreReceta);
	     cout<<endl;
	     if (buscar(nombreReceta)!=NULL)
	     {
	         cout << "Ingrese el nombre del ingrediente nuevo: ";
	         string nombreingrediente;
	         getline(cin, nombreingrediente);
	         cout<<endl;
	         if (buscar(nombreReceta)->receta->ingredientes->buscar(nombreingrediente) == NULL)
	         {
	             cout << "Ingrese la cantidad: ";
	             int ci;
	             cin >> ci;
	             cin.ignore();
	             cout<<endl;
	             cout << "Ingrese la unidad de medida: ";
	             string um;
	             getline(cin, um);
	             insertaIngrediente(nombreReceta, nombreingrediente, ci, um);
	          }
	          else
	          {
	              cout << "El ingrediente ya existe."<<endl;
	              cout << endl;
	          }
	     }
	     else
	     {
	         cout << "La receta no existe." << endl;
	         cout << endl;
	     }
	}  
};
