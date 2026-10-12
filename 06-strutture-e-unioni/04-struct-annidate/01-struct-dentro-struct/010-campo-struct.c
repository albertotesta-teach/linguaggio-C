/*
 * 010-campo-struct.c
 *
 * Un campo che è a sua volta una struct
 *
 * Un tipo già definito, come Data, si può usare per un campo di un altro
 * tipo. Lo studente ha una data di nascita, non tre interi sparsi:
 *
 *     typedef struct {
 *         int giorno;
 *         int mese;
 *         int anno;
 *     } Data;
 *
 *     typedef struct {
 *         char nome[20];
 *         char classe[4];
 *         Data nascita;
 *     } Studente;
 *
 * Per arrivare a un campo interno si usano più punti, da sinistra a
 * destra: s.nascita è la Data dello studente, s.nascita.anno è l'anno.
 *
 * Il tipo interno va definito PRIMA del tipo che lo usa. La struct
 * interna occupa memoria dentro quella esterna: sizeof(Studente)
 * comprende sizeof(Data).
 *
 * Esempio: due studenti della 2A e chi dei due è il più giovane.
 */

#include <stdio.h>
#include <string.h>

typedef struct {
    int giorno;
    int mese;
    int anno;
} Data;

typedef struct {
    char nome[20];
    char classe[4];
    Data nascita;
} Studente;

int main(void)
{
    Studente elena;
    Studente paolo;
    int elena_piu_giovane;

    strcpy(elena.nome, "Rossi Elena");
    strcpy(elena.classe, "2A");
    elena.nascita.giorno = 12;
    elena.nascita.mese = 3;
    elena.nascita.anno = 2010;

    strcpy(paolo.nome, "Greco Paolo");
    strcpy(paolo.classe, "2A");
    paolo.nascita.giorno = 30;
    paolo.nascita.mese = 11;
    paolo.nascita.anno = 2009;

    printf("%-12s %s  nascita %02d/%02d/%d\n", elena.nome, elena.classe, elena.nascita.giorno,
           elena.nascita.mese, elena.nascita.anno);
    printf("%-12s %s  nascita %02d/%02d/%d\n", paolo.nome, paolo.classe, paolo.nascita.giorno,
           paolo.nascita.mese, paolo.nascita.anno);

    /* Si confronta l'anno, a parità il mese, a parità il giorno. */
    elena_piu_giovane = elena.nascita.anno > paolo.nascita.anno ||
                        (elena.nascita.anno == paolo.nascita.anno &&
                         (elena.nascita.mese > paolo.nascita.mese ||
                          (elena.nascita.mese == paolo.nascita.mese &&
                           elena.nascita.giorno > paolo.nascita.giorno)));
    printf("Il piu' giovane: %s\n", elena_piu_giovane ? elena.nome : paolo.nome);

    printf("\nsizeof(Data)         = %zu byte\n", sizeof(Data));
    printf("sizeof(elena.nascita) = %zu byte\n", sizeof(elena.nascita));
    printf("sizeof(Studente)     = %zu byte (20 + 4 + %zu)\n", sizeof(Studente), sizeof(Data));

    /* elena.anno = 2010;        errore: anno è un campo di Data       */
    /* nascita.anno = 2010;      errore: nascita non è una variabile   */

    return 0;
}
