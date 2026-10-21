# Analisi – 060-problema-gioco-della-vita.c

## 1. Problema

Simulare il "gioco della vita" di Conway su una griglia 8 × 12 per 4
generazioni. Ogni cella è viva (`#`) o morta (`.`); a ogni generazione tutte
le celle cambiano contemporaneamente in base al numero di vicine vive:
sopravvive una cella viva con 2 o 3 vicine, nasce una cella morta con
esattamente 3 vicine, in tutti gli altri casi la cella è morta. La griglia
iniziale contiene un aliante e un lampeggiatore.

## 2. Analisi

### Input
Nessun input da tastiera: la griglia iniziale è inizializzata nel codice.

| Variabile | Tipo       | Dimensione    | Descrizione                      |
|-----------|------------|---------------|----------------------------------|
| `mondo`   | `char[][]` | 8 × (12 + 1)  | Generazione attuale              |

### Output
La griglia della generazione 0 e delle 4 successive, ciascuna con il numero
di celle vive, e un messaggio finale sullo spostamento dell'aliante.

### Vincoli
- Le vicine di una cella sono le 8 celle intorno; si scorrono con gli
  spostamenti `dr`, `dc` da −1 a +1, escludendo la cella stessa
  (`dr = dc = 0`)
- Le vicine fuori dalla griglia non si contano: i bordi non si collegano
- Tutte le celle cambiano **insieme**: la nuova generazione si costruisce in
  una seconda griglia leggendo solo da quella attuale, poi si ricopia;
  aggiornando una sola griglia le celle già modificate falserebbero il
  conteggio delle vicine
- Regole: viva con 2 o 3 vicine → viva; morta con 3 vicine → viva; ogni
  altro caso → morta
- Il terminatore `'\0'` di ogni riga si scrive anche nella griglia di
  appoggio

### Assunzioni
- Nessuna figura raggiunge i bordi nelle 4 generazioni simulate

### Variabili di supporto

| Variabile     | Tipo       | Dimensione   | Descrizione                         |
|---------------|------------|--------------|-------------------------------------|
| `appoggio`    | `char[][]` | 8 × (12 + 1) | Generazione successiva in costruzione |
| `generazione` | `int`      | —            | Contatore del ciclo principale      |
| `RIGHE`, `COLONNE`, `GENERAZIONI`, `VIVA`, `MORTA` | `#define` | — | 8, 12, 4, '#', '.' |

| Funzione | Descrizione |
|---|---|
| `int vicine_vive(const char g[][COLONNE + 1], int r, int c)` | Vive tra le 8 vicine |
| `void prossima_generazione(char attuale[][COLONNE + 1], char nuova[][COLONNE + 1])` | Calcola la nuova generazione e la ricopia in `attuale` |
| `void stampa(const char g[][COLONNE + 1], int generazione)` | Griglia con numero di vive |
| `int conta_vive(const char g[][COLONNE + 1])` | Celle vive |

### Algoritmo in linguaggio naturale
1. Stampare la generazione 0.
2. Per ogni generazione da 1 a 4:
   a. per ogni cella contare le vicine vive e scrivere in `nuova` lo stato
      dato dalle regole; chiudere ogni riga con `'\0'`;
   b. copiare `nuova` in `attuale`;
   c. stampare la griglia.
3. Stampare il messaggio finale.

## 3. Casi di test

Il programma non legge dati: si esegue una volta e si confronta con l'output
atteso.

### Test 1 – Lampeggiatore
- **Cosa si verifica:** le tre celle in riga diventano verticali nelle
  generazioni dispari e tornano orizzontali in quelle pari
- **Output atteso (righe 5–7, colonne 9–11):** generazione 1 e 3
  `.........#..` su tre righe; generazione 2 e 4 `........###.` sulla
  riga centrale

### Test 2 – Aliante dopo 4 generazioni
- **Cosa si verifica:** la figura torna uguale spostata di una cella in
  basso a destra, e le celle vive restano 8 in ogni generazione
- **Output atteso:**
```
Generazione 0 (celle vive: 8)
  .#..........
  ..#.........
  ###.........
  ............
...
Generazione 4 (celle vive: 8)
  ............
  ..#.........
  ...#........
  .###........
```

### Test 3 – Generazione intermedia
- **Output atteso:**
```
Generazione 1 (celle vive: 8)
  ............
  #.#.........
  .##.........
  .#..........
  .........#..
  .........#..
  .........#..
  ............
```
