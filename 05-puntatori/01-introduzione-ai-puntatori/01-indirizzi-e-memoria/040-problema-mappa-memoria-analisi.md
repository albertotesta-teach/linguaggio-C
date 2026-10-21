# Analisi – 040-problema-mappa-memoria.c

## 1. Problema

Lo sviluppatore del gestionale della segreteria vuole sapere come è
organizzata in memoria la scheda di uno studente (matricola, età, sezione,
media, nome, voti) e quanta memoria servirebbe per 1000 schede. Il
programma stampa una mappa con tipo, indirizzo e dimensione di ogni dato,
il dettaglio degli elementi dell'array dei voti e il totale.

## 2. Analisi

### Input

I dati della scheda sono inizializzati nel sorgente: il programma non legge
nulla da tastiera.

| Dato | Tipo | Valore |
|------|------|--------|
| `matricola` | `long` | 2026001 |
| `eta` | `int` | 16 |
| `sezione` | `char` | `'C'` |
| `media` | `double` | 7.4 |
| `nome` | `char[20]` | `"Giulia Ferri"` |
| `voti` | `int[6]` | 7, 8, 6, 8, 7, 8 |

### Output

- Una riga per dato: nome, tipo, indirizzo e byte occupati.
- Il valore e l'indirizzo di ogni elemento di `voti`.
- I byte occupati da una scheda e quelli necessari per 1000 schede, anche
  in KB.

### Vincoli

- Gli indirizzi si stampano con `%p`, convertendo il puntatore in `(void *)`.
- Le dimensioni (`size_t`) si stampano con `%zu`.
- `sizeof` di un array restituisce la dimensione dell'intero array
  (`sizeof(voti)` = 6 × `sizeof(int)`).
- Gli elementi di un array sono consecutivi: gli indirizzi di `voti[k]`
  crescono di `sizeof(int)` byte.

### Assunzioni

- Gli indirizzi cambiano a ogni esecuzione; l'ordine delle variabili in
  memoria è scelto dal compilatore.
- Sulle piattaforme a 64 bit usate in laboratorio `long` e `double` occupano
  8 byte e `int` 4 byte.
- Il totale non considera lo spazio che il compilatore può lasciare tra una
  variabile e l'altra.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `totale` | `size_t` | Somma delle dimensioni (stesso tipo restituito da `sizeof`) |
| `k` | `int` | Indice per scorrere `voti` |
| `VOTI`, `SCHEDE` | `#define` | 6 voti, 1000 schede |

### Algoritmo in linguaggio naturale

1. Per ogni dato della scheda stampare nome, tipo, `&dato` e `sizeof(dato)`;
   per gli array l'indirizzo è quello del primo elemento.
2. Per `k` da 0 a 5 stampare `voti[k]` e `&voti[k]`.
3. Calcolare `totale` come somma delle `sizeof` di tutti i dati.
4. Stampare `totale`, `totale × 1000` e lo stesso valore diviso per 1024 (KB).

## 3. Casi di test

Gli indirizzi cambiano a ogni esecuzione: nei test si controllano le
dimensioni e le relazioni tra indirizzi, non i valori esatti.

### Test 1 – Mappa delle variabili

- **Input:** nessuno (dati del sorgente).
- **Output atteso** (gli indirizzi `0x…` variano):
  ```
  === MAPPA DELLA MEMORIA: Giulia Ferri ===
    Dato         Tipo      Indirizzo        Byte
    matricola    long      0x…              8
    eta          int       0x…              4
    sezione      char      0x…              1
    media        double    0x…              8
    nome         char[20]  0x…              20
    voti         int[6]    0x…              24
  ```
  Tutti gli indirizzi sono diversi tra loro.

### Test 2 – Elementi consecutivi dell'array

- **Cosa si verifica:** gli elementi di `voti` occupano celle contigue.
- **Input:** nessuno.
- **Valori intermedi attesi:** se `&voti[0]` vale `X`, `&voti[k]` vale
  `X + 4k` (in esadecimale le ultime cifre avanzano di 4: …88, …8c, …90).
- **Output atteso** (indirizzi variabili):
  ```
  Dettaglio dell'array voti (elementi consecutivi):
      voti[0] = 7  0x…88
      voti[1] = 8  0x…8c
      voti[2] = 6  0x…90
      voti[3] = 8  0x…94
      voti[4] = 7  0x…98
      voti[5] = 8  0x…9c
  ```
  L'indirizzo di `voti[0]` coincide con quello stampato per `voti` nella mappa.

### Test 3 – Memoria per 1000 schede

- **Cosa si verifica:** la somma delle dimensioni e la conversione in KB.
- **Input:** nessuno.
- **Valori intermedi attesi:** `totale` = 8 + 4 + 1 + 8 + 20 + 24 = 65.
- **Output atteso:**
  ```
  Byte occupati da una scheda: 65
  Per 1000 schede servirebbero circa 65000 byte (63.5 KB)
  ```
