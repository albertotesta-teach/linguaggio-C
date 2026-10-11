/*
 * 040-problema-turno-di-guardia.c
 *
 * Sportello di tutoraggio: il docente di turno
 *
 * Lo sportello pomeridiano di tutoraggio è coperto a rotazione da cinque
 * docenti. Il registro tiene le ore svolte da ciascuno (array ore) e un
 * puntatore, turno, all'elemento del docente di turno. Comandi:
 *     T   il docente di turno svolge un'ora; il turno passa al successivo
 *     S   il docente di turno è assente: il turno passa senza ore
 *     Q   fine, con il riepilogo delle ore
 *
 * passa_turno(&turno, ore, n) sposta il puntatore del chiamante
 * all'elemento successivo, ricominciando dal primo dopo l'ultimo. Riceve
 * int ** perché deve cambiare il puntatore turno del main, non i valori.
 */

#include <stdio.h>

#define DOCENTI 5
#define LUNG    12

void passa_turno(int **turno, int *ore, int n);

int main(void)
{
    char nomi[DOCENTI][LUNG] = {"Rossi", "Bianco", "Greco", "Fontana", "Conti"};
    int ore[DOCENTI] = {0, 0, 0, 0, 0};
    int *turno = &ore[0];
    char comando = ' ';
    int i;

    printf("=== SPORTELLO DI TUTORAGGIO ===\n");
    while (comando != 'Q') {
        printf("Di turno: %s. Comando (T svolto, S assente, Q fine): ",
               nomi[turno - ore]);
        if (scanf(" %c", &comando) != 1) {
            comando = 'Q';
        }
        if (comando == 'T') {
            *turno = *turno + 1;
            printf("  %s ha svolto la sua %da ora\n", nomi[turno - ore], *turno);
            passa_turno(&turno, ore, DOCENTI);
        } else if (comando == 'S') {
            printf("  %s assente, turno al successivo\n", nomi[turno - ore]);
            passa_turno(&turno, ore, DOCENTI);
        } else if (comando != 'Q') {
            printf("  Comando sconosciuto.\n");
        }
    }

    printf("\nOre svolte:");
    for (i = 0; i < DOCENTI; i++) {
        printf("  %s %d", nomi[i], ore[i]);
    }
    printf("\n");

    return 0;
}

/* Fa avanzare *turno all'elemento successivo di ore; dopo l'ultimo torna
 * al primo. */
void passa_turno(int **turno, int *ore, int n)
{
    if (*turno == ore + n - 1) {
        *turno = ore;
    } else {
        (*turno)++;
    }
}
