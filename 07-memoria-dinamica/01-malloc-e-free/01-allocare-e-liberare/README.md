# 01 – Allocare e liberare

## Concetto

Le variabili locali stanno nello **stack**: hanno una dimensione fissata
quando si compila e spariscono all'uscita dal blocco. Lo **heap** è la
memoria che il programma chiede mentre è in esecuzione:

```c
#include <stdlib.h>

int *p = malloc(sizeof *p);          /* un int */
double *v = malloc(n * sizeof *v);   /* n double consecutivi */
Studente *s = malloc(sizeof *s);     /* una struct */

if (v == NULL) {
    /* memoria insufficiente */
}
...
free(v);                             /* il blocco torna al sistema */
```

| | Array locale | Blocco con `malloc` |
|-|--------------|---------------------|
| dimensione | fissata quando si compila | scelta durante l'esecuzione |
| durata | fino alla fine del blocco | fino alla `free` |
| `sizeof` | dimensione dell'array | dimensione del **puntatore** |
| errore di memoria | il programma termina | `malloc` restituisce `NULL` |

### Regole del corso

- si scrive `malloc(n * sizeof *p)`: la dimensione segue il tipo di `p`;
- dopo ogni `malloc` si controlla `NULL`;
- il numero di elementi si tiene in una variabile: il blocco non lo
  ricorda;
- ogni blocco si libera con `free`, una sola volta; `free(NULL)` non fa
  nulla.

Un blocco si usa come un array (`v[i]`); se contiene una struct, i campi
si raggiungono con la freccia (`s->nome`), e con il punto per gli
elementi di un array di struct (`classe[i].nome`).

---

## File dell'esempio

| File | Contenuto |
|------|-----------|
| `010-prima-malloc.c` | Un `int` nello stack e uno nello heap, con i loro indirizzi |
| `020-array-di-dimensione-scelta.c` | `n` letto da tastiera e `malloc(n * sizeof *ore)` |
| `030-struct-allocata.c` | Una struct e un array di struct nello heap |
| `040-problema-voti-della-verifica.c` | Voti di una classe di n studenti: media e insufficienze |
| `040-problema-voti-della-verifica-analisi.md` | Analisi di `040-problema-voti-della-verifica.c` |
| `050-problema-misure-del-laboratorio.c` | Periodi di un pendolo: media, scarto e misure anomale |
| `050-problema-misure-del-laboratorio-analisi.md` | Analisi di `050-problema-misure-del-laboratorio.c` |
| `060-problema-scheda-studente.c` | Una struct allocata per riga e riempita da una funzione |
| `060-problema-scheda-studente-analisi.md` | Analisi di `060-problema-scheda-studente.c` |
| `070-problema-posti-della-gita.c` | Array di struct con la capienza del pullman |
| `070-problema-posti-della-gita-analisi.md` | Analisi di `070-problema-posti-della-gita.c` |
| `080-problema-copia-di-una-stringa.c` | Ogni nome in un blocco di `strlen + 1` byte |
| `080-problema-copia-di-una-stringa-analisi.md` | Analisi di `080-problema-copia-di-una-stringa.c` |

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-prima-malloc 010-prima-malloc.c
./010-prima-malloc

gcc -Wall -Wextra -o 020-array-di-dimensione-scelta 020-array-di-dimensione-scelta.c
./020-array-di-dimensione-scelta

gcc -Wall -Wextra -o 030-struct-allocata 030-struct-allocata.c
./030-struct-allocata

gcc -Wall -Wextra -o 040-problema-voti-della-verifica 040-problema-voti-della-verifica.c
./040-problema-voti-della-verifica

gcc -Wall -Wextra -o 050-problema-misure-del-laboratorio 050-problema-misure-del-laboratorio.c -lm
./050-problema-misure-del-laboratorio

gcc -Wall -Wextra -o 060-problema-scheda-studente 060-problema-scheda-studente.c
./060-problema-scheda-studente

gcc -Wall -Wextra -o 070-problema-posti-della-gita 070-problema-posti-della-gita.c
./070-problema-posti-della-gita

gcc -Wall -Wextra -o 080-problema-copia-di-una-stringa 080-problema-copia-di-una-stringa.c
./080-problema-copia-di-una-stringa
```

Gli indirizzi stampati cambiano da un'esecuzione all'altra.

---

## Output atteso

### 010-prima-malloc
```
sizeof *nello_heap = 4 byte
nello_stack = 7   all'indirizzo 0x7fff56c52b1c
*nello_heap = 42  all'indirizzo 0x556397a812a0
il puntatore nello_heap sta nello stack: 0x7fff56c52b20
dopo la somma *nello_heap = 49
blocco liberato
```

### 020-array-di-dimensione-scelta
*(output dipendente dall'input – cinque giorni con due valori da correggere)*
```
Quanti giorni (da 1 a 366)? 5
Blocco di 5 x 8 = 40 byte (sizeof ore = 8)
Ore di sonno del giorno 1: 7
Ore di sonno del giorno 2: 8.5
Ore di sonno del giorno 3: 9
Ore di sonno del giorno 4: x
  valore non valido (da 0 a 24)
Ore di sonno del giorno 4: 25
  valore non valido (da 0 a 24)
Ore di sonno del giorno 4: 6.5
Ore di sonno del giorno 5: 6

Media: 7.4 ore
  giorno 1: 7.0 ore, sotto le 8
  giorno 4: 6.5 ore, sotto le 8
  giorno 5: 6.0 ore, sotto le 8
```

### 030-struct-allocata
```
sizeof(Studente) = 32 byte
candidati: blocco di 96 byte

Marta Bassi  3B  41 voti
Luca Ferri   3A  37 voti
Sara Conti   3B  52 voti

Eletto: Sara Conti (3B) con 52 voti
```

### 040-problema-voti-della-verifica
*(output dipendente dall'input – sei studenti)*
```
Studenti presenti alla verifica (da 1 a 40): 6
Voto dello studente 1: 7
Voto dello studente 2: 5.5
Voto dello studente 3: 8
Voto dello studente 4: 11
  voto non valido (da 1 a 10, anche mezzi voti)
Voto dello studente 4: abc
  voto non valido (da 1 a 10, anche mezzi voti)
Voto dello studente 4: 6.5
Voto dello studente 5: 9
Voto dello studente 6: 4

Media della classe: 6.67
Insufficienze:
  studente  2: 5.5
  studente  6: 4.0
Sopra la media: 3 su 6
Voto piu' alto: 9.0, piu' basso: 4.0
```

*(output dipendente dall'input – numero non valido)*
```
Studenti presenti alla verifica (da 1 a 40): 45
Numero non valido.
```

### 050-problema-misure-del-laboratorio
*(output dipendente dall'input – dieci misure con un errore)*
```
Numero di misure (da 3 a 1000): 10
Periodi misurati in secondi:
1.42
1.40
1.43
1.41
1.39
1.42
1.68
1.40
1.41
1.42

Media: 1.438 s   scarto: 0.086 s
Misure anomale (oltre 0.172 s dalla media):
  misura 7: 1.680 s
Media senza anomalie: 1.411 s (9 misure)
```

*(output dipendente dall'input – misura non valida)*
```
Numero di misure (da 3 a 1000): 4
Periodi misurati in secondi:
1.4
1.5
-2
Misura 3 non valida: inserimento interrotto.
```

### 060-problema-scheda-studente
*(output dipendente dall'input – quattro studenti)*
```
Studente (FINE per terminare): Bassi Marta 3B 7 8.5 6
  +--------------------------------+
  | Bassi      Marta      3B       |
  |   italiano       7.0           |
  |   matematica     8.5           |
  |   inglese        6.0           |
  |   media         7.17           |
  |   esito: promosso              |
  +--------------------------------+
Studente (FINE per terminare): Ferri Luca 3A 5 6 4.5
  +--------------------------------+
  | Ferri      Luca       3A       |
  |   italiano       5.0           |
  |   matematica     6.0           |
  |   inglese        4.5           |
  |   media         5.17           |
  |   esito: 2 insufficienze       |
  +--------------------------------+
Studente (FINE per terminare): Conti Sara 3B 11 7 7
  Riga non valida: scheda non creata.
Studente (FINE per terminare): Neri Paolo 3C 6 5.5 8
  +--------------------------------+
  | Neri       Paolo      3C       |
  |   italiano       6.0           |
  |   matematica     5.5           |
  |   inglese        8.0           |
  |   media         6.50           |
  |   esito: 1 insufficienza       |
  +--------------------------------+
Studente (FINE per terminare): FINE

Schede stampate: 3, righe scartate: 1
```

### 070-problema-posti-della-gita
*(output dipendente dall'input – pullman da 3 posti)*
```
Posti del pullman (da 1 a 80): 3
Elenco di 3 posti: 120 byte
Comando (I, V, A, E, R, Q): I Marta 3B 40
  Marta al posto 1
Comando (I, V, A, E, R, Q): I Luca 3A 85
  Luca al posto 2
Comando (I, V, A, E, R, Q): I Sara 3B 90
  Dati non validi.
Comando (I, V, A, E, R, Q): I Sara 3B 20
  Sara al posto 3
Comando (I, V, A, E, R, Q): I Paolo 3C 30
  Pullman pieno: Paolo non iscritto.
Comando (I, V, A, E, R, Q): V 1 45
  Marta: versati 85.00 euro
Comando (I, V, A, E, R, Q): V 3 40
  Sara: versati 60.00 euro
Comando (I, V, A, E, R, Q): A 1
  Autorizzazione di Marta consegnata.
Comando (I, V, A, E, R, Q): A 2
  Autorizzazione di Luca consegnata.
Comando (I, V, A, E, R, Q): A 5
  Posto non valido.
Comando (I, V, A, E, R, Q): E
   1 Marta        3B  manca   0.00  autorizzato
   2 Luca         3A  manca   0.00  autorizzato
   3 Sara         3B  manca  25.00  senza autorizzazione
Comando (I, V, A, E, R, Q): R
  Posti occupati 3 su 3, liberi 0
  non puo' ancora partire: Sara
  Pronti a partire: 2, raccolti 230.00 euro su 255.00
Comando (I, V, A, E, R, Q): Q
```

### 080-problema-copia-di-una-stringa
*(output dipendente dall'input – nomi scritti come capita)*
```
Nomi dei diplomati (FINE per terminare):
mARTA  bassi
LUCA FERRI
   
  anna maria   de luca 
sara conti
FINE

Elenco per i diplomi:
   1. Marta Bassi              (12 byte)
   2. Luca Ferri               (11 byte)
   3. Anna Maria De Luca       (19 byte)
   4. Sara Conti               (11 byte)
Byte nello heap: 53 (con una matrice char[4][80]: 320)
```

---

## Errori comuni da evitare

**Non controllare il risultato di malloc**
```c
v = malloc(n * sizeof *v);
v[0] = 1;                          /* se v è NULL il programma termina */
if (v != NULL) { v[0] = 1; }       /* corretto */
```

**Calcolare la dimensione con il tipo sbagliato**
```c
double *v = malloc(n * sizeof(int));     /* metà dei byte necessari */
double *v = malloc(n * sizeof *v);       /* corretto */
```

**Usare sizeof sul puntatore per contare gli elementi**
```c
for (i = 0; i < sizeof v / sizeof v[0]; i++)    /* sizeof v è 8 */
for (i = 0; i < n; i++)                          /* corretto */
```

**Dimenticare il byte del '\0'**
```c
copia = malloc(strlen(riga));      /* strcpy scrive un byte fuori */
copia = malloc(strlen(riga) + 1);  /* corretto */
```

**Leggere il blocco prima di averlo riempito**
```c
v = malloc(n * sizeof *v);
somma = somma + v[0];              /* malloc non azzera la memoria */
```

**Dimenticare la free**
```c
/* ogni malloc deve avere la sua free prima della fine del programma */
```

---

## Concetti collegati

- `05-puntatori` → aritmetica dei puntatori e `v[i]` come `*(v + i)`
- `06-strutture-e-unioni/03-struct-e-funzioni` → puntatori a struct e `->`
- `02-funzioni-e-memoria-dinamica` → funzioni che allocano e restituiscono
- `03-errori-con-la-memoria` → perdite, doppio free, fuori dai limiti
- `02-calloc-e-realloc` → blocchi azzerati e blocchi che cambiano dimensione

---

## Esercizi proposti

1. In `020-array-di-dimensione-scelta.c` stampa anche il giorno con più
   ore di sonno.

2. In `040-problema-voti-della-verifica.c` alloca un secondo array con i
   voti arrotondati al voto intero più vicino e stampalo.

3. In `050-problema-misure-del-laboratorio.c` chiedi anche la lunghezza
   del pendolo e calcola g = 4π² l / T².

4. In `070-problema-posti-della-gita.c` aggiungi il comando `T classe`
   con i partecipanti di una classe.

5. (Avanzato) In `080-problema-copia-di-una-stringa.c` ordina l'elenco
   alfabeticamente scambiando i puntatori, senza copiare le stringhe.
