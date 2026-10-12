/*
 * 030-funzioni-a-livelli.c
 *
 * Una funzione per ogni tipo: le funzioni si chiamano a cascata
 *
 * Ogni tipo ha le sue funzioni, e la funzione del tipo esterno chiama
 * quelle dei tipi interni:
 *
 *     stampa_studente(const Studente *s)
 *         -> stampa_data(&s->nascita)
 *         -> stampa_indirizzo(&s->residenza)
 *
 *     studente_valido(const Studente *s)
 *         -> data_valida(&s->nascita)
 *         -> indirizzo_valido(&s->residenza)
 *
 * Così ogni funzione è corta e si occupa di un solo livello. Se cambia il
 * modo di scrivere le date (per esempio "12 mar 2010" invece di
 * 12/03/2010) si modifica solo stampa_data, e tutte le funzioni che la
 * usano si adeguano.
 *
 * Esempio: le schede di due nuovi iscritti, una corretta e una con la
 * data e il CAP sbagliati.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int giorno;
    int mese;
    int anno;
} Data;

typedef struct {
    char via[28];
    char cap[6];
    char comune[16];
} Indirizzo;

typedef struct {
    char nome[20];
    Data nascita;
    Indirizzo residenza;
} Studente;

void stampa_data(const Data *d);
void stampa_indirizzo(const Indirizzo *i);
void stampa_studente(const Studente *s);
int data_valida(const Data *d);
int indirizzo_valido(const Indirizzo *i);
int studente_valido(const Studente *s);

int main(void)
{
    Studente iscritti[2] = {
        {"Rossi Elena", {12, 3, 2010}, {"via Marengo 12", "15121", "Alessandria"}},
        {"Greco Paolo", {31, 4, 2010}, {"corso Italia 4", "150A7", "Novi Ligure"}}
    };
    int i;

    for (i = 0; i < 2; i++) {
        stampa_studente(&iscritti[i]);
        printf("  scheda %s\n", studente_valido(&iscritti[i]) ? "corretta" : "da correggere");
    }

    return 0;
}

void stampa_data(const Data *d)
{
    const char *mesi[12] = {"gen", "feb", "mar", "apr", "mag", "giu",
                            "lug", "ago", "set", "ott", "nov", "dic"};

    if (d->mese >= 1 && d->mese <= 12) {
        printf("%d %s %d", d->giorno, mesi[d->mese - 1], d->anno);
    } else {
        printf("%d/%d/%d", d->giorno, d->mese, d->anno);
    }
}

void stampa_indirizzo(const Indirizzo *i)
{
    printf("%s, %s %s", i->via, i->cap, i->comune);
}

void stampa_studente(const Studente *s)
{
    printf("%s, nato/a il ", s->nome);
    stampa_data(&s->nascita);
    printf("\n  residente in ");
    stampa_indirizzo(&s->residenza);
    printf("\n");
}

/* Mesi di 30 o 31 giorni, febbraio fino a 29: basta per una scheda. */
int data_valida(const Data *d)
{
    int giorni[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int valida = d->mese >= 1 && d->mese <= 12 && d->anno >= 1990 && d->anno <= 2020;

    if (valida) {
        valida = d->giorno >= 1 && d->giorno <= giorni[d->mese - 1];
    }
    if (!valida) {
        printf("  data di nascita non valida\n");
    }
    return valida;
}

/* Il CAP ha 5 cifre; via e comune non sono vuoti. */
int indirizzo_valido(const Indirizzo *i)
{
    int valido = strlen(i->cap) == 5 && i->via[0] != '\0' && i->comune[0] != '\0';
    int k;

    for (k = 0; k < 5 && valido; k++) {
        valido = isdigit((unsigned char) i->cap[k]);
    }
    if (!valido) {
        printf("  indirizzo non valido\n");
    }
    return valido;
}

/* Controlla tutte le parti, anche se la prima è già sbagliata. */
int studente_valido(const Studente *s)
{
    int nome_ok = s->nome[0] != '\0';
    int data_ok = data_valida(&s->nascita);
    int indirizzo_ok = indirizzo_valido(&s->residenza);

    return nome_ok && data_ok && indirizzo_ok;
}
