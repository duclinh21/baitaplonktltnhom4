#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <map>
#include "QuanLy.h"
class KhachHang {
private:
    string name, soDienThoai, mucUuDai;  
    int soTienMua;
public:
    void nhapMoi();
    void suaThongTin(const string& thongTinKhachHang);
    void xoaThongTin(const string& thongTinKhachHang);
    void timKiem();
    void thaoTac();
    string layMucUuDai(int soTienMua);
};

string KhachHang::layMucUuDai(int soTienMua) {
    vector<string> data = quanly::readFromFile<string>("Uudai.txt");

    for (const string& line : data) {
        stringstream ss(line);
        string tenUuDai, giaTriDau, giaTriCuoi, menhGiaUuDai;
        getline(ss, tenUuDai, '|');
        getline(ss, giaTriDau, '|');
        getline(ss, giaTriCuoi, '|');
        getline(ss, menhGiaUuDai, '|');
        giaTriDau = giaTriDau.substr(0, giaTriDau.find_last_not_of(" ") + 1);
        giaTriCuoi = giaTriCuoi.substr(0, giaTriCuoi.find_last_not_of(" ") + 1);

        try {
            int minGiaTriDau = stoi(giaTriDau);
            int maxGiaTriCuoi = stoi(giaTriCuoi);

            if (soTienMua >= minGiaTriDau && soTienMua <= maxGiaTriCuoi) {
                return menhGiaUuDai;  
            }
        } catch (const invalid_argument& e) {
            continue;  
        } catch (const out_of_range& e) {
            continue;  
        }
    }
    return "Khong co uu dai";  
}

void KhachHang::nhapMoi() {
    cout << "Nhap ten khach hang: ";
    getline(cin, name);
    cout << "Nhap so dien thoai: ";
    getline(cin, soDienThoai);
    cout << "Nhap so tien mua hang: ";
    cin >> soTienMua;
    cin.ignore();


    mucUuDai = layMucUuDai(soTienMua);

    string banGhi = name + string(30 - name.size(), ' ') + "|" +
                    soDienThoai + string(30 - soDienThoai.size(), ' ') + "|" +
                    to_string(soTienMua) + string(30 - to_string(soTienMua).size(), ' ') + "|" +
                    mucUuDai;

    vector<string> data = quanly::readFromFile<string>("test.txt");
    if (data.empty()) {
        string tieuDe = "Ten khach hang                |So dien thoai                 |So tien mua hang              |Muc uu dai";
        data.push_back(tieuDe);
    }
    data.push_back(banGhi);
    quanly::writeToFile("test.txt", data);
    cout << "Da luu" << endl;
}

void KhachHang::suaThongTin(const string& thongTinKhachHang) {
    cout << "Nhap ten moi: ";
    getline(cin, name);
    cout << "Nhap so dien thoai moi: ";
    getline(cin, soDienThoai);
    cout << "Nhap so tien mua hang moi: ";
    cin >> soTienMua;
    cin.ignore();

 
    mucUuDai = layMucUuDai(soTienMua);

    string thongTinMoi = name + string(30 - name.size(), ' ') + "|" +
                         soDienThoai + string(30 - soDienThoai.size(), ' ') + "|" +
                         to_string(soTienMua) + string(30 - to_string(soTienMua).size(), ' ') + "|" +
                         mucUuDai;

    vector<string> data = quanly::readFromFile<string>("test.txt");
    vector<string> updatedData;

    for (const string& line : data) {
        if (line == thongTinKhachHang) {
            updatedData.push_back(thongTinMoi);
        } else {
            updatedData.push_back(line);
        }
    }

    quanly::writeToFile("test.txt", updatedData);
    cout << "Thong tin da duoc sua." << endl;
}

void KhachHang::xoaThongTin(const string& thongTinKhachHang) {
    vector<string> data = quanly::readFromFile<string>("test.txt");
    vector<string> updatedData;

    for (const string& line : data) {
        if (line != thongTinKhachHang) {
            updatedData.push_back(line);
        }
    }

    quanly::writeToFile("test.txt", updatedData);
    cout << "Thong tin da duoc xoa." << endl;
}

void KhachHang::timKiem() {
    int c;
    cout << "Nhan 1 de tim kiem theo ten" << endl
         << "Nhan 2 de tim kiem theo so dien thoai" << endl
         << "Nhan 3 de tim kiem theo so tien mua" << endl;
    cin >> c;
    cin.ignore();

    string Tim;
    if (c == 3) {
        int Tim2;
        cout << "Nhap so tien can tim: ";
        cin >> Tim2;
        cin.ignore();
        Tim = to_string(Tim2);
    } else {
        cout << "Nhap thong tin can tim: ";
        getline(cin, Tim);
    }

    vector<string> data = quanly::readFromFile<string>("test.txt");
    vector<string> TimThay;
    
    for (const string& line : data) {
        if (line.find(Tim) != string::npos) {
            TimThay.push_back(line);
        }
    }

    if (TimThay.empty()) {
        cout << "Khach hang khong co trong danh sach" << endl;
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

void KhachHang::thaoTac() {
    int n;
    do {
        cout << "Nhan 1 de nhap moi" << endl
             << "Nhan 2 de tim kiem" << endl
             << "Nhan 0 de ket thuc" << endl;
        cin >> n;
        cin.ignore();
        if (n == 1) {
            nhapMoi();
        } else if (n == 2) {
            timKiem();
        }
    } while (n != 0);
}

int main(){
    KhachHang kh;
    kh.thaoTac();
}
