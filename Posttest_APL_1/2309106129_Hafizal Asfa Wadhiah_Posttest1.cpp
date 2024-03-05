#include <iostream>
#include<iomanip>
using namespace std;


void showMenu();
void celciusConvert();
void reamurConvert();
void farenheitConvert();
void kelvinConvert();

// Username : Aspa
// Password : 129

int main() {

    // Menu Login
    string username, password;
    bool login = false;
    int salah = 0;

    while (!login && salah < 3)
    {
        cout << "Masukan Username : ";
        cin >> username;
        cout << "Masukan Password : ";
        cin >> password;

        if (username == "Aspa" && password == "129") {
            system("cls");
            login = true;
        } 
        else {
            salah++;
            cout << "===== Username atau password salah =====\n";
        }
         
    }

    if (!login) {
        system("cls");
        cout << "===== Akun telah diblokir =====";
        return 0;
    }
    

    // Main Menu
    char pilihan;
    bool berhenti = false;

    while (!berhenti) {
        showMenu();
        cout << "Masukan pilihan : ";
        cin >> pilihan;

        switch (pilihan)
        {
        case '1':
            system("cls");
            celciusConvert();
            break;
        case '2':
            system("cls");
            reamurConvert();
            break;
        case '3':
            system("cls");
            farenheitConvert();
            break;
        case '4':
            system("cls");
            kelvinConvert();
            break;
        case '0':
            berhenti = true;
            system("cls");
            cout << "===== Berhasil keluar =====";
            break;
        
        default:
            system("cls");
            cout << "===== Pilihan tidak Valid =====\n";
            cout << endl;
        }
    }

    return 0;
}


// Show Menu
 void showMenu() {
        cout << "===== Menu =====\n";
        cout << "1. Celcius\n";
        cout << "2. Reamur\n";
        cout << "3. Farenheit\n";
        cout << "4. Kelvin\n";
        cout << "0. Quit\n";
    }

// Celcius
void celciusConvert() {
    double celcius;
    cout << "Masukkan suhu dalam Celcius : ";
    cin >> celcius;
    cout << "Reamur : " << setprecision(2) << fixed << celcius * 0.8 << endl;
    cout << "Farenheit : " << setprecision(2) << fixed << (celcius * 9 / 5) + 32 << endl;
    cout << "Kelvin : " << setprecision(2) << fixed << celcius + 273.15 << endl;
    cout << endl;
}

// Reamur
void reamurConvert() {
    double reamur;
    cout << "Masukkan suhu dalam Reamur : ";
    cin >> reamur;
    cout << "Celcius : " << setprecision(2) << fixed << reamur * 1.25 << endl;
    cout << "Farenheit : " << setprecision(2) << fixed << (reamur * 2.25) + 32 << endl;
    cout << "Kelvin : " << setprecision(2) << fixed << (reamur * 5 / 4) + 273.15 << endl;
    cout << endl;
}

// Farenheit
void farenheitConvert() {
    double farenheit;
    cout << "Masukkan suhu dalam Farenheit : ";
    cin >> farenheit;
    cout << "Celcius : " << setprecision(2) << fixed << (farenheit - 32) * 5 / 9 << endl;
    cout << "Reamur : " << setprecision(2) << fixed << (farenheit - 32) * 4 / 9 << endl;
    cout << "Kelvin : " << setprecision(2) << fixed << (farenheit - 32) * 5 / 9 + 273.15 << endl;
    cout << endl;
}

// Kelvin
void kelvinConvert() {
    double kelvin;
    cout << "Masukkan suhu dalam Kelvin: ";
    cin >> kelvin;
    cout << "Celcius: " << setprecision(2) << fixed << kelvin - 273.15 << endl;
    cout << "Reamur: " << setprecision(2) << fixed << (kelvin - 273.15) * 0.8 << endl;
    cout << "Farenheit: " << setprecision(2) << fixed << (kelvin - 273.15) * 9 / 5 + 32 << endl;
    cout << endl;
}