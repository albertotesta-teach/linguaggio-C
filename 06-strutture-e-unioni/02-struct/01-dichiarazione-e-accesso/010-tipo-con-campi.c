/*
 * 010-tipo-con-campi.c
 *
 * struct: un nuovo tipo fatto di campi
 *
 * Una struct raggruppa in un'unica variabile dati di tipo diverso che
 * descrivono la stessa cosa. Per uno studente: il nome (una stringa), la
 * classe (una stringa corta) e la media (un double).
 *
 *     struct studente {               dichiarazione del tipo
 *         char nome[20];              campi (membri)
 *         char classe[4];
 *         double media;
 *     };                              punto e virgola obbligatorio
 *
 *     struct studente s;              una variabile del nuovo tipo
 *     s.media = 7.5;                  operatore punto: accesso a un campo
 *
 * Il nome del tipo è "struct studente" (due parole). Ogni variabile ha i
 * propri campi: s1.media e s2.media sono due double distinti. Un campo si
 * usa come una variabile del suo tipo: s.nome è un array di char, quindi
 * si riempie con strcpy e si stampa con %s.
 *
 * Esempio: due studenti della 3B e la loro media del primo quadrimestre.
 */

#include <stdio.h>
#include <string.h>

/* La dichiarazione del tipo non crea variabili: descrive come sono
 * fatte le variabili di tipo struct studente. */
struct studente {
    char nome[20];
    char classe[4];
    double media;
};

int main(void)
{
    struct studente primo;
    struct studente secondo;

    strcpy(primo.nome, "Giulia Ferri");
    strcpy(primo.classe, "3B");
    primo.media = 7.8;

    strcpy(secondo.nome, "Marco Riva");
    strcpy(secondo.classe, "3B");
    secondo.media = 6.4;

    printf("=== I CAMPI ===\n");
    printf("  %-14s classe %s  media %.1f\n", primo.nome, primo.classe, primo.media);
    printf("  %-14s classe %s  media %.1f\n", secondo.nome, secondo.classe, secondo.media);

    /* un campo si usa come una variabile del suo tipo */
    secondo.media = secondo.media + 0.5;
    printf("\nDopo il recupero: %s ha media %.1f\n", secondo.nome, secondo.media);
    printf("Iniziale del nome di %s: %c\n", primo.nome, primo.nome[0]);

    printf("\n=== DIMENSIONI ===\n");
    printf("  sizeof(primo.nome)   = %zu\n", sizeof(primo.nome));
    printf("  sizeof(primo.classe) = %zu\n", sizeof(primo.classe));
    printf("  sizeof(primo.media)  = %zu\n", sizeof(primo.media));
    printf("  sizeof(struct studente) = %zu  (somma dei campi piu' eventuale spazio di allineamento)\n",
           sizeof(struct studente));

    return 0;
}
