#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "QuanLy.h"

using namespace std;

class Nhanvien
{
private:
    string name, soDienThoai;
    int maNhanvien, Luong;

public:
    void nhapMoi();
    void suaThongTin(const string &thongTinNhanvien);
    void xoaThongTin(const string &thongTinNhanvien);
    void timKiem();
    void daoTao();
    void thaoTac();
};

void Nhanvien::nhapMoi()
{
    cout << "Nhap ten nhan vien: ";
    getline(cin, name);
    cout << "Nhap so dien thoai: ";
    getline(cin, soDienThoai);
    cout << "Nhap so ma nhan vien: ";
    cin >> maNhanvien;
    cout << "Nhap so Luong:";
    cin >> Luong;

    cin.ignore();

    string banGhi = name + string(30 - name.size(), ' ') + "|" +
                    soDienThoai + string(30 - soDienThoai.size(), ' ') + "|" +
                    to_string(maNhanvien) + string(30 - to_string(maNhanvien).size(), ' ') + "|" +
                    to_string(Luong) + string(30 - to_string(Luong).size(), ' ');

    vector<string> data = quanly::readFromFile<string>("Nhanvien.txt");
    if (data.empty())
    {
        string tieuDe = "Ten nhan vien                |So dien thoai                 |So ma nhan vien                 |Luong";
        data.push_back(tieuDe);
    }
    data.push_back(banGhi);
    quanly::writeToFile("Nhanvien.txt", data);
    cout << "Da luu" << endl;
}

void Nhanvien::suaThongTin(const string &thongTinNhanvien)
{
    cout << "Nhap ten moi: ";
    getline(cin, name);
    cout << "Nhap so dien thoai moi: ";
    getline(cin, soDienThoai);
    cout << "Nhap so ma nhan vien moi: ";
    cin >> maNhanvien;
    cout << "Nhap so luong:";
    cin >> Luong;
    cin.ignore();

    string thongTinMoi = name + string(30 - name.size(), ' ') + "|" +
                         soDienThoai + string(30 - soDienThoai.size(), ' ') + "|" +
                         to_string(maNhanvien) + string(30 - to_string(maNhanvien).size(), ' ') + "|" +
                         to_string(Luong) + string(30 - to_string(Luong).size(), ' ');

    vector<string> data = quanly::readFromFile<string>("Nhanvien.txt");
    vector<string> updatedData;

    for (const string &line : data)
    {
        if (line == thongTinNhanvien)
        {
            updatedData.push_back(thongTinMoi);
        }
        else
        {
            updatedData.push_back(line);
        }
    }

    quanly::writeToFile("Nhanvien.txt", updatedData);
    cout << "Thong tin da duoc sua." << endl;
}

void Nhanvien::xoaThongTin(const string &thongTinNhanvien)
{
    vector<string> data = quanly::readFromFile<string>("Nhanvien.txt");
    vector<string> updatedData;

    for (const string &line : data)
    {
        if (line != thongTinNhanvien)
        {
            updatedData.push_back(line);
        }
    }

    quanly::writeToFile("Nhanvien.txt", updatedData);
    cout << "Thong tin da duoc xoa." << endl;
}

void Nhanvien::timKiem()
{
    int c;
    cout << "Nhan 1 de tim kiem theo ten" << endl
         << "Nhan 2 de tim kiem theo so dien thoai" << endl
         << "Nhan 3 de tim kiem theo ma nhan vien" << endl;
    cin >> c;
    cin.ignore();

    string Tim;
    if (c == 3)
    {
        int Tim2;
        cout << "Nhap so ma nhan vien can tim: ";
        cin >> Tim2;
        cin.ignore();
        Tim = to_string(Tim2);
    }
    else
    {
        cout << "Nhap thong tin can tim: ";
        getline(cin, Tim);
    }

    vector<string> data = quanly::readFromFile<string>("Nhanvien.txt");
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
        cout << "Nhan vien khong co trong danh sach" << endl;
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

void Nhanvien::daoTao()
{
    string chuongTrinh;
    cout << "Nhap chuong trinh dao tao: ";
    getline(cin, chuongTrinh);

    ofstream file("nhan_vien.txt", ios::app);
    if (file.is_open())
    {
        file << chuongTrinh << endl;
        file.close();
        cout << "Chuong trinh dao tao da duoc luu." << endl;
    }
    else
    {
        cout << "Khong the mo file de ghi." << endl;
    }
}

void Nhanvien::thaoTac()
{
    int n;
    do
    {
        cout << "Nhan 1 de nhap moi" << endl
             << "Nhan 2 de tim kiem" << endl
             << "Nhan 3 de dao tao" << endl
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
            daoTao();
        }
    } while (n != 0);
}

int main()
{
    Nhanvien nv;
    nv.thaoTac();
    return 0;
}