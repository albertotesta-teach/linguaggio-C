# Analisi – 040-problema-prestiti-biblioteca.c

## 1. Problema

La biblioteca scolastica registra per ogni prestito il libro, lo studente
e tre date: inizio, scadenza e restituzione (anno 0 se il libro non è
tornato). Il programma legge la data di oggi, la controlla e stampa lo
stato di ogni prestito: restituito (con l'eventuale ritardo), in corso con
i giorni mancanti, in scadenza oggi, oppure in ritardo con la multa di
0.20 euro al giorno, al massimo 5 euro. Le date sono struct `Data` dentro
la struct `Prestito`.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `oggi` | `Data` | Data di oggi nel formato `gg/mm/aaaa` |
| prestiti | nel sorgente | 5 prestiti (vedi tabella) |

| Libro | Studente | Scadenza | Restituzione |
|-------|----------|----------|--------------|
| Il barone rampante | Rossi Elena | 3/12/2025 | 28/11/2025 |
| Fahrenheit 451 | Greco Paolo | 10/12/2025 | — |
| Io, robot | Costa Marta | 17/12/2025 | — |
| La luna e i falo' | Villa Sara | 19/11/2025 | — |
| Se questo e' un uomo | Neri Luca | 1/12/2025 | 5/12/2025 |

### Output

- Per ogni prestito: titolo, studente, scadenza e lo stato:
  `restituito il GG/MM` (con `con N giorni di ritardo` se dopo la
  scadenza), `in corso, mancano N giorni` (`manca 1 giorno`),
  `scade oggi`, oppure `IN RITARDO di N giorni, multa M euro`.
- `Data non valida.`

### Vincoli

- Ai campi annidati si accede con due punti:
  `prestiti[i].scadenza.giorno`.
- Le differenze tra date si calcolano con `numero_giorno` (giorni dal
  1/1/2000), che tiene conto degli anni bisestili.
- Data valida: anno dal 2000, mese 1-12, giorno compatibile con il mese.
- Multa = 0.20 × giorni, al massimo 5.00 euro.
- Singolare e plurale per "giorno".

### Assunzioni

- La data di oggi non è precedente ai prestiti.

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Data` | `typedef struct { int giorno; int mese; int anno; } Data;` | Una data |
| `Prestito` | `typedef struct { char titolo[28]; char studente[20]; Data inizio; Data scadenza; Data restituzione; } Prestito;` | Un prestito con le sue tre date |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `prestiti` | `Prestito[5]` | Array di struct annidate |
| `oggi` | `Data` | Data letta |
| `giorni` | `int` | Differenza in giorni |

| Funzione | Compito |
|----------|---------|
| `bisestile(anno)` | 1 se l'anno è bisestile |
| `giorni_nel_mese(mese, anno)` | Giorni del mese |
| `data_valida(d)` | Controllo della data |
| `numero_giorno(d)` | Giorni trascorsi dal 1/1/2000 |
| `multa(giorni)` | Multa con il tetto massimo |

### Algoritmo in linguaggio naturale

1. Leggere la data di oggi; se non valida stamparlo e terminare.
2. Per ogni prestito:
   1. se è stato restituito, calcolare restituzione − scadenza e stampare
      l'eventuale ritardo;
   2. altrimenti calcolare oggi − scadenza: negativo → giorni mancanti,
      zero → scade oggi, positivo → ritardo e multa.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – Metà dicembre

- **Cosa si verifica:** tutti gli stati e il tetto della multa.
- **Input:** `15/12/2025`
- **Valori intermedi attesi:** Greco 5 giorni × 0.20 = 1.00; Villa 26
  giorni × 0.20 = 5.20 → 5.00.
- **Output atteso:**
  ```
  Il barone rampante    Rossi Elena  scad. 03/12  restituito il 28/11
  Fahrenheit 451        Greco Paolo  scad. 10/12  IN RITARDO di 5 giorni, multa 1.00 euro
  Io, robot             Costa Marta  scad. 17/12  in corso, mancano 2 giorni
  La luna e i falo'     Villa Sara   scad. 19/11  IN RITARDO di 26 giorni, multa 5.00 euro
  Se questo e' un uomo  Neri Luca    scad. 01/12  restituito il 05/12 con 4 giorni di ritardo
  ```

### Test 2 – Scadenza oggi e singolare

- **Input:** `10/12/2025`; poi `16/12/2025`
- **Output atteso:** `Fahrenheit 451 ... scade oggi`; poi
  `Io, robot ... in corso, manca 1 giorno`.

### Test 3 – Cambio d'anno

- **Cosa si verifica:** il conteggio dei giorni attraverso il 31 dicembre.
- **Input:** `28/2/2026`
- **Output atteso:** Greco `IN RITARDO di 80 giorni`, Costa `73 giorni`,
  Villa `101 giorni`, tutti con `multa 5.00 euro`.

### Test 4 – Data non valida

- **Input:** `30/2/2025` (poi `abc`)
- **Output atteso:** `Data non valida.`
