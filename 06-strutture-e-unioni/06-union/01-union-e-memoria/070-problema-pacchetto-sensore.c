/*
 * 070-problema-pacchetto-sensore.c
 *
 * La centralina meteo sul tetto della scuola: decodificare i pacchetti
 *
 * La centralina invia pacchetti di 8 byte. Il ricevitore li scrive in un
 * array di byte; una union permette di leggere gli stessi byte come
 * campi:
 *
 *     typedef union {
 *         uint8_t grezzi[8];
 *         struct {
 *             int16_t temperatura;      decimi di grado
 *             uint16_t umidita;         decimi di percento
 *             uint16_t batteria;        millivolt
 *             uint8_t sensore;
 *             uint8_t controllo;
 *         } campi;
 *     } Pacchetto;
 *
 * I campi della struct sono 2 + 2 + 2 + 1 + 1 = 8 byte, senza padding:
 * il programma lo controlla con sizeof prima di usare la union. I numeri
 * a 16 bit arrivano con il byte meno significativo per primo, come li
 * memorizza una macchina little-endian.
 *
 * Il byte di controllo è la somma dei primi 7 byte modulo 256: se non
 * corrisponde il pacchetto è corrotto. Con la batteria sotto 3000 mV
 * viene segnalato di cambiare le pile.
 *
 * Il programma legge i pacchetti come 8 numeri esadecimali per riga
 * fino a FINE.
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BYTE 8
#define LUNG 64
#define BATTERIA_MINIMA 3000

typedef union {
    uint8_t grezzi[BYTE];
    struct {
        int16_t temperatura;
        uint16_t umidita;
        uint16_t batteria;
        uint8_t sensore;
        uint8_t controllo;
    } campi;
} Pacchetto;

int leggi_pacchetto(const char *riga, Pacchetto *p);
int controllo_corretto(const Pacchetto *p);

int main(void)
{
    char riga[LUNG];
    Pacchetto p;
    int finito = 0;

    if (sizeof(p.campi) != BYTE) {
        printf("I campi occupano %zu byte invece di %d: il programma non puo' funzionare.\n",
               sizeof(p.campi), BYTE);
        finito = 1;
    }
    while (!finito) {
        printf("Pacchetto (8 byte esadecimali, FINE): ");
        if (fgets(riga, LUNG, stdin) == NULL || strncmp(riga, "FINE", 4) == 0) {
            finito = 1;
        } else if (!leggi_pacchetto(riga, &p)) {
            printf("  Servono 8 byte.\n");
        } else if (!controllo_corretto(&p)) {
            printf("  Pacchetto corrotto: controllo errato.\n");
        } else {
            printf("  sensore %d: %.1f gradi, umidita' %.1f%%, batteria %d mV%s\n",
                   p.campi.sensore, p.campi.temperatura / 10.0, p.campi.umidita / 10.0,
                   p.campi.batteria,
                   p.campi.batteria < BATTERIA_MINIMA ? "  CAMBIARE LE PILE" : "");
        }
    }

    return 0;
}

/* Legge 8 numeri esadecimali nei byte grezzi. */
int leggi_pacchetto(const char *riga, Pacchetto *p)
{
    unsigned int b[BYTE];
    int letti;
    int i;

    letti = sscanf(riga, "%x %x %x %x %x %x %x %x", &b[0], &b[1], &b[2], &b[3], &b[4], &b[5],
                   &b[6], &b[7]);
    if (letti == BYTE) {
        for (i = 0; i < BYTE; i++) {
            p->grezzi[i] = (uint8_t) b[i];
        }
    }
    return letti == BYTE;
}

int controllo_corretto(const Pacchetto *p)
{
    unsigned int somma = 0;
    int i;

    for (i = 0; i < BYTE - 1; i++) {
        somma = somma + p->grezzi[i];
    }
    return somma % 256 == p->campi.controllo;
}
