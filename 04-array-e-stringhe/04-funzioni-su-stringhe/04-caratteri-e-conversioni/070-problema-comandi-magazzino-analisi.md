# Analisi – 070-problema-comandi-magazzino.c

## 1. Problema

Il magazzino di una ferramenta si gestisce con comandi scritti su una riga:
`CARICO articolo quantità`, `SCARICO articolo quantità`, `STATO`,
`STATO articolo`, `FINE`. Comandi e nomi possono essere scritti in
maiuscolo o in minuscolo. Lo scarico è rifiutato se la merce non basta; i
comandi incompleti o sconosciuti sono segnalati.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `riga` | `char[60]` | Comando completo letto da tastiera, uno per riga |
| `articoli` | `char[5][16]` | Nomi degli articoli in minuscolo (nel sorgente): viti, dadi, chiodi, tasselli, rondelle |
| `giacenze` | `int[5]` | Pezzi disponibili all'avvio: 200, 150, 500, 80, 300 |

### Output

- `CARICO`/`SCARICO`: `<articolo>: +N -> G pezzi` / `<articolo>: -N -> G pezzi`.
- `STATO`: tutte le giacenze; `STATO articolo`: `<articolo>: G pezzi`.
- Messaggi di errore: `Disponibili solo G <articolo>.`,
  `Articolo "<nome>" sconosciuto.`, `Uso: <COMANDO> articolo quantita' (positiva)`,
  `Comando "<COMANDO>" sconosciuto.`, `Scrivi un comando.`
- Alla fine: `Sessione chiusa.`

### Vincoli

- La riga si scompone con `sscanf(riga, "%15s %15s %d", ...)`: il numero di
  elementi convertiti distingue le forme del comando; `%15s` impedisce di
  superare le 16 celle di `comando` e `articolo`.
- Il comando si converte in maiuscolo, l'articolo in minuscolo.
- La quantità di carico/scarico deve essere positiva.
- La giacenza non può diventare negativa.
- Con una riga vuota `sscanf` non converte nulla (restituisce -1).
- A fine input (EOF) il programma si comporta come se fosse stato scritto `FINE`.

### Assunzioni

- I nomi degli articoli sono una sola parola.
- Le parole oltre la terza vengono ignorate.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `comando`, `articolo` | `char[16]` | Parole lette da `sscanf` |
| `quantita` | `int` | Numero letto da `sscanf` |
| `letti` | `int` | Elementi convertiti da `sscanf` |
| `a` | `int` | Indice dell'articolo (-1 se sconosciuto) |
| `fine` | `int` | Flag di uscita dal ciclo |

| Funzione | Compito |
|----------|---------|
| `leggi_riga` | Legge una riga e toglie il `'\n'` |
| `in_maiuscolo`, `in_minuscolo` | Conversione con `toupper` / `tolower` |
| `cerca_articolo` | Indice dell'articolo con `strcmp`, oppure -1 |

### Algoritmo in linguaggio naturale

1. Finché `fine` è 0:
   1. leggere la riga (a fine input usare `FINE`) e scomporla con `sscanf`;
   2. convertire comando e articolo;
   3. nessun elemento → `Scrivi un comando.`;
   4. `FINE` → `fine` = 1;
   5. `STATO` da solo → stampare tutte le giacenze;
      `STATO articolo` → cercarlo e stamparne la giacenza o l'errore;
   6. `CARICO`/`SCARICO`: se mancano elementi o la quantità non è positiva
      stampare l'uso; se l'articolo è sconosciuto segnalarlo; con `CARICO`
      sommare; con `SCARICO` rifiutare se la quantità supera la giacenza,
      altrimenti sottrarre;
   7. ogni altro comando è sconosciuto.
2. Stampare `Sessione chiusa.`

## 3. Casi di test

I test 1–5 sono righe successive della stessa sessione, quindi le giacenze
risentono dei comandi precedenti.

### Test 1 – Carico e scarico con maiuscole e minuscole miste

- **Cosa si verifica**: conversione di comando e articolo, aggiornamento della giacenza.
- **Input**: `carico VITI 50`, `SCARICO dadi 20`.
- **Output atteso**:
  ```
  >   viti: +50 -> 250 pezzi
  >   dadi: -20 -> 130 pezzi
  ```

### Test 2 – Scarico non possibile

- **Cosa si verifica**: la giacenza non può diventare negativa.
- **Input**: `Scarico dadi 200`.
- **Output atteso**:
  ```
  >   Disponibili solo 130 dadi.
  ```

### Test 3 – Le due forme di STATO

- **Cosa si verifica**: `letti` = 1 e `letti` = 2 distinguono le due forme.
- **Input**: `stato`, `stato viti`, `stato bulloni`.
- **Output atteso**:
  ```
  >   viti       250
    dadi       130
    chiodi     500
    tasselli    80
    rondelle   300
  >   viti: 250 pezzi
  >   Articolo "bulloni" sconosciuto.
  ```

### Test 4 – Comandi incompleti o errati

- **Cosa si verifica**: articolo sconosciuto, quantità mancante o non
  positiva, comando sconosciuto, riga vuota.
- **Input**: `carico bulloni 10`, `carico viti`, `carico viti 0`, `ordina`, riga vuota.
- **Output atteso**:
  ```
  >   Articolo "bulloni" sconosciuto.
  >   Uso: CARICO articolo quantita' (positiva)
  >   Uso: CARICO articolo quantita' (positiva)
  >   Comando "ORDINA" sconosciuto.
  >   Scrivi un comando.
  ```

### Test 5 – Chiusura con FINE

- **Cosa si verifica**: il comando `fine` (anche in minuscolo) termina la sessione.
- **Input**: `fine`.
- **Output atteso**:
  ```
  > Sessione chiusa.
  ```

### Test 6 – Fine dell'input senza FINE

- **Cosa si verifica**: a fine input il programma termina senza ciclare.
- **Input**: `stato dadi`, poi fine dell'input (Ctrl+D, o input da file/pipe).
- **Output atteso**:
  ```
  >   dadi: 150 pezzi
  > Sessione chiusa.
  ```
