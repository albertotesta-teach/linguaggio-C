# 02 – Operazioni sul vettore

## Concetto

Oltre ad `aggiungi` in fondo, un vettore dinamico permette di inserire e
rimuovere **in qualsiasi posizione**, spostando gli elementi.

### Inserire in mezzo

Per inserire in posizione `p` si fa spazio spostando a destra gli
elementi da `p` in poi, **partendo dall'ultimo**:

```
inserisci(v, 2, 50)

prima:   [10 20 30 40 __]
sposta:  [10 20 30 30 40]     for (i = n - 1; i >= p; i--) dati[i + 1] = dati[i];
scrive:  [10 20 50 30 40]
```

La posizione va da `0` (in testa) a `n` (in fondo). Se il vettore è
pieno, la capacità raddoppia prima dello spostamento.

### Rimuovere

Per togliere l'elemento in posizione `p` si spostano a sinistra i
successivi, **partendo dal primo dopo `p`**:

```
rimuovi(v, 1, &valore)          valore = 20

prima:   [10 20 30 40]
sposta:  [10 30 40 40]          for (i = p; i < n - 1; i++) dati[i] = dati[i + 1];
dopo:    [10 30 40]             n = 3
```

`togli_ultimo` non sposta niente: aggiungere e togliere dal fondo costa
una sola operazione.

| Operazione | Elementi spostati |
|------------|-------------------|
| aggiungi in fondo | 0 |
| togli l'ultimo | 0 |
| inserisci / rimuovi in posizione `p` | `n - p` |
| inserisci / rimuovi in testa | `n` |

### Ridurre la capacità

Dopo molte rimozioni si può restituire memoria dimezzando la capacità,
ma **solo quando `n` scende a `capacita / 4`**. Dimezzare già a
`capacita / 2` lascia il vettore pieno: la prossima aggiunta raddoppia di
nuovo e si va in altalena (una realloc a ogni operazione).

---

## File dell'esempio

| File | Contenuto |
|------|-----------|
| `010-inserire-in-mezzo.c` | `inserisci` con spostamento a destra: l'ordine delle interrogazioni |
| `020-rimuovere.c` | `rimuovi` e `togli_ultimo`: i libri in prestito alla classe |
| `030-ridurre-la-capacita.c` | Regola `capacita / 2` contro `capacita / 4`: l'altalena delle realloc |
| `040-problema-classifica-in-ordine.c` | Classifica della corsa campestre tenuta sempre ordinata |
| `040-problema-classifica-in-ordine-analisi.md` | Analisi di `040-problema-classifica-in-ordine.c` |
| `050-problema-coda-della-mensa.c` | Fila della mensa: si entra in fondo, si esce dall'inizio |
| `050-problema-coda-della-mensa-analisi.md` | Analisi di `050-problema-coda-della-mensa.c` |
| `060-problema-annulla-ultima-operazione.c` | Annullare le modifiche a un voto, dall'ultima |
| `060-problema-annulla-ultima-operazione-analisi.md` | Analisi di `060-problema-annulla-ultima-operazione.c` |
| `070-problema-elenco-senza-doppioni.c` | Volontari dell'open day: aggiungi se manca, rimuovi per valore |
| `070-problema-elenco-senza-doppioni-analisi.md` | Analisi di `070-problema-elenco-senza-doppioni.c` |
| `080-problema-unione-e-intersezione.c` | Due vettori ordinati: unione e intersezione in una passata |
| `080-problema-unione-e-intersezione-analisi.md` | Analisi di `080-problema-unione-e-intersezione.c` |

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-inserire-in-mezzo 010-inserire-in-mezzo.c
./010-inserire-in-mezzo

gcc -Wall -Wextra -o 020-rimuovere 020-rimuovere.c
./020-rimuovere

gcc -Wall -Wextra -o 030-ridurre-la-capacita 030-ridurre-la-capacita.c
./030-ridurre-la-capacita

gcc -Wall -Wextra -o 040-problema-classifica-in-ordine 040-problema-classifica-in-ordine.c
./040-problema-classifica-in-ordine

gcc -Wall -Wextra -o 050-problema-coda-della-mensa 050-problema-coda-della-mensa.c
./050-problema-coda-della-mensa

gcc -Wall -Wextra -o 060-problema-annulla-ultima-operazione 060-problema-annulla-ultima-operazione.c
./060-problema-annulla-ultima-operazione

gcc -Wall -Wextra -o 070-problema-elenco-senza-doppioni 070-problema-elenco-senza-doppioni.c
./070-problema-elenco-senza-doppioni

gcc -Wall -Wextra -o 080-problema-unione-e-intersezione 080-problema-unione-e-intersezione.c
./080-problema-unione-e-intersezione
```

---

## Output atteso

### 010-inserire-in-mezzo
```
inizio             [ ]  n = 0, capacita' = 2
inserisci(0, 12)   [ 12 ]  n = 1, capacita' = 2
inserisci(1, 5)    [ 12  5 ]  n = 2, capacita' = 2
inserisci(0, 20)   [ 20 12  5 ]  n = 3, capacita' = 4
inserisci(3, 8)    [ 20 12  5  8 ]  n = 4, capacita' = 4
inserisci(2, 17)   [ 20 12 17  5  8 ]  n = 5, capacita' = 8
inserisci(9, 3)    posizione non valida (da 0 a 5)
```

### 020-rimuovere
```
  [ 101 205 309 412 518 623 ]  n = 6, capacita' = 8
restituito il libro in posizione 1: 205
  [ 101 309 412 518 623 ]  n = 5, capacita' = 8
restituito il primo libro: 101
  [ 309 412 518 623 ]  n = 4, capacita' = 8
posizione 7 non valida: nessuna modifica
restituito l'ultimo: 623
restituito l'ultimo: 518
restituito l'ultimo: 412
restituito l'ultimo: 309
  [ ]  n = 0, capacita' = 8
vettore vuoto: niente da togliere
```

### 030-ridurre-la-capacita
```
dimezza quando n = capacita / 2: 40 realloc in 40 operazioni
dimezza quando n = capacita / 4:  0 realloc in 40 operazioni

Svuotamento con la regola capacita / 4:
  n = 32, capacita' = 32
  n = 16, capacita' = 32
  n =  8, capacita' = 16
  n =  4, capacita' =  8
  n =  2, capacita' =  4
  n =  0, capacita' =  4
```

### 040-problema-classifica-in-ordine
*(output dipendente dall'input – corsa campestre)*
```
Comando (A, S, C, Q): A Rossi 12:40
  Rossi in posizione 1
Comando (A, S, C, Q): A Bianchi 11:55
  Bianchi in posizione 1
Comando (A, S, C, Q): A Verdi 13:10
  Verdi in posizione 3
Comando (A, S, C, Q): A Neri 12:40
  Neri in posizione 3
Comando (A, S, C, Q): A Gialli 11:20
  Gialli in posizione 1
Comando (A, S, C, Q): A Rossi 12:00
  Rossi ha gia' un tempo.
Comando (A, S, C, Q): A Russo 12:61
  Dati non validi.
Comando (A, S, C, Q): C
   1. Gialli     11:20  +0 s
   2. Bianchi    11:55  +35 s
   3. Rossi      12:40  +80 s
   4. Neri       12:40  +80 s
   5. Verdi      13:10  +110 s
Comando (A, S, C, Q): S Bianchi
  squalifica di Bianchi: chi seguiva sale di una posizione
Comando (A, S, C, Q): S Ferri
  Atleta non in classifica.
Comando (A, S, C, Q): C
   1. Gialli     11:20  +0 s
   2. Rossi      12:40  +80 s
   3. Neri       12:40  +80 s
   4. Verdi      13:10  +110 s
Comando (A, S, C, Q): Q
```

### 050-problema-coda-della-mensa
*(output dipendente dall'input – la fila del pranzo)*
```
Comando (E, S, L, F, Q): E Anna
  Anna in fila (posizione 1)
Comando (E, S, L, F, Q): E Luca
  Luca in fila (posizione 2)
Comando (E, S, L, F, Q): E Marta
  Marta in fila (posizione 3)
Comando (E, S, L, F, Q): E Paolo
  Paolo in fila (posizione 4)
Comando (E, S, L, F, Q): E Sara
  Sara in fila (posizione 5)
Comando (E, S, L, F, Q): F
  fila: Anna Luca Marta Paolo Sara
Comando (E, S, L, F, Q): S
  servito: Anna (in fila restano 4)
Comando (E, S, L, F, Q): S
  servito: Luca (in fila restano 3)
Comando (E, S, L, F, Q): L Paolo
  Paolo lascia la fila
Comando (E, S, L, F, Q): L Gianni
  Non e' in fila.
Comando (E, S, L, F, Q): E Teo
  Teo in fila (posizione 3)
Comando (E, S, L, F, Q): F
  fila: Marta Sara Teo
Comando (E, S, L, F, Q): S
  servito: Marta (in fila restano 2)
Comando (E, S, L, F, Q): S
  servito: Sara (in fila restano 1)
Comando (E, S, L, F, Q): S
  servito: Teo (in fila restano 0)
Comando (E, S, L, F, Q): S
  Fila vuota.
Comando (E, S, L, F, Q): Q
Serviti: 5, spostamenti nel vettore: 11
```

### 060-problema-annulla-ultima-operazione
*(output dipendente dall'input – correzioni a un voto)*
```
Voto iniziale: 6.0
Comando (=, +, -, U, S, Q): = 7
  voto 7.0
Comando (=, +, -, U, S, Q): + 0.5
  voto 7.5
Comando (=, +, -, U, S, Q): - 2
  voto 5.5
Comando (=, +, -, U, S, Q): + 6
  modifica non valida: voto invariato 5.5
Comando (=, +, -, U, S, Q): S
  voto 5.5, storia [ 6.0 7.0 7.5 ]
Comando (=, +, -, U, S, Q): U
  annullata: voto 7.5
Comando (=, +, -, U, S, Q): S
  voto 7.5, storia [ 6.0 7.0 ]
Comando (=, +, -, U, S, Q): U
  annullata: voto 7.0
Comando (=, +, -, U, S, Q): U
  annullata: voto 6.0
Comando (=, +, -, U, S, Q): U
  niente da annullare
Comando (=, +, -, U, S, Q): = 11
  modifica non valida: voto invariato 6.0
Comando (=, +, -, U, S, Q): Q
```

### 070-problema-elenco-senza-doppioni
*(output dipendente dall'input – volontari dell'open day)*
```
Comando (I, R, E, Q): I rossi
  iscrizione di Rossi (volontari: 1)
Comando (I, R, E, Q): I Bianchi
  iscrizione di Bianchi (volontari: 2)
Comando (I, R, E, Q): I ROSSI
  Rossi e' gia' nell'elenco
Comando (I, R, E, Q): I verdi
  iscrizione di Verdi (volontari: 3)
Comando (I, R, E, Q): I Neri
  iscrizione di Neri (volontari: 4)
Comando (I, R, E, Q): R bianchi
  ritiro di Bianchi (volontari: 3)
Comando (I, R, E, Q): R Gialli
  Gialli non e' nell'elenco
Comando (I, R, E, Q): I bianchi
  iscrizione di Bianchi (volontari: 4)
Comando (I, R, E, Q): E
  1. Rossi
  2. Verdi
  3. Neri
  4. Bianchi
Comando (I, R, E, Q): Q
```

### 080-problema-unione-e-intersezione
*(output dipendente dall'input – due laboratori)*
```
Matricole iscritte a robotica (0 per finire): 1042 1007 1100 1015 1007 -3 1088 0
  1007 gia' iscritta
  matricola -3 non valida
Matricole iscritte a fotografia (0 per finire): 1100 1003 1042 1120 1015 0

Robotica (5): 1007 1015 1042 1088 1100
Fotografia (5): 1003 1015 1042 1100 1120
Almeno un laboratorio (7): 1003 1007 1015 1042 1088 1100 1120
Entrambi (devono scegliere) (3): 1015 1042 1100
```

---

## Errori comuni da evitare

**Spostare a destra partendo dal primo**
```c
for (i = p; i < n; i++) dati[i + 1] = dati[i];   /* copia dati[p] ovunque */
for (i = n - 1; i >= p; i--) dati[i + 1] = dati[i];   /* corretto */
```

**Scrivere oltre la capacità durante l'inserimento**
```c
/* se n == capacita, dati[n] è fuori dal blocco: prima si raddoppia */
```

**Dimenticare di aggiornare n**
```c
for (i = p; i < n - 1; i++) dati[i] = dati[i + 1];
/* manca n--: l'ultimo elemento compare due volte */
```

**Accettare posizioni non valide**
```c
inserisci(v, n + 1, x);   /* valida da 0 a n */
rimuovi(v, n, &x);        /* valida da 0 a n - 1 */
```

**Dimezzare a capacita / 2**
```c
if (n == capacita / 2) dimezza(v);   /* altalena con le aggiunte */
if (n == capacita / 4) dimezza(v);   /* corretto */
```

---

## Concetti collegati

- `01-vettore-dinamico` → struct, crescita a raddoppio, funzioni del tipo
- `11-algoritmi/02-ordinamento-bubble-sort` → spostare elementi in un array
- `10-strutture-dati/02-pile-stack` → aggiungere e togliere dal fondo
- `10-strutture-dati/03-code-queue` → la coda circolare, senza spostamenti

---

## Esercizi proposti

1. In `010-inserire-in-mezzo.c` scrivi `inserisci_in_testa(v, x)` usando
   `inserisci`.

2. In `040-problema-classifica-in-ordine.c` aggiungi il comando `T n` che
   stampa solo i primi `n` della classifica.

3. In `050-problema-coda-della-mensa.c` aggiungi il comando `P nome` che
   fa passare uno studente in testa (precedenza per chi ha la verifica).

4. In `060-problema-annulla-ultima-operazione.c` aggiungi il comando `R`
   (ripeti) che rifà l'ultima modifica annullata.

5. (Avanzato) In `080-problema-unione-e-intersezione.c` aggiungi la
   differenza: gli iscritti a robotica che non fanno fotografia.
