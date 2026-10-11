# Analisi – 070-problema-comandi-magazzino.c

## 1. Problema

Il magazzino di una ferramenta si gestisce con comandi scritti su una riga:
`CARICO articolo quantità`, `SCARICO articolo quantità`, `STATO`,
`STATO articolo`, `FINE`. Comandi e nomi possono essere scritti in
maiuscolo o in minuscolo. Lo scarico è rifiutato se la merce non basta; i
comandi incompleti o sconosciuti sono segnalati.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `articoli` | `char[][]` | 5 × 16 | Nomi degli articoli, in minuscolo |
| `giacenze` | `int[]` | 5 | Pezzi disponibili (parallelo) |
| `riga` | `char[]` | 60 | Comando completo |
| `comando`, `articolo` | `char[]` | 16 | Parole lette da `sscanf` (`%15s`) |
| `quantita` | `int` | — | Numero letto da `sscanf` |
| `letti` | `int` | — | Elementi convertiti da `sscanf` |
| `fine` | `int` | — | Flag di uscita |

| Funzione | Compito |
|----------|---------|
| `in_maiuscolo`, `in_minuscolo` | Conversione con `toupper` / `tolower` |
| `cerca_articolo` | Indice dell'articolo con `strcmp`, oppure -1 |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Carico e scarico

**a) Input** – `carico VITI 50`; `SCARICO dadi 20`

**b) Output** – `viti: +50 -> 250 pezzi`; `dadi: -20 -> 130 pezzi`

**c) Variabili di supporto** – `letti` = 3, `a`

**d) Vincoli** – `%15s` impedisce di superare le 16 celle di `comando` e `articolo`

**e) Assunzioni** – quantità intere

**f) Algoritmo in linguaggio naturale**
1. Scomporre la riga con `sscanf`.
2. Comando in maiuscolo, articolo in minuscolo.
3. Cercare l'articolo e aggiornare la giacenza.

### Caso d'uso 2 – Scarico non possibile

**a) Input** – `Scarico dadi 200`

**b) Output** – "Disponibili solo 150 dadi."

**c) Variabili di supporto** – `giacenze[a]`

**d) Vincoli** – la giacenza non può diventare negativa

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – se la quantità supera la giacenza
il comando è rifiutato senza modifiche.

### Caso d'uso 3 – Stato

**a) Input** – `stato`; `stato viti`

**b) Output** – tutte le giacenze; `viti: 250 pezzi`

**c) Variabili di supporto** – `letti` = 1 oppure 2

**d) Vincoli** – il numero di elementi letti distingue le due forme del comando

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – con un solo elemento si stampa
l'elenco completo, con due si cerca l'articolo indicato.

### Caso d'uso 4 – Errori

**a) Input** – `carico bulloni 10`; `carico viti`; `ordina`; riga vuota

**b) Output** – articolo sconosciuto; istruzioni d'uso; comando sconosciuto; "Scrivi un comando."

**c) Variabili di supporto** – `letti`, `a`

**d) Vincoli** – con una riga vuota `sscanf` restituisce -1 (nessun elemento)

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – ogni caso è riconosciuto da una
condizione della catena `if-else`; il ciclo termina solo con `FINE`.
