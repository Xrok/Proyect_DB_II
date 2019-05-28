#include <iostream>
#include <bitset>
#include <fstream>
#include <omp.h>
#include <chrono>

#include "extendibleHash.h"
#include "register.h"

#define KEY_INDEX 2
#define NUM_THREADS 2

int main()
{

    /*
*cargamos los registros del archivo en la estructura
*/
    ExtendibleHash<Register *> newHash(150);
    std::fstream arc("data/data1_1.csv", std::ios::in);
    std::string regist;
    int cont = 0;
    while (getline(arc, regist))
    {
        Register *reg = new Register(regist, KEY_INDEX);
        newHash.insert(reg);
    }

    /*
*Utilizamos Chrono para medir tiempo.
*/
    auto start = std::chrono::high_resolution_clock::now();
    newHash.search("L. Messi                      ");
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout<<"Search demora: "<<elapsed.count()<<" segundos"<<'\n';

    std::string regist1 = "34,jugador,club,1.68";
    Register *new1 = new Register(regist1, KEY_INDEX);

    /*
*Simulacion de transacciones concurrentes
*/

    /*

    auto start = std::chrono::high_resolution_clock::now();

#pragma omp parallel num_threads(NUM_THREADS)
    {
        for (int i = omp_get_num_threads(); i < 2; i++)
        {
            if (i == 1)
            {
#pragma omp critical
                {
                    newHash.search("L. Messi");
                    newHash.insert(new1);
                }
            }
            if (i == 0)
            {
#pragma omp critical
                {
                    newHash.search("jugador");
                    newHash.insert(new1);
                }
            }
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    //std::cout<<"Concurrente demora: "<<elapsed.count()<<" segundos"<<'\n';

*/
    return 0;
}
