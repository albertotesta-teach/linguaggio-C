/*
 * 040-problema-ricette-americane.c
 *
 * Laboratorio di cucina dell'alberghiero: convertire le unità americane
 *
 * Le ricette trovate su siti americani usano tazze (cup), cucchiai (tbsp),
 * once (oz), libbre (lb) e gradi Fahrenheit (F). Gli studenti scrivono la
 * quantità e la sigla dell'unità, il programma risponde con la quantità
 * nel sistema metrico.
 *
 * Ogni conversione è una funzione che riceve un double e restituisce un
 * double; il tipo ha un nome:
 *
 *     typedef double (*Conversione)(double);
 *
 * Le conversioni sono in una tabella, parallela alle sigle e alle unità
 * di arrivo:
 *
 *     const char *sigle[UNITA] = {"cup", "tbsp", "oz", "lb", "F"};
 *     Conversione converti[UNITA] = {da_tazze, da_cucchiai, ...};
 *
 * La sigla letta si cerca con strcmp tra le sigle: la sua posizione è
 * l'indice della funzione da chiamare. Una quantità 0 termina.
 */

#include <stdio.h>
#include <string.h>

#define UNITA 5
#define LUNG_SIGLA 10

typedef double (*Conversione)(double);

double da_tazze(double tazze);
double da_cucchiai(double cucchiai);
double da_once(double once);
double da_libbre(double libbre);
double da_fahrenheit(double gradi_f);
void svuota_riga(void);

int main(void)
{
    const char *sigle[UNITA] = {"cup", "tbsp", "oz", "lb", "F"};
    const char *arrivo[UNITA] = {"ml", "ml", "g", "g", "gradi C"};
    Conversione converti[UNITA] = {da_tazze, da_cucchiai, da_once, da_libbre, da_fahrenheit};
    char sigla[LUNG_SIGLA];
    double quantita = 1;
    int k;
    int letti;

    printf("Unita' riconosciute: cup tbsp oz lb F\n");
    while (quantita != 0) {
        printf("Quantita' e unita' (0 per finire): ");
        letti = scanf("%lf", &quantita);
        if (letti == EOF) {
            quantita = 0;               /* input terminato: come 0 */
        } else if (letti == 0) {
            svuota_riga();              /* la quantita' non e' un numero */
            printf("  Quantita' non valida.\n");
            quantita = 1;               /* si continua */
        } else if (quantita != 0) {
            if (scanf("%9s", sigla) != 1) {
                quantita = 0;
            } else {
                svuota_riga();          /* scarta il resto della riga */
                k = 0;
                while (k < UNITA && strcmp(sigla, sigle[k]) != 0) {
                    k++;
                }
                if (k < UNITA) {
                    printf("  %g %s = %.1f %s\n", quantita, sigla, converti[k](quantita), arrivo[k]);
                } else {
                    printf("  Unita' \"%s\" sconosciuta.\n", sigla);
                }
            }
        }
    }

    return 0;
}

/* 1 cup = 236.6 ml */
double da_tazze(double tazze)
{
    return tazze * 236.6;
}

/* 1 tbsp = 14.8 ml */
double da_cucchiai(double cucchiai)
{
    return cucchiai * 14.8;
}

/* 1 oz = 28.35 g */
double da_once(double once)
{
    return once * 28.35;
}

/* 1 lb = 453.6 g */
double da_libbre(double libbre)
{
    return libbre * 453.6;
}

/* C = (F - 32) * 5 / 9 */
double da_fahrenheit(double gradi_f)
{
    return (gradi_f - 32) * 5 / 9;
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
