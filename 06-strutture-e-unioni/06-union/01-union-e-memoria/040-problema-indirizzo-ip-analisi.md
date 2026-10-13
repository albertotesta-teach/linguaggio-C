# Analisi – 040-problema-indirizzo-ip.c

## 1. Problema

Nel laboratorio di reti si calcolano maschera, indirizzo di rete e di broadcast di un indirizzo IPv4 con prefisso, e si controlla se un secondo indirizzo è nella stessa rete. L'indirizzo è una union: come numero a 32 bit per i calcoli con la maschera, come quattro byte per la stampa. Su una macchina little-endian il primo numero dell'indirizzo sta in byte[3].

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Indirizzo` | `union: numero (uint32_t), byte[4] (uint8_t)` | indirizzo IPv4 |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `ip`, `altro`, `maschera`, `rete`, `broadcast` | `Indirizzo` | — | Indirizzi letti e calcolati |
| `prefisso` | `int` | — | Bit della parte di rete |
| `riga`, `primo`, `secondo` | `char[]` | 64 | Riga letta e sue parti |

| Funzione | Compito |
|----------|---------|
| `leggi_ip(testo, &ip)` | Converte a.b.c.d; 0 se i numeri non sono quattro o superano 255 |
| `stampa_ip(ip)` | Stampa byte[3].byte[2].byte[1].byte[0] |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Stessa rete

**a) Input** – `192.168.10.11/24 192.168.10.200`

**b) Output** – maschera 255.255.255.0, rete 192.168.10.0, broadcast 192.168.10.255, in memoria 0B 0A A8 C0

**c) Variabili di supporto** – `maschera`, `rete`

**d) Vincoli** – prefisso da 1 a 30

**e) Assunzioni** – macchina little-endian

**f) Algoritmo in linguaggio naturale** – maschera = tutti 1 spostati di 32 - prefisso; rete = ip AND maschera; broadcast = rete OR NOT maschera.

### Caso d'uso 2 – Rete diversa

**a) Input** – `10.1.5.20/16 10.2.0.1`

**b) Output** – "10.2.0.1 NON e' nella stessa rete"

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – confrontare altro AND maschera con rete.

### Caso d'uso 3 – Indirizzo non valido

**a) Input** – `172.16.300.1/24 1.1.1.1`

**b) Output** – "Dati non validi."

**c) Variabili di supporto** – —

**d) Vincoli** – numeri da 0 a 255

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – leggi_ip rifiuta 300.
