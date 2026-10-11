# Analisi – 080-problema-mappa-del-tesoro.c

## 1. Problema

Su un'isola rappresentata da una griglia di caratteri (`~` mare, `.`
spiaggia, `^` bosco, `#` rocce, `$` tesoro) un pirata ha lasciato le
istruzioni per il tesoro come elenco di tratti: per ogni tratto una direzione
(N, S, E, O) e un numero di passi. Partendo dal relitto `X`, il programma
percorre i tratti tracciando il cammino con `o`, si ferma se le istruzioni
portano in mare, sulle rocce o fuori dalla mappa e infine dice se nella cella
raggiunta c'è il tesoro.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `isola` | `char[][]` | 8 × (14 + 1) | Mappa inizializzata con stringhe |
| `direzioni` | `char[]` | 4 | Direzione di ogni tratto |
| `passi` | `int[]` | 4 | Lunghezza di ogni tratto (parallelo a `direzioni`) |
| `r`, `c` | `int` | — | Posizione attuale |
| `dr`, `dc` | `int` | — | Spostamento di un passo nel tratto corrente |
| `bloccato`, `trovato_partenza` | `int` | — | Flag per fermare i cicli |

| Funzione | Compito |
|----------|---------|
| `stampa_mappa` | Stampa le `COLONNE` celle di ogni riga |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Ricerca della partenza

**a) Input** – mappa

**b) Output** – riga e colonna di `X`

**c) Variabili di supporto** – `trovato_partenza`

**d) Vincoli** – i due `for` si fermano con il flag; poiché l'incremento
avviene prima del controllo, al termine `r` e `c` vanno diminuiti di 1

**e) Assunzioni** – la mappa contiene esattamente una `X`

**f) Algoritmo in linguaggio naturale**
1. Scorrere righe e colonne finché non si trova `X`.
2. Riportare `r` e `c` sulla cella trovata.

### Caso d'uso 2 – Percorso corretto

**a) Input** – `direzioni = {E, S, E, N}`, `passi = {5, 4, 1, 1}`

**b) Output** – i tratti percorsi, "TESORO TROVATO!" e la mappa con la traccia

**c) Variabili di supporto** – `t`, `p`, `dr`, `dc`

**d) Vincoli** – si avanza di un passo alla volta per controllare ogni cella
attraversata, non solo quella di arrivo

**e) Assunzioni** – il tesoro è sulla cella finale, che non viene sovrascritta
dalla traccia

**f) Algoritmo in linguaggio naturale**
1. Per ogni tratto `t`: con uno `switch` su `direzioni[t]` impostare `dr`, `dc`.
2. Ripetere `passi[t]` volte: verificare la cella successiva; se è
   percorribile lasciare `o` nella cella attuale (tranne sulla `X`) e avanzare.
3. Al termine controllare se la cella raggiunta contiene `$`.

### Caso d'uso 3 – Istruzioni sbagliate

**a) Input** – un tratto che attraversa mare o rocce, o esce dalla mappa

**b) Output** – "Ostacolo in riga r, colonna c" oppure "Fuori dalla mappa!"

**c) Variabili di supporto** – `bloccato`

**d) Vincoli** – il flag ferma sia il ciclo dei passi sia quello dei tratti;
il controllo dei limiti precede l'accesso alla matrice

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – impostare `bloccato = 1` e stampare
la mappa con il percorso fatto fino all'ostacolo.

### Caso d'uso 4 – Nessun tesoro

**a) Input** – istruzioni percorribili che terminano su una cella senza `$`

**b) Output** – "Qui non c'e' nessun tesoro."

**c) Variabili di supporto** – `bloccato`, `isola[r][c]`

**d) Vincoli** – nessuno

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – controllo finale sul contenuto della cella.
