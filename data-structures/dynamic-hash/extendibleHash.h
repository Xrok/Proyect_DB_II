/*
*Clase donde creamos la estructura del extendible Hash
*/

#ifndef EXTENDIBLEHASH_H
#define EXTENDIBLEHASH_H

#include <map>
#include <vector>
#include <math.h>
#include "bucket.h"

#define BITSET 20
#define DOC_NAME "documents/doc.csv"

template <typename T>
class ExtendibleHash
{
private:
    int globalDepht;
    int bucketsMaxSize;
    std::map<std::string, Bucket<T> *> hashTable;
    int cont;

public:
    ExtendibleHash() = default;

    void setHash(int);
    std::pair<std::string, std::string> split(std::string line, std::string delimiter)
    {
        std::string token = line.substr(0, line.find(delimiter));
        line.erase(0, line.find(delimiter) + delimiter.length());
        std::pair<std::string, std::string> sub_strings;
        sub_strings.first = token;
        sub_strings.second = line;
        return sub_strings;
    }
/*
*SETEAMOS EL HASH
*/
    ExtendibleHash(int bucketsMaxSize)
    {
        this->globalDepht = 1; // 13
        this->bucketsMaxSize = bucketsMaxSize;
        setHash(this->hashTable, this->globalDepht);
        cont = globalDepht;
    }

    void setHash(std::map<std::string, Bucket<T> *> &hashTable, int globalDepht)
    {

        std::string newDoc;
        for (int i = 0; i < pow(2, globalDepht); i++)
        {
            auto pair = split(DOC_NAME, ".");
            newDoc = pair.first + std::to_string(i) + "." + pair.second;
            std::ofstream ofs;
            ofs.open(newDoc, std::ofstream::out | std::ofstream::trunc);
            ofs.close();
            std::string hashIndex = std::bitset<BITSET>(i).to_string();
            Bucket<T> *newBucket = new Bucket<T>(newDoc);
            newBucket->setMaxCapacity(bucketsMaxSize);
            hashTable[hashIndex] = newBucket;
            newBucket->insertPointing(hashIndex);
        }
    }

    bool inside(std::string index, std::vector<std::string> vec)
    {
        for (auto &i : vec)
        {
            if (i == index)
            {
                return true;
            }
        }
        return false;
    }

/*
*Aqui desarrollamos la funcion de insercion, analizamos los dos casos principales y los dos secundarios: 
*1. Insertar cuando aun hay espacio en el bucket(documento).
*2. Cuando ya no hay espacio:
*   2.1 Cuando el local Depht es menor que el global Depht(anadir un bucket mas).
*   2.2 Cuando el local Depht es igual al global Depht.(extender el hash)
*/

    void insert(T item)
    {
        int power = std::pow(2, globalDepht);
        int num = item->getKeyNumber() % power;
        std::string hashIndex = std::bitset<BITSET>(num).to_string();
        hashTable[hashIndex]->setMaxCapacity(bucketsMaxSize);
/*
*1. Insertar cuando aun hay espacio en el bucket(documento).
*/
        if (hashTable[hashIndex]->insert(item))
        {
            hashTable[hashIndex]->insertPointing(hashIndex);
        }
 /*
*2. Cuando ya no hay espacio:
*/       
        else
        {
            /*
*2.1 Cuando el local Depht es menor que el global Depht(anadir un bucket mas).
*/
            if (hashTable[hashIndex]->getLocalDepht() < globalDepht)
            {

                std::vector<T> currentElements = hashTable[hashIndex]->getElements();
                std::vector<std::string> currentIndexed = hashTable[hashIndex]->getPointing();
                hashTable[hashIndex]->emptyElements();
                int currentLocalDepht = hashTable[hashIndex]->getLocalDepht() + 1;

                auto pair = split(DOC_NAME, ".");
                std::string newDoc = pair.first + std::to_string(cont) + "." + pair.second;
                cont++;
                Bucket<T> *newBucketL = new Bucket<T>(newDoc);
                newBucketL->setMaxCapacity(bucketsMaxSize);
                pair = split(DOC_NAME, ".");
                newDoc = pair.first + std::to_string(cont) + "." + pair.second;
                cont++;
                Bucket<T> *newBucketR = new Bucket<T>(newDoc);
                newBucketR->setMaxCapacity(bucketsMaxSize);

                std::string indexString1 = "";
                std::string indexString2 = "";

                for (auto &indexed : currentIndexed)
                {
                    std::string a = indexed.substr(indexed.length() - (this->globalDepht), indexed.length());
                    std::string b = std::string(BITSET - (this->globalDepht), '0') + a;
                    if (indexString1 == "" or indexString1 == b)
                    {
                        indexString1 = b;
                        hashTable[indexed] = newBucketL;
                        newBucketL->insertPointing(indexed);
                    }
                    if (b != indexString1)
                    {
                        indexString2 = b;
                        hashTable[indexed] = newBucketR;
                        newBucketR->insertPointing(indexed);
                    }
                }

                int cont = 0;
                for (auto &element : currentElements)
                {

                    int newHashIndex = element->getKeyNumber() % power;
                    std::string hashIndex5 = std::bitset<BITSET>(newHashIndex).to_string();
                    hashTable[hashIndex5]->setLocalDepht(currentLocalDepht);
                    hashTable[hashIndex5]->insert(element);
                    hashTable[hashIndex5]->insertPointing(hashIndex5);
                }
                int newHashIndex = item->getKeyNumber() % power;
                std::string hashIndex6 = std::bitset<BITSET>(newHashIndex).to_string();
                hashTable[hashIndex6]->insert(item);
                hashTable[hashIndex6]->insertPointing(hashIndex6);
            }
            /*
*2.2 Cuando el local Depht es igual al global Depht.(extender el hash)
*/
            else
            {
                std::map<std::string, Bucket<T> *> newHash;
                this->globalDepht += 1;
                setHash(newHash, this->globalDepht);
                for (auto &element : hashTable)
                {
                    int currentDepht = element.second->getLocalDepht() + 1;
                    if (element.first == hashIndex)
                    {
                        for (auto &items : element.second->getElements())
                        {
                            int power2 = std::pow(2, this->globalDepht);
                            int num2 = items->getKeyNumber() % power2;
                            std::string hashIndex = std::bitset<BITSET>(num2).to_string();
                            newHash[hashIndex]->setLocalDepht(currentDepht);
                            if (newHash[hashIndex]->insert(items))
                            {
                                newHash[hashIndex]->insertPointing(hashIndex);
                            }
                        }
                        int power3 = std::pow(2, this->globalDepht);
                        int num3 = item->getKeyNumber() % power3;
                        std::string newHashIndex2 = std::bitset<BITSET>(num3).to_string();
                        newHash[newHashIndex2]->insert(item);
                        newHash[newHashIndex2]->setLocalDepht(currentDepht);
                        newHash[newHashIndex2]->insertPointing(newHashIndex2);
                    }
                    else
                    {
                        element.second->insertPointing(element.first);
                        newHash[element.first] = element.second;
                    }
                }

                for (auto &registers : newHash)
                {
                    if (registers.second->getElements().empty())
                    {
                        std::string a = registers.first.substr(registers.first.length() - (this->globalDepht - 1), registers.first.length());
                        std::string b = std::string(BITSET - (this->globalDepht - 1), '0') + a;
                        hashTable[b]->insertPointing(registers.first);
                        registers.second = hashTable[b];
                    }
                }

                this->hashTable = newHash;
            }
        }
    }

    int transformString(std::string key)
    {
        int cont = 0;
        for (auto &i : key)
        {
            cont += i;
        }
        return cont;
    }
    std::string search(std::string key){
        int cont = transformString(key);
        int power = std::pow(2, globalDepht);
        int num = cont % power;
        std::string hashIndex = std::bitset<BITSET>(num).to_string();
        auto a =hashTable[hashIndex]->search(key);
        for(auto &field : a){
            std::cout<<field<<'\n';
        }
    }
    void print()
    {
        for (auto &bucket : hashTable)
        {
            std::cout << bucket.first << '\t' << "(" << bucket.second->getLocalDepht() << ") ";
            bucket.second->print();
            std::cout << '\n';
        }
    }
};

#endif // !EXTENDIBLEHASH_H
