/*
 * 010-costanti-con-nome.c
 *
 * enum: un tipo con un elenco di costanti con nome
 *
 * Un enum elenca i valori possibili di un tipo, dando a ognuno un nome:
 *
 *     typedef enum {
 *         LUNEDI, MARTEDI, MERCOLEDI, GIOVEDI, VENERDI, SABATO, DOMENICA
 *     } Giorno;
 *
 *     Giorno oggi = VENERDI;
 *
 * Le costanti sono numeri interi: la prima vale 0 e ognuna vale uno in
 * più della precedente (LUNEDI 0, MARTEDI 1, ..., DOMENICA 6). Si
 * stampano con %d e si confrontano come gli int.
 *
 * Rispetto a una serie di #define:
 *   - le costanti sono raccolte in un tipo con un nome (Giorno), e il
 *     prototipo di una funzione dice quali valori si aspetta;
 *   - i valori sono assegnati dal compilatore, senza errori di battitura;
 *   - il debugger mostra VENERDI invece di 4.
 * In C però un enum non è un controllo: oggi = 42 compila lo stesso.
 *
 * Convenzione del corso: il tipo ha l'iniziale maiuscola come le struct,
 * le costanti sono tutte maiuscole.
 *
 * Esempio: i giorni della settimana e il fine settimana.
 */

#include <stdio.h>

typedef enum {
    LUNEDI, MARTEDI, MERCOLEDI, GIOVEDI, VENERDI, SABATO, DOMENICA
} Giorno;

int main(void)
{
    Giorno oggi = VENERDI;
    Giorno domani;
    int g;

    printf("LUNEDI = %d, MERCOLEDI = %d, DOMENICA = %d\n", LUNEDI, MERCOLEDI, DOMENICA);
    printf("oggi vale %d\n", oggi);

    for (g = LUNEDI; g <= DOMENICA; g++) {
        printf("  giorno %d: %s\n", g, (g == SABATO || g == DOMENICA) ? "fine settimana" : "lezione");
    }

    domani = (oggi + 1) % 7;
    printf("Domani vale %d: %s\n", domani,
           domani == SABATO || domani == DOMENICA ? "niente scuola" : "si va a scuola");

    printf("sizeof(Giorno) = %zu byte, come un int\n", sizeof(Giorno));

    return 0;
}
