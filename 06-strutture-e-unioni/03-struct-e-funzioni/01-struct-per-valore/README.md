# 01 – Struct per valore

## Concetto

Una struct si passa a una funzione **come un int**: il parametro riceve una
**copia** di tutti i campi, compresi gli array contenuti nella struct.

```c
void stampa(Tessera t);                  /* t è una copia */
Tessera ricaricata(Tessera t, double euro);

tessera = ricaricata(tessera, 20.00);    /* il risultato sostituisce l'originale */
```

| Che cosa fa la funzione | Effetto sul chiamante |
|-------------------------|-----------------------|
| legge i campi della copia | nessuno |
| modifica i campi della copia | nessuno: la copia sparisce al ritorno |
| restituisce una struct | il chiamante riceve tutti i campi in un colpo solo |

### Funzioni che restituiscono una struct

Con `return` si restituisce un solo valore; se il valore è una struct si
restituiscono tutti i suoi campi. È il modo naturale di lavorare con i tipi
che si comportano come numeri (frazioni, orari, numeri complessi):

```c
Frazione somma(Frazione a, Frazione b);
Frazione semplifica(Frazione f);

Frazione r = semplifica(somma(a, b));    /* chiamate annidate */
```

Gli operandi non vengono modificati: ogni operazione produce un valore
nuovo.

### Il costo della copia

A ogni chiamata si copiano `sizeof(Tipo)` byte:

| Struct | Dimensione | Passaggio per valore |
|--------|------------|----------------------|
| `Frazione` (2 int) | 8 byte | conveniente |
| `Orario` (2 int) | 8 byte | conveniente |
| `Registro` (200 voti) | 808 byte | da evitare: si passa l'indirizzo (sezione 02) |

---

## File dell'esempio

| File | Contenuto |
|------|-----------|
| `010-parametro-per-valore.c` | La ricarica della tessera fatta sulla copia e corretta con il valore restituito |
| `020-struct-restituita.c` | `Frazione` con funzioni che creano, sommano e semplificano |
| `030-costo-della-copia.c` | Quanti byte si copiano passando per valore un `Registro` grande |
| `040-problema-calcolatrice-frazioni.c` | Le quattro operazioni sulle frazioni con il risultato normalizzato |
| `040-problema-calcolatrice-frazioni-analisi.md` | Analisi di `040-problema-calcolatrice-frazioni.c` |
| `050-problema-orari-treni.c` | `Orario` restituito da `aggiungi_minuti` e coincidenze del treno |
| `050-problema-orari-treni-analisi.md` | Analisi di `050-problema-orari-treni.c` |
| `060-problema-banchi-laboratorio.c` | Rettangoli sulla pianta: sovrapposizione e intersezione |
| `060-problema-banchi-laboratorio-analisi.md` | Analisi di `060-problema-banchi-laboratorio.c` |
| `070-problema-cambio-valuta.c` | `Importo` convertito in euro con una tabella dei cambi |
| `070-problema-cambio-valuta-analisi.md` | Analisi di `070-problema-cambio-valuta.c` |
| `080-problema-impedenze-circuito.c` | Numeri complessi per le impedenze di un circuito RLC |
| `080-problema-impedenze-circuito-analisi.md` | Analisi di `080-problema-impedenze-circuito.c` |

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-parametro-per-valore 010-parametro-per-valore.c
./010-parametro-per-valore

gcc -Wall -Wextra -o 020-struct-restituita 020-struct-restituita.c
./020-struct-restituita

gcc -Wall -Wextra -o 030-costo-della-copia 030-costo-della-copia.c
./030-costo-della-copia

gcc -Wall -Wextra -o 040-problema-calcolatrice-frazioni 040-problema-calcolatrice-frazioni.c
./040-problema-calcolatrice-frazioni

gcc -Wall -Wextra -o 050-problema-orari-treni 050-problema-orari-treni.c
./050-problema-orari-treni

gcc -Wall -Wextra -o 060-problema-banchi-laboratorio 060-problema-banchi-laboratorio.c
./060-problema-banchi-laboratorio

gcc -Wall -Wextra -o 070-problema-cambio-valuta 070-problema-cambio-valuta.c
./070-problema-cambio-valuta

gcc -Wall -Wextra -o 080-problema-impedenze-circuito 080-problema-impedenze-circuito.c -lm
./080-problema-impedenze-circuito
```

---

## Output atteso

### 010-parametro-per-valore
```
tessera 1024 (Bianchi Sara): credito 3.50 euro
  dentro la funzione la copia ha 23.50 euro
Dopo ricarica_sbagliata:  tessera 1024 (Bianchi Sara): credito 3.50 euro
Dopo tessera = ricaricata(...): tessera 1024 (Bianchi Sara): credito 23.50 euro
```

### 020-struct-restituita
```
Latte 1/2 + panna 1/3 = 5/6 di tazza
Dose doppia: 5/3 di tazza
```

### 030-costo-della-copia
```
Registro della 3B: 12 voti
  media 6.50, massimo 9, insufficienze 3

sizeof(Registro) = 808 byte
3 chiamate per valore: 2424 byte copiati
Un indirizzo occupa 8 byte
```

### 040-problema-calcolatrice-frazioni
*(output dipendente dall'input – esempio di sessione)*
```
Espressione (a/b op c/d, 0/0 per finire): 3/4 + 1/6
  3/4 + 1/6 = 11/12
Espressione (a/b op c/d, 0/0 per finire): 3/4 - 5/4
  3/4 - 5/4 = -1/2
Espressione (a/b op c/d, 0/0 per finire): 3/4 * 2/9
  3/4 * 2/9 = 1/6
Espressione (a/b op c/d, 0/0 per finire): 3/4 : 0/5
  Divisione per zero.
Espressione (a/b op c/d, 0/0 per finire): 1/0 + 1/2
  Denominatore nullo.
Espressione (a/b op c/d, 0/0 per finire): 2/3 ^ 1/2
  Operatore ^ non previsto.
Espressione (a/b op c/d, 0/0 per finire): 0/0
```

### 050-problema-orari-treni
*(output dipendente dall'input – ritardi diversi)*
```
Ritardo del treno da Acqui Terme (minuti, negativo per finire): 0
  partenza 07:02, arrivo 07:40, a scuola 07:52  in orario (8 min di margine)
Ritardo del treno da Ovada (minuti, negativo per finire): 5
  partenza 07:10, arrivo 07:44, a scuola 07:56  in orario (4 min di margine)
Ritardo del treno da Novi Ligure (minuti, negativo per finire): 12
  partenza 07:18, arrivo 07:54, a scuola 08:06  RITARDO di 6 min: serve il permesso
Ritardo del treno da Tortona (minuti, negativo per finire): -1
```

### 060-problema-banchi-laboratorio
*(output dipendente dall'input – banco sovrapposto)*
```
Stanza 900 x 600 cm, banchi esistenti: 3
Nuovo banco (x y larghezza profondita'): 200 100 200 200
Si sovrappone al banco 1 per 4500 cm2.
Si sovrappone al banco 2 per 7500 cm2.
```

*(output dipendente dall'input – banco libero)*
```
Stanza 900 x 600 cm, banchi esistenti: 3
Nuovo banco (x y larghezza profondita'): 400 450 200 100
Posizione libera: banco di 20000 cm2 sistemato.
```

*(output dipendente dall'input – banco fuori dalla stanza)*
```
Stanza 900 x 600 cm, banchi esistenti: 3
Nuovo banco (x y larghezza profondita'): 800 500 200 200
Il banco esce dalla stanza.
```

### 070-problema-cambio-valuta
*(output dipendente dall'input – esempio di sessione)*
```
Spesa (importo valuta, 0 per finire): 12.50 GBP
  12.50 GBP = 14.53 EUR
Spesa (importo valuta, 0 per finire): 8 CHF
  8.00 CHF = 8.42 EUR
Spesa (importo valuta, 0 per finire): 20 EUR
  20.00 EUR = 20.00 EUR
Spesa (importo valuta, 0 per finire): 15 JPY
  Valuta JPY non in tabella.
Spesa (importo valuta, 0 per finire): 0
Totale del viaggio: 42.96 EUR
```

### 080-problema-impedenze-circuito
*(output dipendente dall'input – R = 100 ohm, L = 0.5 H, C = 20 uF, f = 50 Hz)*
```
R (ohm), L (H), C (F), frequenza (Hz): 100 0.5 0.00002 50
  Resistore      Z =    100.00 + j     0.00   |Z| =    100.00 ohm   fase    0.00 gradi
  Induttore      Z =      0.00 + j   157.08   |Z| =    157.08 ohm   fase   90.00 gradi
  Condensatore   Z =      0.00 - j   159.15   |Z| =    159.15 ohm   fase  -90.00 gradi
  Serie RLC      Z =    100.00 - j     2.08   |Z| =    100.02 ohm   fase   -1.19 gradi
  corrente serie: 2.300 A
  R parallelo C  Z =     71.70 - j    45.05   |Z| =     84.67 ohm   fase  -32.14 gradi
```

---

## Errori comuni da evitare

**Aspettarsi che la funzione modifichi la struct del chiamante**
```c
void ricarica(Tessera t, double euro) { t.credito += euro; }
ricarica(tessera, 20.00);               /* tessera non cambia */
tessera = ricaricata(tessera, 20.00);   /* corretto: si usa il valore restituito */
```

**Chiamare una funzione che restituisce una struct e ignorarne il risultato**
```c
semplifica(f);            /* il risultato va perso */
f = semplifica(f);        /* corretto */
```

**Restituire una struct con campi non inizializzati**
```c
Frazione r;
if (b.den != 0) { r.num = ...; r.den = ...; }
return r;                 /* se b.den == 0 r contiene valori casuali */
```

**Passare per valore una struct grande in un ciclo**
```c
for (i = 0; i < 1000; i++) {
    m = media(registro);  /* 808 byte copiati a ogni giro */
}
```

**Confrontare due struct restituite con ==**
```c
if (somma(a, b) == c)                      /* errore di compilazione */
if (uguali(somma(a, b), c))                /* corretto: funzione di confronto */
```

---

## Concetti collegati

- `03-funzioni/02-parametri-e-return` → passaggio per valore dei tipi base
- `02-struct` → assegnamento di struct e copia dei campi
- `02-puntatori-a-struct` → modificare la struct del chiamante senza copiarla
- `03-array-di-struct-e-funzioni` → passare un elenco di struct

---

## Esercizi proposti

1. In `020-struct-restituita.c` aggiungi la funzione `Frazione inversa(Frazione f)`
   e usala per scrivere la divisione come prodotto per l'inversa.

2. In `050-problema-orari-treni.c` scrivi `int prima(Orario a, Orario b)` che
   restituisce 1 se `a` viene prima di `b`, e usala per segnalare le
   coincidenze perse.

3. In `060-problema-banchi-laboratorio.c` aggiungi `Rettangolo spostato(Rettangolo r, int dx, int dy)`
   e prova a spostare il banco nuovo finché non si sovrappone più.

4. In `070-problema-cambio-valuta.c` aggiungi la conversione inversa, da
   euro alla valuta indicata.

5. (Avanzato) In `080-problema-impedenze-circuito.c` calcola la frequenza
   di risonanza e mostra che a quella frequenza l'impedenza serie è
   puramente resistiva.
