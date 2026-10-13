/*
 * 040-problema-indirizzo-ip.c
 *
 * Laboratorio di reti: indirizzo IP come numero e come quattro byte
 *
 * Un indirizzo IPv4 è un numero a 32 bit; si scrive come quattro numeri
 * da 0 a 255 separati da punti. Una union permette di usare entrambe le
 * forme:
 *
 *     typedef union {
 *         uint32_t numero;          per i calcoli con la maschera
 *         uint8_t byte[4];          per stampare i quattro numeri
 *     } Indirizzo;
 *
 * Il numero si costruisce con a.b.c.d come (a << 24) | (b << 16) |
 * (c << 8) | d. Su una macchina little-endian il byte meno significativo
 * (d) sta in byte[0] e a in byte[3]: per stampare a.b.c.d si leggono i
 * byte da 3 a 0.
 *
 * Il programma legge righe nella forma
 *     indirizzo/prefisso altro_indirizzo
 * (per esempio 192.168.10.11/24 192.168.10.200) e stampa la maschera,
 * l'indirizzo di rete, quello di broadcast, i byte in memoria e se il
 * secondo indirizzo è nella stessa rete. FINE termina.
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define LUNG 64

typedef union {
    uint32_t numero;
    uint8_t byte[4];
} Indirizzo;

int leggi_ip(const char *testo, Indirizzo *ip);
void stampa_ip(Indirizzo ip);

int main(void)
{
    char riga[LUNG];
    char primo[LUNG];
    char secondo[LUNG];
    Indirizzo ip;
    Indirizzo altro;
    Indirizzo maschera;
    Indirizzo rete;
    Indirizzo broadcast;
    int prefisso;
    int finito = 0;

    while (!finito) {
        printf("Indirizzo/prefisso e altro indirizzo (FINE): ");
        if (fgets(riga, LUNG, stdin) == NULL || strncmp(riga, "FINE", 4) == 0) {
            finito = 1;
        } else if (sscanf(riga, "%[0-9.]/%d %s", primo, &prefisso, secondo) != 3 ||
                   !leggi_ip(primo, &ip) || !leggi_ip(secondo, &altro) || prefisso < 1 ||
                   prefisso > 30) {
            printf("  Dati non validi.\n");
        } else {
            maschera.numero = (uint32_t) (0xFFFFFFFFUL << (32 - prefisso));
            rete.numero = ip.numero & maschera.numero;
            broadcast.numero = rete.numero | ~maschera.numero;
            printf("  maschera  ");
            stampa_ip(maschera);
            printf("\n  rete      ");
            stampa_ip(rete);
            printf("\n  broadcast ");
            stampa_ip(broadcast);
            printf("\n  in memoria: %02X %02X %02X %02X (byte[0] ... byte[3])\n", ip.byte[0],
                   ip.byte[1], ip.byte[2], ip.byte[3]);
            printf("  ");
            stampa_ip(altro);
            printf(" %s nella stessa rete\n",
                   (altro.numero & maschera.numero) == rete.numero ? "e'" : "NON e'");
        }
    }

    return 0;
}

/* Converte "a.b.c.d"; 0 se i numeri non sono quattro o superano 255. */
int leggi_ip(const char *testo, Indirizzo *ip)
{
    unsigned int a;
    unsigned int b;
    unsigned int c;
    unsigned int d;
    int valido = sscanf(testo, "%u.%u.%u.%u", &a, &b, &c, &d) == 4 && a <= 255 && b <= 255 &&
                 c <= 255 && d <= 255;

    if (valido) {
        ip->numero = ((uint32_t) a << 24) | ((uint32_t) b << 16) | ((uint32_t) c << 8) | d;
    }
    return valido;
}

/* Su una macchina little-endian il primo numero è in byte[3]. */
void stampa_ip(Indirizzo ip)
{
    printf("%d.%d.%d.%d", ip.byte[3], ip.byte[2], ip.byte[1], ip.byte[0]);
}
