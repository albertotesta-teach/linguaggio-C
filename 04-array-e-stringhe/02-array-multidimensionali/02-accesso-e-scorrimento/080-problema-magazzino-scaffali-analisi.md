# Analisi – 080-problema-magazzino-scaffali.c

## 1. Problema

Un magazzino di ricambi ha 4 scaffali da 5 ripiani; ogni ripiano contiene un
articolo in una certa quantità. Ogni scaffale ha un codice e una propria
scorta minima. Il programma deve mostrare la situazione, elencare i ripiani
da rifornire e registrare una serie di prelievi controllandone la validità.

## 2. Analisi

### Input

| Variabile         | Tipo  | Descrizione                                  |
|-------------------|-------|----------------------------------------------|
| `scelta_scaffale` | `int` | Scaffale del prelievo (1–4); 0 termina       |
| `scelta_ripiano`  | `int` | Ripiano del prelievo (1–5)                   |
| `pezzi`           | `int` | Pezzi da prelevare                           |

Le giacenze, i codici degli scaffali e le scorte minime sono inizializzati
nel codice.

### Output
- La situazione: per ogni scaffale le quantità dei cinque ripiani, il totale
  e la scorta minima;
- l'elenco dei ripiani sotto la scorta minima del loro scaffale e il loro
  numero;
- per ogni prelievo l'esito: registrato (con i pezzi rimasti e l'avviso
  "(sotto scorta!)" se serve), "Posizione inesistente.",
  "Quantita' non valida." o "Giacenza insufficiente: disponibili N.";
- i pezzi prelevati in totale.

### Vincoli
- Ogni cella si confronta con la soglia della **sua riga**:
  `quantita[sc][rp] < scorta_minima[sc]`; un ripiano esattamente alla
  scorta minima non va rifornito
- I controlli del prelievo seguono un ordine: prima la posizione, poi la
  quantità (> 0), poi la giacenza; solo se tutti passano la quantità viene
  aggiornata
- La giacenza non diventa mai negativa; prelevare tutti i pezzi è ammesso
- Si sommano ai prelevati solo i prelievi registrati
- La serie termina con lo scaffale 0, letto in anticipo
- Scaffale, ripiano o pezzi non numerici si scartano e rendono non valida
  la richiesta; a fine input (EOF) il programma si comporta come lo
  scaffale 0

### Assunzioni
- Nessuna in particolare


### Variabili di supporto

| Variabile       | Tipo       | Dimensione | Descrizione                               |
|-----------------|------------|------------|-------------------------------------------|
| `quantita`      | `int[][]`  | 4 × 5      | Pezzi per scaffale e ripiano              |
| `codici`        | `char[][]` | 4 × 6      | Codice dello scaffale, parallelo alle righe |
| `scorta_minima` | `int[]`    | 4          | Soglia dello scaffale, parallela alle righe |
| `totale`, `sotto_scorta`, `prelevati` | `int` | — | Accumulatori e contatori   |
| `sc`, `rp`      | `int`      | —          | Indici ricavati dal prelievo              |

### Algoritmo in linguaggio naturale
1. Per ogni scaffale stampare le quantità, il totale e la scorta minima.
2. Per ogni cella sotto la scorta minima del suo scaffale stamparla e
   contarla; stampare il totale.
3. Leggere lo scaffale; finché è diverso da 0:
   a. leggere ripiano e pezzi e ricavare gli indici;
   b. se la posizione non esiste, oppure i pezzi non sono positivi, oppure
      superano la giacenza, stampare il messaggio corrispondente;
   c. altrimenti sottrarre i pezzi, sommarli ai prelevati e stampare i
      rimasti, con l'avviso se sono sotto scorta;
   d. leggere lo scaffale successivo.
4. Stampare i pezzi prelevati in totale.

## 3. Casi di test

Le giacenze sono fisse nel codice; i dati letti sono i prelievi, terminati
da `0`.

### Test 1 – Situazione e ripiani da rifornire
- **Input:** `0`
- **Output atteso:**
```
  SC-A        40    12    35     8    50     145           10
  SC-B        15    22     4    30    18      89           10
  SC-C        60    55    70     9    65     259           20
  SC-D         5    10    14    20     3      52            6

--- Ripiani sotto la scorta minima ---
  SC-A ripiano 4: 8 pezzi (minimo 10)
  SC-B ripiano 3: 4 pezzi (minimo 10)
  SC-C ripiano 4: 9 pezzi (minimo 20)
  SC-D ripiano 1: 5 pezzi (minimo 6)
  SC-D ripiano 5: 3 pezzi (minimo 6)
  Totale ripiani da rifornire: 5
```
- **Osservazione:** SC-D ripiano 2 ha 10 pezzi, sotto la soglia di SC-A ma
  sopra quella del suo scaffale (6): la soglia è per riga

### Test 2 – Prelievi di ogni tipo
- **Input:** `1 2 5`, `3 4 10`, `5 1 1`, `2 3 0`, `4 5 3`, `0`
- **Output atteso:**
  - `Prelievo registrato: SC-A ripiano 2, rimasti 7 (sotto scorta!)`
  - `Giacenza insufficiente: disponibili 9.`
  - `Posizione inesistente.`
  - `Quantita' non valida.`
  - `Prelievo registrato: SC-D ripiano 5, rimasti 0 (sotto scorta!)`
  - `Pezzi prelevati in totale: 8`

### Test 3 – Prelievo che arriva esattamente alla scorta minima
- **Cosa si verifica:** la soglia è esclusa
- **Input:** `1 1 30`, `0`
- **Output atteso:** `Prelievo registrato: SC-A ripiano 1, rimasti 10`, senza
  avviso; `Pezzi prelevati in totale: 30`

### Test 4 – Dati non numerici e fine dell'input
- **Cosa si verifica:** testo al posto dei numeri non blocca la registrazione
- **Input:** `uno`, `2`, `3`, poi fine dell'input (Ctrl+D, o input da pipe)
- **Output atteso:**
```
Scaffale (1-4): Ripiano (1-5): Pezzi da prelevare:   Posizione inesistente.
Scaffale (1-4): 
Pezzi prelevati in totale: 0
```
