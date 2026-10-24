# Analisi – 040-problema-rinnovo-abbonamenti.c

## 1. Problema

La segreteria gestisce gli abbonamenti al bus: rinnovi da 1 a 12 mesi e
avvisi per gli abbonamenti scaduti o in scadenza entro 15 giorni. Le
funzioni sulle date ricevono l'indirizzo di una `Data`, che può essere la
data di oggi o la scadenza dentro un abbonamento (`&ab->scadenza`).

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `oggi` | `Data` | Data di oggi `gg/mm/aaaa` |
| `comando` | `char` | `R numero mesi` rinnovo, `A` avvisi, `S` situazione, `Q` fine (anche minuscoli) |
| `numero`, `mesi` | `char[8]`, `int` | Abbonamento e durata del rinnovo |
| elenco | nel sorgente | A-1001 Rossi Elena L3 31/1/2026; A-1002 Greco Paolo L7 15/1/2026; A-1003 Costa Marta L3 30/6/2026; A-1004 Villa Sara L1 2/2/2026 |

### Output

- Riga di un abbonamento: numero, intestatario, linea, scadenza e stato
  `SCADUTO da N giorni`, `in scadenza tra N giorni` o `valido`.
- `R`: la riga aggiornata, oppure `Durata non valida: da 1 a 12 mesi.`,
  `Abbonamento X inesistente.`, `Dati non validi.`
- `A`: solo gli abbonamenti scaduti o in scadenza; `S`: tutti.
- `Data non valida.` se la data di oggi è errata (il programma termina).

### Vincoli

- In scadenza: entro 15 giorni (compreso); scaduto: scadenza già passata.
- Rinnovo: se l'abbonamento è scaduto si parte da oggi, altrimenti dalla
  scadenza; si aggiungono i mesi e, se il giorno non esiste nel nuovo
  mese, si usa l'ultimo giorno (31/1 + 1 mese = 28/2).
- Data di oggi: anno dal 2000, mese 1-12, giorno compatibile.
- Un comando per riga; i dati non validi non interrompono il programma. A
  fine input termina come con `Q`.

### Assunzioni

- Singolare e plurale per "giorno".

### Variabili di supporto

| Tipo definito | Definizione | Significato |
|---------------|-------------|-------------|
| `Data` | `typedef struct { int giorno; int mese; int anno; } Data;` | Una data |
| `Abbonamento` | `typedef struct { char numero[8]; char intestatario[20]; char linea[4]; Data scadenza; } Abbonamento;` | Abbonamento con la scadenza annidata |

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `elenco` | `Abbonamento[4]` | Abbonamenti |
| `trovato` | `int` | Indice dell'abbonamento (−1 = inesistente) |
| `giorni` | `int` | Giorni fino alla scadenza |
| `PREAVVISO` | `#define` | 15 giorni |

| Funzione | Compito |
|----------|---------|
| `bisestile`, `giorni_nel_mese` | Calendario |
| `numero_giorno(d)` | Giorni dal 1/1/2000 |
| `giorni_tra(da, a)` | Differenza in giorni (positiva se `a` è dopo) |
| `aggiungi_mesi(d, mesi)` | Sposta la data di alcuni mesi |
| `rinnova(ab, mesi, oggi)` | Rinnova l'abbonamento; 1 se la durata è valida |
| `stampa(ab, oggi)` | Riga con lo stato |
| `svuota_riga` | Scarta i caratteri rimasti sulla riga |

### Algoritmo in linguaggio naturale

1. Leggere e controllare la data di oggi; se errata terminare.
2. Finché il comando non è `Q`:
   1. leggere il comando in maiuscolo;
   2. `R`: leggere numero e mesi, cercare l'abbonamento, rinnovarlo e
      stamparlo, o segnalare l'errore;
   3. `A`/`S`: stampare gli abbonamenti (con `A` solo se scaduti o in
      scadenza);
   4. scartare il resto della riga.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe).

### Test 1 – 20 gennaio 2026

- **Cosa si verifica:** stati, avvisi, rinnovo di uno scaduto (da oggi) e
  di uno valido a fine mese, errori.
- **Input:** `20/1/2026`, `S`, `A`, `R A-1002 1`, `r A-1001 1`,
  `R A-1003 13`, `R A-9999 2`, `R A-1004 x`, `A`, `X`, `Q`
- **Output atteso:**
  ```
    A-1001 Rossi Elena  L3  scadenza 31/01/2026  in scadenza tra 11 giorni
    A-1002 Greco Paolo  L7  scadenza 15/01/2026  SCADUTO da 5 giorni
    A-1003 Costa Marta  L3  scadenza 30/06/2026  valido
    A-1004 Villa Sara   L1  scadenza 02/02/2026  in scadenza tra 13 giorni
    A-1001 Rossi Elena  L3  scadenza 31/01/2026  in scadenza tra 11 giorni
    A-1002 Greco Paolo  L7  scadenza 15/01/2026  SCADUTO da 5 giorni
    A-1004 Villa Sara   L1  scadenza 02/02/2026  in scadenza tra 13 giorni
    A-1002 Greco Paolo  L7  scadenza 20/02/2026  valido
    A-1001 Rossi Elena  L3  scadenza 28/02/2026  valido
    Durata non valida: da 1 a 12 mesi.
    Abbonamento A-9999 inesistente.
    Dati non validi.
    A-1004 Villa Sara   L1  scadenza 02/02/2026  in scadenza tra 13 giorni
    Comando sconosciuto.
  ```

### Test 2 – Data di oggi non valida

- **Input:** `31/13/2026` (poi `29/2/2026`, poi `abc`)
- **Output atteso:** `Data non valida.` in tutti i casi (il 2026 non è
  bisestile).
