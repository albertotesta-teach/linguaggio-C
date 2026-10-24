/*
 * 080-problema-pianta-sala-esame.c
 *
 * Esame di Stato: la disposizione dei candidati in aula magna
 *
 * L'aula magna ha 5 file da 8 banchi. Per la prova scritta due candidati
 * non possono sedere vicini: la commissione usa la disposizione a
 * scacchiera, in cui un banco è occupabile solo se fila + banco è pari.
 * Così nessun candidato ha un vicino davanti, dietro o di lato. Alcuni
 * banchi sono rotti ('#') e non si possono usare.
 *
 *     typedef char Pianta[FILE_BANCHI][BANCHI];
 *
 *     int disponi(Pianta p, int candidati);      restituisce quanti ne ha messi
 *     int capienza(const Pianta p);              banchi a scacchiera non rotti
 *     void stampa(const Pianta p);
 *
 * disponi modifica la Pianta del chiamante: scrive 'C' nei banchi
 * assegnati, in ordine di fila e di banco. Il programma legge il numero
 * di candidati, stampa la pianta e, se non bastano i posti, indica quanti
 * candidati vanno in una seconda aula.
 */

#include <stdio.h>

#define FILE_BANCHI 5
#define BANCHI      8

typedef char Pianta[FILE_BANCHI][BANCHI];

int disponi(Pianta p, int candidati);
int capienza(const Pianta p);
void stampa(const Pianta p);
int occupabile(const Pianta p, int f, int b);

int main(void)
{
    Pianta aula;
    int f;
    int b;
    int candidati;
    int sistemati;

    /* tutti i banchi liberi, poi i tre banchi rotti */
    for (f = 0; f < FILE_BANCHI; f++) {
        for (b = 0; b < BANCHI; b++) {
            aula[f][b] = '.';
        }
    }
    aula[1][3] = '#';
    aula[2][4] = '#';
    aula[4][0] = '#';

    printf("Banchi disponibili a scacchiera: %d\n", capienza(aula));
    printf("Numero di candidati: ");
    if (scanf("%d", &candidati) != 1 || candidati < 0) {
        printf("Valore non valido.\n");
    } else {
        sistemati = disponi(aula, candidati);
        stampa(aula);
        printf("Candidati sistemati: %d\n", sistemati);
        if (sistemati < candidati) {
            printf("Serve una seconda aula per %d %s.\n", candidati - sistemati,
                   candidati - sistemati == 1 ? "candidato" : "candidati");
        }
    }

    return 0;
}

/* Banco occupabile: posizione a scacchiera e non rotto. */
int occupabile(const Pianta p, int f, int b)
{
    return (f + b) % 2 == 0 && p[f][b] == '.';
}

int capienza(const Pianta p)
{
    int f;
    int b;
    int posti = 0;

    for (f = 0; f < FILE_BANCHI; f++) {
        for (b = 0; b < BANCHI; b++) {
            if (occupabile(p, f, b)) {
                posti++;
            }
        }
    }
    return posti;
}

/* Assegna i banchi in ordine finché ci sono candidati e posti. */
int disponi(Pianta p, int candidati)
{
    int f = 0;
    int b;
    int messi = 0;

    while (f < FILE_BANCHI && messi < candidati) {
        b = 0;
        while (b < BANCHI && messi < candidati) {
            if (occupabile(p, f, b)) {
                p[f][b] = 'C';
                messi++;
            }
            b++;
        }
        f++;
    }
    return messi;
}

void stampa(const Pianta p)
{
    int f;
    int b;

    printf("\n         CATTEDRA\n");
    for (f = 0; f < FILE_BANCHI; f++) {
        printf("  fila %d ", f + 1);
        for (b = 0; b < BANCHI; b++) {
            printf("%c ", p[f][b]);
        }
        printf("\n");
    }
    printf("  C = candidato, . = libero, # = banco rotto\n\n");
}
