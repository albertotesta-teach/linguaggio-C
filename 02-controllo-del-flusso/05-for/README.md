# 05 – For

## Concetto

Il `for` è il ciclo per un numero di ripetizioni **noto** (o calcolabile)
prima di iniziare. Riunisce in una riga i tre elementi di ogni ciclo:

```c
for (inizializzazione; condizione; aggiornamento) {
    corpo;
}
```

```
  inizializzazione
        │
        ▼
  ┌────────────┐  falsa
  │ condizione │────────► fine del ciclo
  └─────┬──────┘
      vera
        ▼
     corpo
        │
        ▼
  aggiornamento ──► (torna alla condizione)
```

È equivalente a un `while`:

```c
inizializzazione;
while (condizione) {
    corpo;
    aggiornamento;
}
```

### For o while?

| Situazione | Ciclo |
|------------|-------|
| "per i da 1 a N", N noto prima del ciclo | `for` |
| "finché l'utente non inserisce 0", "finché non si raggiunge l'obiettivo" | `while` |
| il corpo va eseguito almeno una volta | `do-while` |

### Quante iterazioni?

| Intestazione | Iterazioni | Valori di `i` |
|--------------|------------|---------------|
| `for (i = 0; i < N; i++)` | N | 0 … N−1 |
| `for (i = 1; i <= N; i++)` | N | 1 … N |
| `for (i = N; i >= 1; i--)` | N | N … 1 |
| `for (i = 0; i < N; i = i + 2)` | ⌈N/2⌉ | 0, 2, 4, … |

### Cicli annidati

Per ogni iterazione del ciclo esterno, il ciclo interno viene eseguito
**per intero**: le iterazioni si moltiplicano. Schema tipico: esterno sulle
righe, interno sulle colonne, a capo alla fine di ogni riga. Le due
variabili di controllo devono essere diverse.

### Uscire prima dal for senza break

Se la ricerca può fermarsi in anticipo, la condizione del `for` contiene
anche un flag:

```c
primo = 1;
for (d = 2; d * d <= n && primo; d++) {
    if (n % d == 0) {
        primo = 0;
    }
}
```

---

## File dell'esempio

| File | Contenuto |
|------|-----------|
| `010-for-base.c` | Conteggio in avanti, all'indietro, con passo; equivalenza con while; numero di iterazioni |
| `020-accumulatori.c` | Sette temperature lette una alla volta: media, massimo, minimo, conteggio sopra soglia |
| `030-cicli-annidati.c` | Tavola pitagorica, rettangolo e triangolo di asterischi, griglia di coordinate |
| `040-problema-tabella-conversione.c` | Tabella Celsius / Fahrenheit / Kelvin con intervallo e passo scelti dall'utente |
| `040-problema-tabella-conversione-analisi.md` | Analisi di `040-problema-tabella-conversione.c` |
| `050-problema-numeri-primi.c` | Verifica di primalità con flag e elenco dei primi fino a un limite |
| `050-problema-numeri-primi-analisi.md` | Analisi di `050-problema-numeri-primi.c` |
| `060-problema-scontrino.c` | Scontrino con n articoli: subtotale, sconto, totale, riga più costosa |
| `060-problema-scontrino-analisi.md` | Analisi di `060-problema-scontrino.c` |
| `070-problema-figure-ascii.c` | Triangolo, piramide, quadrato vuoto e rombo di altezza scelta |
| `070-problema-figure-ascii-analisi.md` | Analisi di `070-problema-figure-ascii.c` |

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-for-base 010-for-base.c
./010-for-base

gcc -Wall -Wextra -o 020-accumulatori 020-accumulatori.c
./020-accumulatori

gcc -Wall -Wextra -o 030-cicli-annidati 030-cicli-annidati.c
./030-cicli-annidati

gcc -Wall -Wextra -o 040-problema-tabella-conversione 040-problema-tabella-conversione.c
./040-problema-tabella-conversione

gcc -Wall -Wextra -o 050-problema-numeri-primi 050-problema-numeri-primi.c
./050-problema-numeri-primi

gcc -Wall -Wextra -o 060-problema-scontrino 060-problema-scontrino.c
./060-problema-scontrino

gcc -Wall -Wextra -o 070-problema-figure-ascii 070-problema-figure-ascii.c
./070-problema-figure-ascii
```

---

## Output atteso

### 010-for-base
```
=== Da 1 a 10 ===
1 2 3 4 5 6 7 8 9 10 

=== Lo stesso con while ===
1 2 3 4 5 6 7 8 9 10 

=== Da 10 a 1 ===
10 9 8 7 6 5 4 3 2 1 

=== Multipli di 5 fino a 50 ===
5 10 15 20 25 30 35 40 45 50 

=== Potenze di 2 minori di 1000 ===
1 2 4 8 16 32 64 128 256 512 

=== Conteggio delle iterazioni ===
for (i = 0; i < 7; i++)  -> 7 iterazioni, alla fine i = 7
for (i = 1; i <= 7; i++) -> 7 iterazioni, alla fine i = 8
for (i = 10; i < 7; i++) -> 0 iterazioni (condizione falsa subito)
```

### 020-accumulatori
*(output dipendente dall'input – esempio con 28.5 31 33.2 29 26.4 30 24.8)*
```
=== TEMPERATURE DELLA SETTIMANA ===
Temperatura massima del giorno 1: 28.5
Temperatura massima del giorno 2: 31
Temperatura massima del giorno 3: 33.2
Temperatura massima del giorno 4: 29
Temperatura massima del giorno 5: 26.4
Temperatura massima del giorno 6: 30
Temperatura massima del giorno 7: 24.8

--- Riepilogo ---
Media della settimana : 29.0 gradi
Massima               : 33.2 gradi (giorno 3)
Minima                : 24.8 gradi
Escursione            : 8.4 gradi
Giorni con almeno 30 gradi: 3 su 7
```

### 030-cicli-annidati
```
=== Tavola pitagorica ===
    |   1   2   3   4   5   6   7   8   9  10
----+----------------------------------------
  1 |   1   2   3   4   5   6   7   8   9  10
  2 |   2   4   6   8  10  12  14  16  18  20
  3 |   3   6   9  12  15  18  21  24  27  30
  4 |   4   8  12  16  20  24  28  32  36  40
  5 |   5  10  15  20  25  30  35  40  45  50
  6 |   6  12  18  24  30  36  42  48  54  60
  7 |   7  14  21  28  35  42  49  56  63  70
  8 |   8  16  24  32  40  48  56  64  72  80
  9 |   9  18  27  36  45  54  63  72  81  90
 10 |  10  20  30  40  50  60  70  80  90 100
Il corpo del ciclo interno e' stato eseguito 100 volte (10 x 10).

=== Rettangolo 3 x 8 ===
********
********
********

=== Triangolo di altezza 5 ===
*
**
***
****
*****

=== Coordinate (riga, colonna) ===
(1,1) (1,2) (1,3) 
(2,1) (2,2) (2,3) 
(3,1) (3,2) (3,3) 
```

### 040-problema-tabella-conversione
*(output dipendente dall'input – esempio da -20 a 100 ogni 20 gradi)*
```
=== TABELLA DI CONVERSIONE TEMPERATURE ===

Temperatura iniziale (gradi C, intero): -20
Temperatura finale (>= -20): 100
Passo (positivo): 20

   Celsius | Fahrenheit |   Kelvin
  ---------|------------|----------
       -20 |       -4.0 |   253.15
         0 |       32.0 |   273.15   <- l'acqua gela
        20 |       68.0 |   293.15
        40 |      104.0 |   313.15
        60 |      140.0 |   333.15
        80 |      176.0 |   353.15
       100 |      212.0 |   373.15   <- l'acqua bolle

Righe stampate: 7
```

### 050-problema-numeri-primi
*(output dipendente dall'input – esempio con 221 e limite 100)*
```
=== NUMERI PRIMI ===

Numero da verificare (>= 2): 221
221 non e' primo: e' divisibile per 13 (221 = 13 x 17).

Elenca i primi fino a (>= 2): 100

     2     3     5     7    11    13    17    19    23    29
    31    37    41    43    47    53    59    61    67    71
    73    79    83    89    97

Tra 2 e 100 ci sono 25 numeri primi.
```

### 060-problema-scontrino
*(output dipendente dall'input – esempio con tre articoli)*
```
=== CASSA ===
Numero di articoli diversi: 3

Articolo 1
  Prezzo unitario: 2.49
  Quantita': 4
  4 x 2.49 = 9.96 euro

Articolo 2
  Prezzo unitario: 15.90
  Quantita': 2
  2 x 15.90 = 31.80 euro

Articolo 3
  Prezzo unitario: 69.00
  Quantita': 1
  1 x 69.00 = 69.00 euro

================================
  Articoli diversi :        3
  Pezzi totali     :        7
  Subtotale        :   110.76
  Sconto 5%        :    -5.54
  TOTALE EURO      :   105.22
================================
Riga piu' costosa: n. 3 (69.00 euro)
```

### 070-problema-figure-ascii
*(output dipendente dall'input – esempio con altezza 4)*
```
=== FIGURE ASCII ===
Altezza delle figure (2-20): 4

1) Triangolo rettangolo
*
**
***
****

2) Piramide
   *
  ***
 *****
*******

3) Quadrato vuoto
* * * * 
*     * 
*     * 
* * * * 

4) Rombo
   *
  ***
 *****
*******
 *****
  ***
   *
```

---

## Errori comuni da evitare

**Punto e virgola dopo la parentesi**
```c
for (i = 1; i <= 10; i++);   /* corpo vuoto */
{
    printf("%d\n", i);       /* eseguito una sola volta, con i = 11 */
}
```

**Errore di una unità (off-by-one)**
```c
for (i = 1; i < 10; i++)     /* 9 iterazioni, non 10 */
for (i = 0; i <= 10; i++)    /* 11 iterazioni, non 10 */
```

**Stessa variabile nei cicli annidati**
```c
for (i = 0; i < 3; i++) {
    for (i = 0; i < 4; i++) { ... }   /* ERRATO: modifica la i esterna */
}
```

**Accumulatore azzerato dentro il ciclo**
```c
for (i = 1; i <= n; i++) {
    somma = 0;               /* ERRATO: va inizializzato prima del ciclo */
    somma = somma + x;
}
```

**Variabile di controllo modificata nel corpo**
```c
for (i = 0; i < 10; i++) {
    i = i + 2;               /* il numero di iterazioni non si legge più
                                dall'intestazione */
}
```

---

## Concetti collegati

- `04-while-do-while` → cicli con numero di ripetizioni non noto e validazione dell'input
- `06-break-continue` → condizione con flag al posto di break
- `04-array-e-stringhe/01-array-monodimensionali` → il for è il ciclo naturale per scorrere un array
- `11-algoritmi` → cicli annidati negli algoritmi di ordinamento

---

## Esercizi proposti

1. Scrivi un programma che stampi la tabellina di un numero letto da tastiera
   (da 1 a 10) e la somma di tutti i risultati.

2. Calcola il fattoriale di un numero n letto da tastiera (n! = 1 × 2 × … × n).
   Da quale valore di n il risultato non sta più in un `int`?

3. Modifica `020-accumulatori.c` perché il numero di giorni sia letto da
   tastiera invece di essere fisso.

4. Aggiungi a `070-problema-figure-ascii.c` una scacchiera di altezza h
   (alternare `#` e spazio: il carattere dipende da `(riga + colonna) % 2`).

5. (Avanzato) Stampa tutte le terne pitagoriche (a, b, c) con
   a < b < c ≤ 50 e a² + b² = c². Quante iterazioni esegue il programma?
   Come si possono ridurre?
