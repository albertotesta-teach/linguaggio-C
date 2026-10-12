# Analisi – 050-problema-campionato-calcetto.c

## 1. Problema

Nel torneo di calcetto il programma legge i risultati, trova le due squadre con una ricerca che restituisce puntatori e aggiorna punti e gol con una funzione che riceve i due puntatori. Alla fine stampa la tabella, la capolista e l'ultima senza ordinare l'array.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Squadra` | `nome, giocate, punti, fatti, subiti` | squadra del torneo |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `torneo` | `Squadra[]` | 5 | Squadre |
| `casa`, `ospite` | `Squadra *` | — | Squadre della partita |
| `prima`, `ultima` | `int` | — | Indici di capolista e ultima |

| Funzione | Compito |
|----------|---------|
| `cerca(s, n, nome)` | Puntatore alla squadra, NULL se assente |
| `registra(casa, gc, ospite, go)` | Aggiorna le due squadre |
| `migliore(a, b)` | 1 se a precede b: punti, poi differenza reti |
| `stampa(s)` | Riga della tabella |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Partita

**a) Input** – `Fulmini 3 Tigri 1`

**b) Output** – Fulmini +3 punti, gol aggiornati per entrambe

**c) Variabili di supporto** – `casa`, `ospite`

**d) Vincoli** – vittoria 3, pareggio 1

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – registra modifica le due struct tramite i puntatori.

### Caso d'uso 2 – Partita non valida

**a) Input** – `Tigri 2 Tigri 1`

**b) Output** – "Squadre non valide."

**c) Variabili di supporto** – —

**d) Vincoli** – due squadre diverse

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – casa == ospite: stesso indirizzo.

### Caso d'uso 3 – Classifica

**a) Input** – `FINE`

**b) Output** – capolista Fulmini (punti 7), ultima Lupi (punti 1)

**c) Variabili di supporto** – `prima`, `ultima`

**d) Vincoli** – a parità conta la differenza reti

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – un solo ciclo con migliore.
