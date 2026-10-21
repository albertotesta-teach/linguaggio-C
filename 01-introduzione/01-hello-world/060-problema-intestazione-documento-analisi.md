# Analisi – 060-problema-intestazione-documento.c

## 1. Problema
Il programma acquisisce i dati identificativi di un documento scolastico
(anno scolastico, classe, sezione, numero progressivo, data di emissione)
e produce un'intestazione formattata. L'anno finale del biennio è calcolato
automaticamente. Non si usano stringhe né array.

## 2. Analisi

### Input

| Variabile           | Tipo  | Significato                                        |
|---------------------|-------|----------------------------------------------------|
| `anno_inizio`       | `int` | Prima metà dell'anno scolastico (es. 2024)         |
| `numero_classe`     | `int` | Numero della classe (1–5)                          |
| `sezione`           | `int` | Sezione come numero intero (1=A, 2=B, 3=C, …)      |
| `numero_documento`  | `int` | Numero progressivo del documento nell'anno         |
| `giorno`            | `int` | Giorno della data di emissione                     |
| `mese`              | `int` | Mese della data di emissione                       |
| `anno`              | `int` | Anno della data di emissione                       |

### Output
Un'intestazione delimitata da righe di `=` con il nome dell'istituto,
l'anno scolastico nella forma `inizio / fine`, classe e sezione, la materia
(testo fisso), il numero del documento su tre cifre e la data con giorno e
mese su due cifre.

### Vincoli
- La classe è compresa tra 1 e 5 e la sezione è un intero positivo
- Il numero di documento non supera 999 (deve stare in tre cifre)
- La data di emissione è una data valida
- I vincoli non vengono verificati dal programma

### Assunzioni
- L'anno scolastico si estende sempre su due anni consecutivi
- La sezione è trattata come intero perché i caratteri e le stringhe non
  sono ancora stati introdotti: è una semplificazione esplicita

### Variabili di supporto

| Variabile   | Tipo  | Significato                                     |
|-------------|-------|-------------------------------------------------|
| `anno_fine` | `int` | Seconda metà dell'anno scolastico, `anno_inizio + 1` |

### Algoritmo in linguaggio naturale
1. Acquisire anno di inizio, classe, sezione, numero del documento e data.
2. Calcolare `anno_fine = anno_inizio + 1`.
3. Stampare l'intestazione, con `%03d` per il numero del documento e
   `%02d` per giorno e mese.

## 3. Casi di test

Per ogni caso si esegue il programma con l'input indicato e si confronta
quanto stampato con l'output atteso.

### Test 1 – Documento di inizio anno (caso tipico)
- **Input:** anno_inizio = 2024, numero_classe = 3, sezione = 1,
  numero_documento = 1, giorno = 15, mese = 10, anno = 2024
- **Valori intermedi attesi:** `anno_fine` = 2025
- **Output atteso:**
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

### Test 2 – Documento di fine anno con numero a due cifre
- **Cosa si verifica:** `%03d` su un numero a due cifre e `%02d` su giorno
  e mese a una cifra
- **Input:** anno_inizio = 2024, numero_classe = 5, sezione = 3,
  numero_documento = 42, giorno = 5, mese = 6, anno = 2025
- **Valori intermedi attesi:** `anno_fine` = 2025
- **Output atteso (righe che cambiano):**
```
  Anno scolastico: 2024 / 2025
  Classe:          5^  Sezione: 3
  Documento n.:    042
  Data:            05 / 06 / 2025
```

### Test 3 – Primo documento di un nuovo anno scolastico
- **Cosa si verifica:** il calcolo di `anno_fine` con un anno di inizio diverso
- **Input:** anno_inizio = 2025, numero_classe = 1, sezione = 2,
  numero_documento = 1, giorno = 2, mese = 9, anno = 2025
- **Valori intermedi attesi:** `anno_fine` = 2026
- **Output atteso (righe che cambiano):**
```
  Anno scolastico: 2025 / 2026
  Classe:          1^  Sezione: 2
  Documento n.:    001
  Data:            02 / 09 / 2025
```
