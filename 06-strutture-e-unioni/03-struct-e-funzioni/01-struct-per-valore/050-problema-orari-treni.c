/*
 * 050-problema-orari-treni.c
 *
 * Pendolari: orari di arrivo e coincidenze del treno regionale
 *
 * Molti studenti arrivano a scuola in treno. Il programma conosce l'orario
 * di partenza da ogni stazione e la durata del viaggio, calcola l'orario di
 * arrivo e controlla se resta il tempo per arrivare a scuola (12 minuti a
 * piedi dalla stazione) prima delle 8:00.
 *
 *     typedef struct {
 *         int ore;
 *         int minuti;
 *     } Orario;
 *
 *     Orario crea_orario(int ore, int minuti);
 *     Orario aggiungi_minuti(Orario o, int minuti);    restituisce un nuovo Orario
 *     int differenza(Orario da, Orario a);             minuti tra due orari
 *
 * aggiungi_minuti riceve l'orario per valore e restituisce il risultato:
 * l'orario di partenza non cambia. Il passaggio dopo la mezzanotte è
 * gestito con il resto della divisione per 24 * 60.
 *
 * Il programma legge partenza e minuti di ritardo per ogni treno; un
 * ritardo negativo termina.
 */

#include <stdio.h>

#define CAMMINO      12
#define TRENI        4

typedef struct {
    int ore;
    int minuti;
} Orario;

Orario crea_orario(int ore, int minuti);
Orario aggiungi_minuti(Orario o, int minuti);
int differenza(Orario da, Orario a);
void stampa(Orario o);
void svuota_riga(void);

int main(void)
{
    const char *stazioni[TRENI] = {"Acqui Terme", "Ovada", "Novi Ligure", "Tortona"};
    int durate[TRENI] = {38, 29, 24, 21};
    Orario partenze[TRENI];
    Orario campanella = crea_orario(8, 0);
    Orario arrivo;
    Orario a_scuola;
    int ritardo = 0;
    int t = 0;
    int letti;

    partenze[0] = crea_orario(7, 2);
    partenze[1] = crea_orario(7, 10);
    partenze[2] = crea_orario(7, 18);
    partenze[3] = crea_orario(7, 25);

    while (t < TRENI && ritardo >= 0) {
        printf("Ritardo del treno da %s (minuti, negativo per finire): ", stazioni[t]);
        letti = scanf("%d", &ritardo);
        if (letti == EOF) {
            ritardo = -1;               /* input terminato: come un negativo */
        } else if (letti == 0) {
            svuota_riga();              /* non e' un numero */
            printf("  Ritardo non valido, ripetere.\n");
        } else if (ritardo >= 0) {
            arrivo = aggiungi_minuti(partenze[t], durate[t] + ritardo);
            a_scuola = aggiungi_minuti(arrivo, CAMMINO);
            printf("  partenza ");
            stampa(partenze[t]);
            printf(", arrivo ");
            stampa(arrivo);
            printf(", a scuola ");
            stampa(a_scuola);
            if (differenza(a_scuola, campanella) >= 0) {
                printf("  in orario (%d min di margine)\n", differenza(a_scuola, campanella));
            } else {
                printf("  RITARDO di %d min: serve il permesso\n", -differenza(a_scuola, campanella));
            }
            t++;
        }
    }

    return 0;
}

Orario crea_orario(int ore, int minuti)
{
    Orario o;

    o.ore = ore;
    o.minuti = minuti;
    return o;
}

/* Nuovo orario dopo un certo numero di minuti, anche oltre la mezzanotte. */
Orario aggiungi_minuti(Orario o, int minuti)
{
    int totale = (o.ore * 60 + o.minuti + minuti) % (24 * 60);

    return crea_orario(totale / 60, totale % 60);
}

/* Minuti da "da" ad "a": positivo se a viene dopo. */
int differenza(Orario da, Orario a)
{
    return (a.ore * 60 + a.minuti) - (da.ore * 60 + da.minuti);
}

void stampa(Orario o)
{
    printf("%02d:%02d", o.ore, o.minuti);
}

/* Scarta i caratteri rimasti sulla riga dopo un inserimento errato. */
void svuota_riga(void)
{
    int c;

    c = getchar();
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}
