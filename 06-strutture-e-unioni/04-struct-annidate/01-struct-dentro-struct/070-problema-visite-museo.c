/*
 * 070-problema-visite-museo.c
 *
 * Museo civico: prenotazioni delle visite guidate per le classi
 *
 * Il museo ha una sola guida: due visite nello stesso giorno non possono
 * sovrapporsi. Ogni visita ha classe, docente accompagnatore, giorno,
 * orario di inizio e durata in minuti:
 *
 *     typedef struct {
 *         char classe[4];
 *         char docente[16];
 *         Data giorno;
 *         Orario inizio;
 *         int durata;
 *     } Visita;
 *
 * Il programma legge le richieste nella forma
 *     classe docente gg/mm/aaaa hh:mm durata
 * e accetta la visita se:
 *   - la durata è tra 30 e 180 minuti;
 *   - inizia dalle 9:00 e finisce entro le 17:00;
 *   - non si sovrappone a un'altra visita dello stesso giorno.
 * La riga FINE termina; alla fine si stampa il calendario.
 *
 * Due visite dello stesso giorno si sovrappongono se ognuna inizia prima
 * che l'altra finisca. Gli orari si confrontano in minuti dalla
 * mezzanotte.
 */

#include <stdio.h>
#include <string.h>

#define MAX_VISITE 8
#define APERTURA (9 * 60)
#define CHIUSURA (17 * 60)

typedef struct {
    int giorno;
    int mese;
    int anno;
} Data;

typedef struct {
    int ore;
    int minuti;
} Orario;

typedef struct {
    char classe[4];
    char docente[16];
    Data giorno;
    Orario inizio;
    int durata;
} Visita;

int main(void)
{
    Visita visite[MAX_VISITE] = {
        {"3B", "Galli", {12, 3, 2026}, {9, 30}, 90},
        {"1A", "Ferri", {12, 3, 2026}, {14, 0}, 60}
    };
    int n_visite = 2;
    Visita nuova;
    char parola[8];
    int inizio;
    int fine;
    int altro_inizio;
    int altra_fine;
    int conflitto;
    int finito = 0;
    int i;

    while (!finito) {
        printf("Visita (classe docente gg/mm/aaaa hh:mm durata, FINE): ");
        if (scanf("%7s", parola) != 1 || strcmp(parola, "FINE") == 0) {
            finito = 1;
        } else if (scanf("%15s %d/%d/%d %d:%d %d", nuova.docente, &nuova.giorno.giorno,
                         &nuova.giorno.mese, &nuova.giorno.anno, &nuova.inizio.ore,
                         &nuova.inizio.minuti, &nuova.durata) != 7) {
            printf("  Richiesta non valida.\n");
            finito = 1;
        } else if (strlen(parola) >= sizeof(nuova.classe)) {
            printf("  Classe %s non valida.\n", parola);
        } else {
            strcpy(nuova.classe, parola);
            inizio = nuova.inizio.ore * 60 + nuova.inizio.minuti;
            fine = inizio + nuova.durata;
            conflitto = -1;
            for (i = 0; i < n_visite; i++) {
                altro_inizio = visite[i].inizio.ore * 60 + visite[i].inizio.minuti;
                altra_fine = altro_inizio + visite[i].durata;
                if (visite[i].giorno.giorno == nuova.giorno.giorno &&
                    visite[i].giorno.mese == nuova.giorno.mese &&
                    visite[i].giorno.anno == nuova.giorno.anno && inizio < altra_fine &&
                    altro_inizio < fine) {
                    conflitto = i;
                }
            }
            if (nuova.durata < 30 || nuova.durata > 180) {
                printf("  Durata non ammessa (da 30 a 180 minuti).\n");
            } else if (inizio < APERTURA || fine > CHIUSURA) {
                printf("  Fuori dall'orario del museo (9:00-17:00).\n");
            } else if (conflitto != -1) {
                printf("  Sovrapposta alla visita della %s (%02d:%02d, %d min).\n",
                       visite[conflitto].classe, visite[conflitto].inizio.ore,
                       visite[conflitto].inizio.minuti, visite[conflitto].durata);
            } else if (n_visite == MAX_VISITE) {
                printf("  Calendario pieno.\n");
            } else {
                visite[n_visite] = nuova;
                n_visite++;
                printf("  Prenotata: %s con %s, fine alle %02d:%02d.\n", nuova.classe,
                       nuova.docente, fine / 60, fine % 60);
            }
        }
    }

    printf("\nCalendario delle visite\n");
    for (i = 0; i < n_visite; i++) {
        printf("  %02d/%02d/%d  %02d:%02d  %3d min  %-3s %s\n", visite[i].giorno.giorno,
               visite[i].giorno.mese, visite[i].giorno.anno, visite[i].inizio.ore,
               visite[i].inizio.minuti, visite[i].durata, visite[i].classe, visite[i].docente);
    }

    return 0;
}
