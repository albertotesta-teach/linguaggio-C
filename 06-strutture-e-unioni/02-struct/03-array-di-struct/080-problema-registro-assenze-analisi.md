# Analisi – 080-problema-registro-assenze.c

## 1. Problema

A fine gennaio il coordinatore controlla le ore di assenza di ogni
studente da settembre a gennaio. Il programma calcola il totale e la
percentuale sulle ore svolte e stima le assenze di fine anno proiettando
la percentuale sul monte ore annuale (1056 ore, limite 264). Segnala gli
studenti a rischio e quelli da tenere d'occhio, e indica il mese con più
assenze nella classe. La classe è un array di struct `Studente`.

## 2. Analisi

### Input

Nessun input da tastiera: i dati sono nel sorgente.

| Dato | Valore |
|------|--------|
| Ore svolte (set-gen) | 64, 132, 128, 88, 104 |
| Amato Giada | 2, 6, 4, 3, 5 |
| Bellini Tommaso | 15, 34, 32, 24, 30 |
| Cattaneo Sofia | 0, 3, 2, 0, 1 |
| Donati Kevin | 12, 27, 25, 19, 24 |
| Longo Martina | 5, 11, 9, 7, 8 |

### Output

- Una tabella con le assenze mese per mese, il totale, la percentuale
  (un decimale), la stima di fine anno (intera) e la nota `a rischio` o
  `attenzione`.
- Le ore svolte sul monte ore.
- Il mese con più assenze nella classe.

### Vincoli

- Percentuale = 100 × totale / ore svolte (516).
- Stima = percentuale / 100 × 1056.
- `a rischio` se la stima supera 264; `attenzione` se supera l'80% del
  limite (211.2).
- A parità vale il primo mese.

### Assunzioni

- Il ritmo delle assenze resta lo stesso fino a fine anno.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Studente` | `typedef struct { char nome[20]; int ore_assenza[5]; } Studente;` | Uno studente con le assenze dei cinque mesi |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `classe` | `Studente[5]` | Array di struct |
| `ore_svolte`, `totale_svolte` | `int[5]`, `int` | Ore di lezione per mese e totale |
| `per_mese` | `int[5]` | Assenze della classe per mese |
| `totale`, `percentuale`, `stima` | `int`, `double`, `double` | Valori dello studente |
| `mese_max` | `int` | Mese con più assenze |
| `MONTE_ORE`, `LIMITE` | `#define` | 1056 e 264 |

### Algoritmo in linguaggio naturale

1. Sommare le ore svolte.
2. Stampare l'intestazione.
3. Per ogni studente: stampare le assenze, sommarle nel totale e in
   `per_mese`; calcolare percentuale e stima; stampare con la nota.
4. Trovare il mese con il valore massimo in `per_mese`.
5. Stampare ore svolte e mese con più assenze.

## 3. Casi di test

### Test 1 – Dati del sorgente

- **Cosa si verifica:** calcoli, soglie e massimo.
- **Input:** nessuno.
- **Valori intermedi attesi:** Bellini 135 / 516 = 26.2%, stima 276 > 264;
  Donati 107 / 516 = 20.7%, stima 219 > 211.2.
- **Output atteso:**
  ```
    Studente          set  ott  nov  dic  gen  Totale     %   Stima
    Amato Giada         2    6    4    3    5      20   3.9      41
    Bellini Tommaso    15   34   32   24   30     135  26.2     276  a rischio
    Cattaneo Sofia      0    3    2    0    1       6   1.2      12
    Donati Kevin       12   27   25   19   24     107  20.7     219  attenzione
    Longo Martina       5   11    9    7    8      40   7.8      82

  Ore di lezione svolte: 516 su 1056
  Mese con piu' assenze nella classe: ott (81 ore)
  ```

### Test 2 – Mesi a pari merito

- **Cosa si verifica:** a parità vale il primo mese.
- **Procedura:** portare a 18 le ore di gennaio di Amato (gennaio = 81,
  come ottobre).
- **Output atteso:** `Mese con piu' assenze nella classe: ott (81 ore)`;
  con 19 ore invece `gen (82 ore)`.
