# Analisi – 080-problema-istogramma-voti.c

## 1. Problema

Il docente vuole vedere come si distribuiscono i 24 voti di una verifica in
cinque fasce (insufficiente, sufficiente, discreto, buono, ottimo): per
ogni fascia il numero di studenti, la percentuale e una barra di asterischi,
poi la fascia più numerosa e il numero di sufficienze.

## 2. Analisi

### Input

I dati sono inizializzati nel sorgente: il programma non legge nulla da
tastiera.

| Dato | Tipo | Valore |
|------|------|--------|
| `voti` | `int[24]` | 6, 7, 5, 8, 4, 9, 6, 7, 7, 6, 10, 5, 6, 8, 7, 3, 6, 7, 8, 5, 9, 6, 7, 6 |
| `nomi` | `char[5][16]` | insufficiente, sufficiente, discreto, buono, ottimo |

### Output

- Per ogni fascia: nome, numero di studenti, percentuale e una barra con un
  asterisco per studente.
- La fascia più numerosa e il numero di studenti con almeno 6.

### Vincoli

- Fasce: insufficiente < 6; sufficiente 6; discreto 7; buono 8; ottimo 9-10.
- `conta_fasce` riceve `conteggi` come `int *`, lo azzera e lo riempie
  usando la notazione `*(conteggi + f)`: modifica l'array del `main`.
- Percentuale intera (`conteggio × 100 / 24`): la somma delle percentuali
  può non fare 100.
- A parità di numerosità vale la fascia più bassa (confronto con `>`).

### Assunzioni

- I voti sono validi, da 1 a 10.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `conteggi` | `int[5]` | Studenti per fascia, riempito dalla funzione |
| `prevalente` | `int` | Indice della fascia più numerosa |
| `f`, `k` | `int` | Indice della fascia, contatore degli asterischi |

| Funzione | Compito |
|----------|---------|
| `indice_fascia(voto)` | Fascia 0-4 di un voto |
| `conta_fasce(voti, n, conteggi)` | Azzera e riempie l'array dei conteggi |
| `posizione_massimo(v, n)` | Posizione dell'elemento maggiore |

### Algoritmo in linguaggio naturale

1. Contare i voti per fascia con `conta_fasce`: azzerare i 5 contatori,
   poi per ogni voto incrementare il contatore della sua fascia.
2. Per ogni fascia stampare nome, conteggio, percentuale e asterischi.
3. Trovare la fascia più numerosa con `posizione_massimo` e stamparla.
4. Stampare `24 − conteggi[0]` sufficienti.

## 3. Casi di test

### Test 1 – Dati del sorgente

- **Input:** nessuno.
- **Valori intermedi attesi:** `conteggi` = {5, 7, 6, 3, 3}; percentuali
  20, 29, 25, 12, 12 (somma 98 per la divisione intera).
- **Output atteso:**
  ```
  === ESITI DELLA VERIFICA (24 studenti) ===
    insufficiente   5   20%  *****
    sufficiente     7   29%  *******
    discreto        6   25%  ******
    buono           3   12%  ***
    ottimo          3   12%  ***

  Fascia piu' numerosa: sufficiente (7 studenti)
  Sufficienti o meglio: 19 su 24
  ```
