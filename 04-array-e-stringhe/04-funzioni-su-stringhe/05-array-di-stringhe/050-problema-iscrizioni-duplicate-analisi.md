# Analisi – 050-problema-iscrizioni-duplicate.c

## 1. Problema

Per la gita d'istituto gli studenti si sono iscritti con un modulo online,
ma alcuni lo hanno inviato più volte scrivendo il nome in modo diverso
(maiuscole, spazi). Bisogna riconoscere i duplicati, indicare per ciascuno
il modulo originale e produrre l'elenco degli iscritti senza ripetizioni.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `moduli` | `char[][]` | 10 × 28 | Nomi come sono stati scritti |
| `normalizzati` | `char[][]` | 10 × 28 | Nomi normalizzati (parallelo) |
| `pulito` | `char[][]` | 10 × 28 | Elenco senza duplicati (array a tappo) |
| `n_pulito` | `int` | — | Righe usate di `pulito` |
| `duplicato`, `duplicati` | `int` | — | Flag del modulo corrente, totale |

| Funzione | Compito |
|----------|---------|
| `normalizza` | Minuscolo, spazi iniziali/finali eliminati, uno spazio tra le parole |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Varianti dello stesso nome

**a) Input** – `"Rossi Mario"`, `"ROSSI MARIO"`, `"  bianchi  sara"`

**b) Output** – i moduli 3 e 5 sono duplicati dei moduli 1 e 2

**c) Variabili di supporto** – `normalizzati`

**d) Vincoli** – il confronto avviene sulle copie normalizzate, la stampa sugli originali

**e) Assunzioni** – nomi senza lettere accentate

**f) Algoritmo in linguaggio naturale**
1. Normalizzare tutti i moduli.
2. Per ogni modulo `i`, confrontarlo con i moduli `j < i` finché non si
   trova un uguale (ciclo fermato dal flag).
3. Se trovato, segnalarlo; altrimenti copiarlo nell'elenco pulito.

### Caso d'uso 2 – Nomi simili ma diversi

**a) Input** – `"Rossi Mario"` e `"Rossi Maria"`

**b) Output** – entrambi nell'elenco degli iscritti

**c) Variabili di supporto** – nessuna

**d) Vincoli** – `strcmp` sulle copie normalizzate: basta una lettera diversa

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – come nel caso 1.

### Caso d'uso 3 – Elenco pulito

**a) Input** – esito dei confronti

**b) Output** – 10 moduli, 4 duplicati, 6 iscritti con il loro elenco

**c) Variabili di supporto** – `n_pulito`

**d) Vincoli** – si conserva il primo modulo inviato, nell'ordine di arrivo

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – ogni modulo non duplicato si copia
con `strcpy` in `pulito[n_pulito]` e si incrementa `n_pulito`.
