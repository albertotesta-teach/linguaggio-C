/*
 * 070-problema-batteria-drone.c
 *
 * Laboratorio di robotica: la batteria del drone
 *
 * Nel laboratorio di robotica un drone viene usato per riprese della
 * scuola. Il programma di controllo tiene la carica della batteria (in
 * percentuale) e i minuti di volo totali, ed esegue i comandi:
 *     V n    vola per n minuti (consuma CONSUMO % al minuto)
 *     R n    ricarica per n minuti (RICARICA % al minuto, massimo 100)
 *     Q      termina
 * Un volo viene rifiutato se, alla fine, la carica scenderebbe sotto la
 * RISERVA di sicurezza.
 *
 * carica e minuti di volo sono parametri di ingresso e uscita:
 *   vola(&carica, &volo, n)      restituisce 1 se il volo è eseguito
 *   ricarica(&carica, n)         restituisce i punti percentuali aggiunti
 *   autonomia(carica)            minuti di volo ancora possibili (solo
 *                                lettura: basta il valore)
 */

#include <stdio.h>

#define CONSUMO  2
#define RICARICA 3
#define RISERVA  20

int vola(int *carica, int *volo, int minuti);
int ricarica(int *carica, int minuti);
int autonomia(int carica);

int main(void)
{
    int carica = 64;
    int volo = 0;
    char comando = ' ';
    int n;

    printf("=== DRONE DEL LABORATORIO ===\n");
    printf("Carica %d%%, autonomia %d minuti\n", carica, autonomia(carica));

    while (comando != 'Q') {
        printf("Comando (V n, R n, Q): ");
        if (scanf(" %c", &comando) != 1) {
            comando = 'Q';
        }
        if (comando == 'V' || comando == 'R') {
            if (scanf("%d", &n) != 1 || n <= 0) {
                printf("  Numero di minuti non valido.\n");
                comando = 'Q';
            } else if (comando == 'V') {
                if (vola(&carica, &volo, n)) {
                    printf("  Volo di %d minuti eseguito.", n);
                } else {
                    printf("  Volo rifiutato: la carica scenderebbe sotto il %d%%.", RISERVA);
                }
                printf(" Carica %d%%, autonomia %d minuti\n", carica, autonomia(carica));
            } else {
                printf("  Ricaricati %d punti.", ricarica(&carica, n));
                printf(" Carica %d%%, autonomia %d minuti\n", carica, autonomia(carica));
            }
        } else if (comando != 'Q') {
            printf("  Comando sconosciuto.\n");
        }
    }
    printf("Minuti di volo totali: %d, carica finale %d%%\n", volo, carica);

    return 0;
}

/* Esegue un volo di minuti minuti se la carica finale resta almeno
 * RISERVA: aggiorna *carica e *volo e restituisce 1, altrimenti 0. */
int vola(int *carica, int *volo, int minuti)
{
    int eseguito = 0;

    if (*carica - minuti * CONSUMO >= RISERVA) {
        *carica = *carica - minuti * CONSUMO;
        *volo = *volo + minuti;
        eseguito = 1;
    }
    return eseguito;
}

/* Ricarica per minuti minuti senza superare 100; restituisce i punti
 * percentuali effettivamente aggiunti. */
int ricarica(int *carica, int minuti)
{
    int prima = *carica;

    *carica = *carica + minuti * RICARICA;
    if (*carica > 100) {
        *carica = 100;
    }
    return *carica - prima;
}

/* Minuti di volo possibili senza scendere sotto la riserva. */
int autonomia(int carica)
{
    int minuti = 0;

    if (carica > RISERVA) {
        minuti = (carica - RISERVA) / CONSUMO;
    }
    return minuti;
}
