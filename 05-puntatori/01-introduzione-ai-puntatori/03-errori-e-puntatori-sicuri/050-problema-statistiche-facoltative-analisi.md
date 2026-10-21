# Analisi – 050-problema-statistiche-facoltative.c

## 1. Problema

Il registro elettronico calcola minimo, massimo e media dei voti di una
verifica con un'unica funzione, ma non tutti i chiamanti hanno bisogno di
tutti i risultati. Chi non vuole un risultato passa `NULL` al posto
dell'indirizzo. Se non ci sono voti la funzione non calcola nulla e lo
segnala.

## 2. Analisi

### Input

I dati sono inizializzati nel sorgente: il programma non legge nulla da
tastiera.

| Dato | Tipo | Valore |
|------|------|--------|
| `verifica` | `int[8]` | 7, 5, 8, 6, 9, 4, 7, 6 |
| chiamate | — | tutti i risultati; solo media; solo minimo; nessun voto (`n = 0`) |

### Output

- Minimo, massimo e media della verifica.
- Solo la media.
- Solo il minimo, con il giudizio sulle insufficienze (voto minimo < 6).
- `Verifica senza voti: statistiche non disponibili`.

### Vincoli

- `statistiche` restituisce i risultati tramite tre puntatori; chi non vuole
  un risultato passa `NULL`.
- I calcoli si fanno sulle variabili locali; un risultato si scrive solo se
  il puntatore corrispondente non è `NULL`: mai scrivere tramite `NULL`.
- Con `n = 0` la media non esiste (divisione per zero): la funzione non
  calcola nulla e restituisce 0.
- La media si calcola in `double` con un cast (`(double) somma / n`).

### Assunzioni

- I voti sono interi.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `minimo`, `massimo`, `media` | `int`, `int`, `double` | Risultati nel `main` |
| `min`, `max`, `somma` | `int` | In `statistiche`: calcoli locali |
| `calcolato` | `int` | In `statistiche`: valore restituito (1 se `n > 0`) |
| `STUDENTI` | `#define` | 8 |

| Funzione | Compito |
|----------|---------|
| `statistiche(voti, n, int *minimo, int *massimo, double *media)` | Calcola e scrive solo nei puntatori non `NULL`; restituisce 0 se `n` è 0 |

### Algoritmo in linguaggio naturale

1. In `statistiche`, se `n > 0`:
   1. scorrere i voti calcolando somma, minimo e massimo;
   2. scrivere ciascun risultato solo se il puntatore non è `NULL`;
   3. restituire 1;
   altrimenti restituire 0 senza scrivere nulla.
2. Nel `main` chiamare la funzione quattro volte (tutti i risultati, solo
   media, solo minimo, nessun voto) e stampare ciò che è stato richiesto.

## 3. Casi di test

### Test 1 – Chiamate del sorgente

- **Cosa si verifica:** risultati completi, parziali e nessun voto.
- **Input:** nessuno (dati del sorgente).
- **Valori intermedi attesi:** somma = 52, media = 52 / 8 = 6.50.
- **Output atteso:**
  ```
  Verifica completa: minimo 4, massimo 9, media 6.50
  Per la pagella serve solo la media: 6.50
  Controllo insufficienze: voto minimo 4 -> ci sono insufficienze
  Verifica senza voti: statistiche non disponibili
  ```

### Test 2 – Nessuna insufficienza

- **Cosa si verifica:** l'altro ramo del giudizio.
- **Procedura:** nel sorgente sostituire i voti con 7, 6, 8, 6, 9, 6, 7, 6,
  ricompilare ed eseguire.
- **Output atteso:**
  ```
  Verifica completa: minimo 6, massimo 9, media 6.88
  Per la pagella serve solo la media: 6.88
  Controllo insufficienze: voto minimo 6 -> nessuna insufficienza
  Verifica senza voti: statistiche non disponibili
  ```
