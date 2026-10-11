# Analisi – 080-problema-elezione-rappresentanti.c

## 1. Problema

Una classe elegge i due rappresentanti. Le 20 schede sono state trascritte
come stringhe: una scheda vuota è bianca, una scheda con il testo esatto di
un candidato è valida, ogni altro testo è nullo. Il programma fa lo spoglio,
stampa i voti con le percentuali sui voti validi e indica gli eletti; se c'è
un pareggio per il secondo posto segnala che serve un ballottaggio.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `candidati` | `char[][]` | 4 × 24 | Nomi dei candidati |
| `voti` | `int[]` | 4 | Voti di ciascun candidato (parallelo) |
| `schede` | `char[][]` | 20 × 24 | Testo trascritto da ogni scheda |
| `bianche`, `nulle`, `valide` | `int` | — | Conteggi dello spoglio |
| `primo`, `secondo` | `int` | — | Indici dei primi due classificati |
| `pari_merito` | `int` | — | Candidati con i voti del secondo |

| Funzione | Compito |
|----------|---------|
| `cerca_candidato` | Indice del candidato con `strcmp`, oppure -1 |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Classificazione delle schede

**a) Input** – `"Neri Giulia"`, `""`, `"neri giulia"`, `"Neri Giula"`

**b) Output** – valida, bianca, nulla, nulla

**c) Variabili di supporto** – `c`

**d) Vincoli** – `strcmp` richiede il testo esatto: maiuscole e refusi rendono la scheda nulla

**e) Assunzioni** – le schede sono già trascritte

**f) Algoritmo in linguaggio naturale**
1. Se `strlen(scheda) == 0` è bianca.
2. Altrimenti cercare il candidato: se -1 è nulla, se no incrementare i suoi voti.

### Caso d'uso 2 – Percentuali

**a) Input** – `voti[]`, `valide`

**b) Output** – voti e percentuale per candidato

**c) Variabili di supporto** – nessuna

**d) Vincoli** – percentuale calcolata sui voti validi; se `valide` è 0 si stampa 0

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – `100.0 * voti[c] / valide`.

### Caso d'uso 3 – Eletti e pareggio

**a) Input** – voti 2, 5, 4, 4

**b) Output** – "Eletto: Neri Giulia"; secondo posto Russo Marco, Gallo Sara; "serve un ballottaggio"

**c) Variabili di supporto** – `primo`, `secondo`, `pari_merito`

**d) Vincoli** – il secondo si cerca escludendo il primo

**e) Assunzioni** – il primo posto non è in pareggio

**f) Algoritmo in linguaggio naturale**
1. Trovare l'indice del massimo (`primo`).
2. Trovare il massimo tra gli altri (`secondo`).
3. Contare e stampare i candidati diversi da `primo` con i voti di `secondo`.
4. Se sono più di uno serve un ballottaggio, altrimenti `secondo` è eletto.
