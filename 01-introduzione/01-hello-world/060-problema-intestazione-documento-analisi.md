# Analisi – 060-problema-intestazione-documento.c

## 1. Problema
Il programma acquisisce i dati identificativi di un documento scolastico
(anno scolastico, classe, sezione, numero progressivo, data di emissione)
e produce un'intestazione formattata. L'anno finale del biennio è calcolato
automaticamente. Non si usano stringhe né array.

## 2. Analisi generale e struttura dati

| Variabile           | Tipo  | Significato                                        |
|---------------------|-------|----------------------------------------------------|
| `anno_inizio`       | `int` | Prima metà dell'anno scolastico (es. 2024)         |
| `anno_fine`         | `int` | Seconda metà, calcolata come anno_inizio + 1       |
| `numero_classe`     | `int` | Numero della classe (1–5)                          |
| `sezione`           | `int` | Sezione come numero intero (1=A, 2=B, 3=C, …)     |
| `numero_documento`  | `int` | Numero progressivo del documento nell'anno         |
| `giorno`            | `int` | Giorno della data di emissione                     |
| `mese`              | `int` | Mese della data di emissione                       |
| `anno`              | `int` | Anno della data di emissione                       |

La sezione è trattata come intero perché le lettere (char[]) non sono ancora
state introdotte. Questa è una semplificazione esplicita e didatticamente utile.

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Documento standard di inizio anno

**a) Input**
- anno_inizio = 2024, numero_classe = 3, sezione = 1
- numero_documento = 1
- giorno = 15, mese = 10, anno = 2024

**b) Output**
```
====================================================
  ISTITUTO TECNICO INDUSTRIALE "G. MARCONI"
====================================================
  Anno scolastico: 2024 / 2025
  Classe:          3^  Sezione: 1
  Materia:         Informatica e Sistemi
  Documento n.:    001
  Data:            15 / 10 / 2024
====================================================
  Verifica scritta - Primo quadrimestre
====================================================
```

**c) Variabili di supporto**
- `anno_fine` = 2024 + 1 = 2025 (calcolato, non inserito)

**d) Vincoli**
- `numero_documento` è formattato con `%03d` (tre cifre con zeri iniziali)
- `anno_fine` è sempre `anno_inizio + 1`

**e) Assunzioni**
- L'anno scolastico è sempre su due anni consecutivi
- La sezione è un intero positivo

**f) Algoritmo in linguaggio naturale**
1. Acquisire anno_inizio, classe, sezione, numero documento, data
2. Calcolare anno_fine = anno_inizio + 1
3. Stampare l'intestazione con i dati formattati

---

### Caso d'uso 2 – Documento di fine anno, numero alto

**a) Input**
- anno_inizio = 2024, numero_classe = 5, sezione = 3
- numero_documento = 42
- giorno = 5, mese = 6, anno = 2025

**b) Output**
```
  Anno scolastico: 2024 / 2025
  Classe:          5^  Sezione: 3
  Documento n.:    042
  Data:            05 / 06 / 2025
```

**c) Variabili di supporto**
- `anno_fine` = 2025

**d) Vincoli**
- `%02d` per giorno e mese garantisce sempre due cifre

**e) Assunzioni**
- Identiche al caso d'uso 1

**f) Algoritmo in linguaggio naturale**
- Identico al caso d'uso 1

---

### Caso d'uso 3 – Primo documento dell'anno, sezione B

**a) Input**
- anno_inizio = 2025, numero_classe = 1, sezione = 2
- numero_documento = 1
- giorno = 2, mese = 9, anno = 2025

**b) Output**
```
  Anno scolastico: 2025 / 2026
  Classe:          1^  Sezione: 2
  Documento n.:    001
  Data:            02 / 09 / 2025
```

**c) Variabili di supporto**
- `anno_fine` = 2026

**d) Vincoli**
- `%03d` per numero_documento mostra sempre tre cifre (001, 042, 100)

**e) Assunzioni**
- Il numero di documento non supera 999

**f) Algoritmo in linguaggio naturale**
- Identico al caso d'uso 1
