# Analisi – 050-problema-torneo-a-squadre.c

## 1. Problema

Nel torneo di calcetto d'istituto ogni squadra ha la sua rosa. Il programma registra i gol cercando prima la squadra e poi il giocatore (un livello alla volta, con funzioni che restituiscono un puntatore), stampa la rosa di una squadra e il capocannoniere, o tutti quelli a pari gol.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Giocatore` | `nome, gol` | giocatore |
| `Squadra` | `nome, rosa[], n_giocatori` | squadra con la rosa |
| `Torneo` | `squadre[], n_squadre` | torneo |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `torneo` | `Torneo` | — | Squadre con le rose |
| `squadra`, `giocatore` | `Squadra *`, `Giocatore *` | — | Elementi trovati |
| `nome_squadra`, `nome_giocatore` | `char[]` | 12 | Argomenti dei comandi |

| Funzione | Compito |
|----------|---------|
| `cerca_squadra(t, nome)` | Puntatore alla squadra o NULL |
| `cerca_giocatore(s, nome)` | Puntatore al giocatore della rosa o NULL |
| `gol_squadra(s)` | Somma dei gol della rosa |
| `stampa_rosa(s)` | Giocatori e totale |
| `capocannonieri(t)` | Massimo e tutti quelli che lo raggiungono |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Gol

**a) Input** – `G Squali Orsi`

**b) Output** – "Gol di Orsi (Squali): 3 in tutto."

**c) Variabili di supporto** – `giocatore`

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – cerca_squadra, poi cerca_giocatore nella sua rosa, poi giocatore->gol++.

### Caso d'uso 2 – Errori

**a) Input** – `G Squali Gallo`; `G Delfini Neri`

**b) Output** – "Gallo non e' nella rosa della squadra Squali."; "Squadra Delfini inesistente."

**c) Variabili di supporto** – —

**d) Vincoli** – il giocatore va cercato nella squadra indicata

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – una delle due ricerche restituisce NULL.

### Caso d'uso 3 – Capocannoniere a pari gol

**a) Input** – `C` dopo il secondo gol di Orsi

**b) Output** – "Capocannoniere con 4 gol: Fumo (Tigri) Orsi (Squali)"

**c) Variabili di supporto** – `massimo`

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – primo passaggio per il massimo, secondo per stampare chi lo raggiunge.

### Caso d'uso 4 – Rosa

**a) Input** – `R Squali`

**b) Output** – i quattro giocatori e "Totale squadra: 4 gol"

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – stampa_rosa usa gol_squadra.
