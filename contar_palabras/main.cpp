#include <iostream>
#include <fstream> //para trabajar con archivos
#include <omp.h>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {

    string aux;
    int total_lines = 0;
    int tid;
    int words;
    int nth;
    ifstream file;
    vector<string> all_lines;

    file.open(argv[1]); //se abre el archivo  argv[1]
    while(getline(file, aux)){//Leera todo el archivo linea por linea
        all_lines.push_back(aux);//Cada linea se agregará al vector all_lines (aux representa la linea actual)
        total_lines++;//Se contaran las lineas totales que tiene el archivo.
    }


    /*La linea a continuacion se utiliza para paralelizar el bucle. Tiene una variable
     * privada tid que es el id de cada hilo. reduction sirve para sumar todas las variables
     * "words" que se sumen en cada hilo.
     * Esta funcion se hace con el fin de que cada núcleo lea una linea diferente y sume las
     * palabras que hay en esta, asi cuando cada uno de los nucleos termine de leer una linea
     * se sumara el numero de palabras a la variable words.
    */
    #pragma omp pararell private(tid) reduction(+:words)
    {
        tid = omp_get_thread_num(); //tid representa el id del hilo
        nth = omp_get_num_threads(); //nth representa el numero total de nucleos

        /* Para realizar el programa en paralelo es necesario que cada hilo lea el numero
         * de palabras de un rango de palabras en específico. Para esto creamos una
         * variable x que simboliza la cantidad de lineas que tiene que leer cada hilo.
         * Es por esto que es igual al numero total de lineas entre el numero total de nucleos.
         * La variable ls se crea para representar el límite superior de cada rango de lineas,
         * en este caso sera el numero de lineas que tiene cada procesador (x) multiplicado
         * por el numero del hilo mas uno (ya que el id del hilo comienza originalmente en 0).
        */
        int x = total_lines/nth;
        int ls = x*(tid+1);

        /* El siguiente if se realiza para obligar al último hilo a tomar como limite superior
         * al numero total de renglones, ya que puede ocurrir que x sea un numero decimal y
         * por lo tanto falten lineas por leer ya que no se encuentran en el rango.
        */
        if ((tid+1) == nth){
            ls = total_lines;
        }

        //El siguiente for toma un rango definido de lineas del archivo y cuenta las palabras.
        bool t = true;//se declara una variable t que representa si hay espacios o no
        for (int i=x*tid; i<ls; i++){
            t = true;

            for (int j=0; j<all_lines[i].size(); j++){
                if (all_lines[i][j]==' ') {
                    t = true;
                }
                else {
                    if (t==true){
                         words++;
                    }
                    t=false;
                }
            }
        }

    }

    cout<<"Hay "<<words<<" en el texto."<<endl;
}
