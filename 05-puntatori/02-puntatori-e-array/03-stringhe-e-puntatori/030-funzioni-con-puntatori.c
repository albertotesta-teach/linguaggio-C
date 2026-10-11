/*
 * 030-funzioni-con-puntatori.c
 *
 * Funzioni sulle stringhe scritte con i puntatori
 *
 * Le funzioni del sottocapitolo 04-funzioni-su-stringhe usavano un indice.
 * Con i puntatori il ciclo diventa: "finché il carattere puntato non è
 * '\0', lavora su *p e avanza".
 *
 *     lunghezza(s)        p avanza fino al '\0', risultato p - s
 *     copia(dest, sorg)   *d = *s e avanzano entrambi; alla fine il '\0'
 *     confronta(a, b)     avanzano finché i caratteri sono uguali
 *
 * Ora si può anche usare davvero il puntatore restituito da strchr:
 * la posizione è chiocciola - email e il testo che segue è chiocciola + 1.
 *
 * Esempio: l'indirizzo e-mail di uno studente.
 */

#include <stdio.h>
#include <string.h>

#define LUNG 40

int lunghezza(const char *s);
void copia(char *dest, const char *sorgente);
int confronta(const char *a, const char *b);

int main(void)
{
    char email[LUNG] = "giulia.rossi@scuola.it";
    char copia_email[LUNG];
    const char *chiocciola;

    printf("Indirizzo:  %s\n", email);
    printf("Lunghezza:  %d (strlen: %zu)\n", lunghezza(email), strlen(email));

    copia(copia_email, email);
    printf("Copia:      %s\n", copia_email);
    printf("confronta(email, copia_email) = %d\n", confronta(email, copia_email));
    printf("confronta(\"andrea\", \"anna\") = %d  (negativo: andrea viene prima)\n",
           confronta("andrea", "anna"));

    chiocciola = strchr(email, '@');
    if (chiocciola != NULL) {
        printf("\n'@' in posizione chiocciola - email = %d\n", (int) (chiocciola - email));
        printf("Dominio:    chiocciola + 1 = \"%s\"\n", chiocciola + 1);
        printf("Utente:     i primi %d caratteri = \"%.*s\"\n",
               (int) (chiocciola - email), (int) (chiocciola - email), email);
    }

    return 0;
}

/* Numero di caratteri prima del '\0'. */
int lunghezza(const char *s)
{
    const char *p = s;

    while (*p != '\0') {
        p++;
    }
    return p - s;
}

/* Copia sorgente in dest, terminatore compreso. dest deve essere grande
 * abbastanza. */
void copia(char *dest, const char *sorgente)
{
    char *d = dest;
    const char *s = sorgente;

    while (*s != '\0') {
        *d = *s;
        d++;
        s++;
    }
    *d = '\0';
}

/* Negativo se a viene prima di b, zero se sono uguali, positivo se dopo. */
int confronta(const char *a, const char *b)
{
    while (*a != '\0' && *a == *b) {
        a++;
        b++;
    }
    return (unsigned char) *a - (unsigned char) *b;
}
