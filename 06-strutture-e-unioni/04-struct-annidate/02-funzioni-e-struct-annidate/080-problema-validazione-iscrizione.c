/*
 * 080-problema-validazione-iscrizione.c
 *
 * Iscrizioni al primo anno: una funzione per ogni parte della scheda
 *
 * La segreteria inserisce le iscrizioni al primo anno. La scheda ha tre
 * parti: il nome, la data di nascita e l'indirizzo.
 *
 *     typedef struct {
 *         char nome[24];
 *         Data nascita;
 *         Indirizzo residenza;
 *     } Iscrizione;
 *
 * leggi_iscrizione riempie la struct del chiamante e delega ogni parte a
 * una funzione che riceve solo l'indirizzo di quella parte:
 *
 *     int leggi_iscrizione(Iscrizione *s);
 *         leggi_testo(..., s->nome, ...)
 *         leggi_data(&s->nascita)
 *         leggi_indirizzo(&s->residenza)
 *
 * Restituisce 0 se la scheda è completa e corretta, altrimenti il numero
 * della parte sbagliata (1 nome, 2 data, 3 indirizzo): il main usa il
 * numero come indice di una tabella di messaggi. La lettura si ferma alla
 * prima parte sbagliata e la scheda si ricomincia; si hanno 3 tentativi.
 *
 * Controlli:
 *   - nome non vuoto e che stia nel campo;
 *   - data esistente, con anno di nascita dal 2011 al 2013;
 *   - via e comune non vuoti, CAP di 5 cifre.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define LUNG 40
#define TENTATIVI 3
#define ANNO_MINIMO 2011
#define ANNO_MASSIMO 2013

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
    char nome[24];
    Data nascita;
    Indirizzo residenza;
} Iscrizione;

int leggi_testo(const char *domanda, char dest[], int dimensione);
int leggi_data(Data *d);
int leggi_indirizzo(Indirizzo *i);
int leggi_iscrizione(Iscrizione *s);
void stampa(const Iscrizione *s);
void scarta_resto(const char riga[]);

int main(void)
{
    const char *parti[4] = {"", "nome", "data di nascita", "indirizzo"};
    Iscrizione nuova;
    int tentativo = 1;
    int esito = -1;

    while (esito != 0 && tentativo <= TENTATIVI) {
        printf("--- Tentativo %d ---\n", tentativo);
        esito = leggi_iscrizione(&nuova);
        if (esito != 0) {
            printf("  Errore nella parte: %s.\n", parti[esito]);
        }
        tentativo++;
    }

    if (esito == 0) {
        printf("\nIscrizione registrata:\n");
        stampa(&nuova);
    } else {
        printf("\nIscrizione non registrata.\n");
    }

    return 0;
}

/* Legge una riga non vuota che stia in dest; 1 se riuscito. */
int leggi_testo(const char *domanda, char dest[], int dimensione)
{
    char riga[LUNG];
    int riuscito = 0;

    printf("%s: ", domanda);
    if (fgets(riga, LUNG, stdin) != NULL) {
        scarta_resto(riga);
        riga[strcspn(riga, "\n")] = '\0';
        if (riga[0] != '\0' && (int) strlen(riga) < dimensione) {
            strcpy(dest, riga);
            riuscito = 1;
        }
    }
    return riuscito;
}

int leggi_data(Data *d)
{
    int giorni[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    char riga[LUNG];
    int valida = 0;

    printf("Data di nascita (gg/mm/aaaa): ");
    if (fgets(riga, LUNG, stdin) == NULL) {
        riga[0] = '\0';                 /* input terminato: data non valida */
    } else {
        scarta_resto(riga);
    }
    if (sscanf(riga, "%d/%d/%d", &d->giorno, &d->mese, &d->anno) == 3 &&
        d->anno >= ANNO_MINIMO && d->anno <= ANNO_MASSIMO && d->mese >= 1 && d->mese <= 12) {
        if (d->anno % 4 == 0) {
            giorni[1] = 29;
        }
        valida = d->giorno >= 1 && d->giorno <= giorni[d->mese - 1];
    }
    return valida;
}

/* Legge le tre righe dell'indirizzo, poi le controlla. */
int leggi_indirizzo(Indirizzo *i)
{
    int via_ok = leggi_testo("Via", i->via, sizeof(i->via));
    int cap_ok = leggi_testo("CAP", i->cap, sizeof(i->cap));
    int comune_ok = leggi_testo("Comune", i->comune, sizeof(i->comune));
    int k;

    cap_ok = cap_ok && strlen(i->cap) == 5;
    for (k = 0; k < 5 && cap_ok; k++) {
        cap_ok = isdigit((unsigned char) i->cap[k]);
    }
    return via_ok && cap_ok && comune_ok;
}

int leggi_iscrizione(Iscrizione *s)
{
    int esito = 0;

    if (!leggi_testo("Nome e cognome", s->nome, sizeof(s->nome))) {
        esito = 1;
    } else if (!leggi_data(&s->nascita)) {
        esito = 2;
    } else if (!leggi_indirizzo(&s->residenza)) {
        esito = 3;
    }
    return esito;
}

void stampa(const Iscrizione *s)
{
    printf("  %s, nato/a il %02d/%02d/%d\n", s->nome, s->nascita.giorno, s->nascita.mese,
           s->nascita.anno);
    printf("  %s, %s %s\n", s->residenza.via, s->residenza.cap, s->residenza.comune);
}

/* Se la riga letta con fgets non contiene l'a capo era troppo lunga:
 * scarta il resto, che altrimenti sarebbe letto come risposta successiva. */
void scarta_resto(const char riga[])
{
    int c;

    if (strchr(riga, '\n') == NULL) {
        c = getchar();
        while (c != '\n' && c != EOF) {
            c = getchar();
        }
    }
}
