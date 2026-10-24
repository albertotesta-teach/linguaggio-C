# Analisi – 060-problema-confronto-pagelle.c

## 1. Problema

Il coordinatore confronta le pagelle del primo e del secondo quadrimestre
di uno studente. La seconda pagella nasce come copia della prima
(`secondo = primo`, array dei voti compreso) e si aggiornano quadrimestre e
voti. Il programma stampa la variazione per materia, il numero di materie
migliorate e peggiorate, le due medie e le insufficienze recuperate.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `voto` | `int` | Voto del secondo quadrimestre per ognuna delle 5 materie, da 1 a 10 |
| `primo` | `Pagella` | Pagella del primo quadrimestre (nel sorgente): Davide Greco, voti 6, 7, 5, 4, 8 |

### Output

- Per ogni voto non valido: `voto non valido, resta N` (resta il voto del
  primo quadrimestre).
- La tabella materia, voto 1Q, voto 2Q, variazione (`+n`, `-n` o `=`).
- `Materie migliorate: M, peggiorate: P`.
- `Media: A -> B` con due decimali.
- `Insufficienze recuperate: R`.

### Vincoli

- L'assegnamento tra struct copia anche l'array `voti` contenuto nella
  struct.
- Un'insufficienza è recuperata se il voto passa da meno di 6 a 6 o più.
- Un voto non numerico viene scartato (resto della riga) e resta il voto
  precedente.

### Assunzioni

- Le materie sono le stesse nei due quadrimestri.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Pagella` | `typedef struct { char nome[20]; int quadrimestre; int voti[5]; } Pagella;` | Pagella di un quadrimestre |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `secondo` | `Pagella` | Copia della prima pagella, poi aggiornata |
| `materie` | `const char *[5]` | Nomi delle materie |
| `letti` | `int` | Valore restituito da `scanf` |
| `migliorate`, `peggiorate`, `recuperate` | `int` | Contatori |
| `somma_primo`, `somma_secondo` | `int` | Per le medie |

| Funzione | Compito |
|----------|---------|
| `svuota_riga` | Scarta i caratteri rimasti dopo un inserimento non valido |

### Algoritmo in linguaggio naturale

1. `secondo = primo`, poi quadrimestre 2.
2. Per ogni materia leggere il voto; se valido sostituirlo, altrimenti
   segnalare che resta quello precedente.
3. Per ogni materia stampare i due voti e la variazione, contare le
   materie migliorate, peggiorate e le insufficienze recuperate, sommare i
   voti.
4. Stampare contatori e medie.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Voto non numerico

- **Cosa si verifica:** variazioni, recupero di matematica e voto che
  resta invariato.
- **Input:** `7`, `6`, `xyz`, `6`, `9`
- **Valori intermedi attesi:** somma 1Q 30, 2Q 33.
- **Output atteso** (dopo le richieste):
  ```
    inglese      (primo: 5):   voto non valido, resta 5
  ...
    Materia        1Q   2Q  Variazione
    italiano        6    7  +1
    storia          7    6  -1
    inglese         5    5  =
    matematica      4    6  +2
    informatica     8    9  +1

  Materie migliorate: 3, peggiorate: 1
  Media: 6.00 -> 6.60
  Insufficienze recuperate: 1
  ```

### Test 2 – Voto fuori intervallo

- **Input:** `7`, `6`, `11`, `6`, `8`
- **Output atteso:** `voto non valido, resta 5` per inglese;
  `Materie migliorate: 2, peggiorate: 1`, `Media: 6.00 -> 6.40`.
