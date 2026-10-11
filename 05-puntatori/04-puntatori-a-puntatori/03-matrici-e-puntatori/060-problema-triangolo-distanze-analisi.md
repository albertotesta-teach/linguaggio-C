# Analisi – 060-problema-triangolo-distanze.c

## 1. Problema

Il pulmino della scuola collega cinque paesi. Le distanze sono simmetriche e nulle sulla diagonale, quindi si memorizza solo la metà della tabella sotto la diagonale, con righe di lunghezza diversa. Il programma stampa la tabella completa e la lunghezza di due giri.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `r1` … `r4` | `int[]` | 1, 2, 3, 4 | Distanze dal paese i ai paesi 0 … i-1 |
| `righe` | `const int *[]` | 5 | Puntatori alle righe (`NULL` per il paese 0) |
| `paesi` | `const char *[]` | 5 | Nomi |
| `giro_mattina`, `giro_alternativo` | `int[]` | 5 | Sequenze di tappe |

| Funzione | Compito |
|----------|---------|
| `distanza(righe, a, b)` | Legge `righe[maggiore][minore]`, 0 se a = b |
| `lunghezza_giro(righe, giro, tappe)` | Somma delle distanze tra tappe consecutive |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Distanza tra due paesi

**a) Input** – Borgo (1) e Ponte (3)

**b) Output** – 15 km

**c) Variabili di supporto** – `righe[3][1]`

**d) Vincoli** – si legge sempre con il primo indice maggiore

**e) Assunzioni** – distanze simmetriche

**f) Algoritmo in linguaggio naturale** – se a > b leggere `righe[a][b]`, se b > a leggere `righe[b][a]`, altrimenti 0.

### Caso d'uso 2 – Tabella completa

**a) Input** – tutte le coppie

**b) Output** – matrice 5 × 5 simmetrica

**c) Variabili di supporto** – nessuna

**d) Vincoli** – la riga 0 (`NULL`) non si dereferenzia mai

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – per ogni coppia chiamare `distanza`: con a = b non si legge la tabella.

### Caso d'uso 3 – Lunghezza di un giro

**a) Input** – Scuola → Ponte → Borgo → Collina → Lago

**b) Output** – 38 km

**c) Variabili di supporto** – `km`

**d) Vincoli** – tappe consecutive

**e) Assunzioni** – il giro non torna alla scuola

**f) Algoritmo in linguaggio naturale** – sommare `distanza(giro[t], giro[t + 1])`.
