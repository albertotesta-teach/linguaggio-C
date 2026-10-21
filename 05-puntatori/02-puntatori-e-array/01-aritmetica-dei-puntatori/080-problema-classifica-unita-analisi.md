# Analisi – 080-problema-classifica-unita.c

## 1. Problema

I 100 metri si sono corsi in due batterie, ciascuna con i tempi già in
ordine crescente. Bisogna costruire la classifica finale unendo i due
elenchi in un solo elenco ordinato, indicando per ogni tempo la batteria di
provenienza e le tre medaglie.

## 2. Analisi

### Input

I dati sono inizializzati nel sorgente: il programma non legge nulla da
tastiera.

| Dato | Tipo | Valore |
|------|------|--------|
| `batteria_a` | `int[5]` | 1185, 1212, 1240, 1301, 1355 (centesimi di secondo, ordinati) |
| `batteria_b` | `int[4]` | 1179, 1226, 1238, 1290 (ordinati) |

### Output

- La classifica dei 9 atleti: posizione, tempo in secondi, batteria di
  provenienza e `medaglia` per i primi tre.
- Il controllo finale `Posizioni scritte: pc - &classifica[0] = 9`.

### Vincoli

- Fusione di due elenchi ordinati con quattro puntatori: `pa` e `pb` sul
  primo tempo non ancora usato di ogni batteria, `pc` e `pv` sulla
  prossima posizione libera di `classifica` e `provenienza`.
- A ogni passo si copia il tempo minore tra `*pa` e `*pb` e si avanza solo il
  puntatore della batteria da cui viene; ogni tempo si copia una sola volta.
- Quando una batteria è finita si copiano in coda i tempi rimasti
  dell'altra: dei due cicli finali al massimo uno viene eseguito.
- A parità di tempo viene prima la batteria A (confronto con `<=`).
- Alla fine `pc − &classifica[0]` deve valere 5 + 4 = 9.

### Assunzioni

- Le due batterie sono già ordinate in modo crescente.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `classifica` | `int[9]` | Tempi uniti |
| `provenienza` | `char[9]` | `'A'` o `'B'`, parallelo a `classifica` |
| `pa`, `pb` | `const int *` | Primo tempo non ancora usato di ogni batteria |
| `fine_a`, `fine_b` | `const int *` | Fine delle due batterie |
| `pc`, `pv` | `int *`, `char *` | Prossima posizione libera in `classifica` e `provenienza` |
| `posto` | `int` | Indice della stampa |

### Algoritmo in linguaggio naturale

1. Finché entrambe le batterie hanno tempi: se `*pa <= *pb` copiare `*pa`
   con `'A'` e avanzare `pa`, altrimenti copiare `*pb` con `'B'` e
   avanzare `pb`; avanzare `pc` e `pv`.
2. Copiare i tempi rimasti della batteria A, poi quelli della B.
3. Stampare la classifica con le medaglie ai primi tre.
4. Stampare il numero di posizioni scritte.

## 3. Casi di test

### Test 1 – Fusione dei dati del sorgente

- **Cosa si verifica:** fusione e coda della batteria A (13.01 e 13.55
  restano dopo che la B è finita con 12.90).
- **Input:** nessuno.
- **Output atteso:**
  ```
  === CLASSIFICA FINALE 100 METRI ===
    1. 11.79 s   batteria B   medaglia
    2. 11.85 s   batteria A   medaglia
    3. 12.12 s   batteria A   medaglia
    4. 12.26 s   batteria B
    5. 12.38 s   batteria B
    6. 12.40 s   batteria A
    7. 12.90 s   batteria B
    8. 13.01 s   batteria A
    9. 13.55 s   batteria A
  Posizioni scritte: pc - &classifica[0] = 9
  ```

### Test 2 – Tempi uguali

- **Cosa si verifica:** a parità viene prima la batteria A.
- **Procedura:** nel sorgente impostare il primo tempo della batteria A a
  1179, ricompilare ed eseguire.
- **Output atteso** (prime righe):
  ```
    1. 11.79 s   batteria A   medaglia
    2. 11.79 s   batteria B   medaglia
  ```
