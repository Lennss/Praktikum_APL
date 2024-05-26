#include <iostream> // 
#include <fstream> //
#include <string> // 
#include <iomanip> //
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <limits>
#include <conio.h>
#include <algorithm>
#include <windows.h>

using namespace std;

// menentukan batas maksimum barang, user, dan peminjaman
const int MAX_BARANG = 10000;
const int MAX_USER = 1000;
const int MAX_PEMINJAMAN = 10000;

// Struct barang
struct Barang {
    string uuid;
    string nama;
    string jenis;
    int jumlah;
    string tanggal;
};

// Struct peminjaman
struct Peminjaman {
    string username;
    string uuid;
    string nama;
    string jenis;
    int jumlah;
    string tanggal;
    string tanggal_pinjam;
};

// Struct user
struct User {
    string username;
    string password;
};

// Menentukan variabel global
int jumlahBarang = 0;
int jumlahUser = 0;
int jumlahPeminjaman = 0;
int jumlahHasilPencarian = 0;

// Array of struct
Barang daftarBarang[MAX_BARANG];
User daftarUser[MAX_USER];
Peminjaman daftarPeminjaman[MAX_PEMINJAMAN];
Barang hasilPencarian[MAX_BARANG];

// Deklarasi fungsi untuk generate UUID secara random
string generateUUID() {
    stringstream ss;
    for (int i = 0; i < 4; ++i) {
        int r = rand() % 16;
        ss << hex << r;
    }
    return ss.str();
}

// Deklarasi fungsi untuk membuat notifikasi terhapus ketika sudah 1 detik
void delayNotif() {
    Sleep(1000);
    system("cls");
}

// Deklarasi fungsi untuk membuat user harus memberikan input tertentu untuk melanjutkan
void action() {
    char ch;
    cout << "Tekan spasi atau enter untuk melanjutkan..." << endl;
    do {
        ch = _getch();
    } while (ch != ' ' && ch != '\r');
    system("cls");
}

// Deklarasi fungsi untuk menyimpan data barang, peminjaman, dan user ke dalam file csv
void saveBarang() {
    ofstream file("data/barang.csv");
    if (file.is_open()) {
        for (int i = 0; i < jumlahBarang; i++) {
            file << daftarBarang[i].uuid << "," << daftarBarang[i].nama << "," << daftarBarang[i].jenis << "," << daftarBarang[i].jumlah << "," << daftarBarang[i].tanggal << endl;
        }
        file.close();
    }
}

// Deklarasi fungsi untuk menyimpan data peminjaman ke dalam file csv
void savePeminjaman() {
    ofstream file("data/peminjaman.csv");
    if (file.is_open()) {
        for (int i = 0; i < jumlahPeminjaman; i++) {
            file << daftarPeminjaman[i].username << "," << daftarPeminjaman[i].uuid << "," << daftarPeminjaman[i].nama << "," << daftarPeminjaman[i].jenis << "," << daftarPeminjaman[i].jumlah << "," << daftarPeminjaman[i].tanggal << "," << daftarPeminjaman[i].tanggal_pinjam << endl;
        }
        file.close();
    }
}

// Deklarasi fungsi untuk menyimpan data user ke dalam file csv
void saveUser() {
    ofstream file("data/user.csv");
    if (file.is_open()) {
        for (int i = 0; i < jumlahUser; i++) {
            file << daftarUser[i].username << "," << daftarUser[i].password << endl;
        }
        file.close();
    }
}

void loadBarang() {
    ifstream file("data/barang.csv");
    if (file.is_open()) {
        jumlahBarang = 0;
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string uuid, nama, jenis, tanggal;
            int jumlah;
            getline(ss, uuid, ',');
            getline(ss, nama, ',');
            getline(ss, jenis, ',');
            ss >> jumlah;
            ss.ignore();
            getline(ss, tanggal);
            daftarBarang[jumlahBarang].uuid = uuid;
            daftarBarang[jumlahBarang].nama = nama;
            daftarBarang[jumlahBarang].jenis = jenis;
            daftarBarang[jumlahBarang].jumlah = jumlah;
            daftarBarang[jumlahBarang].tanggal = tanggal;
            jumlahBarang++;
        }
        file.close();
    }
}

// Deklarasi fungsi untuk memuat/membaca data barang dari file csv
void loadPeminjaman() {
    ifstream file("data/peminjaman.csv");
    if (file.is_open()) {
        jumlahPeminjaman = 0;
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string username, uuid, nama, jenis, tanggal, tanggal_pinjam;
            int jumlah;
            getline(ss, username, ',');
            getline(ss, uuid, ',');
            getline(ss, nama, ',');
            getline(ss, jenis, ',');
            ss >> jumlah;
            ss.ignore();
            getline(ss, tanggal, ',');
            getline(ss, tanggal_pinjam);
            daftarPeminjaman[jumlahPeminjaman].username = username;
            daftarPeminjaman[jumlahPeminjaman].uuid = uuid;
            daftarPeminjaman[jumlahPeminjaman].nama = nama;
            daftarPeminjaman[jumlahPeminjaman].jenis = jenis;
            daftarPeminjaman[jumlahPeminjaman].jumlah = jumlah;
            daftarPeminjaman[jumlahPeminjaman].tanggal = tanggal;
            daftarPeminjaman[jumlahPeminjaman].tanggal_pinjam = tanggal_pinjam;
            jumlahPeminjaman++;
        }
        file.close();
    }
}

// Deklarasi fungsi untuk memuat/membaca data user dari file csv
void loadUser() {
    ifstream file("data/user.csv");
    if (file.is_open()) {
        jumlahUser = 0;
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string username, password;
            getline(ss, username, ',');
            getline(ss, password);
            daftarUser[jumlahUser].username = username;
            daftarUser[jumlahUser].password = password;
            jumlahUser++;
        }
        file.close();
    }
}



// Deklarasi fungsi untuk menampilkan data barang ke dalam bentuk tabel
void printTable(const Barang* data, int jumlah) {
    cout << "+==========================================================================================+" << endl;
    cout << "|  UUID  |          Nama Barang         |           Jenis          |  Jumlah  |  Tanggal   |" << endl;
    cout << "+==========================================================================================+" << endl;
    for (int i = 0; i < jumlah; i++) {
        cout << "|  " << setw(5) << left << data[i].uuid << " | " << setw(28) << data[i].nama << " | " << setw(24) << data[i].jenis << " | " << setw(8) << data[i].jumlah << " | " << setw(8) << data[i].tanggal << " |" << endl;
    }
    cout << "+==========================================================================================+" << endl;
}

// Deklarasi fungsi untuk menampilkan data peminjaman ke dalam bentuk tabel
void printTablePeminjaman(const Peminjaman* data, int jumlah) {
    cout << "+====================================================================================================================+" << endl;
    cout << "|  Username  |    UUID    |          Nama Barang         |           Jenis          |  Jumlah  |   Tanggal Pinjam    |" << endl;
    cout << "+====================================================================================================================+" << endl;
    for (int i = 0; i < jumlah; i++) {
        cout << "| " << setw(10) << left << data[i].username << " | " << setw(10) << data[i].uuid << " | " << setw(28) << data[i].nama << " | " << setw(24) << data[i].jenis << " | " << setw(8) << data[i].jumlah << " | " << setw(15) << data[i].tanggal_pinjam << " |" << endl;
    }
    cout << "+====================================================================================================================+" << endl;
}

// Deklarasi fungsi untuk menampilkan data peminjaman ke dalam bentuk tabel
void printTablePeminjamanAdmin(const Peminjaman* data, int jumlah) {
    for (int i = 0; i < jumlahUser; i++) {
        bool hasPeminjaman = false;
        for (int j = 0; j < jumlah; j++) {
            if (data[j].username == daftarUser[i].username) {
                if (!hasPeminjaman) {
                    cout << "\nPeminjaman oleh: " << daftarUser[i].username << endl;
                    cout << "+=======================================================================================================+" << endl;
                    cout << "|    UUID    |          Nama Barang         |           Jenis          |  Jumlah  |    Tanggal Pinjam   |" << endl;
                    cout << "+=======================================================================================================+" << endl;
                    hasPeminjaman = true;
                }
                cout << "|    " << setw(7) << left << data[j].uuid << " | " << setw(28) << data[j].nama << " | " << setw(24) << data[j].jenis << " | " << setw(8) << data[j].jumlah << " | " << setw(19) << data[j].tanggal_pinjam << " |" << endl;
            }
        }
        if (hasPeminjaman) {
            cout << "+=======================================================================================================+" << endl;
        }
    }
}

// Deklarasi fungsi untuk menampilkan data akun user ke dalam bentuk tabel
void lihatAkunUser() {
    for (int i = 0; i < jumlahUser - 1; i++) {
        for (int j = 0; j < jumlahUser - i - 1; j++) {
            if (daftarUser[j].username > daftarUser[j + 1].username) {
                swap(daftarUser[j], daftarUser[j + 1]);
            }
        }
    }

    cout << "+=======================================================+" << endl;
    cout << "|          Username          |         Password         |" << endl;
    cout << "+=======================================================+" << endl;
    for (int i = 0; i < jumlahUser; i++) {
        cout << "| " << setw(26) << left << daftarUser[i].username << " | " << setw(24) << daftarUser[i].password << " |" << endl;
    }
    cout << "+=======================================================+" << endl;
}

// Deklarasi fungsi untuk menampilkan menu login
void showMenuLogin() {
    cout << endl;
    cout << "+================================================+" << endl;
    cout << "|               Management System                |" << endl;
    cout << "+================================================+" << endl;
    cout << "|                                                |" << endl;
    cout << "|     [1]-------------+   [2]-------------+      |" << endl;
    cout << "|      |     Login    |    |   Register   |      |" << endl;
    cout << "|      +--------------+    +--------------+      |" << endl;
    cout << "|                                                |" << endl;
    cout << "| << Exit[0]                                     |" << endl;
    cout << "+================================================+" << endl;
    cout << "Pilih menu: ";
}

// Deklarasi fungsi untuk menampilkan menu admin
void showMenuAdmin() {
    cout << endl;
    cout << "+================================================+" << endl;
    cout << "|               Management System                |" << endl;
    cout << "+================================================+" << endl;
    cout << "|                                                |" << endl;
    cout << "|   [1]----------------+ [2]----------------+    |" << endl;
    cout << "|    | Tambah Barang   |  | Lihat & Search  |    |" << endl;
    cout << "|    +-----------------+  +-----------------+    |" << endl;
    cout << "|                                                |" << endl;
    cout << "|   [3]----------------+ [4]----------------+    |" << endl;
    cout << "|    | Ubah Barang     |  | Hapus Barang    |    |" << endl;
    cout << "|    +-----------------+  +-----------------+    |" << endl;
    cout << "|                                                |" << endl;
    cout << "|   [5]----------------+ [6]----------------+    |" << endl;
    cout << "|    | Lihat Akun User |  | Lihat Peminjaman|    |" << endl;
    cout << "|    +-----------------+  +-----------------+    |" << endl;
    cout << "|                                                |" << endl;
    cout << "|                                                |" << endl;
    cout << "| << Exit[0]                                     |" << endl;
    cout << "+================================================+" << endl;
    cout << "Pilih menu: ";
}

// Deklarasi fungsi untuk menampilkan menu ubah barang
void showMenuUbahBarang() {
    cout << endl;
    cout << "+================================================+" << endl;
    cout << "|               Menu Ubah Barang                 |" << endl;
    cout << "+================================================+" << endl;
    cout << "|                                                |" << endl;
    cout << "|    [1]--------------+ [2]---------------+      |" << endl;
    cout << "|     | Nama Barang   |  | Jenis Barang   |      |" << endl;
    cout << "|     +---------------+  +----------------+      |" << endl;
    cout << "|                                                |" << endl;
    cout << "|    [3]--------------+ [4]---------------+      |" << endl;
    cout << "|     | Jumlah Barang |  | Tanggal Barang |      |" << endl;
    cout << "|     +---------------+  +----------------+      |" << endl;
    cout << "|                                                |" << endl;
    cout << "| << Kembali[0]                                  |" << endl;
    cout << "+================================================+" << endl;
    cout << "Pilih menu: ";
}

// Deklarasi fungsi untuk menampilkan menu user
void showMenuUser() {
    cout << endl;
    cout << "+================================================+" << endl;
    cout << "|               Management System                |" << endl;
    cout << "+================================================+" << endl;
    cout << "|                                                |" << endl;
    cout << "|   [1]---------------+ [2]------------------+   |" << endl;
    cout << "|    | Lihat & Search |  | Lihat Peminjaman  |   |" << endl;
    cout << "|    +----------------+  +-------------------+   |" << endl;
    cout << "|                                                |" << endl;
    cout << "|   [3]---------------+ [4]------------------+   |" << endl;
    cout << "|    | Pinjam Barang  |  | Kembalikan Barang |   |" << endl;
    cout << "|    +----------------+  +-------------------+   |" << endl;
    cout << "|                                                |" << endl;
    cout << "| << Exit[0]                                     |" << endl;
    cout << "+================================================+" << endl;
    cout << "Pilih menu: ";
}

// Deklarasi fungsi untuk menampilkan menu lihat barang user
void showMenuLihatBarangUser() {
    cout << endl;
    cout << "+================================================+" << endl;
    cout << "|           Menu Lihat dan Search Barang         |" << endl;
    cout << "+================================================+" << endl;
    cout << "|                                                |" << endl;
    cout << "|    [1]--------------+  [2]---------------+     |" << endl;
    cout << "|     | Lihat Barang  |   | Cari Barang    |     |" << endl;
    cout << "|     +---------------+   +----------------+     |" << endl;
    cout << "|                                                |" << endl;
    cout << "| << Kembali[0]                                  |" << endl;
    cout << "+================================================+" << endl;
    cout << "Pilih menu: ";
}

// Deklarasi fungsi untuk menampilkan data barang
void lihatBarang() {
    system("cls");
    if (jumlahBarang == 0) {
        cout << "-----------------------------------" << endl;
        cout << "  Tidak ada barang yang tersedia!" << endl;
        cout << "-----------------------------------" << endl;
        delayNotif();
    } else {
        printTable(daftarBarang, jumlahBarang);
    }

}

// Deklarasi fungsi untuk menambahkan barang
void tambahBarang() {
    string nama, jenis, tanggal;
    int jumlah;
    if (jumlahBarang >= MAX_BARANG) {
        system("cls");
        cout << "------------------------------------------------" << endl;
        cout << " Jumlah barang sudah mencapai batas maksimum!" << endl;
        cout << "------------------------------------------------" << endl;
        delayNotif();
        return;
    }
    system("cls");
    cout << "+================================================+" << endl;
    cout << "|                  Tambah Barang                 |" << endl;
    cout << "+================================================+" << endl;
    cout << " Masukkan nama barang: ";
    cin.ignore();
    while (nama.empty()) {
        getline(cin, nama);
        if (nama.empty()) {
            system("cls");
            cout << "-----------------------------------" << endl;
            cout << "  Nama barang tidak boleh kosong!" << endl;
            cout << "-----------------------------------" << endl;
            delayNotif();
            cout << " Masukkan nama barang: ";
        }
    }
    bool namaSudahAda = false;
    for (int i = 0; i < jumlahBarang; i++) {
        if (daftarBarang[i].nama == nama) {
            namaSudahAda = true;
            break;
        }
    }
    if (namaSudahAda) {
        system("cls");
        cout << "--------------------------" << endl;
        cout << " Nama barang sudah ada!" << endl;
        cout << "--------------------------" << endl;
        delayNotif();
        return;
    }
    cout << " Masukkan jenis barang: ";
    while (jenis.empty()) {
        getline(cin, jenis);
        if (jenis.empty()) {
            system("cls");
            cout << "------------------------------------" << endl;
            cout << "  Jenis barang tidak boleh kosong!" << endl;
            cout << "------------------------------------" << endl;
            delayNotif();
            cout << " Masukkan jenis barang: ";
        }
    }
    cout << " Masukkan jumlah barang: ";
    while (!(cin >> jumlah) || jumlah <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        system("cls");
        cout << "-------------------------------" << endl;
        cout << " Jumlah barang tidak valid!" << endl;
        cout << "-------------------------------" << endl;
        delayNotif();
        cout << " Masukkan jumlah barang: ";
    }
    cout << " Masukkan tanggal (DD/MM/YYYY): ";
    cin.ignore();
    while (tanggal.empty()) {
        getline(cin, tanggal);
        if (tanggal.empty()) {
            system("cls");
            cout << "-------------------------------" << endl;
            cout << " Tanggal tidak boleh kosong!" << endl;
            cout << "-------------------------------" << endl;
            delayNotif();
            cout << " Masukkan tanggal (DD/MM/YYYY): ";
        }
    }
    daftarBarang[jumlahBarang].uuid = generateUUID();
    daftarBarang[jumlahBarang].nama = nama;
    daftarBarang[jumlahBarang].jenis = jenis;
    daftarBarang[jumlahBarang].jumlah = jumlah;
    daftarBarang[jumlahBarang].tanggal = tanggal;
    jumlahBarang++;
    system("cls");
    saveBarang();
    cout << "--------------------------------" << endl;
    cout << "  Barang berhasil ditambahkan!" << endl;
    cout << "--------------------------------" << endl;
    delayNotif();
}

// Deklarasi fungsi untuk mengubah barang
void ubahBarang() {
    int pilihan;
    do {
        string uuid;
        int jumlah;

        system("cls");
        showMenuUbahBarang();

        while (!(cin >> pilihan) || pilihan < 0 || pilihan > 4) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("cls");
            cout << "-----------------------------------" << endl;
            cout << "  Pilihan tidak valid! Coba lagi." << endl;
            cout << "-----------------------------------" << endl;
            delayNotif();
            showMenuUbahBarang();
        }

        if (pilihan == 0) {
            system("cls");
            cout << "---------------------------------" << endl;
            cout << "  Keluar dari menu ubah barang." << endl;
            cout << "---------------------------------" << endl;
            delayNotif();
            break;
        }

        system("cls");
        if (jumlahBarang == 0) {
            cout << "-----------------------------------" << endl;
            cout << "  Tidak ada barang yang tersedia!" << endl;
            cout << "-----------------------------------" << endl;
            delayNotif();
            continue;
        }

        printTable(daftarBarang, jumlahBarang);
        cout << "Masukkan UUID barang yang ingin diubah: ";
        cin.ignore();
        getline(cin, uuid);
        bool foundBarang = false;
        for (int i = 0; i < jumlahBarang; i++) {
            if (daftarBarang[i].uuid == uuid) {
                foundBarang = true;
                switch (pilihan) {
                    case 1:
                        cout << "Masukkan nama barang baru: ";
                        getline(cin, daftarBarang[i].nama);
                        saveBarang();
                        system("cls");
                        cout << "--------------------------------" << endl;
                        cout << "  Nama barang berhasil diubah!" << endl;
                        cout << "--------------------------------" << endl;
                        delayNotif();
                        break;
                    case 2:
                        cout << "Masukkan jenis barang baru: ";
                        getline(cin, daftarBarang[i].jenis);
                        saveBarang();
                        system("cls");
                        cout << "---------------------------------" << endl;
                        cout << "  Jenis barang berhasil diubah!" << endl;
                        cout << "---------------------------------" << endl;
                        delayNotif();
                        break;
                    case 3:
                        cout << "Masukkan jumlah barang baru: ";
                        while (!(cin >> jumlah) || jumlah < 0) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            system("cls");
                            cout << "------------------------------" << endl;
                            cout << "  Jumlah barang tidak valid!" << endl;
                            cout << "------------------------------" << endl;
                            delayNotif();
                            printTable(daftarBarang, jumlahBarang);
                            cout << "Masukkan jumlah barang baru: ";
                        }
                        daftarBarang[i].jumlah = jumlah;
                        saveBarang();
                        system("cls");
                        cout << "----------------------------------" << endl;
                        cout << "  Jumlah barang berhasil diubah!" << endl;
                        cout << "----------------------------------" << endl;
                        delayNotif();
                        break;
                    case 4:
                        cout << "Masukkan tanggal barang baru (DD/MM/YYYY): ";
                        cin.ignore();
                        getline(cin, daftarBarang[i].tanggal);
                        saveBarang();
                        system("cls");
                        cout << "-----------------------------------" << endl;
                        cout << "  Tanggal barang berhasil diubah!" << endl;
                        cout << "-----------------------------------" << endl;
                        delayNotif();
                        break;
                }
                break;
            }
        }

        if (!foundBarang) {
            system("cls");
            cout << "------------------------------------------------" << endl;
            cout << "  Barang dengan UUID tersebut tidak ditemukan!" << endl;
            cout << "------------------------------------------------" << endl;
            delayNotif();
        }
    } while (pilihan != 0);
}

// Deklarasi fungsi untuk menghapus barang
void hapusBarang() {
    if (jumlahBarang == 0) {
        system("cls");
        return;
    }

    string uuid;
    cout << "Masukkan UUID barang yang ingin dihapus: ";
    cin >> uuid;

    bool found = false;
    for (int i = 0; i < jumlahBarang; i++) {
        if (daftarBarang[i].uuid == uuid) {
            found = true;
            for (int j = i; j < jumlahBarang - 1; j++) {
                daftarBarang[j] = daftarBarang[j + 1];
            }
            jumlahBarang--;
            saveBarang();
            system("cls");
            cout << "----------------------------" << endl;
            cout << "  Barang berhasil dihapus!" << endl;
            cout << "----------------------------" << endl;
            delayNotif();
            return;
        }
    }

    if (!found) {
        system("cls");
        cout << "------------------------------------------------" << endl;
        cout << "  Barang dengan UUID tersebut tidak ditemukan!" << endl;
        cout << "------------------------------------------------" << endl;
        delayNotif();
    }
}


// Deklarasi fungsi untuk melihat semua data peminjaman yang dilakukan user pada admin
void lihatPeminjamanAdmin() {
    system("cls");
    if (jumlahPeminjaman == 0) {
        cout << "--------------------------------------------" << endl;
        cout << "  Tidak ada data peminjaman yang tersedia!" << endl;
        cout << "--------------------------------------------" << endl;
        delayNotif();
        return;
    } else {
        printTablePeminjamanAdmin(daftarPeminjaman, jumlahPeminjaman);
        action();
    }
}

// Deklarasi fungsi untuk melihat peminjaman yang dilakukan user
void lihatPeminjamanUser(const string& username) {
    int jumlahPeminjamanUser = 0;

    Peminjaman peminjamanUser[MAX_PEMINJAMAN];
    for (int i = 0; i < jumlahPeminjaman; i++) {
        if (daftarPeminjaman[i].username == username) {
            peminjamanUser[jumlahPeminjamanUser] = daftarPeminjaman[i];
            jumlahPeminjamanUser++;
        }
    }

    if (jumlahPeminjamanUser == 0) {
        system("cls");
        cout << "---------------------------------------------" << endl;
        cout << "  Anda tidak memiliki barang yang dipinjam!" << endl;
        cout << "---------------------------------------------" << endl;
        delayNotif();
        return;
    } else {
        printTablePeminjaman(peminjamanUser, jumlahPeminjamanUser);
    }
}

// Deklarasi fungsi untuk meminjam barang
void pinjamBarang(const string& username) {
    string uuid;
    int jumlah;

    if (jumlahBarang == 0) {
        system("cls");
        return;
    }

    cout << "Masukkan UUID barang yang ingin dipinjam: ";
    cin >> uuid;
    bool found = false;
    for (int i = 0; i < jumlahBarang; i++) {
        if (daftarBarang[i].uuid == uuid) {
            found = true;
            cout << "Masukkan jumlah barang yang ingin dipinjam: ";
            string input;
            while (true) {
                cin >> input;
                if (cin.fail() || input.find_first_not_of("0123456789") != string::npos) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    system("cls");
                    cout << "------------------------------" << endl;
                    cout << " Jumlah barang tidak valid!" << endl;
                    cout << "------------------------------" << endl;
                    delayNotif();
                    printTable(daftarBarang, jumlahBarang);
                    cout << "Masukkan jumlah barang yang ingin dipinjam: ";
                } else {
                    jumlah = stoi(input);
                    if (jumlah <= 0) {
                        system("cls");
                        cout << "------------------------------" << endl;
                        cout << " Jumlah barang tidak valid!" << endl;
                        cout << "------------------------------" << endl;
                        delayNotif();
                        printTable(daftarBarang, jumlahBarang);
                        cout << "Masukkan jumlah barang yang ingin dipinjam: ";
                    } else {
                        break;
                    }
                }
            }
            if (jumlah > daftarBarang[i].jumlah) {
                system("cls");
                cout << "------------------------------------------------------------------" << endl;
                cout << " Jumlah barang yang ingin dipinjam melebihi stok yang tersedia!" << endl;
                cout << "------------------------------------------------------------------" << endl;
                delayNotif();
                return;
            }
            daftarBarang[i].jumlah -= jumlah;
            saveBarang();
            bool alreadyBorrowed = false;
            for (int j = 0; j < jumlahPeminjaman; j++) {
                if (daftarPeminjaman[j].uuid == uuid && daftarPeminjaman[j].username == username) {
                    daftarPeminjaman[j].jumlah += jumlah;
                    alreadyBorrowed = true;
                    break;
                }
            }

            if (!alreadyBorrowed) {
                Peminjaman peminjamanBaru;
                peminjamanBaru.username = username;
                peminjamanBaru.uuid = uuid;
                peminjamanBaru.nama = daftarBarang[i].nama;
                peminjamanBaru.jenis = daftarBarang[i].jenis;
                peminjamanBaru.jumlah = jumlah;
                peminjamanBaru.tanggal = daftarBarang[i].tanggal; // Tambahkan informasi tanggal barang

                time_t now = time(0);
                struct tm tstruct;
                char buf[80];
                tstruct = *localtime(&now);
                strftime(buf, sizeof(buf), "%H:%M:%S %d/%m/%Y", &tstruct);
                peminjamanBaru.tanggal_pinjam = buf;
                daftarPeminjaman[jumlahPeminjaman] = peminjamanBaru;
                jumlahPeminjaman++;
            }
            savePeminjaman();
            system("cls");
            cout << "-----------------------------" << endl;
            cout << " Barang berhasil dipinjam!" << endl;
            cout << "-----------------------------" << endl;
            delayNotif();
            return;
        }
    }
    if (!found) {
        system("cls");
        cout << "--------------------------------" << endl;
        cout << " UUID barang tidak ditemukan!" << endl;
        cout << "--------------------------------" << endl;
        delayNotif();
    }
}

// Deklarasi fungsi untuk mengembalikan barang
void kembalikanBarang(const string& username) {
    string uuid;
    int jumlah;
    bool hasPeminjaman = false;

    for (int i = 0; i < jumlahPeminjaman; i++) {
        if (daftarPeminjaman[i].username == username) {
            hasPeminjaman = true;
            break;
        }
    }

    if (!hasPeminjaman) {
        system("cls");
        return;
    }
    
    cout << "Masukkan UUID barang yang ingin dikembalikan: ";
    cin >> uuid;
    bool foundPeminjaman = false;
    for (int i = 0; i < jumlahPeminjaman; i++) {
        if (daftarPeminjaman[i].uuid == uuid && daftarPeminjaman[i].username == username) {
            foundPeminjaman = true;
            break;
        }
    }
    if (!foundPeminjaman) {
        system("cls");
        cout << "----------------------------------------------------" << endl;
        cout << "  Peminjaman dengan UUID tersebut tidak ditemukan!" << endl;
        cout << "----------------------------------------------------" << endl;
        delayNotif();
        return;
    }
    cout << "Masukkan jumlah barang yang ingin dikembalikan: ";
    string input;
    while (true) {
        cin >> input;
        if (cin.fail() || input.find_first_not_of("0123456789") != string::npos) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("cls");
            cout << "-------------------------------------------------" << endl;
            cout << "  Input tidak valid! Masukkan angka yang valid." << endl;
            cout << "-------------------------------------------------" << endl;
            delayNotif();
            lihatPeminjamanUser(username);
            cout << "Masukkan jumlah barang yang ingin dikembalikan: ";
        } else {
            jumlah = stoi(input);
            if (jumlah <= 0) {
                system("cls");
                cout << "------------------------------------------------" << endl;
                cout << "  Jumlah barang yang dikembalikan tidak valid!" << endl;
                cout << "------------------------------------------------" << endl;
                delayNotif();
                lihatPeminjamanUser(username);
                cout << "Masukkan jumlah barang yang ingin dikembalikan: ";
            } else {
                break;
            }
        }
    }
    for (int i = 0; i < jumlahPeminjaman; i++) {
        if (daftarPeminjaman[i].uuid == uuid && daftarPeminjaman[i].username == username) {
            if (daftarPeminjaman[i].jumlah < jumlah) {
                system("cls");
                cout << "------------------------------------------------------------------------" << endl;
                cout << "  Jumlah barang yang ingin dikembalikan melebihi jumlah yang dipinjam!" << endl;
                cout << "------------------------------------------------------------------------" << endl;
                delayNotif();
                return;
            }
            bool foundBarang = false;
            for (int j = 0; j < jumlahBarang; j++) {
                if (daftarBarang[j].uuid == uuid) {
                    daftarBarang[j].jumlah += jumlah;
                    foundBarang = true;
                    break;
                }
            }
            if (!foundBarang) {
                Barang barangBaru;
                barangBaru.uuid = daftarPeminjaman[i].uuid;
                barangBaru.nama = daftarPeminjaman[i].nama;
                barangBaru.jenis = daftarPeminjaman[i].jenis;
                barangBaru.tanggal = daftarPeminjaman[i].tanggal; // Gunakan informasi tanggal dari objek Peminjaman
                barangBaru.jumlah = jumlah;
                daftarBarang[jumlahBarang] = barangBaru;
                jumlahBarang++;
            }
            if (daftarPeminjaman[i].jumlah == jumlah) {
                for (int j = i; j < jumlahPeminjaman - 1; j++) {
                    daftarPeminjaman[j] = daftarPeminjaman[j + 1];
                }
                jumlahPeminjaman--;
            } else {
                daftarPeminjaman[i].jumlah -= jumlah;
            }
            break;
        }
    }
    saveBarang();
    savePeminjaman();
    system("cls");
    cout << "---------------------------------" << endl;
    cout << "  Barang berhasil dikembalikan!" << endl;
    cout << "---------------------------------" << endl;
    delayNotif();
}

// Deklarasi fungsi untuk mencari barang secara rekursif
void searchRecursive(const string& keyword, int index) {
    if (index >= jumlahBarang) {
        return;
    }

    string namaBrg = daftarBarang[index].nama;
    string namaLower = "";
    string jenisBrg = daftarBarang[index].jenis;
    string jenisLower = "";
    string keywordLower = keyword;

    transform(keywordLower.begin(), keywordLower.end(), keywordLower.begin(), ::tolower);

    transform(namaBrg.begin(), namaBrg.end(), back_inserter(namaLower), ::tolower);
    transform(jenisBrg.begin(), jenisBrg.end(), back_inserter(jenisLower), ::tolower);

    if (namaLower.find(keywordLower) != string::npos || jenisLower.find(keywordLower) != string::npos) {
        hasilPencarian[jumlahHasilPencarian] = daftarBarang[index];
        jumlahHasilPencarian++;
    }

    searchRecursive(keyword, index + 1);
}

// Deklarasi fungsi untuk mencari barang
void search() {
    string keyword;

    cout << "+================================================+" << endl;
    cout << "|                       SEARCH                   |" << endl;
    cout << "+================================================+" << endl;
    cout << " Masukkan keyword: ";
    cin.ignore();
    getline(cin, keyword);
    jumlahHasilPencarian = 0;
    searchRecursive(keyword, 0);

    if (jumlahHasilPencarian == 0) {
        system("cls");
        cout << "---------------------------" << endl;
        cout << "  Barang tidak ditemukan!" << endl;
        cout << "---------------------------" << endl;
        delayNotif();
    } else {
        system("cls");
        printTable(hasilPencarian, jumlahHasilPencarian);
        action();
    }
}

// Deklarasi fungsi untuk menu lihat barang user
void lihatAndSearch() {
    int pilihan;
    do {
        showMenuLihatBarangUser();
        while (!(cin >> pilihan)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("cls");
            cout << "------------------------" << endl;
            cout << "  Pilihan tidak valid!" << endl;
            cout << "------------------------" << endl;
            delayNotif();
            showMenuLihatBarangUser();
        }
        switch (pilihan) {
            case 1:
                system("cls");
                lihatBarang();
                if (jumlahBarang != 0) {
                    action();
                }
                break;
            case 2:
                system("cls");
                search();
                break;
            case 0:
                system("cls");
                cout << "--------------------" << endl;
                cout << "  Berhasil keluar!" << endl;
                cout << "--------------------" << endl;
                delayNotif();
                break;
            default:
                system("cls");
                cout << "------------------------" << endl;
                cout << "  Pilihan tidak valid!" << endl;
                cout << "------------------------" << endl;
                delayNotif();
                break;
        }
    } while (pilihan != 0);
}

// Deklarasi fungsi untuk menampilkan menu admin
void menuAdmin() {
    int pilihan;
    do {
        system("cls");
        showMenuAdmin();

        while (!(cin >> pilihan) || pilihan < 0 || pilihan > 6) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("cls");
            cout << "-----------------------------------" << endl;
            cout << "  Pilihan tidak valid! Coba lagi." << endl;
            cout << "-----------------------------------" << endl;
            delayNotif();
            showMenuAdmin();
        }

        switch (pilihan) {
            case 1:
                tambahBarang();
                break;
            case 2:
                system("cls");
                lihatAndSearch();
                break;
            case 3:
                ubahBarang();
                break;
            case 4:
                system("cls");
                lihatBarang();
                hapusBarang();
                break;
            case 5:
                system("cls");
                lihatAkunUser();
                action();
                break;
            case 6:
                lihatPeminjamanAdmin();
                break;
            case 0:
                system("cls");
                cout << "--------------------" << endl;
                cout << "  Logout berhasil!" << endl;
                cout << "--------------------" << endl;
                delayNotif();
        }
    } while (pilihan != 0);
}


// Deklarasi fungsi untuk menu user
void menuUser(const string& username) {
    int pilihan;
    int jumlahPeminjamanUser = 0;

    do {
        system("cls");
        showMenuUser();

        while (!(cin >> pilihan) || pilihan < 0 || pilihan > 4) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("cls");
            cout << "-----------------------------------" << endl;
            cout << "  Pilihan tidak valid! Coba lagi." << endl;
            cout << "-----------------------------------" << endl;
            delayNotif();
            showMenuUser();
        }

        switch (pilihan) {
            case 1:
                system("cls");
                lihatAndSearch();
                break;
            case 2:
                system("cls");
                lihatPeminjamanUser(username);
                for (int i = 0; i < jumlahPeminjaman; i++) {
                    if (daftarPeminjaman[i].username == username) {
                        jumlahPeminjamanUser++;
                    }
                }
                if (jumlahPeminjamanUser != 0) {
                    action();
                }
                break;
            case 3:
                system("cls");
                lihatBarang();
                pinjamBarang(username);
                break;
            case 4:
                system("cls");
                lihatPeminjamanUser(username);
                kembalikanBarang(username);
                break;
            case 0:
                system("cls");
                cout << "--------------------" << endl;
                cout << "  Logout berhasil!" << endl;
                cout << "--------------------" << endl;
                delayNotif();
                break;
            default:
                system("cls");
                cout << "------------------------" << endl;
                cout << "  Pilihan tidak valid!" << endl;
                cout << "------------------------" << endl;
                delayNotif();
                break;
        }
    } while (pilihan != 0);
}
// Deklarasi fungsi untuk menu registrasi akun baru
void menuRegister() {
    string username, password;
    cout << "+================================================+" << endl;
    cout << "|                     REGISTRASI                 |" << endl;
    cout << "+================================================+" << endl;
    cout << " Masukkan username baru: ";
    cin >> username;

    bool isExistingUser = false;
    for (int i = 0; i < jumlahUser; i++) {
        if (daftarUser[i].username == username) {
            isExistingUser = true;
            break;
        }
    }

    if (isExistingUser) {
        system("cls");
        cout << "---------------------------------------------------------" << endl;
        cout << "  Username sudah digunakan. Silakan coba username lain." << endl;
        cout << "---------------------------------------------------------" << endl;
        delayNotif();
    } else {
        cout << " Masukkan password: ";
        cin >> password;

        daftarUser[jumlahUser].username = username;
        daftarUser[jumlahUser].password = password;
        jumlahUser++;

        system("cls");
        saveUser();
        cout << "-------------------------" << endl;
        cout << "  Akun berhasil dibuat!" << endl;
        cout << "-------------------------" << endl;
        delayNotif();
    }
}

// Deklarasi fungsi untuk menu login
void menuLogin() {
    string username, password;
    int percobaan = 0;

    while (percobaan < 3) {
    cout << "+================================================+" << endl;
    cout << "|                      LOGIN                     |" << endl;
    cout << "+================================================+" << endl;
    cout << " Masukkan username: ";
    cin >> username;
    cout << " Masukkan password: ";
    cin >> password;

    bool userDitemukan = false;
    for (int i = 0; i < jumlahUser; i++) {
        if (daftarUser[i].username == username && daftarUser[i].password == password) {
            userDitemukan = true;
            break;
        }
    }

    if (userDitemukan) {
        system("cls");
        cout << "-------------------" << endl;
        cout << "  Login berhasil!" << endl;
        cout << "-------------------" << endl;
        delayNotif();

        if (username == "admin" && password == "admin") {
            menuAdmin();
        } else {
            menuUser(username);
        }
        return;
    } else {
        system("cls");
        percobaan++;
        cout << "---------------------------------" << endl;
        cout << "  Username atau password salah!" << endl;
        cout << "---------------------------------" << endl;
        delayNotif();
    }
}

    system("cls");
    cout << "-----------------------------------------------------------------------------------------" << endl;
    cout << "  Anda telah salah memasukkan username atau password sebanyak 3 kali. Program berhenti." << endl;
    cout << "-----------------------------------------------------------------------------------------" << endl;
    delayNotif();
    exit(0);
}

// Deklarasi fungsi untuk menjalakan program
int main() {
    srand(time(0));
    loadBarang();
    loadUser();
    loadPeminjaman();

    int pilihan;
    do {
        showMenuLogin();

        while (!(cin >> pilihan)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("cls");
            cout << "----------------------------------------------" << endl;
            cout << "  Input tidak valid, silakan masukkan angka." << endl;
            cout << "----------------------------------------------" << endl;
            delayNotif();
            showMenuLogin();
        }

        switch (pilihan) {
            case 1:
                system("cls");
                menuLogin();
                break;
            case 2:
                system("cls");
                menuRegister();
                break;
            case 0:
                system("cls");
                cout << "------------------------" << endl;
                cout << "  Keluar dari program!" << endl;
                cout << "------------------------" << endl;
                delayNotif();
                break;
            default:
                system("cls");
                cout << "------------------------" << endl;
                cout << "  Pilihan tidak valid!" << endl;
                cout << "------------------------" << endl;
                delayNotif();
                break;
        }
    } while (pilihan != 0);

    return 0;
}