/*
 * 030-puntatore-che-avanza.c
 *
 * Una funzione che legge da una stringa e fa avanzare il puntatore
 *
 * Per leggere più valori da una stringa uno dopo l'altro, una funzione può
 * ricevere l'indirizzo del puntatore di lettura (const char **) e, dopo
 * aver letto un numero, spostarlo oltre il numero stesso. Alla chiamata
 * successiva la lettura riparte da lì:
 *
 *     const char *p = testo;
 *     while (leggi_numero(&p, &n)) {
 *         ... usa n ...                p è già dopo il numero letto
 *     }
 *
 * Dentro la funzione:
 *     *p        il puntatore del chiamante (dove si trova la lettura)
 *     **p       il carattere da leggere
 *     (*p)++    sposta in avanti il puntatore del chiamante
 *
 * Le parentesi in (*p)++ sono necessarie: *p++ sposterebbe la copia
 * locale p, non il puntatore del chiamante.
 *
 * Esempio: i punteggi delle squadre di un quiz, scritti in una riga.
 */

#include <stdio.h>

int leggi_numero(const char **p, int *numero);

int main(void)
{
    const char *punteggi = "  12 7  130 45 9";
    const char *lettura = punteggi;
    int n;
    int squadra = 1;
    int totale = 0;

    printf("Riga: \"%s\"\n\n", punteggi);
    while (leggi_numero(&lettura, &n)) {
        printf("  squadra %d: %3d punti   (lettura ora in posizione %2d: \"%s\")\n",
               squadra, n, (int) (lettura - punteggi), lettura);
        totale = totale + n;
        squadra++;
    }
    printf("\nTotale: %d punti\n", totale);

    return 0;
}

/* Salta gli spazi, legge le cifre di un numero e sposta *p dopo l'ultima
 * cifra. Restituisce 1 se ha letto un numero, 0 se non ci sono più cifre. */
int leggi_numero(const char **p, int *numero)
{
    int letto = 0;

    while (**p == ' ') {
        (*p)++;
    }
    *numero = 0;
    while (**p >= '0' && **p <= '9') {
        *numero = *numero * 10 + (**p - '0');
        (*p)++;
        letto = 1;
    }
    return letto;
}
