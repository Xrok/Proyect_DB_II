#ifndef MANAGER_CSVMANAGER_HPP
#define MANAGER_CSVMANAGER_HPP

#include <fstream>
#include "iostream"

class CSVManager {
  std::string path;
  int cols;
  int line_lenght;
  int *widths;
  std::string *titles;
  int id_counter;

 public:
  CSVManager(std::string &path, int cols, int line_lenght, int &width, std::string &titles, int id_counter) {
    this->path = path;
    this->cols = cols;
    this->line_lenght = line_lenght;
    this->widths = &width;
    this->titles = &titles;
    this->id_counter = id_counter;

  }

  std::string requestData() {
    std::string output = "";
    std::string atrib;

    for (int i = 2; i < cols - 1; ++i) {
      std::cout << this->titles[i] << " : ";
      std::cin >> atrib;
      atrib = atrib + std::string(widths[i] - atrib.length(), ' ');
      output = output + atrib + ',';

    }
    std::cout << titles[cols - 1] + ": ";
    std::cin >> atrib;
    atrib = atrib + std::string(widths[cols - 1] - atrib.length(), ' ');
    output = output + atrib + '\n';

    return output;
  }
  void get(int id) {
    int length = this->line_lenght;
    int pos = id;

    std::ifstream db;

    db.open(path, std::ifstream::in);

    if (!db.is_open()) {
      std::cout << "No se pudo abrir el archivo." << std::endl;
    } else {
      db.seekg(pos * length);

      char *line = new char[length];
      db.read(line, length);
      int p = 0;
      for (int i = 0; i < cols; ++i) {
        std::cout << titles[i] << ": ";

        for (int j = 0; j < widths[i]; ++j) {
          if (line[p] == ',') {
            j--;
          } else {
            std::cout << line[p];

          }
          p++;
        }
        std::cout << std::endl;
      }
    }
  }

  void insert(Random *random,omp_lock_t *mutex) {
    std::string output = "";
    int id;
    std::string atrib_str;
    std::cout << this->titles[1] << " : ";
    std::cin >> id;
    atrib_str = std::to_string(id);

    atrib_str = atrib_str + std::string(widths[1] - atrib_str.length(), ' ');

    output = output + atrib_str + ',';

    output = output + requestData();
      omp_unset_lock(mutex);

    std::fstream db;

    db.open(this->path, std::ios::out | std::ios::in | std::ios::app);

    db.seekg(-line_lenght, std::ios::end);

    char *n_row = new char[id_counter];
    db.read(n_row, id_counter);
    int next_row = std::stoi(n_row) + 1;

    std::string line_num = std::to_string(next_row);

    line_num = line_num + std::string(id_counter - line_num.length(), ' ');

    output = line_num + ',' + output;

    db.seekg(std::ios::end);

    db << output;

    random->insert(id, next_row);
  }

};

#endif //MANAGER_CSVMANAGER_HPP
