# Analisi – 080-problema-turni-lavoro.c

## 1. Problema

Il titolare di un bar ha pianificato le ore di 5 dipendenti per i 7 giorni
della settimana. Deve verificare che ognuno lavori le ore del contratto,
abbia almeno un giorno di riposo, e che ogni giorno ci siano almeno 3
persone in servizio.

## 2. Analisi

### Input
Nessun input da tastiera: i dati sono inizializzati nel codice.

| Variabile   | Tipo       | Dimensione | Descrizione                                     |
|-------------|------------|------------|-------------------------------------------------|
| `ore`       | `int[][]`  | 5 × 7      | Ore previste per dipendente e giorno; 0 = riposo |
| `nomi`      | `char[][]` | 5 × 12     | Nomi, paralleli alle righe                      |
| `contratto` | `int[]`    | 5          | Ore settimanali da contratto, parallele alle righe |
| `giorni`    | `char[][]` | 7 × 4      | Sigle, parallele alle colonne                   |

### Output
- La tabella dei turni (`-` per i riposi) con totale e ore da contratto di
  ogni dipendente;
- per ogni dipendente: ore in linea, straordinario oppure ore mancanti, e
  giorni di riposo, con l'avviso "<- NESSUN RIPOSO";
- per ogni giorno: persone in servizio e ore totali, con l'avviso
  "<- SCOPERTO" se le persone sono meno di 3.

### Vincoli
- Le verifiche per dipendente lavorano su una **riga**, quelle per giorno su
  una **colonna**
- Un dipendente è in servizio in un giorno se le sue ore sono maggiori di 0
- Ogni dipendente deve avere almeno `MIN_RIPOSI` (1) giorno di riposo
- Un giorno è scoperto se le persone in servizio sono **meno** di
  `MIN_PERSONE` (3): con esattamente 3 persone è coperto
- Le tre situazioni del contratto (uguale, superiore, inferiore) si
  escludono a vicenda
- "giorno"/"giorni" si sceglie con il ternario

### Assunzioni
- Le ore sono interi non negativi

### Variabili di supporto

| Variabile | Tipo  | Descrizione                         |
|-----------|-------|-------------------------------------|
| `totale`, `riposi`, `persone` | `int` | Valori restituiti dalle funzioni |
| `MIN_PERSONE`, `MIN_RIPOSI` | `#define` | 3 e 1                  |

| Funzione | Lavora su | Restituisce |
|---|---|---|
| `ore_settimanali(ore, d)` | riga d | somma |
| `giorni_riposo(ore, d)` | riga d | numero di zeri |
| `persone_in_servizio(ore, g)` | colonna g | celle maggiori di 0 |
| `ore_giorno(ore, g)` | colonna g | somma |

### Algoritmo in linguaggio naturale
1. Stampare la tabella dei turni con totale e contratto di ogni dipendente.
2. Per ogni dipendente confrontare il totale con il contratto e stampare
   l'esito; stampare i giorni di riposo e l'avviso se sono meno di 1.
3. Per ogni giorno contare le persone in servizio e le ore; stampare
   l'avviso se le persone sono meno di 3.

## 3. Casi di test

Il programma non legge dati: si esegue una volta e si confronta con l'output
atteso.

### Test 1 – Tabella dei turni
- **Output atteso:**
```
  Marco       8    8    -    8    8    8    -      40        40
  Giulia      6    6    6    6    -    6    6      36        36
  Ahmed       -    4    4    4    -    8    8      28        30
  Sofia       8    8    8    8    8    4    4      48        40
  Luca        4    4    4    -    -    4    -      16        20
```

### Test 2 – Verifica per dipendente
- **Cosa si verifica:** i tre esiti del contratto, il singolare "giorno" e
  l'assenza di riposi
- **Output atteso:**
```
  Marco   ore in linea con il contratto, 2 giorni di riposo
  Giulia  ore in linea con il contratto, 1 giorno di riposo
  Ahmed   mancano 2 ore, 2 giorni di riposo
  Sofia   8 ore di straordinario, 0 giorni di riposo  <- NESSUN RIPOSO
  Luca    mancano 4 ore, 3 giorni di riposo
```

### Test 3 – Copertura giornaliera
- **Cosa si verifica:** la domenica con esattamente 3 persone è coperta, il
  venerdì con 2 no
- **Output atteso:**
```
  Lun: 4 persone, 26 ore
  Mar: 5 persone, 30 ore
  Mer: 4 persone, 22 ore
  Gio: 4 persone, 26 ore
  Ven: 2 persone, 16 ore  <- SCOPERTO
  Sab: 5 persone, 30 ore
  Dom: 3 persone, 18 ore
```
