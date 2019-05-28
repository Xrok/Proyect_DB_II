/*
*Clase donde guardamos como objeto a cada registro
*/

#ifndef REGISTER_H
#define REGISTER_H

#include <iostream>
#include <vector>

class Register
{
private:
    std::string completeRegister;
    std::string key;
    int keyNumber;
    std::vector<std::string> fields;

public:
    Register(std::string completeRegister, int keyIndex)
    {
        auto fields = splitWord(completeRegister);
        this->fields=fields;
        this->keyNumber = transformString(fields[keyIndex]);
        this->key=fields[keyIndex];
        this->completeRegister=completeRegister;
    }
    std::pair<std::string, std::string> split(std::string line, std::string delimiter)
    {
        std::string token = line.substr(0, line.find(delimiter));
        line.erase(0, line.find(delimiter) + delimiter.length());
        std::pair<std::string, std::string> sub_strings;
        sub_strings.first = token;
        sub_strings.second = line;
        return sub_strings;
    }

    std::vector<std::string> splitWord(std::string line)
    {
        std::vector<std::string> words;
        auto substr = split(line, ",");
        while (substr.first != substr.second)
        {
            words.push_back(substr.first);
            substr = split(substr.second, ",");
        }
        words.push_back(substr.first);
        return words;
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

    int getKeyNumber()
    {
        return this->keyNumber;
    }

    std::string getCompleteRegister()
    {
        return this->completeRegister;
    }

    std::vector<std::string> getFields(){
        return this->fields;
    }

    std::string getKey(){
        return this->key;
    }
};

#endif // REGISTER_H