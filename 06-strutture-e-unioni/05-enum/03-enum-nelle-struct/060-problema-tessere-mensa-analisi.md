# Analisi – 060-problema-tessere-mensa.c

## 1. Problema

Il prezzo del pasto in mensa dipende dalla fascia ISEE della famiglia.
Ogni fascia ha nome, tetto ISEE e prezzo in una tabella di `Tariffa`
indicizzata dall'enum `Fascia`; all'avvio la fascia di ogni tessera si
calcola dall'ISEE. I comandi registrano pasti, mostrano una tessera o
riepilogano l'incasso per fascia.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `comando` | `char` | `P numero` pasto, `S numero` situazione, `R` riepilogo, `Q` fine (anche minuscoli) |
| `numero` | `int` | Numero della tessera |
| tessere | nel sorgente | 101 Bassi Rita ISEE 6500 (3 pasti), 102 Corti Ugo 18200 (0), 103 Dini Ada 31000 (2), 104 Elia Gino 15000 (1), 105 Fumo Pia 9800 (0) |

### Output

- `P`/`S`: `numero nome fascia F, P euro a pasto, pasti N: T euro`, oppure
  `Tessera N inesistente.`, `Numero non valido.`
- `R`: per ogni fascia tessere, pasti e incasso; il totale.
- `Comando sconosciuto.`

### Vincoli

- Fasce: A fino a 8000 euro (2.00 a pasto), B fino a 15000 (3.50), C fino
  a 25000 (4.80), D oltre (5.90); il tetto è compreso.
- La fascia iniziale nel sorgente (`FASCIA_A`) viene ricalcolata
  all'avvio con `da_isee`.
- La tabella usa inizializzatori designati (`[FASCIA_B] = {...}`).
- Un comando per riga; i dati non validi non interrompono il programma. A
  fine input termina come con `Q`.

### Assunzioni

- L'ISEE non cambia durante l'anno.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Fascia` | `typedef enum { FASCIA_A, FASCIA_B, FASCIA_C, FASCIA_D, NUM_FASCE } Fascia;` | Fascia ISEE |
| `Tariffa` | `typedef struct { const char *nome; double isee_massimo; double prezzo_pasto; } Tariffa;` | Regole di una fascia |
| `Tessera` | `typedef struct { int numero; char nome[16]; double isee; Fascia fascia; int pasti; } Tessera;` | Tessera mensa |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `tariffe` | `Tariffa[4]` | Tabella indicizzata dalla fascia |
| `tessere` | `Tessera[5]` | Tessere |
| `t` | `Tessera *` | Tessera trovata |
| `quante`, `pasti`, `incasso`, `totale` | `int`, `int`, `double`, `double` | Riepilogo |

| Funzione | Compito |
|----------|---------|
| `da_isee(isee, tariffe)` | Prima fascia con il tetto non superato |
| `cerca(t, n, numero)` | Puntatore alla tessera, o `NULL` |
| `svuota_riga` | Scarta i caratteri rimasti sulla riga |

### Algoritmo in linguaggio naturale

1. Calcolare la fascia di ogni tessera.
2. Finché il comando non è `Q`:
   1. leggere il comando in maiuscolo;
   2. `P`/`S`: cercare la tessera; con `P` aggiungere un pasto; stampare
      la situazione;
   3. `R`: per ogni fascia contare tessere e pasti, calcolare l'incasso e
      il totale;
   4. scartare il resto della riga.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Riepiloghi e pasti

- **Cosa si verifica:** fasce calcolate (15000 è ancora fascia B), pasti
  registrati, errori.
- **Input:** `R`, `S 102`, `P 101`, `p 104`, `P 105`, `P 999`, `S x`, `X`,
  `R`, `Q`
- **Output atteso:**
  ```
    fascia A: tessere 1, pasti  3,   6.00 euro
    fascia B: tessere 2, pasti  1,   3.50 euro
    fascia C: tessere 1, pasti  0,   0.00 euro
    fascia D: tessere 1, pasti  2,  11.80 euro
    totale 21.30 euro
    102 Corti Ugo   fascia C, 4.80 euro a pasto, pasti 0: 0.00 euro
    101 Bassi Rita  fascia A, 2.00 euro a pasto, pasti 4: 8.00 euro
    104 Elia Gino   fascia B, 3.50 euro a pasto, pasti 2: 7.00 euro
    105 Fumo Pia    fascia B, 3.50 euro a pasto, pasti 1: 3.50 euro
    Tessera 999 inesistente.
    Numero non valido.
    Comando sconosciuto.
    fascia A: tessere 1, pasti  4,   8.00 euro
    fascia B: tessere 2, pasti  3,  10.50 euro
    fascia C: tessere 1, pasti  0,   0.00 euro
    fascia D: tessere 1, pasti  2,  11.80 euro
    totale 30.30 euro
  ```
