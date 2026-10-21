# Analisi – 060-problema-menu-ristorante.c

## 1. Problema

Una trattoria vuole un programma per prendere le ordinazioni. Il menu va
stampato raggruppato per categoria; poi il cameriere scrive i piatti ordinati
(senza badare alle maiuscole) uno per riga e chiude con "conto". Il
programma conta le porzioni, ignora i piatti non presenti nel menu e stampa
il conto con il coperto.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `piatti` | `char[8][26]` | Nomi dei piatti (nel sorgente) |
| `categoria` | `char[8][26]` | Categoria di ogni piatto (parallelo) |
| `prezzi` | `int[8]` | Prezzo in centesimi (parallelo) |
| `categorie` | `char[4][26]` | Ordine di stampa delle categorie: Primi, Secondi, Contorni, Dolci |
| `coperti` | `int` | Persone al tavolo (2, nel sorgente) |
| `riga` | `char[40]` | Piatto ordinato, letto da tastiera uno per riga; `conto` chiude |

### Output

- Il menu raggruppato per categoria, con i prezzi in euro.
- Per ogni riga dell'ordinazione: `+ <piatto>` (con il nome come scritto
  nel menu) oppure `"<testo>" non e' nel menu.`
- Il conto: una riga per ogni piatto ordinato (porzioni, nome, importo),
  il coperto e il totale.

### Vincoli

- L'ordine delle categorie nel menu è quello di `categorie`, non quello dei piatti.
- Il confronto dei nomi ignora maiuscole e minuscole (`tolower` carattere per carattere).
- Il ciclo termina con `conto` scritto in qualsiasi forma (`Conto`, `CONTO`)
  o a fine input.
- Nel conto si stampano solo i piatti con almeno una porzione; gli importi
  sono calcolati in centesimi.
- Coperto: 2.50 euro a persona.

### Assunzioni

- Il cameriere scrive il nome completo del piatto, senza spazi in più.
- Le categorie dei piatti sono scritte esattamente come in `categorie`.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `porzioni` | `int[8]` | Porzioni ordinate (parallelo a `piatti`) |
| `c`, `k` | `int` | Indici di categoria e di piatto (`k` = -1 se il piatto non c'è) |
| `totale` | `int` | Conto in centesimi |

| Funzione | Compito |
|----------|---------|
| `leggi_riga` | Legge una riga e toglie il `'\n'` |
| `uguali_senza_maiuscole` | Confronto di due stringhe con `tolower` |
| `cerca_piatto` | Indice del piatto, ignorando le maiuscole, oppure -1 |

### Algoritmo in linguaggio naturale

1. Per ogni categoria, nell'ordine di `categorie`, stampare il nome e i
   piatti di quella categoria con il prezzo.
2. Leggere una riga (a fine input usare `conto`); finché non è `conto`:
   cercare il piatto; se non c'è segnalarlo, altrimenti incrementarne le
   porzioni; leggere la riga successiva.
3. Totale = coperti × coperto; per ogni piatto con porzioni > 0 stampare la
   riga e aggiungere l'importo al totale.
4. Stampare coperto e totale.

## 3. Casi di test

### Test 1 – Menu per categoria

- **Cosa si verifica**: i Contorni sono stampati prima dei Dolci anche se
  nell'array dei piatti vengono dopo.
- **Input**: dati del sorgente.
- **Output atteso**:
  ```
  === TRATTORIA DEL BORGO ===
  Primi
    Agnolotti al sugo     11.00
    Risotto ai funghi     12.00
  Secondi
    Brasato al Barolo     16.00
    Tagliata di manzo     18.00
  Contorni
    Insalata mista         4.50
    Patate al forno        4.50
  Dolci
    Bonet                  5.50
    Panna cotta            5.00
  ```

### Test 2 – Ordinazione con maiuscole diverse e piatto assente

- **Cosa si verifica**: il nome viene riconosciuto in qualsiasi forma e
  stampato come nel menu; un piatto assente viene ignorato.
- **Input**: `agnolotti al sugo`, `BONET`, `Tiramisu`, `Brasato al barolo`,
  `Agnolotti al Sugo`, `Insalata mista`, `Conto`.
- **Output atteso**:
  ```
  >   + Agnolotti al sugo
  >   + Bonet
  >   "Tiramisu" non e' nel menu.
  >   + Brasato al Barolo
  >   + Agnolotti al sugo
  >   + Insalata mista
  ```

### Test 3 – Conto

- **Cosa si verifica**: porzioni multiple, solo piatti ordinati, coperto e totale.
- **Input**: l'ordinazione del Test 2.
- **Valori intermedi attesi**: `porzioni` di Agnolotti = 2; `totale` =
  500 + 2200 + 1600 + 550 + 450 = 5300.
- **Output atteso**:
  ```
  === CONTO ===
    2 x Agnolotti al sugo     22.00
    1 x Brasato al Barolo     16.00
    1 x Bonet                  5.50
    1 x Insalata mista         4.50
    2 x Coperto                5.00
    TOTALE                    53.00
  ```

### Test 4 – Fine dell'input senza "conto"

- **Cosa si verifica**: a fine input il programma si comporta come se fosse
  stato scritto `conto`.
- **Input**: `bonet`, poi fine dell'input (Ctrl+D, o input da pipe).
- **Output atteso** (righe finali):
  ```
  === CONTO ===
    1 x Bonet                  5.50
    2 x Coperto                5.00
    TOTALE                    10.50
  ```
