#ifndef BUCKET_H
#define BUCKET_H

#include <vector>

template <typename T>
class Bucket
{
private:
    int localDepht;
    int maxCapacity;
    std::vector<T> elements;
    std::vector<std::string> pointing;
    std::string docName;

public:
    Bucket(std::string docName)
    {
        this->maxCapacity = maxCapacity;
        this->localDepht = 1;
        this->docName = docName;
    }

    bool insert(T item)
    {
        if (this->elements.size() == this->maxCapacity)
        {
            return false;
        }
        else
        {
            this->elements.push_back(item);
            //std::fstream document(docName, std::ios::out | std::ios::app);
            //document << item->getCompleteRegister() << '\n';

            return true;
        }
    }

    bool insertPointing(std::string index)
    {
        if (!pointing.empty())
        {
            for (auto &i : pointing)
            {
                if (i == index)
                {
                    return false;
                }
            }
            this->pointing.push_back(index);
            return true;
        }
        this->pointing.push_back(index);
        return true;
    }

    std::vector<std::string> getPointing()
    {
        return this->pointing;
    }

    void setMaxCapacity(int maxCapacity)
    {
        this->maxCapacity = maxCapacity;
    }

    void setLocalDepht(int localDepht)
    {
        this->localDepht = localDepht;
    }

    void addLocalDepht()
    {
        this->localDepht += 1;
    }

    int getLocalDepht()
    {
        return this->localDepht;
    }

    std::vector<T> getElements()
    {
        return this->elements;
    }

    void emptyElements()
    {
        this->elements.clear();
    }

    std::vector<std::string> search(std::string key){
        for(auto &element : this->elements){
            if(element->getKey()==key){
                return element->getFields();
            }
        }
    }

    void print()
    {
        for (auto &i : elements)
        {
            std::cout << i->getKeyNumber() << " ";
        }
    }
};

#endif // !BUCKET_H
