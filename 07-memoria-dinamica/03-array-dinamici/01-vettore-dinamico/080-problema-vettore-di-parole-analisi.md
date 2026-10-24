# Analisi – 080-problema-vettore-di-parole.c

## 1. Problema

La classe raccoglie i termini del glossario di informatica, di lunghezza
molto diversa e in numero non noto. Il glossario è un vettore dinamico di
`char *`: ogni termine sta in un blocco di `strlen + 1` byte. Il programma
legge i termini fino a `FINE` senza doppioni, li ordina scambiando i
puntatori e stampa il glossario con la memoria usata, confrontata con una
matrice di `char`.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| termini | parole | Al massimo 39 caratteri ciascuno; `FINE` termina |

### Output

- `X gia' presente` per ogni doppione.
- `Glossario (N termini):` con i termini in ordine alfabetico.
- `Memoria: T byte di testi + P byte di puntatori` e il confronto con
  `char[N][40]`.
- `Memoria insufficiente.`

### Vincoli

- Vettore `{char **dati; int n; int capacita;}` con capacità iniziale 2 e
  raddoppio; il `main` usa solo le funzioni del glossario.
- `aggiungi` alloca prima la copia; se poi il raddoppio fallisce libera la
  copia, così il glossario resta com'era.
- L'ordinamento (selezione) scambia i puntatori, non i testi.
- Liberazione: ogni termine, poi l'array dei puntatori, poi la struct.
- Byte dei puntatori: capacità × `sizeof(char *)` (8 byte su un sistema a
  64 bit).
- A fine input il programma termina come con `FINE`.

### Assunzioni

- I termini si confrontano con `strcmp` (maiuscole prima delle
  minuscole).

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Glossario` | `typedef struct { char **dati; int n; int capacita; } Glossario;` | Vettore dinamico di stringhe |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `glossario` | `Glossario *` | Il glossario |
| `parola` | `char[40]` | Termine letto |
| `byte_testi` | `size_t` | Somma dei blocchi dei termini |

| Funzione | Compito |
|----------|---------|
| `crea_glossario`, `distruggi_glossario` | Allocazione e liberazione |
| `aggiungi`, `lunghezza`, `capacita`, `termine` | Uso del vettore |
| `cerca(g, parola)` | Posizione del termine, −1 se assente |
| `ordina(g)` | Ordinamento per selezione dei puntatori |

### Algoritmo in linguaggio naturale

1. Leggere i termini fino a `FINE`, segnalando i doppioni e aggiungendo
   gli altri.
2. Ordinare e stampare, sommando i byte dei testi.
3. Stampare il confronto della memoria e distruggere il glossario.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Otto termini

- **Input:** `variabile puntatore array funzione puntatore`,
  `struct compilatore algoritmo ciclo array`, `FINE`
- **Valori intermedi attesi:** testi 10 + 10 + 6 + 9 + 7 + 12 + 10 + 6 =
  70 byte; capacità 2 → 4 → 8: 8 puntatori = 64 byte.
- **Output atteso:**
  ```
  Termini (FINE per terminare):
    puntatore gia' presente
    array gia' presente

  Glossario (8 termini):
    algoritmo
    array
    ciclo
    compilatore
    funzione
    puntatore
    struct
    variabile
  Memoria: 70 byte di testi + 64 byte di puntatori
  Con una matrice char[8][40]: 320 byte
  ```
