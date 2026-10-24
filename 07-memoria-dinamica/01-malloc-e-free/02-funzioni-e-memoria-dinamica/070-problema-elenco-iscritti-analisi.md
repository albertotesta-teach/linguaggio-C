# Analisi – 070-problema-elenco-iscritti.c

## 1. Problema

La scuola organizza i corsi pomeridiani di robotica e di teatro, con un
numero di posti deciso all'avvio. Ogni corso è un `Elenco` con un
puntatore a un array di `Iscritto` allocato da `crea_elenco` e liberato da
`distruggi_elenco`; le funzioni `iscrivi`, `ritira` e `stampa` non toccano
mai `malloc` e `free`.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `posti[0]`, `posti[1]` | `int` | Posti di robotica e di teatro, da 1 a 30 |
| `comando` | `char` | `I corso nome classe`, `R corso nome`, `E` elenchi, `Q` fine (anche minuscoli) |

### Output

- `Iscrizione di nome a corso (n/capienza)`, `Il corso di X e' pieno.`,
  `nome e' gia' tra gli iscritti a X.`
- `Ritiro di nome da X.`, `nome non e' tra gli iscritti a X.`
- `E`: per ogni corso gli iscritti numerati.
- `Corso sconosciuto: X`, `Dati non validi.`, `Comando sconosciuto.`,
  `Numero di posti non valido (da 1 a 30).`, `Memoria insufficiente.`

### Vincoli

- `crea_elenco` fa due allocazioni (la struct e l'array); se la seconda
  fallisce libera la prima e restituisce `NULL`. `distruggi_elenco` libera
  nell'ordine inverso e accetta `NULL`.
- Un ritiro sposta indietro gli iscritti successivi (l'ordine resta).
- Iscrizione: prima il controllo del doppione, poi quello dei posti.
- Classe al massimo 3 caratteri.
- Un comando per riga. A fine input il programma termina come con `Q`.

### Assunzioni

- Il nome dello studente è una sola parola.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Iscritto` | `typedef struct { char nome[20]; char classe[4]; } Iscritto;` | Uno studente |
| `Elenco` | `typedef struct { char corso[16]; int capienza; int n; Iscritto *iscritti; } Elenco;` | Un corso con l'array dinamico |
| `Esito` | `typedef enum { ISCRITTO, CORSO_PIENO, GIA_ISCRITTO } Esito;` | Risultato di `iscrivi` |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `corsi` | `Elenco *[2]` | I due corsi |
| `pronti` | `int` | Entrambe le allocazioni riuscite |
| `e` | `Elenco *` | Corso indicato nel comando |

| Funzione | Compito |
|----------|---------|
| `crea_elenco`, `distruggi_elenco` | Allocazione e liberazione |
| `cerca`, `iscrivi`, `ritira`, `stampa` | Operazioni sull'elenco |
| `trova_corso(corsi, corso)` | Elenco con quel nome, o `NULL` |

### Algoritmo in linguaggio naturale

1. Leggere i posti; se validi creare i due elenchi, altrimenti
   segnalarlo.
2. Finché il comando non è `Q`: leggere il comando in maiuscolo; eseguire
   iscrizione, ritiro o stampa; scartare il resto della riga.
3. Distruggere i due elenchi.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Iscrizioni e ritiri

- **Input:** `2 3`, `I robotica Rossi 3A`, `i robotica Bianchi 2B`,
  `I robotica Verdi 1C`, `I robotica Rossi 3A`, `I teatro Rossi 3A`,
  `I danza Neri 1A`, `I teatro Gialli QUARTA`, `R robotica Bianchi`,
  `r teatro Bianchi`, `I robotica Verdi 1C`, `E extra`, `X`, `Q`
- **Output atteso:**
  ```
    Iscrizione di Rossi a robotica (1/2)
    Iscrizione di Bianchi a robotica (2/2)
    Il corso di robotica e' pieno.
    Rossi e' gia' tra gli iscritti a robotica.
    Iscrizione di Rossi a teatro (1/3)
    Corso sconosciuto: danza
    Dati non validi.
    Ritiro di Bianchi da robotica.
    Bianchi non e' tra gli iscritti a teatro.
    Iscrizione di Verdi a robotica (2/2)
    robotica: iscritti 2 su 2 posti
      1. Rossi        3A
      2. Verdi        1C
    teatro: iscritti 1 su 3 posti
      1. Rossi        3A
    Comando sconosciuto.
  ```

### Test 2 – Posti non validi

- **Input:** `0 3`
- **Output atteso:** `Numero di posti non valido (da 1 a 30).`
