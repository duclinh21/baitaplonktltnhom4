#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <map>
#include "QuanLy.h"
class Uudai {
private:
    string name, Sodau, Socuoi, Menhgia; 
public:
    void NhapMoi();
    void timKiem();
    void suaThongTin(const string& ttUudai);
    void xoaThongTin(const string& ttUudai);
    void thaoTac();
}; 

void Uudai::NhapMoi() {
    cout << "Nhap ten uu dai: ";
    getline(cin, name);
    cout << "Nhap muc tien uu dai dau: ";
    getline(cin, Sodau);
    cout << "Nhap muc tien uu dai cuoi: ";
    getline(cin, Socuoi);
    cout << "Nhap menh gia uu dai: ";
    getline(cin, Menhgia);

    string banGhi = name + string(30 - name.size(), ' ') + "|" +
                    Sodau + string(30 - Sodau.size(), ' ') + "|" +
                    Socuoi + string(30 - Socuoi.size(), ' ') + "|" +
                    Menhgia + string(20 - Menhgia.size(), ' ');

    vector<string> data = quanly::readFromFile<string>("Uudai.txt");
    if (data.empty()) {
        string Loaiuudai = "Ten uu dai                    |Gia tri dau                   |Gia tri cuoi                  |Menh gia uu dai";
        data.push_back(Loaiuudai);
    }
    data.push_back(banGhi);
    quanly::writeToFile("Uudai.txt", data);
    cout << "Da luu" << endl;
}

void Uudai::suaThongTin(const string& ttUudai) {
    cout << "Nhap ten moi: ";
    getline(cin, name);
    cout << "Nhap muc tien dau moi: ";
    getline(cin, Sodau);
    cout << "Nhap muc tien cuoi moi: ";
    getline(cin, Socuoi);
    cout << "Nhap menh gia moi: ";
    getline(cin, Menhgia);

    string thongTinMoi = name + string(30 - name.size(), ' ') + "|" +
                         Sodau + string(30 - Sodau.size(), ' ') + "|" +
                         Socuoi + string(30 - Socuoi.size(), ' ') + "|" +
                         Menhgia + string(20 - Menhgia.size(), ' ');

    vector<string> data = quanly::readFromFile<string>("Uudai.txt");
    vector<string> updatedData;

    for (const string& line : data) {
        if (line == ttUudai) {
            updatedData.push_back(thongTinMoi);
        } else {
            updatedData.push_back(line);
        }
    }

    quanly::writeToFile("Uudai.txt", updatedData);
    cout << "Thong tin da duoc sua." << endl;
}

void Uudai::xoaThongTin(const string& ttUudai) {
    vector<string> data = quanly::readFromFile<string>("Uudai.txt");
    vector<string> updatedData;

    for (const string& line : data) {
        if (line != ttUudai) {
            updatedData.push_back(line);
        }
    }

    quanly::writeToFile("Uudai.txt", updatedData);
    cout << "Thong tin da duoc xoa." << endl;
}

void Uudai::timKiem() {
    int c;
    cout << "Nhan 1 de tim kiem theo ten" << endl
         << "Nhan 2 de tim kiem menh gia uu dai" << endl;
    cin >> c;
    cin.ignore();

    string Tim;
    if (c == 2) {
        cout << "Nhap menh gia uu dai can tim: ";
        getline(cin, Tim);
    } else {
        cout << "Nhap thong tin can tim: ";
        getline(cin, Tim);
    }

    vector<string> data = quanly::readFromFile<string>("Uudai.txt");
    vector<string> TimThay;
    
    for (const string& line : data) {
        if (line.find(Tim) != string::npos) {
            TimThay.push_back(line);
        }
    }

    if (TimThay.empty()) {
        cout << "Thong tin khong co trong danh sach" << endl;
        return;
    }

    cout << "Ket qua tim kiem: " << endl;
    for (size_t i = 0; i < TimThay.size(); ++i) {
        cout << "Ket qua " << (i + 1) << ": " << TimThay[i] << endl;
    }

    int choice;
    cout << "Chon mot so de thao tac: " << endl;
    cout << "1. Xoa" << endl;
    cout << "2. Sua" << endl;
    cout << "0. Thoat" << endl;
    cin >> choice;
    cin.ignore();

    if (choice == 1) {
        if (TimThay.size() > 1) {
            int choice2;
            cout << "Chon ket qua de xoa: ";
            cin >> choice2;
            cin.ignore();
            xoaThongTin(TimThay[choice2 - 1]);
        } else {
            xoaThongTin(TimThay[0]);
        }
    } else if (choice == 2) {
        if (TimThay.size() == 1) {
            suaThongTin(TimThay[0]);
        } else {
            int choice3;
            cout << "Chon ket qua de sua: ";
            cin >> choice3;
            cin.ignore();
            if (choice3 > 0 && choice3 <= TimThay.size()) {
                suaThongTin(TimThay[choice3 - 1]);
            } else {
                cout << "Chi so khong hop le." << endl;
            }
        }
    }
}

void Uudai::thaoTac() {
    int n;
    do {
        cout << "Nhan 1 de them 1 uu dai" << endl
             << "Nhan 2 de tim uu dai" << endl
             << "Nhan 0 de ket thuc" << endl;
        cin >> n;
        cin.ignore();
        if (n == 1) {
            NhapMoi();
        } else if (n == 2) {
            timKiem();
        }
    } while (n != 0);
}

int main(){
    Uudai uudai;
    uudai.thaoTac();
}