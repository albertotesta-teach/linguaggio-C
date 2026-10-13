# Analisi – 040-problema-voti-della-verifica.c

## 1. Problema

Il professore inserisce il numero di studenti presenti alla verifica e i loro voti. Il programma calcola la media, conta i voti sopra la media, elenca le insufficienze e trova il voto più alto e il più basso. Per confrontare ogni voto con la media servono due passate, quindi i voti vanno conservati: l'array si alloca con malloc dopo aver letto n, grande esattamente n voti.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `voti` | `double *` | n elementi (heap) | Voti della classe, allocati dopo aver letto n |
| `n`, `letti` | `int` | — | Studenti presenti e voti già inseriti |
| `somma`, `media` | `double` | — | Prima passata |
| `sopra`, `insufficienti` | `int` | — | Conteggi della seconda passata |
| `massimo`, `minimo` | `double` | — | Voti estremi |

| Funzione | Compito |
|----------|---------|
| `leggi_voto(studente, &voto)` | Richiede il voto finché è valido; 0 se l'input finisce |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Classe completa

**a) Input** – `6`, poi `7 5.5 8 6.5 9 4`

**b) Output** – media 6.67, insufficienze studenti 2 e 6, 3 sopra la media, massimo 9.0, minimo 4.0

**c) Variabili di supporto** – `somma`, `sopra`

**d) Vincoli** – n da 1 a 40

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – allocare n double; leggere i voti sommandoli; media = somma / n; seconda passata per i conteggi e gli estremi; free.

### Caso d'uso 2 – Voto non valido

**a) Input** – `11` oppure `abc`

**b) Output** – "voto non valido (da 1 a 10, anche mezzi voti)" e nuova richiesta

**c) Variabili di supporto** – `letto`

**d) Vincoli** – voti da 1 a 10, multipli di 0.5

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – se scanf non legge un numero si scarta la parola; il controllo voto × 2 intero esclude 7.3.

### Caso d'uso 3 – Numero di studenti non valido

**a) Input** – `0` oppure `45`

**b) Output** – "Numero non valido."

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – non si alloca nulla.

### Caso d'uso 4 – Input interrotto

**a) Input** – meno voti di n

**b) Output** – "Input terminato: mancano k voti."

**c) Variabili di supporto** – `letti`

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – leggi_voto restituisce 0 a fine input; il blocco si libera comunque.
