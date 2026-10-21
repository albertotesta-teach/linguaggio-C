# Analisi – 080-problema-mappa-del-tesoro.c

## 1. Problema

Su un'isola rappresentata da una griglia di caratteri (`~` mare, `.`
spiaggia, `^` bosco, `#` rocce, `$` tesoro) un pirata ha lasciato le
istruzioni per il tesoro come elenco di tratti: per ogni tratto una direzione
(N, S, E, O) e un numero di passi. Partendo dal relitto `X`, il programma
percorre i tratti tracciando il cammino con `o`, si ferma se le istruzioni
portano in mare, sulle rocce o fuori dalla mappa e infine dice se nella cella
raggiunta c'è il tesoro.

## 2. Analisi

### Input
Nessun input da tastiera: la mappa e le istruzioni sono inizializzate nel
codice.

| Variabile   | Tipo       | Dimensione   | Descrizione                                 |
|-------------|------------|--------------|---------------------------------------------|
| `isola`     | `char[][]` | 8 × (14 + 1) | Mappa dell'isola                            |
| `direzioni` | `char[]`   | 4            | Direzione di ogni tratto: E, S, E, N        |
| `passi`     | `int[]`    | 4            | Passi di ogni tratto: 5, 4, 1, 1 (parallelo a `direzioni`) |

### Output
- La mappa iniziale e la posizione del relitto;
- per ogni tratto direzione e numero di passi ("passo" al singolare);
- se il cammino si blocca, il motivo ("Fuori dalla mappa!" oppure
  "Ostacolo in riga r, colonna c: istruzioni sbagliate.");
- la posizione finale, l'esito ("TESORO TROVATO!" oppure "Qui non c'e'
  nessun tesoro.", solo se il cammino non si è bloccato) e la mappa con la
  traccia.

### Vincoli
- La partenza si cerca scorrendo la mappa fino alla `X`; poiché i `for`
  incrementano gli indici anche dopo il ritrovamento, alla fine si torna
  indietro di una riga e una colonna
- Ogni tratto si percorre un passo alla volta: un passo è possibile solo se
  la cella di arrivo è dentro la mappa e non è mare né roccia; il controllo
  dei limiti viene prima dell'accesso alla cella
- Al primo passo impossibile il cammino si ferma: un flag nella condizione
  di entrambi i cicli interrompe sia il tratto sia i tratti successivi
  (niente `break`)
- La traccia `o` si scrive nella cella che si lascia, tranne sul relitto; la
  cella finale mantiene il suo simbolo, così si può verificare il tesoro
- Le posizioni stampate sono indici della matrice, quindi partono da 0

### Assunzioni
- La mappa contiene un solo relitto `X`
- Le direzioni sono solo N, S, E, O (qualsiasi altro carattere è trattato
  come O)

### Variabili di supporto

| Variabile   | Tipo  | Descrizione                                          |
|-------------|-------|------------------------------------------------------|
| `r`, `c`    | `int` | Posizione attuale                                    |
| `dr`, `dc`  | `int` | Spostamento di un passo nel tratto corrente          |
| `bloccato`  | `int` | 1 quando un passo è impossibile                      |
| `trovato_partenza` | `int` | Ferma la ricerca della `X`                    |
| `RIGHE`, `COLONNE`, `TRATTI` | `#define` | 8, 14, 4                    |

### Algoritmo in linguaggio naturale
1. Cercare la `X` nella mappa e correggere gli indici; stampare mappa e
   partenza.
2. Per ogni tratto, finché il cammino non è bloccato:
   a. scegliere `dr`, `dc` con uno `switch` sulla direzione e stampare il
      tratto;
   b. per ogni passo, finché non è bloccato: se la cella di arrivo è fuori
      dalla mappa o è mare o roccia, bloccare e stampare il motivo;
      altrimenti lasciare la traccia e spostarsi.
3. Stampare la posizione finale, l'esito se il cammino non è bloccato, e la
   mappa.

## 3. Casi di test

Il programma non legge dati: si esegue con le istruzioni del codice; i test
2 e 3 richiedono di modificare l'array `passi` e ricompilare.

### Test 1 – Tesoro trovato
- **Output atteso:**
```
Partenza dal relitto in riga 1, colonna 2

Tratto 1: 5 passi verso E
Tratto 2: 4 passi verso S
Tratto 3: 1 passo verso E
Tratto 4: 1 passo verso N

Posizione finale: riga 4, colonna 8
TESORO TROVATO!
  ~~~~~~~~~~~~~~
  ~~Xooooo.~~~~~
  ~~...^^o..~~~~
  ~~..^^#o^..~~~
  ~~~..^^o$..~~~
  ~~~....oo.~~~~
  ~~~~~...~~~~~~
  ~~~~~~~~~~~~~~
```

### Test 2 – Istruzioni che portano in mare
- **Cosa si verifica:** il cammino si ferma al primo ostacolo e i tratti
  successivi non vengono eseguiti
- **Procedura:** porre il primo tratto a 8 passi
- **Output atteso:** `Tratto 1: 8 passi verso E`,
  `Ostacolo in riga 1, colonna 9: istruzioni sbagliate.`,
  `Posizione finale: riga 1, colonna 8`, senza esito sul tesoro

### Test 3 – Arrivo nel posto sbagliato
- **Procedura:** porre il secondo tratto a 3 passi
- **Output atteso:** `Posizione finale: riga 3, colonna 8` e
  `Qui non c'e' nessun tesoro.`
