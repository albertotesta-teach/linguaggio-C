# Analisi – 060-problema-prestiti-attrezzatura.c

## 1. Problema

Il magazzino di educazione fisica registra i prestiti. Ogni prestito è una
struct allocata all'uscita e liberata al rientro; l'array di puntatori usa
`NULL` per lo scaffale libero. Mettere `NULL` dopo `free` permette di
riusare lo scaffale, di riconoscere un secondo rientro e di liberare a fine
programma i prestiti rimasti aperti. Due contatori verificano che nessun
blocco resti in memoria.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `comando` | `char` | `U oggetto studente` uscita, `R scaffale` rientro, `E` elenco, `Q` fine (anche minuscoli) |

### Output

- `oggetto a studente: scaffale K`,
  `Registro pieno: nessuno scaffale libero.`, `Dati non validi.`
- `rientrato oggetto da studente`,
  `Scaffale K vuoto: niente da far rientrare.`, `Scaffale non valido.`
- `E`: i 4 scaffali con il prestito o `libero`.
- Alla chiusura: i prestiti da recuperare e
  `blocchi allocati A, liberati L: nessun blocco rimasto in memoria`
  (oppure il numero di blocchi persi).

### Vincoli

- `scaffale[k] = malloc(sizeof *scaffale[k])` con controllo di `NULL`;
  dopo ogni `free` il puntatore torna `NULL`.
- Si usa sempre il primo scaffale libero.
- Un comando per riga. A fine input il programma termina come con `Q`.

### Assunzioni

- Oggetto e studente sono una parola ciascuno.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Prestito` | `typedef struct { char oggetto[16]; char studente[20]; } Prestito;` | Un prestito |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `scaffale` | `Prestito *[4]` | `NULL` = libero |
| `allocati`, `liberati` | `int` | Controllo finale della memoria |

| Funzione | Compito |
|----------|---------|
| `primo_libero(scaffale)` | Indice del primo `NULL`, −1 se pieni |
| `elenco(scaffale)` | Stampa gli scaffali |

### Algoritmo in linguaggio naturale

1. Mettere `NULL` in tutti gli scaffali.
2. Finché il comando non è `Q`: leggere il comando in maiuscolo; con `U`
   allocare un prestito nel primo scaffale libero; con `R` stamparlo,
   liberarlo e mettere `NULL`; con `E` stampare; scartare il resto della
   riga.
3. Liberare i prestiti rimasti e confrontare i contatori.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Scaffali pieni e riuso

- **Input:** `U pallone Rossi`, `u racchetta Bianchi`, `U corda Verdi`,
  `U cerchio Neri`, `U palla Gialli`, `R 2`, `R 2`, `R 7`,
  `U palla Gialli`, `E`, `X`, `Q`
- **Output atteso:**
  ```
    pallone a Rossi: scaffale 1
    racchetta a Bianchi: scaffale 2
    corda a Verdi: scaffale 3
    cerchio a Neri: scaffale 4
    Registro pieno: nessuno scaffale libero.
    rientrato racchetta da Bianchi
    Scaffale 2 vuoto: niente da far rientrare.
    Scaffale non valido.
    palla a Gialli: scaffale 2
    1  pallone        Rossi
    2  palla          Gialli
    3  corda          Verdi
    4  cerchio        Neri
    Comando sconosciuto.

  Chiusura del magazzino
    da recuperare: pallone (Rossi)
    da recuperare: palla (Gialli)
    da recuperare: corda (Verdi)
    da recuperare: cerchio (Neri)
    blocchi allocati 5, liberati 5: nessun blocco rimasto in memoria
  ```
