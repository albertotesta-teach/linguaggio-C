/*
 * 020-ricerca-e-massimo.c
 *
 * Cercare in un array di struct: per campo, il massimo, i conteggi
 *
 * Gli algoritmi visti con gli array (ricerca, massimo, conteggio) si
 * applicano a un array di struct scegliendo il CAMPO su cui lavorare:
 *
 *   - ricerca per titolo:  strcmp(libri[i].titolo, cercato) == 0
 *   - massimo:             libri[i].prestiti > libri[migliore].prestiti
 *   - conteggio:           libri[i].copie > libri[i].in_prestito
 *
 * Il risultato di una ricerca è l'INDICE dell'elemento trovato (o -1):
 * con l'indice si raggiungono tutti gli altri campi dello stesso libro.
 *
 * Esempio: i libri della biblioteca di classe, con il numero di prestiti
 * dell'anno.
 */

#include <stdio.h>
#include <string.h>

#define LIBRI 6

typedef struct {
    char titolo[32];
    char autore[24];
    int copie;
    int in_prestito;
    int prestiti;
} Libro;

int main(void)
{
    Libro libri[LIBRI] = {
        {"Il barone rampante", "Italo Calvino", 2, 1, 14},
        {"La coscienza di Zeno", "Italo Svevo", 1, 0, 6},
        {"Fahrenheit 451", "Ray Bradbury", 3, 3, 21},
        {"Il giorno della civetta", "Leonardo Sciascia", 2, 0, 9},
        {"Lessico famigliare", "Natalia Ginzburg", 1, 1, 11},
        {"Se questo e' un uomo", "Primo Levi", 4, 2, 18}
    };
    const char *cercato = "Fahrenheit 451";
    int i;
    int trovato = -1;
    int piu_letto = 0;
    int disponibili = 0;

    /* ricerca per titolo: si ferma al primo trovato */
    i = 0;
    while (i < LIBRI && trovato == -1) {
        if (strcmp(libri[i].titolo, cercato) == 0) {
            trovato = i;
        }
        i++;
    }
    if (trovato == -1) {
        printf("\"%s\" non e' in biblioteca.\n", cercato);
    } else {
        printf("\"%s\" di %s: %d copie, %d in prestito\n", libri[trovato].titolo,
               libri[trovato].autore, libri[trovato].copie, libri[trovato].in_prestito);
    }

    /* massimo e conteggio in un solo ciclo */
    for (i = 0; i < LIBRI; i++) {
        if (libri[i].prestiti > libri[piu_letto].prestiti) {
            piu_letto = i;
        }
        if (libri[i].copie > libri[i].in_prestito) {
            disponibili++;
        }
    }
    printf("Libro piu' prestato: \"%s\" (%d prestiti)\n", libri[piu_letto].titolo,
           libri[piu_letto].prestiti);
    printf("Titoli con almeno una copia disponibile: %d su %d\n", disponibili, LIBRI);

    return 0;
}
