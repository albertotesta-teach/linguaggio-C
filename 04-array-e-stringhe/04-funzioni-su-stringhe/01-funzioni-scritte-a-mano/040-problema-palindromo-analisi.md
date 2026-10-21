# Analisi – 040-problema-palindromo.c

## 1. Problema

Un gioco di parole per una classe chiede di riconoscere le frasi palindrome,
cioè leggibili allo stesso modo nei due sensi. Spazi, punteggiatura e
differenza tra maiuscole e minuscole non contano. Il programma esamina una
frase alla volta finché l'utente non scrive "fine" e alla fine riporta
quante frasi erano palindrome.

## 2. Analisi

### Input

| Variabile | Tipo     | Dimensione | Descrizione                                  |
|-----------|----------|------------|----------------------------------------------|
| `frase`   | `char[]` | 80         | Una frase per riga; "fine" termina           |

### Output
- Per ogni frase: le sole lettere in minuscolo, la stessa stringa al
  contrario e l'esito ("PALINDROMA", "non palindroma" oppure "nessuna
  lettera da esaminare");
- alla fine il numero di frasi esaminate e di palindrome.

### Vincoli
- Si confrontano solo le lettere, convertite in minuscolo: spazi,
  punteggiatura e cifre vengono scartati
- Una frase è palindroma se la stringa pulita coincide con la sua inversione
- Una frase senza lettere non è classificata
- Il ciclo termina con la parola esatta "fine" (in minuscolo) oppure con la
  fine dell'input
- Tutte le funzioni sulle stringhe sono scritte a mano, senza
  `<string.h>`: `confronta` restituisce 0 se le stringhe sono uguali
- Una riga più lunga di 79 caratteri viene troncata e il resto viene
  scartato, così non diventa la frase successiva

### Assunzioni
- Le frasi non contengono lettere accentate

### Variabili di supporto

| Variabile    | Tipo     | Dimensione | Descrizione                         |
|--------------|----------|------------|-------------------------------------|
| `pulita`     | `char[]` | 80         | Solo le lettere, in minuscolo       |
| `rovesciata` | `char[]` | 80         | `pulita` al contrario               |
| `letta`      | `int`    | —          | 0 se l'input è terminato            |
| `esaminate`, `palindrome` | `int` | — | Contatori                       |

| Funzione | Descrizione |
|---|---|
| `int leggi_riga(char s[], int dim)` | `fgets`, rimozione del `'\n'`, scarto dei caratteri in eccesso |
| `void pulisci(char dest[], const char sorg[])` | Copia solo le lettere, in minuscolo |
| `void inverti(char dest[], const char sorg[])` | Scrive la stringa al contrario |
| `int confronta(const char a[], const char b[])` | 0 se uguali |
| `int lunghezza(const char s[])` | Caratteri fino a `'\0'` |
| `char minuscola(char c)`, `int e_lettera(char c)` | Operazioni sul carattere |

### Algoritmo in linguaggio naturale
1. Leggere una frase.
2. Finché l'input non è terminato e la frase è diversa da "fine":
   a. ricavare la versione pulita e la sua inversione e stamparle;
   b. se la versione pulita è vuota segnalarlo; altrimenti confrontarla con
      l'inversione, stampare l'esito e contare le palindrome;
   c. contare la frase e leggere la successiva.
3. Stampare il riepilogo.

## 3. Casi di test

Si inserisce una sequenza di frasi, una per riga.

### Test 1 – Sessione completa
- **Input:** `I topi non avevano nipoti`, `Ciao a tutti`, `Anna`,
  `!!! ...`, `FINE`, `fine`
- **Output atteso:**
  - `itopinonavevanonipoti` → `PALINDROMA` (maiuscola e spazi non contano)
  - `ciaoatutti` / `ittutaoaic` → `non palindroma`
  - `anna` → `PALINDROMA`
  - `!!! ...` → `nessuna lettera da esaminare`
  - `FINE` non termina il programma: `fine` / `enif` → `non palindroma`
  - `Frasi esaminate: 5, palindrome: 2`

### Test 2 – Fine immediata
- **Input:** `fine`
- **Output atteso:** `Frasi esaminate: 0, palindrome: 0`
