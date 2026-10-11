# 01 – Logica booleana

## Concetto

Tutte le strutture di controllo del capitolo (`if`, `switch`, `while`, `for`)
prendono decisioni valutando una **condizione**. Prima di usarle bisogna
saper costruire una condizione corretta: questa sezione fornisce gli
strumenti essenziali della logica di Boole, senza entrare nella teoria
formale.

Gli operatori relazionali e logici sono già stati presentati come espressioni
nel capitolo 01 (`01-introduzione/04-operatori/020-operatori-relazionali-e-logici.c`).
Qui li riprendiamo dal punto di vista della logica.

### Vero e falso in C

| Valore | Significato in una condizione |
|--------|-------------------------------|
| `0` | falso |
| qualunque valore diverso da `0` | vero |

I confronti (`==`, `!=`, `<`, `>`, `<=`, `>=`) e gli operatori logici
restituiscono sempre `1` (vero) oppure `0` (falso). Una variabile `int` che
contiene solo 0 o 1 si chiama **variabile booleana** o **flag**.

### Tavole di verità

```
  NOT          AND               OR                XOR (o esclusivo)
  a | !a       a b | a && b      a b | a || b      a b | a != b
  0 |  1       0 0 |   0         0 0 |   0         0 0 |   0
  1 |  0       0 1 |   0         0 1 |   1         0 1 |   1
               1 0 |   0         1 0 |   1         1 0 |   1
               1 1 |   1         1 1 |   1         1 1 |   0
```

- **AND**: vero solo se tutte le condizioni sono vere.
- **OR**: vero se almeno una condizione è vera (anche se lo sono tutte).
- **XOR**: in C non esiste come operatore logico; su valori 0/1 si scrive
  `a != b`, oppure `(a || b) && !(a && b)`.

### Precedenza

```
  più alta    !
              <  >  <=  >=
              ==  !=
              &&
  più bassa   ||
```

`&&` lega più di `||`: `a || b && c` si legge `a || (b && c)`. Quando `&&` e
`||` compaiono insieme si scrivono sempre le parentesi: rendono chiaro il
significato e gcc con `-Wall` le richiede.

### Intervalli

| Condizione | Espressione C |
|------------|---------------|
| `x` dentro `[min, max]` | `x >= min && x <= max` |
| `x` fuori da `[min, max]` | `x < min \|\| x > max` |

### Negare una condizione composta (De Morgan)

```
  !(a && b)   equivale a   !a || !b
  !(a || b)   equivale a   !a && !b
```

Si negano le singole parti e si scambia `&&` con `||`. Ricordare che la
negazione di `>=` è `<` e la negazione di `<=` è `>`. Servirà per scrivere
la condizione con cui un ciclo continua a partire da quella con cui si ferma.

### Corto circuito

`&&` e `||` valutano da sinistra a destra e si fermano appena il risultato è
certo. In `divisore != 0 && dividendo / divisore > 2` la divisione avviene
solo se il divisore è diverso da zero.

### Dalla frase alla condizione

1. Individuare le condizioni elementari (un confronto ciascuna).
2. Tradurre i connettivi: "e", "ma" → `&&`; "o", "oppure" → `||`;
   "non", "tranne" → `!`; "o... o..." (uno solo) → `a != b`.
3. Aggiungere le parentesi.

In questa sezione non sono ancora disponibili `if` e cicli: i risultati
vengono stampati come 0/1 oppure scelti con l'operatore ternario `?:`.

---

## File dell'esempio

| File | Contenuto |
|------|-----------|
| `010-valori-di-verita.c` | 0 è falso, tutto il resto è vero; risultato dei confronti; variabili booleane; stampa con il ternario |
| `020-tavole-di-verita.c` | Tavole di verità di NOT, AND, OR, XOR e di un'espressione con tre ingressi, calcolate dal programma |
| `030-combinazione-di-operatori.c` | Precedenza e parentesi, intervalli, leggi di De Morgan, corto circuito |
| `040-dal-testo-alla-condizione.c` | Traduzione di cinque regole scritte in italiano in condizioni C; errori tipici di traduzione |
| `050-problema-anno-bisestile.c` | Regola gregoriana dell'anno bisestile come unica espressione logica |
| `050-problema-anno-bisestile-analisi.md` | Analisi di `050-problema-anno-bisestile.c` |
| `060-problema-requisiti-concorso.c` | Requisiti di ammissione a un concorso: età, titolo, prova con due modi di superamento |
| `060-problema-requisiti-concorso-analisi.md` | Analisi di `060-problema-requisiti-concorso.c` |
| `070-problema-orario-apertura.c` | Apertura di un negozio con fasce orarie diverse per giorni feriali e sabato |
| `070-problema-orario-apertura-analisi.md` | Analisi di `070-problema-orario-apertura.c` |

---

## Compilazione ed esecuzione

```bash
gcc -Wall -Wextra -o 010-valori-di-verita 010-valori-di-verita.c
./010-valori-di-verita

gcc -Wall -Wextra -o 020-tavole-di-verita 020-tavole-di-verita.c
./020-tavole-di-verita

gcc -Wall -Wextra -o 030-combinazione-di-operatori 030-combinazione-di-operatori.c
./030-combinazione-di-operatori

gcc -Wall -Wextra -o 040-dal-testo-alla-condizione 040-dal-testo-alla-condizione.c
./040-dal-testo-alla-condizione

gcc -Wall -Wextra -o 050-problema-anno-bisestile 050-problema-anno-bisestile.c
./050-problema-anno-bisestile

gcc -Wall -Wextra -o 060-problema-requisiti-concorso 060-problema-requisiti-concorso.c
./060-problema-requisiti-concorso

gcc -Wall -Wextra -o 070-problema-orario-apertura 070-problema-orario-apertura.c
./070-problema-orario-apertura
```

---

## Output atteso

### 010-valori-di-verita
```
=== Il risultato di un confronto ===
temperatura = 23
temperatura > 20   vale 1  (vero)
temperatura > 30   vale 0  (falso)
temperatura == 23  vale 1  (vero)

=== Variabili booleane ===
fa_caldo   = 0
sala_piena = 1
in_rosso   = 1

=== Che cosa e' vero per il C ===
valore    0 -> come condizione vale 0 (falso)
valore    1 -> come condizione vale 1 (vero)
valore   42 -> come condizione vale 1 (vero)
valore   -7 -> come condizione vale 1 (vero)
valore saldo (-150) -> vale 1 (vero: e' diverso da 0)
valore posti_liberi (0) -> vale 0 (falso)

=== Stampa leggibile ===
Fa caldo?       no
Sala piena?     si'
Conto in rosso? si'
```

### 020-tavole-di-verita
```
=== NOT (!) ===
  a | !a
  --+---
  0 |  1
  1 |  0

=== AND (&&) ===
  a b | a && b
  ----+-------
  0 0 |   0
  0 1 |   0
  1 0 |   0
  1 1 |   1

=== OR (||) ===
  a b | a || b
  ----+-------
  0 0 |   0
  0 1 |   1
  1 0 |   1
  1 1 |   1

=== XOR (o esclusivo) ===
  a b | (a||b) && !(a&&b) | a != b
  ----+--------------------+-------
  0 0 |         0          |   0
  0 1 |         1          |   1
  1 0 |         1          |   1
  1 1 |         0          |   0

=== Tre ingressi: a && (m || p) ===
  a m p | risultato
  ------+----------
  0 0 0 |     0
  0 0 1 |     0
  0 1 0 |     0
  0 1 1 |     0
  1 0 0 |     0
  1 0 1 |     1
  1 1 0 |     1
  1 1 1 |     1
```

### 030-combinazione-di-operatori
```
=== 1. Precedenza: && prima di || ===
eta = 4, residente = 0, feriale = 0
eta < 6 || (residente && feriale)   -> 1  (gratis anche di domenica)
(eta < 6 || residente) && feriale   -> 0  (regola corretta)
Regola pratica: quando && e || compaiono insieme, usare le parentesi.

=== 2. Intervalli ===
ora = 21
orario d'ufficio [9, 18]:       0
fuori dall'orario d'ufficio:    1
voto = 5
voto valido [1, 10]:            1
voto sufficiente [6, 10]:       0

=== 3. De Morgan ===
!(ora >= 9 && ora <= 18)  -> 1
ora < 9 || ora > 18       -> 1  (stesso valore)
!(eta < 6 || residente)   -> 0
eta >= 6 && !residente    -> 0  (stesso valore)

=== 4. Corto circuito ===
divisore = 0
divisore != 0 && dividendo / divisore > 2  -> 0
La divisione per zero non avviene: la prima condizione e' falsa.
```

### 040-dal-testo-alla-condizione
```
=== Dati ===
eta = 17, giorno = 7, ora = 21
scritto = 7, orale = 5
carta fedelta' = 1, importo = 40 euro
carta = 1, contanti = 0

=== Condizioni ===
Maggiorenne con meno di 65 anni:  0
Giorno festivo oppure sera:       1
Promosso:                         0
Diritto allo sconto:              1
Un solo metodo di pagamento:      1
```

### 050-problema-anno-bisestile
*(output dipendente dall'input – esempio con l'anno 2024)*
```
=== ANNO BISESTILE ===

Inserisci un anno (es. 2024): 2024

--- Passaggi della verifica ---
  divisibile per 4   : 1
  divisibile per 100 : 0
  divisibile per 400 : 0
  (div4 && !div100)  : 1
  || div400          : 1

Il 2024 e' bisestile: febbraio ha 29 giorni.
```

*(output dipendente dall'input – esempio con l'anno 1900)*
```
=== ANNO BISESTILE ===

Inserisci un anno (es. 2024): 1900

--- Passaggi della verifica ---
  divisibile per 4   : 1
  divisibile per 100 : 1
  divisibile per 400 : 0
  (div4 && !div100)  : 0
  || div400          : 0

Il 1900 non e' bisestile: febbraio ha 28 giorni.
```

### 060-problema-requisiti-concorso
*(output dipendente dall'input – esempio con età 28, laurea, punteggio 55)*
```
=== CONCORSO COMUNALE - VERIFICA REQUISITI ===

Eta' del candidato: 28
Titolo di studio (0 = nessuno, 1 = diploma, 2 = laurea): 2
Punteggio della prova preselettiva (0-100): 55

--- Riepilogo ---
  Dati inseriti validi           : SI'
  Eta' tra 18 e 35 anni          : SI'
  Almeno il diploma              : SI'
  Prova preselettiva superata    : SI'

Esito: AMMESSO
```

*(output dipendente dall'input – esempio con età 40, diploma, punteggio 75)*
```
=== CONCORSO COMUNALE - VERIFICA REQUISITI ===

Eta' del candidato: 40
Titolo di studio (0 = nessuno, 1 = diploma, 2 = laurea): 1
Punteggio della prova preselettiva (0-100): 75

--- Riepilogo ---
  Dati inseriti validi           : SI'
  Eta' tra 18 e 35 anni          : NO
  Almeno il diploma              : SI'
  Prova preselettiva superata    : SI'

Esito: NON AMMESSO
```

### 070-problema-orario-apertura
*(output dipendente dall'input – esempio con mercoledì alle 15:45)*
```
=== FERRAMENTA - ORARIO DI APERTURA ===

Giorno (1 = lunedi' ... 7 = domenica): 3
Ora (formato HH MM, es. 15 45): 15 45

--- Verifica ---
  Dati validi             : 1
  Giorno feriale          : 1
  Sabato                  : 0
  Fascia 09:00-12:30      : 0
  Fascia 15:30-19:30      : 1
  Fascia sabato 09-13     : 0

Alle 15:45 del giorno 3 il negozio e' APERTO.
```

*(output dipendente dall'input – esempio con sabato alle 16:00)*
```
=== FERRAMENTA - ORARIO DI APERTURA ===

Giorno (1 = lunedi' ... 7 = domenica): 6
Ora (formato HH MM, es. 15 45): 16 00

--- Verifica ---
  Dati validi             : 1
  Giorno feriale          : 0
  Sabato                  : 1
  Fascia 09:00-12:30      : 0
  Fascia 15:30-19:30      : 1
  Fascia sabato 09-13     : 0

Alle 16:00 del giorno 6 il negozio e' CHIUSO.
```

---

## Errori comuni da evitare

**Intervallo scritto come in matematica**
```c
if (18 <= eta <= 65)        /* ERRATO: (18 <= eta) vale 0 o 1, sempre <= 65 */
if (eta >= 18 && eta <= 65) /* corretto */
```

**Variabile sottintesa nel secondo confronto**
```c
giorno == 6 || 7            /* ERRATO: 7 è diverso da 0, quindi sempre vero */
giorno == 6 || giorno == 7  /* corretto */
```

**"e" tradotto con && quando indica casi alternativi**
```c
/* "sconto il sabato e la domenica" */
giorno == 6 && giorno == 7  /* ERRATO: mai vero */
giorno == 6 || giorno == 7  /* corretto */
```

**Negazione sbagliata di un intervallo**
```c
!(x >= 1 && x <= 10)        /* fuori dall'intervallo */
x < 1 && x > 10             /* ERRATO: mai vero, && va scambiato con || */
x < 1 || x > 10             /* corretto (De Morgan) */
```

**Confusione tra operatori**
```c
a = 0      /* assegnazione: vale 0, quindi falso */
a == 0     /* confronto */
a & b      /* AND bit a bit */
a && b     /* AND logico: quello da usare nelle condizioni */
```

**Ordine sbagliato con il corto circuito**
```c
dividendo / divisore > 2 && divisore != 0   /* ERRATO: divide prima di controllare */
divisore != 0 && dividendo / divisore > 2   /* corretto */
```

---

## Concetti collegati

- `01-introduzione/04-operatori` → operatori relazionali, logici e ternario come espressioni
- `02-if-else` → le condizioni costruite qui decidono quale ramo eseguire
- `04-while-do-while` → condizioni di continuazione dei cicli e uso di De Morgan
- `06-break-continue` → variabili flag al posto delle uscite anticipate

---

## Esercizi proposti

1. Scrivi le tavole di verità di `!a && b` e di `!(a && b)` e verifica che
   sono diverse.

2. Traduci in C la regola: "il parcheggio è gratuito la domenica oppure nei
   giorni feriali prima delle 8 e dopo le 20". Stampa il risultato per alcuni
   valori di giorno e ora.

3. Partendo da `030-combinazione-di-operatori.c`, scrivi con De Morgan la
   negazione di `(eta >= 18 && eta <= 65) || pensionato` e verifica che i due
   valori coincidano per diversi valori delle variabili.

4. Modifica `050-problema-anno-bisestile.c` per stampare anche il numero di
   giorni dell'anno (365 o 366) senza usare il ternario.

5. (Avanzato) Estendi `070-problema-orario-apertura.c` con l'orario estivo:
   in luglio e agosto il pomeriggio va dalle 16:00 alle 20:00. Aggiungi il
   mese tra i dati in ingresso.
