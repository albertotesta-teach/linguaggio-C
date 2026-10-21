# Analisi – 060-problema-coda-prenotazioni.c

## 1. Problema

Uno studio medico gestisce le prenotazioni come due array paralleli a tappo:
ID paziente e orario in minuti. Il programma deve aggiungere prenotazioni in
fondo alla coda, rimuovere la prima (logica FIFO) e stampare la coda corrente
con orari in formato HH:MM.

---

## 2. Analisi

### Input
Nessun input da tastiera: la coda iniziale e le operazioni sono fisse nel
codice.

| Variabile      | Tipo    | Dimensione | Descrizione                                      |
|----------------|---------|------------|--------------------------------------------------|
| `id_pazienti`  | `int[]` | `MAX` (12) | ID del paziente, terminati da `TAPPO` (-1)       |
| `orari_visita` | `int[]` | `MAX` (12) | Orario in minuti dalla mezzanotte, terminati da `TAPPO` |

Coda iniziale: 1042 alle 9:00, 2387 alle 9:30, 1905 alle 10:00, 3201 alle
10:30. Operazioni: aggiunta del paziente 4455 alle 11:00, rimozione del primo.

### Output
- Lo stato iniziale della coda: posizione, ID e orario `HH:MM`, oppure
  "(coda vuota)";
- l'esito dell'aggiunta ("OK" con il numero di prenotazioni, oppure
  "CODA PIENA") e della rimozione ("OK" oppure "CODA VUOTA");
- lo stato finale della coda.

### Vincoli
- I due array hanno il tappo **nella stessa posizione**: ogni operazione
  aggiorna entrambi
- La coda è FIFO: si aggiunge in fondo e si rimuove dalla testa
- L'aggiunta è possibile solo se resta spazio per il tappo
  (`pos + 1 < MAX`): al massimo `MAX − 1` prenotazioni
- La rimozione sposta tutti gli elementi di una posizione a sinistra, tappo
  compreso
- L'orario si stampa come `minuti / 60` ore e `minuti % 60` minuti, su due
  cifre

### Assunzioni
- ID e orari sono ≥ 0, quindi -1 non è mai un dato valido
- Le prenotazioni sono già in ordine di orario

### Variabili di supporto

| Variabile | Tipo      | Descrizione                         |
|-----------|-----------|-------------------------------------|
| `ore`, `minuti` | `int` | Orario convertito per la stampa |
| `TAPPO`   | `#define` | -1                                  |
| `MAX`     | `#define` | 12, capacità incluso il tappo       |

| Funzione | Descrizione |
|---|---|
| `int conta(const int id[])` | Indice del tappo |
| `int aggiungi(int id[], int orari[], int nuovo_id, int nuovo_orario)` | 1 se aggiunta, 0 se piena |
| `int rimuovi_primo(int id[], int orari[])` | 1 se rimossa, 0 se vuota |
| `void stampa_coda(const int id[], const int orari[])` | Coda con orari HH:MM |

### Algoritmo in linguaggio naturale
1. Stampare lo stato iniziale.
2. Aggiunta: trovare la posizione del tappo; se c'è spazio scrivere ID e
   orario in quella posizione e il tappo nella successiva, in entrambi gli
   array.
3. Rimozione: se la coda non è vuota, per ogni posizione da 0 alla
   lunghezza − 1 copiare l'elemento successivo, in entrambi gli array.
4. Stampare lo stato finale.

---

## 3. Casi di test

Il programma non legge dati: si esegue con i dati del codice; i test 3 e 4
richiedono modifiche al codice.

### Test 1 – Aggiunta e rimozione
- **Output atteso:**
```
Aggiunta paziente 4455 alle 11:00 (660 minuti):
  OK -> 5 prenotazioni in coda

Paziente 1042 visitato - rimozione dalla coda:
  OK -> 4 prenotazioni rimanenti
```

### Test 2 – Stato finale
- **Cosa si verifica:** il primo paziente è uscito e il nuovo è in fondo
- **Output atteso:**
```
    1  |   2387  | 09:30
    2  |   1905  | 10:00
    3  |   3201  | 10:30
    4  |   4455  | 11:00
```

### Test 3 – Coda piena
- **Procedura:** porre `MAX` a 5 (4 prenotazioni + tappo)
- **Output atteso:** `CODA PIENA`

### Test 4 – Coda inizialmente vuota
- **Cosa si verifica:** la stampa della coda vuota e il ritorno a vuota dopo
  aggiunta e rimozione
- **Procedura:** inizializzare entrambi gli array con il solo `TAPPO`
- **Output atteso:** `Stato iniziale (0 prenotazioni):` con `(coda vuota)`;
  aggiunta `OK -> 1 prenotazioni in coda`; rimozione del paziente 4455
  `OK -> 0 prenotazioni rimanenti`; stato finale `(coda vuota)`
