#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include "QuanLy.h"
#include <sstream>
#include <vector>

using namespace std;

class ThuNhap
{
private:
    int ThuNhap;

public:
    int getthuNhap(){
        return ThuNhap;
    }
    void TinhThuNhap();
    void LuuThuNhap();
    void thaoTac();
};

string trim(const string &str)
{
    size_t start = 0;
    while (start < str.length() && isspace(str[start]))
    {
        start++;
    }

    size_t end = str.length();
    while (end > start && isspace(str[end - 1]))
    {
        end--;
    }

    return str.substr(start, end - start);
}

void ThuNhap::TinhThuNhap()
{
    int doanhThu = 0;
    // Doc file bill
    vector<string> data = quanly::readFromFile<string>("Bill.txt");
    if (data.empty())
    {
        cout << "Khong the doc du lieu tu file bill.txt" << endl;
        return;
    }

    if (!data.empty())
    {
        data.erase(data.begin());
    }
    for (const string &line : data)
    {
        stringstream ss(line);
        string name, sdt, loaiBan, soLuong, tongTien;
        getline(ss, name, '|');
        getline(ss, sdt, '|');
        getline(ss, loaiBan, '|');
        getline(ss, soLuong, '|');
        getline(ss, tongTien, '|');
        // cout << name << " " << sdt << " " << soLuong << " " << tongTien << endl;

        tongTien = trim(tongTien);

        int tongTienNhap = stoi(tongTien);
        doanhThu += tongTienNhap;
    }
    // End doc file bill

    // Doc file Kho thuc pham

    vector<string> records = quanly::readFromFile<string>("khoThucPham.txt");
    if (records.empty())
    {
        cout << "Khong the doc du lieu tu file bill.txt" << endl;
        return;
    }

    if (!records.empty())
    {
        records.erase(records.begin());
    }
    for (const string &line : records)
    {
        stringstream ss(line);
        string name, soLuong, giaTien, tongGia;
        getline(ss, name, '|');
        getline(ss, soLuong, '|');
        getline(ss, giaTien, '|');
        getline(ss, tongGia, '|');
        // cout << name << " " << soLuong << " " << giaTien << " " << tongGia << endl;

        int tongGiaNhap = stoi(tongGia);
        doanhThu -= tongGiaNhap;
    };
    ThuNhap = doanhThu;
    cout<<"Thu nhap: "<<ThuNhap<<endl;
}


void ThuNhap::LuuThuNhap()
{
    vector<string> output;
    int result = getthuNhap();
    output.push_back("Thu Nhap :"+to_string(result));
    quanly::writeToFile("thuNhap.txt", output);
    cout << "Da luu doanh thu vao file thuNhap.txt" << endl;
}

void ThuNhap::thaoTac(){
     int chon;
    do
    {
        cout << "Nhan 1 de tinh thu nhap" << endl
             << "Nhan 2 de luu thu nhap" << endl
             << "Nhan 0 de ket thuc" << endl;
        cin >> chon;
        // cin.ignore();
        if (chon == 1)
        {
            TinhThuNhap();
        }
        else if (chon == 2)
        {
            LuuThuNhap();
        }
    } while (chon != 0);

}


int main()
{
    ThuNhap thunhap;
    thunhap.thaoTac();

}