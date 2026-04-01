/*
 * 030-shadowing.c
 *
 * Shadowing: oscuramento di una variabile globale
 *
 * Quando una variabile locale ha lo stesso nome di una variabile globale,
 * la locale "oscura" (in inglese: shadows) la globale all'interno del
 * proprio scope. Durante l'esecuzione del blocco, il nome si riferisce
 * alla variabile locale; la globale esiste ancora ma non è accessibile
 * tramite quel nome.
 *
 * Lo shadowing è legale in C ma spesso causa bug difficili da trovare:
 * il programmatore pensa di modificare la globale, ma sta modificando
 * solo la locale. È buona pratica evitarlo usando nomi distinti.
 */

#include <stdio.h>

/* Variabile globale */
int contatore = 0;

/* Prototipi */
void incrementa_globale(void);
void funzione_con_shadowing(void);
void dimostra_shadowing_in_blocco(void);

/* Questa funzione modifica correttamente la variabile globale */
void incrementa_globale(void)
{
    contatore = contatore + 1;
    printf("incrementa_globale: contatore (globale) = %d\n", contatore);
}

/* Questa funzione dichiara una variabile locale con lo stesso nome
 * della globale. All'interno della funzione, "contatore" si riferisce
 * alla variabile locale: la globale non viene toccata. */
void funzione_con_shadowing(void)
{
    int contatore = 100;   /* oscura la variabile globale "contatore" */

    /* Qui "contatore" è la variabile locale, non la globale */
    printf("funzione_con_shadowing: contatore (locale)  = %d\n", contatore);

    contatore = contatore + 1;   /* modifica solo la locale */
    printf("funzione_con_shadowing: contatore (locale)  = %d  (dopo +1)\n",
           contatore);

    /* Quando la funzione termina, la locale scompare.
     * La globale è rimasta invariata per tutta la durata della chiamata. */
}

/* Lo shadowing può avvenire anche all'interno di un blocco annidato */
void dimostra_shadowing_in_blocco(void)
{
    printf("prima del blocco: contatore (globale) = %d\n", contatore);

    {
        int contatore = 999;   /* oscura la globale solo in questo blocco */
        printf("dentro il blocco: contatore (locale)  = %d\n", contatore);
    }

    /* Fuori dal blocco, "contatore" torna a riferirsi alla globale */
    printf("dopo il blocco:   contatore (globale) = %d\n", contatore);
}

int main(void)
{
    printf("=== Modifica corretta della globale ===\n\n");
    printf("contatore globale iniziale = %d\n\n", contatore);

    incrementa_globale();
    incrementa_globale();
    printf("contatore globale dopo 2 incrementi = %d\n\n", contatore);

    printf("=== Shadowing: la globale NON viene modificata ===\n\n");
    funzione_con_shadowing();
    printf("contatore globale dopo funzione_con_shadowing = %d\n\n", contatore);
    /* contatore globale è ancora 2: la funzione ha modificato solo la locale */

    printf("=== Shadowing in un blocco annidato ===\n\n");
    dimostra_shadowing_in_blocco();

    return 0;
}
