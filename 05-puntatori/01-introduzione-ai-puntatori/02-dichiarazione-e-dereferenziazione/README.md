# 02 – Dichiarazione e dereferenziazione

## Concetto

Un **puntatore** è una variabile che contiene un indirizzo.

```c
int livello = 70;
int *p;              /* p può contenere l'indirizzo di un int */

p = &livello;        /* p punta a livello */
*p = 85;             /* scrive 85 nella variabile puntata: livello vale 85 */
x = *p;              /* legge il valore della variabile puntata */
```

| Espressione | Significato |
|-------------|-------------|
| `int *p` | dichiarazione: `p` è un puntatore a `int` |
| `p = &x` | `p` contiene l'indirizzo di `x` |
| `*p` | la variabile puntata (dereferenziazione): si legge e si scrive |
| `&p` | l'indirizzo del puntatore stesso |

Il simbolo `*` ha due significati: nella **dichiarazione** dice che la
variabile è un puntatore, in un'**espressione** indica la variabile puntata.

Il tipo conta: un `int *` punta a un `int`, un `double *` a un `double`.
Un puntatore occupa sempre la stessa memoria (8 byte sui sistemi a 64 bit),
qualunque sia il tipo puntato.

### Copiare un puntatore o copiare un valore

| Istruzione | Effetto |
|------------|---------|
| `q = p;` | `q` punta alla stessa variabile di `p` |
| `*q = *p;` | la variabile puntata da `q` prende il valore di quella puntata da `p` |
| `p = &y;` | `p` ora punta a un'altra variabile |

Se due puntatori indicano la stessa variabile, una modifica fatta tramite
uno si vede anche tramite l'altro.

### `NULL`: nessuna variabile

Un puntatore non inizializzato contiene un indirizzo casuale. Per dire che
non punta a nulla si usa `NULL`, e prima di usare `*p` si controlla:

```c
int *scelta = NULL;
...
if (scelta != NULL) {
    *scelta = *scelta + 1;
}
```

### A che cosa serve

Un puntatore permette di scrivere **una sola volta** le istruzioni che
lavorano sulla variabile "selezionata": la zona del termostato, il
giocatore di turno, il salvadanaio scelto, la scorta più bassa, il miglior
tempo di una gara.

---

## File dell'esempio

| File | Contenuto |
|------|-----------|
| `010-dichiarazione-e-uso.c` | `int *p`, `p = &x`, lettura e scrittura con `*p` |
| `020-piu-puntatori-stessa-variabile.c` | Due puntatori alla stessa variabile, cambio di variabile, copia del valore |
| `030-puntatore-null.c` | `NULL` per "nessuna selezione" e controllo prima dell'uso |
| `040-problema-termostato.c` | Tasti + e − che agiscono sulla zona selezionata |
| `040-problema-termostato-analisi.md` | Analisi di `040-problema-termostato.c` |
| `050-problema-giocatore-di-turno.c` | Punteggio e nome del giocatore di turno tramite puntatori |
| `050-problema-giocatore-di-turno-analisi.md` | Analisi di `050-problema-giocatore-di-turno.c` |
| `060-problema-conto-attivo.c` | Versamenti e prelievi sull'elemento selezionato di un array |
| `060-problema-conto-attivo-analisi.md` | Analisi di `060-problema-conto-attivo.c` |
| `070-problema-riordino-scorte.c` | Puntatore alla scorta più bassa tra tre variabili |
| `070-problema-riordino-scorte-analisi.md` | Analisi di `070-problema-riordino-scorte.c` |
| `080-problema-record-gara.c` | Puntatore al miglior tempo, `NULL` se nessuno, record aggiornato |
| `080-problema-record-gara-analisi.md` | Analisi di `080-problema-record-gara.c` |

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-dichiarazione-e-uso 010-dichiarazione-e-uso.c
./010-dichiarazione-e-uso

gcc -Wall -Wextra -o 020-piu-puntatori-stessa-variabile 020-piu-puntatori-stessa-variabile.c
./020-piu-puntatori-stessa-variabile

gcc -Wall -Wextra -o 030-puntatore-null 030-puntatore-null.c
./030-puntatore-null

gcc -Wall -Wextra -o 040-problema-termostato 040-problema-termostato.c
./040-problema-termostato

gcc -Wall -Wextra -o 050-problema-giocatore-di-turno 050-problema-giocatore-di-turno.c
./050-problema-giocatore-di-turno

gcc -Wall -Wextra -o 060-problema-conto-attivo 060-problema-conto-attivo.c
./060-problema-conto-attivo

gcc -Wall -Wextra -o 070-problema-riordino-scorte 070-problema-riordino-scorte.c
./070-problema-riordino-scorte

gcc -Wall -Wextra -o 080-problema-record-gara 080-problema-record-gara.c
./080-problema-record-gara
```

---

## Output atteso

> Gli indirizzi stampati cambiano a ogni esecuzione.

### 010-dichiarazione-e-uso
```
=== VARIABILE E PUNTATORE ===
  livello  = 70,   &livello = 0x7ffc0bc77b5c
  p        = 0x7ffc0bc77b5c    (contiene l'indirizzo di livello)
  *p       = 70    (il valore della variabile puntata)
  &p       = 0x7ffc0bc77b68    (anche p e' una variabile con un suo indirizzo)

Dopo *p = 85:      livello = 85
Dopo livello -= 10: *p = 75

Dopo *pd = *pd * 2: portata = 5.0 litri/s
Un puntatore occupa 8 byte, qualunque sia il tipo puntato.
```

### 020-piu-puntatori-stessa-variabile
```
=== Le due casse vendono per la sala A ===
  cassa_1 = 0x7ffc0c439960, cassa_2 = 0x7ffc0c439960, &sala_a = 0x7ffc0c439960
  posti liberi in sala A: 114 (120 - 4 - 2)

=== La cassa 2 passa alla sala B ===
  sala A: 114   sala B: 145
  cassa_1 == cassa_2? no

=== *cassa_2 = *cassa_1 ===
  sala B ridotta come la A: sala A 114, sala B 114 (stesso numero, sale diverse)
  dopo altri 10 biglietti in sala A: sala A 104, sala B 114
```

### 030-puntatore-null
```
Codice C: erogato (contatore 1)
Codice P: erogato (contatore 1)
Codice T: erogato (contatore 1)
Codice X: codice inesistente, puntatore NULL: nessuna erogazione
Codice C: erogato (contatore 2)

Totali: caffe' 2, cappuccino 1, te' 1
```

### 040-problema-termostato
*(output dipendente dall'input – esempio di sessione)*
```
=== TERMOSTATO ===
Soggiorno 20.5 | Camera 19.0 | Bagno 22.0
Comando (S C B + - Q): +
  Seleziona prima una zona.
Comando (S C B + - Q): S
  zona: soggiorno
Comando (S C B + - Q): +
  impostata 21.0 gradi
Comando (S C B + - Q): +
  impostata 21.5 gradi
Comando (S C B + - Q): C
  zona: camera
Comando (S C B + - Q): -
  impostata 18.5 gradi
Comando (S C B + - Q): B
  zona: bagno
Comando (S C B + - Q): +
  impostata 22.5 gradi
Comando (S C B + - Q): +
  impostata 23.0 gradi
Comando (S C B + - Q): +
  impostata 23.5 gradi
Comando (S C B + - Q): +
  impostata 24.0 gradi
Comando (S C B + - Q): +
  impostata 24.5 gradi
Comando (S C B + - Q): +
  impostata 25.0 gradi
Comando (S C B + - Q): +
  impostata 25.5 gradi
Comando (S C B + - Q): +
  impostata 26.0 gradi
Comando (S C B + - Q): +
  Massimo raggiunto (26.0 gradi).
Comando (S C B + - Q): X
  Comando sconosciuto.
Comando (S C B + - Q): Q
Soggiorno 21.5 | Camera 18.5 | Bagno 26.0
```

### 050-problema-giocatore-di-turno
```
=== GARA DI DADI (traguardo 20 punti) ===
Turno  1 - Anna   lancia 4: punti  4   (Anna 4 - Bruno 0)
Turno  2 - Bruno  lancia 6: punti  6   (Anna 4 - Bruno 6)
Turno  3 - Anna   lancia 5: punti  9   (Anna 9 - Bruno 6)
Turno  4 - Bruno  lancia 1: punti  3   (Anna 9 - Bruno 3)
Turno  5 - Anna   lancia 6: punti 15   (Anna 15 - Bruno 3)
Turno  6 - Bruno  lancia 3: punti  6   (Anna 15 - Bruno 6)
Turno  7 - Anna   lancia 2: punti 17   (Anna 17 - Bruno 6)
Turno  8 - Bruno  lancia 5: punti 11   (Anna 17 - Bruno 11)
Turno  9 - Anna   lancia 1: punti 14   (Anna 14 - Bruno 11)
Turno 10 - Bruno  lancia 6: punti 17   (Anna 14 - Bruno 17)
Turno 11 - Anna   lancia 4: punti 18   (Anna 18 - Bruno 17)
Turno 12 - Bruno  lancia 4: punti 21   (Anna 18 - Bruno 21)

Vince Bruno con 21 punti!
```

### 060-problema-conto-attivo
*(output dipendente dall'input – esempio di sessione)*
```
=== CASSA DEI GENITORI ===
Comando (N k | V euro | P euro | F): V 50
  Nessun salvadanaio selezionato.
Comando (N k | V euro | P euro | F): N 2
  Selezionato Biblioteca (saldo 120 euro)
Comando (N k | V euro | P euro | F): V 30
  Biblioteca: nuovo saldo 150 euro
Comando (N k | V euro | P euro | F): P 200
  Saldo insufficiente in Biblioteca: 150 euro.
Comando (N k | V euro | P euro | F): N 4
  Selezionato Festa (saldo 0 euro)
Comando (N k | V euro | P euro | F): V 75
  Festa: nuovo saldo 75 euro
Comando (N k | V euro | P euro | F): P 20
  Festa: nuovo saldo 55 euro
Comando (N k | V euro | P euro | F): N 9
  Numero di salvadanaio non valido.
Comando (N k | V euro | P euro | F): X
  Comando sconosciuto.
Comando (N k | V euro | P euro | F): F

=== RIEPILOGO ===
  Gita          350 euro
  Biblioteca    150 euro
  Sport          80 euro
  Festa          55 euro   <- ultimo selezionato
```

### 070-problema-riordino-scorte
```
=== RIFORNIMENTO DEL DISTRIBUTORE ===
Scorte iniziali: acqua 14, succhi 6, snack 9

Confezione 1 -> succhi   scorte: acqua 14, succhi 18, snack  9
Confezione 2 -> snack    scorte: acqua 14, succhi 18, snack 21
Confezione 3 -> acqua    scorte: acqua 26, succhi 18, snack 21
Confezione 4 -> succhi   scorte: acqua 26, succhi 30, snack 21
Confezione 5 -> snack    scorte: acqua 26, succhi 30, snack 33

In caso di parita' viene rifornito il primo prodotto controllato,
perche' il confronto usa < e non <=.
```

### 080-problema-record-gara
```
Record dei giochi: 29"70

=== Finale maschile ===
  corsia 1: 31"25
  corsia 2: 29"87
  corsia 3: squalificato
  corsia 4: 30"10
  corsia 5: 29"55
  corsia 6: 31"02
  Vince la corsia 5 con 29"55: NUOVO RECORD!

=== Finale di recupero ===
  corsia 1: squalificato
  corsia 2: squalificato
  corsia 3: squalificato
  corsia 4: squalificato
  corsia 5: squalificato
  corsia 6: squalificato
  Nessun atleta ha concluso la gara.

Record aggiornato: 29"55
```

---

## Errori comuni da evitare

**Dereferenziare un puntatore non inizializzato**
```c
int *p;
*p = 5;           /* scrive in un punto casuale della memoria */
```

**Dereferenziare `NULL`**
```c
int *scelta = NULL;
*scelta = 1;      /* il programma si interrompe */
```

**Confondere `p` e `*p`**
```c
p = 10;           /* assegna un indirizzo (errore o avviso) */
*p = 10;          /* scrive 10 nella variabile puntata */
```

**Tipo del puntatore diverso dal tipo della variabile**
```c
double prezzo;
int *p = &prezzo;     /* avviso: tipi incompatibili */
```

**Pensare che `int *p, q;` dichiari due puntatori**
```c
int *p, q;        /* p è un puntatore, q è un int */
```
Per chiarezza nel corso si dichiara una variabile per riga.

---

## Concetti collegati

- `01-indirizzi-e-memoria` → `&` e `%p`
- `03-errori-e-puntatori-sicuri` → `NULL`, `const` e gli errori tipici
- `03-funzioni/03-passaggio-per-riferimento` → puntatori come parametri

---

## Esercizi proposti

1. In `020-piu-puntatori-stessa-variabile.c` aggiungi una terza sala e una
   terza cassa che si sposta tra le sale.

2. In `040-problema-termostato.c` aggiungi il comando `R` che riporta la zona
   selezionata a 20.0 gradi.

3. In `050-problema-giocatore-di-turno.c` aggiungi un terzo giocatore.

4. In `070-problema-riordino-scorte.c` rifornisci in caso di parità il
   prodotto controllato per ultimo e confronta i risultati.

5. (Avanzato) In `080-problema-record-gara.c` usa un secondo puntatore per
   trovare anche il secondo classificato.
