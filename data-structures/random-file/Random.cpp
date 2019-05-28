#ifndef SRC_RANDOM_CPP
#define SRC_RANDOM_CPP

#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

typedef int key;
typedef int position;

class Random {
 private:
  std::string filename;
  std::map<key, position> index;

 public:
  Random(std::string &filename) {
    this->filename = filename;
    loadIndex();
  }

  void loadIndex() {
    std::fstream file(this->filename, std::ios::in);
    std::string line;

    if (!file.is_open()) {
      std::cout << "No se pudo cargar el índice" << std::endl;
      return;
    }

    while (std::getline(file, line)) {
      std::vector<std::string> values;
      std::stringstream lineStream(line);
      std::string value;

      while (getline(lineStream, value, ',')) {
        values.push_back(value);
      }

      // Create id and position
      key id = std::stoi(values[0]);
      position pos = std::stoi(values[1]);

      this->index[id] = pos;
    }

    file.close();
  }

  void insert(key id, position pos) {
#pragma opm critical
      {
      this->index[id] = pos;

      std::fstream file(this->filename, std::ios::out | std::ios::app);

      file << id;
      file << ",";
      file << pos;
      file << "\n";

      file.close();
   }
  }

  position search(key id) {
    if (!this->index[id]) {
      std::cout << "Registro no encontrado" << std::endl;
      return -1;
    }

    return this->index[id];
  }

  void describe() {
    for (auto &element : this->index) {
      std::cout << element.first << " " << element.second << std::endl;
    }
  }
};

#endif
