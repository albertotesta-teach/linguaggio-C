/*
 * 040-problema-menu-del-giorno.c
 *
 * Mensa scolastica: il menu del giorno
 *
 * Il menu settimanale della mensa ha un primo, un secondo e un contorno
 * per ogni giorno da lunedì a venerdì. I nomi dei piatti hanno lunghezze
 * molto diverse ("Riso" e "Pasta al pomodoro e basilico"): con tre array
 * di puntatori a stringhe costanti ogni nome occupa solo lo spazio che
 * gli serve.
 *
 * Lo studente inserisce il numero del giorno (1-5) e il programma stampa
 * il menu; 0 termina. Alla fine il programma indica il piatto con il nome
 * più lungo, per verificare che stia nel tabellone della mensa.
 */

#include <stdio.h>
#include <string.h>

#define GIORNI 5

void stampa_menu(int g, const char *giorni[], const char *primi[],
                 const char *secondi[], const char *contorni[]);
void svuota_riga(void);

int main(void)
{
    const char *giorni[GIORNI] = {"Lunedi", "Martedi", "Mercoledi", "Giovedi", "Venerdi"};
    const char *primi[GIORNI] = {"Pasta al pomodoro e basilico", "Riso",
                                 "Minestrone di verdure", "Lasagne", "Gnocchi al pesto"};
    const char *secondi[GIORNI] = {"Pollo arrosto", "Frittata", "Merluzzo al forno",
                                   "Polpette", "Formaggi misti"};
    const char *contorni[GIORNI] = {"Insalata", "Carote", "Patate al forno",
                                    "Fagiolini", "Pomodori"};
    const char *piu_lungo = primi[0];
    int g = 1;
    int letti;
    int i;

    while (g != 0) {
        printf("Giorno (1-5, 0 per finire): ");
        letti = scanf("%d", &g);
        if (letti == EOF) {
            g = 0;                      /* input terminato: come 0 */
        } else if (letti == 0) {
            svuota_riga();              /* non è un numero */
            g = -1;                     /* giorno non valido */
        }
        if (g < 0 || g > GIORNI) {
            printf("  Giorno non valido.\n");
        } else if (g != 0) {
            stampa_menu(g - 1, giorni, primi, secondi, contorni);
        }
    }

    for (i = 0; i < GIORNI; i++) {
        if (strlen(primi[i]) > strlen(piu_lungo)) {
            piu_lungo = primi[i];
        }
        if (strlen(secondi[i]) > strlen(piu_lungo)) {
            piu_lungo = secondi[i];
        }
        if (strlen(contorni[i]) > strlen(piu_lungo)) {
            piu_lungo = contorni[i];
        }
    }
    printf("Nome piu' lungo per il tabellone: \"%s\" (%zu caratteri)\n",
           piu_lungo, strlen(piu_lungo));

    return 0;
}

void stampa_menu(int g, const char *giorni[], const char *primi[],
                 const char *secondi[], const char *contorni[])
{
    printf("  --- %s ---\n", giorni[g]);
    printf("  Primo:    %s\n", primi[g]);
    printf("  Secondo:  %s\n", secondi[g]);
    printf("  Contorno: %s\n", contorni[g]);
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
