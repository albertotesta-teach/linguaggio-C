# Analisi – 040-problema-saluto-personalizzato.c

## 1. Problema
L'utente inserisce la propria data di nascita (giorno, mese, anno) e l'anno
corrente. Il programma calcola l'età approssimata e stampa un riepilogo
formattato con un messaggio di benvenuto personalizzato.

## 2. Analisi generale e struttura dati

| Variabile        | Tipo  | Significato                                    |
|------------------|-------|------------------------------------------------|
| `giorno_nascita` | `int` | Giorno del mese di nascita (1–31)              |
| `mese_nascita`   | `int` | Mese di nascita (1–12)                         |
| `anno_nascita`   | `int` | Anno di nascita (es. 2005)                     |
| `anno_corrente`  | `int` | Anno corrente inserito dall'utente             |
| `eta`            | `int` | Età calcolata per differenza di anni           |

Non si usano array né stringhe: tutti i dati sono interi, nel rispetto
dei vincoli del capitolo 01-introduzione.

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Utente adulto

**a) Input**
- giorno_nascita = 15, mese_nascita = 6, anno_nascita = 1990
- anno_corrente = 2024

**b) Output**
```
--- Riepilogo ---
Data di nascita: 15/06/1990
Anno corrente:   2024
Eta' stimata:    34 anni

Benvenuto! Hai circa 34 anni.
```

**c) Variabili di supporto**
- `eta` = 2024 − 1990 = 34

**d) Vincoli**
- `anno_corrente >= anno_nascita` (l'età non può essere negativa)
- I valori di giorno e mese non vengono validati in questo esempio

**e) Assunzioni**
- Il calcolo dell'età è per differenza di anni interi; non si controlla
  se il compleanno di quest'anno è già passato (approssimazione accettabile
  per un esempio introduttivo)

**f) Algoritmo in linguaggio naturale**
1. Acquisire giorno, mese, anno di nascita
2. Acquisire anno corrente
3. Calcolare eta = anno_corrente − anno_nascita
4. Stampare il riepilogo con i dati e l'età calcolata

---

### Caso d'uso 2 – Utente molto giovane (neonato)

**a) Input**
- giorno_nascita = 3, mese_nascita = 1, anno_nascita = 2024
- anno_corrente = 2024

**b) Output**
```
--- Riepilogo ---
Data di nascita: 03/01/2024
Anno corrente:   2024
Eta' stimata:    0 anni

Benvenuto! Hai circa 0 anni.
```

**c) Variabili di supporto**
- `eta` = 2024 − 2024 = 0

**d) Vincoli**
- Il risultato 0 è corretto e atteso per chi è nato nell'anno corrente

**e) Assunzioni**
- Il valore 0 è accettabile come output; non si gestisce il caso "mesi"

**f) Algoritmo in linguaggio naturale**
- Identico al caso d'uso 1

---

### Caso d'uso 3 – Formattazione della data con zeri iniziali

**a) Input**
- giorno_nascita = 5, mese_nascita = 3, anno_nascita = 2001
- anno_corrente = 2025

**b) Output**
```
--- Riepilogo ---
Data di nascita: 05/03/2001
Anno corrente:   2025
Eta' stimata:    24 anni

Benvenuto! Hai circa 24 anni.
```

**c) Variabili di supporto**
- `eta` = 2025 − 2001 = 24

**d) Vincoli**
- La formattazione `%02d` garantisce sempre due cifre per giorno e mese

**e) Assunzioni**
- L'utente inserisce valori numerici validi (no controllo errori)

**f) Algoritmo in linguaggio naturale**
- Identico al caso d'uso 1; l'uso di `%02d` è automatico in printf
