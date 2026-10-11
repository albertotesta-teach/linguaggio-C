# Analisi – 070-problema-batteria-drone.c

## 1. Problema

Il programma di controllo del drone del laboratorio di robotica tiene la
carica della batteria e i minuti di volo totali. Esegue voli e ricariche
della durata indicata, rifiuta un volo che porterebbe la carica sotto la
riserva del 20% e mostra dopo ogni comando carica e autonomia residua.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `carica` | `int` | — | Percentuale di carica, modificata da `vola` e `ricarica` |
| `volo` | `int` | — | Minuti di volo totali |
| `comando` | `char` | — | `V`, `R` o `Q` |
| `n` | `int` | — | Minuti del comando |

| Funzione | Compito |
|----------|---------|
| `vola(&carica, &volo, n)` | Esegue il volo se possibile, 1 se eseguito |
| `ricarica(&carica, n)` | Ricarica fino a 100, restituisce i punti aggiunti |
| `autonomia(carica)` | Minuti di volo possibili sopra la riserva |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Volo eseguito

**a) Input** – carica 64%, `V 10`

**b) Output** – "Volo di 10 minuti eseguito. Carica 44%, autonomia 12 minuti"

**c) Variabili di supporto** – `*carica`, `*volo`

**d) Vincoli** – due variabili del chiamante aggiornate dalla stessa funzione

**e) Assunzioni** – consumo 2% al minuto

**f) Algoritmo in linguaggio naturale** – se `*carica - minuti × 2 ≥ 20`,
togliere il consumo, aggiungere i minuti a `*volo` e restituire 1.

### Caso d'uso 2 – Volo rifiutato

**a) Input** – carica 44%, `V 15`

**b) Output** – "Volo rifiutato: la carica scenderebbe sotto il 20%."

**c) Variabili di supporto** – nessuna

**d) Vincoli** – in caso di rifiuto le variabili non cambiano

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – il controllo avviene prima di
qualsiasi modifica; la funzione restituisce 0.

### Caso d'uso 3 – Ricarica

**a) Input** – carica 44%, `R 8`

**b) Output** – "Ricaricati 24 punti. Carica 68%, autonomia 24 minuti"

**c) Variabili di supporto** – `prima`

**d) Vincoli** – la carica non supera 100

**e) Assunzioni** – 3% al minuto

**f) Algoritmo in linguaggio naturale** – salvare la carica iniziale,
aggiungere minuti × 3, limitare a 100 e restituire la differenza.
