# Analisi – 060-problema-indovina-numero.c

## 1. Problema

Il computer sceglie a caso un numero segreto tra 1 e 100. Il giocatore ha al
massimo 7 tentativi per indovinarlo; dopo ogni tentativo il programma dice
se la proposta è troppo alta o troppo bassa. Il gioco termina quando il
numero è indovinato oppure quando i tentativi sono esauriti.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `segreto` | `int` | Numero da indovinare |
| `proposta` | `int` | Numero proposto dal giocatore |
| `tentativi` | `int` | Tentativi validi usati |
| `indovinato` | `int` (0/1) | Flag che registra la vittoria |

Costanti: `MINIMO`, `MASSIMO`, `MAX_TENTATIVI`.

Il numero segreto si ottiene con `MINIMO + rand() % (MASSIMO - MINIMO + 1)`;
`srand(time(NULL))` inizializza il generatore con l'ora corrente, così il
numero cambia a ogni partita.

Il ciclo ha **due** motivi per terminare. Invece di uscire con `break`, la
condizione di continuazione li contiene entrambi:
`!indovinato && tentativi < MAX_TENTATIVI`.

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Vittoria

**a) Input** – proposte successive che si avvicinano al numero

**b) Output** – i suggerimenti "Troppo basso" / "Troppo alto" e il messaggio
"Indovinato! Il numero era N (k tentativi)."

**c) Variabili di supporto** – `indovinato`, `tentativi`

**d) Vincoli** – il messaggio finale si sceglie dopo il ciclo guardando il flag

**e) Assunzioni** – l'utente inserisce numeri interi

**f) Algoritmo in linguaggio naturale**
1. Inizializzare il generatore casuale e scegliere `segreto`.
2. Porre `tentativi = 0` e `indovinato = 0`.
3. Finché non è indovinato e i tentativi sono meno di `MAX_TENTATIVI`:
   a. leggere la proposta;
   b. se è fuori da [1, 100] segnalarlo senza contare il tentativo;
   c. altrimenti incrementare `tentativi` e confrontare: uguale → `indovinato = 1`;
      minore → "Troppo basso"; maggiore → "Troppo alto".
4. Se `indovinato` vale 1 stampare la vittoria, altrimenti rivelare il numero.

### Caso d'uso 2 – Tentativi esauriti

**a) Input** – 7 proposte sbagliate

**b) Output** – "Tentativi esauriti. Il numero era N."

**c) Variabili di supporto** – `tentativi`

**d) Vincoli** – il ciclo termina per la seconda parte della condizione

**e) Assunzioni** – nessuna in più

**f) Algoritmo in linguaggio naturale** – come nel caso 1.

### Caso d'uso 3 – Proposta fuori intervallo

**a) Input** – per esempio 150

**b) Output** – "Inserisci un numero tra 1 e 100." senza consumare il tentativo

**c) Variabili di supporto** – nessuna

**d) Vincoli** – `tentativi` si incrementa solo nel ramo della proposta valida

**e) Assunzioni** – nessuna in più

**f) Algoritmo in linguaggio naturale** – come nel caso 1, passo 3b.

### Osservazione

Con la strategia di dimezzare ogni volta l'intervallo (ricerca binaria)
bastano al massimo 7 tentativi per 100 numeri, perché 2⁷ = 128 ≥ 100.
