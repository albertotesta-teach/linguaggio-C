# Analisi – 050-problema-classifica-per-puntatori.c

## 1. Problema

Alla gara di orientamento la classifica provvisoria va corretta scambiando
due concorrenti alla volta. Nomi e tempi restano nei loro array: la
classifica è fatta di due array di puntatori paralleli, e ogni scambio
scambia solo i puntatori. Dopo ogni scambio il programma controlla se i
tempi sono in ordine.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `comando` | `char` | `S a b` scambia le posizioni `a` e `b` (da 1 a 5); `Q` fine |
| `nomi`, `tempi` | `const char *[5]`, `int[5]` | Pietro 1830, Alice 1795, Irene 1912, Tommaso 1801, Nadia 1880 secondi (nel sorgente) |

### Output

- La classifica (posizione, nome, tempo `mm:ss`) all'inizio e dopo ogni
  scambio, con `Classifica in ordine di tempo.` oppure
  `Attenzione: tempi non in ordine.`
- `Posizioni non valide.` oppure `Comando sconosciuto.`

### Vincoli

- `nome_al_posto[i]` punta al nome e `tempo_al_posto[i]` al tempo del
  concorrente in posizione `i`: nomi e tempi originali non si spostano.
- Le funzioni di scambio ricevono gli indirizzi di due elementi degli array
  di puntatori (`const char **`, `const int **`) e scambiano i puntatori;
  nome e tempo si scambiano sempre insieme.
- Il tempo si legge attraverso il puntatore: `*tempo_al_posto[i]`.
- La classifica è in ordine se ogni tempo è minore o uguale al successivo.
- Posizioni fuori da 1-5 o non numeriche sono rifiutate (la riga si scarta)
  e il programma continua; a fine input si comporta come `Q`.

### Assunzioni

- Posizioni numerate da 1; i comandi sono maiuscoli.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `nome_al_posto` | `const char *[5]` | Nome alla posizione `i` della classifica |
| `tempo_al_posto` | `const int *[5]` | Tempo alla posizione `i`, puntatore dentro `tempi` |
| `a`, `b`, `letti` | `int` | Posizioni lette, valore restituito da `scanf` |

| Funzione | Compito |
|----------|---------|
| `scambia_nomi(&a, &b)`, `scambia_tempi(&a, &b)` | Scambiano due puntatori (parametri `**`) |
| `stampa(nomi, tempi, n)` | Classifica con controllo dell'ordine |
| `in_ordine(tempi, n)` | 1 se i tempi sono crescenti |
| `svuota_riga` | Scarta i caratteri rimasti dopo un inserimento non valido |

### Algoritmo in linguaggio naturale

1. Far puntare gli elementi dei due array di puntatori a nomi e tempi
   nell'ordine di iscrizione; stampare la classifica.
2. Finché il comando non è `Q`:
   1. leggere il comando (a fine input `Q`);
   2. `S`: leggere le due posizioni; se non valide segnalarlo, altrimenti
      scambiare i nomi e i tempi alle due posizioni e stampare la
      classifica;
   3. ogni altro comando è sconosciuto.

## 3. Casi di test

Nell'output i comandi inseriti non compaiono (input da pipe).

### Test 1 – Classifica iniziale

- **Input:** `Q`
- **Output atteso:**
  ```
    1. Pietro   30:30
    2. Alice    29:55
    3. Irene    31:52
    4. Tommaso  30:01
    5. Nadia    31:20
    Attenzione: tempi non in ordine.
  ```

### Test 2 – Scambi fino all'ordine corretto

- **Input:** `S 1 2`, `S 2 4`, `S 3 4`, `S 4 5`, `Q`
- **Output atteso** (ultima classifica):
  ```
    1. Alice    29:55
    2. Tommaso  30:01
    3. Pietro   30:30
    4. Nadia    31:20
    5. Irene    31:52
    Classifica in ordine di tempo.
  ```

### Test 3 – Comandi non validi

- **Input:** `S 0 9`, `S x`, `X`, `Q`
- **Output atteso:**
  ```
    Posizioni non valide.
    Posizioni non valide.
    Comando sconosciuto.
  ```
