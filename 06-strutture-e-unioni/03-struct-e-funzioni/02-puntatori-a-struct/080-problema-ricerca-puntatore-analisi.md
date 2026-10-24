# Analisi – 080-problema-ricerca-puntatore.c

## 1. Problema

Il tecnico del laboratorio cerca un computer per numero di inventario e
registra guasti, riparazioni e aggiornamenti della RAM. `cerca`
restituisce l'indirizzo della struct `Computer` trovata nell'array, o
`NULL`: il chiamante modifica direttamente l'elemento con `->`.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `comando` | `char` | `G codice` guasto, `R codice` riparazione, `U codice n` RAM, `S` stato, `Q` fine (anche minuscoli) |
| `codice` | `char[8]` | Numero di inventario |
| `ram` | `int` | Nuova RAM in GB |
| `laboratorio` | `Computer[5]` | PC-011 (8 GB), PC-012 (8 GB, 1 guasto), PC-014 (4 GB, 2 guasti), PC-015 (16 GB), PC-019 (8 GB), tutti funzionanti |

### Output

- `Guasto registrato sulla postazione N.`, `X di nuovo funzionante.`,
  `X ora ha N GB.`, `La RAM si puo' solo aumentare (ora N GB).`,
  `X non e' nell'inventario.`, `Comando sconosciuto.`
- Con `S`: una riga per computer con postazione, inventario, RAM, guasti e
  `ok` / `FUORI SERVIZIO`.

### Vincoli

- `cerca` restituisce `&elenco[i]` oppure `NULL`; il chiamante controlla
  `NULL` prima di usare il puntatore.
- Un guasto aumenta il contatore e mette il computer fuori servizio; una
  riparazione lo rimette in servizio.
- La RAM si può solo aumentare; un valore non numerico è trattato come
  non valido.
- Un comando per riga (il resto viene scartato). A fine input il
  programma termina come con `Q`.

### Assunzioni

- I numeri di inventario sono unici.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Computer` | `typedef struct { char inventario[8]; int postazione; int ram_gb; int guasti; int funzionante; } Computer;` | Un computer del laboratorio |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `laboratorio` | `Computer[5]` | Array di struct |
| `pc` | `Computer *` | Elemento trovato da `cerca` |
| `comando` | `char` | Comando in maiuscolo |

| Funzione | Compito |
|----------|---------|
| `cerca(elenco, n, inventario)` | Indirizzo dell'elemento con quel codice, `NULL` se assente |
| `stampa(c)` | Stampa un computer |
| `svuota_riga` | Scarta i caratteri rimasti sulla riga |

### Algoritmo in linguaggio naturale

1. Finché il comando non è `Q`:
   1. leggere il comando (fine input → `Q`) in maiuscolo;
   2. `G`/`R`/`U`: leggere il codice e cercarlo; se `NULL` segnalarlo;
      altrimenti con `G` aumentare i guasti e mettere fuori servizio, con
      `R` rimettere in servizio, con `U` leggere la RAM e aggiornarla solo
      se maggiore;
   3. `S`: stampare tutti i computer;
   4. altro diverso da `Q`: comando sconosciuto;
   5. scartare il resto della riga.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Sessione completa

- **Cosa si verifica:** modifica dell'elemento tramite il puntatore,
  ricerca fallita, RAM non aumentabile o non numerica.
- **Input:** `S`, `G PC-014`, `g PC-014`, `R PC-012`, `U PC-014 8`,
  `U PC-011 4`, `U PC-015 abc`, `R PC-099`, `X`, `S`, `Q`
- **Output atteso:**
  ```
    postazione 1  PC-011   8 GB  guasti 0  ok
    postazione 2  PC-012   8 GB  guasti 1  ok
    postazione 3  PC-014   4 GB  guasti 2  ok
    postazione 4  PC-015  16 GB  guasti 0  ok
    postazione 5  PC-019   8 GB  guasti 0  ok
    Guasto registrato sulla postazione 3.
    Guasto registrato sulla postazione 3.
    PC-012 di nuovo funzionante.
    PC-014 ora ha 8 GB.
    La RAM si puo' solo aumentare (ora 8 GB).
    La RAM si puo' solo aumentare (ora 16 GB).
    PC-099 non e' nell'inventario.
    Comando sconosciuto.
    postazione 1  PC-011   8 GB  guasti 0  ok
    postazione 2  PC-012   8 GB  guasti 1  ok
    postazione 3  PC-014   8 GB  guasti 4  FUORI SERVIZIO
    postazione 4  PC-015  16 GB  guasti 0  ok
    postazione 5  PC-019   8 GB  guasti 0  ok
  ```
