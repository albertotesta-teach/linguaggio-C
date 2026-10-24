# Analisi – 050-problema-orari-treni.c

## 1. Problema

Per quattro treni regionali usati dagli studenti il programma legge il
ritardo, calcola l'orario di arrivo e l'orario di arrivo a scuola (12
minuti a piedi) e controlla se è prima della campanella delle 8:00. Le
funzioni sugli orari ricevono e restituiscono struct `Orario` per valore.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `ritardo` | `int` | Ritardo in minuti di ogni treno; un valore negativo termina |
| treni | nel sorgente | Acqui Terme 7:02 (38 min), Ovada 7:10 (29), Novi Ligure 7:18 (24), Tortona 7:25 (21) |

### Output

- Per ogni treno: partenza, arrivo, arrivo a scuola e
  `in orario (N min di margine)` oppure
  `RITARDO di N min: serve il permesso`.
- `Ritardo non valido, ripetere.` per un ritardo non numerico.

### Vincoli

- Arrivo = partenza + durata + ritardo; a scuola = arrivo + 12 minuti.
- `aggiungi_minuti` restituisce un nuovo `Orario` e gestisce il passaggio
  della mezzanotte (modulo 24 ore).
- In orario se si arriva a scuola alle 8:00 o prima (margine ≥ 0).
- Un ritardo non numerico viene scartato e richiesto per lo stesso treno;
  a fine input il programma termina.

### Assunzioni

- Il ritardo è in minuti interi.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Orario` | `typedef struct { int ore; int minuti; } Orario;` | Un orario della giornata |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `partenze` | `Orario[4]` | Orari di partenza |
| `durate` | `int[4]` | Durata del viaggio in minuti |
| `campanella` | `Orario` | 8:00 |
| `arrivo`, `a_scuola` | `Orario` | Orari calcolati |
| `t` | `int` | Treno corrente |
| `letti` | `int` | Valore restituito da `scanf` |
| `CAMMINO` | `#define` | 12 minuti a piedi |

| Funzione | Compito |
|----------|---------|
| `crea_orario(ore, minuti)` | Costruisce un `Orario` |
| `aggiungi_minuti(o, minuti)` | Nuovo orario dopo un certo numero di minuti |
| `differenza(da, a)` | Minuti da `da` ad `a` (positivo se `a` viene dopo) |
| `stampa(o)` | Stampa `HH:MM` |
| `svuota_riga` | Scarta i caratteri rimasti dopo un inserimento non valido |

### Algoritmo in linguaggio naturale

1. Finché ci sono treni e il ritardo non è negativo:
   1. leggere il ritardo (fine input → negativo; testo → ripetere);
   2. se non negativo calcolare arrivo e arrivo a scuola, stamparli con il
      margine o il ritardo rispetto alla campanella, passare al treno
      successivo.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Quattro treni

- **Cosa si verifica:** margini, ritardo non numerico e studente in
  ritardo.
- **Input:** `0`, `5`, `abc`, `0`, `20`
- **Valori intermedi attesi:** Tortona 7:25 + 21 + 20 = 8:06, a scuola
  8:18, 18 minuti dopo la campanella.
- **Output atteso:**
  ```
    partenza 07:02, arrivo 07:40, a scuola 07:52  in orario (8 min di margine)
    partenza 07:10, arrivo 07:44, a scuola 07:56  in orario (4 min di margine)
    Ritardo non valido, ripetere.
    partenza 07:18, arrivo 07:42, a scuola 07:54  in orario (6 min di margine)
    partenza 07:25, arrivo 08:06, a scuola 08:18  RITARDO di 18 min: serve il permesso
  ```

### Test 2 – Arrivo esattamente alla campanella

- **Input:** `8`, `-1`
- **Output atteso:** `partenza 07:02, arrivo 07:48, a scuola 08:00  in
  orario (0 min di margine)`, poi il programma termina.

### Test 3 – Uscita anticipata

- **Input:** `3`, `-1`
- **Output atteso:** una sola riga (`a scuola 07:55  in orario (5 min di
  margine)`).
