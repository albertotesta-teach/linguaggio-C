# 02 – Parametri e valore di ritorno

## Concetto

Le funzioni diventano davvero utili quando possono ricevere dati dall'esterno
e restituire un risultato. In C questo avviene tramite i **parametri** e il
**valore di ritorno**.

### Parametri

I parametri sono variabili locali della funzione, inizializzate con i valori
passati dal chiamante al momento della chiamata. In C i tipi scalari (`int`,
`double`, `char`, ...) vengono passati **per valore**: la funzione riceve una
copia del dato originale. Qualsiasi modifica al parametro all'interno della
funzione non ha effetto sulla variabile del chiamante.

```
chiamante              funzione
────────────           ────────────
int x = 5;   ──copia──►  int n = 5;
                          n = n * 2;   ← modifica solo la copia
printf(x);               (n scompare)
  → stampa 5
```

### Valore di ritorno

Una funzione può restituire al chiamante un valore con l'istruzione `return`.
Il tipo del valore restituito è dichiarato davanti al nome della funzione.
Una funzione `void` non restituisce nulla.

```c
double quadrato(double x)    /* restituisce un double */
{
    double risultato;
    risultato = x * x;
    return risultato;        /* unica return, alla fine */
}
```

Il valore restituito può essere usato in tre modi:

```c
double q = quadrato(4.0);       /* assegnato a una variabile */
printf("%.1f\n", quadrato(3.0)); /* usato direttamente in printf */
double s = quadrato(2.0) + 1.0; /* usato in un'espressione */
```

### Parametri multipli

Una funzione può ricevere più parametri di tipi diversi. L'ordine degli
argomenti nella chiamata deve corrispondere esattamente all'ordine dei
parametri nella definizione.

```c
double area_rettangolo(double base, double altezza)
{
    double area;
    area = base * altezza;
    return area;
}

/* Chiamata: base=5.0, altezza=3.0 */
double a = area_rettangolo(5.0, 3.0);
```

### Regola del progetto: una sola `return`

Ogni funzione ha un **unico punto di uscita**, alla fine del corpo.
Il risultato viene accumulato in una variabile locale e restituito
nell'unica `return` finale.

```c
/* CORRETTO */
int massimo(int a, int b)
{
    int max;
    if (a >= b) { max = a; } else { max = b; }
    return max;
}

/* ERRATO: return multipli */
int massimo(int a, int b)
{
    if (a >= b) { return a; }   /* ← vietato */
    return b;
}
```

---

## File dell'esempio

| File | Tipo | Descrizione |
|------|------|-------------|
| `010-parametri-per-valore.c` | Concetto base | Copia dei parametri, indipendenza dal chiamante, indirizzi di memoria |
| `020-valore-di-ritorno.c` | Concetto base | `return` con int, double, char; utilizzo del risultato in espressioni |
| `030-parametri-multipli.c` | Concetto base | Funzioni con 2, 3 e 4 parametri; ordine degli argomenti |
| `040-problema-calcolatrice.c` | Problema specifico | Calcolatrice con quattro operazioni e gestione divisione per zero |
| `040-problema-calcolatrice-analisi.md` | Analisi | Analisi del problema calcolatrice |
| `050-problema-conversione-unita.c` | Problema specifico | Convertitore di unità con menu a 10 voci |
| `050-problema-conversione-unita-analisi.md` | Analisi | Analisi del problema conversione unità |
| `060-problema-analisi-voti.c` | Problema specifico | Scheda studente con media, min/max, giudizio e esito |
| `060-problema-analisi-voti-analisi.md` | Analisi | Analisi del problema analisi voti |

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-parametri-per-valore 010-parametri-per-valore.c
./010-parametri-per-valore

gcc -Wall -Wextra -o 020-valore-di-ritorno 020-valore-di-ritorno.c
./020-valore-di-ritorno

gcc -Wall -Wextra -o 030-parametri-multipli 030-parametri-multipli.c
./030-parametri-multipli

gcc -Wall -Wextra -o 040-problema-calcolatrice 040-problema-calcolatrice.c
./040-problema-calcolatrice

gcc -Wall -Wextra -o 050-problema-conversione-unita 050-problema-conversione-unita.c
./050-problema-conversione-unita

gcc -Wall -Wextra -o 060-problema-analisi-voti 060-problema-analisi-voti.c
./060-problema-analisi-voti
```

---

## Output atteso

### 010-parametri-per-valore
```
=== Dimostrazione: passaggio per valore ===

Prima della chiamata: temperatura_stanza = 20
  Dentro raddoppia() - prima:  numero = 20
  Dentro raddoppia() - dopo:   numero = 40
Dopo la chiamata:     temperatura_stanza = 20

=== Conversioni di temperatura ===

  0.0 gradi Celsius = 32.0 gradi Fahrenheit
  100.0 gradi Celsius = 212.0 gradi Fahrenheit
  37.0 gradi Celsius = 98.6 gradi Fahrenheit
  -40.0 gradi Celsius = -40.0 gradi Fahrenheit

=== Indirizzi di memoria ===

Nel main: temperatura_stanza = 20, indirizzo = 0x... (varia)
  Dentro mostra_copia(): valore = 20, indirizzo = 0x... (diverso dal main)
```

### 020-valore-di-ritorno
```
somma(7, 3) = 10
somma(100, 250) = 350
somma(1,2) + somma(3,4) = 10

media(7.5, 8.0, 6.5) = 7.33
media(10.0, 5.5, 7.0) = 7.50

valore_assoluto(-42) = 42
valore_assoluto(17)  = 17
valore_assoluto(0)   = 0

maiuscolo('g') = 'G'
maiuscolo('A') = 'A'
maiuscolo('3') = '3'
```

### 030-parametri-multipli
```
=== Area rettangolo ===
base=5.0, altezza=3.0  -> area = 15.00
base=12.5, altezza=4.0 -> area = 50.00

=== Area trapezio ===
basi=10.0 e 6.0, altezza=4.0 -> area = 32.00

=== Massimo tra tre valori ===
massimo(7, 3, 9)   = 9
massimo(1, 1, 1)   = 1
massimo(-5, -2, 0) = 0

=== Tavola pitagorica (righe 1-5, colonne 1-6) ===
Riga  1:    1   2   3   4   5   6
Riga  2:    2   4   6   8  10  12
Riga  3:    3   6   9  12  15  18
Riga  4:    4   8  12  16  20  24
Riga  5:    5  10  15  20  25  30
```

### 040-problema-calcolatrice (esempio con 12.5 + 7.3)
```
=== Calcolatrice ===
Inserire: numero operatore numero
Operatori supportati: + - * /
> 12.5 + 7.3
  12.50 + 7.30 = 19.80
```

### 040-problema-calcolatrice (esempio con divisione per zero)
```
> 8.0 / 0.0
  Errore: divisione per zero non consentita.
```

### 050-problema-conversione-unita (esempio scelta 1, valore 100)
```
=== Convertitore di unita' ===
  1. Chilometri → Miglia
  ...
Scelta: 1
Valore da convertire: 100
100.0000 km = 62.1371 miglia
```

### 060-problema-analisi-voti (esempio: 8 9 7 9 8)
```
Inserire i voti (da 1 a 10) per le cinque materie:
Matematica:  8
Italiano:    9
Inglese:     7
Informatica: 9
Fisica:      8

-------------------------------
SCHEDA DELLO STUDENTE
-------------------------------
Matematica:      8
Italiano:        9
Inglese:         7
Informatica:     9
Fisica:          8
-------------------------------
Media:           8.20
Voto minimo:     7
Voto massimo:    9
Giudizio: Ottimo
Esito:           PROMOSSO
-------------------------------
```

---

## Errori comuni da evitare

```c
/* ERRORE 1: credere che la funzione modifichi la variabile originale */
void azzera(int n) { n = 0; }   /* modifica solo la copia */

int main(void) {
    int x = 42;
    azzera(x);
    printf("%d\n", x);   /* stampa ancora 42, non 0 */
    return 0;
}
```

```c
/* ERRORE 2: dimenticare il tipo di ritorno (implicito int in C89, errore in C11) */
somma(int a, int b) { return a + b; }   /* manca il tipo: int somma(...) */
```

```c
/* ERRORE 3: ignorare il valore di ritorno di una funzione non-void */
int quadrato(int x) { return x * x; }

int main(void) {
    quadrato(5);            /* il risultato viene scartato: quasi sempre un errore */
    int r = quadrato(5);    /* corretto: il risultato viene conservato */
    return 0;
}
```

```c
/* ERRORE 4: return multipli (viola la convenzione del progetto) */
int massimo(int a, int b)
{
    if (a > b) { return a; }   /* ERRATO: return anticipato */
    return b;
}

/* CORRETTO: una sola return alla fine */
int massimo(int a, int b)
{
    int max;
    if (a > b) { max = a; } else { max = b; }
    return max;
}
```

---

## Concetti collegati

- `01-definizione-e-chiamata` – struttura base delle funzioni void
- `03-ricorsione` – funzioni che chiamano se stesse passando parametri modificati
- `04-scope-e-visibilita` – durata e visibilità delle variabili locali (parametri inclusi)
- `05-puntatori/03-puntatori-e-funzioni` – come modificare la variabile originale del chiamante

---

## Esercizi proposti

1. **(Facile)** Scrivi una funzione `int cubo(int n)` che restituisce il cubo
   di un intero. Chiamala dal main per i valori da 1 a 5 e stampa i risultati.

2. **(Medio)** Scrivi una funzione `double imc(double peso_kg, double altezza_m)`
   che calcola l'Indice di Massa Corporea (peso / altezza²). Scrivi poi una
   funzione `void categoria_imc(double imc)` che stampa la categoria
   (sottopeso, normopeso, sovrappeso, obesità). Collegale nel main.

3. **(Avanzato)** Scrivi le funzioni `int cifre_di(int n)` (numero di cifre
   di un intero) e `int cifra_n(int n, int pos)` (cifra in posizione pos,
   da destra, con pos=1 per le unità). Usa solo divisioni intere e modulo.
   Verifica i risultati per n=12345.
