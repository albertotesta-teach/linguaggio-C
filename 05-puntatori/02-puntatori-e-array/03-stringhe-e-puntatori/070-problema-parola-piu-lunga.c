/*
 * 070-problema-parola-piu-lunga.c
 *
 * Titoli del giornalino scolastico: la parola più lunga
 *
 * La redazione del giornalino vuole controllare che i titoli stiano nelle
 * colonne della pagina: per ogni titolo il programma conta le parole e
 * trova la parola più lunga, che non deve superare LIMITE lettere.
 *
 * La parola più lunga non si copia: basta sapere DOVE inizia e quanto è
 * lunga. La funzione restituisce la posizione di inizio; il main ottiene
 * il puntatore alla parola con titoli[t] + posizione. Per stamparla si
 * usa %.*s, che stampa al massimo il numero di caratteri indicato a
 * partire dall'indirizzo dato:
 *
 *     printf("%.*s", lunghezza, migliore);
 *
 * Una parola è una sequenza di lettere (isalpha); il resto separa.
 */

#include <stdio.h>
#include <ctype.h>

#define TITOLI 4
#define LUNG   80
#define LIMITE 12

int parola_piu_lunga(const char *testo, int *lunghezza);
int conta_parole(const char *testo);

int main(void)
{
    char titoli[TITOLI][LUNG] = {
        "Torneo di pallavolo: vince la 4B",
        "Intervista alla dirigente scolastica",
        "Laboratorio di elettrotecnica aperto al pomeriggio",
        "Gita a Torino, si parte lunedi"
    };
    const char *migliore;
    int lunghezza;
    int t;

    printf("=== CONTROLLO TITOLI (limite %d lettere per parola) ===\n", LIMITE);
    for (t = 0; t < TITOLI; t++) {
        migliore = titoli[t] + parola_piu_lunga(titoli[t], &lunghezza);
        printf("\n  \"%s\"\n", titoli[t]);
        printf("  parole: %d, la piu' lunga: \"%.*s\" (%d lettere, dalla posizione %d)",
               conta_parole(titoli[t]), lunghezza, migliore, lunghezza,
               (int) (migliore - titoli[t]));
        if (lunghezza > LIMITE) {
            printf("  <- troppo lunga per la colonna");
        }
        printf("\n");
    }

    return 0;
}

/* Restituisce la posizione in cui inizia la prima parola più lunga di
 * testo e scrive in *lunghezza il numero delle sue lettere. */
int parola_piu_lunga(const char *testo, int *lunghezza)
{
    const char *p = testo;
    const char *parola;
    const char *migliore = testo;

    *lunghezza = 0;
    while (*p != '\0') {
        if (isalpha((unsigned char) *p)) {
            parola = p;
            while (isalpha((unsigned char) *p)) {
                p++;
            }
            if (p - parola > *lunghezza) {
                *lunghezza = p - parola;
                migliore = parola;
            }
        } else {
            p++;
        }
    }
    return migliore - testo;
}

/* Numero di parole: si conta ogni lettera preceduta da un non-lettera. */
int conta_parole(const char *testo)
{
    const char *p;
    int parole = 0;

    for (p = testo; *p != '\0'; p++) {
        if (isalpha((unsigned char) *p) &&
            (p == testo || !isalpha((unsigned char) *(p - 1)))) {
            parole++;
        }
    }
    return parole;
}
