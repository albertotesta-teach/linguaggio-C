# 03 – Operazioni su array monodimensionali

## Concetto

Quasi tutte le elaborazioni su un array si costruiscono combinando pochi
**pattern di scorrimento**. Una volta riconosciuti, si riusano in ogni problema.

### Pattern accumulatore

Una variabile inizializzata **prima** del ciclo viene aggiornata a ogni
iterazione. Al termine contiene il risultato (somma, conteggio, prodotto).

```c
somma = 0;
for (i = 0; i < N; i++) {
    somma = somma + valori[i];
}
media = (double) somma / N;   /* cast: evita la divisione intera */
```

### Pattern "ipotesi e smentita" (minimo e massimo)

Si ipotizza che il primo elemento sia l'estremo cercato, poi si scorre il resto
dell'array cercando un elemento che smentisca l'ipotesi.

```
  valori:   34  12  78   5  91  23
             ^
  ipotesi: massimo = valori[0] = 34
  i = 2 → 78 > 34  → massimo = 78
  i = 4 → 91 > 78  → massimo = 91   (risultato)
```

### Pattern ricerca con flag

La ricerca di un valore si ferma appena lo trova, **senza `break`**: la
condizione del ciclo controlla anche una variabile `trovato`.

```c
i = 0;
trovato = 0;
while (i < N && !trovato) {
    if (valori[i] == cercato) {
        trovato = 1;
    } else {
        i++;
    }
}
```

### Trasformazioni in-place e scambio

Per modificare l'array nella sua stessa memoria si scrive direttamente
`valori[i] = ...`. Per invertire l'ordine si scambiano gli elementi simmetrici
con una **variabile d'appoggio**, fermandosi a metà array:

```
  [ 3  -1   7  -4   9 ]        i = 0 ↔ 4,  i = 1 ↔ 3,  il centro resta
    ↑               ↑
```

---

## File dell'esempio

| File | Contenuto |
|------|-----------|
| `010-somma-e-media.c` | Pattern accumulatore: somma totale, media, somme condizionate (positivi/negativi, posizioni pari/dispari), somma cumulativa |
| `020-minimo-massimo-e-ricerca.c` | Minimo e massimo con posizione, secondo massimo, ricerca con flag senza `break`, conteggio occorrenze |
| `030-trasformazione-elementi.c` | Inversione con scambio, valore assoluto, azzeramento selettivo, copia in un secondo array |
| `040-problema-andamento-borsa.c` | Prezzi di un titolo su 10 giorni: variazione giornaliera, giorno di massimo guadagno e perdita, giorni sotto la media |
| `040-problema-andamento-borsa-analisi.md` | Analisi di `040-problema-andamento-borsa.c` |
| `050-problema-contatore-caratteri.c` | Tabella delle frequenze delle lettere in un testo con indice `c - 'a'` e istogramma |
| `050-problema-contatore-caratteri-analisi.md` | Analisi di `050-problema-contatore-caratteri.c` |
| `060-problema-classifica-gara.c` | Array paralleli nomi/tempi: vincitore, distacchi, tempo medio, atleti sotto la media |
| `060-problema-classifica-gara-analisi.md` | Analisi di `060-problema-classifica-gara.c` |
| `070-problema-paghe-dipendenti.c` | Tre array paralleli (nomi, ore, tariffe) e un array calcolato di paghe: totale, media, estremi, confronto |
| `070-problema-paghe-dipendenti-analisi.md` | Analisi di `070-problema-paghe-dipendenti.c` |
| `080-problema-rilevamento-traffico.c` | Veicoli/ora su 8 strade: strade congestionate oltre soglia, media, top-3 senza ordinamento |
| `080-problema-rilevamento-traffico-analisi.md` | Analisi di `080-problema-rilevamento-traffico.c` |

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-somma-e-media 010-somma-e-media.c
./010-somma-e-media

gcc -Wall -Wextra -o 020-minimo-massimo-e-ricerca 020-minimo-massimo-e-ricerca.c
./020-minimo-massimo-e-ricerca

gcc -Wall -Wextra -o 030-trasformazione-elementi 030-trasformazione-elementi.c
./030-trasformazione-elementi

gcc -Wall -Wextra -o 040-problema-andamento-borsa 040-problema-andamento-borsa.c
./040-problema-andamento-borsa

gcc -Wall -Wextra -o 050-problema-contatore-caratteri 050-problema-contatore-caratteri.c
./050-problema-contatore-caratteri

gcc -Wall -Wextra -o 060-problema-classifica-gara 060-problema-classifica-gara.c
./060-problema-classifica-gara

gcc -Wall -Wextra -o 070-problema-paghe-dipendenti 070-problema-paghe-dipendenti.c
./070-problema-paghe-dipendenti

gcc -Wall -Wextra -o 080-problema-rilevamento-traffico 080-problema-rilevamento-traffico.c
./080-problema-rilevamento-traffico
```

---

## Output atteso

Nessun programma richiede input: l'output è sempre lo stesso.

### 010-somma-e-media
```
Array:    4  -2   7   0  15  -8   3  11  -1   6

Somma di tutti gli elementi : 35
Media aritmetica            : 3.50

Somma elementi positivi     : 46  (count: 6)
Somma elementi negativi     : -11  (count: 3)

Somma posizioni pari (0,2,4,...) : 28
Somma posizioni dispari (1,3,...): 7

Somma cumulativa:
  Dopo valori[0] =   4 : totale = 4
  Dopo valori[1] =  -2 : totale = 2
  Dopo valori[2] =   7 : totale = 9
  Dopo valori[3] =   0 : totale = 9
  Dopo valori[4] =  15 : totale = 24
  Dopo valori[5] =  -8 : totale = 16
  Dopo valori[6] =   3 : totale = 19
  Dopo valori[7] =  11 : totale = 30
  Dopo valori[8] =  -1 : totale = 29
  Dopo valori[9] =   6 : totale = 35
```

### 020-minimo-massimo-e-ricerca
```
Array:   34  12  78   5  91  23  67  45  91   8  56  33

Massimo: 91  (posizione 4)
Minimo : 5  (posizione 3)

Secondo massimo: 91  (posizione 8)

Ricerca valore 91:
  Trovato in posizione 4

Occorrenze di 91 nell'array: 2
```

### 030-trasformazione-elementi
```
Array originale   :     3   -1    7   -4    9    2   -6    5

Dopo inversione   :     5   -6    2    9   -4    7   -1    3

Valore assoluto   :     3    1    7    4    9    2    6    5
Negativi azzerati :     3    0    7    0    9    2    0    5

Originale dopo copia :     3   -1    7   -4    9    2   -6    5
Copia modificata     :   999   -1    7   -4    9    2   -6    5
```

### 040-problema-andamento-borsa
```
=== ANDAMENTO TITOLO ===
  Giorno | Prezzo   | Variazione
  -------|----------|------------
     1   |  142.50€ | --
      2  |  145.20€ | +2.70€ (+1.89%)
      3  |  143.80€ | -1.40€ (-0.96%)
      4  |  148.60€ | +4.80€ (+3.34%)
      5  |  151.30€ | +2.70€ (+1.82%)
      6  |  149.70€ | -1.60€ (-1.06%)
      7  |  147.20€ | -2.50€ (-1.67%)
      8  |  152.40€ | +5.20€ (+3.53%)
      9  |  155.10€ | +2.70€ (+1.77%)
     10  |  153.80€ | -1.30€ (-0.84%)

Prezzo medio del periodo: 148.96€

Giorno con guadagno massimo: giorno 8 (+5.20€)
Giorno con perdita massima : giorno 7 (-2.50€)

Giorni con prezzo sotto la media (148.96€):
  Giorno  1: 142.50€ (-6.46€ dalla media)
  Giorno  2: 145.20€ (-3.76€ dalla media)
  Giorno  3: 143.80€ (-5.16€ dalla media)
  Giorno  4: 148.60€ (-0.36€ dalla media)
  Giorno  7: 147.20€ (-1.76€ dalla media)
Totale giorni sotto media: 5 su 10
```

### 050-problema-contatore-caratteri
```
=== ANALISI FREQUENZA LETTERE ===

  Lettera | Freq. | Percentuale | Istogramma
  --------|-------|-------------|--------------------
    a     |   21  |   16.3%     | *********************
    c     |    5  |    3.9%     | *****
    d     |    9  |    7.0%     | *********
    e     |   14  |   10.9%     | **************
    g     |    3  |    2.3%     | ***
    i     |   12  |    9.3%     | ************
    l     |   18  |   14.0%     | ******************
    m     |    3  |    2.3%     | ***
    n     |   12  |    9.3%     | ************
    o     |    9  |    7.0%     | *********
    p     |    3  |    2.3%     | ***
    r     |    5  |    3.9%     | *****
    s     |    2  |    1.6%     | **
    t     |    7  |    5.4%     | *******
    u     |    4  |    3.1%     | ****
    v     |    1  |    0.8%     | *
    z     |    1  |    0.8%     | *

Totale lettere analizzate: 129

Lettera piu' frequente : 'a'  (21 occorrenze)
Lettera meno frequente : 'v'  (1 occorrenza/e)
Lettere distinte usate : 17 su 26
```

### 060-problema-classifica-gara
```
=== CLASSIFICA GARA ===
  Pos. | Nome                | Tempo       | Distacco
  -----|---------------------|-------------|----------
    -  | Rossi Marco         | 3'03"       | +8"
    -  | Bianchi Luca        | 3'17"       | +22"
   1°  | Verdi Paolo         | 2'55"       | --
    -  | Ferrari Giorgio     | 3'22"       | +27"
    -  | Russo Andrea        | 3'11"       | +16"
    -  | Conti Matteo        | 2'58"       | +3"
    -  | Marino Fabio        | 3'29"       | +34"
    -  | Greco Simone        | 3'06"       | +11"

Tempo medio         : 190.1 secondi
Vincitore           : Verdi Paolo (175")

Atleti sotto la media (piu' veloci di 190.1"):
  Rossi Marco: 183"  (-7.1" dalla media)
  Verdi Paolo: 175"  (-15.1" dalla media)
  Conti Matteo: 178"  (-12.1" dalla media)
  Greco Simone: 186"  (-4.1" dalla media)
Totale: 4 atleti su 8
```

### 070-problema-paghe-dipendenti
```
=======================================================
              PROSPETTO PAGHE MENSILI                  
=======================================================
  Dipendente       | Ore  | Tariffa | Paga lorda
  -----------------|------|---------|------------
  Rossi Anna       | 168  |  12.50€ |   2100.00€
  Bianchi Carlo    | 152  |  15.00€ |   2280.00€
  Verdi Elena      | 176  |  11.80€ |   2076.80€
  Ferrari Marco    | 160  |  18.00€ |   2880.00€
  Russo Giulia     | 144  |  13.20€ |   1900.80€
  Conti Pietro     | 168  |  16.50€ |   2772.00€
=======================================================

Totale costo aziendale : 14009.60€
Paga media mensile     : 2334.93€

Paga piu' alta  : Ferrari Marco (2880.00€)
Paga piu' bassa : Russo Giulia (1900.80€)

Confronto con la media (2334.93€):
  Rossi Anna       : -234.93€ sotto la media
  Bianchi Carlo    : -54.93€ sotto la media
  Verdi Elena      : -258.13€ sotto la media
  Ferrari Marco    : +545.07€ sopra la media
  Russo Giulia     : -434.13€ sotto la media
  Conti Pietro     : +437.07€ sopra la media
```

### 080-problema-rilevamento-traffico
```
=== RILEVAMENTO TRAFFICO URBANO ===
  Strada                 | Veicoli/h | Stato
  -----------------------|-----------|----------
  Via Roma               |     620   | SCORREVOLE
  Corso Italia           |     950   | CONGESTA
  Via Garibaldi          |     430   | SCORREVOLE
  Viale Europa           |    1120   | CONGESTA
  Via Mazzini            |     780   | SCORREVOLE
  Corso Vittorio         |     870   | CONGESTA
  Via Dante              |     310   | SCORREVOLE
  Piazza Duomo           |    1050   | CONGESTA

Strade congestioniate (> 800 veicoli/h):
  [!] Corso Italia           : 950 veicoli/h
  [!] Viale Europa           : 1120 veicoli/h
  [!] Corso Vittorio         : 870 veicoli/h
  [!] Piazza Duomo           : 1050 veicoli/h

Densita' media : 766 veicoli/h
Congestioniate : 4 su 8 strade

Top-3 strade piu' trafficate:
  1° posto: Viale Europa           (1120 veicoli/h)
  2° posto: Piazza Duomo           (1050 veicoli/h)
  3° posto: Corso Italia           (950 veicoli/h)
```

---

## Errori comuni da evitare

**Accumulatore non inizializzato**
```c
int somma;                     /* ERRORE: valore iniziale indefinito */
for (i = 0; i < N; i++) {
    somma = somma + valori[i];
}
/* Corretto: int somma = 0; */
```

**Divisione intera nel calcolo della media**
```c
double media = somma / N;          /* ERRORE: somma e N sono int → 35 / 10 = 3 */
double media = (double) somma / N; /* corretto: 3.50 */
```

**Inizializzare il massimo a zero**
```c
int massimo = 0;    /* ERRORE: se tutti i valori sono negativi, il risultato è 0 */
int massimo = valori[0];   /* corretto: ipotesi sul primo elemento */
```

**Inversione che arriva fino in fondo all'array**
```c
for (i = 0; i < N; i++) {     /* ERRORE: dopo metà array gli scambi si annullano */
    appoggio = v[i];
    v[i] = v[N - 1 - i];
    v[N - 1 - i] = appoggio;
}
/* Corretto: for (i = 0; i < N / 2; i++) */
```

**Copiare un array con l'assegnazione**
```c
int copia[N];
copia = valori;   /* ERRORE di compilazione: gli array non si assegnano */
/* Corretto: copiare elemento per elemento con un ciclo */
```

---

## Concetti collegati

- `02-accesso-e-scorrimento` → cicli di scorrimento su cui si basano tutti i pattern
- `04-array-e-funzioni` → gli stessi pattern incapsulati in funzioni riusabili
- `05-array-a-tappo` → le stesse operazioni quando la fine è segnata da un tappo
- `11-algoritmi/02-ordinamento-bubble-sort` → lo scambio con variabile d'appoggio come base dell'ordinamento

---

## Esercizi proposti

1. Modifica `010-somma-e-media.c` per calcolare anche il prodotto degli
   elementi diversi da zero e la media dei soli valori positivi.

2. Scrivi un programma che, dato un array di 10 interi, conti quanti elementi
   sono maggiori dell'elemento che li precede e stampi le loro posizioni.

3. Partendo da `020-minimo-massimo-e-ricerca.c`, fai in modo che il secondo
   massimo sia il secondo valore **distinto** (nell'esempio 78, non di nuovo 91).

4. Modifica `060-problema-classifica-gara.c` per stampare gli atleti in ordine
   di arrivo, usando la stessa tecnica del top-3 di
   `080-problema-rilevamento-traffico.c` ripetuta su tutti gli atleti.

5. (Avanzato) Estendi `040-problema-andamento-borsa.c` per trovare la sequenza
   più lunga di giorni consecutivi in rialzo, stampando il giorno di inizio,
   quello di fine e il guadagno complessivo.
