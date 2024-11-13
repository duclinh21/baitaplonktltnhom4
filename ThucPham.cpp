#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "QuanLy.h"

using namespace std;

class ThucPham
{
private:
    string tenHang;
    int soLuong, giaTien;
    long long tongGiaTien;

public:
    void nhapMoi();
    void suaThongTin(const string &thongTinThucPham);
    void xoaThongTin(const string &thongTinThucPham);
    void timKiem();
    void hienThiKho();
    void thaoTac();
};

void ThucPham::nhapMoi(){
    cout << "Nhap ten thuc pham: ";
    getline(cin, tenHang);

    cout << "Nhap so luong: ";
    cin >> soLuong;
    cout << "Nhap gia Tien: ";
    cin >> giaTien;

    tongGiaTien = static_cast<long long>(soLuong) * giaTien;
    cout << "Tong gia Tien: " << tongGiaTien << endl;

    cin.ignore();  // Đảm bảo cin.ignore() để không bị lỗi khi đọc chuỗi sau đó.

    string banGhi = tenHang + string(30 - tenHang.size(), ' ') + "|" +
                    to_string(soLuong) + string(30 - to_string(soLuong).size(), ' ') + "|" +
                    to_string(giaTien) + string(30 - to_string(giaTien).size(), ' ') + "|" +
                    to_string(tongGiaTien) + string(30 - to_string(tongGiaTien).size(), ' ');

    vector<string> data = quanly::readFromFile<string>("khoThucPham.txt");
    if (data.empty()) {
        string tieuDe = "Ten thuc pham                 |So luong                      |Gia tien                      |Tong gia";
        data.push_back(tieuDe);
    }
    data.push_back(banGhi);
    quanly::writeToFile("khoThucPham.txt", data);

    cout << "Da luu" << endl;
}

void ThucPham::suaThongTin(const string &thongTinThucPham){
    cout << "Nhap ten moi: ";
    getline(cin, tenHang);

    cout << "Nhap so luong moi: ";
    cin >> soLuong;
    cout << "Nhap gia tien moi: ";
    cin >> giaTien;

    tongGiaTien = static_cast<long long>(soLuong) * giaTien;
    cout << "Tong gia tien moi: " << tongGiaTien << endl;
    cin.ignore();

    string thongTinMoi = tenHang + string(30 - tenHang.size(), ' ') + "|" +
                    to_string(soLuong) + string(30 - to_string(soLuong).size(), ' ') + "|" +
                    to_string(giaTien) + string(30 - to_string(giaTien).size(), ' ') + "|" +
                    to_string(tongGiaTien) + string(30 - to_string(tongGiaTien).size(), ' ');

    vector<string> data = quanly::readFromFile<string>("khoThucPham.txt");
    vector<string> updatedData;

    for (const string &line : data)
    {
        if (line == thongTinThucPham)
        {
            updatedData.push_back(thongTinMoi);
        }
        else
        {
            updatedData.push_back(line);
        }
    }

    quanly::writeToFile("khoThucPham.txt", updatedData);
    cout << "Thong tin da duoc sua." << endl;
}

void ThucPham::xoaThongTin(const string &thongTinThucPham)
{
    vector<string> data = quanly::readFromFile<string>("khoThucPham.txt");
    vector<string> updatedData;

    for (const string &line : data)
    {
        if (line != thongTinThucPham)
        {
            updatedData.push_back(line);
        }
    }

    quanly::writeToFile("khoThucPham.txt", updatedData);
    cout << "Thong tin da duoc xoa." << endl;
}


void ThucPham::timKiem()
{
    int c;
    cout << "Nhan 1 de tim kiem theo ten" << endl
         << "Nhan 2 de tim kiem theo so tien mua" << endl;
    cin >> c;
    cin.ignore();

    string Tim;
    if (c == 2)
    {
        int Tim2;
        cout << "Nhap so tien can tim: ";
        cin >> Tim2;
        cin.ignore();
        Tim = to_string(Tim2);
    }
    else if (c == 1)
    {
        cout << "Nhap thong tin can tim: ";
        getline(cin, Tim);
    }

    vector<string> data = quanly::readFromFile<string>("khoThucPham.txt");
    vector<string> TimThay;

    for (const string &line : data)
    {
        if (line.find(Tim) != string::npos)
        {
            TimThay.push_back(line);
        }
    }

    if (TimThay.empty())
    {
        cout << "Thuc pham khong co trong danh sach" << endl;
        return;
    }

    cout << "Ket qua tim kiem: " << endl;
    for (size_t i = 0; i < TimThay.size(); ++i)
    {
        cout << "Ket qua " << (i + 1) << ": " << TimThay[i] << endl;
    }

    int choice;
    cout << "Chon mot so de thao tac: " << endl;
    cout << "1. Xoa" << endl;
    cout << "2. Sua" << endl;
    cout << "0. Thoat" << endl;
    cin >> choice;
    cin.ignore();

    if (choice == 1)
    {
        if (TimThay.size() > 1)
        {
            int choice2;
            cout << "Chon ket qua de xoa: ";
            cin >> choice2;
            cin.ignore();
            xoaThongTin(TimThay[choice2 - 1]);
        }
        else
        {
            xoaThongTin(TimThay[0]);
        }
    }
    else if (choice == 2)
    {
        if (TimThay.size() == 1)
        {
            suaThongTin(TimThay[0]);
        }
        else
        {
            int choice3;
            cout << "Chon ket qua de sua: ";
            cin >> choice3;
            cin.ignore();
            if (choice3 > 0 && choice3 <= TimThay.size())
            {
                suaThongTin(TimThay[choice3 - 1]);
            }
            else
            {
                cout << "Chi so khong hop le." << endl;
            }
        }
    }
}

void ThucPham::hienThiKho() {
    // Đọc dữ liệu từ tệp khoThucPham.txt
    vector<string> data = quanly::readFromFile<string>("khoThucPham.txt");

    // Kiểm tra xem tệp có chứa dữ liệu hay không
    if (data.empty()) {
        cout << "Kho hang hien tai rong." << endl;
        return;
    }

    // Hiển thị tất cả các dòng từ tệp
    for (const string &line : data) {
        cout << line << endl;
    }

    cout << "-----------------------------------------------------------" << endl;
}

void ThucPham::thaoTac()
{
    int n;
    do
    {
        cout << "Nhan 1 de nhap moi" << endl
             << "Nhan 2 de tim kiem" << endl
             <<"Nhan 3 de hien thi kho"<<endl
             << "Nhan 0 de ket thuc" << endl;
        cin >> n;
        cin.ignore();
        if (n == 1)
        {
            nhapMoi();
        }
        else if (n == 2)
        {
            timKiem();
        }
        else if (n == 3)
        {
            hienThiKho();
        }
    } while (n != 0);
}

int main() {
    ThucPham thucpham;
    thucpham.thaoTac();
}
