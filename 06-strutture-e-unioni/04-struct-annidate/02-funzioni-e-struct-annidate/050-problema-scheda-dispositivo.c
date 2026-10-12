/*
 * 050-problema-scheda-dispositivo.c
 *
 * Laboratorio di sistemi: controllo delle schede dei PC
 *
 * Prima della verifica di sistemi e reti il tecnico controlla le schede
 * dei PC del laboratorio. Ogni scheda ha due parti, l'hardware e la
 * configurazione di rete:
 *
 *     typedef struct {
 *         char cpu[12];
 *         int ram_gb;
 *         int disco_gb;
 *     } Hardware;
 *
 *     typedef struct {
 *         int ip[4];
 *         int prefisso;             /24 = maschera 255.255.255.0
 *         int gateway[4];
 *     } Rete;
 *
 *     typedef struct {
 *         char nome[8];
 *         Hardware hw;
 *         Rete rete;
 *     } Dispositivo;
 *
 * Ogni parte ha la sua funzione di controllo, che riceve solo la parte:
 *     hardware_valido(&d->hw)     RAM almeno 8 GB, disco almeno 256 GB
 *     rete_valida(&d->rete)       numeri da 0 a 255, prefisso da 8 a 30,
 *                                 gateway nella stessa sottorete e
 *                                 diverso dall'indirizzo del PC
 * e una funzione controlla l'intero laboratorio: due PC non possono avere
 * lo stesso indirizzo IP.
 *
 * Stessa sottorete: l'AND bit a bit con la maschera dà lo stesso
 * risultato per l'indirizzo del PC e per quello del gateway.
 */

#include <stdio.h>

#define PC 5
#define RAM_MINIMA 8
#define DISCO_MINIMO 256

typedef struct {
    char cpu[12];
    int ram_gb;
    int disco_gb;
} Hardware;

typedef struct {
    int ip[4];
    int prefisso;
    int gateway[4];
} Rete;

typedef struct {
    char nome[8];
    Hardware hw;
    Rete rete;
} Dispositivo;

int ip_valido(const int ip[]);
unsigned long valore_ip(const int ip[]);
int stesso_ip(const int a[], const int b[]);
void stampa_ip(const int ip[]);
int hardware_valido(const Hardware *h);
int rete_valida(const Rete *r);
void stampa_dispositivo(const Dispositivo *d);
int controlla_laboratorio(const Dispositivo lab[], int n);

int main(void)
{
    Dispositivo laboratorio[PC] = {
        {"PC-01", {"i5", 16, 512}, {{192, 168, 10, 11}, 24, {192, 168, 10, 1}}},
        {"PC-02", {"i3", 8, 256}, {{192, 168, 10, 12}, 24, {192, 168, 1, 1}}},
        {"PC-03", {"i5", 4, 512}, {{192, 168, 10, 13}, 24, {192, 168, 10, 1}}},
        {"PC-04", {"i7", 16, 1024}, {{192, 168, 10, 11}, 24, {192, 168, 10, 1}}},
        {"PC-05", {"i5", 16, 512}, {{192, 168, 10, 300}, 24, {192, 168, 10, 1}}}
    };
    int errori;

    errori = controlla_laboratorio(laboratorio, PC);
    printf("\nSchede da correggere: %d su %d\n", errori, PC);

    return 0;
}

int ip_valido(const int ip[])
{
    int valido = 1;
    int i;

    for (i = 0; i < 4; i++) {
        if (ip[i] < 0 || ip[i] > 255) {
            valido = 0;
        }
    }
    return valido;
}

/* I quattro numeri come un unico numero a 32 bit. */
unsigned long valore_ip(const int ip[])
{
    return ((unsigned long) ip[0] << 24) | ((unsigned long) ip[1] << 16) |
           ((unsigned long) ip[2] << 8) | (unsigned long) ip[3];
}

int stesso_ip(const int a[], const int b[])
{
    return valore_ip(a) == valore_ip(b);
}

void stampa_ip(const int ip[])
{
    printf("%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
}

int hardware_valido(const Hardware *h)
{
    int valido = 1;

    if (h->ram_gb < RAM_MINIMA) {
        printf("    RAM insufficiente: %d GB\n", h->ram_gb);
        valido = 0;
    }
    if (h->disco_gb < DISCO_MINIMO) {
        printf("    disco insufficiente: %d GB\n", h->disco_gb);
        valido = 0;
    }
    return valido;
}

int rete_valida(const Rete *r)
{
    int valida = 1;
    unsigned long maschera;

    if (!ip_valido(r->ip) || !ip_valido(r->gateway)) {
        printf("    indirizzo o gateway con numeri oltre 255\n");
        valida = 0;
    } else if (r->prefisso < 8 || r->prefisso > 30) {
        printf("    prefisso /%d non ammesso\n", r->prefisso);
        valida = 0;
    } else {
        maschera = (0xFFFFFFFFUL << (32 - r->prefisso)) & 0xFFFFFFFFUL;
        if ((valore_ip(r->ip) & maschera) != (valore_ip(r->gateway) & maschera)) {
            printf("    gateway fuori dalla sottorete\n");
            valida = 0;
        } else if (stesso_ip(r->ip, r->gateway)) {
            printf("    indirizzo uguale al gateway\n");
            valida = 0;
        }
    }
    return valida;
}

void stampa_dispositivo(const Dispositivo *d)
{
    printf("%s  %-3s %3d GB RAM %5d GB  ", d->nome, d->hw.cpu, d->hw.ram_gb, d->hw.disco_gb);
    stampa_ip(d->rete.ip);
    printf("/%d gw ", d->rete.prefisso);
    stampa_ip(d->rete.gateway);
    printf("\n");
}

/* Controlla ogni scheda e gli indirizzi duplicati; restituisce le schede
   con almeno un errore. */
int controlla_laboratorio(const Dispositivo lab[], int n)
{
    int errori = 0;
    int corretta;
    int hw_ok;
    int rete_ok;
    int i;
    int j;

    for (i = 0; i < n; i++) {
        stampa_dispositivo(&lab[i]);
        hw_ok = hardware_valido(&lab[i].hw);
        rete_ok = rete_valida(&lab[i].rete);
        corretta = hw_ok && rete_ok;
        for (j = 0; j < i; j++) {
            if (stesso_ip(lab[i].rete.ip, lab[j].rete.ip)) {
                printf("    indirizzo gia' usato da %s\n", lab[j].nome);
                corretta = 0;
            }
        }
        if (corretta) {
            printf("    ok\n");
        } else {
            errori++;
        }
    }
    return errori;
}
