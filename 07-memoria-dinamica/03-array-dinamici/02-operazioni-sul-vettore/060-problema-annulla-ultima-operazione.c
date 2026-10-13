/*
 * 060-problema-annulla-ultima-operazione.c
 *
 * Il registro elettronico: annullare le modifiche a un voto
 *
 * Quando il docente corregge un voto può sbagliare, e vuole tornare
 * indietro anche di più passi. Prima di ogni modifica il programma salva
 * il valore VECCHIO in fondo a un vettore dinamico di double; il comando
 * U toglie l'ultimo valore salvato e lo rimette:
 *
 *     modifica:  aggiungi(storia, voto); voto = nuovo;
 *     annulla:   togli_ultimo(storia, &voto);
 *
 *     voto 6     storia []
 *     = 7        storia [6]         voto 7
 *     + 0.5      storia [6 7]       voto 7.5
 *     U          storia [6]         voto 7       (annulla il +0.5)
 *     U          storia []          voto 6       (annulla l'= 7)
 *
 * Si aggiunge e si toglie sempre dallo stesso lato, il fondo: l'ultima
 * modifica salvata è la prima annullata. Questo modo di usare un vettore
 * diventerà una struttura dati a sé nel capitolo 10.
 *
 * Comandi:
 *     = voto       nuovo voto
 *     + delta      aggiunge (anche mezzo voto)
 *     - delta      toglie
 *     U            annulla l'ultima modifica
 *     S            mostra voto e storia
 *     Q            fine
 *
 * Il voto deve restare tra 1 e 10: una modifica che lo porterebbe fuori
 * non viene eseguita né salvata.
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double *dati;
    int n;
    int capacita;
} Storia;

Storia *crea_storia(int capacita);
int aggiungi(Storia *s, double valore);
int togli_ultimo(Storia *s, double *valore);
int lunghezza(const Storia *s);
double elemento(const Storia *s, int i);
void distruggi_storia(Storia *s);

int main(void)
{
    Storia *storia = crea_storia(2);
    double voto = 6;
    double valore;
    double nuovo = 0;
    char comando = ' ';
    int ok;
    int i;

    if (storia == NULL) {
        printf("Memoria insufficiente.\n");
        comando = 'Q';
    } else {
        printf("Voto iniziale: %.1f\n", voto);
    }
    while (comando != 'Q') {
        printf("Comando (=, +, -, U, S, Q): ");
        if (scanf(" %c", &comando) != 1) {
            comando = 'Q';
        }
        if (comando == '=' || comando == '+' || comando == '-') {
            ok = scanf("%lf", &valore) == 1;
            if (ok) {
                if (comando == '=') {
                    nuovo = valore;
                } else if (comando == '+') {
                    nuovo = voto + valore;
                } else {
                    nuovo = voto - valore;
                }
                ok = nuovo >= 1 && nuovo <= 10;
            }
            if (!ok) {
                printf("  modifica non valida: voto invariato %.1f\n", voto);
            } else if (!aggiungi(storia, voto)) {
                printf("  Memoria insufficiente: modifica non eseguita.\n");
            } else {
                voto = nuovo;
                printf("  voto %.1f\n", voto);
            }
            scanf("%*[^\n]");
        } else if (comando == 'U') {
            if (togli_ultimo(storia, &voto)) {
                printf("  annullata: voto %.1f\n", voto);
            } else {
                printf("  niente da annullare\n");
            }
        } else if (comando == 'S') {
            printf("  voto %.1f, storia [", voto);
            for (i = 0; i < lunghezza(storia); i++) {
                printf(" %.1f", elemento(storia, i));
            }
            printf(" ]\n");
        } else if (comando != 'Q') {
            printf("  Comando sconosciuto.\n");
        }
    }
    distruggi_storia(storia);

    return 0;
}

Storia *crea_storia(int capacita)
{
    Storia *s = malloc(sizeof *s);

    if (s != NULL) {
        s->dati = malloc(capacita * sizeof *s->dati);
        if (s->dati == NULL) {
            free(s);
            s = NULL;
        } else {
            s->n = 0;
            s->capacita = capacita;
        }
    }
    return s;
}

int aggiungi(Storia *s, double valore)
{
    double *tmp;
    int ok = 1;

    if (s->n == s->capacita) {
        tmp = realloc(s->dati, 2 * s->capacita * sizeof *tmp);
        if (tmp == NULL) {
            ok = 0;
        } else {
            s->dati = tmp;
            s->capacita = 2 * s->capacita;
        }
    }
    if (ok) {
        s->dati[s->n] = valore;
        s->n++;
    }
    return ok;
}

int togli_ultimo(Storia *s, double *valore)
{
    int ok = s->n > 0;

    if (ok) {
        s->n--;
        *valore = s->dati[s->n];
    }
    return ok;
}

int lunghezza(const Storia *s)
{
    return s->n;
}

double elemento(const Storia *s, int i)
{
    return s->dati[i];
}

void distruggi_storia(Storia *s)
{
    if (s != NULL) {
        free(s->dati);
        free(s);
    }
}
