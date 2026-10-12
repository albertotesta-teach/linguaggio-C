/*
 * 060-problema-scambio-studenti.c
 *
 * Classi parallele: scambio di due studenti tra la 1A e la 1B
 *
 * A inizio anno due studenti chiedono di cambiare sezione l'uno con
 * l'altro. La segreteria deve scambiare le loro schede, ma ogni scheda
 * conserva la sezione nella quale si trova:
 *
 *     typedef struct {
 *         char nome[24];
 *         char sezione[4];
 *         int lingua;              1 = francese, 2 = tedesco
 *     } Scheda;
 *
 *     int scambia_studenti(Scheda *a, Scheda *b);
 *
 * La funzione riceve gli INDIRIZZI delle due schede, quindi può
 * modificarle: scambia i nomi e lascia ogni scheda nella sua sezione. Lo
 * scambio è permesso solo se i due studenti studiano la stessa seconda
 * lingua, perché ogni sezione ha i suoi corsi di lingua: altrimenti la
 * funzione restituisce 0 e non modifica nulla.
 *
 * Una versione che ricevesse le schede per valore scambierebbe due copie:
 * il programma la mostra per confronto.
 */

#include <stdio.h>
#include <string.h>

typedef struct {
    char nome[24];
    char sezione[4];
    int lingua;
} Scheda;

int scambia_studenti(Scheda *a, Scheda *b);
void scambia_copie(Scheda a, Scheda b);
void stampa(const Scheda *s);

int main(void)
{
    Scheda prima = {"Lorenzo Fabbri", "1A", 2};
    Scheda seconda = {"Aurora Neri", "1B", 2};
    Scheda terza = {"Mattia Conte", "1B", 1};

    printf("Prima dello scambio:\n");
    stampa(&prima);
    stampa(&seconda);

    scambia_copie(prima, seconda);
    printf("\nDopo scambia_copie (per valore): nessun cambiamento\n");
    stampa(&prima);
    stampa(&seconda);

    if (scambia_studenti(&prima, &seconda)) {
        printf("\nDopo scambia_studenti(&prima, &seconda):\n");
        stampa(&prima);
        stampa(&seconda);
    }

    if (!scambia_studenti(&prima, &terza)) {
        printf("\nScambio con %s rifiutato: seconda lingua diversa.\n", terza.nome);
    }

    return 0;
}

/* Scambia i nomi; sezioni e lingua restano dove sono. */
int scambia_studenti(Scheda *a, Scheda *b)
{
    char nome[24];
    int possibile = a->lingua == b->lingua;

    if (possibile) {
        strcpy(nome, a->nome);
        strcpy(a->nome, b->nome);
        strcpy(b->nome, nome);
    }
    return possibile;
}

/* SBAGLIATA: lavora su due copie che spariscono alla fine della funzione. */
void scambia_copie(Scheda a, Scheda b)
{
    Scheda temp = a;

    a = b;
    b = temp;
    printf("  (dentro scambia_copie la copia a contiene %s)\n", a.nome);
}

void stampa(const Scheda *s)
{
    printf("  %s: %-16s %s\n", s->sezione, s->nome, s->lingua == 1 ? "francese" : "tedesco");
}
