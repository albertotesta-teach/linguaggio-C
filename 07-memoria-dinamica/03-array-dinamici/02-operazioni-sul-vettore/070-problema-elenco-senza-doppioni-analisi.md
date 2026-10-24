# Analisi – 070-problema-elenco-senza-doppioni.c

## 1. Problema

Gli studenti si offrono volontari per l'open day; qualcuno si iscrive due
volte, qualcuno si ritira. L'elenco è un vettore dinamico di `Nome` con
due operazioni in più: `aggiungi_se_manca` e `rimuovi_valore`. I nomi si
normalizzano (iniziale maiuscola, resto minuscolo) così `rossi` e `ROSSI`
sono la stessa persona.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `comando` | `char` | `I nome` iscrivi, `R nome` ritira, `E` elenco, `Q` fine (anche minuscoli) |

### Output

- `iscrizione di Nome (volontari: N)`, `Nome e' gia' nell'elenco`.
- `ritiro di Nome (volontari: N)`, `Nome non e' nell'elenco`.
- `E`: i volontari numerati.
- `Nome mancante.`, `Memoria insufficiente.`, `Comando sconosciuto.`

### Vincoli

- Vettore `{Nome *dati; int n; int capacita;}` con capacità iniziale 2 e
  raddoppio; il `main` usa solo le funzioni del vettore.
- `aggiungi_se_manca`: 1 aggiunto, 0 già presente, −1 memoria
  insufficiente.
- `rimuovi_valore` cerca il nome e sposta indietro i successivi (l'ordine
  di iscrizione resta).
- I nomi si normalizzano prima di ogni ricerca.
- Un comando per riga. A fine input il programma termina come con `Q`.

### Assunzioni

- Il nome è una sola parola.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Nome` | `typedef struct { char testo[20]; } Nome;` | Un nome |
| `Elenco` | `typedef struct { Nome *dati; int n; int capacita; } Elenco;` | Vettore dinamico |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `volontari` | `Elenco *` | Il vettore |
| `esito` | `int` | Risultato di `aggiungi_se_manca` |

| Funzione | Compito |
|----------|---------|
| `crea_elenco`, `distruggi_elenco` | Allocazione e liberazione |
| `aggiungi_se_manca(e, nome)` | Aggiunge solo se assente |
| `rimuovi_valore(e, nome)` | Toglie il nome; 0 se assente |
| `cerca`, `lunghezza`, `elemento` | Accesso |
| `sistema(nome)` | Iniziale maiuscola, resto minuscolo |

### Algoritmo in linguaggio naturale

1. Finché il comando non è `Q`: leggere il comando in maiuscolo; con
   `I`/`R` leggere e normalizzare il nome, poi aggiungerlo o toglierlo;
   con `E` stampare; scartare il resto della riga.
2. Distruggere l'elenco.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Iscrizioni e ritiri

- **Input:** `I rossi`, `i ROSSI`, `I Bianchi`, `I verdi`, `R bianchi`,
  `R Neri`, `E extra`, `X`, `Q`
- **Valori intermedi attesi:** la terza iscrizione fa raddoppiare la
  capacità da 2 a 4.
- **Output atteso:**
  ```
    iscrizione di Rossi (volontari: 1)
    Rossi e' gia' nell'elenco
    iscrizione di Bianchi (volontari: 2)
    iscrizione di Verdi (volontari: 3)
    ritiro di Bianchi (volontari: 2)
    Neri non e' nell'elenco
    1. Rossi
    2. Verdi
    Comando sconosciuto.
  ```
