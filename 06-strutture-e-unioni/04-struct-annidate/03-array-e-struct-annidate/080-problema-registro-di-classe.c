/*
 * 080-problema-registro-di-classe.c
 *
 * Registro elettronico: voti con data e materia, medie per materia e
 * per periodo
 *
 * Il registro di una classe ha gli studenti; ogni studente ha i suoi
 * voti; ogni voto ha valore, data e materia:
 *
 *     typedef struct {
 *         int valore;
 *         Data data;
 *         char materia[12];
 *     } Voto;
 *
 *     typedef struct {
 *         char nome[12];
 *         Voto voti[MAX_VOTI];
 *         int n_voti;
 *     } Studente;
 *
 *     typedef struct {
 *         char classe[4];
 *         Studente studenti[MAX_STUDENTI];
 *         int n_studenti;
 *     } Registro;
 *
 *     r.studenti[s].voti[v].data.mese      quattro livelli
 *
 * Una sola funzione calcola le medie con due filtri facoltativi:
 *
 *     double media(const Studente *s, const char *materia,
 *                  const Data *da, const Data *a, int *quanti);
 *
 * materia NULL significa "tutte le materie", da e a NULL significano
 * "tutto l'anno"; in *quanti scrive il numero di voti usati.
 *
 * Comandi:
 *     V studente materia voto gg/mm/aaaa     nuovo voto
 *     M materia                              media di ogni studente
 *     P gg/mm/aaaa gg/mm/aaaa                media di ogni studente nel
 *                                            periodo, tutte le materie
 *     Q                                      fine
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_VOTI 8
#define MAX_STUDENTI 4

typedef struct {
    int giorno;
    int mese;
    int anno;
} Data;

typedef struct {
    int valore;
    Data data;
    char materia[12];
} Voto;

typedef struct {
    char nome[12];
    Voto voti[MAX_VOTI];
    int n_voti;
} Studente;

typedef struct {
    char classe[4];
    Studente studenti[MAX_STUDENTI];
    int n_studenti;
} Registro;

int confronta_date(const Data *a, const Data *b);
Studente *cerca(Registro *r, const char *nome);
int aggiungi_voto(Studente *s, const Voto *v);
double media(const Studente *s, const char *materia, const Data *da, const Data *a, int *quanti);
void stampa_medie(const Registro *r, const char *materia, const Data *da, const Data *a);
void svuota_riga(void);

int main(void)
{
    Registro registro = {
        "3B",
        {
            {"Bassi", {{7, {2, 10, 2025}, "Matematica"}, {8, {15, 10, 2025}, "Inglese"},
                       {6, {20, 11, 2025}, "Matematica"}}, 3},
            {"Conte", {{5, {2, 10, 2025}, "Matematica"}, {6, {15, 10, 2025}, "Inglese"},
                       {7, {20, 11, 2025}, "Matematica"}, {7, {3, 12, 2025}, "Inglese"}}, 4},
            {"Dini", {{9, {2, 10, 2025}, "Matematica"}, {8, {3, 12, 2025}, "Inglese"}}, 2}
        },
        3
    };
    Studente *studente;
    Voto nuovo;
    Data da;
    Data a;
    char comando = ' ';
    char nome[12];
    char materia[12];

    while (comando != 'Q') {
        printf("Comando (V studente materia voto data, M materia, P da a, Q): ");
        if (scanf(" %c", &comando) != 1) {
            comando = 'Q';              /* input terminato: come Q */
        }
        comando = (char) toupper((unsigned char) comando);
        if (comando == 'V') {
            if (scanf("%11s %11s %d %d/%d/%d", nome, nuovo.materia, &nuovo.valore,
                      &nuovo.data.giorno, &nuovo.data.mese, &nuovo.data.anno) != 6) {
                printf("  Dati non validi.\n");
            } else {
                studente = cerca(&registro, nome);
                if (studente == NULL) {
                    printf("  %s non e' nella %s.\n", nome, registro.classe);
                } else if (nuovo.valore < 1 || nuovo.valore > 10) {
                    printf("  Voto non valido.\n");
                } else if (nuovo.data.mese < 1 || nuovo.data.mese > 12 || nuovo.data.giorno < 1 ||
                           nuovo.data.giorno > 31) {
                    printf("  Data non valida.\n");
                } else if (!aggiungi_voto(studente, &nuovo)) {
                    printf("  Spazio esaurito per i voti di %s.\n", studente->nome);
                } else {
                    printf("  Registrato: %s, %s %d\n", studente->nome, nuovo.materia,
                           nuovo.valore);
                }
            }
        } else if (comando == 'M') {
            if (scanf("%11s", materia) != 1) {
                printf("  Manca la materia.\n");
            } else {
                stampa_medie(&registro, materia, NULL, NULL);
            }
        } else if (comando == 'P') {
            if (scanf("%d/%d/%d %d/%d/%d", &da.giorno, &da.mese, &da.anno, &a.giorno, &a.mese,
                      &a.anno) != 6) {
                printf("  Dati non validi.\n");
            } else if (confronta_date(&da, &a) > 0) {
                printf("  Periodo non valido.\n");
            } else {
                stampa_medie(&registro, NULL, &da, &a);
            }
        } else if (comando != 'Q') {
            printf("  Comando sconosciuto.\n");
        }
        svuota_riga();                  /* un comando per riga */
    }

    return 0;
}

/* Negativo, zero o positivo se a viene prima, insieme o dopo b. */
int confronta_date(const Data *a, const Data *b)
{
    return (a->anno * 10000 + a->mese * 100 + a->giorno) -
           (b->anno * 10000 + b->mese * 100 + b->giorno);
}

Studente *cerca(Registro *r, const char *nome)
{
    Studente *trovato = NULL;
    int s = 0;

    while (s < r->n_studenti && trovato == NULL) {
        if (strcmp(r->studenti[s].nome, nome) == 0) {
            trovato = &r->studenti[s];
        }
        s++;
    }
    return trovato;
}

int aggiungi_voto(Studente *s, const Voto *v)
{
    int riuscito = s->n_voti < MAX_VOTI;

    if (riuscito) {
        s->voti[s->n_voti] = *v;
        s->n_voti++;
    }
    return riuscito;
}

double media(const Studente *s, const char *materia, const Data *da, const Data *a, int *quanti)
{
    int somma = 0;
    int v;

    *quanti = 0;
    for (v = 0; v < s->n_voti; v++) {
        if ((materia == NULL || strcmp(s->voti[v].materia, materia) == 0) &&
            (da == NULL || confronta_date(&s->voti[v].data, da) >= 0) &&
            (a == NULL || confronta_date(&s->voti[v].data, a) <= 0)) {
            somma = somma + s->voti[v].valore;
            (*quanti)++;
        }
    }
    return *quanti > 0 ? (double) somma / *quanti : 0;
}

void stampa_medie(const Registro *r, const char *materia, const Data *da, const Data *a)
{
    double m;
    int quanti;
    int s;

    for (s = 0; s < r->n_studenti; s++) {
        m = media(&r->studenti[s], materia, da, a, &quanti);
        if (quanti == 0) {
            printf("  %-8s nessun voto\n", r->studenti[s].nome);
        } else {
            printf("  %-8s %.2f (%d %s)\n", r->studenti[s].nome, m, quanti,
                   quanti == 1 ? "voto" : "voti");
        }
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
