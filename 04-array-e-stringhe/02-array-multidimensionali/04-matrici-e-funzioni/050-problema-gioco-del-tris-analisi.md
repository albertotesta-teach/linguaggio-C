# Analisi – 050-problema-gioco-del-tris.c

## 1. Problema

Realizzare il gioco del tris per due giocatori sulla console. I giocatori
inseriscono a turno riga e colonna (da 1 a 3); il programma rifiuta le mosse
non valide, disegna la griglia dopo ogni mossa e termina con la vittoria di
un giocatore o con il pareggio a griglia piena.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `griglia` | `char[][]` | 3 × 3 | `' '` vuota, `'X'`, `'O'` |
| `giocatore` | `char` | — | Simbolo del giocatore di turno |
| `vince` | `char` | — | Vincitore o `' '` |
| `riga`, `colonna` | `int` | — | Mossa inserita (da 1 a 3) |

| Funzione | Compito |
|----------|---------|
| `svuota` | Porta tutte le caselle a vuota |
| `stampa` | Disegna la griglia con le coordinate |
| `mossa_valida` | Indici nei limiti e casella vuota |
| `vincitore` | Controlla 3 righe, 3 colonne, 2 diagonali |
| `griglia_piena` | Nessuna casella vuota |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Vittoria sulla diagonale

**a) Input** – X: 2 2, O: 1 1, X: 1 3, O: 2 2 (occupata), O: 3 3, X: 3 1

**b) Output** – griglia dopo ogni mossa, "Mossa non valida" per 2 2,
"Vince il giocatore X!"

**c) Variabili di supporto** – `vince`, `giocatore`

**d) Vincoli** – il turno cambia solo dopo una mossa valida

**e) Assunzioni** – l'utente inserisce due interi

**f) Algoritmo in linguaggio naturale**
1. Svuotare e stampare la griglia; `giocatore = 'X'`, `vince = ' '`.
2. Finché nessuno ha vinto e la griglia non è piena: leggere la mossa.
3. Se valida: scrivere il simbolo, stampare, calcolare il vincitore, cambiare turno.
4. Altrimenti segnalare la mossa non valida.
5. Al termine stampare vincitore o pareggio.

### Caso d'uso 2 – Pareggio

**a) Input** – nove mosse senza tris

**b) Output** – "Pareggio."

**c) Variabili di supporto** – `griglia_piena`

**d) Vincoli** – il ciclo termina per la seconda parte della condizione

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – come nel caso 1.

### Caso d'uso 3 – Verifica del vincitore

**a) Input** – griglia corrente

**b) Output** – `'X'`, `'O'` oppure `' '`

**c) Variabili di supporto** – `esito`

**d) Vincoli** – una casella vuota non può formare un tris (controllo `!= VUOTA`);
una sola `return`, con i controlli fermati dal flag nella condizione del ciclo

**e) Assunzioni** – griglia 3 × 3

**f) Algoritmo in linguaggio naturale**
1. Per i da 0 a 2, finché nessun vincitore: controllare la riga i e la colonna i.
2. Se ancora nessuno e la casella centrale non è vuota: controllare le diagonali.
3. Restituire l'esito.
