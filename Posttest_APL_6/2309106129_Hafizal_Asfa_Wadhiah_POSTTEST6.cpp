#include <iostream>
using namespace std;

// Deklarasi struct Pasal
struct Pasal {
    int nomorPasal;
    string isiPasal;
};

// Batas menyimpan pasal
const int MAX_PASAL = 100;
Pasal daftarPasal[MAX_PASAL];
int jumlahPasal = 0;

// Deklarasi struct Pengguna
struct Pengguna {
    string username;
    string password;
};

// Pengguna
Pengguna pengguna = {"Aspa", "129"};

// Fungsi sorting huruf secara ascending
void sortAscendingAlpha(Pasal *pasalArr, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (pasalArr[j].isiPasal > pasalArr[j + 1].isiPasal) {
                Pasal temp = pasalArr[j];
                pasalArr[j] = pasalArr[j + 1];
                pasalArr[j + 1] = temp;
            }
        }
    }
}

// Fungsi sorting angka secara descending
void sortDescendingNumber(Pasal *pasalArr, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (pasalArr[j].nomorPasal < pasalArr[j + 1].nomorPasal) {
                Pasal temp = pasalArr[j];
                pasalArr[j] = pasalArr[j + 1];
                pasalArr[j + 1] = temp;
            }
        }
    }
}

// Fungsi sorting menggunakan metode bubble sort
void bubbleSort(Pasal *pasalArr, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (pasalArr[j].nomorPasal > pasalArr[j + 1].nomorPasal) {
                Pasal temp = pasalArr[j];
                pasalArr[j] = pasalArr[j + 1];
                pasalArr[j + 1] = temp;
            }
        }
    }
}

// Metode pencarian pada kumpulan data yang terurut secara ascending
int binarySearchAscending(Pasal *pasalArr, int left, int right, int target) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        // Jika target ditemukan di tengah
        if (pasalArr[mid].nomorPasal == target)
            return mid;
        
        // Jika target lebih besar, cari di sebelah kanan
        if (pasalArr[mid].nomorPasal < target)
            left = mid + 1;
        
        // Jika target lebih kecil, cari di sebelah kiri
        else
            right = mid - 1;
    }
    
    // Jika tidak ditemukan
    return -1;
}

// Metode pencarian pada kumpulan data yang terurut secara descending
int binarySearchDescending(Pasal *pasalArr, int left, int right, int target) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        // Jika target ditemukan di tengah
        if (pasalArr[mid].nomorPasal == target)
            return mid;
        
        // Jika target lebih besar, cari di sebelah kiri
        if (pasalArr[mid].nomorPasal < target)
            right = mid - 1;
        
        // Jika target lebih kecil, cari di sebelah kanan
        else
            left = mid + 1;
    }
    
    // Jika tidak ditemukan
    return -1;
}

// Deklarasi fungsi
void createPasal(Pasal *pasalArr, int *count);
void readPasal(Pasal *pasalArr, int *count);
void updatePasal(Pasal *pasalArr, int *count);
void deletePasal(Pasal *pasalArr, int *count);
void mainMenu();

int main() {
    // Menu Login
    string username, password;
    bool login = false;
    int salah = 0;

    while (!login && salah < 3) {
        cout << "===== Login =====\n";
        cout << "Masukan Username : ";
        cin >> username;
        cout << "Masukan Password : ";
        cin >> password;

        if (username == pengguna.username && password == pengguna.password) {
            system("cls");
            login = true;
        } else {
            salah++;
            cout << "===== Username atau password salah =====\n";
        }
    }
    if (!login) {
        system("cls");
        cout << "===== Akun telah diblokir =====";
        return 0;
    }

    // Memanggil Main Menu
    mainMenu();
    return 0;
}

void mainMenu() {
    int pilihan;
    int targetAscending; // Deklarasi variabel di sini
    int resultAscending; // Deklarasi variabel di sini
    int targetDescending; // Deklarasi variabel di sini
    int resultDescending; // Deklarasi variabel di sini

    cout << "===== Main Menu =====\n";
    cout << "1. Create\n";
    cout << "2. Read\n";
    cout << "3. Update\n";
    cout << "4. Delete\n";
    cout << "5. Search Ascending\n";
    cout << "6. Search Descending\n";
    cout << "0. Quit\n";

    cout << "Masukan pilihan: ";
    cin >> pilihan;

    switch(pilihan){
    case 1:
        createPasal(daftarPasal, &jumlahPasal);
        break;
    case 2:
        readPasal(daftarPasal, &jumlahPasal);
        break;
    case 3:
       updatePasal(daftarPasal, &jumlahPasal);
       break;
    case 4:
       deletePasal(daftarPasal, &jumlahPasal);
       break;
    case 5:
        cout << "Masukkan nomor pasal yang ingin dicari secara ascending: ";
        cin >> targetAscending;
        resultAscending = binarySearchAscending(daftarPasal, 0, jumlahPasal - 1, targetAscending);
        if (resultAscending != -1) {
            cout << "Pasal ditemukan pada indeks: " << resultAscending << endl;
        } else {
            cout << "Pasal tidak ditemukan.\n";
        }
        break;
    case 6:
        cout << "Masukkan nomor pasal yang ingin dicari secara descending: ";
        cin >> targetDescending;
        resultDescending = binarySearchDescending(daftarPasal, 0, jumlahPasal - 1, targetDescending);
        if (resultDescending != -1) {
            cout << "Pasal ditemukan pada indeks: " << resultDescending << endl;
        } else {
            cout << "Pasal tidak ditemukan.\n";
        }
        break;
    case 0:
        system("cls");
        cout << "===== Berhasil keluar =====";
        return;
    default:
        system("cls");
        cout << "===== Pilihan tidak Valid =====\n";
        cout << endl;
    }

    // Memanggil main menu secara rekursif
    mainMenu();
}


// Menambahkan pasal baru
void createPasal(Pasal *pasalArr, int *count) {
    if (*count < MAX_PASAL) {
        int nomorPasal;
        cout << "Nomor Pasal: ";
        cin >> nomorPasal;
        
        // Cek apakah nomor pasal sudah ada
        bool nomorSudahAda = false;
        for (int i = 0; i < *count; i++) {
            if (pasalArr[i].nomorPasal == nomorPasal) {
                nomorSudahAda = true;
                break;
            }
        }

        if (!nomorSudahAda) {
            pasalArr[*count].nomorPasal = nomorPasal;
            cout << "Isi Pasal: ";
            cin.ignore();
            getline(cin, pasalArr[*count].isiPasal);
            (*count)++;
            system("cls");
            cout << "===== Pasal berhasil ditambahkan =====" << endl;
        } else {
            cout << "===== Nomor pasal sudah ada =====" << endl;
        }

    } else {
        cout << "===== Tidak bisa menambahkan pasal lagi. Batas maksimum tercapai. =====\n";
    }
}


// Menampilkan Pasal
void readPasal(Pasal *pasalArr, int *count) {
    system("cls");
    if (*count > 0) {
        // Memilih metode sorting
        int metodeSorting;
        cout << "Pilih Metode Sorting:\n";
        cout << "1. Huruf Ascending\n";
        cout << "2. Angka Descending\n";
        cout << "3. Bubble Sort\n";
        cout << "Masukkan pilihan: ";
        cin >> metodeSorting;

        // Melakukan sorting sesuai pilihan pengguna
        switch (metodeSorting) {
            case 1:
                sortAscendingAlpha(pasalArr, *count);
                break;
            case 2:
                sortDescendingNumber(pasalArr, *count);
                break;
            case 3:
                bubbleSort(pasalArr, *count);
                break;
            default:
                cout << "Pilihan tidak valid.\n";
                return;
        }

        // Menampilkan data yang sudah terurut
        cout << "===== Daftar Pasal =====\n";
        for (int i = 0; i < *count; i++) {
            cout << pasalArr[i].nomorPasal << ". " << pasalArr[i].isiPasal << endl;
        }
    } else {
        cout << "===== Tidak ada pasal yang tersedia =====" << endl;
    }
}


// Memperbarui pasal
void updatePasal(Pasal *pasalArr, int *count) {
    if (*count > 0) {
        int nomorPasal;
        cout << "Nomor Pasal yang akan diperbarui: ";
        cin >> nomorPasal;
        bool ditemukan = false;
        for (int i = 0; i < *count; i++) {
            if (pasalArr[i].nomorPasal == nomorPasal) {
                cout << "Isi Pasal baru: ";
                cin.ignore();
                getline(cin, pasalArr[i].isiPasal);
                system("cls");
                cout << "===== Pasal berhasil diperbarui =====" << endl;
                ditemukan = true;
                break;
            }
        }
        if (!ditemukan) {
            system("cls");
            cout << "===== Pasal dengan nomor tersebut tidak ditemukan =====" << endl;
        }
    } else {
        system("cls");
        cout << "===== Tidak ada pasal yang tersedia =====" << endl;
    }
}


// Menghapus pasal
void deletePasal(Pasal *pasalArr, int *count) {
    if (*count > 0) {
        int nomorPasal;
        cout << "Nomor Pasal yang akan dihapus: ";
        cin >> nomorPasal;
        bool ditemukan = false;
        for (int i = 0; i < *count; i++) {
            if (pasalArr[i].nomorPasal == nomorPasal) {
                for (int j = i; j < *count - 1; j++) {
                    pasalArr[j] = pasalArr[j + 1];
                }
                (*count)--;
                system("cls");
                cout << "===== Pasal berhasil dihapus =====" << endl;
                ditemukan = true;
                break;
            }
        }
        if (!ditemukan) {
            cout << "===== Pasal dengan nomor tersebut tidak ditemukan =====" << endl;
        }
    } else {
        cout << "===== Tidak ada pasal yang tersedia =====" << endl;
    }
}
