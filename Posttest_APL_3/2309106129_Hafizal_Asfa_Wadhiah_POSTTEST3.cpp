#include <iostream>
using namespace std;

// Deklarasi fungsi
void createPasal();
void readPasal();
void updatePasal();
void deletePasal();
void mainMenu();

// Username: Aspa
// Password: 129S

// Menyimpan pasal
struct Pasal {
    int nomorPasal;
    string isiPasal;
};

// Batas menyimpan pasal
const int MAX_PASAL = 100;
Pasal daftarPasal[MAX_PASAL];
int jumlahPasal = 0;

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

        if (username == "Aspa" && password == "129") {
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
}

// Fungsi main menu
void mainMenu() {
    int pilihan;

    cout << "===== Main Menu =====\n";
    cout << "1. Create\n";
    cout << "2. Read\n";
    cout << "3. Update\n";
    cout << "4. Delete\n";
    cout << "0. Quit\n";

    cout << "Masukan pilihan: ";
    cin >> pilihan;

    switch(pilihan){
    case 1:
        createPasal();
        break;
    case 2:
        readPasal();
        break;
    case 3:
       updatePasal();
       break;
    case 4:
       deletePasal();
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
void createPasal() {
    if (jumlahPasal < MAX_PASAL) {
        int nomorPasal;
        cout << "Nomor Pasal: ";
        cin >> nomorPasal;
        
        // Cek apakah nomor pasal sudah ada
        bool nomorSudahAda = false;
        for (int i = 0; i < jumlahPasal; i++) {
            if (daftarPasal[i].nomorPasal == nomorPasal) {
                nomorSudahAda = true;
                break;
            }
        }

        if (!nomorSudahAda) {
            daftarPasal[jumlahPasal].nomorPasal = nomorPasal;
            cout << "Isi Pasal: ";
            cin.ignore();
            getline(cin, daftarPasal[jumlahPasal].isiPasal);
            jumlahPasal++;
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
void readPasal() {
    system("cls");
    if (jumlahPasal > 0) {
        // Bubble sort untuk mengurutkan nomor pasal
        for (int i = 0; i < jumlahPasal - 1; i++) {
            for (int j = 0; j < jumlahPasal - i - 1; j++) {
                if (daftarPasal[j].nomorPasal > daftarPasal[j + 1].nomorPasal) {
                    Pasal temp = daftarPasal[j];
                    daftarPasal[j] = daftarPasal[j + 1];
                    daftarPasal[j + 1] = temp;
                }
            }
        }
        
        // Menampilkan data yang sudah terurut
        cout << "===== Daftar Pasal =====\n";
        for (int i = 0; i < jumlahPasal; i++) {
            cout << daftarPasal[i].nomorPasal << ". " << daftarPasal[i].isiPasal << endl;
        }
    } else {
        cout << "===== Tidak ada pasal yang tersedia =====" << endl;
    }
}


// Memperbarui pasal
void updatePasal() {
    if (jumlahPasal > 0) {
        int nomorPasal;
        cout << "Nomor Pasal yang akan diperbarui: ";
        cin >> nomorPasal;
        bool ditemukan = false;
        for (int i = 0; i < jumlahPasal; i++) {
            if (daftarPasal[i].nomorPasal == nomorPasal) {
                cout << "Isi Pasal baru: ";
                cin.ignore();
                getline(cin, daftarPasal[i].isiPasal);
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
void deletePasal() {
    if (jumlahPasal > 0) {
        int nomorPasal;
        cout << "Nomor Pasal yang akan dihapus: ";
        cin >> nomorPasal;
        bool ditemukan = false;
        for (int i = 0; i < jumlahPasal; i++) {
            if (daftarPasal[i].nomorPasal == nomorPasal) {
                for (int j = i; j < jumlahPasal - 1; j++) {
                    daftarPasal[j] = daftarPasal[j + 1];
                }
                jumlahPasal--;
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
