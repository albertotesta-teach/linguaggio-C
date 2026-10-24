/*
 * 060-problema-agenda-verifiche.c
 *
 * Agenda delle verifiche: spostare una verifica senza cambiare il resto
 *
 * Il coordinatore di classe tiene l'agenda delle verifiche scritte:
 *
 *     typedef struct {
 *         char classe[4];
 *         char materia[12];
 *         Data giorno;
 *         Orario ora;
 *     } Verifica;
 *
 * La regola della scuola: una classe non può avere due verifiche nello
 * stesso giorno. Le verifiche si fanno tra le 8:00 e le 13:00.
 *
 * Le funzioni lavorano sulle parti:
 *     int data_valida(const Data *d);
 *     int orario_valido(const Orario *o);
 *     int stessa_data(const Data *a, const Data *b);
 *     int conflitto(const Verifica v[], int n, int escluso,
 *                   const char *classe, const Data *giorno);
 *     void sposta(Verifica *v, const Data *giorno, const Orario *ora);
 *
 * sposta assegna solo v->giorno e v->ora: classe e materia restano
 * quelle di prima. conflitto cerca un'altra verifica (diversa da quella
 * in posizione escluso, cioè quella che si sta spostando) della stessa
 * classe nello stesso giorno.
 *
 * Comandi:
 *     E                         elenco numerato
 *     S n gg/mm/aaaa hh:mm      sposta la verifica n
 *     C classe                  verifiche di una classe
 *     Q                         fine
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define VERIFICHE 5

typedef struct {
    int giorno;
    int mese;
    int anno;
} Data;

typedef struct {
    int ore;
    int minuti;
} Orario;

typedef struct {
    char classe[4];
    char materia[12];
    Data giorno;
    Orario ora;
} Verifica;

int data_valida(const Data *d);
int orario_valido(const Orario *o);
int stessa_data(const Data *a, const Data *b);
int conflitto(const Verifica v[], int n, int escluso, const char *classe, const Data *giorno);
void sposta(Verifica *v, const Data *giorno, const Orario *ora);
void stampa(const Verifica *v);
void svuota_riga(void);

int main(void)
{
    Verifica agenda[VERIFICHE] = {
        {"3B", "Matematica", {10, 2, 2026}, {8, 0}},
        {"3B", "Inglese", {12, 2, 2026}, {10, 0}},
        {"3B", "Storia", {13, 2, 2026}, {11, 0}},
        {"4A", "Matematica", {12, 2, 2026}, {9, 0}},
        {"4A", "Fisica", {16, 2, 2026}, {8, 0}}
    };
    char comando = ' ';
    char classe[4];
    Data giorno;
    Orario ora;
    int n;
    int altra;
    int i;

    while (comando != 'Q') {
        printf("Comando (E, S n gg/mm/aaaa hh:mm, C classe, Q): ");
        if (scanf(" %c", &comando) != 1) {
            comando = 'Q';              /* input terminato: come Q */
        }
        comando = (char) toupper((unsigned char) comando);
        if (comando == 'E') {
            for (i = 0; i < VERIFICHE; i++) {
                printf("  %d  ", i);
                stampa(&agenda[i]);
            }
        } else if (comando == 'S') {
            if (scanf("%d %d/%d/%d %d:%d", &n, &giorno.giorno, &giorno.mese, &giorno.anno, &ora.ore,
                      &ora.minuti) != 6) {
                printf("  Dati non validi.\n");
            } else if (n < 0 || n >= VERIFICHE) {
                printf("  Verifica %d inesistente.\n", n);
            } else if (!data_valida(&giorno)) {
                printf("  Data non valida.\n");
            } else if (!orario_valido(&ora)) {
                printf("  Le verifiche si fanno tra le 8:00 e le 13:00.\n");
            } else {
                altra = conflitto(agenda, VERIFICHE, n, agenda[n].classe, &giorno);
                if (altra != -1) {
                    printf("  La %s ha gia' %s quel giorno.\n", agenda[n].classe,
                           agenda[altra].materia);
                } else {
                    sposta(&agenda[n], &giorno, &ora);
                    printf("  Spostata: ");
                    stampa(&agenda[n]);
                }
            }
        } else if (comando == 'C') {
            if (scanf("%3s", classe) != 1) {
                comando = 'Q';
            } else {
                for (i = 0; i < VERIFICHE; i++) {
                    if (strcmp(agenda[i].classe, classe) == 0) {
                        printf("  ");
                        stampa(&agenda[i]);
                    }
                }
            }
        } else if (comando != 'Q') {
            printf("  Comando sconosciuto.\n");
        }
        svuota_riga();                  /* un comando per riga */
    }

    return 0;
}

int data_valida(const Data *d)
{
    int giorni[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int valida = d->mese >= 1 && d->mese <= 12 && d->anno >= 2025;

    if (valida) {
        if (d->mese == 2 && ((d->anno % 4 == 0 && d->anno % 100 != 0) || d->anno % 400 == 0)) {
            giorni[1] = 29;
        }
        valida = d->giorno >= 1 && d->giorno <= giorni[d->mese - 1];
    }
    return valida;
}

int orario_valido(const Orario *o)
{
    int minuti = o->ore * 60 + o->minuti;

    return o->minuti >= 0 && o->minuti < 60 && minuti >= 8 * 60 && minuti <= 13 * 60;
}

int stessa_data(const Data *a, const Data *b)
{
    return a->giorno == b->giorno && a->mese == b->mese && a->anno == b->anno;
}

/* Posizione di un'altra verifica della classe in quel giorno, o -1. */
int conflitto(const Verifica v[], int n, int escluso, const char *classe, const Data *giorno)
{
    int trovata = -1;
    int i = 0;

    while (i < n && trovata == -1) {
        if (i != escluso && strcmp(v[i].classe, classe) == 0 && stessa_data(&v[i].giorno, giorno)) {
            trovata = i;
        }
        i++;
    }
    return trovata;
}

void sposta(Verifica *v, const Data *giorno, const Orario *ora)
{
    v->giorno = *giorno;
    v->ora = *ora;
}

void stampa(const Verifica *v)
{
    printf("%-3s %-11s %02d/%02d/%d  %02d:%02d\n", v->classe, v->materia, v->giorno.giorno,
           v->giorno.mese, v->giorno.anno, v->ora.ore, v->ora.minuti);
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
