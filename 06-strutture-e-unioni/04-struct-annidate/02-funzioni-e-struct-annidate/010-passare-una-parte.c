/*
 * 010-passare-una-parte.c
 *
 * Passare a una funzione solo la parte che le serve
 *
 * Una funzione che lavora sulle date riceve una Data, non uno Studente:
 *
 *     int eta(Data nascita, Data oggi);
 *     void stampa_data(Data d);
 *
 *     eta(s.nascita, gita);           s.nascita è una Data
 *     stampa_data(s.nascita);
 *     stampa_data(gita);
 *
 * La stessa funzione serve per qualunque Data, qualunque sia la struct
 * che la contiene: la data di nascita di uno studente, la data della
 * gita, la scadenza di un prestito. Se la funzione ricevesse lo Studente
 * intero, si potrebbe usare solo con gli studenti.
 *
 * La parte si passa per valore come ogni struct: la funzione riceve una
 * copia di s.nascita (12 byte), non dello studente intero.
 *
 * Esempio: per la gita di aprile servono l'autorizzazione dei genitori
 * per chi non ha ancora 18 anni il giorno della partenza.
 */

#include <stdio.h>

#define STUDENTI 4
#define MAGGIORE_ETA 18

typedef struct {
    int giorno;
    int mese;
    int anno;
} Data;

typedef struct {
    char nome[20];
    Data nascita;
} Studente;

int eta(Data nascita, Data oggi);
void stampa_data(Data d);

int main(void)
{
    Studente classe[STUDENTI] = {
        {"Bruni Chiara", {14, 4, 2008}},
        {"Conte Mattia", {20, 4, 2008}},
        {"Fabbri Ivo", {2, 1, 2008}},
        {"Galli Nora", {30, 9, 2008}}
    };
    Data gita = {18, 4, 2026};
    int anni;
    int autorizzazioni = 0;
    int i;

    printf("Gita del ");
    stampa_data(gita);
    printf("\n");
    for (i = 0; i < STUDENTI; i++) {
        anni = eta(classe[i].nascita, gita);
        printf("  %-13s nato/a il ", classe[i].nome);
        stampa_data(classe[i].nascita);
        printf("  %d anni", anni);
        if (anni < MAGGIORE_ETA) {
            printf("  serve l'autorizzazione");
            autorizzazioni++;
        }
        printf("\n");
    }
    printf("Autorizzazioni da raccogliere: %d\n", autorizzazioni);

    return 0;
}

/* Anni compiuti alla data oggi. */
int eta(Data nascita, Data oggi)
{
    int anni = oggi.anno - nascita.anno;

    if (oggi.mese < nascita.mese || (oggi.mese == nascita.mese && oggi.giorno < nascita.giorno)) {
        anni--;
    }
    return anni;
}

void stampa_data(Data d)
{
    printf("%02d/%02d/%d", d.giorno, d.mese, d.anno);
}
