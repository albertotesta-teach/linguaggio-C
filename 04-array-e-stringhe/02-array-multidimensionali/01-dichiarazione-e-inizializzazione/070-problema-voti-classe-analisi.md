# Analisi – 070-problema-voti-classe.c

## 1. Problema

Per lo scrutinio il coordinatore prepara il tabellone dei voti di 6 studenti
in 4 materie. Il programma deve stampare il tabellone con media e numero di
insufficienze di ogni studente, segnalare chi ha almeno un debito e contare
gli insufficienti di ogni materia.

## 2. Analisi

### Input
Nessun input da tastiera: i dati sono inizializzati nel codice.

| Variabile  | Tipo       | Dimensione | Descrizione                                 |
|------------|------------|------------|---------------------------------------------|
| `voti`     | `int[][]`  | 6 × 4      | Riga = studente, colonna = materia          |
| `studenti` | `char[][]` | 6 × 16     | Nome dello studente, parallelo alle righe   |
| `materie`  | `char[][]` | 4 × 12     | Nome della materia, parallelo alle colonne  |

### Output
- Il tabellone: per ogni studente i quattro voti, la media (due decimali),
  il numero di insufficienze e la nota "<- debito" se ne ha almeno una;
- il numero di studenti con almeno un'insufficienza;
- per ogni materia il numero di studenti insufficienti.

### Vincoli
- Un voto è insufficiente se è **minore** di `SUFFICIENZA` (6): il 6 è
  sufficiente
- Media e insufficienze di uno studente si calcolano scorrendo una
  **riga**; gli insufficienti di una materia scorrendo una **colonna**
- `studenti` descrive le righe e si usa all'inizio di ogni riga; `materie`
  descrive le colonne e si usa nell'intestazione
- La media si calcola con una divisione reale

### Assunzioni
- I voti sono interi tra 1 e 10

### Variabili di supporto

| Variabile               | Tipo  | Descrizione                                  |
|-------------------------|-------|----------------------------------------------|
| `somma`, `insufficienze`| `int` | Accumulatore e contatore della riga corrente |
| `studenti_con_debito`   | `int` | Studenti con almeno un'insufficienza         |
| `insufficienti_materia` | `int` | Contatore della colonna corrente             |
| `SUFFICIENZA`           | `#define` | 6                                        |

### Algoritmo in linguaggio naturale
1. Stampare l'intestazione con i nomi delle materie.
2. Per ogni studente: stampare il nome e i voti, sommandoli e contando
   quelli minori di 6; stampare media e insufficienze; se ce n'è almeno
   una aggiungere "<- debito" e contare lo studente.
3. Stampare il numero di studenti con debito.
4. Per ogni materia contare, scorrendo la colonna, i voti minori di 6 e
   stampare il risultato.

## 3. Casi di test

Il programma non legge dati: si esegue una volta e si confronta con l'output
atteso.

### Test 1 – Tabellone
- **Cosa si verifica:** il 6 non è un'insufficienza (Bianchi Sara ha un 6 e
  nessun debito)
- **Output atteso:**
```
  Bianchi Sara               7           6           8           9    7.50      0
  Colombo Luca               5           4           6           7    5.50      2   <- debito
  Esposito Ilaria            8           9           7           8    8.00      0
  Ferri Matteo               6           5           5           6    5.50      2   <- debito
  Galli Chiara               9           8           9          10    9.00      0
  Marini Davide              6           6           4           7    5.75      1   <- debito

Studenti con almeno un'insufficienza: 3 su 6
```

### Test 2 – Insufficienze per materia
- **Cosa si verifica:** lo scorrimento per colonne
- **Output atteso:**
```
  Italiano    : 1
  Matematica  : 2
  Inglese     : 2
  Informatica : 0
```
