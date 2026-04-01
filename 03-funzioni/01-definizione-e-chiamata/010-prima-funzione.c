/*
 * 010-prima-funzione.c
 *
 * La prima funzione definita dall'utente
 *
 * Questo file mostra come definire una funzione semplice in C:
 * la sintassi di dichiarazione, la struttura del corpo e come
 * richiamare una funzione dal main. La funzione non riceve
 * parametri e non restituisce valori (tipo void).
 */

#include <stdio.h>

/* --- Definizione della funzione ---
 *
 * Una funzione si definisce PRIMA di main (oppure si usa il prototipo,
 * vedi 020-prototipo.c). La struttura è:
 *
 *   tipo_ritorno nome_funzione(parametri) {
 *       istruzioni;
 *   }
 *
 * "void" come tipo di ritorno significa che la funzione non restituisce
 * alcun valore al chiamante. "void" tra le parentesi significa che
 * la funzione non accetta parametri.
 */
void stampa_benvenuto(void)
{
    printf("==============================\n");
    printf("  Benvenuto nel programma C!  \n");
    printf("==============================\n");
}

/* Una seconda funzione, sempre void, che stampa un separatore */
void stampa_separatore(void)
{
    printf("------------------------------\n");
}

/* Una terza funzione che stampa un messaggio di addio */
void stampa_arrivederci(void)
{
    printf("==============================\n");
    printf("  Arrivederci!                \n");
    printf("==============================\n");
}

int main(void)
{
    /* Chiamare una funzione significa scrivere il suo nome seguito
     * da parentesi tonde. Il programma "salta" al corpo della funzione,
     * lo esegue, poi torna alla riga successiva nel main.
     */
    stampa_benvenuto();

    /* Posso chiamare la stessa funzione più volte */
    stampa_separatore();
    printf("Questo testo è nel main.\n");
    stampa_separatore();
    printf("Anche questo testo è nel main.\n");
    stampa_separatore();

    /* Le funzioni rendono il codice più leggibile e riutilizzabile:
     * invece di riscrivere ogni volta le righe di printf, chiamo
     * una sola funzione con un nome significativo.
     */
    stampa_arrivederci();

    return 0;
}
