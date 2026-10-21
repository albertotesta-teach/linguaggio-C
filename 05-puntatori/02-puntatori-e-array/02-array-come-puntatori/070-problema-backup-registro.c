/*
 * 070-problema-backup-registro.c
 *
 * Registro dei voti: copia di sicurezza e annullamento delle modifiche
 *
 * Prima di correggere i voti di una verifica, il registro elettronico ne fa
 * una copia di sicurezza. Il docente inserisce le correzioni (numero dello
 * studente e nuovo voto); al termine il programma mostra le differenze
 * rispetto alla copia e chiede conferma. Se il docente non conferma, i voti
 * vengono ripristinati dalla copia.
 *
 * La copia di un blocco di memoria è scritta con due puntatori che
 * avanzano insieme: *d = *s; d++; s++;  La stessa funzione serve sia per
 * il backup sia per il ripristino, scambiando sorgente e destinazione.
 *
 * Funzioni:
 *   copia_blocco(dest, sorgente, n)
 *   mostra_differenze(attuali, backup, n, nomi)  quanti voti sono cambiati
 *   stampa_registro(voti, n, nomi)
 */

#include <stdio.h>

#define STUDENTI 8
#define LUNG     12

void copia_blocco(int *dest, const int *sorgente, int n);
int mostra_differenze(const int *attuali, const int *backup, int n,
                      const char nomi[][LUNG]);
void stampa_registro(const int *voti, int n, const char nomi[][LUNG]);
void svuota_riga(void);

int main(void)
{
    char nomi[STUDENTI][LUNG] = {"Bianchi", "Colombo", "Ferrari", "Galli",
                                 "Marino", "Ricci", "Russo", "Villa"};
    int voti[STUDENTI] = {6, 7, 5, 8, 4, 9, 6, 7};
    int backup[STUDENTI];
    int studente = 1;
    int voto = 0;
    int letti;
    int cambiati;
    char risposta = 'S';

    copia_blocco(backup, voti, STUDENTI);
    printf("=== REGISTRO (copia di sicurezza eseguita) ===\n");
    stampa_registro(voti, STUDENTI, nomi);

    while (studente != 0) {
        printf("Studente (1-%d) e nuovo voto, 0 0 per finire: ", STUDENTI);
        letti = scanf("%d %d", &studente, &voto);
        if (letti == EOF) {
            studente = 0;               /* input terminato: come 0 0 */
        } else if (letti != 2) {
            svuota_riga();              /* non sono due numeri */
            studente = -1;
        }
        if (studente < 0 || studente > STUDENTI) {
            printf("  Studente inesistente.\n");
        } else if (studente != 0 && (voto < 1 || voto > 10)) {
            printf("  Il voto deve essere tra 1 e 10.\n");
        } else if (studente != 0) {
            voti[studente - 1] = voto;
        }
    }

    printf("\n=== MODIFICHE RISPETTO ALLA COPIA ===\n");
    cambiati = mostra_differenze(voti, backup, STUDENTI, nomi);
    if (cambiati > 0) {
        printf("Voti modificati: %d. Confermi? (S/N): ", cambiati);
        if (scanf(" %c", &risposta) != 1) {
            risposta = 'N';
        }
        if (risposta != 'S' && risposta != 's') {
            copia_blocco(voti, backup, STUDENTI);
            printf("Modifiche annullate: voti ripristinati dalla copia.\n");
        } else {
            printf("Modifiche confermate.\n");
        }
    }

    printf("\n=== REGISTRO FINALE ===\n");
    stampa_registro(voti, STUDENTI, nomi);

    return 0;
}

/* Copia n interi da sorgente a dest. */
void copia_blocco(int *dest, const int *sorgente, int n)
{
    int *d = dest;
    const int *s = sorgente;

    while (d < dest + n) {
        *d = *s;
        d++;
        s++;
    }
}

/* Stampa gli studenti il cui voto è diverso dalla copia e ne restituisce
 * il numero. I due puntatori avanzano insieme sui due array. */
int mostra_differenze(const int *attuali, const int *backup, int n,
                      const char nomi[][LUNG])
{
    const int *a;
    const int *b = backup;
    int differenze = 0;

    for (a = attuali; a < attuali + n; a++) {
        if (*a != *b) {
            printf("  %-10s %2d -> %2d\n", nomi[a - attuali], *b, *a);
            differenze++;
        }
        b++;
    }
    if (differenze == 0) {
        printf("  Nessuna modifica.\n");
    }
    return differenze;
}

void stampa_registro(const int *voti, int n, const char nomi[][LUNG])
{
    int i;

    for (i = 0; i < n; i++) {
        printf("  %d. %-10s %2d\n", i + 1, nomi[i], voti[i]);
    }
}

/* Scarta i caratteri rimasti sulla riga dopo un inserimento errato. */
void svuota_riga(void)
{
    int c;

    c = getchar();
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}
