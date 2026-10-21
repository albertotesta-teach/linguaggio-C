# Analisi – 070-problema-salvataggio-partita.c

## 1. Problema

Un gioco a livelli salva la partita copiando byte per byte le variabili
dello stato: vite, punteggio, livello, tempo di gioco, personaggio e la
mappa dei livelli completati. Bisogna sapere quanto è grande un
salvataggio e quanti slot entrano in 1024 byte, confrontando la mappa dei
livelli memorizzata come array di `int` o di `char`.

## 2. Analisi

### Input

I dati sono inizializzati nel sorgente: il programma non legge nulla da
tastiera.

| Dato | Tipo | Valore | Significato |
|------|------|--------|-------------|
| `vite` | `int` | 3 | Vite rimaste |
| `punteggio` | `long` | 125400 | Punteggio (può superare i limiti di `short`) |
| `livello` | `short` | 12 | Livello corrente |
| `tempo_gioco` | `double` | 5423.7 | Secondi giocati |
| `personaggio` | `char` | `'M'` | Iniziale del personaggio |
| `completati_int` | `int[40]` | tutti 0 | Livelli completati, 4 byte ciascuno |
| `completati_char` | `char[40]` | tutti 0 | Livelli completati, 1 byte ciascuno |

### Output

- La tabella dello stato: per ogni variabile tipo, indirizzo e byte.
- La dimensione del salvataggio nelle due versioni e quanti slot entrano in
  1024 byte.
- I byte risparmiati usando `char` per i livelli e un riepilogo della
  partita di esempio.

### Vincoli

- Gli indirizzi si stampano con `%p` e `(void *)`, le dimensioni con `%zu`.
- La dimensione di base è la somma delle `sizeof` delle cinque variabili
  semplici; a questa si aggiunge la dimensione di uno dei due array.
- Gli slot sono un numero intero (divisione intera tra `size_t`).

### Assunzioni

- Il salvataggio contiene solo i byte delle variabili, senza spazi
  aggiuntivi.
- Dimensioni tipiche: `int` 4, `long` 8, `short` 2, `double` 8, `char` 1 byte.
- Gli indirizzi cambiano a ogni esecuzione.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `base` | `size_t` | Byte delle cinque variabili semplici |
| `con_int`, `con_char` | `size_t` | Dimensione del salvataggio nelle due versioni |
| `LIVELLI`, `MEMORIA_SLOT` | `#define` | 40 livelli, 1024 byte |

### Algoritmo in linguaggio naturale

1. Stampare la tabella con nome, tipo, `&variabile` e `sizeof(variabile)`;
   per gli array l'indirizzo del primo elemento e la dimensione dell'intero
   array.
2. Calcolare `base`, `con_int` = `base` + `sizeof(completati_int)` e
   `con_char` = `base` + `sizeof(completati_char)`.
3. Stampare per entrambe le versioni la dimensione e `1024 / dimensione` slot.
4. Stampare la differenza `con_int − con_char` e il riepilogo della partita.

## 3. Casi di test

### Test 1 – Tabella dello stato

- **Input:** nessuno (dati del sorgente).
- **Output atteso** (gli indirizzi variano): colonna `Byte` con 4, 8, 2, 8,
  1, 160, 40; tutti gli indirizzi diversi.

### Test 2 – Dimensione del salvataggio e slot

- **Cosa si verifica:** somme delle `sizeof` e divisione intera.
- **Input:** nessuno.
- **Valori intermedi attesi:** `base` = 4 + 8 + 2 + 8 + 1 = 23;
  `con_int` = 23 + 160 = 183; `con_char` = 23 + 40 = 63;
  1024 / 183 = 5; 1024 / 63 = 16.
- **Output atteso:**
  ```
  === DIMENSIONE DEL SALVATAGGIO ===
    livelli come int  :  183 byte ->  5 slot in 1024 byte
    livelli come char :   63 byte -> 16 slot in 1024 byte
    Usare char per i livelli fa risparmiare 120 byte a salvataggio.
    (Partita di esempio: vite 3, livello 12, punteggio 125400, personaggio M, 5424 s)
  ```

### Test 3 – Arrotondamento del tempo

- **Cosa si verifica:** `%.0f` arrotonda 5423.7 secondi a 5424.
- **Input:** nessuno.
- **Output atteso:** il riepilogo termina con `5424 s)`.
