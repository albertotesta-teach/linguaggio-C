/*
 * 030-chi-libera.c
 *
 * Chi alloca e chi libera: le coppie crea_... e distruggi_...
 *
 * Ogni blocco deve essere liberato una e una sola volta. Quando la
 * memoria passa da una funzione all'altra bisogna sapere chi ne è
 * responsabile (il "proprietario"). Una regola semplice: per ogni tipo
 * che usa lo heap si scrivono due funzioni,
 *
 *     Registro *crea_registro(const char *classe, int capienza);
 *     void distruggi_registro(Registro *r);
 *
 * e ogni crea_registro ha la sua distruggi_registro. Chi usa il registro
 * non chiama mai malloc o free sui suoi pezzi.
 *
 * Qui il registro è una struct nello heap che contiene un puntatore a
 * un secondo blocco, l'array dei voti:
 *
 *     typedef struct {
 *         char classe[4];
 *         int capienza;
 *         int n;
 *         double *voti;              blocco di capienza double
 *     } Registro;
 *
 * crea_registro fa due malloc; se la seconda fallisce libera la prima e
 * restituisce NULL. distruggi_registro libera prima l'array e poi la
 * struct: dopo free(r) il campo r->voti non si può più leggere.
 *
 *         r ──► +----------+
 *               | "3B"     |
 *               | capienza |       +-----+-----+-----+-----+
 *               | n        |       | 7.5 | 6.0 |     |     |
 *               | voti ────────►   +-----+-----+-----+-----+
 *               +----------+
 *
 * Esempio: i registri di due classi con capienze diverse.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char classe[4];
    int capienza;
    int n;
    double *voti;
} Registro;

Registro *crea_registro(const char *classe, int capienza);
void distruggi_registro(Registro *r);
int aggiungi_voto(Registro *r, double voto);
void stampa_registro(const Registro *r);

int main(void)
{
    Registro *terza_b = crea_registro("3B", 4);
    Registro *quarta_a = crea_registro("4A", 2);

    if (terza_b == NULL || quarta_a == NULL) {
        printf("Memoria insufficiente.\n");
    } else {
        aggiungi_voto(terza_b, 7.5);
        aggiungi_voto(terza_b, 6);
        aggiungi_voto(quarta_a, 8);
        aggiungi_voto(quarta_a, 5.5);
        if (!aggiungi_voto(quarta_a, 9)) {
            printf("Registro della 4A pieno: voto 9 non inserito.\n");
        }
        stampa_registro(terza_b);
        stampa_registro(quarta_a);
    }

    distruggi_registro(terza_b);
    distruggi_registro(quarta_a);

    return 0;
}

/* Struct e array dei voti; NULL se una delle due malloc fallisce. */
Registro *crea_registro(const char *classe, int capienza)
{
    Registro *r = malloc(sizeof *r);

    if (r != NULL) {
        r->voti = malloc(capienza * sizeof *r->voti);
        if (r->voti == NULL) {
            free(r);
            r = NULL;
        } else {
            strcpy(r->classe, classe);
            r->capienza = capienza;
            r->n = 0;
        }
    }
    return r;
}

/* Prima l'array, poi la struct; con NULL non fa nulla. */
void distruggi_registro(Registro *r)
{
    if (r != NULL) {
        free(r->voti);
        free(r);
    }
}

int aggiungi_voto(Registro *r, double voto)
{
    int aggiunto = r->n < r->capienza;

    if (aggiunto) {
        r->voti[r->n] = voto;
        r->n++;
    }
    return aggiunto;
}

void stampa_registro(const Registro *r)
{
    int i;

    printf("%s (%d/%d voti):", r->classe, r->n, r->capienza);
    for (i = 0; i < r->n; i++) {
        printf(" %.1f", r->voti[i]);
    }
    printf("\n");
}
