#include <iostream>
#include <bitset>
#include <fstream>
#include <omp.h>

#include "extendibleHash.h"
#include "register.h"

#define KEY_INDEX 2
#define NUM_THREADS 2

int main()
{

    ExtendibleHash<Register *> newHash(150);
    std::fstream arc("data/data1_1.csv", std::ios::in);
    std::string regist;
    int cont = 0;
    while (getline(arc, regist))
    {
        Register *reg = new Register(regist, KEY_INDEX);
        newHash.insert(reg);
    }

    std::string regist1 = "34,jugador,club,1.68";
    Register *new1 = new Register(regist1, KEY_INDEX);

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

    return 0;
}
