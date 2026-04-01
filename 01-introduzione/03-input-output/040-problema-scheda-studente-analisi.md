# Analisi – 040-problema-scheda-studente.c

## 1. Problema
L'utente inserisce i dati numerici di uno studente (matricola, anno di corso,
tre voti di esame, voto di laurea). Il programma calcola la media dei tre voti
e stampa una scheda formattata con colonne allineate.

## 2. Analisi generale e struttura dati

| Variabile       | Tipo     | Significato                                  |
|-----------------|----------|----------------------------------------------|
| `matricola`     | `int`    | Numero di matricola (stampato con 7 cifre)   |
| `anno_corso`    | `int`    | Anno di corso (1–5)                          |
| `voto1`         | `int`    | Voto primo esame (18–30)                     |
| `voto2`         | `int`    | Voto secondo esame (18–30)                   |
| `voto3`         | `int`    | Voto terzo esame (18–30)                     |
| `voto_laurea`   | `double` | Voto di laurea (66.0–110.0)                  |
| `media_voti`    | `double` | Media calcolata dei tre voti interi           |

La divisione per `3.0` (reale) garantisce un risultato in virgola mobile.

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Studente con buoni voti

**a) Input**
- matricola = 12345, anno_corso = 2
- voto1 = 28, voto2 = 30, voto3 = 27
- voto_laurea = 105.5

**b) Output**
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

**c) Variabili di supporto**
- media_voti = (28 + 30 + 27) / 3.0 = 85 / 3.0 = 28.33...

**d) Vincoli**
- I voti devono essere compresi tra 18 e 30 (non validati)
- Il voto di laurea tra 66 e 110 (non validato)

**e) Assunzioni**
- I valori inseriti sono coerenti con la realtà universitaria italiana

**f) Algoritmo in linguaggio naturale**
1. Acquisire matricola, anno di corso, tre voti, voto di laurea
2. Calcolare media = (voto1 + voto2 + voto3) / 3.0
3. Stampare la scheda con tutti i dati e la media

---

### Caso d'uso 2 – Voti minimi

**a) Input**
- matricola = 1, anno_corso = 1
- voto1 = 18, voto2 = 18, voto3 = 18
- voto_laurea = 66.0

**b) Output**
```
  Voto esame 1:    18 / 30
  Voto esame 2:    18 / 30
  Voto esame 3:    18 / 30
  Media:           18.00 / 30
  Voto di laurea:   66.0 / 110
```

**c) Variabili di supporto**
- media_voti = 54 / 3.0 = 18.00

**d) Vincoli**
- Identici al caso d'uso 1

**e) Assunzioni**
- Identiche al caso d'uso 1

**f) Algoritmo in linguaggio naturale**
- Identico al caso d'uso 1

---

### Caso d'uso 3 – Matricola con molte cifre

**a) Input**
- matricola = 9876543, anno_corso = 3
- voto1 = 25, voto2 = 29, voto3 = 22
- voto_laurea = 98.0

**b) Output**
```
  Matricola:      9876543
  Media:           25.33 / 30
```

**c) Variabili di supporto**
- media_voti = (25 + 29 + 22) / 3.0 = 76 / 3.0 = 25.33...

**d) Vincoli**
- Con 7 cifre la matricola occupa esattamente la larghezza `%07d`

**e) Assunzioni**
- La matricola non supera 7 cifre

**f) Algoritmo in linguaggio naturale**
- Identico al caso d'uso 1
