# Analisi – 060-problema-campionato.c

## 1. Problema

In un torneo di calcio a 5 la matrice dei punti contiene, per 6 squadre e 5
giornate, i punti ottenuti (3, 1, 0). Il programma deve stampare il prospetto
con V/P/S e i totali, la classifica ordinata, le squadre imbattute e il
numero di vittorie e pareggi di ogni giornata.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `punti` | `int[][]` | 6 × 5 | Riga = squadra, colonna = giornata |
| `squadre` | `char[][]` | 6 × 16 | Nomi, paralleli alle righe |
| `totale` | `int[]` | 6 | Totali di riga, calcolati una volta e riusati |
| `classificata` | `int[]` | 6 | Flag per la classifica |
| `migliore` | `int` | — | Indice della squadra scelta per la posizione corrente |
| `imbattuta` | `int` (0/1) | — | Esito della verifica su una riga |

I totali di riga vengono salvati in un array perché servono due volte: nel
prospetto e nella classifica.

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Prospetto e classifica

**a) Input** – `punti`, `squadre`

**b) Output** – prospetto con V/P/S e punti; classifica: Dinamo Acqui 13,
Atletico Volta 10, Real Tortona 8, ...

**c) Variabili di supporto** – `totale`, `classificata`, `migliore`

**d) Vincoli** – a parità di punti precede la squadra che compare prima
nell'elenco (confronto `>`)

**e) Assunzioni** – i punti sono solo 0, 1 o 3

**f) Algoritmo in linguaggio naturale**
1. Per ogni squadra: sommare la riga in `totale[s]` stampando V, P o S.
2. Per ogni posizione da 1 a 6: tra le squadre non classificate scegliere
   quella con il totale più alto, marcarla e stamparla.

### Caso d'uso 2 – Squadre imbattute

**a) Input** – `punti`

**b) Output** – "Dinamo Acqui"

**c) Variabili di supporto** – `imbattuta`

**d) Vincoli** – la verifica di una riga si ferma alla prima sconfitta

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – per ogni squadra ipotizzare
`imbattuta = 1` e smentirla al primo 0 della riga.

### Caso d'uso 3 – Esiti per giornata

**a) Input** – `punti`

**b) Output** – per ogni giornata vittorie e pareggi (es. "2 vittorie, 1 pareggio")

**c) Variabili di supporto** – `vittorie_giornata`, `pareggi_giornata`

**d) Vincoli** – un pareggio compare due volte nella colonna (una per squadra),
quindi il conteggio si divide per 2

**e) Assunzioni** – i dati sono coerenti: ogni giornata ha tante vittorie
quante sconfitte

**f) Algoritmo in linguaggio naturale** – per ogni colonna contare i 3 e gli 1;
stampare le vittorie e metà dei pareggi.
