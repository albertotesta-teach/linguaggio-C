# 01 – Dichiarazione e valori

## Concetto

Un **enum** è un tipo che elenca i suoi valori possibili, dando a ognuno
un nome:

```c
typedef enum {
    LUNEDI, MARTEDI, MERCOLEDI, GIOVEDI, VENERDI, SABATO, DOMENICA
} Giorno;

Giorno oggi = VENERDI;
```

Le costanti sono numeri interi: la prima vale 0, ognuna vale uno in più
della precedente. Si stampano con `%d` e si confrontano come gli `int`.

| `#define` | `enum` |
|-----------|--------|
| costanti sparse, senza un tipo che le raccolga | un tipo con un nome (`Giorno`) che compare nei prototipi |
| i valori si scrivono a mano | i valori li assegna il compilatore |
| il debugger mostra `4` | il debugger mostra `VENERDI` |

Un enum non controlla i valori: `oggi = 42;` compila lo stesso.

### Valori espliciti

```c
typedef enum { GENNAIO = 1, FEBBRAIO, ..., DICEMBRE } Mese;           /* da 1 a 12 */
typedef enum { BASSA = 1, MEDIA, ALTA, URGENTE = 10 } Priorita;      /* 1, 2, 3, 10 */
typedef enum { OK = 200, NON_TROVATO = 404, SUCCESSO = OK } Risposta;
```

Dopo una costante con `=` le successive continuano a contare da lì.

### Enum come indice

```c
typedef enum { VERDE, GIALLO, ROSSO, NUM_COLORI } Colore;   /* NUM_COLORI = 3 */

int durata[NUM_COLORI] = {[VERDE] = 40, [GIALLO] = 5, [ROSSO] = 45};
const char *nomi[NUM_COLORI] = {[VERDE] = "verde", [GIALLO] = "giallo", [ROSSO] = "rosso"};

colore = (colore + 1) % NUM_COLORI;          /* il colore successivo */
```

L'ultima costante conta le altre: aggiungendo un valore prima di lei, gli
array si ridimensionano da soli.

---

## File dell'esempio

| File | Contenuto |
|------|-----------|
| `010-costanti-con-nome.c` | `Giorno`: valori da 0, confronti e fine settimana |
| `020-valori-espliciti.c` | `Mese` da 1, priorità con un salto, codici HTTP con un sinonimo |
| `030-enum-come-indice.c` | `NUM_GIORNI`, array di ore e tabella dei nomi con `[MERCOLEDI] = ...` |
| `040-problema-semaforo.c` | Ciclo dei colori con `(colore + 1) % NUM_COLORI` |
| `040-problema-semaforo-analisi.md` | Analisi di `040-problema-semaforo.c` |
| `050-problema-giorni-di-lezione.c` | Ore per giorno, giorno più lungo e giorni liberi |
| `050-problema-giorni-di-lezione-analisi.md` | Analisi di `050-problema-giorni-di-lezione.c` |
| `060-problema-taglie-magazzino.c` | Scorte di magliette per taglia, sigla cercata nella tabella |
| `060-problema-taglie-magazzino-analisi.md` | Analisi di `060-problema-taglie-magazzino.c` |
| `070-problema-mesi-e-stagioni.c` | Mese da `GENNAIO = 1`: giorni del mese e stagione |
| `070-problema-mesi-e-stagioni-analisi.md` | Analisi di `070-problema-mesi-e-stagioni.c` |
| `080-problema-livelli-di-log.c` | Livelli ordinati per gravità: filtro con `>=` e conteggi |
| `080-problema-livelli-di-log-analisi.md` | Analisi di `080-problema-livelli-di-log.c` |

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-costanti-con-nome 010-costanti-con-nome.c
./010-costanti-con-nome

gcc -Wall -Wextra -o 020-valori-espliciti 020-valori-espliciti.c
./020-valori-espliciti

gcc -Wall -Wextra -o 030-enum-come-indice 030-enum-come-indice.c
./030-enum-come-indice

gcc -Wall -Wextra -o 040-problema-semaforo 040-problema-semaforo.c
./040-problema-semaforo

gcc -Wall -Wextra -o 050-problema-giorni-di-lezione 050-problema-giorni-di-lezione.c
./050-problema-giorni-di-lezione

gcc -Wall -Wextra -o 060-problema-taglie-magazzino 060-problema-taglie-magazzino.c
./060-problema-taglie-magazzino

gcc -Wall -Wextra -o 070-problema-mesi-e-stagioni 070-problema-mesi-e-stagioni.c
./070-problema-mesi-e-stagioni

gcc -Wall -Wextra -o 080-problema-livelli-di-log 080-problema-livelli-di-log.c
./080-problema-livelli-di-log
```

---

## Output atteso

### 010-costanti-con-nome
```
LUNEDI = 0, MERCOLEDI = 2, DOMENICA = 6
oggi vale 4
  giorno 0: lezione
  giorno 1: lezione
  giorno 2: lezione
  giorno 3: lezione
  giorno 4: lezione
  giorno 5: fine settimana
  giorno 6: fine settimana
Domani vale 5: niente scuola
sizeof(Giorno) = 4 byte, come un int
```

### 020-valori-espliciti
```
GENNAIO = 1, SETTEMBRE = 9, DICEMBRE = 12
La scuola inizia il 15/09

BASSA = 1, MEDIA = 2, ALTA = 3, URGENTE = 10
Il guasto del proiettore ha priorita' 10: intervento immediato

OK = 200, NON_TROVATO = 404, ERRORE_SERVER = 500, SUCCESSO = 200
Risposta del registro elettronico: 404 (errore)
```

### 030-enum-come-indice
```
NUM_GIORNI = 6
  lunedi     6 ore
  martedi    5 ore
  mercoledi  5 ore
  giovedi    6 ore
  venerdi    5 ore
  sabato     0 ore
Totale settimanale: 27 ore
Il mercoledi si esce prima: 5 ore
```

### 040-problema-semaforo
*(output dipendente dall'input – istante 100 s)*
```
Istante (secondi, da 1 a 600): 100
    0 s  VERDE
   40 s  GIALLO
   45 s  ROSSO
   90 s  VERDE
A 100 s il semaforo e' VERDE: cambia tra 30 s.
```

*(output dipendente dall'input – istante non valido)*
```
Istante (secondi, da 1 a 600): 0
Istante non valido.
```

### 050-problema-giorni-di-lezione
*(output dipendente dall'input – con due valori da correggere)*
```
Ore di lunedi: 6
Ore di martedi: 6
Ore di mercoledi: x
  Scrivi un numero.
Ore di mercoledi: 9
  Da 0 a 8 ore.
Ore di mercoledi: 6
Ore di giovedi: 6
Ore di venerdi: 8
Ore di sabato: 0

Totale: 32 ore (corretto)
Giorno piu' lungo: venerdi con 8 ore
Giorni liberi: sabato
```

### 060-problema-taglie-magazzino
*(output dipendente dall'input – esempio di sessione)*
```
Comando (V taglia n, C taglia n, S, Q): S
  XS    4  da riordinare
  S    12
  M    20
  L    15
  XL    6
  XXL   0  ESAURITA
Comando (V taglia n, C taglia n, S, Q): V M 3
  Vendita registrata: taglia M, ne restano 17.
Comando (V taglia n, C taglia n, S, Q): V XS 5
  Taglia XS: ne restano solo 4.
Comando (V taglia n, C taglia n, S, Q): V XXL 1
  Taglia XXL esaurita.
Comando (V taglia n, C taglia n, S, Q): C XXL 10
  Taglia XXL: 10 magliette.
Comando (V taglia n, C taglia n, S, Q): V XXXL 2
  Taglia XXXL inesistente.
Comando (V taglia n, C taglia n, S, Q): V L 0
  Quantita' non valida.
Comando (V taglia n, C taglia n, S, Q): S
  XS    4  da riordinare
  S    12
  M    17
  L    15
  XL    6
  XXL  10
Comando (V taglia n, C taglia n, S, Q): Q
```

### 070-problema-mesi-e-stagioni
*(output dipendente dall'input – esempio di sessione)*
```
Mese e anno (0 per finire): 2 2028
  febbraio 2028: 29 giorni, inverno
Mese e anno (0 per finire): 4 2026
  aprile 2026: 30 giorni, primavera
Mese e anno (0 per finire): 12 2025
  dicembre 2025: 31 giorni, inverno
Mese e anno (0 per finire): 7 2026
  luglio 2026: 31 giorni, estate
Mese e anno (0 per finire): 13 2026
  13 non e' un mese.
Mese e anno (0 per finire): 0
```

### 080-problema-livelli-di-log
*(output dipendente dall'input – soglia AVVISO)*
```
Soglia (0 DEBUG, 1 INFO, 2 AVVISO, 3 ERRORE): 2
  09:02 [AVVISO] disco al 85%
  10:12 [ERRORE] stampante lab non risponde
  10:13 [AVVISO] nuovo tentativo di stampa
  11:30 [ERRORE] backup notturno non trovato
Mostrati 4 messaggi su 8
  DEBUG  1
  INFO   3
  AVVISO 2
  ERRORE 2
```

*(output dipendente dall'input – soglia non valida)*
```
Soglia (0 DEBUG, 1 INFO, 2 AVVISO, 3 ERRORE): 7
Soglia non valida.
```

---

## Errori comuni da evitare

**Aspettarsi che l'enum controlli i valori**
```c
Mese m = numero;                   /* nessun controllo: numero può valere 42 */
if (numero >= GENNAIO && numero <= DICEMBRE) { m = numero; }   /* corretto */
```

**Indicizzare con un enum che non parte da 0**
```c
nomi_mesi[DICEMBRE]                /* DICEMBRE vale 12: fuori da un array di 12 */
nomi_mesi[DICEMBRE - GENNAIO]      /* corretto */
```

**Scrivere a mano la dimensione degli array**
```c
int ore[6];                        /* da cambiare a mano se si aggiunge un giorno */
int ore[NUM_GIORNI];               /* corretto */
```

**Usare la costante di conteggio come valore**
```c
Colore c = NUM_COLORI;             /* non è un colore: è solo il numero dei colori */
```

**Stampare il nome con %s**
```c
printf("%s", oggi);                /* errore: oggi è un intero */
printf("%s", nomi[oggi]);          /* corretto */
```

---

## Concetti collegati

- `01-introduzione` → `#define` e `const`
- `01-typedef` → dare un nome a un tipo
- `02-enum-e-switch` → uno `switch` per ogni costante
- `03-enum-nelle-struct` → campi enum e macchine a stati

---

## Esercizi proposti

1. In `010-costanti-con-nome.c` stampa i giorni che mancano al sabato a
   partire da `oggi`.

2. In `040-problema-semaforo.c` aggiungi il colore `GIALLO_LAMPEGGIANTE`
   prima di `NUM_COLORI` e verifica che il programma funzioni senza altre
   modifiche, a parte le tabelle.

3. In `060-problema-taglie-magazzino.c` aggiungi il comando `T` con il
   valore del magazzino, dato un prezzo diverso per ogni taglia.

4. In `070-problema-mesi-e-stagioni.c` stampa anche quanti giorni mancano
   alla fine dell'anno dal primo giorno del mese.

5. (Avanzato) In `080-problema-livelli-di-log.c` leggi la soglia come
   parola (`AVVISO`) invece che come numero.
