#ifndef HASHTABLE_H
#define HASHTABLE_H

struct Movie{
    std::string title;
    int year;
    Movie *next;

    Movie(){};

    Movie(std::string in_title, int in_year)
    {
        title = in_title;
        year = in_year;
    }

};

class HashTable
{
    public:
        HashTable(int);
        ~HashTable();
        void insertMovie(std::string, int);
        Movie* findMovie(std::string);
        void deleteMovie(std::string);
        void printInventory();
        int hSum(std::string);
    protected:
    private:
        Movie **hashTable;
        int tableSize;
};

#endif // HASHTABLE_H
