/*
 * 070-problema-posti-a-teatro.c
 *
 * Lo spettacolo di fine anno: prenotazioni dei posti in sala
 *
 * La sala cambia da un anno all'altro (aula magna, teatro comunale),
 * quindi righe e posti per riga si leggono all'avvio. La sala è una
 * matrice in un solo blocco: ogni cella contiene il codice della
 * prenotazione che occupa il posto, 0 se il posto è libero.
 *
 *     int *sala = calloc(righe * posti, sizeof *sala);   tutto libero
 *
 *     sala[r * posti + p]      riga r (A, B, ...), posto p (da 1)
 *
 * Una prenotazione occupa più posti vicini nella stessa riga e riceve un
 * codice progressivo (1, 2, 3, ...). Cancellarla rimette a 0 i suoi
 * posti.
 *
 * Comandi:
 *     P riga posto quanti    prenota quanti posti a partire da posto
 *     C codice               cancella la prenotazione
 *     M                      mappa della sala (. libero, # occupato)
 *     Q                      fine
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_RIGHE 26
#define MAX_POSTI 40

void mappa(const int sala[], int righe, int posti);

int main(void)
{
    int *sala;
    int righe;
    int posti;
    int codice = 0;
    int occupati = 0;
    int numero;
    int quanti;
    int liberi;
    int k;
    int r;
    char lettera;
    char comando = ' ';

    printf("Righe e posti per riga: ");
    if (scanf("%d %d", &righe, &posti) != 2 || righe < 1 || righe > MAX_RIGHE || posti < 1 ||
        posti > MAX_POSTI) {
        printf("Sala non valida (righe 1-%d, posti 1-%d).\n", MAX_RIGHE, MAX_POSTI);
    } else {
        sala = calloc(righe * posti, sizeof *sala);
        if (sala == NULL) {
            printf("Memoria insufficiente.\n");
        } else {
            while (comando != 'Q') {
                printf("Comando (P, C, M, Q): ");
                if (scanf(" %c", &comando) != 1) {
                    comando = 'Q';      /* input terminato: come Q */
                }
                comando = (char) toupper((unsigned char) comando);
                if (comando == 'P') {
                    if (scanf(" %c %d %d", &lettera, &numero, &quanti) == 3) {
                        lettera = (char) toupper((unsigned char) lettera);
                    } else {
                        lettera = ' ';          /* dati mancanti: non valido */
                    }
                    if (lettera < 'A' ||
                        lettera >= 'A' + righe || numero < 1 || quanti < 1 ||
                        numero + quanti - 1 > posti) {
                        printf("  Posti non validi.\n");
                    } else {
                        r = lettera - 'A';
                        liberi = 1;
                        for (k = numero - 1; k < numero - 1 + quanti; k++) {
                            if (sala[r * posti + k] != 0) {
                                liberi = 0;
                            }
                        }
                        if (!liberi) {
                            printf("  Alcuni posti sono gia' occupati.\n");
                        } else {
                            codice++;
                            for (k = numero - 1; k < numero - 1 + quanti; k++) {
                                sala[r * posti + k] = codice;
                            }
                            occupati = occupati + quanti;
                            printf("  prenotazione %d: %c%d-%c%d\n", codice, lettera, numero,
                                   lettera, numero + quanti - 1);
                        }
                    }
                } else if (comando == 'C') {
                    quanti = 0;
                    if (scanf("%d", &numero) == 1 && numero > 0) {
                        for (k = 0; k < righe * posti; k++) {
                            if (sala[k] == numero) {
                                sala[k] = 0;
                                quanti++;
                            }
                        }
                    }
                    if (quanti == 0) {
                        printf("  Prenotazione inesistente.\n");
                    } else {
                        occupati = occupati - quanti;
                        printf("  prenotazione %d cancellata: %s %d %s\n", numero,
                               quanti == 1 ? "liberato" : "liberati", quanti,
                               quanti == 1 ? "posto" : "posti");
                    }
                } else if (comando == 'M') {
                    mappa(sala, righe, posti);
                    printf("  occupati %d su %d\n", occupati, righe * posti);
                } else if (comando != 'Q') {
                    printf("  Comando sconosciuto.\n");
                }
                if (comando != 'Q') {
                    scanf("%*[^\n]");  /* un comando per riga */
                }
            }
            free(sala);
        }
    }

    return 0;
}

void mappa(const int sala[], int righe, int posti)
{
    int r;
    int p;

    printf("   palco\n");
    for (r = 0; r < righe; r++) {
        printf("  %c ", 'A' + r);
        for (p = 0; p < posti; p++) {
            printf("%c", sala[r * posti + p] == 0 ? '.' : '#');
        }
        printf("\n");
    }
}
