# 03 – Vettori in pratica

## Concetto

Un vettore dinamico può contenere qualsiasi tipo: struct, puntatori,
perfino altri vettori. Questa sezione mostra tre situazioni frequenti e
le regole che le accompagnano.

### Puntatore a un elemento

Per modificare una struct dentro il vettore senza copiarla, `elemento`
restituisce un puntatore:

```c
Studente *elemento(Classe *c, int i)
{
    return &c->dati[i];
}

Studente *s = elemento(classe, 0);
s->assenze++;                       /* modifica il vettore */
```

Il puntatore punta **dentro** il blocco `dati`. Se `aggiungi` chiama
`realloc`, il blocco può spostarsi e il puntatore resta "appeso":

```c
Studente *s = elemento(classe, 0);
aggiungi(classe, nuovo);            /* può spostare il blocco */
s->assenze++;                       /* ERRORE: memoria già liberata */
```

**Regola:** il puntatore vale solo fino alla prossima aggiunta; dopo si
richiede.

### Vettore di vettori

Quando le righe hanno lunghezze diverse, ogni riga contiene il puntatore
a un **proprio** vettore dinamico:

```
Scuola                         vettore di Riga
  dati[0]  "3A"  voti --->     Voti: 7 8 6        (3 su capacità 4)
  dati[1]  "3B"  voti --->     Voti: 5 9          (2 su capacità 2)
  dati[2]  "3C"  voti --->     Voti: 6 6 7 8 4    (5 su capacità 8)
```

La distruzione va **dal basso verso l'alto**: prima il vettore di ogni
riga, poi il blocco delle righe, poi la struct esterna.

### Copiare e confrontare

| Operazione | Che cosa fa | Risultato |
|------------|-------------|-----------|
| `Vettore *b = a;` | copia il puntatore | due nomi per lo stesso vettore |
| `Vettore b = *a;` | copia superficiale della struct | `b.dati == a->dati`: stesso blocco |
| `b = copia(a);` | copia profonda | struct nuova e blocco nuovo |
| `a == b` | confronta gli indirizzi | non dice nulla sul contenuto |
| `prima_differenza(a, b)` | confronta elemento per elemento | -1 se uguali |

### Funzioni che restituiscono un vettore nuovo

Quando il risultato ha una lunghezza non nota (i mesi di aumento, gli
articoli sotto scorta), la funzione crea un vettore nuovo e lo
restituisce. Il chiamante **deve distruggerlo**:

```c
Magazzino *riordino = sotto_scorta(magazzino);
...
distruggi_magazzino(riordino);
```

---

## File dell'esempio

| File | Contenuto |
|------|-----------|
| `010-vettore-di-struct.c` | Vettore di `Studente` e puntatore a un elemento: quando il blocco si sposta |
| `020-vettore-di-vettori.c` | Una riga per classe, ognuna con il proprio vettore di voti |
| `030-copiare-e-confrontare.c` | Alias, copia profonda e confronto elemento per elemento |
| `040-problema-rubrica-della-classe.c` | Rubrica: aggiunta, ricerca, modifica, cancellazione |
| `040-problema-rubrica-della-classe-analisi.md` | Analisi di `040-problema-rubrica-della-classe.c` |
| `050-problema-orario-dei-docenti.c` | Ore occupate di ogni docente e ore libere comuni |
| `050-problema-orario-dei-docenti-analisi.md` | Analisi di `050-problema-orario-dei-docenti.c` |
| `060-problema-storico-dei-prezzi.c` | Prezzi della mensa, variazioni e vettore dei mesi di aumento |
| `060-problema-storico-dei-prezzi-analisi.md` | Analisi di `060-problema-storico-dei-prezzi.c` |
| `070-problema-magazzino-del-laboratorio.c` | Carico, scarico e vettore degli articoli sotto scorta |
| `070-problema-magazzino-del-laboratorio-analisi.md` | Analisi di `070-problema-magazzino-del-laboratorio.c` |
| `080-problema-statistiche-del-torneo.c` | Squadre con il proprio vettore di risultati e classifica |
| `080-problema-statistiche-del-torneo-analisi.md` | Analisi di `080-problema-statistiche-del-torneo.c` |

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-vettore-di-struct 010-vettore-di-struct.c
./010-vettore-di-struct

gcc -Wall -Wextra -o 020-vettore-di-vettori 020-vettore-di-vettori.c
./020-vettore-di-vettori

gcc -Wall -Wextra -o 030-copiare-e-confrontare 030-copiare-e-confrontare.c
./030-copiare-e-confrontare

gcc -Wall -Wextra -o 040-problema-rubrica-della-classe 040-problema-rubrica-della-classe.c
./040-problema-rubrica-della-classe

gcc -Wall -Wextra -o 050-problema-orario-dei-docenti 050-problema-orario-dei-docenti.c
./050-problema-orario-dei-docenti

gcc -Wall -Wextra -o 060-problema-storico-dei-prezzi 060-problema-storico-dei-prezzi.c
./060-problema-storico-dei-prezzi

gcc -Wall -Wextra -o 070-problema-magazzino-del-laboratorio 070-problema-magazzino-del-laboratorio.c
./070-problema-magazzino-del-laboratorio

gcc -Wall -Wextra -o 080-problema-statistiche-del-torneo 080-problema-statistiche-del-torneo.c
./080-problema-statistiche-del-torneo
```

---

## Output atteso

### 010-vettore-di-struct
```
aggiunto Bianchi   capacita 2  primo elemento a 0x55742ce172c0
aggiunto Rossi     capacita 2  primo elemento a 0x55742ce172c0
aggiunto Verdi     capacita 4  primo elemento a 0x55742ce18310  <- blocco spostato
aggiunto Neri      capacita 4  primo elemento a 0x55742ce18310
aggiunto Russo     capacita 8  primo elemento a 0x55742ce18310

Registro delle assenze:
  Bianchi  0
  Rossi    3
  Verdi    0
  Neri     1
  Russo    0
```

### 020-vettore-di-vettori
*(output dipendente dall'input – verifica comune di quattro classi)*
```
Classe e voto (FINE per terminare):
3A 7 3B 5 3A 8 3C 6 3C 6 3B 9 3A 6
3C 7 3C 8 3C 4 3D x 3D 11 3D 7 FINE
  voto non valido per 3D
  voto non valido per 3D

Classe Voti Cap. Media  Elenco
3A        3    4  7.00  7 8 6
3B        2    2  7.00  5 9
3C        5    8  6.20  6 6 7 8 4
3D        1    2  7.00  7
```

### 030-copiare-e-confrontare
```
Partenza:
  originale   12   7   9  15
  alias       12   7   9  15
  copia       12   7   9  15
originale == alias: si'
originale == copia: no
originale e copia hanno lo stesso contenuto

imposta(alias, 0, 99):
  originale   99   7   9  15
  copia       12   7   9  15

imposta(copia, 2, 40) e aggiungi(copia, 3):
  originale   99   7   9  15
  copia       12   7  40  15   3
originale e copia differiscono dalla posizione 0
```

### 040-problema-rubrica-della-classe
*(output dipendente dall'input – contatti della classe)*
```
Comando (A, C, M, D, E, Q): A Rossi 3331234567
  aggiunto Rossi (contatti: 1)
Comando (A, C, M, D, E, Q): A Russo 3479876543
  aggiunto Russo (contatti: 2)
Comando (A, C, M, D, E, Q): A Bianchi 3201112223
  aggiunto Bianchi (contatti: 3)
Comando (A, C, M, D, E, Q): A Rossi 3330000000
  Rossi e' gia' in rubrica.
Comando (A, C, M, D, E, Q): A Verdi 12ab
  Dati non validi.
Comando (A, C, M, D, E, Q): C Ru
  Russo        3479876543
Comando (A, C, M, D, E, Q): M Russo 3470000001
  Russo: 3479876543 -> 3470000001
Comando (A, C, M, D, E, Q): M Neri 3331111111
  Neri non e' in rubrica.
Comando (A, C, M, D, E, Q): D Rossi
  cancellato Rossi (contatti: 2)
Comando (A, C, M, D, E, Q): D Gialli
  Contatto non trovato.
Comando (A, C, M, D, E, Q): E
  Contatti in rubrica: 2
   1. Russo        3470000001
   2. Bianchi      3201112223
Comando (A, C, M, D, E, Q): Q
```

### 050-problema-orario-dei-docenti
*(output dipendente dall'input – tre docenti)*
```
Lezioni: docente giorno ora (FINE per terminare)
Rossi lun 1
Rossi lun 2
Rossi mar 3
Rossi ven 6
Rossi gio 4
Bianchi lun 3
Bianchi lun 1
Bianchi mar 1 Bianchi mar 2 Bianchi mar 4 Bianchi mar 5 Bianchi mar 6
Verdi mer 1 Verdi mer 2 Verdi mer 3 Verdi mer 4 Verdi mer 5 Verdi mer 6
Verdi lun 4 Verdi lun 5 Verdi lun 6
Rossi lun 1
  Rossi lun 1 gia' inserita
Neri sab 2
  lezione non valida per Neri
Neri gio x
  lezione non valida per Neri
FINE

Carico dei docenti:
  Rossi      ore  5  (capacita del vettore 8)
  Bianchi    ore  7  (capacita del vettore 8)
  Verdi      ore  9  (capacita del vettore 16)

Ore libere per tutti:
  lun: nessuna
  mar: nessuna
  mer: nessuna
  gio: 1 2 3 5 6
  ven: 1 2 3 4 5
Totale ore libere comuni: 10 su 30
```

### 060-problema-storico-dei-prezzi
*(output dipendente dall'input – un anno scolastico)*
```
Mese e prezzo (FINE per terminare):
set24 4.20
ott24 4.20
nov24 4.35
dic24 4.30
gen25 4.50
feb25 abc
  prezzo non valido per feb25
feb25 4.50
mar25 4.95
apr25 4.90
mag25 4.90
FINE

Mese    Prezzo    Var. %
set24     4.20
ott24     4.20     +0.0%
nov24     4.35     +3.6%
dic24     4.30     -1.1%
gen25     4.50     +4.7%
feb25     4.50     +0.0%
mar25     4.95    +10.0%
apr25     4.90     -1.0%
mag25     4.90     +0.0%

Mesi con aumento: 3 su 8
  nov24
  gen25
  mar25
Aumento piu' forte: mar25 (+10.0%)
Complessivo set24-mag25: 4.20 -> 4.90 euro (+16.7%)
```

### 070-problema-magazzino-del-laboratorio
*(output dipendente dall'input – materiale di elettronica)*
```
Comando (N, C, S, R, E, Q): N resistenze 200 50
  nuovo articolo: resistenze
Comando (N, C, S, R, E, Q): N LED 40 30
  nuovo articolo: LED
Comando (N, C, S, R, E, Q): N breadboard 12 10
  nuovo articolo: breadboard
Comando (N, C, S, R, E, Q): N LED 5 5
  LED esiste gia'.
Comando (N, C, S, R, E, Q): N Arduino 6 4
  nuovo articolo: Arduino
Comando (N, C, S, R, E, Q): R
  Niente da riordinare.
Comando (N, C, S, R, E, Q): S LED 15
  LED: disponibili 25  (sotto scorta)
Comando (N, C, S, R, E, Q): S breadboard 20
  breadboard: disponibili solo 12
Comando (N, C, S, R, E, Q): S breadboard 3
  breadboard: disponibili 9  (sotto scorta)
Comando (N, C, S, R, E, Q): C resistenze 100
  resistenze: disponibili 300
Comando (N, C, S, R, E, Q): S Arduino 3
  Arduino: disponibili 3  (sotto scorta)
Comando (N, C, S, R, E, Q): C transistor 10
  Articolo inesistente o quantita non valida.
Comando (N, C, S, R, E, Q): R
  Da riordinare: 3
  Articolo         Quantita  Scorta
  LED                    25      30
  breadboard              9      10
  Arduino                 3       4
Comando (N, C, S, R, E, Q): C LED 50
  LED: disponibili 75
Comando (N, C, S, R, E, Q): R
  Da riordinare: 2
  Articolo         Quantita  Scorta
  breadboard              9      10
  Arduino                 3       4
Comando (N, C, S, R, E, Q): E
  Articolo         Quantita  Scorta
  resistenze            300      50
  LED                    75      30
  breadboard              9      10
  Arduino                 3       4
Comando (N, C, S, R, E, Q): Q
```

### 080-problema-statistiche-del-torneo
*(output dipendente dall'input – torneo a quattro squadre)*
```
Partite: casa ospite gol gol (FINE per terminare)
4A 3B 2 1
5C 2D 0 0
4A 5C 1 1
3B 2D 3 0
4A 2D 4 2
3B 5C 2 2
5C 5C 1 0
  partita non valida (5C)
2D 4A x
  partita non valida (2D)
4A 3B 1 3
2D 5C 1 0
FINE

    Squadra   G   V   N   P  GF  GS   DR  Pt
 1. 3B        4   2   1   1   9   5   +4   7
 2. 4A        4   2   1   1   8   7   +1   7
 3. 2D        4   1   1   2   3   7   -4   4
 4. 5C        4   0   3   1   3   4   -1   3

Il cammino di 3B:
  P  1-2 con 4A
  V  3-0 con 2D
  N  2-2 con 5C
  V  3-1 con 4A
```

---

## Errori comuni da evitare

**Tenere un puntatore a un elemento attraverso un'aggiunta**
```c
Contatto *p = trova(rubrica, "Rossi");
aggiungi(rubrica, nuovo);
strcpy(p->telefono, "...");         /* p può puntare a memoria liberata */
```

**Distruggere un vettore di vettori dall'alto**
```c
free(s->dati);                      /* i vettori delle righe sono persi */
```

**Credere che copiare la struct copi gli elementi**
```c
Vettore b = *a;
b.dati[0] = 99;                     /* cambia anche a */
free(a->dati); free(b.dati);        /* doppio free */
```

**Distruggere due volte tramite un alias**
```c
Vettore *alias = originale;
distruggi_vettore(originale);
distruggi_vettore(alias);           /* stesso blocco: doppio free */
```

**Dimenticare il vettore restituito da una funzione**
```c
stampa(sotto_scorta(magazzino));    /* il vettore creato non si può più liberare */
```

---

## Concetti collegati

- `01-vettore-dinamico` → il tipo vettore e le sue funzioni
- `02-operazioni-sul-vettore` → inserire e rimuovere
- `01-malloc-e-free` → array di puntatori a blocchi
- `10-strutture-dati/01-liste-concatenate` → strutture in cui gli elementi non si spostano mai

---

## Esercizi proposti

1. In `010-vettore-di-struct.c` aggiungi la funzione `cerca(c, nome)` che
   restituisce il puntatore allo studente o `NULL`.

2. In `020-vettore-di-vettori.c` stampa per ogni classe anche il voto
   migliore e il peggiore.

3. In `030-copiare-e-confrontare.c` scrivi `copia_parte(v, da, a)` che
   restituisce un vettore nuovo con gli elementi da `da` ad `a - 1`.

4. In `060-problema-storico-dei-prezzi.c` trova la serie più lunga di
   mesi consecutivi senza aumenti.

5. (Avanzato) In `080-problema-statistiche-del-torneo.c` aggiungi la
   classifica dei migliori attacchi (gol fatti) senza modificare l'ordine
   della classifica: crea un vettore di indici e ordina quello.
