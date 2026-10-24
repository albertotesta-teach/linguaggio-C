# Analisi – 080-problema-livelli-di-log.c

## 1. Problema

Il server del laboratorio scrive messaggi di livello diverso. Il livello è
un `enum` ordinato dal meno al più grave, quindi due livelli si
confrontano con `>=`. Il programma legge la soglia, stampa i messaggi con
livello almeno pari alla soglia e conta i messaggi di ogni livello.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `soglia` | `int` | 0 DEBUG, 1 INFO, 2 AVVISO, 3 ERRORE |
| `registro` | `Messaggio[8]` | Messaggi della mattina (nel sorgente) |

### Output

- I messaggi con livello ≥ soglia: `ora [LIVELLO] testo`.
- `Mostrati N messaggi su 8`.
- Il conteggio dei messaggi per ogni livello (su tutto il registro).
- `Soglia non valida.`

### Vincoli

- `typedef enum { DEBUG, INFO, AVVISO, ERRORE, NUM_LIVELLI } Livello;`:
  l'ordine delle costanti è l'ordine di gravità.
- La soglia si controlla prima di convertirla in `Livello`.
- I conteggi usano il livello come indice.

### Assunzioni

- I messaggi sono in ordine di orario.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Livello` | `typedef enum { DEBUG, INFO, AVVISO, ERRORE, NUM_LIVELLI } Livello;` | Gravità del messaggio |
| `Messaggio` | `typedef struct { char ora[6]; Livello livello; char testo[40]; } Messaggio;` | Una riga del registro |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `nomi` | `const char *[4]` | Nomi indicizzati dal livello |
| `conteggi` | `int[4]` | Messaggi per livello |
| `mostrati` | `int` | Messaggi stampati |
| `l` | `Livello` | Indice del ciclo sui livelli |

### Algoritmo in linguaggio naturale

1. Leggere la soglia; se non è tra 0 e 3 segnalarlo.
2. Per ogni messaggio: contarlo nel suo livello; se il livello è ≥ soglia
   stamparlo e contarlo tra i mostrati.
3. Stampare il totale mostrato e i conteggi per livello.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Soglia AVVISO

- **Input:** `2`
- **Output atteso:**
  ```
  Soglia (0 DEBUG, 1 INFO, 2 AVVISO, 3 ERRORE):   09:02 [AVVISO] disco al 85%
    10:12 [ERRORE] stampante lab non risponde
    10:13 [AVVISO] nuovo tentativo di stampa
    11:30 [ERRORE] backup notturno non trovato
  Mostrati 4 messaggi su 8
    DEBUG  1
    INFO   3
    AVVISO 2
    ERRORE 2
  ```

### Test 2 – Soglia minima e massima

- **Input:** `0`; poi `3`
- **Output atteso:** con 0 tutti gli 8 messaggi (`Mostrati 8 messaggi su
  8`); con 3 solo i due `ERRORE` (`Mostrati 2 messaggi su 8`); i conteggi
  per livello non cambiano.

### Test 3 – Soglia non valida

- **Input:** `4` (poi `-1`, `abc`)
- **Output atteso:** `Soglia non valida.`
