#ifndef QUANLY_H
#define QUANLY_H

#include <fstream>
#include <vector>
#include <string>

using namespace std;
class quanly {
public:
    template<typename T>
    static vector<T> readFromFile(const string& tenfile);

    template<typename T>
    static void writeToFile(const string& tenfile, const vector<T>& data);
};

#endif