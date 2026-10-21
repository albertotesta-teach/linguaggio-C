# Analisi – 070-problema-sensori-attivi.c

## 1. Problema

Un sistema di monitoraggio registra solo i sensori attivi in due array paralleli
a tappo (ID e lettura). Il programma deve aggiungere sensori (rifiutando i
duplicati), rimuoverli per ID con shift, calcolare la media delle letture e
mantenere i due array sempre sincronizzati.

---

## 2. Analisi

### Input
Nessun input da tastiera: il registro iniziale e le operazioni sono fissi
nel codice.

| Variabile | Tipo       | Dimensione | Descrizione                                     |
|-----------|------------|------------|-------------------------------------------------|
| `id`      | `int[]`    | `MAX` (22) | ID del sensore, terminati da `TAPPO` (-1)       |
| `letture` | `double[]` | `MAX` (22) | Ultima lettura in °C, tappo nella stessa posizione |

Registro iniziale: S101 23.5, S102 31.2, S103 19.8, S105 28.4. Operazioni:
aggiunta di S104 (25.0), aggiunta di S102 (duplicato), rimozione di S103.

### Output
- Lo stato del registro (ID nel formato `S%03d` e lettura), oppure
  "(nessun sensore attivo)", con la media delle letture;
- l'esito di ogni operazione: "OK" con il numero di sensori,
  "RIFIUTATO: sensore gia' presente", "RIFIUTATO: registro pieno" oppure
  "NON TROVATO";
- lo stato finale con la nuova media.

### Vincoli
- I due array hanno il tappo nella stessa posizione e ogni operazione li
  aggiorna entrambi
- Un ID non può comparire due volte: prima di aggiungere si cerca il
  sensore e, se c'è già, l'aggiunta è rifiutata
- L'aggiunta richiede spazio anche per il tappo (`pos + 1 < MAX`)
- La rimozione avviene per ID, non per posizione: si cerca l'indice e si
  spostano a sinistra gli elementi successivi, tappo compreso
- La media si calcola solo sui sensori presenti; con il registro vuoto vale
  0.0

### Assunzioni
- Gli ID sono ≥ 0, quindi -1 non è un ID valido

### Variabili di supporto

| Variabile | Tipo      | Descrizione                                    |
|-----------|-----------|------------------------------------------------|
| `esito`   | `int`     | Risultato dell'aggiunta: 1 OK, 0 pieno, -1 duplicato |
| `TAPPO`   | `#define` | -1                                             |
| `MAX`     | `#define` | 22                                             |

| Funzione | Descrizione |
|---|---|
| `int conta_sensori(const int id[])` | Indice del tappo |
| `int cerca_sensore(const int id[], int id_cercato)` | Indice o -1 |
| `int aggiungi_sensore(...)` | 1 OK, 0 pieno, -1 duplicato |
| `int rimuovi_sensore(...)` | 1 rimosso, 0 non trovato |
| `double media_letture(const double letture[], const int id[])` | Media fino al tappo |
| `void stampa_sensori(...)` | Registro |

### Algoritmo in linguaggio naturale
1. Stampare lo stato iniziale e la media.
2. Aggiunta: se l'ID è già presente restituire -1; altrimenti, se non c'è
   spazio restituire 0; altrimenti scrivere ID e lettura al posto del tappo
   e spostare il tappo in avanti in entrambi gli array.
3. Rimozione: cercare l'indice; se esiste spostare a sinistra tutti gli
   elementi successivi in entrambi gli array.
4. Stampare lo stato finale e la media.

---

## 3. Casi di test

Il programma non legge dati: si esegue con i dati del codice; il Test 3
richiede di modificare l'ID da rimuovere e ricompilare.

### Test 1 – Aggiunta e duplicato
- **Output atteso:**
```
Media letture: 25.7 °C

Aggiunta sensore S104 (lettura 25.0 °C):
  OK -> 5 sensori attivi

Aggiunta sensore S102 (gia' presente):
  RIFIUTATO: sensore gia' presente
```

### Test 2 – Rimozione e stato finale
- **Cosa si verifica:** S103 esce e i successivi scorrono a sinistra; il
  nuovo S104 resta in fondo
- **Output atteso:**
```
Rimozione sensore S103:
  OK -> 4 sensori attivi

Stato finale:
  ID    | Lettura
  ------|--------
  S101  |  23.5 °C
  S102  |  31.2 °C
  S105  |  28.4 °C
  S104  |  25.0 °C
Media letture: 27.0 °C
```

### Test 3 – Rimozione di un sensore inesistente
- **Procedura:** rimuovere l'ID 999 invece di 103
- **Output atteso:** `NON TROVATO`; il registro resta con 5 sensori
