/*
 * 060-problema-registro-presenze.c
 *
 * Registro delle presenze di una settimana
 *
 * Il registro di un corso serale contiene, per 6 studenti e 5 giorni, un
 * carattere: 'P' (presente), 'A' (assente), 'R' (ritardo, conta come
 * presenza). Il docente vuole sapere:
 *   - per ogni studente: presenze, assenze, ritardi;
 *   - per ogni giorno: quanti erano presenti;
 *   - chi ha superato il limite di 1 assenza nella settimana;
 *   - le presenze di uno studente scelto da tastiera, giorno per giorno.
 *
 * Struttura dati:
 *   char registro[STUDENTI][GIORNI]   matrice di caratteri 'P', 'A', 'R'
 *   char studenti[STUDENTI][LUNG]     nomi, paralleli alle righe
 *   char giorni[GIORNI][4]            sigle dei giorni, parallele alle colonne
 */

#include <stdio.h>

#define STUDENTI 6
#define GIORNI   5
#define LUNG     16
#define LIMITE_ASSENZE 1

int main(void)
{
    char registro[STUDENTI][GIORNI] = {
        {'P', 'P', 'P', 'P', 'P'},
        {'P', 'A', 'P', 'R', 'P'},
        {'A', 'A', 'P', 'P', 'R'},
        {'P', 'P', 'R', 'R', 'P'},
        {'P', 'P', 'P', 'A', 'P'},
        {'A', 'P', 'A', 'P', 'A'}
    };
    char studenti[STUDENTI][LUNG] = {
        "Amato Elena", "Bruno Paolo", "Costa Marta",
        "De Luca Ivan", "Fontana Rita", "Greco Omar"
    };
    char giorni[GIORNI][4] = {"Lun", "Mar", "Mer", "Gio", "Ven"};

    int s;
    int g;
    int presenze;
    int assenze;
    int ritardi;
    int presenti_giorno;
    int scelto;

    /* ── 1. Registro con riepilogo per studente ───────────────────── */
    printf("=== REGISTRO PRESENZE - SETTIMANA 12 ===\n\n");
    printf("  %-16s", "Studente");
    for (g = 0; g < GIORNI; g++) {
        printf("%5s", giorni[g]);
    }
    printf("   Pres. Ass. Rit.\n");

    for (s = 0; s < STUDENTI; s++) {
        presenze = 0;
        assenze = 0;
        ritardi = 0;
        printf("  %-16s", studenti[s]);
        for (g = 0; g < GIORNI; g++) {
            printf("%5c", registro[s][g]);
            switch (registro[s][g]) {
                case 'P':
                    presenze++;
                    break;
                case 'R':
                    presenze++;     /* il ritardo conta come presenza */
                    ritardi++;
                    break;
                default:
                    assenze++;
                    break;
            }
        }
        printf("   %5d %4d %4d", presenze, assenze, ritardi);
        if (assenze > LIMITE_ASSENZE) {
            printf("  <- oltre il limite");
        }
        printf("\n");
    }

    /* ── 2. Presenti per giorno (per colonne) ─────────────────────── */
    printf("\n  %-16s", "Presenti");
    for (g = 0; g < GIORNI; g++) {
        presenti_giorno = 0;
        for (s = 0; s < STUDENTI; s++) {
            if (registro[s][g] != 'A') {
                presenti_giorno++;
            }
        }
        printf("%5d", presenti_giorno);
    }
    printf("\n\n");

    /* ── 3. Dettaglio di uno studente: una sola riga ──────────────── */
    printf("Studenti:\n");
    for (s = 0; s < STUDENTI; s++) {
        printf("  %d - %s\n", s + 1, studenti[s]);
    }
    do {
        printf("Numero dello studente (1-%d): ", STUDENTI);
        scanf("%d", &scelto);
    } while (scelto < 1 || scelto > STUDENTI);

    s = scelto - 1;
    printf("\nPresenze di %s:\n", studenti[s]);
    for (g = 0; g < GIORNI; g++) {
        printf("  %s: ", giorni[g]);
        switch (registro[s][g]) {
            case 'P':
                printf("presente\n");
                break;
            case 'R':
                printf("presente (ritardo)\n");
                break;
            default:
                printf("assente\n");
                break;
        }
    }

    return 0;
}
