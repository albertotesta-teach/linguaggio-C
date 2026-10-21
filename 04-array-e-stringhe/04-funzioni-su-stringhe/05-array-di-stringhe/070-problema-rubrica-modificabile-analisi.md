# Analisi – 070-problema-rubrica-modificabile.c

## 1. Problema

Il cellulare di servizio di un'associazione sportiva ha una rubrica di al
massimo 5 contatti. Da un menu numerico si possono aggiungere contatti (non
duplicati e solo se c'è posto), cercarli per una parte del nome, cancellarli
ed elencarli.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `riga` | `char[40]` | Voce del menu (0–4), letta da tastiera |
| `nome`, `numero` | `char[40]` | Dati del contatto da aggiungere, testo da cercare o nome da cancellare |

All'avvio la rubrica contiene 3 contatti: Allenatore Marco, Magazzino, Presidente.

### Output

- A ogni giro il menu con il numero di contatti presenti (`[n/5]`).
- `Aggiunto.`, `Cancellato.`, l'elenco numerato o i contatti trovati.
- Messaggi di errore: `Rubrica piena: cancella un contatto.`,
  `Nome e numero sono obbligatori.`, `"<nome>" e' gia' in rubrica.`,
  `"<nome>" non e' in rubrica.`, `Nessun contatto.`, `Scelta non valida.`
- Alla fine: `Rubrica chiusa con N contatti.`

### Vincoli

- La rubrica è un array riempito parzialmente: `n` contatti nelle prime `n` righe.
- Si aggiunge solo se `n < MAX`, se nome e numero non sono vuoti e se il
  nome non è già presente (`strcmp`).
- La ricerca trova i nomi che **contengono** il testo (`strstr`) e
  distingue maiuscole e minuscole.
- Per cancellare, le righe successive si spostano indietro di una posizione.
- Se la riga del menu non contiene un numero `scelta` vale -1; a fine input vale 0.

### Assunzioni

- Nome e numero sono lunghi al massimo 23 caratteri (la lettura in fase di
  aggiunta è limitata a `LUNG`).

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `nomi` | `char[5][24]` | Nomi dei contatti |
| `numeri` | `char[5][24]` | Numeri di telefono (parallelo) |
| `n` | `int` | Contatti presenti |
| `scelta` | `int` | Voce del menu (letta con `sscanf`) |
| `k`, `pos` | `int` | Indice di scorrimento, posizione del contatto da cancellare |
| `trovati` | `int` | Contatti trovati nella ricerca |

| Funzione | Compito |
|----------|---------|
| `leggi_riga` | Lettura con `fgets`; a fine input restituisce una stringa vuota |
| `cerca_esatto` | Indice del nome con `strcmp`, oppure -1 |

### Algoritmo in linguaggio naturale

1. Finché `scelta` è diversa da 0:
   1. stampare il menu e leggere la scelta;
   2. **1 Aggiungi**: se la rubrica è piena segnalarlo; altrimenti leggere
      nome e numero, controllare che non siano vuoti e che il nome non ci
      sia già, poi copiarli nella riga `n` e incrementare `n`;
   3. **2 Cerca**: leggere il testo e stampare i contatti tra i primi `n`
      il cui nome lo contiene; se nessuno, `Nessun contatto.`;
   4. **3 Cancella**: leggere il nome; se non c'è segnalarlo, altrimenti
      spostare indietro le righe da `pos + 1` a `n - 1` e decrementare `n`;
   5. **4 Elenco**: stampare i primi `n` contatti numerati;
   6. ogni altro valore diverso da 0 è una scelta non valida.
2. Stampare il numero di contatti alla chiusura.

## 3. Casi di test

I test 1–5 sono passi successivi della stessa sessione.

### Test 1 – Aggiunta, duplicato e rubrica piena

- **Cosa si verifica**: i tre esiti dell'aggiunta.
- **Input**: `1`, `Medico sociale`, `340 1112223`; `1`, `Magazzino`, `0131 000`;
  `1`, `Segreteria`, `011 22`; `1`.
- **Valori intermedi attesi**: `n` passa da 3 a 4, resta 4, passa a 5.
- **Output atteso**:
  ```
  >   Nome:   Numero:   Aggiunto.
  >   Nome:   Numero:   "Magazzino" e' gia' in rubrica.
  >   Nome:   Numero:   Aggiunto.
  >   Rubrica piena: cancella un contatto.
  ```

### Test 2 – Ricerca per parte del nome

- **Cosa si verifica**: `strstr` trova il testo in qualsiasi punto del nome
  ("Allenatore Marco" contiene `M`).
- **Input**: `2`, `M`.
- **Output atteso**:
  ```
  >   Testo da cercare:   Allenatore Marco   333 1234567
    Magazzino          0131 445566
    Medico sociale     340 1112223
  ```

### Test 3 – Cancellazione ed elenco

- **Cosa si verifica**: i contatti successivi salgono di una posizione.
- **Input**: `3`, `Magazzino`; `4`.
- **Valori intermedi attesi**: `pos` = 1, `n` passa da 5 a 4.
- **Output atteso**:
  ```
  >   Nome da cancellare:   Cancellato.
  >   1. Allenatore Marco   333 1234567
    2. Presidente         347 7654321
    3. Medico sociale     340 1112223
    4. Segreteria         011 22
  ```

### Test 4 – Errori di inserimento

- **Cosa si verifica**: cancellazione di un nome assente, nome vuoto,
  scelta fuori menu e scelta non numerica.
- **Input**: `3`, `Pippo`; `1`, riga vuota, `123`; `7`; `abc`.
- **Output atteso**:
  ```
  >   Nome da cancellare:   "Pippo" non e' in rubrica.
  >   Nome:   Numero:   Nome e numero sono obbligatori.
  >   Scelta non valida.
  >   Scelta non valida.
  ```

### Test 5 – Uscita

- **Cosa si verifica**: la scelta 0 termina il programma.
- **Input**: `0`.
- **Output atteso**: `> Rubrica chiusa con 4 contatti.`

### Test 6 – Ricerca senza risultati e ricerca sensibile alle maiuscole

- **Cosa si verifica**: la ricerca distingue maiuscole e minuscole.
- **Input** (nuova esecuzione): `2`, `marco`; `0`.
- **Output atteso**:
  ```
  >   Testo da cercare:   Nessun contatto.
  > Rubrica chiusa con 3 contatti.
  ```

### Test 7 – Fine dell'input

- **Cosa si verifica**: a fine input il programma esce invece di ciclare.
- **Input** (nuova esecuzione): `4`, poi fine dell'input (Ctrl+D, o input da pipe).
- **Output atteso** (righe finali):
  ```
  [3/5] 1 Aggiungi  2 Cerca  3 Cancella  4 Elenco  0 Esci
  > Rubrica chiusa con 3 contatti.
  ```
