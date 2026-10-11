# 03 – Puntatori a funzione

## Concetto

Anche il codice di una funzione si trova in memoria e ha un indirizzo. Un
**puntatore a funzione** contiene quell'indirizzo e permette di chiamare la
funzione scelta in quel momento.

```c
int somma(int a, int b);
int massimo(int a, int b);

int (*operazione)(int, int);     /* puntatore a funzione (int, int) -> int */

operazione = somma;              /* il nome della funzione, senza () */
x = operazione(78, 71);          /* 149 */
operazione = massimo;
x = operazione(78, 71);          /* 78 */
```

| Scrittura | Significato |
|-----------|-------------|
| `int (*f)(int, int)` | `f` è un puntatore a una funzione che riceve due `int` e restituisce `int` |
| `int *f(int, int)` | `f` è una **funzione** che restituisce un `int *` (senza parentesi è un'altra cosa) |
| `f = somma` | `f` punta a `somma` |
| `f(a, b)` oppure `(*f)(a, b)` | chiamata tramite il puntatore |
| `f == somma`, `f == NULL` | confronto |

Il puntatore può ricevere solo funzioni con lo **stesso prototipo**.

### La funzione come parametro (callback)

L'uso più importante: una funzione generale riceve, oltre ai dati, la
funzione da applicare.

```c
void applica(int *v, int n, int (*trasforma)(int))
{
    int *p;

    for (p = v; p < v + n; p++) {
        *p = trasforma(*p);
    }
}

applica(punti, N, raddoppia);
applica(punti, N, minimo_zero);
```

Il ciclo si scrive **una volta**; il "che cosa fare" cambia a ogni chiamata.
Lo stesso schema serve per contare con una condizione (`conta_se`),
convertire con una formula (`converti`), scegliere il migliore con un
criterio (`migliore`, `vincitore`).

### Una funzione che restituisce un puntatore a funzione

```c
double (*scegli_operazione(char simbolo))(double, double);
```

Si legge dall'interno: `scegli_operazione` è una funzione che riceve un
`char` e restituisce un puntatore a una funzione `(double, double)` che
restituisce `double`. Restituisce `NULL` se il simbolo non è previsto.

---

## File dell'esempio

| File | Contenuto |
|------|-----------|
| `010-dichiarazione-e-chiamata.c` | `int (*operazione)(int, int)`, assegnazione, chiamata, confronto |
| `020-funzione-come-parametro.c` | `applica(v, n, trasforma)` con tre trasformazioni dei punteggi |
| `030-criterio-di-scelta.c` | `migliore(v, n, preferisci)`: consegna più rapida, più lenta, più vicina ai 30 minuti |
| `040-problema-calcolatrice.c` | L'operatore letto sceglie il puntatore alla funzione di calcolo |
| `040-problema-calcolatrice-analisi.md` | Analisi di `040-problema-calcolatrice.c` |
| `050-problema-filtro-misure.c` | `conta_se` ed `elenca_se` con tre condizioni sul rumore |
| `050-problema-filtro-misure-analisi.md` | Analisi di `050-problema-filtro-misure.c` |
| `060-problema-conversioni.c` | `converti(in, out, n, formula)`: Celsius, Fahrenheit, kelvin |
| `060-problema-conversioni-analisi.md` | Analisi di `060-problema-conversioni.c` |
| `070-problema-trasforma-testo.c` | Una regola applicata a ogni carattere: maiuscolo, Cesare, cifre oscurate |
| `070-problema-trasforma-testo-analisi.md` | Analisi di `070-problema-trasforma-testo.c` |
| `080-problema-classifica-criterio.c` | Il vincitore del triathlon secondo tre criteri diversi |
| `080-problema-classifica-criterio-analisi.md` | Analisi di `080-problema-classifica-criterio.c` |

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-dichiarazione-e-chiamata 010-dichiarazione-e-chiamata.c
./010-dichiarazione-e-chiamata

gcc -Wall -Wextra -o 020-funzione-come-parametro 020-funzione-come-parametro.c
./020-funzione-come-parametro

gcc -Wall -Wextra -o 030-criterio-di-scelta 030-criterio-di-scelta.c
./030-criterio-di-scelta

gcc -Wall -Wextra -o 040-problema-calcolatrice 040-problema-calcolatrice.c
./040-problema-calcolatrice

gcc -Wall -Wextra -o 050-problema-filtro-misure 050-problema-filtro-misure.c
./050-problema-filtro-misure

gcc -Wall -Wextra -o 060-problema-conversioni 060-problema-conversioni.c
./060-problema-conversioni

gcc -Wall -Wextra -o 070-problema-trasforma-testo 070-problema-trasforma-testo.c
./070-problema-trasforma-testo

gcc -Wall -Wextra -o 080-problema-classifica-criterio 080-problema-classifica-criterio.c
./080-problema-classifica-criterio
```

---

## Output atteso

### 010-dichiarazione-e-chiamata
```
Casa 78 - Ospiti 71

operazione = somma       -> operazione(casa, ospiti) = 149  (punti totali)
operazione = differenza  -> operazione(casa, ospiti) =   7  (scarto)
operazione = massimo     -> operazione(casa, ospiti) =  78  (punti vincitrice)

(*operazione)(casa, ospiti) = 78
Ora operazione punta a massimo.
```

### 020-funzione-come-parametro
```
Punteggi grezzi          34   -6   57   12  -15   41
applica(raddoppia)       68  -12  114   24  -30   82
applica(minimo_zero)     68    0  114   24    0   82
applica(alla_decina)     70    0  110   20    0   80
```

### 030-criterio-di-scelta
```
Consegna piu' rapida:       ordine 7, 18 minuti
Consegna piu' lenta:        ordine 5, 52 minuti
Piu' vicina ai 30 minuti:   ordine 4, 29 minuti
```

### 040-problema-calcolatrice
*(output dipendente dall'input – esempio di sessione)*
```
=== CALCOLATRICE (q per finire) ===
> 12.5 * 4
  12.5 * 4 = 50
> 7 / 2
  7 / 2 = 3.5
> 2 ^ 10
  2 ^ 10 = 1024
> 8 / 0
  Divisione per zero.
> 5 % 2
  Operatore '%' sconosciuto.
> q
```

### 050-problema-filtro-misure
```
=== RUMORE IN MENSA (una misura ogni 10 minuti dalle 12:30) ===
Oltre 80 dB:    3 misure ->  13:00 84  13:10 88  13:20 82
Da 60 a 80 dB:  7 misure ->  12:30 62  12:40 71  12:50 78  13:30 76  13:40 69  14:10 66  14:20 73
Sotto 60 dB:    2 misure ->  13:50 58  14:00 55
```

### 060-problema-conversioni
```
Ore          08:00   10:00   12:00   14:00   16:00   18:00
Celsius       -2.5     1.0     6.5    12.0    14.5     9.0
Fahrenheit    27.5    33.8    43.7    53.6    58.1    48.2
Kelvin       270.6   274.1   279.6   285.1   287.6   282.1
```

### 070-problema-trasforma-testo
*(output dipendente dall'input – esempio di sessione)*
```
Messaggio (riga vuota per finire): Ciao Zeno, chiamami al 333 1234567
  maiuscolo    CIAO ZENO, CHIAMAMI AL 333 1234567
  Cesare +3    Fldr Chqr, fkldpdpl do 333 1234567
  senza cifre  Ciao Zeno, chiamami al *** *******
Messaggio (riga vuota per finire): Verifica di Fisica il 12 marzo
  maiuscolo    VERIFICA DI FISICA IL 12 MARZO
  Cesare +3    Yhulilfd gl Ilvlfd lo 12 pducr
  senza cifre  Verifica di Fisica il ** marzo
Messaggio (riga vuota per finire): 
```

### 080-problema-classifica-criterio
```
Atleta    corsa  salto   peso  totale
Elena        72     65     80     217
Davide       95     40     70     205
Sara         68     74     71     213
Omar         60     88     79     227
Giulia       81     70     62     213

Premio Assoluto   : Omar    (valore 227)
Premio Specialista: Davide  (valore 95)
Premio Regolarita': Sara    (valore 68)
```

---

## Errori comuni da evitare

**Dimenticare le parentesi nella dichiarazione**
```c
int *operazione(int, int);     /* dichiara una funzione, non un puntatore */
int (*operazione)(int, int);   /* corretto */
```

**Chiamare la funzione invece di passarla**
```c
applica(punti, N, raddoppia(3));   /* passa il numero 6, non la funzione */
applica(punti, N, raddoppia);      /* corretto */
```

**Prototipo diverso**
```c
double meta(double x);
applica(punti, N, meta);   /* avviso: applica vuole int (*)(int) */
```

**Chiamare un puntatore a funzione `NULL`**
```c
operazione = scegli_operazione('%');   /* NULL */
operazione(a, b);                      /* il programma si interrompe */
```

**Funzioni di condizione che non restituiscono 0 o 1**
```c
int rumorosa(int db)
{
    return db - 80;        /* negativo, zero o positivo: non è un "sì/no" */
}
```

---

## Concetti collegati

- `02-funzioni-che-restituiscono-puntatori` → `migliore` restituisce un puntatore all'elemento
- `01-parametri-per-riferimento` → parametri puntatore
- `04-array-e-stringhe/02-array-multidimensionali` → righe di una matrice passate come `int *`
- `11-algoritmi` → ordinamenti con un criterio di confronto

---

## Esercizi proposti

1. In `010-dichiarazione-e-chiamata.c` aggiungi la funzione `minimo` e usala
   tramite il puntatore.

2. In `020-funzione-come-parametro.c` aggiungi la trasformazione
   `bonus_cinque`, che aggiunge 5 punti alle squadre con almeno 50 punti.

3. In `050-problema-filtro-misure.c` scrivi `int media_se(const int *v, int
   n, int (*condizione)(int))`, che calcola la media delle sole misure che
   soddisfano la condizione.

4. In `070-problema-trasforma-testo.c` aggiungi la regola `decifra`, che
   annulla il cifrario di Cesare.

5. (Avanzato) In `080-problema-classifica-criterio.c` aggiungi il premio
   "miglior saltatore" con un criterio che restituisce solo la seconda
   prova.
