# Analisi – 040-problema-orario-scolastico.c

## 1. Problema

L'orario settimanale di una classe va rappresentato come una tabella di
5 giorni per 6 ore, in cui ogni cella contiene il codice della materia.
Il programma deve stampare l'orario in forma leggibile, calcolare le ore
settimanali di ogni materia e indicare il giorno con più ore di Informatica.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `orario` | `int[][]` | 5 × 6 | Riga = giorno, colonna = ora; il valore è il codice materia |
| `materia` | `int` | — | Codice in esame durante il conteggio (da 1 a 7) |
| `ore_materia` | `int` | — | Contatore delle celle con quel codice |
| `ore_info_giorno` | `int` | — | Ore di Informatica in un giorno |
| `max_ore_info`, `giorno_max_info` | `int` | — | Massimo e indice del giorno corrispondente |

Costanti: `GIORNI`, `ORE`, `NUM_MATERIE`, `INFORMATICA`.

I codici numerici rendono la matrice compatta; le sigle e i nomi vengono
stampati con uno `switch` sul codice, perché gli array di stringhe non sono
ancora stati introdotti.

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Stampa dell'orario

**a) Input** – matrice `orario` inizializzata nel codice

**b) Output** – tabella con le sigle (ITA, MAT, ...) e i giorni abbreviati

**c) Variabili di supporto** – `giorno`, `ora`

**d) Vincoli** – un codice non previsto viene stampato come `???`

**e) Assunzioni** – ogni ora contiene esattamente una materia

**f) Algoritmo in linguaggio naturale**
1. Per ogni giorno: stampare l'abbreviazione del giorno.
2. Per ogni ora del giorno: stampare la sigla corrispondente al codice.
3. Andare a capo alla fine della riga.

### Caso d'uso 2 – Ore settimanali per materia

**a) Input** – matrice `orario`

**b) Output** – per ogni materia il numero di ore, e il totale (30)

**c) Variabili di supporto** – `materia`, `ore_materia`, `totale_ore`

**d) Vincoli** – il totale deve coincidere con `GIORNI × ORE`: è un controllo
di correttezza dei dati

**e) Assunzioni** – i codici vanno da 1 a 7

**f) Algoritmo in linguaggio naturale**
1. Per ogni codice di materia da 1 a 7: azzerare il contatore.
2. Scorrere tutta la matrice e contare le celle uguali al codice.
3. Stampare il nome della materia e il conteggio; aggiungerlo al totale.

### Caso d'uso 3 – Giorno con più ore di Informatica

**a) Input** – matrice `orario`

**b) Output** – "Giorno con piu' ore di Informatica: mercoledi' (3 ore)"

**c) Variabili di supporto** – `ore_info_giorno`, `max_ore_info`, `giorno_max_info`

**d) Vincoli** – in caso di parità vince il primo giorno trovato (confronto `>`)

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale**
1. Per ogni giorno: contare le celle della riga uguali a `INFORMATICA`.
2. Se il conteggio supera il massimo, aggiornare massimo e giorno.
3. Stampare il giorno trovato.
