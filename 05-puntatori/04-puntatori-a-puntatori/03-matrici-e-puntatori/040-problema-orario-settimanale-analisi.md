# Analisi – 040-problema-orario-settimanale.c

## 1. Problema

L'orario settimanale della 3B è una matrice giorni × ore con il codice
della materia in ogni cella. Lo studente chiede un giorno e il programma
stampa le sei lezioni; alla fine stampa le ore settimanali di ogni materia.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `g` | `int` | Giorno scelto (1-5); 0 per finire |
| `orario` | `int[5][6]` | Codice della materia per giorno e ora (nel sorgente) |
| `materie`, `giorni` | `const char *[7]`, `const char *[5]` | Nomi (nel sorgente); l'indice di `materie` è il codice |

### Output

- Per ogni giorno valido: il nome del giorno e le sei ore con la materia.
- `Giorno non valido.` per un numero fuori da 0-5 o un testo.
- Alla fine le ore settimanali di ogni materia.

### Vincoli

- La riga `orario[g − 1]` si passa a `stampa_giorno` come un array
  (`const int *`).
- `ore_settimanali` riceve la matrice come puntatore a righe
  (`const int (*)[ORE]`) e la scorre riga per riga con `riga++`, leggendo
  le celle con `(*riga)[h]`.
- La riga si usa solo con un indice valido.
- Un testo non numerico è un giorno non valido (la riga si scarta); a fine
  input il programma termina come con 0.

### Assunzioni

- Giorni numerati da 1 (lunedì); sei ore al giorno.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `m` | `int` | Codice della materia nel riepilogo |
| `letti` | `int` | Valore restituito da `scanf` |
| `riga` | `const int (*)[ORE]` | In `ore_settimanali`: riga corrente |

| Funzione | Compito |
|----------|---------|
| `stampa_giorno(orario[g], ORE, materie)` | Stampa una riga ricevuta come `const int *` |
| `ore_settimanali(orario, GIORNI, m)` | Conta le celle della materia con un puntatore a riga |
| `svuota_riga` | Scarta i caratteri rimasti dopo un inserimento non valido |

### Algoritmo in linguaggio naturale

1. Finché il giorno non è 0: leggerlo (a fine input 0; testo → non valido);
   se fuori da 0-5 segnalarlo, altrimenti, se non è 0, stampare il nome del
   giorno e le sue ore.
2. Per ogni materia stampare le ore settimanali, contando con
   `ore_settimanali` le celle con quel codice.

## 3. Casi di test

Nell'output i giorni inseriti non compaiono (input da pipe).

### Test 1 – Sessione completa

- **Input:** `3`, `6`, `x`, `0`
- **Output atteso:**
  ```
    Mercoledi:
      1a ora  Informatica
      2a ora  Informatica
      3a ora  Informatica
      4a ora  Inglese
      5a ora  Ed. fisica
      6a ora  Ed. fisica
    Giorno non valido.
    Giorno non valido.

  Ore settimanali per materia:
    Italiano     6
    Matematica   5
    Informatica  7
    Inglese      3
    Sistemi      4
    Ed. fisica   2
    Storia       3
  ```
  (il totale delle ore è 30 = 5 × 6).
