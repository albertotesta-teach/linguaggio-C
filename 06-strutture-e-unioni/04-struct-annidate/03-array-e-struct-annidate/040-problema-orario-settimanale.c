/*
 * 040-problema-orario-settimanale.c
 *
 * Orario delle classi prime: griglia, ore dei docenti e conflitti
 *
 * L'orario di una classe è una matrice di lezioni, 5 giorni per 4 ore;
 * ogni lezione ha materia, docente e aula:
 *
 *     typedef struct {
 *         char materia[12];
 *         char docente[10];
 *         char aula[8];
 *     } Lezione;
 *
 *     typedef struct {
 *         char nome[4];
 *         Lezione orario[GIORNI][ORE];
 *     } Classe;
 *
 *     prime[k].orario[g][h].docente     docente della classe k, giorno g,
 *                                       ora h
 *
 * Comandi:
 *     O classe     stampa la griglia dell'orario della classe
 *     D docente    lezioni del docente nella settimana e ore totali
 *     C            conflitti tra le due classi: stesso docente o stessa
 *                  aula nello stesso giorno alla stessa ora
 *     Q            fine
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define CLASSI 2
#define GIORNI 5
#define ORE 4

typedef struct {
    char materia[12];
    char docente[10];
    char aula[8];
} Lezione;

typedef struct {
    char nome[4];
    Lezione orario[GIORNI][ORE];
} Classe;

const Classe *cerca_classe(const Classe c[], int n, const char *nome);
void stampa_orario(const Classe *c);
int lezioni_docente(const Classe c[], int n, const char *docente);
int conflitti(const Classe *a, const Classe *b);
const char *nome_giorno(int g);
void svuota_riga(void);

int main(void)
{
    Classe prime[CLASSI] = {
        {"1A", {
            {{"Matematica", "Rossi", "A12"}, {"Italiano", "Bianchi", "A12"},
             {"Inglese", "Verdi", "A12"}, {"Informatica", "Neri", "LabInf"}},
            {{"Fisica", "Galli", "LabFis"}, {"Matematica", "Rossi", "A12"},
             {"Storia", "Sala", "A12"}, {"Italiano", "Bianchi", "A12"}},
            {{"Informatica", "Neri", "LabInf"}, {"Informatica", "Neri", "LabInf"},
             {"Matematica", "Rossi", "A12"}, {"Inglese", "Verdi", "A12"}},
            {{"Italiano", "Bianchi", "A12"}, {"Ed. fisica", "Riva", "Palestra"},
             {"Ed. fisica", "Riva", "Palestra"}, {"Matematica", "Rossi", "A12"}},
            {{"Inglese", "Verdi", "A12"}, {"Fisica", "Galli", "LabFis"},
             {"Italiano", "Bianchi", "A12"}, {"Storia", "Sala", "A12"}}
        }},
        {"1B", {
            {{"Italiano", "Bianchi", "A14"}, {"Matematica", "Rossi", "A14"},
             {"Fisica", "Galli", "LabFis"}, {"Inglese", "Verdi", "A14"}},
            {{"Inglese", "Verdi", "A14"}, {"Matematica", "Rossi", "A14"},
             {"Italiano", "Bianchi", "A14"}, {"Storia", "Sala", "A14"}},
            {{"Matematica", "Rossi", "A14"}, {"Italiano", "Bianchi", "A14"},
             {"Informatica", "Neri", "LabInf"}, {"Informatica", "Neri", "LabInf"}},
            {{"Ed. fisica", "Riva", "Palestra"}, {"Storia", "Sala", "A14"},
             {"Inglese", "Verdi", "A14"}, {"Fisica", "Galli", "LabFis"}},
            {{"Italiano", "Bianchi", "A14"}, {"Matematica", "Rossi", "LabFis"},
             {"Ed. fisica", "Riva", "Palestra"}, {"Inglese", "Verdi", "A14"}}
        }}
    };
    const Classe *classe;
    char comando = ' ';
    char nome[10];
    int ore;
    int trovati;

    while (comando != 'Q') {
        printf("Comando (O classe, D docente, C, Q): ");
        if (scanf(" %c", &comando) != 1) {
            comando = 'Q';              /* input terminato: come Q */
        }
        comando = (char) toupper((unsigned char) comando);
        if (comando == 'O' || comando == 'D') {
            if (scanf("%9s", nome) != 1) {
                printf("  Manca il nome.\n");
            } else if (comando == 'O') {
                classe = cerca_classe(prime, CLASSI, nome);
                if (classe == NULL) {
                    printf("  Classe %s inesistente.\n", nome);
                } else {
                    stampa_orario(classe);
                }
            } else {
                ore = lezioni_docente(prime, CLASSI, nome);
                printf("  %s: %d ore settimanali\n", nome, ore);
            }
        } else if (comando == 'C') {
            trovati = conflitti(&prime[0], &prime[1]);
            printf("  Conflitti: %d\n", trovati);
        } else if (comando != 'Q') {
            printf("  Comando sconosciuto.\n");
        }
        svuota_riga();                  /* un comando per riga */
    }

    return 0;
}

const Classe *cerca_classe(const Classe c[], int n, const char *nome)
{
    const Classe *trovata = NULL;
    int k = 0;

    while (k < n && trovata == NULL) {
        if (strcmp(c[k].nome, nome) == 0) {
            trovata = &c[k];
        }
        k++;
    }
    return trovata;
}

/* Una riga per ora, una colonna per giorno. */
void stampa_orario(const Classe *c)
{
    int g;
    int h;

    printf("  %-4s", c->nome);
    for (g = 0; g < GIORNI; g++) {
        printf(" %-11s", nome_giorno(g));
    }
    printf("\n");
    for (h = 0; h < ORE; h++) {
        printf("  %da  ", h + 1);
        for (g = 0; g < GIORNI; g++) {
            printf(" %-11s", c->orario[g][h].materia);
        }
        printf("\n");
    }
}

/* Stampa le lezioni del docente in tutte le classi; restituisce le ore. */
int lezioni_docente(const Classe c[], int n, const char *docente)
{
    int ore = 0;
    int k;
    int g;
    int h;

    for (g = 0; g < GIORNI; g++) {
        for (h = 0; h < ORE; h++) {
            for (k = 0; k < n; k++) {
                if (strcmp(c[k].orario[g][h].docente, docente) == 0) {
                    printf("  %s %da ora  %s  %-8s %s\n", nome_giorno(g), h + 1, c[k].nome,
                           c[k].orario[g][h].aula, c[k].orario[g][h].materia);
                    ore++;
                }
            }
        }
    }
    return ore;
}

/* Stesso docente o stessa aula nella stessa cella delle due classi. */
int conflitti(const Classe *a, const Classe *b)
{
    int trovati = 0;
    int g;
    int h;

    for (g = 0; g < GIORNI; g++) {
        for (h = 0; h < ORE; h++) {
            if (strcmp(a->orario[g][h].docente, b->orario[g][h].docente) == 0) {
                printf("  %s %da ora: %s in %s e in %s\n", nome_giorno(g), h + 1,
                       a->orario[g][h].docente, a->nome, b->nome);
                trovati++;
            }
            if (strcmp(a->orario[g][h].aula, b->orario[g][h].aula) == 0) {
                printf("  %s %da ora: aula %s occupata da %s e %s\n", nome_giorno(g), h + 1,
                       a->orario[g][h].aula, a->nome, b->nome);
                trovati++;
            }
        }
    }
    return trovati;
}

const char *nome_giorno(int g)
{
    const char *nomi[GIORNI] = {"Lun", "Mar", "Mer", "Gio", "Ven"};

    return nomi[g];
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
