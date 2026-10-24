/*
 * 040-problema-rinnovo-abbonamenti.c
 *
 * Abbonamenti studenti al bus: rinnovi e avvisi di scadenza
 *
 * La segreteria gestisce gli abbonamenti al bus degli studenti. Ogni
 * abbonamento ha numero, intestatario, linea e data di scadenza:
 *
 *     typedef struct {
 *         char numero[8];
 *         char intestatario[20];
 *         char linea[4];
 *         Data scadenza;
 *     } Abbonamento;
 *
 * Le funzioni sulle date ricevono l'indirizzo di una Data, che può essere
 * la data di oggi o la scadenza dentro un abbonamento:
 *
 *     int giorni_tra(const Data *da, const Data *a);
 *     void aggiungi_mesi(Data *d, int mesi);
 *     int rinnova(Abbonamento *ab, int mesi, const Data *oggi);
 *
 * rinnova chiama aggiungi_mesi(&ab->scadenza, mesi): se l'abbonamento è
 * ancora valido si allunga dalla vecchia scadenza, se è scaduto riparte
 * da oggi. Se il giorno non esiste nel nuovo mese (31 gennaio + 1 mese)
 * si usa l'ultimo giorno del mese.
 *
 * Il programma legge la data di oggi e poi i comandi:
 *     R numero mesi    rinnovo da 1 a 12 mesi
 *     A                avvisi: scaduti e in scadenza entro 15 giorni
 *     S                stato di tutti gli abbonamenti
 *     Q                fine
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ABBONAMENTI 4
#define PREAVVISO 15

typedef struct {
    int giorno;
    int mese;
    int anno;
} Data;

typedef struct {
    char numero[8];
    char intestatario[20];
    char linea[4];
    Data scadenza;
} Abbonamento;

int bisestile(int anno);
int giorni_nel_mese(int mese, int anno);
int numero_giorno(const Data *d);
int giorni_tra(const Data *da, const Data *a);
void aggiungi_mesi(Data *d, int mesi);
int rinnova(Abbonamento *ab, int mesi, const Data *oggi);
void stampa(const Abbonamento *ab, const Data *oggi);
void svuota_riga(void);

int main(void)
{
    Abbonamento elenco[ABBONAMENTI] = {
        {"A-1001", "Rossi Elena", "L3", {31, 1, 2026}},
        {"A-1002", "Greco Paolo", "L7", {15, 1, 2026}},
        {"A-1003", "Costa Marta", "L3", {30, 6, 2026}},
        {"A-1004", "Villa Sara", "L1", {2, 2, 2026}}
    };
    Data oggi;
    char comando = ' ';
    char numero[8];
    int mesi;
    int trovato;
    int giorni;
    int i;

    printf("Data di oggi (gg/mm/aaaa): ");
    if (scanf("%d/%d/%d", &oggi.giorno, &oggi.mese, &oggi.anno) != 3 || oggi.anno < 2000 ||
        oggi.mese < 1 || oggi.mese > 12 || oggi.giorno < 1 ||
        oggi.giorno > giorni_nel_mese(oggi.mese, oggi.anno)) {
        printf("Data non valida.\n");
        comando = 'Q';
    } else {
        svuota_riga();
    }
    while (comando != 'Q') {
        printf("Comando (R numero mesi, A, S, Q): ");
        if (scanf(" %c", &comando) != 1) {
            comando = 'Q';              /* input terminato: come Q */
        }
        comando = (char) toupper((unsigned char) comando);
        if (comando == 'R') {
            if (scanf("%7s %d", numero, &mesi) != 2) {
                printf("  Dati non validi.\n");
            } else {
                trovato = -1;
                for (i = 0; i < ABBONAMENTI; i++) {
                    if (strcmp(elenco[i].numero, numero) == 0) {
                        trovato = i;
                    }
                }
                if (trovato == -1) {
                    printf("  Abbonamento %s inesistente.\n", numero);
                } else if (!rinnova(&elenco[trovato], mesi, &oggi)) {
                    printf("  Durata non valida: da 1 a 12 mesi.\n");
                } else {
                    stampa(&elenco[trovato], &oggi);
                }
            }
        } else if (comando == 'A' || comando == 'S') {
            for (i = 0; i < ABBONAMENTI; i++) {
                giorni = giorni_tra(&oggi, &elenco[i].scadenza);
                if (comando == 'S' || giorni <= PREAVVISO) {
                    stampa(&elenco[i], &oggi);
                }
            }
        } else if (comando != 'Q') {
            printf("  Comando sconosciuto.\n");
        }
        svuota_riga();                  /* un comando per riga */
    }

    return 0;
}

int bisestile(int anno)
{
    return (anno % 4 == 0 && anno % 100 != 0) || anno % 400 == 0;
}

int giorni_nel_mese(int mese, int anno)
{
    int giorni[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int risultato = giorni[mese - 1];

    if (mese == 2 && bisestile(anno)) {
        risultato = 29;
    }
    return risultato;
}

/* Giorni trascorsi dal 1/1/2000. */
int numero_giorno(const Data *d)
{
    int giorni = d->giorno - 1;
    int anno;
    int mese;

    for (anno = 2000; anno < d->anno; anno++) {
        giorni = giorni + (bisestile(anno) ? 366 : 365);
    }
    for (mese = 1; mese < d->mese; mese++) {
        giorni = giorni + giorni_nel_mese(mese, d->anno);
    }
    return giorni;
}

/* Positivo se a viene dopo da. */
int giorni_tra(const Data *da, const Data *a)
{
    return numero_giorno(a) - numero_giorno(da);
}

void aggiungi_mesi(Data *d, int mesi)
{
    int ultimo;

    d->mese = d->mese + mesi;
    while (d->mese > 12) {
        d->mese = d->mese - 12;
        d->anno++;
    }
    ultimo = giorni_nel_mese(d->mese, d->anno);
    if (d->giorno > ultimo) {
        d->giorno = ultimo;
    }
}

int rinnova(Abbonamento *ab, int mesi, const Data *oggi)
{
    int riuscito = mesi >= 1 && mesi <= 12;

    if (riuscito) {
        if (giorni_tra(oggi, &ab->scadenza) < 0) {
            ab->scadenza = *oggi;
        }
        aggiungi_mesi(&ab->scadenza, mesi);
    }
    return riuscito;
}

void stampa(const Abbonamento *ab, const Data *oggi)
{
    int giorni = giorni_tra(oggi, &ab->scadenza);

    printf("  %s %-12s %-3s scadenza %02d/%02d/%d  ", ab->numero, ab->intestatario, ab->linea,
           ab->scadenza.giorno, ab->scadenza.mese, ab->scadenza.anno);
    if (giorni < 0) {
        printf("SCADUTO da %d %s\n", -giorni, giorni == -1 ? "giorno" : "giorni");
    } else if (giorni <= PREAVVISO) {
        printf("in scadenza tra %d %s\n", giorni, giorni == 1 ? "giorno" : "giorni");
    } else {
        printf("valido\n");
    }
}

/* Scarta i caratteri rimasti sulla riga. */
void svuota_riga(void)
{
    int c;

    c = getchar();
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}
