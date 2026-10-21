# Analisi – 070-problema-scambio-righe.c

## 1. Problema

Nel torneo di calcetto d'istituto ogni squadra ha una riga con vittorie,
pareggi e sconfitte. Dopo ogni partita inserita si aggiorna la riga e la
squadra sale in classifica finché ha più punti di chi la precede. La
classifica è un array di puntatori alle righe.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `squadra`, `esito` | `int`, `char` | Numero della squadra (1-5) ed esito `V`/`P`/`S`; 0 per finire |
| `risultati` | `int[5][3]` | V, P, S iniziali (nel sorgente): Fulmini 3 1 0, Tigri 2 2 0, Squali 2 0 2, Aquile 1 2 1, Lupi 0 1 3 |

### Output

- La classifica (posizione, squadra, V P S, punti) all'inizio e dopo ogni
  partita valida.
- `Dati non validi.` per squadra fuori da 1-5, esito diverso da V/P/S o
  testo non numerico.

### Vincoli

- `classifica[k]` punta alla riga della squadra in posizione `k`: per far
  salire una squadra si scambiano i puntatori, le righe della matrice
  restano ferme.
- Punti = 3 × vittorie + pareggi.
- La squadra sale finché ha più punti di chi la precede: a parità di punti
  non sorpassa.
- Il nome si ricava dal puntatore alla riga: le righe sono consecutive in
  memoria, quindi `(classifica[k] − &risultati[0][0]) / 3` è il numero
  della riga.
- I dati non validi si scartano (resto della riga) e il programma continua;
  a fine input termina come con 0.

### Assunzioni

- 3 colonne per riga; l'esito è in maiuscolo.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `classifica` | `int *[5]` | Puntatori alle righe in ordine di classifica |
| `nomi` | `const char *[5]` | Nomi delle squadre |
| `temp` | `int *` | Appoggio per lo scambio dei puntatori |
| `k` | `int` | Posizione della squadra in classifica |
| `letti` | `int` | Valore restituito da `scanf` |

| Funzione | Compito |
|----------|---------|
| `punti(riga)` | 3 × vittorie + pareggi |
| `stampa(classifica, inizio, nomi)` | Classifica; il nome si ricava dal puntatore alla riga |
| `svuota_riga` | Scarta i caratteri rimasti dopo un inserimento non valido |

### Algoritmo in linguaggio naturale

1. Far puntare `classifica[k]` alla riga `k`; stampare la classifica.
2. Finché la squadra non è 0:
   1. leggere squadra ed esito (a fine input 0; testo → non valido);
   2. se validi: incrementare la colonna dell'esito nella riga della
      squadra; trovare la posizione `k` della squadra in classifica; finché
      `k > 0` e i suoi punti superano quelli di `classifica[k − 1]`
      scambiare i due puntatori e decrementare `k`; stampare la classifica;
   3. altrimenti, se la squadra non è 0, scartare la riga e segnalare i
      dati non validi.

## 3. Casi di test

Nell'output le partite inserite non compaiono (input da pipe).

### Test 1 – Sorpassi

- **Cosa si verifica:** a parità non si sorpassa; con più punti si sale di
  più posizioni.
- **Input:** `4 V`, `4 V`, `3 P`, `0`
- **Valori intermedi attesi:** dopo la prima vittoria le Aquile hanno 8
  punti come le Tigri e restano dietro; dopo la seconda (11 punti) salgono
  in testa.
- **Output atteso** (classifiche dopo ogni partita):
  ```
    Pos Squadra   V P S  Punti
     1. Fulmini   3 1 0   10
     2. Tigri     2 2 0    8
     3. Aquile    2 2 1    8
     4. Squali    2 0 2    6
     5. Lupi      0 1 3    1
    Pos Squadra   V P S  Punti
     1. Aquile    3 2 1   11
     2. Fulmini   3 1 0   10
     3. Tigri     2 2 0    8
     4. Squali    2 0 2    6
     5. Lupi      0 1 3    1
    Pos Squadra   V P S  Punti
     1. Aquile    3 2 1   11
     2. Fulmini   3 1 0   10
     3. Tigri     2 2 0    8
     4. Squali    2 1 2    7
     5. Lupi      0 1 3    1
  ```

### Test 2 – Dati non validi e fine dell'input

- **Input:** `9 V`, `2 X`, `abc`, `5 S`, poi fine dell'input
- **Output atteso:** tre volte `  Dati non validi.`, poi la classifica con i
  Lupi a `0 1 4`; il programma termina.
