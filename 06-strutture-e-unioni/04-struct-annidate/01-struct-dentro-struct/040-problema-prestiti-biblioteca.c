/*
 * 040-problema-prestiti-biblioteca.c
 *
 * Biblioteca scolastica: prestiti scaduti e multe
 *
 * Ogni prestito ricorda il libro, lo studente e tre date: l'inizio del
 * prestito, la scadenza e la restituzione (anno zero se il libro non è
 * ancora tornato):
 *
 *     typedef struct {
 *         char titolo[28];
 *         char studente[20];
 *         Data inizio;
 *         Data scadenza;
 *         Data restituzione;
 *     } Prestito;
 *
 * Il programma legge la data di oggi (gg/mm/aaaa), la controlla e stampa
 * lo stato di ogni prestito:
 *   - restituito: data della restituzione, con il ritardo se c'è stato;
 *   - in corso: giorni che mancano alla scadenza, oppure giorni di
 *     ritardo e multa di 0.20 euro al giorno, al massimo 5 euro.
 *
 * Per contare i giorni tra due date si trasforma ogni data nel numero di
 * giorni trascorsi dal 1/1/2000, tenendo conto degli anni bisestili.
 */

#include <stdio.h>

#define PRESTITI 5
#define MULTA_GIORNO 0.20
#define MULTA_MASSIMA 5.00

typedef struct {
    int giorno;
    int mese;
    int anno;
} Data;

typedef struct {
    char titolo[28];
    char studente[20];
    Data inizio;
    Data scadenza;
    Data restituzione;
} Prestito;

int bisestile(int anno);
int giorni_nel_mese(int mese, int anno);
int data_valida(Data d);
int numero_giorno(Data d);
double multa(int giorni_ritardo);

int main(void)
{
    Prestito prestiti[PRESTITI] = {
        {"Il barone rampante", "Rossi Elena", {3, 11, 2025}, {3, 12, 2025}, {28, 11, 2025}},
        {"Fahrenheit 451", "Greco Paolo", {10, 11, 2025}, {10, 12, 2025}, {0, 0, 0}},
        {"Io, robot", "Costa Marta", {17, 11, 2025}, {17, 12, 2025}, {0, 0, 0}},
        {"La luna e i falo'", "Villa Sara", {20, 10, 2025}, {19, 11, 2025}, {0, 0, 0}},
        {"Se questo e' un uomo", "Neri Luca", {1, 11, 2025}, {1, 12, 2025}, {5, 12, 2025}}
    };
    Data oggi;
    int giorni;
    int i;

    printf("Data di oggi (gg/mm/aaaa): ");
    if (scanf("%d/%d/%d", &oggi.giorno, &oggi.mese, &oggi.anno) != 3 || !data_valida(oggi)) {
        printf("Data non valida.\n");
    } else {
        for (i = 0; i < PRESTITI; i++) {
            printf("%-21s %-12s scad. %02d/%02d  ", prestiti[i].titolo, prestiti[i].studente,
                   prestiti[i].scadenza.giorno, prestiti[i].scadenza.mese);
            if (prestiti[i].restituzione.anno != 0) {
                giorni = numero_giorno(prestiti[i].restituzione) - numero_giorno(prestiti[i].scadenza);
                printf("restituito il %02d/%02d", prestiti[i].restituzione.giorno,
                       prestiti[i].restituzione.mese);
                if (giorni > 0) {
                    printf(" con %d %s di ritardo", giorni, giorni == 1 ? "giorno" : "giorni");
                }
                printf("\n");
            } else {
                giorni = numero_giorno(oggi) - numero_giorno(prestiti[i].scadenza);
                if (giorni < 0) {
                    printf("in corso, %s %d %s\n", giorni == -1 ? "manca" : "mancano", -giorni,
                           giorni == -1 ? "giorno" : "giorni");
                } else if (giorni == 0) {
                    printf("scade oggi\n");
                } else {
                    printf("IN RITARDO di %d %s, multa %.2f euro\n", giorni,
                           giorni == 1 ? "giorno" : "giorni", multa(giorni));
                }
            }
        }
    }

    return 0;
}

int bisestile(int anno)
{
    return (anno % 4 == 0 && anno % 100 != 0) || anno % 400 == 0;
}

int giorni_nel_mese(int mese, int anno)
{
    int giorni[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int risultato = giorni[mese - 1];

    if (mese == 2 && bisestile(anno)) {
        risultato = 29;
    }
    return risultato;
}

/* Anni dal 2000 in poi: le date della biblioteca non vanno più indietro. */
int data_valida(Data d)
{
    return d.anno >= 2000 && d.mese >= 1 && d.mese <= 12 && d.giorno >= 1 &&
           d.giorno <= giorni_nel_mese(d.mese, d.anno);
}

/* Giorni trascorsi dal 1/1/2000 (che vale 0). */
int numero_giorno(Data d)
{
    int giorni = d.giorno - 1;
    int anno;
    int mese;

    for (anno = 2000; anno < d.anno; anno++) {
        giorni = giorni + (bisestile(anno) ? 366 : 365);
    }
    for (mese = 1; mese < d.mese; mese++) {
        giorni = giorni + giorni_nel_mese(mese, d.anno);
    }
    return giorni;
}

double multa(int giorni_ritardo)
{
    double euro = giorni_ritardo * MULTA_GIORNO;

    if (euro > MULTA_MASSIMA) {
        euro = MULTA_MASSIMA;
    }
    return euro;
}
