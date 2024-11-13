#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "QuanLy.h"

using namespace std;

class quanLyDatBan
{
private:
    string ten, sdt, loaiBan;
    int soLuongBan;
    const int giaBanThuong = 1000000; // Giá bàn thường
    const int giaBanVIP = 2000000;    // Giá bàn VIP

public:
    void datBan();
    void tinhTienBan();
    void thaoTac();

    // Hàm loại bỏ khoảng trắng thừa ở đầu và cuối chuỗi
    string trim(const string &str)
    {
        size_t first = str.find_first_not_of(' ');
        if (first == string::npos)
            return ""; // Không có ký tự nào ngoài khoảng trắng
        size_t last = str.find_last_not_of(' ');
        return str.substr(first, (last - first + 1));
    }
};

// Hàm đặt bàn
void quanLyDatBan::datBan()
{
    cout << "Nhap ten khach hang: ";
    getline(cin, ten);
    cout << "Nhap sdt: ";
    getline(cin, sdt);
    cout << "Nhap loai ban (Ban Thuong, Ban VIP): ";
    getline(cin, loaiBan);
    cout << "Nhap so luong ban: ";
    cin >> soLuongBan;
    cin.ignore(); // Bỏ qua ký tự '\n' còn sót lại trong bộ đệm

    // Loại bỏ khoảng trắng thừa và chuẩn hóa chuỗi loaiBan
    loaiBan = trim(loaiBan);
    if (loaiBan == "Ban Thuong")
    {
        vector<string> data = quanly::readFromFile<string>("khoThucPham.txt");
        for (auto line : data)
        {
            if(line.find())
        }
    }

    // Ghi thông tin vào file
    string banGhi = ten + string(30 - ten.size(), ' ') + "|" + sdt + string(30 - sdt.size(), ' ') +
                    "|" + loaiBan + string(30 - loaiBan.size(), ' ') + "|" +
                    to_string(soLuongBan) + string(30 - to_string(soLuongBan).size(), ' ');

    vector<string> data = quanly::readFromFile<string>("datBan.txt");
    if (data.empty())
    {
        string tieuDe = "Ten khach hang                |Sdt                           |Loai ban                      |So luong";
        data.push_back(tieuDe);
    }
    data.push_back(banGhi);
    quanly::writeToFile("datBan.txt", data);

    cout << "Da luu thong tin dat ban." << endl;
}

// Hàm tính tiền bàn
void quanLyDatBan::tinhTienBan()
{
    vector<string> data = quanly::readFromFile<string>("datBan.txt");

    if (data.size() <= 1)
    {
        cout << "Chua co du lieu dat ban!" << endl;
        return;
    }

    string tenKhach;
    cout << "Nhap ten khach hang de tinh tien: ";
    getline(cin, tenKhach);

    bool timThay = false;
    int tongTien = 0;
    string ten, sdt, loaiBan;
    int soLuong;

    // Duyệt qua các dòng dữ liệu trong file
    for (const string &line : data)
    {
        stringstream ss(line);

        getline(ss, ten, '|');
        getline(ss, sdt, '|');
        getline(ss, loaiBan, '|');
        ss >> soLuong;

        // Loại bỏ khoảng trắng thừa và chuẩn hóa chuỗi loaiBan
        loaiBan = trim(loaiBan);

        // Tìm kiếm tên khách hàng
        if (ten.find(tenKhach) != string::npos)
        {
            timThay = true;

            // Kiểm tra loại bàn và tính tiền
            if (loaiBan == "Ban Thuong")
            {
                tongTien += giaBanThuong * soLuong;
            }
            else if (loaiBan == "Ban VIP")
            {
                tongTien += giaBanVIP * soLuong;
            }
            else
            {
                cout << "Loai ban khong hop le: " << loaiBan << endl;
            }
        }
    }

    if (timThay)
    {
        cout << "Tong tien dat ban cho " << tenKhach << " la: " << tongTien << " VND." << endl;

        // Tạo bản ghi hóa đơn và lưu vào file bill.txt
        string billGhi = "Ten: " + tenKhach + string(30 - tenKhach.size(), ' ') +
                         "|" + sdt + string(30 - sdt.size(), ' ') +
                         "|" + loaiBan + string(30 - loaiBan.size(), ' ') +
                         "|" + to_string(soLuong) + string(30 - to_string(soLuong).size(), ' ') +
                         "|" + to_string(tongTien);

        // Đọc dữ liệu từ bill.txt
        vector<string> billData = quanly::readFromFile<string>("bill.txt");

        // Nếu file bill.txt trống, thêm tiêu đề
        if (billData.empty())
        {
            string tieuDe = "Ten Khach Hang                     |Sdt                           |Loai Ban                      |So Luong                      |Tong Tien";
            billData.push_back(tieuDe);
        }

        // Thêm thông tin hóa đơn vào billData
        billData.push_back(billGhi);

        // Ghi lại dữ liệu vào file bill.txt
        quanly::writeToFile("bill.txt", billData);

        cout << "Hoa don da duoc ghi vao file bill.txt." << endl;
    }
    else
    {
        cout << "Khong tim thay khach hang!" << endl;
    }
}
void quanLyDatBan::thaoTac()
{
    int chon;

    do
    {
        cout << "Menu:" << endl;
        cout << "1. Dat Ban" << endl;
        cout << "2. Tinh Tien Ban" << endl;
        cout << "0. Thoat" << endl;
        cout << "Chon thao tac: ";
        cin >> chon;
        cin.ignore(); // Bỏ qua ký tự '\n' còn lại trong bộ đệm

        switch (chon)
        {
        case 1:
            datBan();
            break;
        case 2:
            tinhTienBan();
            break;
        case 0:
            cout << "Thoat chuong trinh!" << endl;
            break;
        default:
            cout << "Chon sai! Vui long chon lai." << endl;
        }

    } while (chon != 0);
}

int main()
{
    quanLyDatBan qldt;
    qldt.thaoTac();
}
