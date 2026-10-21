# Analisi – 060-problema-campionato.c

## 1. Problema

In un torneo di calcio a 5 la matrice dei punti contiene, per 6 squadre e 5
giornate, i punti ottenuti (3, 1, 0). Il programma deve stampare il prospetto
con V/P/S e i totali, la classifica ordinata, le squadre imbattute e il
numero di vittorie e pareggi di ogni giornata.

## 2. Analisi

### Input
Nessun input da tastiera: i dati sono inizializzati nel codice.

| Variabile | Tipo       | Dimensione | Descrizione                          |
|-----------|------------|------------|--------------------------------------|
| `punti`   | `int[][]`  | 6 × 5      | Riga = squadra, colonna = giornata   |
| `squadre` | `char[][]` | 6 × 16     | Nomi, paralleli alle righe           |

### Output
- Il prospetto: per ogni squadra il risultato di ogni giornata (V, P, S) e il
  totale dei punti;
- la classifica in ordine di punti;
- l'elenco delle squadre imbattute;
- per ogni giornata il numero di vittorie e di pareggi, al singolare o al
  plurale.

### Vincoli
- I punti valgono 3 (vittoria), 1 (pareggio), 0 (sconfitta)
- I totali di riga si calcolano una volta e si salvano in un array, perché
  servono sia nel prospetto sia nella classifica
- La classifica si costruisce senza ordinare: per ogni posizione si cerca la
  squadra con più punti tra quelle non ancora classificate; a parità
  precede la squadra che compare prima nell'array
- Una squadra è imbattuta se nella sua riga non c'è nessuno 0; la verifica
  si ferma alla prima sconfitta con un flag (niente `break`)
- Gli esiti per giornata si contano per **colonna**: un pareggio compare
  due volte (una per squadra), quindi le partite pareggiate sono la metà dei
  pareggi contati; una vittoria compare una volta sola

### Assunzioni
- La matrice è coerente: in ogni giornata vittorie e sconfitte si
  corrispondono e i pareggi sono in numero pari

### Variabili di supporto

| Variabile      | Tipo      | Dimensione | Descrizione                                 |
|----------------|-----------|------------|---------------------------------------------|
| `totale`       | `int[]`   | 6          | Punti di ogni squadra                       |
| `classificata` | `int[]`   | 6          | 1 se la squadra è già in classifica         |
| `migliore`     | `int`     | —          | Squadra scelta per la posizione corrente    |
| `imbattuta`    | `int` (0/1) | —        | Esito della verifica su una riga            |
| `vittorie_giornata`, `pareggi_giornata` | `int` | — | Contatori della colonna    |
| `VITTORIA`, `PAREGGIO`, `SCONFITTA` | `#define` | — | 3, 1, 0                  |

### Algoritmo in linguaggio naturale
1. Per ogni squadra stampare V, P o S per ogni giornata con uno `switch`,
   sommare i punti in `totale[s]` e stamparlo.
2. Per ogni posizione da 1 a 6 scegliere la squadra non classificata con
   più punti, segnarla e stamparla.
3. Per ogni squadra verificare l'assenza di sconfitte e, se imbattuta,
   stamparla.
4. Per ogni giornata contare vittorie e pareggi nella colonna e stampare le
   vittorie e la metà dei pareggi.

## 3. Casi di test

Il programma non legge dati: si esegue una volta e si confronta con l'output
atteso.

### Test 1 – Prospetto
- **Output atteso:**
```
  Atletico Volta    V  P  V  S  V      10
  Real Tortona      P  P  V  V  S       8
  Sporting Novi     S  V  S  P  S       4
  Dinamo Acqui      V  V  P  V  V      13
  Olimpia Ovada     S  S  P  S  V       4
  Union Casale      P  S  S  P  S       2
```

### Test 2 – Classifica con parità
- **Cosa si verifica:** Sporting Novi e Olimpia Ovada hanno 4 punti: precede
  Sporting Novi, che compare prima nell'array
- **Output atteso:**
```
  1. Dinamo Acqui      13 punti
  2. Atletico Volta    10 punti
  3. Real Tortona       8 punti
  4. Sporting Novi      4 punti
  5. Olimpia Ovada      4 punti
  6. Union Casale       2 punti
```

### Test 3 – Imbattute ed esiti per giornata
- **Cosa si verifica:** i pareggi contati due volte e il singolare
- **Output atteso:**
```
--- Squadre imbattute ---
  Dinamo Acqui

--- Esiti per giornata ---
  Giornata 1: 2 vittorie, 1 pareggio
  Giornata 2: 2 vittorie, 1 pareggio
  Giornata 3: 2 vittorie, 1 pareggio
  Giornata 4: 2 vittorie, 1 pareggio
  Giornata 5: 3 vittorie, 0 pareggi
```
