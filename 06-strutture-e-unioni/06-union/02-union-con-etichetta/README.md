# 02 – Union con etichetta

## Concetto

Una union da sola non ricorda quale campo è stato scritto. Si mette
quindi in una struct, accanto a un campo **enum** (l'**etichetta**, in
inglese *tag*) che lo dice:

```c
typedef enum { INTERO, REALE, TESTO } TipoDato;

typedef struct {
    TipoDato tipo;            /* l'etichetta */
    union {
        int intero;
        double reale;
        char testo[16];
    } v;
} Dato;
```

Regola: ogni volta che si scrive un campo della union si aggiorna
l'etichetta, e prima di leggere un campo si controlla l'etichetta.

### Uno switch per ogni operazione

```c
void stampa(const Dato *d)
{
    switch (d->tipo) {
    case INTERO:
        printf("%d", d->v.intero);
        break;
    case REALE:
        printf("%g", d->v.reale);
        break;
    case TESTO:
        printf("%s", d->v.testo);
        break;
    }
}
```

Senza `default`, con `-Wall` il compilatore segnala i case mancanti: se
si aggiunge un tipo, indica tutte le operazioni da aggiornare.

### Funzioni costruttrici

```c
Dato crea_intero(int valore);
Dato crea_reale(double valore);
Dato crea_testo(const char *valore);

elenco[0] = crea_reale(36.6);       /* etichetta e campo sempre coerenti */
```

| Dove va un campo | Esempio |
|------------------|---------|
| fuori dalla union: comune a tutti i tipi | titolo, importo, disponibilità |
| dentro la union: specifico di un tipo | raggio del cerchio, cifre della carta |

---

## File dell'esempio

| File | Contenuto |
|------|-----------|
| `010-etichetta-enum.c` | `Dato` con etichetta: scrivere campo ed etichetta insieme |
| `020-switch-sull-etichetta.c` | Stampa e confronto con uno switch: le risposte a un questionario |
| `030-funzioni-costruttrici.c` | `crea_intero`, `crea_reale`, `crea_testo` per la scheda di un esperimento |
| `040-problema-figure-geometriche.c` | Cerchi, rettangoli e triangoli: area, perimetro e validità |
| `040-problema-figure-geometriche-analisi.md` | Analisi di `040-problema-figure-geometriche.c` |
| `050-problema-celle-foglio.c` | Foglio di calcolo con celle vuote, numeri e testi |
| `050-problema-celle-foglio-analisi.md` | Analisi di `050-problema-celle-foglio.c` |
| `060-problema-pagamenti-bar.c` | Contanti, carta o buono: ricevuta e totali per metodo |
| `060-problema-pagamenti-bar-analisi.md` | Analisi di `060-problema-pagamenti-bar.c` |
| `070-problema-catalogo-media.c` | Libri, DVD e riviste: campi comuni fuori dalla union |
| `070-problema-catalogo-media-analisi.md` | Analisi di `070-problema-catalogo-media.c` |
| `080-problema-risultati-misure.c` | Una misura riuscita, fuori scala o guasta |
| `080-problema-risultati-misure-analisi.md` | Analisi di `080-problema-risultati-misure.c` |

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-etichetta-enum 010-etichetta-enum.c
./010-etichetta-enum

gcc -Wall -Wextra -o 020-switch-sull-etichetta 020-switch-sull-etichetta.c
./020-switch-sull-etichetta

gcc -Wall -Wextra -o 030-funzioni-costruttrici 030-funzioni-costruttrici.c
./030-funzioni-costruttrici

gcc -Wall -Wextra -o 040-problema-figure-geometriche 040-problema-figure-geometriche.c -lm
./040-problema-figure-geometriche

gcc -Wall -Wextra -o 050-problema-celle-foglio 050-problema-celle-foglio.c
./050-problema-celle-foglio

gcc -Wall -Wextra -o 060-problema-pagamenti-bar 060-problema-pagamenti-bar.c
./060-problema-pagamenti-bar

gcc -Wall -Wextra -o 070-problema-catalogo-media 070-problema-catalogo-media.c
./070-problema-catalogo-media

gcc -Wall -Wextra -o 080-problema-risultati-misure 080-problema-risultati-misure.c
./080-problema-risultati-misure
```

---

## Output atteso

### 010-etichetta-enum
```
risposta 1: intero 16
risposta 2: reale 7.45
risposta 3: testo "3B"

sizeof(Dato) = 24 byte: l'etichetta (4) e la union (16), con padding
```

### 020-switch-sull-etichetta
```
domanda 1:  3  /  3  -> uguali
domanda 2:  9.81  /  9.8  -> diverse
domanda 3:  "Volta"  /  "Volta"  -> uguali
domanda 4:  1861  /  "1861"  -> diverse
```

### 030-funzioni-costruttrici
```
  gruppo        (intero) 4
  reagente      (testo)  "solfato di rame"
  temperatura   (reale)  21.5
  provette      (intero) 6
  osservazioni  (testo)  "precipitato azz"
```

### 040-problema-figure-geometriche
*(output dipendente dall'input – sei figure)*
```
Figura (C r, R b h, T a b c, FINE): C 2
  cerchio: area 12.57, perimetro 12.57
Figura (C r, R b h, T a b c, FINE): R 3 4
  rettangolo: area 12.00, perimetro 14.00
Figura (C r, R b h, T a b c, FINE): T 3 4 5
  triangolo: area 6.00, perimetro 12.00
Figura (C r, R b h, T a b c, FINE): T 1 1 5
  Misure non valide per un triangolo.
Figura (C r, R b h, T a b c, FINE): X
  Figura non riconosciuta.
Figura (C r, R b h, T a b c, FINE): R 0 2
  Misure non valide per un rettangolo.
Figura (C r, R b h, T a b c, FINE): FINE
Area maggiore: figura 1 (cerchio), 12.57
```

### 050-problema-celle-foglio
*(output dipendente dall'input – esempio di sessione)*
```
Comando (P, M cella contenuto, V cella, S colonna, Q): P
     A            B            C
  1  Voce         Euro         Note        
  2  Pullman           1450.00 .           
  3  Museo              156.00 .           
  4  Pranzo       da definire  chiedere    
  5  .            .            .           
  6  .            .            .           
Comando (P, M cella contenuto, V cella, S colonna, Q): S B
  Somma colonna B: 1606.00 (celle di testo ignorate: 2)
Comando (P, M cella contenuto, V cella, S colonna, Q): M B4 32.5
  B4: numero
Comando (P, M cella contenuto, V cella, S colonna, Q): M C2 sconto 10%
  C2: testo
Comando (P, M cella contenuto, V cella, S colonna, Q): V A3
Comando (P, M cella contenuto, V cella, S colonna, Q): M D1 5
  Cella non valida.
Comando (P, M cella contenuto, V cella, S colonna, Q): S B
  Somma colonna B: 1638.50 (celle di testo ignorate: 1)
Comando (P, M cella contenuto, V cella, S colonna, Q): P
     A            B            C
  1  Voce         Euro         Note        
  2  Pullman           1450.00 sconto 10%  
  3  .                  156.00 .           
  4  Pranzo              32.50 chiedere    
  5  .            .            .           
  6  .            .            .           
Comando (P, M cella contenuto, V cella, S colonna, Q): Q
```

### 060-problema-pagamenti-bar
*(output dipendente dall'input – sette pagamenti)*
```
Pagamento (C importo consegnato, K importo cifre, B importo codice, FINE): C 3.20 5
  3.20 euro in contanti, resto 1.80
Pagamento (C importo consegnato, K importo cifre, B importo codice, FINE): K 4.50 1234
  4.50 euro con carta **** 1234
Pagamento (C importo consegnato, K importo cifre, B importo codice, FINE): B 2.80 BU-17
  2.80 euro con buono BU-17 (non da' resto)
Pagamento (C importo consegnato, K importo cifre, B importo codice, FINE): C 2.00 1.50
  Pagamento rifiutato.
Pagamento (C importo consegnato, K importo cifre, B importo codice, FINE): K 1.00 12345
  Pagamento rifiutato.
Pagamento (C importo consegnato, K importo cifre, B importo codice, FINE): B 6.00 BU-18
  Pagamento rifiutato.
Pagamento (C importo consegnato, K importo cifre, B importo codice, FINE): C 1.30 2
  1.30 euro in contanti, resto 0.70
Pagamento (C importo consegnato, K importo cifre, B importo codice, FINE): FINE

Incassi del giorno
  contanti  pagamenti  2     4.50 euro
  carta     pagamenti  1     4.50 euro
  buono     pagamenti  1     2.80 euro
```

### 070-problema-catalogo-media
*(output dipendente dall'input – esempio di sessione)*
```
Comando (E, C parola, P n, R n, Q): E
  1  Il sistema periodico  libro    Primo Levi, 240 pagine
  2  Il nome della rosa    DVD      J.-J. Annaud, 130 minuti
  3  Le Scienze            rivista  n. 687, 2025
  4  Il nome della rosa    libro    Umberto Eco, 503 pagine  (in prestito)
  5  Il sistema solare     DVD      BBC, 58 minuti
  6  Fahrenheit 451        libro    Ray Bradbury, 176 pagine
Comando (E, C parola, P n, R n, Q): C nome
  2  Il nome della rosa    DVD      J.-J. Annaud, 130 minuti
  4  Il nome della rosa    libro    Umberto Eco, 503 pagine  (in prestito)
  Trovati: 2
Comando (E, C parola, P n, R n, Q): P 4
  "Il nome della rosa" e' gia' in prestito.
Comando (E, C parola, P n, R n, Q): P 2
  "Il nome della rosa": prestito registrato
Comando (E, C parola, P n, R n, Q): P 3
  Le riviste si consultano in biblioteca.
Comando (E, C parola, P n, R n, Q): R 4
  "Il nome della rosa": restituito
Comando (E, C parola, P n, R n, Q): R 1
  "Il sistema periodico" non era in prestito.
Comando (E, C parola, P n, R n, Q): E
  1  Il sistema periodico  libro    Primo Levi, 240 pagine
  2  Il nome della rosa    DVD      J.-J. Annaud, 130 minuti  (in prestito)
  3  Le Scienze            rivista  n. 687, 2025
  4  Il nome della rosa    libro    Umberto Eco, 503 pagine
  5  Il sistema solare     DVD      BBC, 58 minuti
  6  Fahrenheit 451        libro    Ray Bradbury, 176 pagine
Comando (E, C parola, P n, R n, Q): Q
```

### 080-problema-risultati-misure
*(output dipendente dall'input – fondo scala 20 V)*
```
Fondo scala (V): 20
Lettura (FINE): 3.27
  (3.270 +/- 0.043) V
Lettura (FINE): 12.5
  (12.500 +/- 0.135) V
Lettura (FINE): 21.4
  Fuori scala: oltre 20.0 V, scegliere una portata piu' alta.
Lettura (FINE): -1
  Guasto: cavo staccato (codice -1)
Lettura (FINE): 0.85
  (0.850 +/- 0.019) V
Lettura (FINE): -2
  Guasto: batteria scarica (codice -2)
Lettura (FINE): abc
  Non e' un numero.
Lettura (FINE): FINE
Media delle misure riuscite: 5.540 V
Riuscite 3, fuori scala 1, guasti 2
```

---

## Errori comuni da evitare

**Scrivere il campo senza aggiornare l'etichetta**
```c
d.v.reale = 2.5;                   /* d.tipo vale ancora INTERO */
d = crea_reale(2.5);               /* corretto */
```

**Leggere il campo senza controllare l'etichetta**
```c
printf("%g", d.v.reale);           /* e se d.tipo è TESTO? */
if (d.tipo == REALE) { printf("%g", d.v.reale); }   /* corretto */
```

**Mettere un default nello switch sull'etichetta**
```c
default: break;                    /* nasconde i tipi aggiunti in seguito */
```

**Confrontare due dati byte per byte**
```c
memcmp(&a, &b, sizeof(Dato))       /* i byte non usati sono casuali */
a.tipo == b.tipo && ...            /* corretto: confronto secondo il tipo */
```

**Mettere nella union un campo comune a tutti i tipi**
```c
union { double importo_contanti; double importo_carta; ... }
double importo;                    /* corretto: fuori dalla union */
```

---

## Concetti collegati

- `05-enum` → switch su enum senza `default`
- `03-struct-e-funzioni` → funzioni che restituiscono una struct
- `01-union-e-memoria` → campi sovrapposti
- `03-union-in-pratica` → union anonima e accesso controllato

---

## Esercizi proposti

1. In `010-etichetta-enum.c` aggiungi il tipo `BOOLEANO` e guarda quali
   avvisi dà il compilatore.

2. In `040-problema-figure-geometriche.c` aggiungi il quadrato, con il
   solo lato.

3. In `050-problema-celle-foglio.c` aggiungi il comando `X B` con il
   valore massimo della colonna.

4. In `060-problema-pagamenti-bar.c` aggiungi il pagamento con
   applicazione, identificato da un codice di 6 lettere.

5. (Avanzato) In `070-problema-catalogo-media.c` aggiungi il tipo
   `AUDIOLIBRO` con narratore e durata, aggiornando tutti gli switch.
