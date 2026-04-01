# Analisi – 060-problema-dati-veicolo.c

## 1. Problema
L'utente inserisce i dati numerici di un veicolo (anno di immatricolazione,
cilindrata, potenza in kW, numero di porte, prezzo di listino). Il programma
calcola l'anzianità e converte la potenza in CV, stampando una scheda tecnica
formattata.

## 2. Analisi generale e struttura dati

| Variabile                  | Tipo     | Significato                           |
|----------------------------|----------|---------------------------------------|
| `anno_immatricolazione`    | `int`    | Anno di prima immatricolazione        |
| `cilindrata_cc`            | `int`    | Cilindrata in centimetri cubici       |
| `potenza_kw`               | `double` | Potenza del motore in kilowatt        |
| `num_porte`                | `int`    | Numero di porte                       |
| `prezzo_listino`           | `double` | Prezzo di listino in EUR              |
| `anzianita_anni`           | `int`    | Anni trascorsi dall'immatricolazione  |
| `potenza_cv`               | `double` | Potenza convertita in cavalli vapore  |

Costanti: `ANNO_CORRENTE = 2024`, `KW_IN_CV = 1.35962`

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Veicolo recente

**a) Input**
- anno_immatricolazione = 2022, cilindrata_cc = 1200
- potenza_kw = 66.0, num_porte = 5, prezzo_listino = 18500.00

**b) Output**
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

**c) Variabili di supporto**
- anzianita_anni = 2024 - 2022 = 2
- potenza_cv = 66.0 × 1.35962 = 89.73...

**d) Vincoli**
- `anno_immatricolazione <= ANNO_CORRENTE` (non validato)
- `potenza_kw > 0` (non validato)

**e) Assunzioni**
- L'anno corrente è fisso a 2024 tramite costante `#define`
- I valori inseriti sono realistici per un veicolo stradale

**f) Algoritmo in linguaggio naturale**
1. Acquisire anno, cilindrata, potenza kW, porte, prezzo
2. Calcolare anzianita = ANNO_CORRENTE - anno_immatricolazione
3. Calcolare potenza_cv = potenza_kw × KW_IN_CV
4. Stampare la scheda tecnica

---

### Caso d'uso 2 – Veicolo d'epoca

**a) Input**
- anno_immatricolazione = 1975, cilindrata_cc = 1600
- potenza_kw = 55.0, num_porte = 2, prezzo_listino = 12000.00

**b) Output**
```
  Anno immatricolazione: 1975
  Anzianita':            49 anni
  Potenza:             55.0 kW
  Potenza:             74.8 CV
```

**c) Variabili di supporto**
- anzianita_anni = 2024 - 1975 = 49
- potenza_cv = 55.0 × 1.35962 = 74.78...

**d) Vincoli**
- Identici al caso d'uso 1

**e) Assunzioni**
- Identiche al caso d'uso 1

**f) Algoritmo in linguaggio naturale**
- Identico al caso d'uso 1

---

### Caso d'uso 3 – Veicolo ad alte prestazioni

**a) Input**
- anno_immatricolazione = 2023, cilindrata_cc = 2998
- potenza_kw = 250.0, num_porte = 4, prezzo_listino = 75000.00

**b) Output**
```
  Cilindrata:        2998 cc
  Potenza:            250.0 kW
  Potenza:            339.9 CV
  Prezzo listino:  75000.00 EUR
```

**c) Variabili di supporto**
- anzianita_anni = 2024 - 2023 = 1
- potenza_cv = 250.0 × 1.35962 = 339.905

**d) Vincoli**
- La larghezza `%8.1f` è sufficiente per potenze fino a 9999.9 kW/CV

**e) Assunzioni**
- Identiche al caso d'uso 1

**f) Algoritmo in linguaggio naturale**
- Identico al caso d'uso 1
