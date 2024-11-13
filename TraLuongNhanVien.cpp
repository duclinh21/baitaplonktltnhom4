#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include "QuanLy.h"
#include <sstream>
#include <vector> 

using namespace std;

class TraLuongNhanVien {
private:
    string tenNhanVien;
    string ngay;
    int LuongTheoGio = 20000;
    int checkIn;
    int checkOut;
    int luongTheoNgay; 

public:
    void tinhLuong();
    void traLuong();
    void thaoTac();
};

void TraLuongNhanVien::tinhLuong() {
    cout << "Nhap ten nhan vien: ";
    
    getline(cin, tenNhanVien);

    cout << "Ngay (ngay/thang/nam): ";
    getline(cin, ngay);

    cout << "Nhap thoi gian check in: ";
    cin >> checkIn;

    cout << "Nhap thoi gian check out: ";
    cin >> checkOut;
    cin.ignore();
    string checkInStr = to_string(checkIn);
    string checkOutStr = to_string(checkOut);
    
    luongTheoNgay = (checkOut - checkIn + 1) * LuongTheoGio;
    string luongTheoNgayStr = to_string(luongTheoNgay);
    
    string banGhi = tenNhanVien + string(30 - tenNhanVien.size(), ' ') + "|" +
                    ngay + string(30 - ngay.size(), ' ') + "|" +
                    checkInStr + string(10 - checkInStr.size(), ' ') + "|" +
                    checkOutStr + string(10 - checkOutStr.size(), ' ') + "|" +
					luongTheoNgayStr + string(10 - luongTheoNgayStr.size(), ' ');
                    
    
    cout <<  banGhi;
    vector<string> data = quanly::readFromFile<string>("TraLuong.txt");
    if (data.empty())
    {
        string tieuDe = "Ten Nhan Vien                 |Ngay                          |TI        |TO        |Luong theo ngay";
        data.push_back(tieuDe);
    }
    data.push_back(banGhi);
    quanly::writeToFile("TraLuong.txt", data);
    cout << "Da luu" << endl;
    vector<string> data2 = quanly::readFromFile<string>("NhanVien.txt");
    vector<string> updatedData;
    for(string &line : data2){
        if (line.find(tenNhanVien) != string::npos){
            stringstream ss(line);
                string ten, sdt, mnv, luong;
                getline(ss, ten, '|');
                getline(ss, sdt, '|');
                getline(ss, mnv, '|');
                getline(ss, luong, '|');
            
            int tongLuong = stoi(luong) + luongTheoNgay;

            ostringstream oss;
            oss <<  ten + string(30 - ten.size(), ' ') + "|" +
                    sdt + string(30 - sdt.size(), ' ') + "|" +
                    mnv + string(30 - mnv.size(), ' ') + "|" +
                    to_string(tongLuong) + string(30 - to_string(tongLuong).size(), ' ');

            line = oss.str();
            updatedData.push_back(line);
        } else {
            updatedData.push_back(line);
        }
    }
    quanly::writeToFile("NhanVien.txt", updatedData);
    cout << "Da cap nhat so luong hang hoa trong file." << endl;
}

void TraLuongNhanVien::traLuong(){
    vector<string> data2 = quanly::readFromFile<string>("NhanVien.txt");
    vector<string> updatedData;
    for(string &line : data2){
        if (line.find(tenNhanVien) != string::npos){
            stringstream ss(line);
                string ten, sdt, mnv, luong;
                getline(ss, ten, '|');
                getline(ss, sdt, '|');
                getline(ss, mnv, '|');
                getline(ss, luong, '|');
            
            cout << "Luong cuoi thang: " << luong << endl;

            int tongLuong = 0;

            ostringstream oss;
            oss <<  ten + string(30 - ten.size(), ' ') + "|" +
                    sdt + string(30 - sdt.size(), ' ') + "|" +
                    mnv + string(30 - mnv.size(), ' ') + "|" +
                    to_string(tongLuong) + string(30 - to_string(tongLuong).size(), ' ');

            line = oss.str();
            updatedData.push_back(line);
        } else {
            updatedData.push_back(line);
        }
    }
    quanly::writeToFile("NhanVien.txt", updatedData);
    cout << "Da cap nhat so luong hang hoa trong file." << endl;
}


void TraLuongNhanVien::thaoTac(){
    int chon;
    do{
        cin >> chon;
        cin.ignore();
        if(chon == 1){
            tinhLuong();
            stringstream ss(ngay);
                string day, month, year;
                getline(ss, day, '/');
                getline(ss, month, '/');
                getline(ss, year, '/');
            if(stoi(month) == 2){
                if(stoi(day)== 28){
                    traLuong();
                }
            }
            else if(stoi(month)==1||stoi(month)==3||stoi(month)==5||stoi(month)==7||stoi(month)==8||stoi(month)==10||stoi(month)==12){
                if(stoi(day)==31){
                    traLuong();
                }
            }
            else if(stoi(month)==4||stoi(month)==6||stoi(month)==9||stoi(month)==11){
                if(stoi(day)==30){
                    traLuong();
                }
            }
        }
    }while(chon != 0);
}

int main() {
    TraLuongNhanVien a;
    a.thaoTac();
    return 0;
}