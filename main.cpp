#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct nilai {
    float Mtk;
    float BIn;
    float Big;
    float IPA;
    float akhir;
};

struct siswa {
    string nama;
    string NISN;
    string jurusan;
    nilai Nilai;
};

float hitungNilaiAkhir(nilai n) {
    return (n.Mtk * 0.4) + (n.IPA * 0.3) + (n.BIn * 0.2) + (n.Big * 0.1);
}


void tambahDataSiswa() {
    int jumlahSiswa;
    cout << "Berapa banyak siswa yang ingin anda tambahkan? ";
    cin >> jumlahSiswa;
    cin.ignore();

    ofstream fileOutput("Datasiswa.txt", ios::app);

    for (int i = 0; i < jumlahSiswa; i++) {
        siswa data;
        cout << "\nMasukkan Data Siswa ke-" << i + 1 << endl;
        cout << "Nama : ";
        getline(cin, data.nama);
        cout << "NISN : ";
        getline(cin, data.NISN);
        cout << "Jurusan : ";
        getline(cin, data.jurusan);
        cout << "Nilai dari " << data.nama << endl;
        cout << "Nilai Matematika : ";
        cin >> data.Nilai.Mtk;
        cout << "Nilai Bahasa Indonesia : ";
        cin >> data.Nilai.BIn;
        cout << "Nilai Bahasa Inggris : ";
        cin >> data.Nilai.Big;
        cout << "Nilai IPA : ";
        cin >> data.Nilai.IPA;
        data.Nilai.akhir = hitungNilaiAkhir(data.Nilai);
        cin.ignore();

        fileOutput << "Nama  : " << data.nama << " - "
                   << "NISN : " << data.NISN << " - "
                   << "Jurusan : " << data.jurusan << endl;
        fileOutput << "Nilai -> "
                   << "Matematika : " << data.Nilai.Mtk << ", "
                   << "Bahasa Indonesia : " << data.Nilai.BIn << ", "
                   << "Bahasa Inggris : " << data.Nilai.Big << ", "
                   << "IPA : " << data.Nilai.IPA << ", "
                   << "Nilai Akhir : " << data.Nilai.akhir << endl
                   << endl;
    }
    fileOutput.close();
    cout << "Data Tersimpan!" << endl;
}


void tampilDataSiswa() {
    ifstream fileInput("Datasiswa.txt");
    string baris;

    if (!fileInput.is_open()) {
        cout << "File tidak ditemukan!" << endl;
        return;
    }

    while (getline(fileInput, baris)) {
        cout << baris << endl;
    }

    fileInput.close();
}


void cariSiswa() {
    ifstream fileInput("Datasiswa.txt");
    string baris, keyword;

    if (!fileInput.is_open()) {
        cout << "File tidak ditemukan!" << endl;
        return;
    }

    cout << "Masukkan NISN yang ingin dicari: ";
    cin.ignore();
    getline(cin, keyword);

    bool ditemukan = false;
    while (getline(fileInput, baris)) {
        if (baris.find(keyword) != string::npos) {
            cout << baris << endl;
            getline(fileInput, baris);
            cout << baris << endl << endl;
            ditemukan = true;
        }
    }

    if (!ditemukan) {
        cout << "Data dengan NISN " << keyword << " tidak ditemukan." << endl;
    }

    fileInput.close();
}


void ranking() {
    ifstream fileInput("Datasiswa.txt");
    if (!fileInput.is_open()) {
        cout << "File tidak ditemukan!" << endl;
        return;
    }
    int jumlah;
    cout << "Masukkan jumlah siswa yang ingin diranking: ";
    cin >> jumlah;
    siswa data[jumlah];
    cin.ignore();

    for (int i = 0; i < jumlah; i++) {
        cout << "\nNama: ";
        getline(cin, data[i].nama);
        cout << "NISN: ";
        getline(cin, data[i].NISN);
        cout << "Jurusan: ";
        getline(cin, data[i].jurusan);
        cout << "Nilai Matematika: ";
        cin >> data[i].Nilai.Mtk;
        cout << "Nilai Bahasa Indonesia: ";
        cin >> data[i].Nilai.BIn;
        cout << "Nilai Bahasa Inggris: ";
        cin >> data[i].Nilai.Big;
        cout << "Nilai IPA: ";
        cin >> data[i].Nilai.IPA;
        data[i].Nilai.akhir = hitungNilaiAkhir(data[i].Nilai);
        cin.ignore();
    }

    
    for (int i = 0; i < jumlah - 1; i++) {
        for (int j = 0; j < jumlah - i - 1; j++) {
            if (data[j].Nilai.akhir < data[j + 1].Nilai.akhir) {
                siswa temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
    }

    cout << "\n=== PERINGKAT SISWA ===" << endl;
    for (int i = 0; i < jumlah; i++) {
        cout << i + 1 << ". " << data[i].nama
             << " (" << data[i].Nilai.akhir << ")" <<"jurusan : "<< data[i].jurusan<<endl;
    }
}


int main() {
    int menu;

    do {
        cout << "\n===== MENU DATA SISWA =====" << endl;
        cout << "1. Tambah Data Siswa" << endl;
        cout << "2. Tampil Data Siswa" << endl;
        cout << "3. Cari Data Siswa (berdasarkan NISN)" << endl;
        cout << "4. Ranking Siswa" << endl;
        cout << "5. Keluar" << endl;
        cout << "Pilih Menu : ";
        cin >> menu;

        switch (menu) {
        case 1:
            tambahDataSiswa();
            break;
        case 2:
            tampilDataSiswa();
            break;
        case 3:
            cariSiswa();
            break;
        case 4:
            ranking();
            break;
        case 5:
            cout << "Keluar dari program..." << endl;
            break;
        default:
            cout << "Menu tidak valid!" << endl;
        }
    } while (menu != 5);

    return 0;
}
