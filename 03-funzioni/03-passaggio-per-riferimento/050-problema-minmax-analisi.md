# Analisi – 050-problema-minmax.c

## 1. Problema
Un laboratorio raccoglie cinque misurazioni di temperatura durante la giornata
e vuole conoscere il valore minimo, il massimo, la media e l'escursione termica
(differenza tra massimo e minimo). La funzione `calcola_minmax` deve produrre
due risultati (min e max) in una sola chiamata: il passaggio per riferimento
permette di scrivere entrambi i valori direttamente nelle variabili del
chiamante senza dover eseguire due scansioni separate.

## 2. Analisi

### Input
Nessun input da tastiera: le cinque misurazioni di ogni stazione sono
passate come argomenti a `stampa_report` nel `main`.

| Parametro | Tipo | Descrizione |
|---|---|---|
| `v1`…`v5` | double | Cinque misurazioni di temperatura (°C) |

### Output
Per ogni stazione: le cinque misurazioni, poi minimo, massimo, media ed
escursione termica, tutti con un decimale.

### Vincoli
- `min` e `max` sono parametri di uscita: `calcola_minmax` riceve due
  puntatori validi (non `NULL`) e scrive i risultati nelle variabili del
  chiamante
- Il minimo e il massimo partono dal primo valore, poi ogni altro valore
  li aggiorna se è più piccolo o più grande
- L'escursione è `max − min` e non è mai negativa

### Assunzioni
- I valori sono temperature fisicamente plausibili
- I cinque valori si passano come parametri separati, perché gli array non
  sono ancora disponibili

### Variabili di supporto

| Variabile | Tipo | Descrizione |
|---|---|---|
| `min`, `max` | double | Locali a `stampa_report`, scritte da `calcola_minmax` |
| `media` | double | Media aritmetica restituita da `calcola_media` |
| `escursione` | double | `max − min` |

| Funzione | Firma | Descrizione |
|---|---|---|
| `calcola_minmax` | `void(double×5, double*, double*)` | Trova min e max tra cinque valori |
| `calcola_media` | `double(double×5)` | Media aritmetica |
| `stampa_report` | `void(double×5)` | Report completo della stazione |

### Algoritmo in linguaggio naturale
1. Stampare le cinque misurazioni.
2. Chiamare `calcola_minmax` passando gli indirizzi di `min` e `max`:
   a. porre `*min = *max = v1`;
   b. per ciascuno dei valori da `v2` a `v5`: se è minore di `*min`
      aggiornare `*min`, se è maggiore di `*max` aggiornare `*max`.
3. Calcolare la media con `calcola_media`.
4. Calcolare l'escursione come `max − min`.
5. Stampare minimo, massimo, media ed escursione.

## 3. Casi di test

Il `main` esegue il report di tre stazioni: si esegue il programma una volta
e si confronta ogni blocco con l'output atteso.

### Test 1 – Stazione A (città)
- **Input:** 18.5, 22.0, 24.3, 21.5, 19.0
- **Output atteso:**
```
Minimo:      18.5 C
Massimo:     24.3 C
Media:       21.1 C
Escursione:  5.8 C
```

### Test 2 – Stazione B (montagna)
- **Cosa si verifica:** il minimo è il primo valore, quindi non viene mai
  aggiornato
- **Input:** 4.0, 8.5, 11.0, 9.0, 5.5
- **Output atteso:** minimo 4.0, massimo 11.0, media 7.6, escursione 7.0

### Test 3 – Stazione C (costa)
- **Input:** 21.0, 23.5, 25.0, 24.0, 22.0
- **Output atteso:** minimo 21.0, massimo 25.0, media 23.1, escursione 4.0

Test aggiuntivi da eseguire aggiungendo una chiamata a `stampa_report` nel
`main`:

### Test 4 – Tutti i valori uguali
- **Cosa si verifica:** nessun confronto aggiorna min e max
- **Input:** 20.0, 20.0, 20.0, 20.0, 20.0
- **Output atteso:** minimo 20.0, massimo 20.0, media 20.0, escursione 0.0

### Test 5 – Valori negativi
- **Cosa si verifica:** i confronti funzionano anche con i negativi
- **Input:** -8.0, -3.5, 1.0, -1.5, -6.0
- **Output atteso:** minimo -8.0, massimo 1.0, media -3.6, escursione 9.0
