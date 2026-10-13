# Analisi – 050-problema-tabella-dei-voti.c

## 1. Problema

Il tabellone dello scrutinio ha una riga per studente e una colonna per materia; il numero di righe e di colonne si sceglie all'avvio. Si alloca un unico blocco di righe × colonne double con le righe una dopo l'altra: l'elemento (r, c) sta in tab[r × colonne + c]. Il programma stampa il tabellone con le medie per studente e per materia e lo studente migliore.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `tab` | `double *` | righe × colonne (heap) | Tutti i voti in un blocco |
| `righe`, `colonne` | `int` | — | Studenti (1-30) e materie (1-6) |
| `media_migliore`, `migliore` | `double`, `int` | — | Studente con la media più alta |

| Funzione | Compito |
|----------|---------|
| `crea_tabella(righe, colonne)` | Una malloc per tutto il tabellone |
| `indice(r, c, colonne)` | Posizione dell'elemento (r, c) |
| `leggi_tabella(tab, righe, colonne)` | Voti riga per riga; 0 se un voto manca o è fuori da 1-10 |
| `stampa_tabella(tab, righe, colonne)` | Tabellone, medie e studente migliore |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Tabellone completo

**a) Input** – `3 4`, poi tre righe di 4 voti

**b) Output** – medie 7.62, 5.88, 8.62; medie per materia; "Media piu' alta: studente 3 con 8.62"

**c) Variabili di supporto** – `somma`

**d) Vincoli** – voti da 1 a 10

**e) Assunzioni** – a parità di media vince il primo

**f) Algoritmo in linguaggio naturale** – elemento (r, c) in tab[indice(r, c, colonne)]; somme per riga e per colonna.

### Caso d'uso 2 – Dimensioni non valide

**a) Input** – `2 7`

**b) Output** – "Dimensioni non valide (studenti 1-30, materie 1-6)."

**c) Variabili di supporto** – —

**d) Vincoli** – al massimo 6 materie

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – nessuna allocazione.

### Caso d'uso 3 – Voto non valido

**a) Input** – `2 2`, poi `7 12`

**b) Output** – "Voti mancanti o non validi."

**c) Variabili di supporto** – `ok`

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – leggi_tabella si ferma al primo voto errato; il blocco si libera comunque.
