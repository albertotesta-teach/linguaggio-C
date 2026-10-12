/*
 * 070-problema-menu-mensa.c
 *
 * Mensa scolastica: calorie del menu settimanale e piatti ripetuti
 *
 * Il menu di ogni giorno ha tre portate (primo, secondo, contorno) e la
 * settimana ha cinque menu:
 *
 *     typedef struct {
 *         char nome[20];
 *         int calorie;
 *     } Piatto;
 *
 *     typedef struct {
 *         char giorno[4];
 *         Piatto portate[PORTATE];
 *     } Menu;
 *
 *     typedef struct {
 *         int numero;
 *         Menu giorni[GIORNI];
 *     } Settimana;
 *
 *     s.giorni[g].portate[p].calorie
 *
 * Il programma legge il limite di calorie per il pranzo fissato dal
 * dietista e stampa:
 *   - le calorie di ogni giorno, segnalando i giorni oltre il limite;
 *   - il giorno più calorico e la media della settimana;
 *   - i piatti che compaiono in più giorni, ognuno una volta sola, con
 *     il numero di volte.
 */

#include <stdio.h>
#include <string.h>

#define GIORNI 5
#define PORTATE 3

typedef struct {
    char nome[20];
    int calorie;
} Piatto;

typedef struct {
    char giorno[4];
    Piatto portate[PORTATE];
} Menu;

typedef struct {
    int numero;
    Menu giorni[GIORNI];
} Settimana;

int calorie_menu(const Menu *m);
const Menu *piu_calorico(const Settimana *s);
int conta_piatto(const Settimana *s, const char *nome);
int gia_visto(const Settimana *s, int giorno, int portata);

int main(void)
{
    Settimana menu = {
        12,
        {
            {"Lun", {{"Pasta al pomodoro", 380}, {"Petto di pollo", 220}, {"Insalata", 40}}},
            {"Mar", {{"Risotto", 410}, {"Frittata", 260}, {"Carote", 50}}},
            {"Mer", {{"Lasagne", 520}, {"Arrosto", 300}, {"Patate al forno", 180}}},
            {"Gio", {{"Pasta al pomodoro", 380}, {"Merluzzo", 180}, {"Insalata", 40}}},
            {"Ven", {{"Minestrone", 210}, {"Pizza margherita", 450}, {"Insalata", 40}}}
        }
    };
    const Menu *massimo;
    int limite;
    int calorie;
    int totale = 0;
    int volte;
    int g;
    int p;

    printf("Limite di calorie per il pranzo: ");
    if (scanf("%d", &limite) != 1 || limite <= 0) {
        printf("Limite non valido.\n");
    } else {
        printf("\nSettimana %d\n", menu.numero);
        for (g = 0; g < GIORNI; g++) {
            calorie = calorie_menu(&menu.giorni[g]);
            totale = totale + calorie;
            printf("  %s  %-18s %-17s %-16s %4d kcal%s\n", menu.giorni[g].giorno,
                   menu.giorni[g].portate[0].nome, menu.giorni[g].portate[1].nome,
                   menu.giorni[g].portate[2].nome, calorie, calorie > limite ? "  OLTRE" : "");
        }
        massimo = piu_calorico(&menu);
        printf("Piu' calorico: %s (%d kcal); media %d kcal\n", massimo->giorno,
               calorie_menu(massimo), totale / GIORNI);

        printf("Piatti ripetuti:\n");
        for (g = 0; g < GIORNI; g++) {
            for (p = 0; p < PORTATE; p++) {
                volte = conta_piatto(&menu, menu.giorni[g].portate[p].nome);
                if (volte > 1 && !gia_visto(&menu, g, p)) {
                    printf("  %s: %d volte\n", menu.giorni[g].portate[p].nome, volte);
                }
            }
        }
    }

    return 0;
}

int calorie_menu(const Menu *m)
{
    int totale = 0;
    int p;

    for (p = 0; p < PORTATE; p++) {
        totale = totale + m->portate[p].calorie;
    }
    return totale;
}

const Menu *piu_calorico(const Settimana *s)
{
    const Menu *massimo = &s->giorni[0];
    int g;

    for (g = 1; g < GIORNI; g++) {
        if (calorie_menu(&s->giorni[g]) > calorie_menu(massimo)) {
            massimo = &s->giorni[g];
        }
    }
    return massimo;
}

/* Quante volte il piatto compare nella settimana. */
int conta_piatto(const Settimana *s, const char *nome)
{
    int volte = 0;
    int g;
    int p;

    for (g = 0; g < GIORNI; g++) {
        for (p = 0; p < PORTATE; p++) {
            if (strcmp(s->giorni[g].portate[p].nome, nome) == 0) {
                volte++;
            }
        }
    }
    return volte;
}

/* 1 se lo stesso piatto compare in un giorno precedente. */
int gia_visto(const Settimana *s, int giorno, int portata)
{
    int visto = 0;
    int g;
    int p;

    for (g = 0; g < giorno; g++) {
        for (p = 0; p < PORTATE; p++) {
            if (strcmp(s->giorni[g].portate[p].nome, s->giorni[giorno].portate[portata].nome) == 0) {
                visto = 1;
            }
        }
    }
    return visto;
}
