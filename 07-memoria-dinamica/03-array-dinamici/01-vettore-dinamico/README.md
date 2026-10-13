# 01 – Il vettore dinamico

## Concetto

Un **vettore dinamico** è un array che cresce da solo man mano che si
aggiungono elementi. Si costruisce con tre informazioni tenute insieme in
una struct:

```c
typedef struct {
    int *dati;         /* blocco nell'heap */
    int n;             /* elementi usati (lunghezza) */
    int capacita;      /* elementi allocati */
} Vettore;
```

```
dati ---> [ 12 | 30 |  0 | 25 |    |    |    |    ]
            \_______ n = 4 ____/
            \____________ capacita = 8 ____________/
```

Vale sempre `0 <= n <= capacita`. Le celle dopo `n` sono allocate ma non
ancora usate.

### Crescita a raddoppio

Quando `n == capacita` la funzione `aggiungi` ingrandisce il blocco con
`realloc`, **raddoppiando** la capacità:

```c
int aggiungi(Vettore *v, int valore)
{
    int *tmp;
    int ok = 1;

    if (v->n == v->capacita) {
        tmp = realloc(v->dati, 2 * v->capacita * sizeof *tmp);
        if (tmp == NULL) {
            ok = 0;                    /* il vettore resta com'era */
        } else {
            v->dati = tmp;
            v->capacita = 2 * v->capacita;
        }
    }
    if (ok) {
        v->dati[v->n] = valore;
        v->n++;
    }
    return ok;
}
```

| Strategia | realloc per 100000 aggiunte | Elementi copiati al massimo |
|-----------|-----------------------------|-----------------------------|
| +16 alla volta | 6249 | 312450000 (circa n² / 32) |
| ×2 alla volta | 13 | 131056 (meno di 2n) |

Con il raddoppio il costo medio di un'aggiunta è costante.

### Le funzioni del tipo

Il programma usa il vettore **solo** con le sue funzioni, mai con i campi:

| Funzione | Compito |
|----------|---------|
| `crea_vettore(capacita)` | alloca struct e blocco; `NULL` se manca memoria |
| `aggiungi(v, x)` | scrive in fondo, raddoppia se pieno; 0 se fallisce |
| `lunghezza(v)`, `capacita(v)` | i due contatori |
| `elemento(v, i)` | l'elemento `i` (copia o puntatore) |
| `distruggi_vettore(v)` | libera blocco e struct |

Così il `main` non può rendere incoerenti `n` e `capacita`, e cambiare la
strategia di crescita tocca una sola funzione.

---

## File dell'esempio

| File | Contenuto |
|------|-----------|
| `010-lunghezza-e-capacita.c` | Lunghezza, capacità e posti liberi senza bisogno di realloc |
| `020-crescita-a-raddoppio.c` | +16 contro ×2: numero di realloc ed elementi copiati |
| `030-funzioni-del-vettore.c` | Il vettore usato solo con le sue funzioni: pagine lette ogni giorno |
| `040-problema-registro-dei-ritardi.c` | Vettore di struct con gli ingressi in ritardo dell'anno |
| `040-problema-registro-dei-ritardi-analisi.md` | Analisi di `040-problema-registro-dei-ritardi.c` |
| `050-problema-misure-continue.c` | Letture del rumore fino a STOP e media mobile |
| `050-problema-misure-continue-analisi.md` | Analisi di `050-problema-misure-continue.c` |
| `060-problema-numeri-del-lotto.c` | Archivio di estrazioni, frequenze e ritardi |
| `060-problema-numeri-del-lotto-analisi.md` | Analisi di `060-problema-numeri-del-lotto.c` |
| `070-problema-scontrini-del-bar.c` | Vendite della giornata e riepilogo in un secondo vettore |
| `070-problema-scontrini-del-bar-analisi.md` | Analisi di `070-problema-scontrini-del-bar.c` |
| `080-problema-vettore-di-parole.c` | Vettore di `char *`: ogni termine nel suo blocco |
| `080-problema-vettore-di-parole-analisi.md` | Analisi di `080-problema-vettore-di-parole.c` |

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-lunghezza-e-capacita 010-lunghezza-e-capacita.c
./010-lunghezza-e-capacita

gcc -Wall -Wextra -o 020-crescita-a-raddoppio 020-crescita-a-raddoppio.c
./020-crescita-a-raddoppio

gcc -Wall -Wextra -o 030-funzioni-del-vettore 030-funzioni-del-vettore.c
./030-funzioni-del-vettore

gcc -Wall -Wextra -o 040-problema-registro-dei-ritardi 040-problema-registro-dei-ritardi.c
./040-problema-registro-dei-ritardi

gcc -Wall -Wextra -o 050-problema-misure-continue 050-problema-misure-continue.c
./050-problema-misure-continue

gcc -Wall -Wextra -o 060-problema-numeri-del-lotto 060-problema-numeri-del-lotto.c
./060-problema-numeri-del-lotto

gcc -Wall -Wextra -o 070-problema-scontrini-del-bar 070-problema-scontrini-del-bar.c
./070-problema-scontrini-del-bar

gcc -Wall -Wextra -o 080-problema-vettore-di-parole 080-problema-vettore-di-parole.c
./080-problema-vettore-di-parole
```

---

## Output atteso

### 010-lunghezza-e-capacita
```
n = 0, capacita = 8, liberi = 8  [  .  .  .  .  .  .  .  . ]
n = 1, capacita = 8, liberi = 7  [  7  .  .  .  .  .  .  . ]
n = 2, capacita = 8, liberi = 6  [  7  3  .  .  .  .  .  . ]
n = 3, capacita = 8, liberi = 5  [  7  3  9  .  .  .  .  . ]
n = 4, capacita = 8, liberi = 4  [  7  3  9  4  .  .  .  . ]
n = 5, capacita = 8, liberi = 3  [  7  3  9  4 12  .  .  . ]
n = 6, capacita = 8, liberi = 2  [  7  3  9  4 12  1  .  . ]
Byte allocati: 32, usati: 24
```

### 020-crescita-a-raddoppio
```
 elementi  crescita      realloc    copie (max)
     1000  +16                62          31248
     1000  x2                  6           1008
    10000  +16               624        3120000
    10000  x2                 10          16368
   100000  +16              6249      312450000
   100000  x2                 13         131056
```

### 030-funzioni-del-vettore
*(output dipendente dall'input – pagine di due settimane)*
```
Pagine lette ogni giorno (-1 per terminare): 12 30 0 25 18 40 22 15 33 27 8 35 20 19 -1

  capacita' da 2 a 4
  capacita' da 4 a 8
  capacita' da 8 a 16
Giorni: 14, capacita' finale: 16
Totale 304 pagine, media 21.7 al giorno
Sopra la media: giorno 2 (30) giorno 4 (25) giorno 6 (40) giorno 7 (22) giorno 9 (33) giorno 10 (27) giorno 12 (35)
```

### 040-problema-registro-dei-ritardi
*(output dipendente dall'input – un trimestre di ingressi)*
```
Ritardi (gg/mm nome minuti, FINE per terminare):
15/09 Rossi 10
15/09 Bianchi 5
02/10 Rossi 20
02/10 Verdi 15
02/10 Neri 8
31/11 Verdi 5
  riga non valida
20/10 Rossi 12
05/11 Bianchi 30
05/11 Rossi 7
12/12 Verdi 10
18/12 Verdi 25
FINE

Ingressi in ritardo: 10 (capacita' 16)
  set  2
  ott  4
  nov  2
  dic  2
  gen  0
  feb  0
  mar  0
  apr  0
  mag  0
  giu  0
Data con piu' ritardi: 02/10 (3)
Avviso alla famiglia (almeno 3 ritardi):
  Rossi: 4 ritardi
  Verdi: 3 ritardi
```

### 050-problema-misure-continue
*(output dipendente dall'input – un pranzo di 14 minuti)*
```
Letture in dB (STOP per terminare):
72 75 78 81 84 79 86 90 88 -3 85 rumore 76 74 70 68 STOP
  -3 scartata
  rumore scartata

Letture: 14
Massimo: 90.0 dB al minuto 8
Media mobile su 5 minuti:
  minuto  5:  78.0
  minuto  6:  79.4
  minuto  7:  81.6  troppo rumore
  minuto  8:  84.0  troppo rumore
  minuto  9:  85.4  troppo rumore
  minuto 10:  85.6  troppo rumore
  minuto 11:  85.0  troppo rumore
  minuto 12:  82.6  troppo rumore
  minuto 13:  78.6
  minuto 14:  74.6
Minuti sopra 80 dB (media mobile): 6
```

### 060-problema-numeri-del-lotto
*(output dipendente dall'input – otto estrazioni)*
```
Estrazioni (5 numeri, FINE per terminare):
12 45 67 3 88
5 12 33 71 90
45 2 18 12 60
7 45 33 81 29
12 12 4 5 6
  estrazione non valida
91 2 3 4 5
  estrazione non valida
63 18 45 50 1
9 33 12 77 40
44 18 2 66 13
FINE

Estrazioni: 7
Piu' frequenti:  12 (4)  45 (4)  18 (3)  33 (3)  2 (2)
Piu' in ritardo tra gli usciti:  3 (6)  67 (6)  88 (6)  5 (5)  71 (5)
Ogni estrazione e' indipendente: il ritardo non aumenta la probabilita'.
```

### 070-problema-scontrini-del-bar
*(output dipendente dall'input – una mattina al bar)*
```
Vendite (prodotto prezzo quantita', FINE per terminare):
cornetto 1.20 2
caffe 1.00 1
succo 1.50 1
cornetto 1.20 1
pizzetta 1.80 3
caffe 1.00 2
acqua 0.50 4
succo 1.50 -1
  vendita non valida
cornetto 1.20 3
FINE

Vendite registrate: 8, prodotti diversi: 5
  cornetto       6 pz     7.20 euro
  caffe          3 pz     3.00 euro
  succo          1 pz     1.50 euro
  pizzetta       3 pz     5.40 euro
  acqua          4 pz     2.00 euro
Incasso: 19.10 euro
Piu' venduto: cornetto
```

### 080-problema-vettore-di-parole
*(output dipendente dall'input – glossario di informatica)*
```
Termini (FINE per terminare):
processore
bit
compilatore
multiprogrammazione
RAM
byte
bit
  bit gia' presente
algoritmo
FINE

Glossario (7 termini):
  RAM
  algoritmo
  bit
  byte
  compilatore
  multiprogrammazione
  processore
Memoria: 66 byte di testi + 64 byte di puntatori
Con una matrice char[7][40]: 280 byte
```

---

## Errori comuni da evitare

**Confondere lunghezza e capacità**
```c
for (i = 0; i < v->capacita; i++)   /* legge celle mai scritte */
for (i = 0; i < lunghezza(v); i++)  /* corretto */
```

**Assegnare il risultato di realloc direttamente**
```c
v->dati = realloc(v->dati, nuova);  /* se fallisce il blocco è perso */
```

**Aggiornare la capacità prima di sapere se realloc è riuscita**
```c
v->capacita *= 2;
tmp = realloc(v->dati, v->capacita * sizeof *tmp);  /* se fallisce, capacita è falsa */
```

**Partire da capacità 0**
```c
crea_vettore(0);                    /* 2 * 0 = 0: il vettore non cresce mai */
```

**Liberare solo la struct**
```c
free(v);                            /* il blocco v->dati resta allocato */
```

---

## Concetti collegati

- `02-calloc-e-realloc` → `realloc` con il puntatore temporaneo
- `06-strutture-e-unioni/03-struct-e-funzioni` → struct passate per puntatore
- `02-operazioni-sul-vettore` → inserire e rimuovere in mezzo
- `10-strutture-dati` → pile e code costruite su un vettore

---

## Esercizi proposti

1. In `030-funzioni-del-vettore.c` aggiungi la funzione `somma(v)` e usala
   per calcolare la media.

2. In `040-problema-registro-dei-ritardi.c` stampa per ogni studente i
   minuti di ritardo totali.

3. In `050-problema-misure-continue.c` rendi la larghezza della finestra
   un valore letto all'avvio.

4. In `070-problema-scontrini-del-bar.c` stampa il riepilogo in ordine di
   incasso decrescente.

5. (Avanzato) In `080-problema-vettore-di-parole.c` aggiungi la funzione
   `rimuovi_termine(g, parola)` che libera il blocco del termine e
   compatta l'array di puntatori.
