#include "QuanLy.h"
#include <fstream>
#include <iostream>

using namespace std;

template<typename T>
vector<T> quanly::readFromFile(const string& tenfile) {
    ifstream file(tenfile);
    vector<T> data;
    T tmp;

    if (file.is_open()) {
        while (getline(file, tmp)) { 
            data.push_back(tmp);
        }
        file.close();
    }

    return data;
}

template<typename T>
void quanly::writeToFile(const string& tenfile, const vector<T>& data) {
    ofstream file(tenfile, ios::trunc);
    if (file.is_open()) { // Kiểm tra xem tệp có mở thành công không
        for (const auto& tmp : data) {
            file << tmp << endl; // Ghi từng đối tượng vào tệp
        }
        file.close(); // Đóng tệp sau khi ghi
    } else {
        cerr << "Khong the mo tep: " << tenfile << endl; // Thông báo lỗi nếu không mở được tệp
    }
}

// Explicit instantiation for std::string
template vector<string> quanly::readFromFile<string>(const string&);
template void quanly::writeToFile<string>(const string&, const vector<string>&);