# Analisi – 040-problema-figure-geometriche.c

## 1. Problema

Per la verifica di geometria il programma legge cerchi, rettangoli e triangoli, li controlla e ne calcola area e perimetro; alla fine indica la figura con l'area maggiore. Una Figura contiene un'etichetta e una union delle tre alternative; area, perimetro e valida sono switch sull'etichetta.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Figura` | `tipo, union dati {cerchio, rettangolo, triangolo}` | figura geometrica |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `figure` | `Figura[]` | 8 | Figure valide |
| `n`, `massima` | `int` | — | Figure lette e indice della più grande |
| `esito` | `int` | — | Risultato della lettura |

| Funzione | Compito |
|----------|---------|
| `leggi_figura(&f)` | 1 letta, 0 FINE o numeri mancanti, -1 lettera sconosciuta |
| `valida(&f)` | Misure positive; disuguaglianza triangolare |
| `area(&f), perimetro(&f)` | Switch sull'etichetta; Erone per il triangolo |
| `nome(&f)` | Nome della figura |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Figure valide

**a) Input** – `C 2`; `R 3 4`; `T 3 4 5`

**b) Output** – area 12.57, 12.00, 6.00

**c) Variabili di supporto** – `figure`

**d) Vincoli** – misure positive

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – leggere la lettera, impostare l'etichetta e leggere i campi della sua alternativa.

### Caso d'uso 2 – Triangolo impossibile

**a) Input** – `T 1 1 5`

**b) Output** – "Misure non valide per un triangolo."

**c) Variabili di supporto** – —

**d) Vincoli** – ogni lato minore della somma degli altri

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – valida controlla i tre lati.

### Caso d'uso 3 – Figura sconosciuta

**a) Input** – `X`

**b) Output** – "Figura non riconosciuta."

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – leggi_figura restituisce -1.

### Caso d'uso 4 – Area maggiore

**a) Input** – `FINE`

**b) Output** – "Area maggiore: figura 1 (cerchio), 12.57"

**c) Variabili di supporto** – `massima`

**d) Vincoli** – —

**e) Assunzioni** – a parità vince la prima

**f) Algoritmo in linguaggio naturale** – confronto delle aree con la funzione area.
