# Analisi – 080-problema-file-di-blocco.c

## 1. Problema

Più docenti prenotano l'aula informatica con lo stesso programma. Un file
di blocco, `aula.lock`, dice con la sua sola esistenza che l'aula è
occupata e contiene il cognome di chi l'ha prenotata. Prenotare crea il
file e aggiunge una riga a `prenotazioni.txt`; liberare lo rimuove, ma
solo se lo chiede chi ha prenotato.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `comando` | `char` | `P`, `L`, `S`, `R`, `Q` (anche minuscoli), uno per riga |
| `cognome` | testo | Dopo `P` e `L`: cognome del docente, fino a 29 caratteri |
| `aula.lock` | file di testo | Se esiste, contiene il cognome dell'occupante |

### Output

- `  aula prenotata da C`, `  aula occupata da C`, `  aula liberata da C`,
  `  solo C puo' liberare l'aula`, `  l'aula e' gia' libera`.
- `S`: `  occupata da C` oppure `  libera`; `R`: il contenuto di
  `prenotazioni.txt` (`prenotazione di C` per riga) oppure
  `  registro vuoto`.
- `  comando sconosciuto`; su `stderr` `  prenotazione non riuscita` e
  `  impossibile rimuovere aula.lock`.

### Vincoli

- Lo stato dell'aula è solo nel file: si controlla ogni volta aprendo
  `aula.lock` in `"r"`, così due esecuzioni diverse del programma vedono
  lo stesso stato.
- Prenotare scrive il cognome in `aula.lock` (`"w"`) e aggiunge una riga
  in fondo a `prenotazioni.txt` (`"a"`); liberare usa `remove` e ne
  controlla il risultato.
- Si libera solo se il cognome coincide con quello nel file (maiuscole
  comprese).
- Un comando per riga: il resto della riga si scarta. La fine dell'input
  vale come `Q`.

### Assunzioni

- Due docenti non prenotano nello stesso istante: tra il controllo e la
  creazione di `aula.lock` c'è un intervallo in cui un altro programma
  potrebbe creare il file.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `comando` | `char` | Comando in maiuscolo |
| `cognome` | `char[30]` | Docente che chiede |
| `occupante` | `char[30]` | Cognome letto da `aula.lock` |
| `BLOCCO`, `REGISTRO` | `#define` | Nomi dei due file |

| Funzione | Compito |
|----------|---------|
| `leggi_occupante(occupante, dimensione)` | 1 se `aula.lock` esiste; copia la prima riga in `occupante` |
| `prenota(cognome)` | Crea il blocco e registra la prenotazione; 0 se non riesce |
| `ricopia(nome)` | Stampa il registro |
| `svuota_riga` | Scarta il resto della riga del comando |

### Algoritmo in linguaggio naturale

1. Ripetere fino a `Q`: leggere il comando e convertirlo in maiuscolo.
2. `P`: se l'aula è occupata dirlo, altrimenti prenotare.
3. `L`: se l'aula è libera dirlo; se il cognome non è quello
   dell'occupante rifiutare; altrimenti rimuovere `aula.lock`.
4. `S`: stampare lo stato; `R`: stampare il registro.
5. Scartare il resto della riga.

## 3. Casi di test

Nell'output i dati inseriti non compaiono (input da pipe). Si parte senza
`aula.lock` e `prenotazioni.txt`.

### Test 1 – Due docenti e l'aula

- **Input:** `S`, `P Rossi`, `P Bianchi`, `L Bianchi`, `S`, `L Rossi`,
  `P Bianchi`, `R`, `L Bianchi`, `Q`
- **Output atteso:**
  ```
  Comando (P, L, S, R, Q):   libera
  Comando (P, L, S, R, Q):   aula prenotata da Rossi
  Comando (P, L, S, R, Q):   aula occupata da Rossi
  Comando (P, L, S, R, Q):   solo Rossi puo' liberare l'aula
  Comando (P, L, S, R, Q):   occupata da Rossi
  Comando (P, L, S, R, Q):   aula liberata da Rossi
  Comando (P, L, S, R, Q):   aula prenotata da Bianchi
  Comando (P, L, S, R, Q): prenotazione di Rossi
  prenotazione di Bianchi
  Comando (P, L, S, R, Q):   aula liberata da Bianchi
  Comando (P, L, S, R, Q): 
  ```

### Test 2 – Minuscole e dati in più

- **Input:** `p Verdi extra`, `x yy`, `l verdi`, `l Verdi`, `s`, poi fine
  input
- **Output atteso:**
  ```
  Comando (P, L, S, R, Q):   aula prenotata da Verdi
  Comando (P, L, S, R, Q):   comando sconosciuto
  Comando (P, L, S, R, Q):   solo Verdi puo' liberare l'aula
  Comando (P, L, S, R, Q):   aula liberata da Verdi
  Comando (P, L, S, R, Q):   libera
  Comando (P, L, S, R, Q): 
  ```

### Test 3 – Lo stato resta tra due esecuzioni

- **Input:** prima esecuzione `P Neri`, `Q`; seconda esecuzione `S`, `Q`
- **Output atteso:** nella seconda esecuzione `  occupata da Neri`.
