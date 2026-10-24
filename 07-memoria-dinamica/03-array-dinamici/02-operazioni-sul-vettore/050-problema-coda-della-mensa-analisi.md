# Analisi – 050-problema-coda-della-mensa.c

## 1. Problema

Gli studenti si mettono in fila in fondo e vengono serviti dal primo. La
fila è un vettore dinamico di `Studente`: entrare costa una scrittura,
essere serviti significa rimuovere la posizione 0 e spostare tutti gli
altri. Il programma conta gli spostamenti per mostrare il costo di questa
scelta; uno studente può anche lasciare la fila prima del suo turno.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `comando` | `char` | `E nome` entra, `S` servi, `L nome` lascia, `F` mostra la fila, `Q` fine (anche minuscoli) |

### Output

- `nome in fila (posizione P)`, `Nome mancante.`
- `servito: nome (in fila restano N)`, `Fila vuota.`
- `nome lascia la fila`, `Non e' in fila.`
- `fila:` con i nomi in ordine.
- Alla fine: `Serviti: S, spostamenti nel vettore: M`.

### Vincoli

- Vettore `{Studente *dati; int n; int capacita;}` con capacità iniziale 4
  e raddoppio; il `main` usa solo le funzioni del vettore.
- `rimuovi` sposta indietro gli elementi successivi e conta ogni
  spostamento nel parametro di uscita: servire il primo di n studenti
  costa n − 1 spostamenti.
- Un comando per riga. A fine input il programma termina come con `Q`.

### Assunzioni

- I nomi in fila sono diversi.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Studente` | `typedef struct { char nome[20]; } Studente;` | Uno studente |
| `Fila` | `typedef struct { Studente *dati; int n; int capacita; } Fila;` | Vettore dinamico |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `fila` | `Fila *` | Il vettore |
| `spostamenti` | `long` | Costo totale delle rimozioni |
| `serviti` | `int` | Studenti serviti |

| Funzione | Compito |
|----------|---------|
| `crea_fila`, `distruggi_fila` | Allocazione e liberazione |
| `aggiungi(f, s)` | In fondo alla fila |
| `rimuovi(f, posizione, &uscito, &spostamenti)` | Toglie una posizione |
| `lunghezza`, `elemento`, `cerca` | Accesso e ricerca |

### Algoritmo in linguaggio naturale

1. Finché il comando non è `Q`: leggere il comando in maiuscolo; eseguire
   ingresso, servizio dalla posizione 0, uscita dalla posizione trovata o
   stampa; scartare il resto della riga.
2. Stampare serviti e spostamenti; distruggere la fila.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Ora di pranzo

- **Input:** `S`, `E Anna`, `e Bruno`, `E Carla`, `E Dario`, `E Elena`,
  `F`, `S`, `L Dario`, `L Zoe`, `S extra`, `F`, `X`, `Q`
- **Valori intermedi attesi:** servire Anna su 5: 4 spostamenti; Dario in
  terza posizione su 4: 1; servire Bruno su 3: 2; totale 7.
- **Output atteso:**
  ```
    Fila vuota.
    Anna in fila (posizione 1)
    Bruno in fila (posizione 2)
    Carla in fila (posizione 3)
    Dario in fila (posizione 4)
    Elena in fila (posizione 5)
    fila: Anna Bruno Carla Dario Elena
    servito: Anna (in fila restano 4)
    Dario lascia la fila
    Non e' in fila.
    servito: Bruno (in fila restano 2)
    fila: Carla Elena
    Comando sconosciuto.
  Serviti: 2, spostamenti nel vettore: 7
  ```
