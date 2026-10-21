# Analisi – 060-problema-dati-veicolo.c

## 1. Problema
L'utente inserisce i dati numerici di un veicolo (anno di immatricolazione,
cilindrata, potenza in kW, numero di porte, prezzo di listino). Il programma
calcola l'anzianità e converte la potenza in CV, stampando una scheda tecnica
formattata.

## 2. Analisi

### Input

| Variabile               | Tipo     | Significato                       |
|-------------------------|----------|-----------------------------------|
| `anno_immatricolazione` | `int`    | Anno di prima immatricolazione    |
| `cilindrata_cc`         | `int`    | Cilindrata in centimetri cubici   |
| `potenza_kw`            | `double` | Potenza del motore in kilowatt    |
| `num_porte`             | `int`    | Numero di porte                   |
| `prezzo_listino`        | `double` | Prezzo di listino in EUR          |

### Output
Una scheda tecnica con anno di immatricolazione e anzianità, cilindrata,
potenza in kW e in CV (un decimale), numero di porte e prezzo di listino
(due decimali), in colonne allineate.

### Vincoli
- `anno_immatricolazione <= ANNO_CORRENTE`
- `potenza_kw > 0`
- Le potenze non superano 9999.9, la capienza della larghezza `%8.1f`
- I vincoli non vengono verificati dal programma

### Assunzioni
- L'anno corrente è fisso a 2024 tramite costante `#define`
- I valori inseriti sono realistici per un veicolo stradale

### Variabili di supporto

| Variabile        | Tipo     | Significato                          |
|------------------|----------|--------------------------------------|
| `anzianita_anni` | `int`    | Anni trascorsi dall'immatricolazione |
| `potenza_cv`     | `double` | Potenza convertita in cavalli vapore |

Costanti: `ANNO_CORRENTE = 2024`, `KW_IN_CV = 1.35962`

### Algoritmo in linguaggio naturale
1. Acquisire anno, cilindrata, potenza in kW, porte e prezzo.
2. Calcolare `anzianita_anni = ANNO_CORRENTE − anno_immatricolazione`.
3. Calcolare `potenza_cv = potenza_kw × KW_IN_CV`.
4. Stampare la scheda tecnica.

## 3. Casi di test

Per ogni caso si esegue il programma con l'input indicato e si confronta
quanto stampato con l'output atteso.

### Test 1 – Veicolo recente (caso tipico)
- **Input:** anno_immatricolazione = 2022, cilindrata_cc = 1200,
  potenza_kw = 66.0, num_porte = 5, prezzo_listino = 18500.00
- **Valori intermedi attesi:** anzianita_anni = 2; potenza_cv = 89.73…
- **Output atteso:**
```
==========================================
  SCHEDA TECNICA VEICOLO
==========================================
  Anno immatricolazione: 2022
  Anzianita':            2 anni
------------------------------------------
  Cilindrata:        1200 cc
  Potenza:             66.0 kW
  Potenza:             89.7 CV
  Porte:                  5
------------------------------------------
  Prezzo listino:  18500.00 EUR
==========================================
```

### Test 2 – Veicolo d'epoca
- **Cosa si verifica:** anzianità a due cifre
- **Input:** anno_immatricolazione = 1975, cilindrata_cc = 1600,
  potenza_kw = 55.0, num_porte = 2, prezzo_listino = 12000.00
- **Valori intermedi attesi:** anzianita_anni = 49; potenza_cv = 74.78…
- **Output atteso (righe che cambiano):**
```
  Anno immatricolazione: 1975
  Anzianita':            49 anni
  Potenza:             55.0 kW
  Potenza:             74.8 CV
```

### Test 3 – Veicolo ad alte prestazioni
- **Cosa si verifica:** potenze a tre cifre nella larghezza `%8.1f`
- **Input:** anno_immatricolazione = 2023, cilindrata_cc = 2998,
  potenza_kw = 250.0, num_porte = 4, prezzo_listino = 75000.00
- **Valori intermedi attesi:** anzianita_anni = 1; potenza_cv = 339.905
- **Output atteso (righe che cambiano):**
```
  Cilindrata:        2998 cc
  Potenza:            250.0 kW
  Potenza:            339.9 CV
  Prezzo listino:  75000.00 EUR
```
