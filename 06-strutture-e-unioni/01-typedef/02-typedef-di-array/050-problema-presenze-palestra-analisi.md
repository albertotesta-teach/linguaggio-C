# Analisi – 050-problema-presenze-palestra.c

## 1. Problema

Il custode della palestra registra le presenze di ogni giorno (da lunedì a sabato) per quattro settimane. Il programma stampa la tabella con il totale di ogni settimana e di ogni giorno della settimana, la settimana più frequentata, il giorno della settimana con più presenze e il giorno più affollato del mese.

## 2. Analisi generale e struttura dati

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Settimana` | `typedef int Settimana[6];` | presenze da lunedì a sabato |
| `Mese` | `typedef Settimana Mese[4];` | quattro settimane: int[4][6] |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `presenze` | `Mese` | 4 × 6 | Presenze giornaliere |
| `per_giorno` | `Settimana` | 6 | Totali del mese per giorno della settimana |
| `migliore` | `int` | — | Settimana più frequentata |
| `max_s`, `max_g` | `int` | — | Coordinate del giorno più affollato |

| Funzione | Compito |
|----------|---------|
| `totale(s)` | Somma delle presenze di una Settimana |
| `giorno_massimo(s)` | Indice del giorno con più presenze |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Tabella

**a) Input** – dati nel programma

**b) Output** – righe per settimana con totale; riga "Mese" con i totali per giorno

**c) Variabili di supporto** – `per_giorno`

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – per ogni settimana sommare la riga con totale() e accumulare ogni colonna in per_giorno.

### Caso d'uso 2 – Settimana e giorno della settimana

**a) Input** – dati nel programma

**b) Output** – settimana 4 (221); venerdì (192)

**c) Variabili di supporto** – `migliore`

**d) Vincoli** – a parità vale il primo

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – per_giorno è una Settimana: totale() e giorno_massimo() funzionano anche su di essa.

### Caso d'uso 3 – Giorno più affollato

**a) Input** – dati nel programma

**b) Output** – venerdì della settimana 3 (51 presenze)

**c) Variabili di supporto** – `max_s`, `max_g`

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – per ogni settimana prendere il giorno massimo e confrontarlo con il record.
