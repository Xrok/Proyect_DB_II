#include <iostream>
#include <omp.h>
#include <chrono>

#include "data-structures/random-file/Random.cpp"
#include "manager/CSVManager.hpp"

omp_lock_t mutex;





int main() {

    omp_init_lock(&mutex);
  std::string filename1 = "../data/index.csv";
  std::string filename2 = "../data/index2.csv";
  std::string data1_1 = "../data/data1_1.csv";
  //std::string data1_2 = "data/data1_2.csv";
  std::string data2_1 = "../data/data2_1.csv";
  //std::string data2_2 = "data/data2_2.csv";

  int const cols = 14;
  int line_lenght = 161;
  int widths[cols] = {5, 6, 30, 2, 30, 2, 2, 40, 8, 5, 5, 2, 4, 6};
  int id_len = 5;
  std::string title[cols] =
      {"NumFila", "ID", "Name", "Age", "Nationality", "Overall", "Potential", "Club", "Value", "Wage", "Preferred Foot",
       "Jersey Number", "Height", "Weight"};

  int const cols2 = 6;
  int line_lenght2 = 526;
  int widths2[cols] = {5, 8, 127, 100, 160, 120};
  int id_len2 = 5;
  std::string title2[cols] = {"NumFila", "Commodity", "Segment Name", "Family Name", "Class Name", "Commodity Name"};

  auto random1 = new Random(filename1);
  auto random2 = new Random(filename2);

  auto manager1_1 = new CSVManager(data1_1, cols, line_lenght, widths[0], title[0], id_len);
  auto manager2_1 = new CSVManager(data2_1, cols2, line_lenght2, widths2[0], title2[0], id_len2);


  int op;
  int id;
#pragma opm parallel num_threads(2)
  {

  do {

      omp_set_lock(&mutex);
    std::cout << std::endl;
    std::cout << "Eliga una de las opciones:" << std::endl;
    std::cout << std::endl;
    std::cout << "1 : Buscar un dato por su ID  (Random Index)" << std::endl;
    std::cout << "2 : Añadir un nuevo dato      (Random Index)" << std::endl;
    std::cout << std::endl;
    std::cout << "0 : Exit" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    std::cin >> op;

    while (op < 0 || op > 2) {
      std::cout << "Opcion no valida, ingrese una nueva: " << std::endl;
      std::cin >> op;
    }

    switch (op) {
      case 1: {
        std::cout << "Ingresa ID a buscar: ";
        std::cin >> id;
          omp_unset_lock(&mutex);
          auto start = std::chrono::high_resolution_clock::now();

        key row = random1->search(id);

        if (row != -1) {
          manager1_1->get(row);
        }
          auto end = std::chrono::high_resolution_clock::now();

        std::cout << "-----------------------------------------------" << std::endl;

        std::chrono::duration<double> elapsed = end - start;
          std::cout<<"Search demora: "<<elapsed.count()<<" segundos"<<'\n';

        break;
      }
      case 2: {
          auto start2 = std::chrono::high_resolution_clock::now();


        manager1_1->insert(random1,&mutex);
          auto end2 = std::chrono::high_resolution_clock::now();
          std::chrono::duration<double> elapsed2 = end2 - start2;
          //std::cout<<"Search2 demora: "<<elapsed2.count()<<" segundos"<<'\n';

        std::cout << "-----------------------------------------------" << std::endl;
        break;
      }

    }

  } while (op != 0);
 }

  return 0;
}
