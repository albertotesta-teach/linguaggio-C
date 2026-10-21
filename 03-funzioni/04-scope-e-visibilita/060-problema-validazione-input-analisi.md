# Analisi – 060-problema-validazione-input.c

## 1. Problema
Un modulo di registrazione raccoglie età e codice cliente. Ogni campo viene
validato da una funzione dedicata. Un contatore globale di errori viene
incrementato da ciascuna funzione di validazione quando rileva un dato non
valido. Al termine, il main legge il contatore per decidere se accettare o
rifiutare il modulo. Il programma simula la validazione di tre moduli distinti,
azzerando il contatore tra uno e l'altro.

## 2. Analisi

### Input
Nessun input da tastiera: i dati dei tre moduli sono assegnati nel `main`.

| Variabile | Tipo | Descrizione |
|---|---|---|
| `eta` | int | Età del cliente |
| `codice` | int | Codice cliente |

### Output
Per ogni modulo: i dati inseriti, un messaggio `ERRORE: ...` per ogni campo
non valido e l'esito finale, "Modulo ACCETTATO. Nessun errore rilevato."
oppure "Modulo RIFIUTATO. Errori rilevati: N".

### Vincoli
- Età valida: tra 18 e 120, estremi compresi
- Codice valido: numero di 5 cifre, tra 10000 e 99999
- Tutti i campi vengono sempre validati, anche dopo il primo errore, così
  l'utente vede tutti gli errori in una volta
- Il modulo è accettato solo se `errori_trovati` vale 0
- `errori_trovati` va azzerato prima di ogni nuovo modulo

### Assunzioni
- I dati sono numeri interi
- Gli errori di un modulo non devono influire sul successivo

### Variabili di supporto

| Variabile globale | Tipo | Descrizione |
|---|---|---|
| `errori_trovati` | int | Contatore degli errori del modulo corrente |

| Funzione | Firma | Descrizione |
|---|---|---|
| `segnala_errore` | `void(int)` | Stampa il messaggio corrispondente al codice di errore (`ERRORE_ETA` o `ERRORE_CODICE`) e incrementa `errori_trovati` |
| `valida_eta` | `int(int)` | Controlla 18 ≤ eta ≤ 120; restituisce 1 se valida |
| `valida_codice` | `int(int)` | Controlla 10000 ≤ codice ≤ 99999; restituisce 1 se valido |
| `stampa_esito` | `void(void)` | Legge `errori_trovati` e stampa l'esito |

### Algoritmo in linguaggio naturale
Per ogni modulo:
1. Azzerare `errori_trovati`.
2. Stampare età e codice.
3. Chiamare `valida_eta`: se l'età è fuori intervallo, `segnala_errore`
   stampa il messaggio e incrementa il contatore.
4. Chiamare `valida_codice`, con lo stesso comportamento.
5. Chiamare `stampa_esito`: se il contatore vale 0 il modulo è accettato,
   altrimenti è rifiutato con il numero di errori.

## 3. Casi di test

Il `main` valida tre moduli in sequenza: si esegue il programma una volta e
si confronta ogni blocco con l'output atteso.

### Test 1 – Modulo corretto
- **Input:** età 35, codice 47231
- **Output atteso:**
```
--- Caso 1: dati corretti ---
  Eta':    35
  Codice:  47231

Modulo ACCETTATO. Nessun errore rilevato.
```

### Test 2 – Età non valida
- **Cosa si verifica:** un solo campo errato basta per il rifiuto
- **Input:** età 15, codice 83400
- **Output atteso:**
```
--- Caso 2: eta' non valida ---
  Eta':    15
  Codice:  83400
  ERRORE: eta' non valida (deve essere compresa tra 18 e 120)

Modulo RIFIUTATO. Errori rilevati: 1
```

### Test 3 – Tutti i campi errati
- **Cosa si verifica:** entrambi i campi vengono validati e gli errori si
  sommano
- **Input:** età 200, codice 999
- **Output atteso:**
```
--- Caso 3: tutti i campi errati ---
  Eta':    200
  Codice:  999
  ERRORE: eta' non valida (deve essere compresa tra 18 e 120)
  ERRORE: codice cliente non valido (deve essere a 5 cifre)

Modulo RIFIUTATO. Errori rilevati: 2
```

### Test 4 – Azzeramento del contatore
- **Cosa si verifica:** gli errori di un modulo non passano al successivo
- **Procedura:** nell'output complessivo, il Test 3 riporta 2 errori e non
  3 (1 del modulo precedente + 2): il contatore è stato azzerato
- **Output atteso:** "Errori rilevati: 2"

### Test 5 – Valori ai limiti degli intervalli
- **Cosa si verifica:** gli estremi sono compresi
- **Procedura:** aggiungere nel `main` un modulo con età 18 e codice 10000,
  e uno con età 120 e codice 99999
- **Output atteso:** entrambi "Modulo ACCETTATO."
