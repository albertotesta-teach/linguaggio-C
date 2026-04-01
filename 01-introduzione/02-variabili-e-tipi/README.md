# 02 – Variabili e tipi

## Concetto

In C ogni variabile deve essere dichiarata con un **tipo** che determina
quanti byte occupa in memoria, quali valori può contenere e quali operazioni
sono consentite su di essa.

```
┌─────────────────────────────────────────────────────────┐
│  TIPI INTERI          TIPI REALI         ALTRI          │
│  ─────────────        ──────────         ──────         │
│  char    1 byte       float   4 byte     _Bool  1 byte  │
│  short   2 byte       double  8 byte                    │
│  int     4 byte       long                              │
│  long    8 byte       double 16 byte                    │
│  long long 8 byte                                       │
└─────────────────────────────────────────────────────────┘
```

Le dimensioni riportate sono quelle tipiche su sistemi a 64 bit;
il C garantisce solo relazioni di ordine (`sizeof(short) <= sizeof(int)
<= sizeof(long)`), non valori assoluti.

Per definire valori costanti si usano due tecniche:
- `#define NOME valore` — sostituzione testuale a compile-time, senza tipo
- `const tipo nome = valore;` — variabile tipizzata protetta da modifiche

---

## File dell'esempio

| File | Tipo | Descrizione |
|------|------|-------------|
| `010-tipi-interi.c` | concetto base | short, int, long, long long, unsigned; sizeof e limits.h |
| `020-tipi-reali.c` | concetto base | float, double, long double; precisione, notazione scientifica |
| `030-caratteri-e-booleani.c` | concetto base | char, codici ASCII, sequenze di escape, bool simulato con int |
| `040-costanti.c` | concetto base | #define vs const: differenze, usi consigliati, esempi pratici |
| `050-problema-conversione-temperature.c` | problema specifico | Conversione °C → °F e K con formule e costanti |
| `050-problema-conversione-temperature-analisi.md` | analisi | Analisi del problema conversione temperature |
| `060-problema-calcolo-area.c` | problema specifico | Area e perimetro di quadrato, rettangolo, cerchio |
| `060-problema-calcolo-area-analisi.md` | analisi | Analisi del problema calcolo area |
| `070-problema-scheda-prodotto.c` | problema specifico | Scheda prodotto con prezzo, sconto e valore magazzino |
| `070-problema-scheda-prodotto-analisi.md` | analisi | Analisi del problema scheda prodotto |

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-tipi-interi              010-tipi-interi.c
gcc -Wall -Wextra -o 020-tipi-reali               020-tipi-reali.c
gcc -Wall -Wextra -o 030-caratteri-e-booleani     030-caratteri-e-booleani.c
gcc -Wall -Wextra -o 040-costanti                 040-costanti.c
gcc -Wall -Wextra -o 050-problema-conv-temp       050-problema-conversione-temperature.c
gcc -Wall -Wextra -o 060-problema-calcolo-area    060-problema-calcolo-area.c
gcc -Wall -Wextra -o 070-problema-scheda-prodotto 070-problema-scheda-prodotto.c
```

---

## Output atteso

### 010-tipi-interi
```
=== Dimensioni dei tipi interi ===
short:         2 byte
int:           4 byte
long:          8 byte
long long:     8 byte
unsigned int:  4 byte

=== Valori limite ===
short:      da -32768  a 32767
int:        da -2147483648  a 2147483647
long:       da -9223372036854775808 a 9223372036854775807
long long:  da -9223372036854775808 a 9223372036854775807
uint max:   4294967295

=== Valori di esempio ===
short:      30000
int:        2000000000
long:       2000000000
long long:  9000000000
uint:       4000000000
```

### 020-tipi-reali
```
=== Dimensioni dei tipi reali ===
float:        4 byte
double:       8 byte
long double:  16 byte

=== Cifre significative garantite ===
float:        6 cifre
double:       15 cifre
long double:  18 cifre

=== Precisione a confronto (pi greco) ===
float:        3.14159274101257324219
double:       3.14159265358979323846
long double:  3.14159265358979323851

=== Notazione scientifica ===
Distanza Terra-Sole:  1.496e+08 km
Massa elettrone:      9.109e-31 kg

=== Attenzione agli arrotondamenti ===
1.0 / 3.0 (float):   0.33333334326744079590
1.0 / 3.0 (double):  0.33333333333333331483
```

### 030-caratteri-e-booleani
```
=== Caratteri e codici ASCII ===
Carattere 'A':  come char=A  come intero=65
Carattere '7':  come char=7  come intero=55
Carattere '+':  come char=+  come intero=43
Dimensione di char: 1 byte

=== Aritmetica sui char ===
'A' + 1 = 'B'  (codice 66)
'A' + 2 = 'C'  (codice 67)

=== Sequenze di escape ===
\n  = a capo          (codice 10)
\t  = tabulazione     (codice 9)
\'  = apice singolo   (codice 39)
\\  = barra rovescia  (codice 92)
\0  = carattere null  (codice 0)

=== Simulazione booleana con int ===
Eta':         20
Maggiorenne:  1  (0=falso, 1=vero)
Ha la patente: 1
```

### 040-costanti
```
=== Costanti con #define ===
Pi greco:      3.1415926536
Gravita':      9.81 m/s^2
Eta' minima:   18 anni
Posti massimi: 50
IVA:           22%

=== Costanti con const ===
Velocita' luce: 2.99792e+08 m/s
Giorni/settim.: 7
Euro/Dollaro:   1.0800

=== Uso in calcoli ===
Area cerchio (r=5.0):  78.5398
Prezzo netto:  100.00 EUR
Prezzo con IVA al 22%: 122.00 EUR
```

### 050-problema-conversione-temperature
Input: 20.0
```
=== Convertitore di temperature ===

Temperatura in gradi Celsius: 20

--- Risultato ---
Celsius:        20.00 °C
Fahrenheit:     68.00 °F
Kelvin:        293.15 K

--- Valori di riferimento ---
Acqua: congela a  0 °C = 32.00 °F = 273.15 K
Acqua: bolle  a 100 °C = 212.00 °F = 373.15 K
```

### 060-problema-calcolo-area
Input: 3 (cerchio), raggio 5.0
```
=== Calcolo area e perimetro ===

Scegli la figura:
  1 - Quadrato
  2 - Rettangolo
  3 - Cerchio
Scelta: 3
Raggio (m): 5.0

--- Cerchio ---
Area:       78.5398 m^2
Perimetro:  31.4159 m
```

### 070-problema-scheda-prodotto
Input: codice=1042, prezzo=24.90, quantità=100, sconto=10.0
```
=== Inserimento dati prodotto ===

Codice prodotto:          1042
Prezzo unitario (EUR):    24.90
Quantita' in magazzino:   100
Sconto (%, es. 15.0):    10.0

====================================
  SCHEDA PRODOTTO
====================================
  Codice:           001042
  Prezzo pieno:      24.90 EUR
  Sconto:            10.0 %
  Risparmio:          2.49 EUR
  Prezzo scontato:   22.41 EUR
------------------------------------
  Quantita':            100 pz
  Valore magazzino:  2490.00 EUR
====================================
```

---

## Errori comuni da evitare

```c
/* ERRORE 1: divisione intera dove serve quella reale */
double fahrenheit = 37 * 9/5 + 32;   /* 9/5 = 1, non 1.8! */
double fahrenheit = 37 * 9.0/5.0 + 32;   /* corretto */

/* ERRORE 2: leggere un double con %f invece di %lf in scanf */
double x;
scanf("%f", &x);    /* sbagliato: %f è per float */
scanf("%lf", &x);   /* corretto: %lf è per double */

/* ERRORE 3: confrontare reali con == */
double x = 0.1 + 0.2;
if (x == 0.3) { ... }   /* potrebbe non entrare mai per arrotondamenti */

/* ERRORE 4: dimenticare il suffisso f per le costanti float */
float pi = 3.14159265358979;    /* il letterale è double, poi troncato */
float pi = 3.14159265358979f;   /* corretto: letterale float */

/* ERRORE 5: modificare una variabile const */
const int MAX = 100;
MAX = 200;   /* errore di compilazione: assignment of read-only variable */
```

---

## Concetti collegati

- [`01-hello-world`](../01-hello-world/) — struttura di base del programma, printf
- [`03-input-output`](../03-input-output/) — specificatori di formato in dettaglio

---

## Esercizi proposti

1. **Conversione di unità**: scrivi un programma che chieda una distanza in
   chilometri e la converta in miglia (1 km = 0.621371 mi), metri e centimetri.
   Usa `#define` per i fattori di conversione.

2. **Calcolo dell'IMC**: chiedi peso (kg) e altezza (m) e calcola l'Indice di
   Massa Corporea (IMC = peso / altezza²). Stampa il risultato con due
   cifre decimali. Usa `double` per tutte le misure.

3. **Tavola ASCII**: scrivi un programma che stampi i codici ASCII e i
   caratteri corrispondenti per le lettere maiuscole da 'A' a 'E', usando
   l'aritmetica sui `char` come mostrato in `030-caratteri-e-booleani.c`.

4. **Sconto a cascata**: modifica `070-problema-scheda-prodotto.c` aggiungendo
   un secondo sconto (es. sconto fedeltà) applicato al prezzo già scontato.
   Mostra il prezzo dopo ogni sconto e il risparmio totale.

5. **Confronto float/double**: scrivi un programma che calcoli 1.0/7.0 con
   `float` e con `double`, stampando entrambi i risultati con 20 cifre
   decimali. Osserva e commenta la differenza.
