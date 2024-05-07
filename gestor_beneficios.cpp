#include <iostream> 
#include <string.h>

using namespace std;

void menu();
char operacion(int CE[], int n);
bool repetir(int CE[], int n);
void crearArchivo(string nombreArchivo, string modoArchivo);
FILE* abrirArchivo(string nombreArchivo, string modoArchivo);
void limpiar(int& i);
bool nombreFlag(string nombreArchivo, string nombre);
bool costoFlag(string costo);
void agregar(string nombreArchivo, int CE[], int n);
void listar(string nombreArchivo);
void modificar(string nombreArchivo, int CE[], int n);
string generarNombreArchivoTemporal(string nombreArchivo);
void eliminar(string nombreArchivo, int CE[], int n);  
void salir();

struct Beneficio{
	
	static const int longitudNombre = 50, longitudCosto = 5;
	
	char nombre[longitudNombre], costo[longitudCosto];
};
struct BeneficioAux{
	
	static const int longitudNombreAux =  50, longitudCostoAux = 5;
	
	char nombreAux[longitudNombreAux], costoAux[longitudCostoAux];
};

int main(){

	int n = 5; int CE[n] = {160, 130, 161, 162, 163};
	
	string nombreArchivo = "gestor_beneficios.dat"; 
	
	setlocale(LC_ALL, "es_ES.UTF-8");	
	
	menu();
	crearArchivo(nombreArchivo, "ab"); 
	
	int i = 0;
	while(true){
		
		switch(operacion(CE, n)){
			
			case '1':
				limpiar(i);
				agregar(nombreArchivo, CE, n);
			break;
			
			case '2':
				limpiar(i);
				listar(nombreArchivo);
			break;
			
			case '3':
				limpiar(i);
				modificar(nombreArchivo, CE, n);
			break;
			
			case '4':
				limpiar(i);
				eliminar(nombreArchivo, CE, n); 
			break;
			
			case '5':
				salir();
			break;
		}
		i++;
	}
}
void menu(){
	
	cout<<"<---- Gestor de Beneficios ---->"<<
	endl<<"  1. Agregar                    "<<
	endl<<"  2. Listar                     "<<
	endl<<"  3. Modificar costo            "<<
	endl<<"  4. Eliminar                   "<<
	endl<<"  5. Salir                      "<<
	endl<<"<------------------------------>"<<endl;
}
char operacion(int CE[], int n){
	
	char ope;
	
	cout<<endl<<"<------------------------------>"<<endl<<"Operaci"<<char(CE[3])<<"n: ";
	cin>>ope;
	
	fflush(stdin);
	
	if(ope < 49 || ope > 53){
			
		cout<<endl<<"Operaci"<<char(CE[3])<<"n inv"<<char(CE[0])<<"lida. Ingrese"<<
		endl<<"un solo car"<<char(CE[0])<<"cter num"<<char(CE[1])<<"rico"<<
		endl<<"entre 1 y 5, ambos inclusive."<<endl;
	}
	
	return ope;
}
bool repetir(int CE[], int n){
	
	char rep;
	
	cout<<"Repetir acci"<<char(CE[3])<<"n? (y/n): ";
	cin>>rep;
	fflush(stdin);
	
	if(rep == 'y' || rep == 'Y'){
		
		return true;
		
	}else if(rep == 'n' || rep == 'N'){
		
		return false;
		
	}else{
		
		cout<<endl<<"Operaci"<<char(CE[3])<<"n inv"<<char(CE[0])<<"lida. Ingrese solo"<<
		endl<<"uno de los siguientes"<<
		endl<<"caracteres: y/Y o n/N."<<endl<<endl;
		repetir(CE, n);
	}
}
void limpiar(int& i){
	
	if(i >= 3){
		
		#ifdef _WIN32
	    system("cls");
	    #else
	    system("clear");
	    #endif
	
		menu();
		i = 0;
	}
}
void crearArchivo(string nombreArchivo, string modoArchivo){
	
	FILE *arch = fopen(nombreArchivo.c_str(), modoArchivo.c_str());
	
	if(!arch){
		
		cout<<"Error: No se pudo abrir o"<<endl<<"crear el archivo.";
		exit(-1);
	}else{
		
		fseek(arch, 0, SEEK_END);
		
		if(strcmp(nombreArchivo.c_str(), "gestor_beneficios_temporal.dat") != 0){
			
			if(ftell(arch) == 0){
			
				cout<<"Archivo creado.";
			}else{
				
				cout<<"Archivo cargado.";
			}
		}
		fclose(arch);
	}
}
FILE* abrirArchivo(string nombreArchivo, string modoArchivo){
	
	FILE* arch = fopen(nombreArchivo.c_str(), modoArchivo.c_str());
	
	if(!arch){ 
	
		cout<<"Error: No se pudo abrir el"<<
		endl<<"archivo.";
		exit(-1);
		
	}else{
		
		return arch;
	}
}
bool nombreFlag(string nombreArchivo, string nombre){ 
	
	Beneficio beneficio;
	
	FILE *archivo = abrirArchivo(nombreArchivo, "rb");
	
	fseek(archivo, 0, SEEK_SET);
	while(fread(&beneficio, sizeof(Beneficio), 1, archivo) == 1){
			
		if(strcmp(beneficio.nombre, nombre.c_str()) == 0){
				
			fclose(archivo);
			return true;
		}
	}
	fclose(archivo);
	return false;
}
bool costoFlag(string costo){
	
	for(int i = 0; i < costo.size(); i++){
		
		if(!isdigit(costo[i])){
			
			return true;
		}
	}
	return false;
}
void agregar(string nombreArchivo, int CE[], int n){
	
	Beneficio beneficio;
	         
	do{	
	
		FILE *archivo = abrirArchivo(nombreArchivo, "ab"); 
		
		cout<<endl<<"Nombre (agregar): ";
		cin.getline(beneficio.nombre, beneficio.longitudNombre);
		fflush(stdin);
		
		cout<<"Costo: ";
		cin>>beneficio.costo;
		fflush(stdin);
		cout<<endl;
		
		if(nombreFlag(nombreArchivo, beneficio.nombre) || costoFlag(beneficio.costo)){ 
		
			cout<<endl<<"Operaci"<<char(CE[3])<<"n inv"<<char(CE[0])<<"lida. El beneficio"<<
			endl<<"a agregar ya est"<<char(CE[0])<<" en la lista"<<
			endl<<"y/o costo no est"<<char(CE[0])<<" conformado"<<
			endl<<""<<char(CE[4])<<"nicamente por caracteres num"<<char(CE[1])<<"ricos."<<endl<<endl;
			
			fclose(archivo);
			
		}else{
			
			fwrite(&beneficio, sizeof(Beneficio), 1, archivo);
			
			fclose(archivo);
			
		}
	}while(repetir(CE, n));
}
void listar(string nombreArchivo){
	
	Beneficio beneficio;
	FILE *archivo = abrirArchivo(nombreArchivo, "rb"); 
	
	fseek(archivo, 0, SEEK_END);
	
	if(ftell(archivo) == 0){
		
		cout<<"No hay beneficios cargados.";
		
	}else{
		
		fseek(archivo, 0, SEEK_SET);
		
		cout<<endl;
		while(fread(&beneficio, sizeof(Beneficio), 1, archivo) == 1){
			
			cout<<beneficio.nombre<<": "<<beneficio.costo<<"cts."<<endl;		
		}
	}
	
	fclose(archivo);
}
void modificar(string nombreArchivo, int CE[], int n){
	
	Beneficio beneficio;
	BeneficioAux beneficioAux;
	
	do{
		
		FILE *archivo = abrirArchivo(nombreArchivo, "r+b");
		
		cout<<endl<<"Nombre (modificar): ";
		cin.getline(beneficioAux.nombreAux, beneficioAux.longitudNombreAux);
		cout<<"Costo: ";
		cin>>beneficioAux.costoAux;
		cout<<endl;
		
		if(nombreFlag(nombreArchivo, beneficioAux.nombreAux) && !costoFlag(beneficioAux.costoAux)){ 
			
			fseek(archivo, 0, SEEK_SET);
			while(fread(&beneficio, sizeof(Beneficio), 1, archivo) == 1){
							
				if(strcmp(beneficio.nombre, beneficioAux.nombreAux) == 0){
						
					strcpy(beneficio.costo, beneficioAux.costoAux);	
					fseek(archivo, -sizeof(Beneficio), SEEK_CUR);
					fwrite(&beneficio, sizeof(Beneficio), 1, archivo);
					break;
				}
			}
			
			cout<<"Se modific"<<char(CE[3])<<": "<<beneficio.nombre<<endl;
			cout<<"Costo actual: "<<beneficio.costo<<endl<<endl;
			
			fclose(archivo);
			
		}else{
			
			cout<<endl<<"Operaci"<<char(CE[3])<<"n inv"<<char(CE[0])<<"lida. El"<<
			endl<<"beneficio cuyo costo intento"<<
			endl<<"modificar no est"<<char(CE[0])<<" en la lista"<<
			endl<<"y/o costo no est"<<char(CE[0])<<" conformado"<<
			endl<<""<<char(CE[4])<<"nicamente por caracteres"<<
			endl<<"num"<<char(CE[1])<<"ricos."<<endl<<endl;
			
			fclose(archivo);
		}
	}while(repetir(CE, n));
}
string generarNombreArchivoTemporal(string nombreArchivo){
	
	string nombreGenerado;
	
	for(int i = 0; i < nombreArchivo.length(); i++){
		
		if(nombreArchivo[i] != '.'){
			
			nombreGenerado += nombreArchivo[i];
		}else{
			
			nombreGenerado += "_temporal.dat";
			break;
		}
	}
	
	return nombreGenerado;
}
void eliminar(string nombreArchivo, int CE[], int n){
	
	Beneficio beneficio;
	BeneficioAux beneficioAux;
	
	string nombreArchivoTemporal = generarNombreArchivoTemporal(nombreArchivo);
	
	do{
		FILE *archivo = abrirArchivo(nombreArchivo, "rb");
		crearArchivo(nombreArchivoTemporal, "wb"); 
		FILE *archivoTemporal = abrirArchivo(nombreArchivoTemporal, "wb");
		
		cout<<endl<<"Nombre (eliminar): ";
		cin.getline(beneficioAux.nombreAux, beneficioAux.longitudNombreAux);
		cout<<endl;
		
		if(nombreFlag(nombreArchivo, beneficioAux.nombreAux)){
			
			fseek(archivo, 0, SEEK_SET);
			while(fread(&beneficio, sizeof(Beneficio), 1, archivo) == 1){
								
				if(strcmp(beneficio.nombre, beneficioAux.nombreAux) != 0){
						
					fwrite(&beneficio, sizeof(Beneficio), 1, archivoTemporal);			
				}
			}
				
			fclose(archivo);
			fclose(archivoTemporal);
							
			remove(nombreArchivo.c_str());
			rename(nombreArchivoTemporal.c_str(), nombreArchivo.c_str());
				
			cout<<"Se elimin"<<char(CE[3])<<": "<<beneficioAux.nombreAux<<endl<<endl;
			
		}else{
			
			cout<<endl<<"Operaci"<<char(CE[3])<<"n inv"<<char(CE[0])<<"lida. El"<<
			endl<<"beneficio a eliminar no est"<<char(CE[0])<<""<<
			endl<<"en la lista."<<endl<<endl;
			
			fclose(archivo);
			fclose(archivoTemporal);
			
			remove(nombreArchivoTemporal.c_str());
			
		}	
	}while(repetir(CE, n));
}
void salir(){
	
	cout<<endl<<"Fin del programa.";
	exit(0);
	
}
