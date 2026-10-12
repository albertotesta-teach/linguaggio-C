/*
 * 020-puntatore-e-campo-interno.c
 *
 * Puntatori a struct annidate: p->residenza.cap e &s.residenza
 *
 * Con un puntatore allo studente, i campi interni si raggiungono con la
 * freccia per il primo livello e con il punto per i successivi:
 *
 *     Studente *p = &s;
 *     p->residenza.cap        uguale a (*p).residenza.cap e a s.residenza.cap
 *
 * La freccia serve solo dove c'è un puntatore: p è un puntatore,
 * p->residenza è una struct Indirizzo, quindi poi si usa il punto.
 *
 * Per modificare SOLO la parte interna si passa il suo indirizzo:
 *
 *     void cambia_indirizzo(Indirizzo *i, const char *via, ...);
 *
 *     cambia_indirizzo(&s.residenza, ...);     da una variabile
 *     cambia_indirizzo(&p->residenza, ...);    da un puntatore
 *
 * &p->residenza si legge &(p->residenza): l'operatore -> lega più forte
 * di &. La funzione riceve 8 byte e non può toccare il resto dello
 * studente (nome, classe), che non vede.
 *
 * Esempio: uno studente cambia casa e poi cambia classe.
 */

#include <stdio.h>
#include <string.h>

typedef struct {
    char via[28];
    char cap[6];
    char comune[16];
} Indirizzo;

typedef struct {
    char nome[20];
    char classe[4];
    Indirizzo residenza;
} Studente;

void cambia_indirizzo(Indirizzo *i, const char *via, const char *cap, const char *comune);
void trasferisci(Studente *p, const char *classe, const char *via, const char *cap,
                 const char *comune);
void stampa(const Studente *p);

int main(void)
{
    Studente s = {"Neri Luca", "4C", {"via Roma 77", "15076", "Ovada"}};

    printf("Prima:            ");
    stampa(&s);

    cambia_indirizzo(&s.residenza, "via Cavour 3", "15121", "Alessandria");
    printf("Nuova casa:       ");
    stampa(&s);

    trasferisci(&s, "4A", "corso Roma 10", "15121", "Alessandria");
    printf("Nuova classe:     ");
    stampa(&s);

    return 0;
}

/* Modifica solo l'indirizzo: non sa nulla degli studenti. */
void cambia_indirizzo(Indirizzo *i, const char *via, const char *cap, const char *comune)
{
    strcpy(i->via, via);
    strcpy(i->cap, cap);
    strcpy(i->comune, comune);
}

/* Cambia classe e indirizzo; per l'indirizzo passa &p->residenza. */
void trasferisci(Studente *p, const char *classe, const char *via, const char *cap,
                 const char *comune)
{
    strcpy(p->classe, classe);
    cambia_indirizzo(&p->residenza, via, cap, comune);
}

void stampa(const Studente *p)
{
    printf("%s, %s, %s - %s %s\n", p->nome, p->classe, p->residenza.via, p->residenza.cap,
           p->residenza.comune);
}
