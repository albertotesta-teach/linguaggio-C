/*
 * 060-problema-confronto-pagelle.c
 *
 * Consiglio di classe: confronto tra primo e secondo quadrimestre
 *
 * Per il consiglio di classe il coordinatore confronta le due pagelle di
 * uno studente. Una pagella contiene il nome, il quadrimestre e il voto di
 * ogni materia:
 *
 *     typedef struct {
 *         char nome[20];
 *         int quadrimestre;
 *         int voti[MATERIE];
 *     } Pagella;
 *
 * Il programma legge i voti del secondo quadrimestre partendo da una
 * COPIA del primo (secondo = primo; poi si cambiano quadrimestre e voti),
 * così il nome è già corretto. Poi confronta le due pagelle materia per
 * materia e stampa:
 *   - la variazione di ogni voto (+1, -2, =);
 *   - le materie migliorate e peggiorate;
 *   - le due medie;
 *   - le insufficienze recuperate (voto da sotto 6 a 6 o più).
 * Un voto fuori dall'intervallo 1-10 lascia invariato il voto copiato.
 */

#include <stdio.h>

#define MATERIE 5

typedef struct {
    char nome[20];
    int quadrimestre;
    int voti[MATERIE];
} Pagella;

void svuota_riga(void);

int main(void)
{
    const char *materie[MATERIE] = {"italiano", "storia", "inglese", "matematica", "informatica"};
    Pagella primo = {"Davide Greco", 1, {6, 7, 5, 4, 8}};
    Pagella secondo;
    int m;
    int voto;
    int letti;
    int migliorate = 0;
    int peggiorate = 0;
    int recuperate = 0;
    int somma_primo = 0;
    int somma_secondo = 0;

    secondo = primo;
    secondo.quadrimestre = 2;

    printf("Voti del secondo quadrimestre di %s\n", secondo.nome);
    for (m = 0; m < MATERIE; m++) {
        printf("  %-12s (primo: %d): ", materie[m], primo.voti[m]);
        letti = scanf("%d", &voto);
        if (letti == 0) {
            svuota_riga();              /* non e' un numero */
        }
        if (letti == 1 && voto >= 1 && voto <= 10) {
            secondo.voti[m] = voto;
        } else {
            printf("  voto non valido, resta %d\n", secondo.voti[m]);
        }
    }

    printf("\n  %-12s %4s %4s  Variazione\n", "Materia", "1Q", "2Q");
    for (m = 0; m < MATERIE; m++) {
        printf("  %-12s %4d %4d  ", materie[m], primo.voti[m], secondo.voti[m]);
        if (secondo.voti[m] > primo.voti[m]) {
            printf("%+d\n", secondo.voti[m] - primo.voti[m]);
            migliorate++;
        } else if (secondo.voti[m] < primo.voti[m]) {
            printf("%+d\n", secondo.voti[m] - primo.voti[m]);
            peggiorate++;
        } else {
            printf("=\n");
        }
        if (primo.voti[m] < 6 && secondo.voti[m] >= 6) {
            recuperate++;
        }
        somma_primo = somma_primo + primo.voti[m];
        somma_secondo = somma_secondo + secondo.voti[m];
    }

    printf("\nMaterie migliorate: %d, peggiorate: %d\n", migliorate, peggiorate);
    printf("Media: %.2f -> %.2f\n", (double) somma_primo / MATERIE, (double) somma_secondo / MATERIE);
    printf("Insufficienze recuperate: %d\n", recuperate);

    return 0;
}

/* Scarta i caratteri rimasti sulla riga. */
void svuota_riga(void)
{
    int c;

    c = getchar();
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}
