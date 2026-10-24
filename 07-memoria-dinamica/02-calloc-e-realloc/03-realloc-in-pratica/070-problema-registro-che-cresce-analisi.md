# Analisi – 070-problema-registro-che-cresce.c

## 1. Problema

Durante l'anno arrivano studenti nuovi e altri si trasferiscono. Il
registro ha due blocchi che partono da `NULL`: i nomi e il tabellone dei
voti (una riga di tre voti per studente). Aggiungere uno studente
significa aggiungere una riga in fondo con `realloc`; toglierlo significa
far salire le righe successive e ridurre i blocchi, liberandoli quando
restano vuoti.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `comando` | `char` | `A nome voto voto voto` ingresso, `T nome` uscita, `S` stampa, `Q` fine (anche minuscoli) |

### Output

- `ingresso di nome: righe R, B byte di voti`,
  `nome e' gia' nel registro.`, `Dati non validi.`
- `uscita di nome: righe R`, `nome non e' nel registro.`,
  `Nome mancante.`
- `S`: il tabellone con le medie oppure `registro vuoto`.
- `Memoria insufficiente.`, `Comando sconosciuto.`

### Vincoli

- `aggiungi`: `realloc` dei nomi e poi dei voti, ciascuna in un
  temporaneo; `realloc(NULL, ...)` equivale a `malloc`.
- `togli`: spostamento delle righe successive di un posto, poi riduzione
  con `realloc`; con 0 studenti i blocchi si liberano con `free` e i
  puntatori tornano `NULL` (mai `realloc(p, 0)`).
- Se una riduzione fallisce il blocco resta più grande ma i dati sono
  corretti.
- Un comando per riga. A fine input il programma termina come con `Q`.

### Assunzioni

- I voti inseriti sono validi; i nomi sono una sola parola.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Nome` | `typedef struct { char testo[20]; } Nome;` | Un nome (struct per poterlo assegnare) |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `nomi`, `voti` | `Nome *`, `double *` | I due blocchi |
| `studenti` | `int` | Righe del registro |
| `v` | `double[3]` | Voti letti |

| Funzione | Compito |
|----------|---------|
| `aggiungi(&nomi, &voti, studenti, nome, v)` | Una riga in più; 0 se manca memoria |
| `togli(&nomi, &voti, studenti, posizione)` | Toglie una riga e restituisce il nuovo numero |
| `cerca(nomi, studenti, nome)` | Posizione, −1 se assente |
| `stampa(nomi, voti, studenti)` | Tabellone con medie |

### Algoritmo in linguaggio naturale

1. Finché il comando non è `Q`: leggere il comando in maiuscolo; con `A`
   controllare e aggiungere; con `T` cercare e togliere; con `S`
   stampare; scartare il resto della riga.
2. Liberare i blocchi (`free(NULL)` è ammesso).

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Ingressi e uscite

- **Input:** `S`, `A Rossi 7 8 6`, `a Bianchi 5 6 7`, `A Rossi 6 6 6`,
  `A Verdi 8 x`, `A Verdi 8 9 10`, `S extra`, `T Bianchi`, `T Neri`, `S`,
  `T Rossi`, `T Verdi`, `S`, `X`, `Q`
- **Valori intermedi attesi:** 3 voti × 8 byte = 24 byte per riga.
- **Output atteso:**
  ```
    registro vuoto
    ingresso di Rossi: righe 1, 24 byte di voti
    ingresso di Bianchi: righe 2, 48 byte di voti
    Rossi e' gia' nel registro.
    Dati non validi.
    ingresso di Verdi: righe 3, 72 byte di voti
                ITA  MAT  ING  media
    Rossi       7.0  8.0  6.0   7.00
    Bianchi     5.0  6.0  7.0   6.00
    Verdi       8.0  9.0 10.0   9.00
    uscita di Bianchi: righe 2
    Neri non e' nel registro.
                ITA  MAT  ING  media
    Rossi       7.0  8.0  6.0   7.00
    Verdi       8.0  9.0 10.0   9.00
    uscita di Rossi: righe 1
    uscita di Verdi: righe 0
    registro vuoto
    Comando sconosciuto.
  ```
