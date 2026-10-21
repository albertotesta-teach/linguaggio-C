# Analisi – 040-problema-codice-fiscale.c

## 1. Problema

All'iscrizione la segreteria inserisce il codice fiscale degli studenti e
vuole intercettare subito gli errori di battitura. Il programma accetta il
codice anche in minuscolo, ne controlla la lunghezza e il tipo di ogni
carattere secondo lo schema del codice fiscale, verifica la lettera del
mese e, se il formato è corretto, ricava sesso e data di nascita.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `cf` | `char[30]` | Codice fiscale letto da tastiera, uno per riga; una riga vuota termina. Il buffer è più lungo di 16 per accorgersi dei codici troppo lunghi |

### Output

Per ogni codice, ripetuto in maiuscolo, uno dei messaggi:
- `deve avere 16 caratteri, ne ha N`;
- `in posizione P serve una lettera` / `una cifra` (posizione contata da 1);
- `la lettera del mese 'X' non esiste`;
- `formato corretto` seguito da `sesso M, nato il G <mese> 'AA` oppure
  `sesso F, nata il G <mese> 'AA`.

### Vincoli

- Il codice si converte in maiuscolo con `toupper` prima dei controlli.
- I controlli seguono l'ordine lunghezza → schema → lettera del mese;
  si segnala solo il primo errore.
- Schema del codice: `LLLLLLCCLCCLCCCL` (L = lettera, verificata con
  `isalpha`; C = cifra, verificata con `isdigit`).
- Lettere dei mesi: `ABCDEHLMPRST` (gennaio … dicembre).
- Le cifre si convertono in numero con `c - '0'`.
- Per le donne il giorno è aumentato di 40: un giorno > 40 indica sesso F.

### Assunzioni

- Non si verifica il carattere di controllo finale né il codice del comune.
- Non si verifica che il giorno sia compatibile con il mese.
- L'anno è stampato con due cifre, come compare nel codice.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `schema` | `char[17]` | `"LLLLLLCCLCCLCCCL"` |
| `lettere_mesi` | `char[13]` | `"ABCDEHLMPRST"`: lettera di ogni mese |
| `nomi_mesi` | `char[12][10]` | Nomi dei mesi (parallelo a `lettere_mesi`) |
| `letta` | `int` | 1 se la lettura è riuscita |
| `errore` | `int` | Indice del primo carattere fuori schema, o -1 |
| `mese` | `int` | Indice del mese (0–11), o -1 |
| `giorno`, `anno` | `int` | Valori ricavati dalle cifre |

| Funzione | Compito |
|----------|---------|
| `leggi_riga` | Legge una riga e toglie il `'\n'` |
| `in_maiuscolo` | `toupper` su ogni carattere |
| `primo_errore` | Confronta il codice con lo schema usando `isalpha` e `isdigit` |
| `indice_mese` | Indice della lettera del mese, oppure -1 |

### Algoritmo in linguaggio naturale

1. Leggere un codice.
2. Finché la lettura riesce e il codice non è vuoto:
   1. convertirlo in maiuscolo e stamparlo;
   2. se la lunghezza è diversa da 16 segnalarlo;
   3. altrimenti cercare il primo carattere fuori schema: se c'è,
      segnalare la posizione e il tipo di carattere richiesto;
   4. altrimenti cercare la lettera del mese (carattere 9): se non esiste segnalarlo;
   5. altrimenti calcolare anno (caratteri 7–8) e giorno (caratteri 10–11);
      se il giorno supera 40 stampare sesso F e giorno − 40, altrimenti sesso M;
   6. leggere il codice successivo.

## 3. Casi di test

### Test 1 – Codice corretto scritto in minuscolo

- **Cosa si verifica**: conversione in maiuscolo e decodifica di un codice maschile.
- **Input**: `rssmra85t10a944s`, poi riga vuota.
- **Valori intermedi attesi**: `errore` = -1, `mese` = 11 (`T`), `anno` = 85, `giorno` = 10.
- **Output atteso**:
  ```
    RSSMRA85T10A944S: formato corretto
      sesso M, nato il 10 dicembre '85
  ```

### Test 2 – Codice femminile

- **Cosa si verifica**: giorno aumentato di 40.
- **Input**: `BNCLRA92M52F205X`, poi riga vuota.
- **Valori intermedi attesi**: `mese` = 7 (`M`), `giorno` = 52 → 52 − 40 = 12.
- **Output atteso**:
  ```
    BNCLRA92M52F205X: formato corretto
      sesso F, nata il 12 agosto '92
  ```

### Test 3 – Lunghezza errata

- **Cosa si verifica**: codice troppo corto e troppo lungo.
- **Input**: `RSSMRA85T10A94`, `RSSMRA85T10A944SXX`, poi riga vuota.
- **Output atteso**:
  ```
    RSSMRA85T10A94: deve avere 16 caratteri, ne ha 14
    RSSMRA85T10A944SXX: deve avere 16 caratteri, ne ha 18
  ```

### Test 4 – Carattere fuori schema

- **Cosa si verifica**: una cifra dove serve una lettera e viceversa;
  la posizione è contata da 1.
- **Input**: `RSSMR485T10A944S`, `RSSMRA8XT10A944S`, poi riga vuota.
- **Valori intermedi attesi**: `errore` = 5 e `errore` = 7.
- **Output atteso**:
  ```
    RSSMR485T10A944S: in posizione 6 serve una lettera
    RSSMRA8XT10A944S: in posizione 8 serve una cifra
  ```

### Test 5 – Lettera del mese inesistente

- **Cosa si verifica**: il nono carattere è una lettera ma non corrisponde a nessun mese.
- **Input**: `RSSMRA85Z10A944S`, poi riga vuota.
- **Valori intermedi attesi**: `errore` = -1, `mese` = -1.
- **Output atteso**:
  ```
    RSSMRA85Z10A944S: la lettera del mese 'Z' non esiste
  ```
