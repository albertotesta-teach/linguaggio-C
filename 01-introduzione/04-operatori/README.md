# 04 – Operatori

## Concetto

Gli operatori sono i simboli che indicano al programma quale operazione
eseguire su uno o più valori (operandi). In C si dividono in categorie:

```
┌─────────────────────────────────────────────────────────────┐
│  ARITMETICI     +  -  *  /  %  (unari: +  -)               │
│  RELAZIONALI    ==  !=  <  >  <=  >=                        │
│  LOGICI         &&  ||  !                                   │
│  ASSEGNAZIONE   =  +=  -=  *=  /=  %=                      │
│  INCREMENTO     ++  --  (prefisso e postfisso)              │
│  TERNARIO       condizione ? valore_vero : valore_falso     │
│  BIT A BIT      &  |  ^  ~  <<  >>                         │
└─────────────────────────────────────────────────────────────┘
```

Punti chiave da ricordare:

- La **divisione intera** tra due `int` tronca la parte decimale:
  `7 / 2 = 3`, non `3.5`. Basta un operando `double` per ottenere
  la divisione reale: `7.0 / 2 = 3.5`.
- Gli operatori relazionali e logici producono **0 o 1** (int),
  non solo condizioni per `if`.
- L'**operatore ternario** `?:` restituisce un valore ed è
  un'espressione, non un'istruzione di controllo.
- Gli operatori **bit a bit** agiscono sui singoli bit degli interi
  e sono fondamentali in programmazione di sistema.

---

## File dell'esempio

| File | Tipo | Descrizione |
|------|------|-------------|
| `010-operatori-aritmetici.c` | concetto base | +, -, *, /, %, divisione intera vs reale, precedenza |
| `020-operatori-relazionali-e-logici.c` | concetto base | ==, !=, <, >, &&, \|\|, !; risultato 0/1 salvato in int |
| `030-operatori-di-assegnazione.c` | concetto base | +=, -=, *=, /=, %=; ++, -- prefisso e postfisso |
| `040-operatori-bit-a-bit.c` | concetto base | &, \|, ^, ~, <<, >>; maschere e applicazioni |
| `050-problema-calcolo-bolletta.c` | problema specifico | Bolletta elettrica con selezione fascia via ternario |
| `050-problema-calcolo-bolletta-analisi.md` | analisi | Analisi del problema calcolo bolletta |
| `060-problema-indice-massa-corporea.c` | problema specifico | IMC con classificazione tramite operatori rel./logici |
| `060-problema-indice-massa-corporea-analisi.md` | analisi | Analisi del problema IMC |
| `070-problema-cambio-valuta.c` | problema specifico | Cambio valuta con selezione tasso e commissione |
| `070-problema-cambio-valuta-analisi.md` | analisi | Analisi del problema cambio valuta |

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-operatori-aritmetici         010-operatori-aritmetici.c
gcc -Wall -Wextra -o 020-operatori-rel-logici         020-operatori-relazionali-e-logici.c
gcc -Wall -Wextra -o 030-operatori-assegnazione       030-operatori-di-assegnazione.c
gcc -Wall -Wextra -o 040-operatori-bit-a-bit          040-operatori-bit-a-bit.c
gcc -Wall -Wextra -o 050-problema-bolletta            050-problema-calcolo-bolletta.c
gcc -Wall -Wextra -o 060-problema-imc                 060-problema-indice-massa-corporea.c
gcc -Wall -Wextra -o 070-problema-cambio-valuta       070-problema-cambio-valuta.c
```

---

## Output atteso

### 010-operatori-aritmetici
```
=== Operazioni di base ===
a = 17,  b = 5

a + b = 22
a - b = 12
a * b = 85

=== Divisione intera vs reale ===
17 / 5   (int / int)    = 3   <- parte decimale persa!
17.0 / 5 (double / int) = 3.4000 <- risultato corretto
17 / 5.0 (int / double) = 3.4000 <- basta un operando double
17.0/5.0 (double/double)= 3.4000
(double)a / b           = 3.4000 <- cast esplicito

=== Operatore modulo (%) ===
17 % 5  = 2   (17 = 5*3 + 2)
10 % 2  = 0   (pari: resto zero)
11 % 2  = 1   (dispari: resto uno)
17 % 10 = 7   (ultima cifra di 17)
123 % 100 = 23 (ultime due cifre)

=== Operatori unari ===
+a = 17
-a = -17

=== Precedenza ===
2 + 3 * 4     = 14  (prima *)
(2 + 3) * 4   = 20  (parentesi prima)
10 - 4 / 2    = 8   (prima /)
(10 - 4) / 2  = 3   (parentesi prima)
```

### 020-operatori-relazionali-e-logici
```
=== Operatori relazionali ===
a=10, b=20

a == b  -> 0
a != b  -> 1
a <  b  -> 1
a >  b  -> 0
a <= b  -> 1
a >= b  -> 0

=== Risultati salvati in variabili ===
eta=22: maggiorenne=1
eta in [18,65]:    1
altezza>180cm:     0
stipendio>=1500:   1

=== Operatori logici ===
maggiorenne && stipendio_ok  -> 1
alta_statura && stipendio_ok -> 0
alta_statura || maggiorenne  -> 1
alta_statura || (eta > 100)  -> 0

!maggiorenne                 -> 0
!alta_statura                -> 1

=== Condizioni composte ===
accesso consentito (eta>=18 E stip>=1000): 1
altezza fuori [150,210]:                   0
nessun requisito soddisfatto:              0
```

### 030-operatori-di-assegnazione
```
=== Assegnazione semplice ===
valore = 10  ->  10

=== Assegnazione composta (partendo da valore=10) ===
dopo += 5  ->  15
dopo -= 3  ->  12
dopo *= 2  ->  24
dopo /= 4  ->  6
dopo %= 4  ->  2

=== Uso tipico: accumulatore ===
somma di 10+25+7 = 42
100.00 EUR con IVA al 22% = 122.00 EUR

=== Incremento e decremento ===
a=5: b = ++a  ->  a=6, b=6
a=5: b = a++  ->  a=6, b=5
a=5: b = --a  ->  a=4, b=4
a=5: b = a--  ->  a=4, b=5
```

### 040-operatori-bit-a-bit
```
=== Valori di partenza ===
a = 60  (binario: 0011 1100)
b = 15  (binario: 0000 1111)

=== AND bit a bit (a & b) ===
  0011 1100
& 0000 1111
= 0000 1100  ->  12

=== OR bit a bit (a | b) ===
  0011 1100
| 0000 1111
= 0011 1111  ->  63

=== XOR bit a bit (a ^ b) ===
  0011 1100
^ 0000 1111
= 0011 0011  ->  51

=== NOT bit a bit (~a) ===
~60 (unsigned int) = 4294967235

=== Shift sinistro (<<) ===
a << 1 = 120  (equivale a 60 * 2)
a << 2 = 240  (equivale a 60 * 4)
1 << 0 = 1
1 << 1 = 2
1 << 2 = 4
1 << 3 = 8

=== Shift destro (>>) ===
a >> 1 = 30  (equivale a 60 / 2)
a >> 2 = 15  (equivale a 60 / 4)

=== Applicazioni pratiche ===
valore = 181, bit 2 attivo: 1
valore con bit 2 forzato a 1: 181
valore con bit 2 forzato a 0: 177
```

### 050-problema-calcolo-bolletta
Input: 1000  1180  3.0  1
```
==========================================
  BOLLETTA ELETTRICA
==========================================
  Lettura precedente:      1000 kWh
  Lettura attuale:         1180 kWh
  Consumo:                  180 kWh
  Fascia:                     1
  Prezzo/kWh:            0.2800 EUR
------------------------------------------
  Costo energia:          50.40 EUR
  Quota fissa:            31.50 EUR
  Imponibile:             81.90 EUR
  IVA 10%:                 8.19 EUR
==========================================
  TOTALE:                 90.09 EUR
==========================================
```

### 060-problema-indice-massa-corporea
Input: 70.0  1.75
```
=== Risultato ===
Peso:    70.0 kg
Altezza: 1.75 m
IMC:     22.86

=== Classificazione (1=si', 0=no) ===
Sottopeso  (IMC < 18.5):        0
Normopeso  (18.5 <= IMC < 25):  1
Sovrappeso (25 <= IMC < 30):    0
Obesita'   (IMC >= 30):         0

Categoria: Normopeso
```

### 070-problema-cambio-valuta
Input: 200.00  1
```
=== Dettaglio conversione ===
Importo originale:     200.00 EUR
Valuta:                   USD
Tasso di cambio:        1.0850
Importo convertito:    217.00
Commissione (1.5%):      3.26
------------------------------
Importo netto:         213.75
```

---

## Errori comuni da evitare

```c
/* ERRORE 1: divisione intera involontaria */
int a = 7, b = 2;
double risultato = a / b;       /* risultato = 3.0, non 3.5! */
double risultato = (double)a / b;  /* corretto: cast prima della divisione */

/* ERRORE 2: confondere = (assegnazione) con == (confronto) */
int x = 5;
int uguale = (x = 10);    /* assegna 10 a x, poi uguale = 10 (non 0 o 1!) */
int uguale = (x == 10);   /* corretto: confronto, risultato 0 o 1 */

/* ERRORE 3: confondere prefisso e postfisso */
int i = 5;
int a = i++;   /* a = 5, poi i = 6 */
int a = ++i;   /* i = 6, poi a = 6 */

/* ERRORE 4: usare % con operandi reali */
double x = 7.5;
double r = x % 2;    /* ERRORE: % è solo per interi */
double r = fmod(x, 2.0);  /* corretto: fmod() da <math.h> per i reali */

/* ERRORE 5: modificare la stessa variabile due volte nella stessa espressione */
int i = 5;
int x = i++ + i++;   /* comportamento indefinito: non farlo mai */
```

---

## Concetti collegati

- [`02-variabili-e-tipi`](../02-variabili-e-tipi/) — tipi di dato e compatibilità nelle espressioni
- [`03-input-output`](../03-input-output/) — printf e scanf usati per mostrare i risultati
- [`02-controllo-del-flusso`](../../02-controllo-del-flusso/) — if/else e switch che usano espressioni booleane

---

## Esercizi proposti

1. **Divisione con resto**: chiedi due interi a e b. Stampa il quoziente
   intero, il resto e il quoziente reale (con due decimali). Usa solo
   operatori aritmetici e formattazione con printf.

2. **Semaforo booleano**: chiedi ore (0–23) e minuti (0–59). Calcola
   con operatori logici se l'orario è in fascia di punta (7–9 oppure
   17–19). Stampa il risultato come 0 o 1 e la stringa corrispondente
   con l'operatore ternario.

3. **Contatore con assegnazione composta**: parti da un valore inserito
   dall'utente. Applica in sequenza: +15, ×2, −7, /3 (intera), %10.
   Stampa il valore dopo ogni operazione usando gli operatori composti.

4. **Maschera di bit**: chiedi un intero senza segno. Usa operatori bit
   a bit per stampare se il bit 0 (meno significativo) è attivo, il
   valore shiftato di 1 a destra e il valore shiftato di 2 a sinistra.

5. **Convertitore temperatura con ternario**: chiedi una temperatura e
   un carattere intero (1=C→F, 2=F→C). Seleziona la formula con
   l'operatore ternario e stampa il risultato con due decimali.
