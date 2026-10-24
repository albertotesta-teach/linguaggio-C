/*
 * 080-problema-unione-e-intersezione.c
 *
 * I laboratori pomeridiani: chi ne segue almeno uno e chi li segue tutti e due
 *
 * Gli studenti si iscrivono al laboratorio di robotica e a quello di
 * fotografia indicando il numero di matricola. Le iscrizioni arrivano in
 * ordine sparso: ogni matricola si inserisce nella posizione giusta, così
 * i due vettori restano ordinati e senza doppioni.
 *
 * Con due vettori ordinati unione e intersezione si calcolano con una
 * sola passata parallela, come la fusione di due elenchi:
 *
 *     i su a, j su b:
 *         a[i] < b[j]   ->  a[i] solo in a:   unione
 *         a[i] > b[j]   ->  b[j] solo in b:   unione
 *         a[i] == b[j]  ->  in entrambi:      unione e intersezione
 *
 * Ogni risultato è un vettore NUOVO, creato dalla funzione e restituito
 * al chiamante, che deve distruggerlo: alla fine del programma ci sono
 * quattro vettori da liberare.
 *
 * Il programma legge le matricole di robotica fino a 0, poi quelle di
 * fotografia fino a 0, e stampa i due elenchi, l'unione (quanti studenti
 * diversi restano a scuola il pomeriggio) e l'intersezione (chi deve
 * scegliere, perché i laboratori sono nello stesso giorno).
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *dati;
    int n;
    int capacita;
} Vettore;

Vettore *crea_vettore(int capacita);
int aggiungi(Vettore *v, int valore);
int inserisci_ordinato(Vettore *v, int valore);
int lunghezza(const Vettore *v);
int elemento(const Vettore *v, int i);
void distruggi_vettore(Vettore *v);
Vettore *unione(const Vettore *a, const Vettore *b);
Vettore *intersezione(const Vettore *a, const Vettore *b);
int leggi_iscrizioni(const char *laboratorio, Vettore *v);
void stampa(const char *titolo, const Vettore *v);

int main(void)
{
    Vettore *robotica = crea_vettore(4);
    Vettore *fotografia = crea_vettore(4);
    Vettore *tutti = NULL;
    Vettore *entrambi = NULL;
    int ok = robotica != NULL && fotografia != NULL;

    if (ok) {
        ok = leggi_iscrizioni("robotica", robotica) &&
             leggi_iscrizioni("fotografia", fotografia);
    }
    if (ok) {
        tutti = unione(robotica, fotografia);
        entrambi = intersezione(robotica, fotografia);
        ok = tutti != NULL && entrambi != NULL;
    }
    if (!ok) {
        printf("Memoria insufficiente.\n");
    } else {
        stampa("\nRobotica", robotica);
        stampa("Fotografia", fotografia);
        stampa("Almeno un laboratorio", tutti);
        stampa("Entrambi (devono scegliere)", entrambi);
    }
    distruggi_vettore(robotica);
    distruggi_vettore(fotografia);
    distruggi_vettore(tutti);
    distruggi_vettore(entrambi);

    return 0;
}

Vettore *crea_vettore(int capacita)
{
    Vettore *v = malloc(sizeof *v);

    if (v != NULL) {
        v->dati = malloc(capacita * sizeof *v->dati);
        if (v->dati == NULL) {
            free(v);
            v = NULL;
        } else {
            v->n = 0;
            v->capacita = capacita;
        }
    }
    return v;
}

int aggiungi(Vettore *v, int valore)
{
    int *tmp;
    int ok = 1;

    if (v->n == v->capacita) {
        tmp = realloc(v->dati, 2 * v->capacita * sizeof *tmp);
        if (tmp == NULL) {
            ok = 0;
        } else {
            v->dati = tmp;
            v->capacita = 2 * v->capacita;
        }
    }
    if (ok) {
        v->dati[v->n] = valore;
        v->n++;
    }
    return ok;
}

/*
 * Inserisce mantenendo l'ordine crescente. Restituisce 1 se inserito,
 * 0 se il valore c'era già, -1 se manca memoria.
 */
int inserisci_ordinato(Vettore *v, int valore)
{
    int posizione = 0;
    int esito = 1;
    int i;

    while (posizione < v->n && v->dati[posizione] < valore) {
        posizione++;
    }
    if (posizione < v->n && v->dati[posizione] == valore) {
        esito = 0;
    } else if (!aggiungi(v, valore)) {
        esito = -1;
    } else {
        for (i = v->n - 1; i > posizione; i--) {
            v->dati[i] = v->dati[i - 1];
        }
        v->dati[posizione] = valore;
    }
    return esito;
}

int lunghezza(const Vettore *v)
{
    return v->n;
}

int elemento(const Vettore *v, int i)
{
    return v->dati[i];
}

void distruggi_vettore(Vettore *v)
{
    if (v != NULL) {
        free(v->dati);
        free(v);
    }
}

/* Vettore nuovo con gli elementi di a o di b; NULL se manca memoria. */
Vettore *unione(const Vettore *a, const Vettore *b)
{
    Vettore *r = crea_vettore(4);
    int ok = r != NULL;
    int i = 0;
    int j = 0;

    while (ok && (i < lunghezza(a) || j < lunghezza(b))) {
        if (j == lunghezza(b) || (i < lunghezza(a) && elemento(a, i) < elemento(b, j))) {
            ok = aggiungi(r, elemento(a, i));
            i++;
        } else if (i == lunghezza(a) || elemento(a, i) > elemento(b, j)) {
            ok = aggiungi(r, elemento(b, j));
            j++;
        } else {
            ok = aggiungi(r, elemento(a, i));
            i++;
            j++;
        }
    }
    if (!ok) {
        distruggi_vettore(r);
        r = NULL;
    }
    return r;
}

/* Vettore nuovo con gli elementi di a e di b; NULL se manca memoria. */
Vettore *intersezione(const Vettore *a, const Vettore *b)
{
    Vettore *r = crea_vettore(4);
    int ok = r != NULL;
    int i = 0;
    int j = 0;

    while (ok && i < lunghezza(a) && j < lunghezza(b)) {
        if (elemento(a, i) < elemento(b, j)) {
            i++;
        } else if (elemento(a, i) > elemento(b, j)) {
            j++;
        } else {
            ok = aggiungi(r, elemento(a, i));
            i++;
            j++;
        }
    }
    if (!ok) {
        distruggi_vettore(r);
        r = NULL;
    }
    return r;
}

/* Matricole fino a 0; 0 se manca memoria. */
int leggi_iscrizioni(const char *laboratorio, Vettore *v)
{
    int matricola = -1;
    int esito = 1;
    int letto;

    printf("Matricole iscritte a %s (0 per finire): ", laboratorio);
    while (matricola != 0 && esito != -1) {
        letto = scanf("%d", &matricola);
        if (letto == EOF) {
            matricola = 0;              /* input terminato: come 0 */
        } else if (letto == 0) {
            scanf("%*s");               /* scarta la parola che non e' un numero */
            printf("  matricola non valida\n");
            matricola = -1;
        } else if (matricola < 0) {
            printf("  matricola %d non valida\n", matricola);
        } else if (matricola > 0) {
            esito = inserisci_ordinato(v, matricola);
            if (esito == 0) {
                printf("  %d gia' iscritta\n", matricola);
            }
        }
    }
    return esito != -1;
}

void stampa(const char *titolo, const Vettore *v)
{
    int i;

    printf("%s (%d):", titolo, lunghezza(v));
    for (i = 0; i < lunghezza(v); i++) {
        printf(" %d", elemento(v, i));
    }
    printf("\n");
}
