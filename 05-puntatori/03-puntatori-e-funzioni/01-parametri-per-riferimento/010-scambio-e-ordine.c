/*
 * 010-scambio-e-ordine.c
 *
 * Funzioni che modificano le variabili del chiamante
 *
 * Una funzione riceve COPIE dei suoi argomenti: assegnare un nuovo valore
 * a un parametro non cambia la variabile del chiamante. Per modificarla
 * la funzione deve riceverne l'INDIRIZZO:
 *
 *     void scambia(int *a, int *b);     dichiarazione
 *     scambia(&x, &y);                  chiamata: si passano gli indirizzi
 *     *a = *b;                          nella funzione si usa *a, *b
 *
 * Una funzione che riceve puntatori può a sua volta passarli ad altre
 * funzioni SENZA &: a e b sono già indirizzi. ordina_tre usa scambia per
 * mettere in ordine crescente tre variabili del chiamante.
 *
 * Esempio: i tempi (in secondi) dei primi tre classificati di una gara di
 * corsa campestre, da mettere in ordine.
 */

#include <stdio.h>

void scambia_copie(int a, int b);
void scambia(int *a, int *b);
void ordina_tre(int *a, int *b, int *c);

int main(void)
{
    int primo = 412;
    int secondo = 398;
    int terzo = 405;

    printf("Tempi iniziali:          %d %d %d\n", primo, secondo, terzo);

    scambia_copie(primo, secondo);
    printf("Dopo scambia_copie:      %d %d %d   (nulla e' cambiato)\n", primo, secondo, terzo);

    scambia(&primo, &secondo);
    printf("Dopo scambia(&p, &s):    %d %d %d\n", primo, secondo, terzo);

    ordina_tre(&primo, &secondo, &terzo);
    printf("Dopo ordina_tre:         %d %d %d\n", primo, secondo, terzo);

    return 0;
}

/* Scambia le copie: il chiamante non vede alcun effetto. */
void scambia_copie(int a, int b)
{
    int temp = a;

    a = b;
    b = temp;
    printf("  dentro scambia_copie:  a = %d, b = %d\n", a, b);
}

/* Scambia le variabili del chiamante di cui riceve gli indirizzi. */
void scambia(int *a, int *b)
{
    int temp = *a;

    *a = *b;
    *b = temp;
}

/* Mette in ordine crescente le tre variabili puntate. a, b e c sono già
 * indirizzi: si passano a scambia così come sono, senza &. */
void ordina_tre(int *a, int *b, int *c)
{
    if (*a > *b) {
        scambia(a, b);
    }
    if (*b > *c) {
        scambia(b, c);
    }
    if (*a > *b) {
        scambia(a, b);
    }
}
