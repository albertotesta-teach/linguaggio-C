# Analisi – 040-problema-impostazioni.c

## 1. Problema

Il server del registro di classe legge un file di impostazioni
`chiave=valore`. Una tabella dice il tipo previsto di ogni chiave; il
valore si converte secondo il tipo in una `union` anonima dentro la
struct `Impostazione`. Righe vuote e commenti si ignorano; chiavi
sconosciute e valori non validi si segnalano con il numero di riga.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `riga` | `char[64]` | Una riga del file; `FINE` termina |

Chiavi e valori predefiniti: `porta` intero (80), `timeout` reale (1.0),
`registro` si/no (no), `server` testo ("localhost").

### Output

- Per le righe errate: `riga N: manca '='`,
  `riga N: chiave sconosciuta "x"`, `riga N: valore non valido per x`.
- `Configurazione:` con il valore finale di ogni chiave.

### Vincoli

- Porta intera da 1 a 65535; timeout reale positivo; registro `si` o
  `no`; server non vuoto, al massimo 23 caratteri.
- Il valore deve essere completo: `8080x` non è un intero (`%d %c` deve
  leggere un solo valore).
- Una riga che inizia con `#` è un commento; le righe vuote si ignorano ma
  si contano.
- Un valore non valido lascia quello precedente.
- Una riga più lunga del buffer viene troncata e il resto scartato. A fine
  input il programma termina come con `FINE`.
- La union anonima (C11) permette di scrivere `imp->intero` senza un nome
  intermedio.

### Assunzioni

- Nessuno spazio intorno a `=`.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `TipoValore` | `typedef enum { INTERO, REALE, SI_NO, TESTO } TipoValore;` | Tipo previsto della chiave |
| `Impostazione` | struct con `chiave`, `tipo` e `union { int intero; double reale; int si_no; char testo[24]; }` anonima | Una impostazione |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `config` | `Impostazione[4]` | Tabella delle chiavi |
| `uguale` | `char *` | Posizione di `=` nella riga |
| `numero_riga` | `int` | Per i messaggi |
| `trovata` | `int` | Chiave trovata (−1 = sconosciuta) |
| `resto` | `int` | Caratteri scartati di una riga lunga |

| Funzione | Compito |
|----------|---------|
| `leggi_valore(imp, testo)` | Converte secondo il tipo; 0 se non valido |
| `stampa(imp)` | Stampa con `switch` sul tipo |

### Algoritmo in linguaggio naturale

1. Finché non si termina: leggere una riga, scartare il resto se troppo
   lunga, contarla; con `FINE` terminare; ignorare vuote e commenti;
   cercare `=`, separare la chiave, cercarla nella tabella e convertire il
   valore, segnalando gli errori.
2. Stampare la configurazione.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – File con errori

- **Input:** `# configurazione`, `porta=8080`, riga vuota, `timeout=2.5`,
  `registro=si`, `server=registro.scuola.it`, `porta=70000`,
  `timeout=abc`, `registro=forse`, `colore=blu`, `senza uguale`,
  `server=`, `server=` seguito da 60 zeri, `FINE`
- **Output atteso:**
  ```
  File delle impostazioni (FINE per terminare):
    riga 7: valore non valido per porta
    riga 8: valore non valido per timeout
    riga 9: valore non valido per registro
    riga 10: chiave sconosciuta "colore"
    riga 11: manca '='
    riga 12: valore non valido per server
    riga 13: valore non valido per server

  Configurazione:
    porta     = 8080
    timeout   = 2.5 s
    registro  = si
    server    = "registro.scuola.it"
  ```

### Test 2 – File vuoto

- **Input:** `FINE`
- **Output atteso:** i valori predefiniti: `porta = 80`,
  `timeout = 1.0 s`, `registro = no`, `server = "localhost"`.
