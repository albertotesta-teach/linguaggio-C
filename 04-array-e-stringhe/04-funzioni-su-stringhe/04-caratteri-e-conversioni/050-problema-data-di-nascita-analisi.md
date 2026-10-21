# Analisi – 050-problema-data-di-nascita.c

## 1. Problema

Nel modulo di iscrizione la data di nascita si scrive come testo nel
formato gg/mm/aaaa. Il programma deve ricavare giorno, mese e anno,
verificare che la data esista (mesi di 30 e 31 giorni, anni bisestili),
riscriverla per esteso e calcolare l'età compiuta alla data di riferimento
(11/10/2026).

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `riga` | `char[40]` | Data scritta come testo `gg/mm/aaaa`, una per riga; una riga vuota termina |

La data di riferimento è fissata nel sorgente con `ANNO_CORRENTE`,
`MESE_CORRENTE`, `GIORNO_CORRENTE` (11/10/2026).

### Output

Per ogni riga uno dei messaggi:
- `Formato non valido: usare gg/mm/aaaa`;
- `Testo in piu' dopo la data`;
- `Anno A fuori dall'intervallo 1900-2026`;
- `Il mese M non esiste`;
- `<mese> <anno> ha N giorni` (giorno fuori intervallo);
- `La data e' successiva a quella di riferimento`;
- `Data valida: G <mese> AAAA, eta' E anni`.

### Vincoli

- Giorno, mese e anno si ricavano con `sscanf(riga, "%d/%d/%d%c", ...)`:
  meno di 3 valori convertiti → formato non valido; 4 valori → c'è testo
  dopo l'anno.
- I controlli seguono l'ordine formato → anno → mese → giorno → data
  futura: il mese va controllato prima del giorno, perché i giorni
  dipendono dal mese.
- Una data dell'anno di riferimento successiva all'11/10/2026 è rifiutata.
- Anno bisestile: divisibile per 4 e non per 100, oppure divisibile per 400.
- La data per esteso si costruisce con `snprintf`.
- L'età diminuisce di 1 se il compleanno dell'anno di riferimento non è ancora arrivato.

### Assunzioni

- L'anno ammesso va da 1900 all'anno di riferimento.
- Si accettano giorni e mesi scritti con una cifra (`5/3/2010`).

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `nomi_mesi` | `char[12][10]` | Nomi dei mesi |
| `per_esteso` | `char[40]` | Data riscritta con `snprintf` |
| `letta` | `int` | 1 se la lettura è riuscita |
| `letti` | `int` | Valori convertiti da `sscanf` |
| `g`, `m`, `a` | `int` | Giorno, mese, anno letti |
| `resto` | `char` | Carattere dopo la data, se presente |
| `eta` | `int` | Età compiuta |

| Funzione | Compito |
|----------|---------|
| `leggi_riga` | Legge una riga e toglie il `'\n'` |
| `bisestile` | 1 se l'anno è bisestile |
| `giorni_del_mese` | 28, 29, 30 o 31 |

### Algoritmo in linguaggio naturale

1. Leggere una riga.
2. Finché la lettura riesce e la riga non è vuota:
   1. convertire con `sscanf` e controllare nell'ordine: valori letti,
      testo in più, anno, mese, giorno (confrontato con `giorni_del_mese`),
      data successiva a quella di riferimento;
   2. se tutto è corretto costruire la data per esteso;
   3. età = anno di riferimento − anno; se il mese è successivo a quello di
      riferimento, o è lo stesso mese con giorno successivo, togliere 1;
   4. stampare il messaggio e leggere la riga successiva.

## 3. Casi di test

### Test 1 – Data valida e compleanno già passato

- **Cosa si verifica**: conversione, data per esteso ed età.
- **Input**: `12/05/2010`, poi riga vuota.
- **Valori intermedi attesi**: `letti` = 3, `eta` = 2026 − 2010 = 16 (maggio < ottobre).
- **Output atteso**:
  ```
    Data valida: 12 maggio 2010, eta' 16 anni
  ```

### Test 2 – Compleanno nel giorno di riferimento e il giorno dopo

- **Cosa si verifica**: il confine della correzione dell'età.
- **Input**: `11/10/2010`, `12/10/2010`, poi riga vuota.
- **Output atteso**:
  ```
    Data valida: 11 ottobre 2010, eta' 16 anni
    Data valida: 12 ottobre 2010, eta' 15 anni
  ```

### Test 3 – Formato sbagliato e testo in più

- **Cosa si verifica**: il valore restituito da `sscanf`.
- **Input**: `12-05-2010`, `12/05/2010 ore 8`, poi riga vuota.
- **Valori intermedi attesi**: `letti` = 1 (si ferma al `-`); `letti` = 4 (`resto` = spazio).
- **Output atteso**:
  ```
    Formato non valido: usare gg/mm/aaaa
    Testo in piu' dopo la data
  ```

### Test 4 – Data inesistente

- **Cosa si verifica**: giorni del mese, mese e anno fuori intervallo.
- **Input**: `29/02/2023`, `31/04/2011`, `15/13/2009`, `03/02/1850`, `31/12/2027`, poi riga vuota.
- **Output atteso**:
  ```
    febbraio 2023 ha 28 giorni
    aprile 2011 ha 30 giorni
    Il mese 13 non esiste
    Anno 1850 fuori dall'intervallo 1900-2026
    Anno 2027 fuori dall'intervallo 1900-2026
  ```

### Test 5 – Anni bisestili

- **Cosa si verifica**: le tre condizioni della regola dei bisestili.
- **Input**: `29/02/2024`, `29/02/1900`, `29/02/2000`, poi riga vuota.
- **Valori intermedi attesi**: `bisestile(2024)` = 1; `bisestile(1900)` = 0
  (divisibile per 100 ma non per 400); `bisestile(2000)` = 1.
- **Output atteso**:
  ```
    Data valida: 29 febbraio 2024, eta' 2 anni
    febbraio 1900 ha 28 giorni
    Data valida: 29 febbraio 2000, eta' 26 anni
  ```

### Test 6 – Data successiva a quella di riferimento nello stesso anno
- **Cosa si verifica:** una data di nascita "futura" nell'anno di
  riferimento è rifiutata, mentre la data di riferimento stessa è accettata.
- **Input:** `15/12/2026`, `12/10/2026`, `11/10/2026`, poi riga vuota.
- **Output atteso:**
  ```
    La data e' successiva a quella di riferimento
    La data e' successiva a quella di riferimento
    Data valida: 11 ottobre 2026, eta' 0 anni
  ```
