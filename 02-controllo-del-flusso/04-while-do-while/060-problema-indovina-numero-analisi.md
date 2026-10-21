# Analisi – 060-problema-indovina-numero.c

## 1. Problema

Il computer sceglie a caso un numero segreto tra 1 e 100. Il giocatore ha al
massimo 7 tentativi per indovinarlo; dopo ogni tentativo il programma dice
se la proposta è troppo alta o troppo bassa. Il gioco termina quando il
numero è indovinato oppure quando i tentativi sono esauriti.

## 2. Analisi

### Input

| Variabile  | Tipo  | Significato                                     |
|------------|-------|-------------------------------------------------|
| `proposta` | `int` | Numero proposto dal giocatore a ogni tentativo  |

### Output
Dopo ogni proposta: "Troppo basso", "Troppo alto" oppure l'avviso di
proposta fuori intervallo. Al termine: "Indovinato! Il numero era N
(k tentativi)." oppure "Tentativi esauriti. Il numero era N."

### Vincoli
- Il numero segreto e le proposte valide sono compresi tra 1 e 100
- I tentativi validi sono al massimo 7; una proposta fuori intervallo non
  consuma un tentativo
- Il ciclo ha due motivi per terminare, entrambi nella condizione di
  continuazione: `!indovinato && tentativi < MAX_TENTATIVI`
- Il messaggio finale si sceglie dopo il ciclo guardando il flag

### Assunzioni
- L'utente inserisce numeri interi
- Il numero segreto cambia a ogni partita

### Variabili di supporto

| Variabile    | Tipo        | Significato                       |
|--------------|-------------|-----------------------------------|
| `segreto`    | `int`       | Numero da indovinare              |
| `tentativi`  | `int`       | Tentativi validi usati            |
| `indovinato` | `int` (0/1) | Flag che registra la vittoria     |

Costanti: `MINIMO`, `MASSIMO`, `MAX_TENTATIVI`.

Il numero segreto si ottiene con `MINIMO + rand() % (MASSIMO - MINIMO + 1)`;
`srand(time(NULL))` inizializza il generatore con l'ora corrente, così il
numero cambia a ogni partita.

### Algoritmo in linguaggio naturale
1. Inizializzare il generatore casuale e scegliere `segreto`.
2. Porre `tentativi = 0` e `indovinato = 0`.
3. Finché non è indovinato e i tentativi sono meno di `MAX_TENTATIVI`:
   a. leggere la proposta;
   b. se è fuori da [1, 100] segnalarlo senza contare il tentativo;
   c. altrimenti incrementare `tentativi` e confrontare: uguale → `indovinato = 1`;
      minore → "Troppo basso"; maggiore → "Troppo alto".
4. Se `indovinato` vale 1 stampare la vittoria, altrimenti rivelare il numero.

### Osservazione

Con la strategia di dimezzare ogni volta l'intervallo (ricerca binaria)
bastano al massimo 7 tentativi per 100 numeri, perché 2⁷ = 128 ≥ 100.

## 3. Casi di test

Il numero segreto è casuale, quindi l'output esatto cambia a ogni
esecuzione: per collaudare i casi si seguono i suggerimenti del programma
oppure, solo durante il collaudo, si stampa temporaneamente il segreto.

### Test 1 – Vittoria
- **Input:** proposte successive che si avvicinano al numero seguendo i
  suggerimenti (es. 50, 25, 37, …)
- **Output atteso:** i suggerimenti "Troppo basso" / "Troppo alto" e il
  messaggio "Indovinato! Il numero era N (k tentativi)."

### Test 2 – Tentativi esauriti
- **Cosa si verifica:** il ciclo termina per la seconda parte della condizione
- **Input:** 7 proposte valide sbagliate
- **Output atteso:** "Tentativi esauriti. Il numero era N."

### Test 3 – Proposta fuori intervallo
- **Cosa si verifica:** `tentativi` si incrementa solo nel ramo della
  proposta valida
- **Input:** per esempio 150
- **Output atteso:** "Inserisci un numero tra 1 e 100." senza consumare
  il tentativo
