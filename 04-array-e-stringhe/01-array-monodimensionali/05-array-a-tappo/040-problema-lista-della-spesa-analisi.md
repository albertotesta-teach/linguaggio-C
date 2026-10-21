# Analisi – 040-problema-lista-della-spesa.c

## 1. Problema

Un'applicazione gestisce una lista della spesa come array di prezzi in centesimi
terminato da -1. Il programma deve calcolare il totale, contare gli articoli,
trovare il più caro e permettere di aggiungere nuovi articoli prima del tappo.

---

## 2. Analisi

### Input
Nessun input da tastiera: la lista iniziale e gli articoli da aggiungere
sono fissi nel codice.

| Variabile | Tipo    | Dimensione | Descrizione                                      |
|-----------|---------|------------|--------------------------------------------------|
| `lista`   | `int[]` | `MAX` (20) | Prezzi in centesimi, terminati da `TAPPO` (-1)   |

Lista iniziale: 149, 299, 89, 450, 199; articoli da aggiungere: 250 e 75.

### Output
- La lista con il prezzo di ogni articolo in euro;
- numero di articoli, totale e articolo più caro;
- l'esito di ogni aggiunta ("OK" con il nuovo numero di articoli, oppure
  "LISTA PIENA");
- la lista aggiornata e il nuovo totale.

### Vincoli
- La lunghezza della lista non è memorizzata: si ricava scorrendo fino al
  tappo, quindi le funzioni non ricevono il numero di elementi
- Il tappo -1 non può essere un prezzo valido, perché i prezzi sono ≥ 0
- Aggiungere un articolo significa scriverlo al posto del tappo e spostare
  il tappo nella cella successiva
- Un'aggiunta è possibile solo se resta spazio anche per il tappo
  (`pos + 1 < MAX`): con capacità `MAX` la lista contiene al massimo
  `MAX − 1` articoli
- I prezzi sono interi in centesimi; in euro si stampano con `/ 100` e
  `% 100`
- A parità di prezzo l'articolo più caro è il primo trovato

### Assunzioni
- La lista contiene sempre il tappo
- Per l'articolo più caro la lista non è vuota

### Variabili di supporto

| Variabile | Tipo      | Descrizione                                    |
|-----------|-----------|------------------------------------------------|
| `n`, `tot`, `idx` | `int` | Numero di articoli, totale, indice del più caro |
| `TAPPO`   | `#define` | -1                                             |
| `MAX`     | `#define` | 20, capacità incluso il tappo                  |

| Funzione | Descrizione |
|---|---|
| `int conta_articoli(const int prezzi[])` | Indice del tappo |
| `int totale(const int prezzi[])` | Somma fino al tappo |
| `int indice_piu_caro(const int prezzi[])` | Indice del massimo |
| `int aggiungi(int prezzi[], int prezzo_centesimi)` | 1 se aggiunto, 0 se la lista è piena |
| `void stampa_lista(const int prezzi[])` | Prezzi in euro |

### Algoritmo in linguaggio naturale
1. Stampare la lista scorrendo fino al tappo.
2. Calcolare e stampare numero di articoli, totale e articolo più caro.
3. Per ogni articolo da aggiungere: trovare la posizione del tappo; se
   `pos + 1 < MAX` scrivere il prezzo in `pos` e il tappo in `pos + 1`,
   altrimenti segnalare che la lista è piena.
4. Stampare la lista aggiornata e il nuovo totale.

---

## 3. Casi di test

Il programma non legge dati: si esegue con i dati del codice; il Test 3
richiede di modificare `MAX` e ricompilare.

### Test 1 – Statistiche della lista iniziale
- **Output atteso:**
```
Articoli     : 5
Totale       : 11,86 euro
Articolo piu' caro: n.4 (4,50 euro)
```

### Test 2 – Aggiunta di due articoli
- **Cosa si verifica:** il tappo si sposta e la lista cresce
- **Output atteso:** `OK -> ora 6 articoli`, `OK -> ora 7 articoli`; nella
  lista aggiornata le righe `6 |   2,50 euro` e `7 |   0,75 euro`;
  `Nuovo totale : 15,11 euro`

### Test 3 – Lista piena
- **Cosa si verifica:** con `MAX` 7 la lista contiene al massimo 6 articoli
- **Procedura:** porre `MAX` a 7
- **Output atteso:** la prima aggiunta `OK -> ora 6 articoli`, la seconda
  `LISTA PIENA`
