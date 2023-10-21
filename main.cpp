#include <iostream>
#include <string>
#include <ctime>

using namespace std;
int inversion = 1000000;

class Transaccion {
public:
    int tipo;
    int cantidad;
    string fecha;

	Transaccion() {
        tipo = 1;
        cantidad = 1;
        time_t now = time(0);
        fecha = "11/10/2023";
    }

    Transaccion(int tipo, int cantidad) {
        this->tipo = tipo;
        this->cantidad = cantidad;
        time_t now = time(0);
        this->fecha = ctime(&now);
    }
};

class Libro {
public:
    int isbn;
    string titulo;
    int precioCompra;
    int precioVenta;	
    int cantidadActual;
    int cantidadVendida;
    int cantidadComprada;
    int numTransacciones;
    Transaccion transacciones[100];
    
    Libro(){
	    isbn = 1000;
	    titulo = "none";
	    precioCompra = 10000;
	    precioVenta = 8000;
	    cantidadActual = 0;
		cantidadVendida = 0;
		cantidadComprada = 0;
	    numTransacciones = 0;
	}

	Libro(int isbn, const string& titulo, int precioCompra, int precioVenta){
	    this->isbn = isbn;
	    this->titulo = titulo;
	    this->precioCompra = precioCompra;
	    this->precioVenta = precioVenta;
	    this->cantidadActual = 0;
	    this->cantidadVendida = 0;
		this->cantidadComprada = 0;
	    this->numTransacciones = 0;
	}

    void abastecer(int cantidad, int& inversion) {
        if (numTransacciones < 100) {
            cantidadActual += cantidad;
            transacciones[numTransacciones++] = Transaccion(2, cantidad);
        	inversion -= precioCompra * cantidad;
            cantidadComprada += cantidad;
        }
    }

    bool vender(int cantidad, int& inversion) {
        if (cantidadActual >= cantidad && numTransacciones < 100) {
            cantidadActual -= cantidad;
            transacciones[numTransacciones++] = Transaccion(1, cantidad);
            inversion += precioVenta * cantidad;
            cantidadVendida += cantidad;
            return true;
        }
        return false;
    }

    int numAbastecimientos() const {
        int num = 0;
        for (int i = 0; i < numTransacciones; i++) {
            if (transacciones[i].tipo == 2) {
                num++;
            }
        }
        return num;
    }

    double calcularGanancias() const {
        double ganancias = 0.0;
        for (int i = 0; i < numTransacciones; i++) {
            if (transacciones[i].tipo == 1) {
                ganancias += (transacciones[i].cantidad * precioVenta) - (transacciones[i].cantidad * precioCompra);
            }
        }
        return ganancias;
    }

    void mostrarInfo(){
        cout << "\t\tISBN: " << isbn << endl;
        cout << "\t\tT�tulo: " << titulo << endl;
        cout << "\t\tPrecio de Compra: $" << precioCompra << endl;
        cout << "\t\tPrecio de Venta: $" << precioVenta << endl;
        cout << "\t\tCantidad Actual: " << cantidadActual << endl;
        cout << "\t\tTransacciones de Abastecimiento: " << numAbastecimientos() << endl;
        cout << "\t\tGanancias totales: $" << calcularGanancias() << endl;
    }
};

class Catalogo {
public:
    Libro libros[100];
    int numLibros;
    
    Catalogo() {
        numLibros = 0;
    }


    void agregarLibro(Libro& libro) {
        if (numLibros < 100) {
            libros[numLibros] = libro;
            numLibros++;
        }
    }

    void eliminarLibro(int isbn) {
        for (int i = 0; i < numLibros; i++) {
            if (libros[i].isbn == isbn) {
                for (int j = i; j < numLibros - 1; j++) {
                    libros[j] = libros[j + 1];
                }
                numLibros--;
                break;
            }
        }
    }

    Libro* buscarPorTitulo(string& titulo) {
        for (int i = 0; i < numLibros; i++) {
            if (libros[i].titulo == titulo) {
                return &libros[i];
            }
        }
        return 0;
    }

    Libro* buscarPorISBN(int isbn) {
        for (int i = 0; i < numLibros; i++) {
            if (libros[i].isbn == isbn) {
                return &libros[i];
            }
        }
        return nullptr;
    }

    Libro* buscarLibroMasCostoso() {
        if (numLibros == 0) return 0;

        Libro* masCostoso = &libros[0];
        for (int i = 1; i < numLibros; i++) {
            if (libros[i].precioVenta > masCostoso->precioVenta) {
                masCostoso = &libros[i];
            }
        }
        return masCostoso;
    }

    Libro* buscarLibroMenosCostoso() {
        if (numLibros == 0) return 0;

        Libro* menosCostoso = &libros[0];
        for (int i = 1; i < numLibros; i++) {
            if (libros[i].precioVenta < menosCostoso->precioVenta) {
                menosCostoso = &libros[i];
            }
        }
        return menosCostoso;
    }

    Libro* buscarLibroMasVendido() {
        if (numLibros == 0) return 0;

        Libro* masVendido = &libros[0];
        for (int i = 1; i < numLibros; i++) {
            if (libros[i].cantidadVendida > libros[i+1].cantidadVendida) {
                masVendido = &libros[i];
            }
        }
        return masVendido;
    }
};

int main() {
    Catalogo catalogo;
    int dineroEnCaja = inversion, isbn = 1000;

    while (true) {
        cout << "\t\t\t\tBIENVENIDO\n" << "Dinero: $" << dineroEnCaja << endl;
        cout << "\t1. Registrar un libro en el catalogo" << endl;
        cout << "\t2. Eliminar un libro del catalogo" << endl;
        cout << "\t3. Buscar un libro" << endl;
        cout << "\t4. Abastecer libros" << endl;
        cout << "\t5. Vender libros" << endl;
        cout << "\t6. Filtro" << endl;
        cout << "\t7. Salir" << endl;
        cout << "Elija una opcion: ";
	
        int opcion;
        cin >> opcion;
		system("clear");
        switch (opcion) {
            case 1: {
            	cout << "\t\t\t\tAGREGAR" << endl;
                int precioCompra, precioVenta;
                string titulo;

                cout << "\tTitulo: ";
                	cin.ignore();
                	getline(cin, titulo);
                cout << "\tPrecio de Compra: $";
                	cin >> precioCompra;
                cout << "\tPrecio de Venta: $";
                	cin >> precioVenta;

                Libro libro(isbn, titulo, precioCompra, precioVenta);
                catalogo.agregarLibro(libro);
				isbn++;
                cout << "\tLibro registrado en el catalogo." << endl;
               	system("pause");
                system("clear");
			    break;
            }
            case 2: {
            	cout << "\t\t\t\tELIMINAR" << endl;
                int id;
                cout << "\tISBN del libro a eliminar: ";
                cin >> id;

                catalogo.eliminarLibro(id);
                cout << "\tLibro eliminado del catalogo." << endl;
                break;
                system("pause");
                system("clear");
            }
            case 3: {
            	cout << "\t\t\t\tBUSQUEDA" << endl;
            	int choose;
            	cout << "\tBuscar por: \n" << "\t\t1.titulo\n" << "\t\t2.ISBN\n" << endl;
            	cin >> choose;
	            	if (choose == 1){
		                string titulo;
		                	cout << "\tTitulo del libro a buscar: ";
		                	cin.ignore();
		                	getline(cin, titulo);
		
		                	Libro* encontrado = catalogo.buscarPorTitulo(titulo);
			                	if (encontrado != 0) {
			                    	encontrado->mostrarInfo();
			                	} else {
			                    	cout << "\tLibro no encontrado." << endl;
			                	}
		        	}else if (choose == 2){
		                int id;
		                	cout << "\tISBN del libro a buscar: ";
		                	cin >> id;
		
		                	Libro* encontrado = catalogo.buscarPorISBN(id);
		                		if (encontrado != 0) {
		                    		encontrado->mostrarInfo();
		                		} else {
		                    		cout << "\tLibro no encontrado." << endl;
		                		}
	          		}
	          	system("pause");
                system("clear");
                break;
			}
            case 4: {
            	cout << "\t\t\t\tABASTECER" << endl;
                int isbn, cantidad;
                cout << "\tISBN del libro: ";
                cin >> isbn;
                cout << "\tCantidad a abastecer: ";
                cin >> cantidad;

                Libro* encontrado = catalogo.buscarPorISBN(isbn);
                if (encontrado != 0) {
                    encontrado->abastecer(cantidad, dineroEnCaja);
                    cout << cantidad << " ejemplares abastecidos." << endl;
                } else {
                    cout << "\tLibro no encontrado." << endl;
                }
	          	system("pause");
                system("clear");
                break;
            }
            case 5: {
            	cout << "\t\t\t\tVENDER" << endl;
                int isbn, cantidad;
                cout << "\tISBN del libro: ";
                cin >> isbn;
                cout << "\tCantidad a vender: ";
                cin >> cantidad;
                
				Libro* encontrado = catalogo.buscarPorISBN(isbn);
                if (encontrado != 0) {
                    if (encontrado->vender(cantidad, dineroEnCaja)) {
                        int ganancias = cantidad * encontrado->precioVenta;
                        dineroEnCaja += ganancias;
                        cout << cantidad << " ejemplares vendidos. Ganancias: $" << ganancias << endl;
                    } else {
                        cout << "\tNo hay suficientes ejemplares para la venta." << endl;
                    }
                } else {
                    cout << "\tLibro no encontrado." << endl;
                }
	          	system("pause");
                system("clear");                
                break;
            }
            case 6: {
            	cout << "\t\t\t\tFiltro" << endl;
            	int choose;
				cout << "\t1.Buscar el libro mas costoso\n" << "\t2. Buscar el libro menos costoso\n" << "\t3. Buscar el libro mas vendido\n" << endl;
				cin >> choose;
	                if (choose == 1){
		                Libro* masCostoso = catalogo.buscarLibroMasCostoso();
			                if (masCostoso != 0) {
			                    cout << "\tLibro mas costoso:" << endl;
			                    masCostoso->mostrarInfo();
			                } else {
			                    cout << "\tNo hay libros registrados en el catalogo." << endl;
			                }
		        	}else if (choose == 2){
		                Libro* menosCostoso = catalogo.buscarLibroMenosCostoso();
			                if (menosCostoso != 0) {
			                    cout << "\tLibro menos costoso:" << endl;
			                    menosCostoso->mostrarInfo();
			                } else {
			                    cout << "\tNo hay libros registrados en el catalogo." << endl;
			                }
		        	}else if (choose == 3){
		                Libro* masVendido = catalogo.buscarLibroMasVendido();
			                if (masVendido != 0) {
			                    cout << "\tLibro mas vendido:" << endl;
			                    masVendido->mostrarInfo();
			                } else {
			                    cout << "\tNo hay libros registrados en el catalogo." << endl;
			           		}
		            } else {
		            	cout << "\tOpcion no valida" << endl;
		            }
	                system("pause");
	                system("clear");
	                break;
	    	}
            case 7: {
                cout << "\tSaliendo del programa." << endl;
                return 0;
            }
            default:
                cout << "\tOpcion no valida. Intente de nuevo." << endl;
        }
    }
    return 0;
}
