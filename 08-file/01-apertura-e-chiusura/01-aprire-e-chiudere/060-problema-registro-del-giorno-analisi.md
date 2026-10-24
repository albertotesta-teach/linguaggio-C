# Analisi – 060-problema-registro-del-giorno.c

## 1. Problema

Il docente della prima ora registra gli assenti in un file per ogni
giorno, il cui nome si costruisce dalla data con `sprintf`
(`presenze-16-10.txt`). Se il file esiste già, il programma chiede se
aggiungere (`"a"`), sovrascrivere (`"w"`) o annullare. Poi scrive una
riga per ogni assente fino a FINE e ristampa il file.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `giorno`, `mese` | `int` | Data del registro, `gg mm` |
| `scelta` | `char` | `A`, `S` o `N` (anche minuscole), solo se il file esiste |
| `cognome` | testo | Un assente alla volta (senza spazi, 29 caratteri), fino a `FINE` |

### Output

- Il file `presenze-GG-MM.txt` con una riga `assente: COGNOME` per
  assente.
- `Assenti registrati in NOME: N` seguito da `--- NOME ---` e dal
  contenuto del file.
- `Data non valida.` seguito da `Nessuna registrazione.`;
  `Nessuna registrazione.` con la scelta `N`;
  `Scelta non valida: nessuna modifica.` con un'altra lettera.
- `Impossibile aprire NOME` su `stderr`.

### Vincoli

- Il nome si costruisce con `sprintf(nome, "presenze-%02d-%02d.txt", ...)`
  in un array di 40 caratteri, abbastanza per il nome più lungo.
- La data deve esistere: mese da 1 a 12 e giorno fino all'ultimo del mese
  (29 febbraio compreso).
- La modalità si sceglie solo quando il file esiste: `"a"` aggiunge in
  fondo, `"w"` cancella e riscrive; un file nuovo si crea con `"w"`.
- Si controlla il risultato di `fopen` e il file si chiude prima di
  rileggerlo.
- `FINE` va scritto in maiuscolo; anche la fine dell'input termina.

### Assunzioni

- Il registro riguarda l'anno in corso: l'anno non fa parte del nome.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `registro` | `FILE *` | File del giorno; `NULL` se non aperto |
| `nome` | `char[40]` | Nome costruito con `sprintf` |
| `scelta` | `char` | Vale `S` se il file non esiste ancora, `N` se la data non è valida |
| `assenti` | `int` | Righe scritte |
| `finito` | `int` | 1 a FINE o a fine input |

| Funzione | Compito |
|----------|---------|
| `data_valida(giorno, mese)` | 1 se il giorno esiste nel mese |
| `esiste(nome)` | 1 se il file si può aprire in lettura |
| `stampa(nome)` | Stampa il file preceduto da `--- nome ---` |

### Algoritmo in linguaggio naturale

1. Leggere la data; se non è valida, non registrare nulla.
2. Costruire il nome del file; se esiste, chiedere A, S o N e convertire
   la risposta in maiuscolo.
3. Con `A` aprire in `"a"`, con `S` (o file nuovo) in `"w"`; con `N` non
   registrare; con un'altra lettera segnalare la scelta non valida.
4. Scrivere `assente: COGNOME` per ogni cognome fino a `FINE`, chiudere il
   file, stampare il numero di assenti e il contenuto del file.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe). Si parte da una
cartella senza file `presenze-*`; i test vanno eseguiti in ordine.

### Test 1 – Primo registro del giorno

- **Input:** `16 10`, `Rossi Bianchi FINE`
- **Valori intermedi attesi:** `nome` = `presenze-16-10.txt`, file nuovo
  aperto in `"w"`.
- **Output atteso:**
  ```
  Data (gg mm): Assenti (FINE per terminare): Assenti registrati in presenze-16-10.txt: 2
  --- presenze-16-10.txt ---
  assente: Rossi
  assente: Bianchi
  ```

### Test 2 – Il file esiste: si aggiunge

- **Cosa si verifica:** la scelta `a` in minuscolo vale come `A` e
  `"a"` conserva le righe precedenti.
- **Input:** `16 10`, `a`, `Verdi FINE`
- **Output atteso:**
  ```
  Data (gg mm): presenze-16-10.txt esiste gia': A aggiungere, S sovrascrivere, N annullare? Assenti (FINE per terminare): Assenti registrati in presenze-16-10.txt: 1
  --- presenze-16-10.txt ---
  assente: Rossi
  assente: Bianchi
  assente: Verdi
  ```

### Test 3 – Annullare, scelta non valida, sovrascrivere

- **Input:** `16 10`, `n`; poi `16 10`, `x`; poi `16 10`, `s`, `Neri FINE`
- **Output atteso:** `Nessuna registrazione.`; poi
  `Scelta non valida: nessuna modifica.`; poi il registro con la sola
  riga `assente: Neri`.

### Test 4 – Date non valide

- **Input:** `30 2` (poi `16 13`, `abc`)
- **Output atteso:**
  ```
  Data (gg mm): Data non valida.
  Nessuna registrazione.
  ```
- **Nota:** `29 2` è accettato e crea `presenze-29-02.txt`.
