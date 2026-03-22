# Analisi – 060-problema-classifica-gara.c

## 1. Problema

Otto atleti partecipano a una gara di corsa. Il programma deve identificare il
vincitore, stampare la classifica con il distacco dal primo in secondi, calcolare
il tempo medio e indicare quanti atleti hanno corso sotto la media.

---

## 2. Analisi generale e struttura dati

| Variabile          | Tipo       | Dimensione | Motivazione                                        |
|--------------------|------------|------------|----------------------------------------------------|
| `nomi`             | `char[][]` | 8 × 20     | Nome e cognome di ogni atleta                      |
| `tempi`            | `int[]`    | 8          | Tempo in secondi; indice parallelo a `nomi`        |
| `indice_vincitore` | `int`      | —          | Posizione dell'atleta con tempo minimo             |
| `somma`            | `int`      | —          | Accumulatore per il calcolo della media            |
| `media`            | `double`   | —          | Tempo medio del gruppo                             |
| `sotto_media`      | `int`      | —          | Contatore atleti più veloci della media            |
| `ATLETI`           | `#define`  | 8          | Dimensione degli array e limite dei cicli          |

---

## 3. Casi d'uso e funzionalità

---

### Caso d'uso 1 – Stampa della classifica con distacco

**a) Input**
Array `nomi`, `tempi`, variabile `indice_vincitore`.

**b) Output**
```
=== CLASSIFICA GARA ===
  Pos. | Nome                | Tempo       | Distacco
  -----|---------------------|-------------|----------
   1°  | Verdi Paolo         | 2'55"       | --
    -  | Rossi Marco         | 3'03"       | +8"
  ...
```

**c) Variabili di supporto**
- `minuti` (`int`): `tempi[i] / 60`.
- `secondi` (`int`): `tempi[i] % 60`.
- `distacco` (`int`): `tempi[i] - tempi[indice_vincitore]`.

**d) Vincoli**
- Il vincitore viene identificato prima del ciclo di stampa.
- Il distacco è sempre positivo o zero (il vincitore ha distacco zero).
- Il formato `%02d` garantisce due cifre per i secondi (es. `3'05"` non `3'5"`).

**e) Assunzioni**
- I tempi sono espressi in secondi interi.
- Non ci sono pareggi: se due atleti hanno lo stesso tempo minimo, viene
  mostrato solo il primo trovato come vincitore.

**f) Algoritmo in linguaggio naturale**
```
1. Trovare indice_vincitore (ricerca del minimo su tempi[]).
2. Per i da 0 a ATLETI - 1:
   a. Calcolare minuti = tempi[i] / 60, secondi = tempi[i] % 60.
   b. distacco = tempi[i] - tempi[indice_vincitore].
   c. Se i == indice_vincitore: stampare "1°" e "--".
      Altrimenti: stampare "-" e "+distacco".
```

---

### Caso d'uso 2 – Media e atleti sotto media

**a) Input**
Array `tempi`.

**b) Output**
```
Tempo medio : 190.1 secondi

Atleti sotto la media (piu' veloci di 190.1"):
  Verdi Paolo: 175"  (-15.1" dalla media)
  Conti Matteo: 178"  (-12.1" dalla media)
  Rossi Marco: 183"  (-7.1" dalla media)
  Greco Simone: 186"  (-4.1" dalla media)
Totale: 4 atleti su 8
```

**c) Variabili di supporto**
- `somma` (`int`): somma dei tempi.
- `media` (`double`): `somma / ATLETI`.
- `sotto_media` (`int`): contatore.

**d) Vincoli**
- Il cast `(double)tempi[i]` nel confronto garantisce la comparazione corretta
  con `media` (che è double).
- "Sotto la media" per i tempi significa più veloci, quindi minore è meglio.

**f) Algoritmo in linguaggio naturale**
```
1. somma = 0. Per i da 0 a ATLETI-1: somma += tempi[i].
2. media = (double)somma / ATLETI.
3. Per i da 0 a ATLETI-1:
   a. Se (double)tempi[i] < media: stampare e incrementare sotto_media.
4. Stampare totale.
```
