# Analisi – 080-problema-smistamento-messaggi.c

## 1. Problema

Le richieste dei genitori arrivano allo sportello online della scuola e
devono essere inoltrate all'ufficio giusto (Didattica, Amministrazione,
Servizi). Ogni ufficio ha alcune parole chiave: il messaggio va all'ufficio
di cui contiene più parole chiave. Se non ne contiene nessuna, o se due
uffici sono a pari merito, va alla Segreteria generale. Alla fine si conta
quanti messaggi ha ricevuto ogni ufficio.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `uffici` | `char[4][24]` | Nomi degli uffici; l'ultimo è la Segreteria generale |
| `parole` | `char[11][14]` | Parole chiave, anche solo radici (`pagell`, `assenz`) |
| `ufficio_di` | `int[11]` | Ufficio di ogni parola (parallelo a `parole`) |
| `messaggi` | `char[6][80]` | Richieste arrivate |

I dati sono inizializzati nel sorgente: il programma non legge nulla da tastiera.

### Output

- Per ogni messaggio: il testo, il numero di parole chiave trovate per
  Didattica, Amministrazione e Servizi e l'ufficio a cui viene inoltrato.
- Riepilogo dei messaggi ricevuti da ogni ufficio.

### Vincoli

- La ricerca non distingue maiuscole e minuscole: si cerca in una copia
  del messaggio convertita in minuscolo.
- Ogni parola chiave conta al massimo una volta per messaggio (si verifica
  solo se `strstr` la trova).
- Se il punteggio massimo è 0 oppure è raggiunto da più uffici il messaggio
  va alla Segreteria generale.
- `scegli_ufficio` ha una sola `return`.

### Assunzioni

- Le parole chiave sono scritte in minuscolo; usando la radice si
  riconoscono singolare e plurale (`pagell` trova `pagella` e `pagelle`).
- La Segreteria generale non ha parole chiave proprie.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `testo` | `char[80]` | Messaggio in minuscolo |
| `punteggi` | `int[4]` | Parole trovate per ufficio nel messaggio corrente |
| `ricevuti` | `int[4]` | Messaggi assegnati a ogni ufficio |
| `m`, `p`, `u` | `int` | Indici di messaggio, parola, ufficio |
| `migliore`, `pari`, `scelta` | `int` | In `scegli_ufficio`: ufficio con il massimo, quanti lo raggiungono, risultato |

| Funzione | Compito |
|----------|---------|
| `in_minuscolo` | Copia in minuscolo |
| `scegli_ufficio` | Ufficio con il punteggio massimo, oppure la Segreteria generale |

### Algoritmo in linguaggio naturale

1. Per ogni messaggio:
   1. copiarlo in minuscolo e azzerare i punteggi;
   2. per ogni parola chiave, se è contenuta nel testo incrementare il
      punteggio del suo ufficio;
   3. scegliere l'ufficio: trovare il massimo tra i primi tre, contare
      quanti uffici lo raggiungono; se il massimo è 0 o è condiviso
      scegliere la Segreteria generale;
   4. incrementare `ricevuti` dell'ufficio scelto e stampare il dettaglio.
2. Stampare il riepilogo per ufficio.

## 3. Casi di test

### Test 1 – Un ufficio prevale

- **Cosa si verifica**: più parole dello stesso ufficio portano a quell'ufficio.
- **Input**: `Vorrei prenotare un colloquio per parlare dei voti di mio figlio` (dati del sorgente).
- **Valori intermedi attesi**: trovate `voti` e `colloquio` → `punteggi` = {2, 0, 0}.
- **Output atteso**:
  ```
     parole trovate: didattica 2, amministrazione 0, servizi 0 -> Didattica
  ```

### Test 2 – Parola chiave in maiuscolo

- **Cosa si verifica**: la conversione in minuscolo del messaggio.
- **Input**: `Lo SCUOLABUS di via Roma passa in ritardo`.
- **Output atteso**:
  ```
     parole trovate: didattica 0, amministrazione 0, servizi 1 -> Servizi
  ```

### Test 3 – Radice di una parola

- **Cosa si verifica**: la radice `pagell` è contenuta in `pagelle`.
- **Input**: `Quando escono le pagelle del primo quadrimestre?`
- **Output atteso**:
  ```
     parole trovate: didattica 1, amministrazione 0, servizi 0 -> Didattica
  ```

### Test 4 – Pareggio

- **Cosa si verifica**: un massimo condiviso da più uffici manda il messaggio
  alla Segreteria generale.
- **Input**: `Chiedo il rimborso della mensa per i giorni di assenza`.
- **Valori intermedi attesi**: `punteggi` = {1, 1, 1}, `migliore` = 0, `pari` = 3.
- **Output atteso**:
  ```
     parole trovate: didattica 1, amministrazione 1, servizi 1 -> Segreteria generale
  ```

### Test 5 – Nessuna parola chiave

- **Cosa si verifica**: con punteggio massimo 0 il messaggio va alla Segreteria generale.
- **Input**: `Buongiorno, a chi posso chiedere informazioni?`
- **Output atteso**:
  ```
     parole trovate: didattica 0, amministrazione 0, servizi 0 -> Segreteria generale
  ```

### Test 6 – Riepilogo

- **Cosa si verifica**: conteggio dei messaggi ricevuti su tutti i sei messaggi del sorgente.
- **Input**: dati del sorgente.
- **Output atteso**:
  ```
  === MESSAGGI PER UFFICIO ===
    Didattica            2
    Amministrazione      1
    Servizi              1
    Segreteria generale  2
  ```
