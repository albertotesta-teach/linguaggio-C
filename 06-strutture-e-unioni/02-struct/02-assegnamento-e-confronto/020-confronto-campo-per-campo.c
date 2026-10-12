/*
 * 020-confronto-campo-per-campo.c
 *
 * Due struct non si confrontano con ==: si confrontano i campi
 *
 * L'assegnamento = funziona tra struct, il confronto no:
 *
 *     if (a == b)          errore di compilazione: invalid operands to binary ==
 *
 * Per sapere se due struct sono uguali si confrontano i campi uno per uno,
 * ciascuno nel modo adatto al suo tipo:
 *   - numeri con ==;
 *   - stringhe con strcmp (a.codice == b.codice confronterebbe gli
 *     indirizzi di due array diversi e sarebbe sempre falso).
 *
 * Spesso non servono tutti i campi: due articoli sono "lo stesso articolo"
 * se hanno lo stesso codice, anche se la quantità è diversa.
 *
 * Esempio: l'inventario del laboratorio di elettronica confrontato con il
 * conteggio fatto a fine anno.
 */

#include <stdio.h>
#include <string.h>

typedef struct {
    char codice[8];
    char descrizione[30];
    int quantita;
} Articolo;

int main(void)
{
    Articolo inventario = {"EL-0042", "Multimetro digitale", 12};
    Articolo conteggio = {"EL-0042", "Multimetro digitale", 11};
    int stesso_articolo;
    int identici;

    /* if (inventario == conteggio)   errore di compilazione */

    stesso_articolo = strcmp(inventario.codice, conteggio.codice) == 0;
    identici = stesso_articolo &&
               strcmp(inventario.descrizione, conteggio.descrizione) == 0 &&
               inventario.quantita == conteggio.quantita;

    printf("Inventario: %s  %-20s %3d\n", inventario.codice, inventario.descrizione, inventario.quantita);
    printf("Conteggio:  %s  %-20s %3d\n\n", conteggio.codice, conteggio.descrizione, conteggio.quantita);

    printf("Stesso articolo (stesso codice): %s\n", stesso_articolo ? "si'" : "no");
    printf("Schede identiche (tutti i campi): %s\n", identici ? "si'" : "no");
    if (stesso_articolo && !identici) {
        printf("Differenza di quantita': %+d\n", conteggio.quantita - inventario.quantita);
    }

    /* l'errore da non fare:
     *     if (inventario.codice == conteggio.codice)
     * confronta gli indirizzi dei due array, che sono sempre diversi: la
     * condizione è sempre falsa anche quando il testo è uguale (gcc e
     * clang lo segnalano con un avviso). */

    return 0;
}
