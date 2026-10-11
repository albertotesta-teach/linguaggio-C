# Analisi – 060-problema-gioco-della-vita.c

## 1. Problema

Simulare il "gioco della vita" di Conway su una griglia 8 × 12 per 4
generazioni. Ogni cella è viva (`#`) o morta (`.`); a ogni generazione tutte
le celle cambiano contemporaneamente in base al numero di vicine vive:
sopravvive una cella viva con 2 o 3 vicine, nasce una cella morta con
esattamente 3 vicine, in tutti gli altri casi la cella è morta. La griglia
iniziale contiene un aliante e un lampeggiatore.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `mondo` | `char[][]` | 8 × (12 + 1) | Generazione attuale |
| `appoggio` | `char[][]` | 8 × (12 + 1) | Generazione successiva in costruzione |
| `generazione` | `int` | — | Contatore del ciclo principale |

| Funzione | Compito |
|----------|---------|
| `vicine_vive` | Conta le vive tra le 8 vicine con gli spostamenti `dr`, `dc` |
| `prossima_generazione` | Scrive la nuova generazione in `nuova` leggendo solo da `attuale`, poi la ricopia |
| `stampa` | Stampa la griglia con il numero di celle vive |
| `conta_vive` | Conta le celle vive |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Calcolo di una generazione

**a) Input** – la griglia `mondo`

**b) Output** – `mondo` aggiornata alla generazione successiva

**c) Variabili di supporto** – `appoggio`, `n` (vicine vive)

**d) Vincoli** – le regole si applicano tutte allo **stesso** istante: non si
può scrivere in `mondo` mentre lo si legge (vedi `030`)

**e) Assunzioni** – le celle fuori dalla griglia sono considerate morte

**f) Algoritmo in linguaggio naturale**
1. Per ogni cella contare le vicine vive in `attuale`.
2. Se la cella è viva: in `nuova` resta viva con 2 o 3 vicine, altrimenti muore.
3. Se la cella è morta: in `nuova` nasce con esattamente 3 vicine.
4. Scrivere il `'\0'` a fine riga di `nuova`.
5. Copiare `nuova` in `attuale`.

### Caso d'uso 2 – Conteggio delle vicine

**a) Input** – griglia, riga `r`, colonna `c`

**b) Output** – numero da 0 a 8

**c) Variabili di supporto** – `dr`, `dc`, `rv`, `cv`

**d) Vincoli** – escludere `(0, 0)` e le celle fuori dalla griglia

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – due cicli su `dr` e `dc` da -1 a
+1, sommando le celle vive valide.

### Caso d'uso 3 – Simulazione di 4 generazioni

**a) Input** – nessuno (configurazione iniziale fissa)

**b) Output** – le 5 griglie (generazione 0–4) con il numero di celle vive

**c) Variabili di supporto** – `generazione`

**d) Vincoli** – nessuno

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale**
1. Stampare la generazione 0.
2. Ripetere 4 volte: calcolare la generazione successiva e stamparla.
3. Osservare che l'aliante si è spostato di una cella in diagonale e il
   lampeggiatore è tornato nella posizione iniziale.
