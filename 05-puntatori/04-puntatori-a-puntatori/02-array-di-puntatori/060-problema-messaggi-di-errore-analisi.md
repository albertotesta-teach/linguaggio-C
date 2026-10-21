# Analisi – 060-problema-messaggi-di-errore.c

## 1. Problema

La stampante 3D del laboratorio registra gli errori come codici numerici.
Il tecnico vuole il registro della settimana con la descrizione di ogni
codice e il conteggio per tipo, compresi i codici che non hanno
descrizione.

## 2. Analisi

### Input

I dati sono inizializzati nel sorgente: il programma non legge nulla da
tastiera.

| Dato | Tipo | Valore |
|------|------|--------|
| `descrizioni` | `const char *[6]` | Testi dei codici 0-5 (l'indice è il codice) |
| `registro` | `int[10]` | 1, 3, 1, 0, 5, 9, 1, 3, 4, 1 |

### Output

- Il registro: per ogni evento numero, codice e descrizione (o
  `codice sconosciuto`).
- Il riepilogo: numero di eventi per ogni codice da 1 a 5 che compare, e il
  numero di codici sconosciuti.

### Vincoli

- `descrizione` restituisce il puntatore alla descrizione del codice, oppure
  a un testo di riserva (`"codice sconosciuto"`) se il codice è fuori da
  0-5: l'array non si legge mai fuori dai limiti.
- Il codice 0 (nessun errore) si conta ma non compare nel riepilogo.
- Il riepilogo segue l'ordine dei codici, non quello degli eventi.

### Assunzioni

- I codici previsti vanno da 0 a 5.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `conteggi` | `int[6]` | Eventi per codice |
| `sconosciuti` | `int` | Codici fuori tabella |
| `i` | `int` | Indice |

| Funzione | Compito |
|----------|---------|
| `descrizione(codice, descrizioni)` | Puntatore alla descrizione, o a "codice sconosciuto" |

### Algoritmo in linguaggio naturale

1. Per ogni evento stampare codice e descrizione; se il codice è tra 0 e 5
   incrementarne il conteggio, altrimenti contare un codice sconosciuto.
2. Stampare i conteggi dei codici da 1 a 5 maggiori di zero e il numero di
   codici sconosciuti.

## 3. Casi di test

### Test 1 – Registro del sorgente

- **Input:** nessuno.
- **Output atteso:**
  ```
  === REGISTRO DELLA SETTIMANA ===
    evento  1  codice 1  filamento esaurito
    evento  2  codice 3  piatto non livellato
    evento  3  codice 1  filamento esaurito
    evento  4  codice 0  nessun errore
    evento  5  codice 5  file di stampa danneggiato
    evento  6  codice 9  codice sconosciuto
    evento  7  codice 1  filamento esaurito
    evento  8  codice 3  piatto non livellato
    evento  9  codice 4  porta aperta durante la stampa
    evento 10  codice 1  filamento esaurito

  === RIEPILOGO ===
    4x filamento esaurito
    2x piatto non livellato
    1x porta aperta durante la stampa
    1x file di stampa danneggiato
    1x codice sconosciuto
  ```
