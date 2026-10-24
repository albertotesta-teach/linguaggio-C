# Analisi – 060-problema-taglie-magazzino.c

## 1. Problema

Il comitato studentesco vende le magliette della scuola. Le taglie sono un
`enum`, le scorte un array indicizzato dalla taglia. La sigla scritta
dall'utente si cerca nella tabella delle sigle: la sua posizione è la
costante dell'enum, e `NUM_TAGLIE` indica una sigla inesistente.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `comando` | `char` | `V taglia n` vendita, `C taglia n` carico, `S` scorte, `Q` fine (anche minuscoli) |
| `sigla` | `char[8]` | `XS`, `S`, `M`, `L`, `XL`, `XXL` |
| `quantita` | `int` | Numero di magliette, positivo |
| scorte iniziali | nel sorgente | XS 4, S 12, M 20, L 15, XL 6, XXL 0 |

### Output

- `Vendita registrata: taglia T, ne restano N.`, `Taglia T esaurita.`,
  `Taglia T: ne restano solo N.`, `Taglia T: N magliette.` (carico),
  `Taglia X inesistente.`, `Quantita' non valida.`, `Dati non validi.`
- `S`: una riga per taglia con `ESAURITA` (0) o `da riordinare` (meno di
  5).
- `Comando sconosciuto.`

### Vincoli

- La ricerca della sigla scorre l'enum da `XS` a `NUM_TAGLIE`.
- La sigla si confronta con `strcmp`: va scritta in maiuscolo.
- Non si vende più di quanto disponibile.
- Un comando per riga (il resto viene scartato); i dati non validi non
  interrompono il programma. A fine input termina come con `Q`.

### Assunzioni

- Nessuna.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Taglia` | `typedef enum { XS, S, M, L, XL, XXL, NUM_TAGLIE } Taglia;` | Taglia della maglietta |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `sigle` | `const char *[6]` | Sigle indicizzate dalla taglia |
| `scorte` | `int[6]` | Magliette per taglia |
| `t` | `Taglia` | Taglia trovata (`NUM_TAGLIE` = inesistente) |
| `SOGLIA_RIORDINO` | `#define` | 5 |

| Funzione | Compito |
|----------|---------|
| `svuota_riga` | Scarta i caratteri rimasti sulla riga |

### Algoritmo in linguaggio naturale

1. Finché il comando non è `Q`:
   1. leggere il comando in maiuscolo;
   2. `V`/`C`: leggere sigla e quantità, cercare la taglia, controllare,
      aggiornare le scorte;
   3. `S`: stampare le scorte con le note;
   4. scartare il resto della riga.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Vendite e carichi

- **Input:** `S`, `V M 3`, `v XS 4`, `V XXL 1`, `V L 20`, `C XXL 10`,
  `V XXXL 2`, `V S 0`, `V S x`, `X`, `S`, `Q`
- **Output atteso:**
  ```
    XS    4  da riordinare
    S    12
    M    20
    L    15
    XL    6
    XXL   0  ESAURITA
    Vendita registrata: taglia M, ne restano 17.
    Vendita registrata: taglia XS, ne restano 0.
    Taglia XXL esaurita.
    Taglia L: ne restano solo 15.
    Taglia XXL: 10 magliette.
    Taglia XXXL inesistente.
    Quantita' non valida.
    Dati non validi.
    Comando sconosciuto.
    XS    0  ESAURITA
    S    12
    M    17
    L    15
    XL    6
    XXL  10
  ```
