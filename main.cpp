#include "flight.h"

int main() {
    flightNetwork N;
    initNetwork(N);
    int pilihan;
    string startID, destID;
    int flightTime;

    do {
        cout << "==============================================";
        cout << "\n--- Selamat Datang Di Aplikasi Penerbangan ---" << endl;
        cout << "==============================================" << endl;
        cout << "1. Tambah Bandara" << endl;
        cout << "2. Tambah Rute Penerbangan" << endl;
        cout << "3. Tampilkan Jaringan Penerbangan" << endl;
        cout << "4. Cari Rute dengan DFS (Rekursif)" << endl;
        cout << "5. Cari Rute dengan BFS (Iteratif)" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilih: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
        case 1:
            cout << "Masukkan Nama Bandara: ";
            getline(cin, startID);
            addAirport(N, startID);
            break;
        case 2:
            cout << "Masukkan Bandara Asal: ";
            getline(cin, startID);
            cout << "Masukkan Bandara Tujuan: ";
            getline(cin, destID);
            cout << "Masukkan Waktu Penerbangan (menit): ";
            cin >> flightTime;
            cin.ignore();
            addRoute(N, startID, destID, flightTime);
            break;
        case 3:
            cout << "\n========= Rute Jalur Penerbangan =========" << endl;
            printNetwork(N);
            break;
        case 4: {
            cout << "Masukkan Bandara Asal: ";
            getline(cin, startID);
            cout << "Masukkan Bandara Tujuan: ";
            getline(cin, destID);

            string visited[100], path[100];
            int visitCount = 0, pathCount = 0;

            adrAirport start = firstAirport(N);
            while (start != NULL && airportID(start) != startID) {
                start = nextAirport(start);
            }

            if (start == NULL) {
                cout << "Bandara asal tidak ditemukan!" << endl;
                break;
            }

            if (dfsRecursive(N, start, destID, visited, visitCount, path, pathCount)) {
                cout << "Rute ditemukan dengan DFS: ";
                for (int i = 0; i < pathCount; ++i) {
                    cout << path[i] << " ";
                }
                cout << endl;
            } else {
                cout << "Rute tidak ditemukan dengan DFS!" << endl;
            }
            break;
        }
        case 5: {
            cout << "Masukkan Bandara Asal: ";
            getline(cin, startID);
            cout << "Masukkan Bandara Tujuan: ";
            getline(cin, destID);

            string visited[100], path[100];
            int visitCount = 0, pathCount = 0;

            if (bfsIterative(N, startID, destID, visited, visitCount, path, pathCount)) {
                cout << "Rute ditemukan dengan BFS: ";
                for (int i = 0; i < pathCount; ++i) {
                    cout << path[i] << " ";
                }
                cout << endl;
            } else {
                cout << "Rute tidak ditemukan dengan BFS!" << endl;
            }
            break;
        }
        case 0:
            cout << "Terima kasih telah menggunakan aplikasi kami dan sampai jumpa!" << endl;
            break;
        default:
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    } while (pilihan != 0);

    return 0;
}
