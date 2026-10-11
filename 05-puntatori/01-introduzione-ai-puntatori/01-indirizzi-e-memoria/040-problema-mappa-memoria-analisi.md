# Analisi – 040-problema-mappa-memoria.c

## 1. Problema

Lo sviluppatore del gestionale della segreteria vuole sapere come è
organizzata in memoria la scheda di uno studente (matricola, età, sezione,
media, nome, voti) e quanta memoria servirebbe per 1000 schede. Il
programma stampa una mappa con tipo, indirizzo e dimensione di ogni dato,
il dettaglio degli elementi dell'array dei voti e il totale.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `matricola` | `long` | — | Numero di matricola |
| `eta` | `int` | — | Età |
| `sezione` | `char` | — | Lettera della sezione |
| `media` | `double` | — | Media dei voti |
| `nome` | `char[]` | 20 | Nome e cognome |
| `voti` | `int[]` | 6 | Voti dell'ultimo periodo |
| `totale` | `size_t` | — | Somma delle dimensioni (tipo restituito da `sizeof`) |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Mappa delle variabili

**a) Input** – nessuno (dati fissi)

**b) Output** – una riga per dato: nome, tipo, indirizzo (`%p`), byte (`%zu`)

**c) Variabili di supporto** – nessuna

**d) Vincoli** – l'indirizzo si stampa con `%p` convertendolo in `(void *)`

**e) Assunzioni** – gli indirizzi cambiano a ogni esecuzione; l'ordine delle
variabili in memoria è scelto dal compilatore

**f) Algoritmo in linguaggio naturale** – per ogni dato stampare `&dato` e
`sizeof(dato)`.

### Caso d'uso 2 – Elementi consecutivi dell'array

**a) Input** – `voti[]`

**b) Output** – gli indirizzi di `voti[0]` … `voti[5]`, che crescono di 4

**c) Variabili di supporto** – `k`

**d) Vincoli** – nessuno

**e) Assunzioni** – `int` di 4 byte

**f) Algoritmo in linguaggio naturale** – per `k` da 0 a 5 stampare `voti[k]`
e `&voti[k]`.

### Caso d'uso 3 – Memoria per 1000 schede

**a) Input** – dimensioni dei dati

**b) Output** – byte di una scheda (65) e per 1000 schede (circa 63.5 KB)

**c) Variabili di supporto** – `totale`

**d) Vincoli** – `sizeof` di un array dà la dimensione dell'intero array

**e) Assunzioni** – non si considera lo spazio che il compilatore può
lasciare tra una variabile e l'altra

**f) Algoritmo in linguaggio naturale** – sommare le `sizeof` di tutti i dati
e moltiplicare per il numero di schede.
