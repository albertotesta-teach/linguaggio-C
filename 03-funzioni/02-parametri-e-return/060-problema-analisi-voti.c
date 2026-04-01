/*
 * 060-problema-analisi-voti.c
 *
 * Analisi dei voti di uno studente
 *
 * Un registro scolastico raccoglie i voti di uno studente in cinque
 * materie. Il programma calcola la media, determina se lo studente è
 * promosso, e classifica il risultato complessivo. Ogni operazione
 * è implementata in una funzione separata che riceve i dati come
 * parametri e restituisce il risultato elaborato.
 *
 * Nota: in questo capitolo non usiamo ancora gli array. I cinque voti
 * vengono passati esplicitamente come parametri separati.
 */

#include <stdio.h>

/* Voto minimo per la promozione */
#define VOTO_MINIMO_SUFFICIENZA  6

/* Prototipi */
double calcola_media(int v1, int v2, int v3, int v4, int v5);
int determina_promosso(int v1, int v2, int v3, int v4, int v5);
int voto_minimo(int v1, int v2, int v3, int v4, int v5);
int voto_massimo(int v1, int v2, int v3, int v4, int v5);
void stampa_giudizio(double media);
void stampa_scheda(int v1, int v2, int v3, int v4, int v5);

/* --- Funzioni di calcolo --- */

/* La media viene calcolata come somma divisa per il numero di materie.
 * La divisione deve essere tra double per non perdere le cifre decimali. */
double calcola_media(int v1, int v2, int v3, int v4, int v5)
{
    double media;
    media = (v1 + v2 + v3 + v4 + v5) / 5.0;
    return media;
}

/* Lo studente è promosso se TUTTI i voti sono sufficienti (>= 6).
 * Restituisce 1 se promosso, 0 altrimenti. */
int determina_promosso(int v1, int v2, int v3, int v4, int v5)
{
    int promosso;
    promosso = (v1 >= VOTO_MINIMO_SUFFICIENZA &&
                v2 >= VOTO_MINIMO_SUFFICIENZA &&
                v3 >= VOTO_MINIMO_SUFFICIENZA &&
                v4 >= VOTO_MINIMO_SUFFICIENZA &&
                v5 >= VOTO_MINIMO_SUFFICIENZA);
    return promosso;
}

/* Trova il voto più basso tra i cinque */
int voto_minimo(int v1, int v2, int v3, int v4, int v5)
{
    int min;
    min = v1;
    if (v2 < min) { min = v2; }
    if (v3 < min) { min = v3; }
    if (v4 < min) { min = v4; }
    if (v5 < min) { min = v5; }
    return min;
}

/* Trova il voto più alto tra i cinque */
int voto_massimo(int v1, int v2, int v3, int v4, int v5)
{
    int max;
    max = v1;
    if (v2 > max) { max = v2; }
    if (v3 > max) { max = v3; }
    if (v4 > max) { max = v4; }
    if (v5 > max) { max = v5; }
    return max;
}

/* Stampa il giudizio testuale basato sulla media */
void stampa_giudizio(double media)
{
    printf("Giudizio: ");
    if (media >= 9.0) {
        printf("Eccellente\n");
    } else if (media >= 8.0) {
        printf("Ottimo\n");
    } else if (media >= 7.0) {
        printf("Buono\n");
    } else if (media >= 6.0) {
        printf("Sufficiente\n");
    } else {
        printf("Insufficiente\n");
    }
}

/* Funzione di orchestrazione: stampa la scheda completa */
void stampa_scheda(int v1, int v2, int v3, int v4, int v5)
{
    double media;
    int promosso;

    printf("-------------------------------\n");
    printf("SCHEDA DELLO STUDENTE\n");
    printf("-------------------------------\n");
    printf("Matematica:      %d\n", v1);
    printf("Italiano:        %d\n", v2);
    printf("Inglese:         %d\n", v3);
    printf("Informatica:     %d\n", v4);
    printf("Fisica:          %d\n", v5);
    printf("-------------------------------\n");

    media = calcola_media(v1, v2, v3, v4, v5);
    printf("Media:           %.2f\n", media);
    printf("Voto minimo:     %d\n", voto_minimo(v1, v2, v3, v4, v5));
    printf("Voto massimo:    %d\n", voto_massimo(v1, v2, v3, v4, v5));

    stampa_giudizio(media);

    promosso = determina_promosso(v1, v2, v3, v4, v5);
    if (promosso) {
        printf("Esito:           PROMOSSO\n");
    } else {
        printf("Esito:           NON PROMOSSO\n");
    }
    printf("-------------------------------\n");
}

int main(void)
{
    int mat, ita, ing, inf, fis;

    printf("Inserire i voti (da 1 a 10) per le cinque materie:\n");
    printf("Matematica:  "); scanf("%d", &mat);
    printf("Italiano:    "); scanf("%d", &ita);
    printf("Inglese:     "); scanf("%d", &ing);
    printf("Informatica: "); scanf("%d", &inf);
    printf("Fisica:      "); scanf("%d", &fis);

    printf("\n");
    stampa_scheda(mat, ita, ing, inf, fis);

    return 0;
}
