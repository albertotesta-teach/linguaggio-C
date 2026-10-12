/*
 * 030-da-testo-a-enum.c
 *
 * Da testo a enum e da enum a testo
 *
 * L'utente scrive parole, il programma lavora con le costanti. Una sola
 * tabella di nomi, indicizzata dall'enum, serve in tutte e due le
 * direzioni:
 *
 *     const char *a_testo(Materia m);           nomi[m]
 *     Materia da_testo(const char *parola);     cerca la parola in nomi
 *
 * Per una parola che non corrisponde a nessuna costante serve un valore
 * in più. Si mette dopo NUM_MATERIE, così non diventa un indice valido
 * della tabella:
 *
 *     typedef enum {
 *         ITALIANO, MATEMATICA, INGLESE, INFORMATICA,
 *         NUM_MATERIE,
 *         MATERIA_NON_VALIDA
 *     } Materia;
 *
 * Esempio: il registro delle ore di lezione svolte. Il docente scrive
 * le materie delle ore fatte; il programma conta le ore di ogni materia
 * e segnala le parole che non sono materie. FINE termina.
 */

#include <stdio.h>
#include <string.h>

typedef enum {
    ITALIANO, MATEMATICA, INGLESE, INFORMATICA,
    NUM_MATERIE,
    MATERIA_NON_VALIDA
} Materia;

const char *a_testo(Materia m);
Materia da_testo(const char *parola);

int main(void)
{
    int ore[NUM_MATERIE] = {0};
    char parola[20];
    Materia m;
    int finito = 0;

    while (!finito) {
        printf("Materia (FINE per terminare): ");
        if (scanf("%19s", parola) != 1 || strcmp(parola, "FINE") == 0) {
            finito = 1;
        } else {
            m = da_testo(parola);
            if (m == MATERIA_NON_VALIDA) {
                printf("  \"%s\" non e' una materia.\n", parola);
            } else {
                ore[m]++;
            }
        }
    }

    printf("Ore svolte:\n");
    for (m = ITALIANO; m < NUM_MATERIE; m++) {
        printf("  %-12s %d\n", a_testo(m), ore[m]);
    }

    return 0;
}

const char *a_testo(Materia m)
{
    const char *nomi[NUM_MATERIE] = {[ITALIANO] = "italiano", [MATEMATICA] = "matematica",
                                     [INGLESE] = "inglese", [INFORMATICA] = "informatica"};
    const char *testo = "?";

    if (m >= ITALIANO && m < NUM_MATERIE) {
        testo = nomi[m];
    }
    return testo;
}

/* Confronta la parola con il nome di ogni materia. */
Materia da_testo(const char *parola)
{
    Materia trovata = MATERIA_NON_VALIDA;
    Materia m = ITALIANO;

    while (m < NUM_MATERIE && trovata == MATERIA_NON_VALIDA) {
        if (strcmp(a_testo(m), parola) == 0) {
            trovata = m;
        }
        m++;
    }
    return trovata;
}
