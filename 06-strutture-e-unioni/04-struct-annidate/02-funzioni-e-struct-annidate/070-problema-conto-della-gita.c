/*
 * 070-problema-conto-della-gita.c
 *
 * Gita a Torino: il conto e la quota di ogni studente
 *
 * Il docente organizzatore prepara il conto della gita di due giorni.
 * Ogni voce di spesa ha una descrizione, un importo e un'indicazione: se
 * l'importo è a persona va moltiplicato per i partecipanti, altrimenti è
 * il costo totale (il pullman, la guida).
 *
 *     typedef struct {
 *         int euro;
 *         int centesimi;
 *     } Importo;
 *
 *     typedef struct {
 *         char descrizione[24];
 *         Importo costo;
 *         int a_persona;
 *     } Voce;
 *
 * Le funzioni sugli importi ricevono e restituiscono Importo per valore
 * (sono piccoli, come le frazioni); quella sulla voce riceve const Voce *
 * e passa la parte v->costo alle funzioni sugli importi:
 *
 *     Importo somma(Importo a, Importo b);
 *     Importo per(Importo a, int volte);
 *     Importo diviso_per_eccesso(Importo a, int parti);
 *     Importo costo_voce(const Voce *v, int partecipanti);
 *
 * I docenti accompagnatori partecipano (albergo, ingressi) ma non pagano:
 * il totale si divide tra gli studenti, arrotondando la quota al
 * centesimo superiore. Servono almeno un accompagnatore ogni 15 studenti
 * e da 10 a 50 studenti.
 *
 * Il programma legge "studenti accompagnatori" e stampa il conto.
 */

#include <stdio.h>

#define VOCI 5
#define STUDENTI_PER_DOCENTE 15

typedef struct {
    int euro;
    int centesimi;
} Importo;

typedef struct {
    char descrizione[24];
    Importo costo;
    int a_persona;
} Voce;

int in_centesimi(Importo a);
Importo da_centesimi(int centesimi);
Importo somma(Importo a, Importo b);
Importo per(Importo a, int volte);
Importo diviso_per_eccesso(Importo a, int parti);
Importo costo_voce(const Voce *v, int partecipanti);
void stampa_importo(Importo a);

int main(void)
{
    Voce voci[VOCI] = {
        {"Pullman (2 giorni)", {1450, 0}, 0},
        {"Albergo, 1 notte", {58, 50}, 1},
        {"Museo Egizio", {6, 0}, 1},
        {"Guida", {180, 0}, 0},
        {"Assicurazione", {3, 50}, 1}
    };
    int studenti;
    int docenti;
    int partecipanti;
    Importo totale = {0, 0};
    Importo parziale;
    Importo quota;
    Importo raccolto;
    int i;

    printf("Studenti e accompagnatori: ");
    if (scanf("%d %d", &studenti, &docenti) != 2 || studenti < 10 || studenti > 50 ||
        docenti < 1) {
        printf("Dati non validi: da 10 a 50 studenti e almeno un accompagnatore.\n");
    } else if (docenti * STUDENTI_PER_DOCENTE < studenti) {
        printf("Servono almeno %d accompagnatori per %d studenti.\n",
               (studenti + STUDENTI_PER_DOCENTE - 1) / STUDENTI_PER_DOCENTE, studenti);
    } else {
        partecipanti = studenti + docenti;
        for (i = 0; i < VOCI; i++) {
            parziale = costo_voce(&voci[i], partecipanti);
            printf("  %-20s ", voci[i].descrizione);
            if (voci[i].a_persona) {
                stampa_importo(voci[i].costo);
                printf(" x %2d = ", partecipanti);
            } else {
                printf("%21s", "");
            }
            stampa_importo(parziale);
            printf("\n");
            totale = somma(totale, parziale);
        }
        quota = diviso_per_eccesso(totale, studenti);
        raccolto = per(quota, studenti);
        printf("  %-20s %21s", "Totale", "");
        stampa_importo(totale);
        printf("\nQuota per studente: ");
        stampa_importo(quota);
        printf(" (%d studenti, %d accompagnatori gratuiti)\n", studenti, docenti);
        printf("Raccolto ");
        stampa_importo(raccolto);
        printf(", avanzo ");
        stampa_importo(da_centesimi(in_centesimi(raccolto) - in_centesimi(totale)));
        printf("\n");
    }

    return 0;
}

int in_centesimi(Importo a)
{
    return a.euro * 100 + a.centesimi;
}

Importo da_centesimi(int centesimi)
{
    Importo risultato;

    risultato.euro = centesimi / 100;
    risultato.centesimi = centesimi % 100;
    return risultato;
}

Importo somma(Importo a, Importo b)
{
    return da_centesimi(in_centesimi(a) + in_centesimi(b));
}

Importo per(Importo a, int volte)
{
    return da_centesimi(in_centesimi(a) * volte);
}

/* Divide arrotondando per eccesso: nessun centesimo resta scoperto. */
Importo diviso_per_eccesso(Importo a, int parti)
{
    return da_centesimi((in_centesimi(a) + parti - 1) / parti);
}

Importo costo_voce(const Voce *v, int partecipanti)
{
    Importo costo = v->costo;

    if (v->a_persona) {
        costo = per(v->costo, partecipanti);
    }
    return costo;
}

void stampa_importo(Importo a)
{
    printf("%5d.%02d euro", a.euro, a.centesimi);
}
