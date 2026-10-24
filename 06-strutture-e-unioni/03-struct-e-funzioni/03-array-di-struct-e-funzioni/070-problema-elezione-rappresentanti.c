/*
 * 070-problema-elezione-rappresentanti.c
 *
 * Elezione dei rappresentanti di istituto: lo spoglio delle schede
 *
 * I candidati sono identificati da un numero di lista. Lo spoglio legge
 * una scheda alla volta: il numero del candidato votato, 0 per scheda
 * bianca, un numero inesistente per scheda nulla; -1 termina.
 *
 *     typedef struct {
 *         int numero;
 *         char nome[20];
 *         char classe[4];
 *         int voti;
 *     } Candidato;
 *
 *     Candidato *cerca(Candidato c[], int n, int numero);
 *     void classifica_primi(const Candidato c[], int n, int *primo, int *secondo);
 *
 * classifica_primi trova i due candidati più votati scorrendo l'array una
 * volta, senza ordinarlo, e li restituisce come indici. Vengono eletti i
 * primi due; se il secondo e il terzo sono a pari voti serve un
 * ballottaggio, e il programma lo segnala.
 */

#include <stdio.h>

#define CANDIDATI 5
#define ELETTI 2

typedef struct {
    int numero;
    char nome[20];
    char classe[4];
    int voti;
} Candidato;

Candidato *cerca(Candidato c[], int n, int numero);
void classifica_primi(const Candidato c[], int n, int *primo, int *secondo);
void svuota_riga(void);

int main(void)
{
    Candidato lista[CANDIDATI] = {
        {1, "Rossi Elena", "4A", 0},
        {2, "Marchetti Luca", "5B", 0},
        {3, "Sanna Giulia", "3C", 0},
        {4, "Ferri Omar", "4B", 0},
        {5, "Leone Chiara", "5A", 0}
    };
    Candidato *votato;
    int scheda = 0;
    int bianche = 0;
    int nulle = 0;
    int valide = 0;
    int primo;
    int secondo;
    int i;
    int pari_merito = 0;
    int letti;

    while (scheda != -1) {
        printf("Scheda (numero candidato, 0 bianca, -1 fine): ");
        letti = scanf("%d", &scheda);
        if (letti == EOF) {
            scheda = -1;                /* input terminato: come -1 */
        } else if (letti == 0) {
            svuota_riga();              /* non e' un numero */
            printf("  Inserimento non valido, ripetere.\n");
        } else if (scheda == 0) {
            bianche++;
        } else if (scheda != -1) {
            votato = cerca(lista, CANDIDATI, scheda);
            if (votato == NULL) {
                nulle++;
            } else {
                votato->voti++;
                valide++;
            }
        }
    }

    printf("\nSchede valide %d, bianche %d, nulle %d\n", valide, bianche, nulle);
    for (i = 0; i < CANDIDATI; i++) {
        printf("  %d. %-15s %s  voti %2d\n", lista[i].numero, lista[i].nome, lista[i].classe,
               lista[i].voti);
    }

    if (valide == 0) {
        printf("\nNessun voto valido: nessun eletto.\n");
    } else {
        classifica_primi(lista, CANDIDATI, &primo, &secondo);
        printf("\nPrimo eletto:   %s (voti %d)\n", lista[primo].nome, lista[primo].voti);
        for (i = 0; i < CANDIDATI; i++) {
            if (i != primo && i != secondo && lista[i].voti == lista[secondo].voti) {
                pari_merito++;
            }
        }
        if (pari_merito > 0) {
            printf("Secondo posto: %s e ", lista[secondo].nome);
            if (pari_merito == 1) {
                printf("un altro");
            } else {
                printf("altri %d", pari_merito);
            }
            printf(" a pari voti (%d): serve il ballottaggio\n", lista[secondo].voti);
        } else {
            printf("Secondo eletto: %s (voti %d)\n", lista[secondo].nome, lista[secondo].voti);
        }
    }

    return 0;
}

Candidato *cerca(Candidato c[], int n, int numero)
{
    Candidato *trovato = NULL;
    int i = 0;

    while (i < n && trovato == NULL) {
        if (c[i].numero == numero) {
            trovato = &c[i];
        }
        i++;
    }
    return trovato;
}

/* Indici dei due più votati (a parità vale l'ordine di lista). */
void classifica_primi(const Candidato c[], int n, int *primo, int *secondo)
{
    int i;

    *primo = 0;
    *secondo = 1;
    if (c[1].voti > c[0].voti) {
        *primo = 1;
        *secondo = 0;
    }
    for (i = 2; i < n; i++) {
        if (c[i].voti > c[*primo].voti) {
            *secondo = *primo;
            *primo = i;
        } else if (c[i].voti > c[*secondo].voti) {
            *secondo = i;
        }
    }
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
