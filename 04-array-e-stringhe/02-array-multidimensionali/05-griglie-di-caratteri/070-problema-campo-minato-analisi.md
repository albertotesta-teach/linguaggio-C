# Analisi – 070-problema-campo-minato.c

## 1. Problema

Realizzare il campo minato su una griglia 6 × 8 con mine in posizioni fisse.
Il giocatore scopre una cella alla volta indicando riga e colonna (da 1).
Una cella sicura scoperta mostra quante mine ha intorno (spazio se nessuna);
le celle coperte sono mostrate con `#`. Il giocatore perde se scopre una mina
e vince quando ha scoperto tutte le celle sicure. Alla fine si mostra il
campo completo.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `mine` | `char[][]` | 6 × (8 + 1) | Campo segreto: `'*'` mina, `'.'` sicura |
| `numeri` | `int[][]` | 6 × 8 | Mine vicine a ogni cella, calcolate una sola volta |
| `scoperte` | `int[][]` | 6 × 8 | 1 se la cella è stata scoperta; inizializzata con `{{0}}` |
| `celle_sicure`, `scoperte_sicure` | `int` | — | Condizione di vittoria |
| `esplosa` | `int` | — | Flag di sconfitta |

Le tre matrici sono **parallele**: descrivono aspetti diversi delle stesse celle.

| Funzione | Compito |
|----------|---------|
| `conta_mine_vicine` | Mine nelle 8 celle intorno (spostamenti `dr`, `dc`) |
| `stampa_campo` | Stampa celle coperte, numeri e, a fine partita, le mine |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Preparazione del campo

**a) Input** – griglia `mine`

**b) Output** – matrice `numeri`, numero di celle sicure

**c) Variabili di supporto** – `r`, `c`

**d) Vincoli** – i numeri si calcolano una volta sola, non a ogni stampa

**e) Assunzioni** – il campo contiene almeno una cella sicura

**f) Algoritmo in linguaggio naturale**
1. Per ogni cella: `numeri[r][c] = conta_mine_vicine(mine, r, c)`.
2. Se la cella non è una mina incrementare `celle_sicure`.

### Caso d'uso 2 – Cella sicura scoperta

**a) Input** – es. `3 3`

**b) Output** – campo aggiornato con il numero `2` nella cella

**c) Variabili di supporto** – `scoperte`, `scoperte_sicure`

**d) Vincoli** – una cella già scoperta non viene contata due volte

**e) Assunzioni** – l'utente inserisce due interi

**f) Algoritmo in linguaggio naturale**
1. Convertire le coordinate in indici (meno 1) e controllare i limiti.
2. Se la cella è già scoperta segnalarlo.
3. Altrimenti segnarla scoperta; se non è una mina incrementare
   `scoperte_sicure` e stampare il campo.

### Caso d'uso 3 – Mina scoperta

**a) Input** – es. `4 4`

**b) Output** – "BOOM!" e il campo completo con le mine

**c) Variabili di supporto** – `esplosa`

**d) Vincoli** – il ciclo termina per il flag, senza `break`

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – impostare `esplosa = 1`; al termine
del ciclo stampare il messaggio e il campo con `mostra_mine = 1`.

### Caso d'uso 4 – Vittoria

**a) Input** – l'ultima cella sicura

**b) Output** – "Complimenti, campo sminato!"

**c) Variabili di supporto** – `scoperte_sicure == celle_sicure`

**d) Vincoli** – nessuno

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – il ciclo termina perché tutte le
celle sicure sono state scoperte.
