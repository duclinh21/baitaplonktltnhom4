#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "QuanLy.h"

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

class quanLyDatBan {
private:
    string ten, sdt, loaiBan;
    int soLuongBan;
    const int giaBanThuong = 1000000;  // Giá bàn thường
    const int giaBanVIP = 2000000;     // Giá bàn VIP

public:
    void datBan();
    void tinhTienBan();
    void thaoTac();
    
    // Hàm loại bỏ khoảng trắng thừa ở đầu và cuối chuỗi
    string trim(const string &str) {
        size_t first = str.find_first_not_of(' ');
        if (first == string::npos) return "";  // Không có ký tự nào ngoài khoảng trắng
        size_t last = str.find_last_not_of(' ');
        return str.substr(first, (last - first + 1));
    }
};

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

void quanLyDatBan::datBan() {
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
    
    // Ghi thông tin vào file
    string banGhi = ten + string(30 - ten.size(), ' ') + "|" + sdt + string(30 - sdt.size(), ' ') +
                    "|" + loaiBan + string(30 - loaiBan.size(), ' ') + "|" +
                    to_string(soLuongBan) + string(30 - to_string(soLuongBan).size(), ' ');

    vector<string> data = quanly::readFromFile<string>("datBan.txt");
    if (data.empty()) {
        string tieuDe = "Ten khach hang                |Sdt                           |Loai ban                      |So luong";
        data.push_back(tieuDe);
    }
    data.push_back(banGhi);
    quanly::writeToFile("datBan.txt", data);

    cout << "Da luu thong tin dat ban." << endl;
}

void quanLyDatBan::tinhTienBan() {
    vector<string> data = quanly::readFromFile<string>("datBan.txt");

    if (data.size() <= 1) {
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
    for (const string &line : data) {
        stringstream ss(line);

        getline(ss, ten, '|');
        getline(ss, sdt, '|');
        getline(ss, loaiBan, '|');
        ss >> soLuong;

        // Loại bỏ khoảng trắng thừa và chuẩn hóa chuỗi loaiBan
        loaiBan = trim(loaiBan);

        // Tìm kiếm tên khách hàng
        if (ten.find(tenKhach) != string::npos) {
            timThay = true;

            // Kiểm tra loại bàn và tính tiền
            if (loaiBan == "Ban Thuong") {
                tongTien += giaBanThuong * soLuong;
            } else if (loaiBan == "Ban VIP") {
                tongTien += giaBanVIP * soLuong;
            } else {
                cout << "Loai ban khong hop le: " << loaiBan << endl;
            }
        }
    }

    if (timThay) {
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
        if (billData.empty()) {
            string tieuDe = "Ten Khach Hang                     |Sdt                           |Loai Ban                      |So Luong                      |Tong Tien";
            billData.push_back(tieuDe);
        }

        // Thêm thông tin hóa đơn vào billData
        billData.push_back(billGhi);

        // Ghi lại dữ liệu vào file bill.txt
        quanly::writeToFile("bill.txt", billData);

        cout << "Hoa don da duoc ghi vao file bill.txt." << endl;
    } else {
        cout << "Khong tim thay khach hang!" << endl;
    }
}
void quanLyDatBan::thaoTac(){
    int chon;

    do {
        cout << "Menu:" << endl;
        cout << "1. Dat Ban" << endl;
        cout << "2. Tinh Tien Ban" << endl;
        cout << "0. Thoat" << endl;
        cout << "Chon thao tac: ";
        cin >> chon;
        cin.ignore(); // Bỏ qua ký tự '\n' còn lại trong bộ đệm

        switch (chon) {
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

    int chon;
    do{
        cout<<"-----HE THONG QUAN LY NHA HANG-----"<<endl;
        cout<<"nhan 1 de thao tac thuc pham"<<endl;
        cout<<"nhan 2 de thao tac khach hang"<<endl;
        cout<<"nhan 3 de thao tac quan ly dat ban"<<endl;
        cout<<"nhan 4 de thao tac nhan vien"<<endl;
        cout<<"nhan 5 de thao tac tra luong nhan vien"<<endl;
        cout<<"nhan 6 de thao tac thu nhap"<<endl;
        cout<<"nhan 7 de thao tac uu dai"<<endl;
        cout<<"nhan 0 de dong chuong trinh"<<endl;
        // cin.ignore();
        cin>>chon;

        if(chon==1){
           ThucPham thucpham;
           thucpham.thaoTac();
        }
        if(chon==2){
            KhachHang khachhang;
            khachhang.thaoTac();
        }
        if(chon==3){
            quanLyDatBan qldb;
            qldb.thaoTac();
        }
        if(chon==4){
            Nhanvien nhanvien;
            nhanvien.thaoTac();
        }
        if(chon==5){
            TraLuongNhanVien tlnv;
            tlnv.thaoTac();
        }
        if(chon==6){
            ThuNhap thunhap;
            thunhap.thaoTac();
        }
        if(chon==7){
            Uudai ud;
            ud.thaoTac();
        }
        if(chon==0){
            cout<<"Ket thuc"<<endl;
        }


    }while(chon!=0);
    return 0;
}







