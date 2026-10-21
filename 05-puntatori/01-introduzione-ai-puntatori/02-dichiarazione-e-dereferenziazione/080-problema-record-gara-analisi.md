# Analisi – 080-problema-record-gara.c

## 1. Problema

Nella finale dei 50 metri stile libero dei giochi studenteschi i tempi
delle 6 corsie sono in un array (0 = squalificato o assente). Bisogna
trovare il vincitore e la sua corsia, segnalare se ha battuto il record dei
giochi (aggiornandolo) e gestire il caso in cui nessun atleta abbia concluso.

## 2. Analisi

### Input

I dati sono inizializzati nel sorgente: il programma non legge nulla da
tastiera.

| Dato | Tipo | Valore |
|------|------|--------|
| `finale_a` | `int[6]` | 3125, 2987, 0, 3010, 2955, 3102 (centesimi di secondo) |
| `finale_b` | `int[6]` | tutti 0 |
| `record` | `int` | 2970 (29"70) |

### Output

- Il record iniziale.
- Per ogni finale: il tempo di ogni corsia (o `squalificato`), poi
  `Vince la corsia N con S"CC`, con `: NUOVO RECORD!` se il record è
  battuto, oppure `Nessun atleta ha concluso la gara.`
- Il record aggiornato.

### Vincoli

- I tempi 0 non partecipano al confronto.
- `migliore` contiene l'indirizzo dell'elemento con il tempo migliore ed è
  `NULL` finché non si trova un tempo valido: se resta `NULL` non si
  dereferenzia.
- La corsia si ricava confrontando `&tempi[k]` con `migliore`.
- `esamina_finale` riceve `&record` e aggiorna il record del `main`
  tramite il puntatore; il record si batte solo con un tempo strettamente
  minore.
- I tempi si stampano come secondi e centesimi (`29"55`).

### Assunzioni

- Non ci sono tempi uguali; a parità vincerebbe la corsia più bassa.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `migliore` | `int *` | Indirizzo del tempo migliore, `NULL` se nessuno |
| `corsia` | `int` | Corsia del vincitore |
| `k` | `int` | Indice delle corsie |
| `CORSIE` | `#define` | 6 |

| Funzione | Compito |
|----------|---------|
| `esamina_finale(titolo, tempi, int *record)` | Stampa i tempi, trova il migliore e aggiorna il record |
| `stampa_tempo` | Stampa secondi e centesimi |

### Algoritmo in linguaggio naturale

1. Stampare il record.
2. Per ogni finale chiamare `esamina_finale`, che:
   1. per ogni corsia stampa il tempo o `squalificato`; se il tempo non è 0
      e `migliore` è `NULL` o il tempo è minore di `*migliore`, pone
      `migliore = &tempi[k]`;
   2. se `migliore` è `NULL` stampa che nessuno ha concluso;
   3. altrimenti trova la corsia con `&tempi[k] == migliore`, stampa il
      vincitore e, se `*migliore < *record`, aggiorna `*record` e segnala il
      nuovo record.
3. Stampare il record aggiornato.

## 3. Casi di test

### Test 1 – Vincitore con nuovo record

- **Input:** `finale_a` e `record` del sorgente.
- **Valori intermedi attesi:** `migliore` = `&tempi[4]` (2955 < 2970).
- **Output atteso:**
  ```
  === Finale maschile ===
    corsia 1: 31"25
    corsia 2: 29"87
    corsia 3: squalificato
    corsia 4: 30"10
    corsia 5: 29"55
    corsia 6: 31"02
    Vince la corsia 5 con 29"55: NUOVO RECORD!
  ```

### Test 2 – Nessun atleta all'arrivo

- **Cosa si verifica:** `migliore` resta `NULL` e non si dereferenzia.
- **Input:** `finale_b` (tutti 0).
- **Output atteso:** sei righe `squalificato`, poi
  `  Nessun atleta ha concluso la gara.`

### Test 3 – Record aggiornato nel main

- **Cosa si verifica:** la funzione modifica la variabile del `main`.
- **Input:** dati del sorgente.
- **Output atteso:** prima riga `Record dei giochi: 29"70`, ultima riga
  `Record aggiornato: 29"55`.

### Test 4 – Record non battuto

- **Procedura:** nel sorgente impostare `record = 2900`, ricompilare ed eseguire.
- **Output atteso:**
  ```
    Vince la corsia 5 con 29"55
  ...
  Record aggiornato: 29"00
  ```
