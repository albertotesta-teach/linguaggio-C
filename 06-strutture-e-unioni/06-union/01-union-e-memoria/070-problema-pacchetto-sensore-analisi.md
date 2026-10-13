# Analisi – 070-problema-pacchetto-sensore.c

## 1. Problema

La centralina meteo invia pacchetti di 8 byte. Una union sovrappone l'array dei byte ricevuti e una struct con i campi (temperatura e umidità in decimi, batteria in mV, sensore, controllo). Il programma verifica che la struct sia di 8 byte, controlla il byte di controllo (somma dei primi 7 modulo 256) e stampa i valori.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Pacchetto` | `union: grezzi[8], campi {temperatura, umidita, batteria, sensore, controllo}` | pacchetto della centralina |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `p` | `Pacchetto` | — | Union: grezzi[8] e campi |
| `riga` | `char[]` | 64 | Riga con 8 numeri esadecimali |
| `b` | `unsigned int[]` | 8 | Byte letti (in leggi_pacchetto) |

| Funzione | Compito |
|----------|---------|
| `leggi_pacchetto(riga, &p)` | Riempie grezzi; 0 se i byte non sono 8 |
| `controllo_corretto(&p)` | Somma dei primi 7 byte modulo 256 |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Pacchetto valido

**a) Input** – `E1 00 5E 01 E8 0B 03 36`

**b) Output** – "sensore 3: 22.5 gradi, umidita' 35.0%, batteria 3048 mV"

**c) Variabili di supporto** – `p.campi`

**d) Vincoli** – struct di 8 byte senza padding

**e) Assunzioni** – numeri a 16 bit little-endian

**f) Algoritmo in linguaggio naturale** – i byte E1 00 diventano 0x00E1 = 225 decimi.

### Caso d'uso 2 – Temperatura negativa e pile

**a) Input** – `DD FF 22 03 86 0B 07 99`

**b) Output** – -3.5 gradi, 80.2%, 2950 mV "CAMBIARE LE PILE"

**c) Variabili di supporto** – —

**d) Vincoli** – batteria minima 3000 mV

**e) Assunzioni** – int16_t con segno

**f) Algoritmo in linguaggio naturale** – 0xFFDD in complemento a due vale -35.

### Caso d'uso 3 – Pacchetto corrotto

**a) Input** – ultimo byte `37` invece di `36`

**b) Output** – "Pacchetto corrotto: controllo errato."

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – la somma non coincide con il byte di controllo.

### Caso d'uso 4 – Pacchetto incompleto

**a) Input** – `E1 00`

**b) Output** – "Servono 8 byte."

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – sscanf legge meno di 8 numeri.
