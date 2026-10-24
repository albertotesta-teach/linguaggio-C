# Analisi – 070-problema-posti-della-gita.c

## 1. Problema

Per la gita di fine anno si iscrivono gli studenti sui posti del pullman.
La capienza dipende dal pullman prenotato: si legge all'inizio e l'elenco
dei partecipanti (array di struct `Partecipante`) si alloca con `malloc`.
Il programma registra iscrizioni con acconto, versamenti e autorizzazioni
e indica chi non può ancora partire.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `capienza` | `int` | Posti del pullman, da 1 a 80 |
| `comando` | `char` | `I nome classe acconto`, `V posto euro`, `A posto`, `E` elenco, `R` riepilogo, `Q` fine (anche minuscoli) |

### Output

- `Elenco di N posti: B byte` (dimensione del blocco allocato).
- `I`: `nome al posto P`, `Pullman pieno: nome non iscritto.`,
  `Dati non validi.`
- `V`: `nome: versati E euro`, `Versamento non valido.`
- `A`: `Autorizzazione di nome consegnata.`, `Posto non valido.`
- `E`: per ogni posto quanto manca alla quota e lo stato
  dell'autorizzazione.
- `R`: posti occupati e liberi, chi non può partire, pronti e raccolto.
- `Numero di posti non valido.`, `Memoria insufficiente.`,
  `Comando sconosciuto.`

### Vincoli

- `posti = malloc(capienza * sizeof *posti)`, controllo di `NULL`, `free`
  a fine programma.
- Quota 85 euro: acconto da 0 a 85, versamenti positivi senza superare la
  quota; classe al massimo 3 caratteri.
- Può partire chi ha versato tutta la quota e consegnato l'autorizzazione
  (confronto con tolleranza di mezzo centesimo).
- Un comando per riga (il resto viene scartato). A fine input il
  programma termina come con `Q`.

### Assunzioni

- I posti si assegnano in ordine di iscrizione.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Partecipante` | `typedef struct { char nome[20]; char classe[4]; double versato; int autorizzazione; } Partecipante;` | Un posto del pullman |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `posti` | `Partecipante *` | Array allocato dinamicamente |
| `capienza`, `iscritti` | `int` | Dimensione e posti occupati |
| `posto`, `euro` | `int`, `double` | Argomenti dei comandi |
| `QUOTA` | `#define` | 85.0 euro |

| Funzione | Compito |
|----------|---------|
| `elenco(posti, iscritti)` | Stampa i partecipanti |
| `riepilogo(posti, iscritti, capienza)` | Posti, chi non può partire, raccolto |

### Algoritmo in linguaggio naturale

1. Leggere la capienza e allocare l'array.
2. Finché il comando non è `Q`: leggere il comando in maiuscolo;
   eseguire iscrizione, versamento, autorizzazione, elenco o riepilogo con
   i controlli; scartare il resto della riga.
3. Liberare la memoria.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Pullman da 3 posti

- **Input:** `3`, `I Rossi 4A 50`, `i Bianchi 4A 85`, `I Verdi 4B 90`,
  `I Neri QUARTA 10`, `I Verdi 4B 0`, `I Gialli 4C 20`, `V 1 35`, `V 2 1`,
  `v 9 10`, `A 2`, `a 1`, `A 7`, `E altro`, `R`, `X`, `Q`
- **Valori intermedi attesi:** `struct` di 40 byte × 3 = 120 byte; Rossi
  50 + 35 = 85; Bianchi già a 85 non può versare altro.
- **Output atteso:**
  ```
  Elenco di 3 posti: 120 byte
    Rossi al posto 1
    Bianchi al posto 2
    Dati non validi.
    Dati non validi.
    Verdi al posto 3
    Pullman pieno: Gialli non iscritto.
    Rossi: versati 85.00 euro
    Versamento non valido.
    Versamento non valido.
    Autorizzazione di Bianchi consegnata.
    Autorizzazione di Rossi consegnata.
    Posto non valido.
     1 Rossi        4A  manca   0.00  autorizzato
     2 Bianchi      4A  manca   0.00  autorizzato
     3 Verdi        4B  manca  85.00  senza autorizzazione
    Posti occupati 3 su 3, liberi 0
    non puo' ancora partire: Verdi
    Pronti a partire: 2, raccolti 170.00 euro su 255.00
    Comando sconosciuto.
  ```
  (i byte dipendono dalla dimensione della struct: 40 con gcc a 64 bit).

### Test 2 – Capienza non valida

- **Input:** `0`
- **Output atteso:** `Numero di posti non valido.`
