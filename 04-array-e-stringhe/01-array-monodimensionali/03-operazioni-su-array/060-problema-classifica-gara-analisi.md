# Analisi – 060-problema-classifica-gara.c

## 1. Problema

Otto atleti partecipano a una gara di corsa. Il programma deve stabilire
l'ordine di arrivo, stampare la classifica con il distacco dal primo in secondi, calcolare
il tempo medio e indicare quanti atleti hanno corso sotto la media.

---

## 2. Analisi

### Input
Nessun input da tastiera: nomi e tempi sono inizializzati nel codice.

| Variabile | Tipo       | Dimensione | Descrizione                                   |
|-----------|------------|------------|-----------------------------------------------|
| `nomi`    | `char[][]` | 8 × 20     | Cognome e nome di ogni atleta                 |
| `tempi`   | `int[]`    | 8          | Tempo in secondi, parallelo a `nomi`          |

### Output
- La classifica in ordine di arrivo: posizione, nome, tempo nel formato
  `m'ss"` e distacco dal vincitore in secondi ("--" per il primo);
- il tempo medio e il vincitore;
- l'elenco, in ordine di arrivo, degli atleti più veloci della media, con lo
  scarto, e il loro numero.

### Vincoli
- L'ordine di arrivo si costruisce senza algoritmi di ordinamento: a ogni
  posizione si cerca il tempo minimo tra gli atleti non ancora classificati
- Ogni atleta compare in classifica una sola volta (flag `classificato`)
- A parità di tempo precede l'atleta che compare prima negli array
- Il distacco è `tempo dell'atleta − tempo del vincitore`
- Un atleta è sotto la media se il suo tempo è **strettamente** minore
- La media si calcola con una divisione reale

### Assunzioni
- I tempi sono positivi e inferiori a un'ora

### Variabili di supporto

| Variabile          | Tipo      | Dimensione | Descrizione                                     |
|--------------------|-----------|------------|-------------------------------------------------|
| `ordine`           | `int[]`   | 8          | `ordine[p]` = indice dell'atleta in posizione p+1 |
| `classificato`     | `int[]`   | 8          | 1 se l'atleta è già in `ordine`                 |
| `migliore`         | `int`     | —          | Candidato della ricerca corrente (-1 se nessuno)|
| `indice_vincitore` | `int`     | —          | `ordine[0]`                                     |
| `minuti`, `secondi`, `distacco` | `int` | — | Dati della riga stampata                     |
| `somma`, `media`   | `int`, `double` | —    | Tempo totale e medio                            |
| `sotto_media`      | `int`     | —          | Atleti più veloci della media                   |
| `ATLETI`           | `#define` | 8          | Numero di atleti                                |

### Algoritmo in linguaggio naturale
1. Per ogni posizione da 1 a 8:
   a. cercare, tra gli atleti non ancora classificati, quello con il tempo
      minimo;
   b. inserirlo in `ordine` e segnarlo come classificato.
2. Il vincitore è `ordine[0]`.
3. Per ogni posizione stampare nome, tempo (`tempo / 60` minuti e
   `tempo % 60` secondi) e distacco dal vincitore.
4. Calcolare e stampare la media; stampare il vincitore.
5. Scorrendo `ordine`, stampare gli atleti con tempo minore della media e
   contarli.

---

## 3. Casi di test

Il programma non legge dati: si esegue con i dati del codice; il Test 3
richiede di modificare i tempi e ricompilare.

### Test 1 – Classifica
- **Input:** tempi 183, 197, 175, 202, 191, 178, 209, 186
- **Output atteso:**
```
   1°  | Verdi Paolo         | 2'55"       | --
   2°  | Conti Matteo        | 2'58"       | +3"
   3°  | Rossi Marco         | 3'03"       | +8"
   4°  | Greco Simone        | 3'06"       | +11"
   5°  | Russo Andrea        | 3'11"       | +16"
   6°  | Bianchi Luca        | 3'17"       | +22"
   7°  | Ferrari Giorgio     | 3'22"       | +27"
   8°  | Marino Fabio        | 3'29"       | +34"
```

### Test 2 – Media e atleti sotto la media
- **Valori intermedi attesi:** somma 1521, media 190.125
- **Output atteso:**
```
Tempo medio         : 190.1 secondi
Vincitore           : Verdi Paolo (175")

Atleti sotto la media (piu' veloci di 190.1"):
  Verdi Paolo: 175"  (-15.1" dalla media)
  Conti Matteo: 178"  (-12.1" dalla media)
  Rossi Marco: 183"  (-7.1" dalla media)
  Greco Simone: 186"  (-4.1" dalla media)
Totale: 4 atleti su 8
```

### Test 3 – Due atleti a pari tempo
- **Cosa si verifica:** a parità precede chi compare prima negli array
- **Procedura:** dare a Russo Andrea (quinto) il tempo 175, uguale a quello
  di Verdi Paolo (terzo)
- **Output atteso:**
```
   1°  | Verdi Paolo         | 2'55"       | --
   2°  | Russo Andrea        | 2'55"       | +0"
   3°  | Conti Matteo        | 2'58"       | +3"
```
