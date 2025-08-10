#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 100

// Struktur data buku
struct Buku {
    char kode[10];
    char nama[50];
    char jenis[30];
    float harga;
};

// Struktur data history penjualan
struct History {
    char kode[10];
    int jumlah;
    float total;
};

// Variabel global
struct Buku daftarBuku[MAX];
struct History daftarHistory[MAX];
int jumlahBuku = 0;
int jumlahHistory = 0;

// menjalankan fungsi membaca data buku dari file databuku.txt dan jika file tidak ditemukan, maka akan membuat file baru
void bacaDataBuku() {
    FILE *fp = fopen("databuku.txt", "r");
    if (!fp) {
        printf("File databuku.txt tidak ditemukan, membuat file baru...\n");
        fp = fopen("databuku.txt", "w");
        fclose(fp);
        return;
    }
    while (fscanf(fp, "%[^|]|%[^|]|%[^|]|%f\n",
                  daftarBuku[jumlahBuku].kode,
                  daftarBuku[jumlahBuku].nama,
                  daftarBuku[jumlahBuku].jenis,
                  &daftarBuku[jumlahBuku].harga) != EOF) {
        jumlahBuku++;
    }
    fclose(fp);
}

// untuk menjalankan fungsi membuat file history.txt jika belum ada
void bacaHistory() {
    FILE *fp = fopen("history.txt", "r");
    if (!fp) {
        fp = fopen("history.txt", "w"); // buat file kosong
        fclose(fp);
        return;
    }
    while (fscanf(fp, "%[^|]|%d|%f\n",
                  daftarHistory[jumlahHistory].kode,
                  &daftarHistory[jumlahHistory].jumlah,
                  &daftarHistory[jumlahHistory].total) != EOF) {
        jumlahHistory++;
    }
    fclose(fp);
}

// untuk menyimpan data buku ke file
void simpanDataBuku() {
    FILE *fp = fopen("databuku.txt", "w");
    for (int i = 0; i < jumlahBuku; i++) {
        fprintf(fp, "%s|%s|%s|%.2f\n",
                daftarBuku[i].kode,
                daftarBuku[i].nama,
                daftarBuku[i].jenis,
                daftarBuku[i].harga);
    }
    fclose(fp);
}

// melakukan penyimpanan history penjualan ke file
void simpanHistory() {
    FILE *fp = fopen("history.txt", "w");
    for (int i = 0; i < jumlahHistory; i++) {
        fprintf(fp, "%s|%d|%.2f\n",
                daftarHistory[i].kode,
                daftarHistory[i].jumlah,
                daftarHistory[i].total);
    }
    fclose(fp);
}

// untuk menginput data buku baru
void inputBuku() {
    struct Buku b;
    printf("Masukkan kode buku: ");
    scanf(" %[^\n]", b.kode);
    printf("Masukkan nama buku: ");
    scanf(" %[^\n]", b.nama);
    printf("Masukkan jenis buku: ");
    scanf(" %[^\n]", b.jenis);
    printf("Masukkan harga buku: ");
    scanf("%f", &b.harga);

    // untuk menyimpan  buku ke array (memori sementara)
    daftarBuku[jumlahBuku++] = b;

    // ditambahkan data dummy untuk history penjualan agar setiap buku yang diinput memiliki history penjualan
    srand(time(NULL));
    struct History h;
    strcpy(h.kode, b.kode);
    h.jumlah = (rand() % 5) + 1; // jumlah 1-5
    h.total = h.jumlah * b.harga;
    daftarHistory[jumlahHistory++] = h;
}

// Menampilkan daftar buku yang telah diinput
void viewBuku() {
    if (jumlahBuku == 0) {
        printf("\nTidak ada data buku.\n");
        return;
    }
    printf("\n=== Daftar Buku ===\n");
    for (int i = 0; i < jumlahBuku; i++) {
        printf("%d. %s | %s | %s | Rp%.2f\n",
               i + 1,
               daftarBuku[i].kode,
               daftarBuku[i].nama,
               daftarBuku[i].jenis,
               daftarBuku[i].harga);
    }
}

// Menjalankan fungsi delete buku jika ada buku yang ingin dihapus
void deleteBuku() {
    viewBuku();
    if (jumlahBuku == 0) return;

    int index;
    printf("Masukkan index buku yang ingin dihapus: ");
    scanf("%d", &index);

    if (index < 1 || index > jumlahBuku) {
        printf("Index tidak valid!\n");
        return;
    }

    for (int i = index - 1; i < jumlahBuku - 1; i++) {
        daftarBuku[i] = daftarBuku[i + 1];
    }
    jumlahBuku--;
    printf("Data Successfully delete..\n");
}

// Menampilkan history penjualan
void viewHistory() {
    if (jumlahHistory == 0) {
        printf("\nBelum ada history penjualan.\n");
        return;
    }
    printf("\n=== History Penjualan ===\n");
    for (int i = 0; i < jumlahHistory; i++) {
        printf("%d. %s | Jumlah: %d | Total: Rp%.2f\n",
               i + 1,
               daftarHistory[i].kode,
               daftarHistory[i].jumlah,
               daftarHistory[i].total);
    }
}

// untuk menjalankan fungsi delete history jika ada history penjualan yang ingin dihapus
void deleteHistory() {
    viewHistory();
    if (jumlahHistory == 0) return;

    int index;
    printf("Masukkan index history yang ingin dihapus: ");
    scanf("%d", &index);

    if (index < 1 || index > jumlahHistory) {
        printf("Index tidak valid!\n");
        return;
    }

    for (int i = index - 1; i < jumlahHistory - 1; i++) {
        daftarHistory[i] = daftarHistory[i + 1];
    }
    jumlahHistory--;
    printf("Data Successfully delete..\n");
}

int main() {
    int pilihan;
    bacaDataBuku();
    bacaHistory();

    do {
        printf("\n=== Menu ===\n");
        printf("1. Input Buku\n");
        printf("2. View History\n");
        printf("3. View Buku\n");
        printf("4. Delete History\n");
        printf("5. Delete Buku\n");
        printf("6. Exit\n");
        printf("Pilih menu: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1: inputBuku(); break;
            case 2: viewHistory(); break;
            case 3: viewBuku(); break;
            case 4: deleteHistory(); break;
            case 5: deleteBuku(); break;
            case 6:
                // menyimpan semua file yang sebelumnya ada di memory sementara/RAM (Random Access Memory)
                simpanDataBuku();
                simpanHistory();
                printf("Data disimpan ke file. Keluar program...\n");
                break;
            default:
                printf("Pilihan tidak valid!\n");
        }
    } while (pilihan != 6);

    return 0;
}
