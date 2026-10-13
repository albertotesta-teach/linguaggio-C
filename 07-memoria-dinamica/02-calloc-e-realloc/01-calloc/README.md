# 01 – calloc

## Concetto

`calloc` alloca un blocco per `n` elementi di una certa dimensione e
mette a zero tutti i suoi byte:

```c
int *conta = calloc(n, sizeof *conta);     /* n int che valgono 0 */

if (conta == NULL) {
    /* memoria insufficiente */
}
...
free(conta);
```

| | `malloc` | `calloc` |
|-|----------|----------|
| argomenti | byte totali: `n * sizeof *p` | numero e dimensione: `n, sizeof *p` |
| contenuto iniziale | non definito | tutti i byte a zero |
| quando usarla | ogni elemento verrà scritto prima di essere letto | contatori, totali, flag, celle "vuote" |

### Zero per ogni tipo

`calloc` azzera i **byte**. Per gli interi e i `char` il valore è 0; per i
`double` e i puntatori lo standard non lo garantisce, ma su tutte le
macchine di uso comune (IEEE 754, `NULL` fatto di soli zeri) i byte a zero
valgono `0.0` e `NULL`.

### Matrice azzerata

```c
double *punti = calloc(righe * colonne, sizeof *punti);
punti[r * colonne + c]           /* elemento (r, c), all'inizio 0 */
```

---

## File dell'esempio

| File | Contenuto |
|------|-----------|
| `010-calloc-azzera.c` | `calloc` a confronto con `malloc` seguita da un ciclo di azzeramento |
| `020-contatori-con-calloc.c` | 26 contatori di lettere già a zero |
| `030-matrice-azzerata.c` | Tabella del torneo di scacchi in un blocco azzerato |
| `040-problema-istogramma-dei-voti.c` | Un contatore per ogni voto della scala scelta |
| `040-problema-istogramma-dei-voti-analisi.md` | Analisi di `040-problema-istogramma-dei-voti.c` |
| `050-problema-presenze-del-mese.c` | Matrice giorni × studenti delle assenze |
| `050-problema-presenze-del-mese-analisi.md` | Analisi di `050-problema-presenze-del-mese.c` |
| `060-problema-parole-per-lunghezza.c` | Contatori per lunghezza delle parole di un testo |
| `060-problema-parole-per-lunghezza-analisi.md` | Analisi di `060-problema-parole-per-lunghezza.c` |
| `070-problema-posti-a-teatro.c` | Sala con i codici delle prenotazioni, 0 = libero |
| `070-problema-posti-a-teatro-analisi.md` | Analisi di `070-problema-posti-a-teatro.c` |
| `080-problema-crivello-di-eratostene.c` | Flag dei numeri composti fino a un milione |
| `080-problema-crivello-di-eratostene-analisi.md` | Analisi di `080-problema-crivello-di-eratostene.c` |

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-calloc-azzera 010-calloc-azzera.c
./010-calloc-azzera

gcc -Wall -Wextra -o 020-contatori-con-calloc 020-contatori-con-calloc.c
./020-contatori-con-calloc

gcc -Wall -Wextra -o 030-matrice-azzerata 030-matrice-azzerata.c
./030-matrice-azzerata

gcc -Wall -Wextra -o 040-problema-istogramma-dei-voti 040-problema-istogramma-dei-voti.c
./040-problema-istogramma-dei-voti

gcc -Wall -Wextra -o 050-problema-presenze-del-mese 050-problema-presenze-del-mese.c
./050-problema-presenze-del-mese

gcc -Wall -Wextra -o 060-problema-parole-per-lunghezza 060-problema-parole-per-lunghezza.c
./060-problema-parole-per-lunghezza

gcc -Wall -Wextra -o 070-problema-posti-a-teatro 070-problema-posti-a-teatro.c
./070-problema-posti-a-teatro

gcc -Wall -Wextra -o 080-problema-crivello-di-eratostene 080-problema-crivello-di-eratostene.c
./080-problema-crivello-di-eratostene
```

---

## Output atteso

### 010-calloc-azzera
```
calloc(6, 4): 24 byte
con_calloc: 0 0 0 0 0 0
con_malloc: il contenuto iniziale non e' definito
dopo il ciclo di azzeramento: tutto a zero? si'
con_calloc dopo con_calloc[2] = 7: 0 0 7 0 0 0
```

### 020-contatori-con-calloc
*(output dipendente dall'input – due righe)*
```
Testo (riga vuota per terminare):
Ciao a tutti
Domani verifica di informatica


Lettere: 37
  a   6 ######
  c   3 ###
  d   2 ##
  e   1 #
  f   2 ##
  i   8 ########
  m   2 ##
  n   2 ##
  o   3 ###
  r   2 ##
  t   4 ####
  u   1 #
  v   1 #
Piu' frequente: i (8 volte)
```

### 030-matrice-azzerata
```
         Marta   Luca   Sara  Paolo  totale
Marta        -    1.0    0.0    0.5     1.5
Luca       0.0      -    0.5    1.0     1.5
Sara       1.0    0.5      -    0.5     2.0
Paolo      0.5    0.0    0.5      -     1.0
```

### 040-problema-istogramma-dei-voti
*(output dipendente dall'input – scala da 3 a 10)*
```
Scala dei voti (minimo massimo): 3 10
15 contatori azzerati da calloc
Voti (FINE per terminare):
6 7.5 5 6.5 8 6 4.5 11 6 7.3 9 6.5 FINE
  11 scartato
  7.3 scartato

10.0 |
 9.5 |
 9.0 | *
 8.5 |
 8.0 | *
 7.5 | *
 7.0 |
 6.5 | * *
 6.0 | * * *
 5.5 |
 5.0 | *
 4.5 | *
 4.0 |
 3.5 |
 3.0 |
Voti: 10, piu' frequente: 6.0 (3 volte), sufficienze: 80%
```

### 050-problema-presenze-del-mese
*(output dipendente dall'input – 5 studenti, 8 giorni)*
```
Studenti e giorni di lezione: 5 8
Giorno 1, assenti (0 per finire): 2 0
Giorno 2, assenti (0 per finire): 0
Giorno 3, assenti (0 per finire): 2 4 0
Giorno 4, assenti (0 per finire): 9 0
  studente 9 inesistente
Giorno 5, assenti (0 per finire): 2 0
Giorno 6, assenti (0 per finire): 1 2 3 0
Giorno 7, assenti (0 per finire): 0
Giorno 8, assenti (0 per finire): 4 0

        12345678  assenze
stud  1 .....A..   1
stud  2 A.A.AA..   4  oltre il 25%
stud  3 .....A..   1
stud  4 ..A....A   2
stud  5 ........   0
Giorno con piu' assenti: 6 (3 su 5)
```

### 060-problema-parole-per-lunghezza
*(output dipendente dall'input – testo di scienze)*
```
Lunghezza massima da distinguere (da 2 a 30): 8
Testo (FINE per terminare):
La fotosintesi clorofilliana trasforma l'energia luminosa
in energia chimica: le piante producono zucchero e ossigeno.
FINE

Parole: 16
   1  lettere:   2  (12.5%)
   2  lettere:   3  (18.8%)
   6  lettere:   1  ( 6.2%)
   7  lettere:   3  (18.8%)
   8+ lettere:   7  (43.8%)
Lunghezza media: 6.3 lettere
Parola piu' lunga: clorofilliana
```

### 070-problema-posti-a-teatro
*(output dipendente dall'input – sala 4 x 10)*
```
Righe e posti per riga: 4 10
Comando (P, C, M, Q): P A 3 4
  prenotazione 1: A3-A6
Comando (P, C, M, Q): P A 5 2
  Alcuni posti sono gia' occupati.
Comando (P, C, M, Q): P B 1 3
  prenotazione 2: B1-B3
Comando (P, C, M, Q): P D 9 3
  Posti non validi.
Comando (P, C, M, Q): P E 1 1
  Posti non validi.
Comando (P, C, M, Q): C 1
  prenotazione 1 cancellata: liberati 4 posti
Comando (P, C, M, Q): P A 5 2
  prenotazione 3: A5-A6
Comando (P, C, M, Q): C 7
  Prenotazione inesistente.
Comando (P, C, M, Q): M
   palco
  A ....##....
  B ###.......
  C ..........
  D ..........
  occupati 5 su 40
Comando (P, C, M, Q): Q
```

### 080-problema-crivello-di-eratostene
*(output dipendente dall'input – fino a 100)*
```
Primi fino a (da 2 a 1000000): 100
Flag allocati: 101 byte
Primi fino a 100: 25
 2 3 5 7 11 13 17 19 23 29 31 37 41 43 47 53 59 61 67 71 73 79 83 89 97
Coppie di primi gemelli: 8
```

*(output dipendente dall'input – fino a un milione)*
```
Primi fino a (da 2 a 1000000): 1000000
Flag allocati: 1000001 byte
Primi fino a 1000000: 78498
 2 3 5 7 11 13 17 19 23 29 ... 999863 999883 999907 999917 999931 999953 999959 999961 999979 999983
Coppie di primi gemelli: 8169
```

---

## Errori comuni da evitare

**Moltiplicare gli argomenti di calloc**
```c
calloc(n * sizeof *v, 1)           /* funziona, ma calloc controlla già il prodotto */
calloc(n, sizeof *v)               /* corretto */
```

**Contare su malloc per avere zeri**
```c
conta = malloc(n * sizeof *conta);
conta[k]++;                        /* parte da un valore casuale */
```

**Usare calloc quando ogni elemento viene comunque scritto**
```c
voti = calloc(n, sizeof *voti);    /* azzeramento inutile se poi si leggono tutti */
```

**Dimenticare il +1 per l'indice n**
```c
composto = calloc(n, sizeof *composto);       /* composto[n] è fuori */
composto = calloc(n + 1, sizeof *composto);   /* indici da 0 a n */
```

---

## Concetti collegati

- `01-malloc-e-free` → `malloc`, `free`, matrici in un blocco
- `04-array-e-stringhe/01-array-monodimensionali` → array di contatori
- `02-realloc` → cambiare la dimensione di un blocco

---

## Esercizi proposti

1. In `020-contatori-con-calloc.c` conta anche le cifre, con un secondo
   blocco di 10 contatori.

2. In `040-problema-istogramma-dei-voti.c` stampa l'istogramma in
   orizzontale con le percentuali.

3. In `050-problema-presenze-del-mese.c` segnala gli studenti assenti per
   tre giorni consecutivi.

4. In `070-problema-posti-a-teatro.c` aggiungi il comando `L riga quanti`
   che trova i primi posti liberi vicini in quella riga.

5. (Avanzato) In `080-problema-crivello-di-eratostene.c` usa un bit per
   numero invece di un byte, con un blocco di `n / 8 + 1` byte.
