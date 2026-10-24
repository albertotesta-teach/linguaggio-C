# Analisi – 040-problema-rubrica-della-classe.c

## 1. Problema

Il rappresentante di classe tiene i contatti dei compagni in una rubrica,
vettore dinamico di `Contatto`. Le quattro operazioni classiche: aggiunta
(rifiutata se il nome c'è già), ricerca per inizio del nome, modifica del
telefono tramite il puntatore restituito da `trova`, cancellazione con
spostamento dei successivi.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `comando` | `char` | `A nome telefono`, `C inizio`, `M nome telefono`, `D nome`, `E` elenco, `Q` fine (anche minuscoli) |

### Output

- `aggiunto nome (contatti: N)`, `nome e' gia' in rubrica.`,
  `Dati non validi.`
- `C`: i contatti il cui nome inizia con il testo, oppure
  `Nessun contatto trovato.`
- `M`: `nome: vecchio -> nuovo`, `nome non e' in rubrica.`
- `D`: `cancellato nome (contatti: N)`, `Contatto non trovato.`
- `E`: numero di contatti e elenco.
- `Memoria insufficiente.`, `Comando sconosciuto.`

### Vincoli

- Vettore `{Contatto *dati; int n; int capacita;}` con capacità iniziale 2
  e raddoppio; il `main` usa solo le funzioni della rubrica.
- `trova` ed `elemento` restituiscono un puntatore all'elemento, valido
  solo fino alla prossima aggiunta (che può spostare il blocco): la
  modifica lo usa subito.
- Telefono: da 6 a 15 cifre.
- Ricerca per prefisso con `strncmp`; maiuscole e minuscole contano.
- Un comando per riga. A fine input il programma termina come con `Q`.

### Assunzioni

- Il nome è una sola parola.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Contatto` | `typedef struct { char nome[20]; char telefono[16]; } Contatto;` | Un contatto |
| `Rubrica` | `typedef struct { Contatto *dati; int n; int capacita; } Rubrica;` | Vettore dinamico |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `rubrica` | `Rubrica *` | Il vettore |
| `c` | `Contatto` | Dati letti |
| `p` | `Contatto *` | Contatto trovato |
| `trovati` | `int` | Risultati della ricerca |

| Funzione | Compito |
|----------|---------|
| `crea_rubrica`, `distruggi_rubrica` | Allocazione e liberazione |
| `aggiungi`, `rimuovi` | Inserimento in fondo e cancellazione |
| `lunghezza`, `elemento`, `cerca`, `trova` | Accesso e ricerca |
| `telefono_valido(telefono)` | Solo cifre, 6-15 |
| `inizia_con(nome, testo)` | Prefisso |

### Algoritmo in linguaggio naturale

1. Finché il comando non è `Q`: leggere il comando in maiuscolo; eseguire
   aggiunta, ricerca, modifica, cancellazione o elenco; scartare il resto
   della riga.
2. Distruggere la rubrica.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Le quattro operazioni

- **Input:** `A Rossi 3331234567`, `a Rosa 3409876543`,
  `A Bianchi 01311234`, `A Rossi 3330000000`, `A Verdi 12ab45`, `C Ro`,
  `c Z`, `M Rosa 3401111111`, `M Neri 3402222222`, `D Bianchi`, `D Mori`,
  `E extra`, `X`, `Q`
- **Output atteso:**
  ```
    aggiunto Rossi (contatti: 1)
    aggiunto Rosa (contatti: 2)
    aggiunto Bianchi (contatti: 3)
    Rossi e' gia' in rubrica.
    Dati non validi.
    Rossi        3331234567
    Rosa         3409876543
    Nessun contatto trovato.
    Rosa: 3409876543 -> 3401111111
    Neri non e' in rubrica.
    cancellato Bianchi (contatti: 2)
    Contatto non trovato.
    Contatti in rubrica: 2
     1. Rossi        3331234567
     2. Rosa         3401111111
    Comando sconosciuto.
  ```
