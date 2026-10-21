# Analisi – 040-problema-orario-scolastico.c

## 1. Problema

L'orario settimanale di una classe va rappresentato come una tabella di
5 giorni per 6 ore, in cui ogni cella contiene il codice della materia.
Il programma deve stampare l'orario in forma leggibile, calcolare le ore
settimanali di ogni materia e indicare il giorno con più ore di Informatica.

## 2. Analisi

### Input
Nessun input da tastiera: l'orario è inizializzato nel codice.

| Variabile | Tipo      | Dimensione | Descrizione                                         |
|-----------|-----------|------------|-----------------------------------------------------|
| `orario`  | `int[][]` | 5 × 6      | Riga = giorno, colonna = ora, valore = codice materia |

Codici: 1 Italiano, 2 Matematica, 3 Inglese, 4 Informatica, 5 Sistemi,
6 Storia, 7 Scienze motorie.

### Output
- La tabella dell'orario con la sigla di tre lettere di ogni materia
  ("???" per un codice sconosciuto);
- le ore settimanali di ogni materia e il totale;
- il giorno con più ore di Informatica e il numero di ore.

### Vincoli
- Il totale delle ore delle materie è uguale al numero di celle
  (5 × 6 = 30) se tutti i codici sono validi
- Per contare le ore di una materia si scorre tutta la matrice; per contare
  le ore di Informatica di un giorno si scorre una sola riga
- A parità di ore di Informatica vince il primo giorno della settimana,
  perché il confronto è stretto (`>`)
- Nomi e sigle si stampano con uno `switch` sul codice, perché gli array di
  stringhe non sono ancora stati introdotti

### Assunzioni
- I codici delle materie sono tra 1 e 7
- Almeno un giorno ha ore di Informatica

### Variabili di supporto

| Variabile         | Tipo      | Descrizione                                 |
|-------------------|-----------|---------------------------------------------|
| `materia`         | `int`     | Codice in esame durante il conteggio (1–7)  |
| `ore_materia`     | `int`     | Celle con quel codice                       |
| `totale_ore`      | `int`     | Somma delle ore di tutte le materie         |
| `ore_info_giorno` | `int`     | Ore di Informatica in un giorno             |
| `max_ore_info`, `giorno_max_info` | `int` | Massimo e giorno corrispondente |
| `GIORNI`, `ORE`, `NUM_MATERIE`, `INFORMATICA` | `#define` | 5, 6, 7, 4 |

### Algoritmo in linguaggio naturale
1. Per ogni giorno stampare l'abbreviazione del giorno e, per ogni ora, la
   sigla della materia.
2. Per ogni codice da 1 a 7: contare le celle della matrice con quel codice,
   sommarle al totale e stampare nome e ore. Stampare il totale.
3. Per ogni giorno contare le ore di Informatica della riga e aggiornare il
   massimo se è maggiore. Stampare il giorno e le ore.

## 3. Casi di test

Il programma non legge dati: si esegue con i dati del codice; il Test 3
richiede di modificare l'orario e ricompilare.

### Test 1 – Stampa dell'orario
- **Output atteso:**
```
          1a    2a    3a    4a    5a    6a
  Lun     ITA   ITA   MAT   INF   INF   STO 
  Mar     MAT   ING   SIS   SIS   ITA   MOT 
  Mer     INF   INF   INF   MAT   STO   ING 
  Gio     ITA   MAT   MAT   SIS   ING   MOT 
  Ven     SIS   INF   INF   ITA   MAT   STO 
```

### Test 2 – Ore per materia e giorno con più Informatica
- **Cosa si verifica:** il totale è 30
- **Output atteso:**
```
  Italiano        : 5 ore
  Matematica      : 6 ore
  Inglese         : 3 ore
  Informatica     : 7 ore
  Sistemi         : 4 ore
  Storia          : 3 ore
  Scienze motorie : 2 ore
  Totale          : 30 ore (5 giorni x 6 ore)

Giorno con piu' ore di Informatica: mercoledi' (3 ore)
```

### Test 3 – Parità tra due giorni
- **Cosa si verifica:** a parità vince il primo giorno
- **Procedura:** al venerdì sostituire la 4a ora (ITA, codice 1) con
  Informatica (codice 4), così venerdì ha anche lui 3 ore di Informatica
- **Output atteso:** `Giorno con piu' ore di Informatica: mercoledi' (3 ore)`
