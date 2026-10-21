# Analisi – 040-problema-scheda-studente.c

## 1. Problema
L'utente inserisce i dati numerici di uno studente (matricola, anno di corso,
tre voti di esame, voto di laurea). Il programma calcola la media dei tre voti
e stampa una scheda formattata con colonne allineate.

## 2. Analisi

### Input

| Variabile     | Tipo     | Significato                    |
|---------------|----------|--------------------------------|
| `matricola`   | `int`    | Numero di matricola            |
| `anno_corso`  | `int`    | Anno di corso (1–5)            |
| `voto1`       | `int`    | Voto primo esame (18–30)       |
| `voto2`       | `int`    | Voto secondo esame (18–30)     |
| `voto3`       | `int`    | Voto terzo esame (18–30)       |
| `voto_laurea` | `double` | Voto di laurea (66.0–110.0)    |

### Output
Una scheda con la matricola su sette cifre (`%07d`), l'anno di corso,
i tre voti, la media con due decimali e il voto di laurea con un decimale,
in colonne allineate.

### Vincoli
- I voti d'esame sono compresi tra 18 e 30
- Il voto di laurea è compreso tra 66 e 110
- La matricola ha al massimo 7 cifre
- I vincoli non vengono verificati dal programma

### Assunzioni
- I valori inseriti sono coerenti con la realtà universitaria italiana

### Variabili di supporto

| Variabile    | Tipo     | Significato                         |
|--------------|----------|-------------------------------------|
| `media_voti` | `double` | Media aritmetica dei tre voti       |

La divisione per `3.0` (reale) garantisce un risultato in virgola mobile:
con `3` intero la parte decimale andrebbe persa.

### Algoritmo in linguaggio naturale
1. Acquisire matricola, anno di corso, tre voti e voto di laurea.
2. Calcolare `media_voti = (voto1 + voto2 + voto3) / 3.0`.
3. Stampare la scheda con tutti i dati e la media.

## 3. Casi di test

Per ogni caso si esegue il programma con l'input indicato e si confronta
quanto stampato con l'output atteso.

### Test 1 – Studente con buoni voti (caso tipico)
- **Input:** matricola = 12345, anno_corso = 2, voto1 = 28, voto2 = 30,
  voto3 = 27, voto_laurea = 105.5
- **Valori intermedi attesi:** media_voti = 85 / 3.0 = 28.33…
- **Output atteso:**
```
============================================
  SCHEDA STUDENTE
============================================
  Matricola:      0012345
  Anno di corso:  2° anno
--------------------------------------------
  Voto esame 1:    28 / 30
  Voto esame 2:    30 / 30
  Voto esame 3:    27 / 30
  Media:           28.33 / 30
--------------------------------------------
  Voto di laurea:  105.5 / 110
============================================
```

### Test 2 – Voti minimi
- **Cosa si verifica:** i valori al limite inferiore degli intervalli
- **Input:** matricola = 1, anno_corso = 1, voto1 = 18, voto2 = 18,
  voto3 = 18, voto_laurea = 66.0
- **Valori intermedi attesi:** media_voti = 54 / 3.0 = 18.00
- **Output atteso (righe che cambiano):**
```
  Voto esame 1:    18 / 30
  Voto esame 2:    18 / 30
  Voto esame 3:    18 / 30
  Media:           18.00 / 30
  Voto di laurea:   66.0 / 110
```

### Test 3 – Matricola di sette cifre
- **Cosa si verifica:** la matricola occupa esattamente la larghezza `%07d`,
  senza zeri iniziali
- **Input:** matricola = 9876543, anno_corso = 3, voto1 = 25, voto2 = 29,
  voto3 = 22, voto_laurea = 98.0
- **Valori intermedi attesi:** media_voti = 76 / 3.0 = 25.33…
- **Output atteso (righe che cambiano):**
```
  Matricola:      9876543
  Media:           25.33 / 30
```
