#include <iostream>
#include <string> //trabajar con cadenas
#include <fstream> //para trabajar con archivos
#include <cstdlib>// para usar la funcion strcpy(arreglo, busqueda.c_str());
#include <cstring>//Para leer caracteres en el archivo

using namespace std;

int main() {
  ifstream archivo;
  archivo.open("libro.txt");
  int words= 0;
  string word;

  while (archivo>>word){
    words++;
  }

  cout<<words<<" palabras"<<endl;

}
