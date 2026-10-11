# Analisi – 040-problema-palindromo.c

## 1. Problema

Un gioco di parole per una classe chiede di riconoscere le frasi palindrome,
cioè leggibili allo stesso modo nei due sensi. Spazi, punteggiatura e
differenza tra maiuscole e minuscole non contano. Il programma esamina una
frase alla volta finché l'utente non scrive "fine" e alla fine riporta
quante frasi erano palindrome.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `frase` | `char[]` | 80 | Riga letta con `fgets` (può contenere spazi) |
| `pulita` | `char[]` | 80 | Solo le lettere, in minuscolo |
| `rovesciata` | `char[]` | 80 | `pulita` al contrario |
| `esaminate`, `palindrome` | `int` | — | Contatori per il riepilogo |

| Funzione | Compito |
|----------|---------|
| `leggi_riga` | `fgets`, rimozione del `'\n'`, scarto dei caratteri in eccesso |
| `pulisci` | Copia solo le lettere, convertite in minuscolo |
| `inverti` | Scrive la stringa in ordine inverso |
| `confronta` | Confronto alfabetico scritto a mano (0 = uguali) |
| `minuscola`, `e_lettera` | Operazioni sul singolo carattere |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Frase palindroma

**a) Input** – `I topi non avevano nipoti`

**b) Output** – `itopinonavevanonipoti`, la stessa stringa al contrario, "PALINDROMA"

**c) Variabili di supporto** – `pulita`, `rovesciata`

**d) Vincoli** – `pulita` e `rovesciata` devono terminare con `'\0'`

**e) Assunzioni** – frase di al massimo 79 caratteri; lettere senza accenti

**f) Algoritmo in linguaggio naturale**
1. Copiare in `pulita` solo le lettere della frase, in minuscolo.
2. Scrivere in `rovesciata` i caratteri di `pulita` dall'ultimo al primo.
3. Se le due stringhe sono uguali la frase è palindroma.

### Caso d'uso 2 – Frase non palindroma

**a) Input** – `Programmare in C`

**b) Output** – "non palindroma"

**c) Variabili di supporto** – esito di `confronta`

**d) Vincoli** – nessuno

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – come nel caso 1; il confronto
restituisce un valore diverso da 0.

### Caso d'uso 3 – Frase senza lettere

**a) Input** – `?!`

**b) Output** – "nessuna lettera da esaminare"

**c) Variabili di supporto** – `lunghezza(pulita)`

**d) Vincoli** – una stringa vuota sarebbe "palindroma" per definizione: il
caso va escluso prima del confronto

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – se `pulita` è vuota si segnala e non
si conta come palindroma.

### Caso d'uso 4 – Fine del programma

**a) Input** – `fine` (oppure fine dell'input)

**b) Output** – frasi esaminate e palindrome

**c) Variabili di supporto** – `letta`, contatori

**d) Vincoli** – il ciclo termina per la condizione, senza `break`

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – il ciclo continua finché la lettura
riesce e la frase è diversa da "fine"; poi si stampa il riepilogo.
