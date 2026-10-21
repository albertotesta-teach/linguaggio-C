# Analisi – 040-problema-saluto-personalizzato.c

## 1. Problema
L'utente inserisce la propria data di nascita (giorno, mese, anno) e l'anno
corrente. Il programma calcola l'età approssimata e stampa un riepilogo
formattato con un messaggio di benvenuto personalizzato.

## 2. Analisi

### Input

| Variabile        | Tipo  | Significato                         |
|------------------|-------|-------------------------------------|
| `giorno_nascita` | `int` | Giorno del mese di nascita (1–31)   |
| `mese_nascita`   | `int` | Mese di nascita (1–12)              |
| `anno_nascita`   | `int` | Anno di nascita (es. 2005)          |
| `anno_corrente`  | `int` | Anno corrente inserito dall'utente  |

### Output
Un riepilogo con la data di nascita nel formato `gg/mm/aaaa` (giorno e mese
sempre su due cifre), l'anno corrente, l'età stimata e un messaggio di
benvenuto che riporta l'età.

### Vincoli
- `anno_corrente >= anno_nascita`: l'età non può essere negativa
- Giorno compreso tra 1 e 31, mese tra 1 e 12
- Nessuno di questi vincoli viene verificato dal programma: il controllo
  dei dati richiede `if`, introdotto nel capitolo 02

### Assunzioni
- L'età si calcola per differenza di anni interi, senza controllare se il
  compleanno di quest'anno è già passato (approssimazione accettabile per
  un esempio introduttivo)
- Per chi è nato nell'anno corrente l'età risulta 0; i mesi non si gestiscono
- L'utente inserisce valori numerici validi

### Variabili di supporto

| Variabile | Tipo  | Significato                                    |
|-----------|-------|------------------------------------------------|
| `eta`     | `int` | Età calcolata come `anno_corrente − anno_nascita` |

Non si usano array né stringhe: tutti i dati sono interi, nel rispetto
dei vincoli del capitolo 01-introduzione.

### Algoritmo in linguaggio naturale
1. Acquisire giorno, mese e anno di nascita.
2. Acquisire l'anno corrente.
3. Calcolare `eta = anno_corrente − anno_nascita`.
4. Stampare il riepilogo: la data con `%02d` per giorno e mese, l'anno
   corrente, l'età e il messaggio di benvenuto.

## 3. Casi di test

Per ogni caso si esegue il programma con l'input indicato e si confronta
quanto stampato con l'output atteso.

### Test 1 – Utente adulto (caso tipico)
- **Input:** giorno_nascita = 15, mese_nascita = 6, anno_nascita = 1990,
  anno_corrente = 2024
- **Valori intermedi attesi:** `eta` = 2024 − 1990 = 34
- **Output atteso:**
```
--- Riepilogo ---
Data di nascita: 15/06/1990
Anno corrente:   2024
Eta' stimata:    34 anni

Benvenuto! Hai circa 34 anni.
```

### Test 2 – Nato nell'anno corrente (età 0)
- **Cosa si verifica:** il caso limite in cui le due date hanno lo stesso anno
- **Input:** giorno_nascita = 3, mese_nascita = 1, anno_nascita = 2024,
  anno_corrente = 2024
- **Valori intermedi attesi:** `eta` = 2024 − 2024 = 0
- **Output atteso:**
```
--- Riepilogo ---
Data di nascita: 03/01/2024
Anno corrente:   2024
Eta' stimata:    0 anni

Benvenuto! Hai circa 0 anni.
```

### Test 3 – Giorno e mese con una sola cifra
- **Cosa si verifica:** la formattazione `%02d` aggiunge lo zero iniziale
- **Input:** giorno_nascita = 5, mese_nascita = 3, anno_nascita = 2001,
  anno_corrente = 2025
- **Valori intermedi attesi:** `eta` = 2025 − 2001 = 24
- **Output atteso:**
```
--- Riepilogo ---
Data di nascita: 05/03/2001
Anno corrente:   2025
Eta' stimata:    24 anni

Benvenuto! Hai circa 24 anni.
```
