#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

	typedef struct {
    char kullaniciAdi[50];
    char sifre[50];
} Kullanici;

typedef struct {
    char isim[50];
    char uygunSaatler[10][20];
} HizmetSaglayici;

typedef struct {
    char hizmetTuru[50];
    char saglayiciIsim[50];
    char randevuSaati[20];
    int kullaniciId;
} Randevu;

Kullanici kullanicilar[100];
int kullaniciSayisi = 0;
HizmetSaglayici hizmetSaglayicilar[6][10];
Randevu randevular[50];
int randevuSayisi = 0;

void kayitOl();
int girisYap();
void hizmetleriGoster();
void randevuAl(int kullaniciId);
void hatirlatmaGonder(int kullaniciId);
void randevulariGor(int kullaniciId);
int gosterRandevular(int kullaniciId);
void resmiIslemlerFirslari();

int main() {
    int secim, kullaniciId = -1;

    strcpy(hizmetSaglayicilar[0][0].isim, "Dr. Ahmet");
    strcpy(hizmetSaglayicilar[0][0].uygunSaatler[0], "09:00");
    strcpy(hizmetSaglayicilar[0][0].uygunSaatler[1], "10:00");
    strcpy(hizmetSaglayicilar[0][0].uygunSaatler[2], "11:00");

    strcpy(hizmetSaglayicilar[0][1].isim, "Dr. Mehmet");
    strcpy(hizmetSaglayicilar[0][1].uygunSaatler[0], "12:00");
    strcpy(hizmetSaglayicilar[0][1].uygunSaatler[1], "14:00");

    strcpy(hizmetSaglayicilar[1][0].isim, "Kuafor Ali");
    strcpy(hizmetSaglayicilar[1][0].uygunSaatler[0], "14:00");
    strcpy(hizmetSaglayicilar[1][0].uygunSaatler[1], "15:00");

    strcpy(hizmetSaglayicilar[1][1].isim, "Kuafor Zeynep");
    strcpy(hizmetSaglayicilar[1][1].uygunSaatler[0], "16:00");
    strcpy(hizmetSaglayicilar[1][1].uygunSaatler[1], "17:00");

    strcpy(hizmetSaglayicilar[2][0].isim, "Elektrikci Mehmet");
    strcpy(hizmetSaglayicilar[2][0].uygunSaatler[0], "17:00");
    strcpy(hizmetSaglayicilar[2][0].uygunSaatler[1], "18:00");

    strcpy(hizmetSaglayicilar[2][1].isim, "Elektrikci Hasan");
    strcpy(hizmetSaglayicilar[2][1].uygunSaatler[0], "19:00");
    strcpy(hizmetSaglayicilar[2][1].uygunSaatler[1], "20:00");

    strcpy(hizmetSaglayicilar[3][0].isim, "Avukat Zeynep");
    strcpy(hizmetSaglayicilar[3][0].uygunSaatler[0], "19:00");
    strcpy(hizmetSaglayicilar[3][0].uygunSaatler[1], "20:00");

    strcpy(hizmetSaglayicilar[3][1].isim, "Avukat Ahmet");
    strcpy(hizmetSaglayicilar[3][1].uygunSaatler[0], "21:00");
    strcpy(hizmetSaglayicilar[3][1].uygunSaatler[1], "22:00");

    strcpy(hizmetSaglayicilar[4][0].isim, "Tercuman Elif");
    strcpy(hizmetSaglayicilar[4][0].uygunSaatler[0], "08:00");
    strcpy(hizmetSaglayicilar[4][0].uygunSaatler[1], "12:00");

    strcpy(hizmetSaglayicilar[4][1].isim, "Tercuman Ayse");
    strcpy(hizmetSaglayicilar[4][1].uygunSaatler[0], "16:00");
    strcpy(hizmetSaglayicilar[4][1].uygunSaatler[1], "18:00");

    while (kullaniciId == -1) {
        printf("\n--- Akilli Randevu Sistemi ---\n");
        printf("1. Kayit Ol\n");
        printf("2. Giris Yap\n");
        printf("Seciminizi yapin: ");
        scanf("%d", &secim);

        if (secim == 1) {
            kayitOl();
        } else if (secim == 2) {
            kullaniciId = girisYap();
        } else {
            printf("Gecersiz secim! Lutfen tekrar deneyin.\n");
        }
    }

    while (1) {
        printf("\n--- Ana Menu ---\n");
        printf("1. Randevu Al\n");
        printf("2. Hatirlatma Gonder\n");
        printf("3. Randevulari Gor\n");
        printf("4. Cikis\n");
        printf("Seciminizi yapin: ");
        scanf("%d", &secim);

        switch (secim) {
            case 1:
                randevuAl(kullaniciId);
                break;
            case 2:
                hatirlatmaGonder(kullaniciId);
                break;
            case 3:
                randevulariGor(kullaniciId);
                break;
            case 4:
                printf("Cikis yapiliyor... Tesekkurler!\n");
                exit(0);
            default:
                printf("Gecersiz secim!\n");
        }
    }
    return 0;
}

void kayitOl() {
    if (kullaniciSayisi >= 100) {
        printf("Maksimum kullanici sayisina ulasildi.\n");
        return;
    }

    printf("Kullanici adi: ");
    scanf("%s", kullanicilar[kullaniciSayisi].kullaniciAdi);
    printf("Sifre: ");
    scanf("%s", kullanicilar[kullaniciSayisi].sifre);

    kullaniciSayisi++;
    printf("Kayit basarili!\n");
}

int girisYap() {
    if (kullaniciSayisi == 0) {
        printf("Henuz kayitli bir hesap yok! Lutfen once kayit olun.\n");
        return -1;
    }

    char kullaniciAdi[50], sifre[50];
    printf("Kullanici adi: ");
    scanf("%s", kullaniciAdi);
    printf("Sifre: ");
    scanf("%s", sifre);

    for (int i = 0; i < kullaniciSayisi; i++) {
        if (strcmp(kullanicilar[i].kullaniciAdi, kullaniciAdi) == 0 &&
            strcmp(kullanicilar[i].sifre, sifre) == 0) {
            printf("Giris basarili!\n");
            return i;
        }
    }
    printf("Gecersiz kullanici adi veya sifre.\n");
    return -1;
}

void hizmetleriGoster() {
    printf("\nHizmet Turleri:\n");
    printf("1. Doktor\n");
    printf("2. Kuafor\n");
    printf("3. Elektrikci\n");
    printf("4. Avukat\n");
    printf("5. Tercuman\n");
    printf("6. Resmi Islemler\n");
}

void resmiIslemlerFirslari() {
    printf("\nResmi Islemler:\n");
    printf("1. Kimlik Yenileme\n");
    printf("2. Pasaport Basvurusu\n");
    printf("3. Vergi Dairesi Islemleri\n");
    printf("4. Nufus Kaydi\n");
}

void randevuAl(int kullaniciId) {
    int hizmetSecimi, saglayiciSecimi, saatSecimi, firmaSecimi;

    hizmetleriGoster();
    printf("Hizmet turunu secin: ");
    scanf("%d", &hizmetSecimi);

    if (hizmetSecimi == 6) {
        resmiIslemlerFirslari();
        scanf("%d", &firmaSecimi);

        if (firmaSecimi < 1 || firmaSecimi > 4) {
            printf("Gecersiz secim.\n");
            return;
        }

        printf("\nUygun Saatler:\n");
        printf(" 1. 08:00\n");
        printf(" 2. 09:00\n");
        printf(" 3. 10:00\n");
        printf(" 4. 11:00\n");
        printf(" 5. 12:00\n");
        printf(" 6. 13:00\n");
        printf(" 7. 14:00\n");
        printf(" 8. 15:00\n");
        printf(" 9. 16:00\n");
        printf("10. 17:00\n");
    } else if (hizmetSecimi < 1 || hizmetSecimi > 6) {
        printf("Gecersiz secim.\n");
        return;
    } else {
        printf("\nUygun Hizmet Saglayicilar:\n");
        for (int i = 0; i < 10; i++) {
            if (strlen(hizmetSaglayicilar[hizmetSecimi - 1][i].isim) > 0)
                printf("%d. %s\n", i + 1, hizmetSaglayicilar[hizmetSecimi - 1][i].isim);
        }

        printf("Hizmet saglayicisini secin: ");
        scanf("%d", &saglayiciSecimi);

        if (saglayiciSecimi < 1 || saglayiciSecimi > 10 ||
            strlen(hizmetSaglayicilar[hizmetSecimi - 1][saglayiciSecimi - 1].isim) == 0) {
            printf("Gecersiz secim.\n");
            return;
        }

        printf("\nUygun Saatler:\n");
        for (int i = 0; i < 10; i++) {
            if (strlen(hizmetSaglayicilar[hizmetSecimi - 1][saglayiciSecimi - 1].uygunSaatler[i]) > 0)
                printf("%d. %s\n", i + 1, hizmetSaglayicilar[hizmetSecimi - 1][saglayiciSecimi - 1].uygunSaatler[i]);
        }
    }

    printf("Randevu saatini secin: ");
    scanf("%d", &saatSecimi);

    if (hizmetSecimi == 6) {
        if (saatSecimi < 1 || saatSecimi > 10) {
            printf("Gecersiz secim.\n");
            return;
        }
        strcpy(randevular[randevuSayisi].randevuSaati,
               (saatSecimi == 1) ? "08:00" :
               (saatSecimi == 2) ? "09:00" :
               (saatSecimi == 3) ? "10:00" :
               (saatSecimi == 4) ? "11:00" :
               (saatSecimi == 5) ? "12:00" :
               (saatSecimi == 6) ? "13:00" :
               (saatSecimi == 7) ? "14:00" :
               (saatSecimi == 8) ? "15:00" :
               (saatSecimi == 9) ? "16:00" : "17:00");
    } else if (saatSecimi < 1 || saatSecimi > 10 ||
               strlen(hizmetSaglayicilar[hizmetSecimi - 1][saglayiciSecimi - 1].uygunSaatler[saatSecimi - 1]) == 0) {
        printf("Gecersiz secim.\n");
        return;
    } else {
        strcpy(randevular[randevuSayisi].randevuSaati,
               hizmetSaglayicilar[hizmetSecimi - 1][saglayiciSecimi - 1].uygunSaatler[saatSecimi - 1]);
    }

    strcpy(randevular[randevuSayisi].hizmetTuru, (hizmetSecimi == 1) ? "Doktor" :
                                             (hizmetSecimi == 2) ? "Kuafor" :
                                             (hizmetSecimi == 3) ? "Elektrikci" :
                                             (hizmetSecimi == 4) ? "Avukat" :
                                             (hizmetSecimi == 5) ? "Tercuman" :
                                             (hizmetSecimi == 6) ? "Resmi Islemler" : "Bilinmeyen");
    strcpy(randevular[randevuSayisi].saglayiciIsim, hizmetSecimi == 6 ? "Resmi Islemler" : hizmetSaglayicilar[hizmetSecimi - 1][saglayiciSecimi - 1].isim);

    randevular[randevuSayisi].kullaniciId = kullaniciId;
    randevuSayisi++;

    printf("Randevunuz basariyla alindi!\n");
}

void hatirlatmaGonder(int kullaniciId) {
    int randevuBulundu = 0;
    for (int i = 0; i < randevuSayisi; i++) {
        if (randevular[i].kullaniciId == kullaniciId) {
            randevuBulundu = 1;
            printf("Randevu hatirlaticisi:\n");
            printf("Bir hatirlatma mesaji, randevu saatinden once gonderilecektir.\n");

            break;
        }
    }
    if (!randevuBulundu) {
        printf("Henuz bir randevunuz bulunmamaktadir.\n");
    }
}

void randevulariGor(int kullaniciId) {
    int randevuBulundu = 0;
    for (int i = 0; i < randevuSayisi; i++) {
        if (randevular[i].kullaniciId == kullaniciId) {
            randevuBulundu = 1;
            printf("Randevulariniz:\n");
            printf("Hizmet: %s\n", randevular[i].hizmetTuru);
            printf("Saglayici: %s\n", randevular[i].saglayiciIsim);
            printf("Saat: %s\n", randevular[i].randevuSaati);
        }
    }
    if (!randevuBulundu) {
        printf("Henuz bir randevunuz bulunmamaktadir.\n");
    }
}

int gosterRandevular(int kullaniciId) {
    int randevuBulundu = 0;
    for (int i = 0; i < randevuSayisi; i++) {
        if (randevular[i].kullaniciId == kullaniciId) {
            randevuBulundu = 1;
            printf("Randevulariniz:\n");
            printf("Hizmet: %s\n", randevular[i].hizmetTuru);
            printf("Saglayici: %s\n", randevular[i].saglayiciIsim);
            printf("Saat: %s\n", randevular[i].randevuSaati);
        }
    }
    return randevuBulundu;
}