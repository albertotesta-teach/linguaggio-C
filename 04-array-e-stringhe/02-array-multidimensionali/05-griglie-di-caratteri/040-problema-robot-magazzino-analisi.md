# Analisi – 040-problema-robot-magazzino.c

## 1. Problema

In un magazzino automatico un robot deve raccogliere dei pacchi. La pianta è
una griglia di caratteri con scaffali (`#`), corridoi (`.`), pacchi (`P`) e il
robot (`R`). L'operatore guida il robot con i comandi N, S, E, O; il robot non
può uscire dalla mappa né attraversare gli scaffali. Entrando in una cella con
un pacco lo raccoglie. La sessione termina con Q oppure quando tutti i pacchi
sono stati raccolti; alla fine si stampano mosse e pacchi raccolti.

## 2. Analisi

### Input

| Variabile | Tipo   | Descrizione                                            |
|-----------|--------|--------------------------------------------------------|
| `comando` | `char` | N (su), S (giù), E (destra), O (sinistra), Q (fine); anche in minuscolo |

La pianta iniziale è inizializzata nel codice: il robot parte dall'angolo in
alto a sinistra e ci sono 3 pacchi.

### Output
- Il numero di pacchi da raccogliere e la mappa iniziale;
- per i comandi che non spostano il robot il motivo: "Bordo del magazzino",
  "Scaffale" oppure "Comando sconosciuto."; per ogni pacco raccolto
  "Pacco raccolto! (n)";
- alla fine la mappa, le mosse eseguite, i pacchi raccolti e rimasti, e
  "Missione completata!" se non resta nessun pacco.

### Vincoli
- Lo spostamento si esprime con due variabili `dr`, `dc` (−1, 0, +1) scelte
  da uno `switch`: la verifica della cella di arrivo è la stessa per tutte
  le direzioni
- Il robot si sposta solo se la cella di arrivo è dentro la mappa e non è
  uno scaffale; il controllo dei limiti viene **prima** dell'accesso alla
  cella
- Si contano solo le mosse effettivamente eseguite
- Spostandosi il robot lascia un corridoio nella cella di partenza
- La sessione termina con Q oppure appena l'ultimo pacco è raccolto; in
  quel caso non viene chiesto un altro comando
- Ogni riga della mappa ha `COLONNE + 1` caratteri, perché è inizializzata
  con una stringa che contiene anche `'\0'`
- A fine input (EOF) il programma si comporta come il comando Q

### Assunzioni
- La mappa contiene un solo robot

### Variabili di supporto

| Variabile            | Tipo       | Dimensione   | Descrizione                         |
|----------------------|------------|--------------|-------------------------------------|
| `mappa`              | `char[][]` | 6 × (10 + 1) | Pianta del magazzino                |
| `r_robot`, `c_robot` | `int`      | —            | Posizione attuale del robot         |
| `r_nuova`, `c_nuova` | `int`      | —            | Cella di arrivo da verificare       |
| `dr`, `dc`           | `int`      | —            | Spostamento scelto dal comando      |
| `raccolti`, `pacchi_rimasti`, `mosse` | `int` | — | Contatori                     |

| Funzione | Descrizione |
|---|---|
| `void stampa_mappa(const char m[][COLONNE + 1])` | Stampa le celle di ogni riga |
| `int conta_pacchi(const char m[][COLONNE + 1])` | Conta le celle `'P'` |

### Algoritmo in linguaggio naturale
1. Contare i pacchi e stampare la mappa; leggere il primo comando.
2. Finché il comando non è Q e restano pacchi:
   a. porre `dr = dc = 0` e impostarli secondo il comando, oppure stampare
      "Comando sconosciuto.";
   b. se c'è uno spostamento calcolare la cella di arrivo: se è fuori dalla
      mappa o è uno scaffale annullare il movimento; altrimenti, se contiene
      un pacco raccoglierlo, spostare il robot e contare la mossa;
   c. se restano pacchi leggere il comando successivo.
3. Stampare la mappa e il riepilogo.

## 3. Casi di test

Si esegue il programma con la sequenza di comandi indicata.

### Test 1 – Movimenti bloccati e due pacchi raccolti
- **Input:** `N`, `E`, `E`, `E`, `E`, `S`, `S`, `O`, `X`, `S`, `S`, `E`, `Q`
- **Output atteso:**
  - `N` alla partenza → `Bordo del magazzino: movimento annullato.`
  - il quarto `E` → `Scaffale: movimento annullato.`
  - dopo `S S O` → `Pacco raccolto! (1)`
  - `X` → `Comando sconosciuto.`
  - dopo `S S E` → `Pacco raccolto! (2)`
  - alla fine `Mosse eseguite: 9, pacchi raccolti: 2, rimasti: 1`

### Test 2 – Missione completata
- **Cosa si verifica:** la sessione termina da sola all'ultimo pacco
- **Input:** `E E E S S O S S E E E N N N N E E E E`
- **Output atteso:**
```
  ....#....R
  .##.#.##..
  .#....#...
  .#.##.#.##
  ......#...
  ####......

Mosse eseguite: 19, pacchi raccolti: 3, rimasti: 0
Missione completata!
```

### Test 3 – Fine dell'input senza Q
- **Cosa si verifica:** la chiusura senza ciclo infinito
- **Input:** `E`, poi fine dell'input (Ctrl+D, o input da pipe)
- **Output atteso:**
```
Comando (N S E O, Q = fine): Comando (N S E O, Q = fine): 
...
Mosse eseguite: 1, pacchi raccolti: 0, rimasti: 3
```
