/*
 * 020-prototipo.c
 *
 * Il prototipo di funzione
 *
 * In C, il compilatore legge il file dall'alto verso il basso.
 * Se una funzione viene chiamata prima di essere definita, il compilatore
 * segnala un errore. Il prototipo risolve questo problema: è una
 * dichiarazione anticipata che informa il compilatore dell'esistenza
 * della funzione, dei suoi parametri e del tipo restituito.
 * La definizione completa può trovarsi più in basso nel file.
 */

#include <stdio.h>

/* --- Prototipi ---
 *
 * Il prototipo ha la stessa firma della funzione, ma il corpo
 * viene sostituito da un punto e virgola.
 *
 *   tipo_ritorno nome_funzione(parametri);
 *
 * I nomi dei parametri nel prototipo sono opzionali, ma aiutano
 * la leggibilità. Queste tre forme sono tutte valide:
 *
 *   void stampa_titolo(void);          ← forma usata qui
 *   void stampa_titolo();              ← equivalente in C (ma non in C++)
 */
void stampa_titolo(void);
void stampa_corpo(void);
void stampa_piede(void);

/* --- main viene PRIMA delle definizioni grazie ai prototipi --- */
int main(void)
{
    /* Posso chiamare le funzioni anche se sono definite dopo main,
     * perché il compilatore conosce già la loro firma grazie ai prototipi.
     */
    stampa_titolo();
    stampa_corpo();
    stampa_piede();

    return 0;
}

/* --- Definizioni (corpo completo delle funzioni) ---
 *
 * Le definizioni si trovano dopo il main. Questa organizzazione
 * è comune nei programmi reali: i prototipi (o gli header .h)
 * in cima, il main subito dopo, le implementazioni in fondo.
 */
void stampa_titolo(void)
{
    printf("+---------------------------+\n");
    printf("|   REPORT SETTIMANALE      |\n");
    printf("+---------------------------+\n");
}

void stampa_corpo(void)
{
    printf("| Lunedi    : attivita A    |\n");
    printf("| Martedi   : attivita B    |\n");
    printf("| Mercoledi : attivita C    |\n");
    printf("| Giovedi   : attivita D    |\n");
    printf("| Venerdi   : attivita E    |\n");
}

void stampa_piede(void)
{
    printf("+---------------------------+\n");
    printf("|   Fine report             |\n");
    printf("+---------------------------+\n");
}
