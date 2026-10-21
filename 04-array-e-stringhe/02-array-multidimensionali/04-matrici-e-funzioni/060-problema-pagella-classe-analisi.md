# Analisi – 060-problema-pagella-classe.c

## 1. Problema

Allo scrutinio finale ogni studente riceve un esito in base al numero di
insufficienze: nessuna → ammesso, 1 o 2 → sospensione del giudizio, 3 o più
→ non ammesso. Il programma deve stampare la pagella di 6 studenti in 5
materie con media ed esito, le statistiche per materia e lo studente con la
media più alta, organizzando i calcoli in funzioni.

## 2. Analisi

### Input
Nessun input da tastiera: i dati sono inizializzati nel codice.

| Variabile  | Tipo       | Dimensione | Descrizione                          |
|------------|------------|------------|--------------------------------------|
| `voti`     | `int[][]`  | 6 × 5      | Riga = studente, colonna = materia   |
| `studenti` | `char[][]` | 6 × 16     | Nomi, paralleli alle righe           |
| `materie`  | `char[][]` | 5 × 16     | Nomi, paralleli alle colonne         |

### Output
- La pagella: per ogni studente i voti, la media e l'esito ("AMMESSO",
  "SOSPENSIONE (n)" con il numero di insufficienze, "NON AMMESSO");
- per ogni materia la media e il numero di insufficienze;
- lo studente con la media più alta.

### Vincoli
- Un voto è insufficiente se è minore di 6
- Esito: 0 insufficienze → ammesso; da 1 a `MAX_SOSPENSIONE` (2) →
  sospensione; 3 o più → non ammesso
- L'esito dipende dal **numero** di insufficienze, non dalla media
- Le funzioni per lo studente scorrono una **riga**, quelle per la materia
  una **colonna**; le medie si calcolano con una divisione reale
- A parità di media resta il primo studente trovato
- Nell'intestazione `%4.3s` stampa solo le prime 3 lettere della materia
  senza modificare la stringa

### Assunzioni
- I voti sono interi tra 1 e 10

### Variabili di supporto

| Variabile  | Tipo      | Descrizione                         |
|------------|-----------|-------------------------------------|
| `migliore` | `int`     | Studente con la media più alta      |
| `SUFFICIENZA`, `MAX_SOSPENSIONE` | `#define` | 6 e 2       |

| Funzione | Lavora su | Restituisce |
|---|---|---|
| `media_studente(voti, s)` | riga s | media |
| `insufficienze_studente(voti, s)` | riga s | conteggio |
| `media_materia(voti, n, m)` | colonna m | media |
| `insufficienze_materia(voti, n, m)` | colonna m | conteggio |
| `stampa_esito(insufficienze)` | — | stampa l'esito |

### Algoritmo in linguaggio naturale
1. Stampare l'intestazione con le sigle delle materie.
2. Per ogni studente stampare i voti e la media, stampare l'esito a partire
   dal numero di insufficienze e aggiornare lo studente migliore.
3. Per ogni materia stampare media e insufficienze della colonna.
4. Stampare lo studente con la media più alta.

## 3. Casi di test

Il programma non legge dati: si esegue una volta e si confronta con l'output
atteso.

### Test 1 – Pagelle ed esiti
- **Cosa si verifica:** tutti e tre gli esiti, compresi i casi limite di 1 e
  2 insufficienze; Ferri Matteo (3 insufficienze) non è ammesso anche con
  media 5.20
- **Output atteso:**
```
  Bianchi Sara       7   6   8   7   8    7.20  AMMESSO
  Colombo Luca       5   4   6   6   7    5.60  SOSPENSIONE (2)
  Esposito Ilaria    8   9   8   9   9    8.60  AMMESSO
  Ferri Matteo       5   4   5   6   6    5.20  NON AMMESSO
  Galli Chiara       6   6   7   5   7    6.20  SOSPENSIONE (1)
  Marini Davide      4   5   5   6   4    4.80  NON AMMESSO
```

### Test 2 – Statistiche per materia e studente migliore
- **Output atteso:**
```
  Italiano         5.83              3
  Matematica       5.67              3
  Inglese          6.50              2
  Informatica      6.50              1
  Sistemi          6.83              1

Media piu' alta: Esposito Ilaria (8.60)
```
