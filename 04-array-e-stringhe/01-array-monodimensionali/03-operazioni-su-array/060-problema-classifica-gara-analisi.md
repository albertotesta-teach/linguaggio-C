# Analisi – 060-problema-classifica-gara.c

## 1. Problema

Otto atleti partecipano a una gara di corsa. Il programma deve stabilire
l'ordine di arrivo, stampare la classifica con il distacco dal primo in secondi, calcolare
il tempo medio e indicare quanti atleti hanno corso sotto la media.

---

## 2. Analisi generale e struttura dati

| Variabile          | Tipo       | Dimensione | Motivazione                                        |
|--------------------|------------|------------|----------------------------------------------------|
| `nomi`             | `char[][]` | 8 × 20     | Nome e cognome di ogni atleta                      |
| `tempi`            | `int[]`    | 8          | Tempo in secondi; indice parallelo a `nomi`        |
| `ordine`           | `int[]`    | 8          | `ordine[p]` = indice dell'atleta in posizione p+1  |
| `classificato`     | `int[]`    | 8          | Flag: 1 se l'atleta è già stato inserito in `ordine` |
| `indice_vincitore` | `int`      | —          | Indice dell'atleta con tempo minimo (`ordine[0]`)  |
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
   2°  | Conti Matteo        | 2'58"       | +3"
   3°  | Rossi Marco         | 3'03"       | +8"
  ...
```

**c) Variabili di supporto**
- `migliore` (`int`): indice del candidato con tempo minimo tra i non classificati
  (-1 finché non se ne trova uno).
- `atleta` (`int`): `ordine[pos]`, indice dell'atleta da stampare.
- `minuti` (`int`): `tempi[i] / 60`.
- `secondi` (`int`): `tempi[i] % 60`.
- `distacco` (`int`): `tempi[i] - tempi[indice_vincitore]`.

**d) Vincoli**
- L'ordine di arrivo viene costruito prima del ciclo di stampa.
- Ogni atleta compare in `ordine` una sola volta: dopo essere stato scelto
  il suo flag in `classificato` vale 1 e non è più candidabile.
- Il distacco è sempre positivo o zero (il vincitore ha distacco zero).
- Il formato `%02d` garantisce due cifre per i secondi (es. `3'05"` non `3'5"`).

**e) Assunzioni**
- I tempi sono espressi in secondi interi.
- Non ci sono pareggi: a parità di tempo precede l'atleta inserito per primo
  negli array, perché il confronto usa `<` e non `<=`.

**f) Algoritmo in linguaggio naturale**
```
1. Porre classificato[i] = 0 per ogni atleta.
2. Per pos da 0 a ATLETI - 1:
   a. migliore = -1.
   b. Per i da 0 a ATLETI - 1: se classificato[i] == 0 e
      (migliore == -1 oppure tempi[i] < tempi[migliore]): migliore = i.
   c. ordine[pos] = migliore, classificato[migliore] = 1.
3. indice_vincitore = ordine[0].
4. Per pos da 0 a ATLETI - 1:
   a. atleta = ordine[pos].
   b. Calcolare minuti e secondi da tempi[atleta].
   c. distacco = tempi[atleta] - tempi[indice_vincitore].
   d. Stampare la posizione pos + 1; se pos == 0 stampare "--",
      altrimenti "+distacco".
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
3. Per pos da 0 a ATLETI-1 (in ordine di arrivo):
   a. atleta = ordine[pos].
   b. Se (double)tempi[atleta] < media: stampare e incrementare sotto_media.
4. Stampare totale.
```
