# Analisi – 040-problema-calcolatrice.c

## 1. Problema

Per il laboratorio di fisica serve una calcolatrice che legge espressioni
`numero operatore numero` e stampa il risultato, con gli operatori
`+ - * / ^`. Gli operatori sconosciuti, la divisione per zero e gli
esponenti negativi vanno segnalati. Un input non numerico termina.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `a`, `simbolo`, `b` | `double`, `char`, `double` | Espressione `numero operatore numero`; un testo non numerico (es. `q`) termina |

### Output

- `a op b = risultato` (formato `%g`).
- `Operatore 'x' sconosciuto.`, `Divisione per zero.` oppure
  `Esponente negativo non ammesso.`

### Vincoli

- Le cinque operazioni hanno lo stesso prototipo `double (double, double)`,
  quindi i loro indirizzi si possono assegnare allo stesso puntatore a
  funzione `operazione`.
- `scegli_operazione` restituisce il puntatore alla funzione dell'operatore
  oppure `NULL`; un puntatore a funzione `NULL` non si chiama mai.
- Divisione per zero ed esponente negativo si controllano prima della
  chiamata, confrontando il puntatore con `dividi` e `potenza`.
- La potenza usa la parte intera dell'esponente.

### Assunzioni

- Gli spazi intorno all'operatore sono facoltativi.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `operazione` | `double (*)(double, double)` | Funzione scelta, `NULL` se l'operatore non esiste |
| `scelta` | `double (*)(double, double)` | In `scegli_operazione`: risultato |

| Funzione | Compito |
|----------|---------|
| `scegli_operazione(simbolo)` | Restituisce il puntatore alla funzione dell'operatore, `NULL` se non previsto |
| `somma`, `sottrai`, `moltiplica`, `dividi`, `potenza` | Le cinque operazioni, stesso prototipo |

### Algoritmo in linguaggio naturale

1. Finché si legge un'espressione completa:
   1. scegliere la funzione dell'operatore;
   2. se è `NULL` segnalare l'operatore sconosciuto;
   3. altrimenti, se è una divisione per zero o una potenza con esponente
      negativo segnalarlo;
   4. altrimenti chiamare `operazione(a, b)` e stampare il risultato.
2. Alla prima riga che non è un'espressione terminare.

## 3. Casi di test

Nell'output le espressioni inserite non compaiono (input da pipe).

### Test 1 – Sessione completa

- **Input:** `12.5 * 4`, `2 ^ 10`, `5 % 2`, `8 / 0`, `7 - 10.5`, `2 ^ -1`,
  `2 ^ 2.9`, `1 / 3`, `q`
- **Output atteso:**
  ```
  >   12.5 * 4 = 50
  >   2 ^ 10 = 1024
  >   Operatore '%' sconosciuto.
  >   Divisione per zero.
  >   7 - 10.5 = -3.5
  >   Esponente negativo non ammesso.
  >   2 ^ 2.9 = 4
  >   1 / 3 = 0.333333
  > 
  ```
  (`2 ^ 2.9` usa la parte intera dell'esponente: 2² = 4).
