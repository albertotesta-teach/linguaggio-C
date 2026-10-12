/*
 * 010-operatore-freccia.c
 *
 * Puntatore a struct e operatore ->
 *
 * Un puntatore può contenere l'indirizzo di una struct:
 *
 *     Studente s = {...};
 *     Studente *p = &s;
 *
 * Per raggiungere un campo attraverso il puntatore ci sono due scritture
 * equivalenti:
 *
 *     (*p).media        prima *p (la struct), poi .media
 *     p->media          la stessa cosa, più leggibile
 *
 * Le parentesi in (*p).media sono necessarie: il punto ha la precedenza
 * sull'asterisco, quindi *p.media significherebbe *(p.media), un errore
 * (p non è una struct, è un indirizzo).
 *
 * L'operatore -> si usa SOLO con i puntatori; con una variabile struct si
 * usa il punto: s.media, p->media.
 *
 * Esempio: il rappresentante di classe scelto tra due studenti; un
 * puntatore indica quello eletto.
 */

#include <stdio.h>

typedef struct {
    char nome[20];
    char classe[4];
    double media;
} Studente;

int main(void)
{
    Studente giulia = {"Giulia Ferri", "3B", 7.8};
    Studente marco = {"Marco Riva", "3B", 6.9};
    Studente *eletto = &giulia;

    printf("=== TRE SCRITTURE DELLO STESSO CAMPO ===\n");
    printf("  giulia.media     = %.1f\n", giulia.media);
    printf("  (*eletto).media  = %.1f\n", (*eletto).media);
    printf("  eletto->media    = %.1f\n", eletto->media);
    /* *eletto.media      errore: equivale a *(eletto.media) */

    printf("\nIndirizzo di giulia: %p, valore di eletto: %p\n", (void *) &giulia, (void *) eletto);

    /* scrivere tramite il puntatore modifica la variabile puntata */
    eletto->media = eletto->media + 0.2;
    printf("Dopo eletto->media += 0.2: giulia.media = %.1f\n", giulia.media);

    /* il puntatore può indicare un'altra struct */
    eletto = &marco;
    printf("\nOra il rappresentante e' %s (%s), media %.1f\n", eletto->nome, eletto->classe, eletto->media);
    printf("Iniziale: %c\n", eletto->nome[0]);

    return 0;
}
