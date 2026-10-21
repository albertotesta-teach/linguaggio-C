# Analisi – 040-problema-lancio-dado.c

## 1. Problema

Un gioco da tavolo vuole verificare statisticamente l'equilibrio di un dado
a sei facce. Il programma legge 30 lanci da tastiera, conta le uscite di
ciascuna faccia, visualizza la distribuzione con un istogramma testuale e
identifica la faccia più e meno frequente.

---

## 2. Analisi

### Input

| Variabile | Tipo  | Descrizione                                      |
|-----------|-------|--------------------------------------------------|
| `lancio`  | `int` | Risultato di un lancio (1–6), letto 30 volte     |

### Output
- Una tabella con, per ogni faccia, il numero di uscite e un istogramma di
  asterischi (un asterisco per uscita);
- la faccia uscita più spesso e quella uscita meno spesso, con il numero di
  uscite;
- la frequenza attesa per un dado equilibrato (30 / 6 = 5.0).

### Vincoli
- Ogni lancio è compreso tra 1 e 6: un valore fuori intervallo viene
  segnalato e richiesto di nuovo, senza essere contato
- La somma delle frequenze è sempre 30
- Il numero di asterischi di ogni riga è uguale alla frequenza della faccia
- In caso di parità tra più facce vince la prima trovata (indice più basso),
  perché il confronto usa `>` e `<` stretti
- Il valore restituito da `scanf` si controlla: un testo non numerico è un
  valore non valido e il resto della riga si scarta con `getchar`; se
  l'input termina prima dei 30 lanci (EOF) l'analisi viene annullata

### Assunzioni
- Nessuna in particolare


### Variabili di supporto

Il punto chiave del problema è l'uso di **un solo array come tabella di
frequenze**: il valore letto (1–6) diventa direttamente un indice
(`lancio - 1`), così ogni cella conta le uscite della faccia corrispondente.
Non servono array paralleli perché il dato stesso funge da indice.

```
  Faccia:      1    2    3    4    5    6
  Indice:     [0]  [1]  [2]  [3]  [4]  [5]
```

| Variabile    | Tipo      | Dimensione | Descrizione                                       |
|--------------|-----------|------------|---------------------------------------------------|
| `frequenze`  | `int[]`   | 6          | `frequenze[i]` = uscite della faccia i+1          |
| `valido`     | `int`     | —          | Flag del ciclo di validazione                     |
| `max_freq`, `min_freq`     | `int` | — | Frequenze estreme trovate                       |
| `faccia_max`, `faccia_min` | `int` | — | Facce corrispondenti agli estremi               |
| `i`, `j`     | `int`     | —          | Indice della faccia e contatore degli asterischi  |
| `NUM_FACCE`  | `#define` | 6          | Numero di facce del dado                          |
| `NUM_LANCI`  | `#define` | 30         | Numero di lanci da inserire                       |

### Algoritmo in linguaggio naturale
1. Inizializzare tutte le frequenze a 0.
2. Per ciascuno dei 30 lanci:
   a. leggere il valore ripetendo finché non è compreso tra 1 e 6
      (con messaggio di errore per i valori non validi);
   b. incrementare `frequenze[lancio - 1]`.
3. Per ogni faccia stampare il numero, la frequenza e tanti asterischi
   quanto vale la frequenza.
4. Porre massimo e minimo uguali a `frequenze[0]` (faccia 1); per le facce
   da 2 a 6 aggiornare il massimo se la frequenza è maggiore e il minimo se
   è minore.
5. Stampare faccia più e meno frequente e la frequenza attesa
   `NUM_LANCI / NUM_FACCE`.

---

## 3. Casi di test

Per ogni caso si esegue il programma con i 30 lanci indicati e si confronta
quanto stampato con l'output atteso.

### Test 1 – Distribuzione tipica
- **Input:** 1 1 1 1 1 · 2 2 2 2 · 3 3 3 3 3 3 · 4 4 4 · 5 5 5 5 5 5 5 ·
  6 6 6 6 6
- **Output atteso:**
```
=== RISULTATI ===
  Faccia | Conteggio | Istogramma
  -------|-----------|--------------------
    1    |      5    | *****
    2    |      4    | ****
    3    |      6    | ******
    4    |      3    | ***
    5    |      7    | *******
    6    |      5    | *****

Faccia uscita piu' spesso : 5 (7 volte)
Faccia uscita meno spesso : 4 (3 volte)

Frequenza attesa per dado equilibrato: 5.0 volte per faccia
```

### Test 2 – Dado perfettamente equilibrato
- **Cosa si verifica:** con tutte le frequenze uguali vince la prima faccia
- **Input:** la sequenza 1 2 3 4 5 6 ripetuta 5 volte
- **Output atteso:** tutte le facce con 5 uscite;
  `Faccia uscita piu' spesso : 1 (5 volte)` e
  `Faccia uscita meno spesso : 1 (5 volte)`

### Test 3 – Valori non validi e una sola faccia
- **Cosa si verifica:** la validazione e una faccia con 0 uscite
- **Input:** 0, 7 (rifiutati), poi 30 volte il valore 3
- **Output atteso:** due volte
  `Valore non valido. Inserire un numero da 1 a 6.` al primo lancio;
  `Faccia uscita piu' spesso : 3 (30 volte)` e
  `Faccia uscita meno spesso : 1 (0 volte)`

### Test 4 – Testo non numerico e fine dell'input
- **Cosa si verifica:** la validazione di un testo al posto del numero e la chiusura senza ciclo infinito
- **Input:** `tre`, `4`, poi fine dell'input (Ctrl+D, o input da pipe)
- **Output atteso:**
```
  Lancio  1:   Valore non valido. Inserire un numero da 1 a 6.
  Lancio  1:   Lancio  2: 

Input terminato prima di 30 lanci: analisi annullata.
```
