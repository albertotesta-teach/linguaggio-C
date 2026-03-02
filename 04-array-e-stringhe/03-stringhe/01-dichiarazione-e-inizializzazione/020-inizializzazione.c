/*
 * 02-inizializzazione.c
 *
 * I diversi modi di inizializzare una stringa in C.
 *
 * C offre più sintassi per inizializzare una stringa. Alcune sono
 * equivalenti, altre hanno differenze importanti in termini di memoria
 * e modificabilità. Conoscerle evita errori comuni.
 */

#include <stdio.h>

int main(void) {

    /* MODO 1: inizializzazione carattere per carattere (esplicita).
     * Utile per capire la struttura interna, ma scomoda nella pratica.
     * Il '\0' finale è obbligatorio. */
    char citta1[7] = {'T', 'o', 'r', 'i', 'n', 'o', '\0'};
    printf("Modo 1 - carattere per carattere: %s\n", citta1);

    /* MODO 2: inizializzazione con stringa letterale (la più comune).
     * Il compilatore aggiunge automaticamente '\0' in fondo.
     * La dimensione può essere omessa: il compilatore la calcola da solo. */
    char citta2[] = "Milano";
    printf("Modo 2 - stringa letterale, dimensione automatica: %s\n", citta2);

    /* MODO 3: dimensione esplicita maggiore della stringa.
     * Le celle non usate vengono inizializzate a 0 ('\0').
     * Utile quando si sa che la stringa potrebbe crescere (es. input utente). */
    char citta3[50] = "Roma";
    printf("Modo 3 - array sovradimensionato: %s\n", citta3);
    printf("         (le celle da 4 a 49 contengono \\0)\n");

    /* MODO 4: array dichiarato senza inizializzazione, poi assegnato carattere
     * per carattere. Necessario quando il valore non è noto a compile time. */
    char citta4[10];
    citta4[0] = 'G';
    citta4[1] = 'e';
    citta4[2] = 'n';
    citta4[3] = 'o';
    citta4[4] = 'v';
    citta4[5] = 'a';
    citta4[6] = '\0'; /* OBBLIGATORIO: senza questo, il comportamento è indefinito */
    printf("Modo 4 - assegnazione manuale: %s\n", citta4);

    /* ATTENZIONE: array non inizializzato senza '\0' finale.
     * Il codice seguente è commentato perché causa comportamento indefinito:
     * printf stamperebbe caratteri casuali fino al primo '\0' trovato in memoria.
     *
     * char errata[5];
     * errata[0] = 'X';
     * printf("%s\n", errata);  <-- ERRORE: nessun terminatore!
     */

    return 0;
}
