# Analisi – 080-problema-statistiche-del-torneo.c

## 1. Problema

Al torneo di calcetto d'istituto il numero di squadre e di partite non è
noto. Ogni partita `casa ospite gol gol` si registra due volte, una per
squadra dal suo punto di vista, nel vettore di risultati della squadra.
Dai risultati si ricavano partite, vittorie, pareggi, sconfitte, gol e
punti; il vettore delle squadre si ordina con selection sort per la
classifica, e si stampa il cammino della prima.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| partite | testo | `casa ospite gol gol`; `FINE` termina |

### Output

- `partita non valida (casa)` per ogni partita scartata.
- La classifica: posizione, squadra, giocate, vinte, pari, perse, gol
  fatti e subiti, differenza reti, punti.
- `Il cammino di X:` con `V`/`N`/`P`, punteggio e avversario per ogni
  partita della prima.
- `Nessuna partita registrata.`, `Memoria insufficiente.`

### Vincoli

- Due livelli di vettori: `Torneo` di `Squadra`, ognuna con un
  `Risultati *` che parte da 2 posti e raddoppia.
- Le squadre si creano alla prima partita (`indice_squadra`).
- Vittoria 3 punti, pareggio 1; ordine per punti, poi differenza reti,
  poi gol fatti; a parità completa resta l'ordine di comparsa.
- L'ordinamento scambia le struct `Squadra` (nome e puntatore), non i
  vettori dei risultati.
- Partita valida: squadre diverse, gol non negativi.
- Distruzione: i risultati di ogni squadra, poi l'array, poi la struct.

### Assunzioni

- I nomi delle squadre hanno al massimo 7 caratteri.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Risultato` | `typedef struct { char avversario[8]; int fatti; int subiti; } Risultato;` | Una partita dal punto di vista di una squadra |
| `Risultati` | `typedef struct { Risultato *dati; int n; int capacita; } Risultati;` | Vettore dei risultati |
| `Squadra` | `typedef struct { char nome[8]; Risultati *risultati; } Squadra;` | Una squadra |
| `Torneo` | `typedef struct { Squadra *dati; int n; int capacita; } Torneo;` | Vettore delle squadre |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `torneo` | `Torneo *` | Le squadre |
| `r`, `x` | `Risultati *`, `Risultato` | Per la stampa |
| `letti` | `int` | Valore restituito da `scanf` |

| Funzione | Compito |
|----------|---------|
| funzioni di `Risultati` | Creazione, aggiunta, accesso, distruzione |
| `segno`, `conta`, `punti`, `gol_fatti`, `gol_subiti` | Statistiche |
| funzioni di `Torneo` | Ricerca, aggiunta, accesso, distruzione |
| `registra(t, casa, ospite, gc, go)` | Registra per entrambe le squadre |
| `prima_in_classifica(a, b)`, `ordina_classifica(t)` | Classifica |

### Algoritmo in linguaggio naturale

1. Leggere le partite fino a `FINE` e registrarle.
2. Ordinare le squadre e stampare la classifica.
3. Stampare il cammino della prima.
4. Distruggere il torneo.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Cinque partite

- **Input:** `Leoni Tigri 2 1`, `Aquile Leoni 0 0`, `Tigri Aquile 3 1`,
  `Leoni Aquile 2 2`, `Tigri Leoni 1 0`, `Orsi Orsi 1 1`,
  `Orsi Leoni x`, `FINE`
- **Output atteso:**
  ```
  Partite: casa ospite gol gol (FINE per terminare)
    partita non valida (Orsi)
    partita non valida (Orsi)

      Squadra   G   V   N   P  GF  GS   DR  Pt
   1. Tigri     3   2   0   1   5   3   +2   6
   2. Leoni     4   1   2   1   4   4   +0   5
   3. Aquile    3   0   2   1   3   5   -2   2

  Il cammino di Tigri:
    P  1-2 con Leoni
    V  3-1 con Aquile
    V  1-0 con Leoni
  ```

### Test 2 – Nessuna partita

- **Input:** `FINE`
- **Output atteso:** `Nessuna partita registrata.`
