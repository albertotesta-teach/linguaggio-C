# Analisi – 040-problema-indirizzo-postale.c

## 1. Problema

Un negozio online stampa le etichette dei pacchi. L'operatore inserisce
destinatario, via con numero civico, CAP, comune e sigla della provincia.
Il programma verifica che il CAP abbia 5 cifre e la provincia 2 caratteri,
compone le tre righe dell'etichetta (al massimo 30 caratteri ciascuna) e
avvisa se qualche riga è stata troncata.

## 2. Analisi

### Input

| Variabile      | Tipo     | Dimensione | Descrizione                     |
|----------------|----------|------------|---------------------------------|
| `destinatario` | `char[]` | 50         | Nome del destinatario           |
| `via`          | `char[]` | 50         | Via e numero civico             |
| `cap`          | `char[]` | 50         | CAP (5 cifre)                   |
| `comune`       | `char[]` | 50         | Comune                          |
| `provincia`    | `char[]` | 50         | Sigla della provincia (2 caratteri) |

### Output
- Le richieste ripetute con "CAP non valido." o "Sigla non valida." per i
  dati errati;
- l'etichetta di tre righe dentro un bordo: destinatario, via,
  `CAP Comune (PR)`;
- "Etichetta pronta." oppure "Attenzione: N riga troppo lunga / righe
  troppo lunghe, controllare l'etichetta.";
- se l'input termina prima della fine: "Input terminato: etichetta non composta.".

### Vincoli
- Il CAP deve avere esattamente 5 caratteri, tutti cifre; la provincia
  esattamente 2 caratteri; entrambi si richiedono finché non sono validi
- Ogni riga dell'etichetta ha al massimo `LARGHEZZA` (30) caratteri
- I pezzi si aggiungono con `strncat`, calcolando lo spazio libero come
  `dim − strlen(dest) − 1` (una cella resta per `'\0'`): così la riga non
  supera mai il buffer
- `aggiungi` restituisce 0 se il pezzo è stato troncato; per la terza riga
  la chiamata è scritta a sinistra di `&&`, così viene eseguita anche dopo
  un troncamento
- Si conta il numero di righe troncate, non di pezzi
- La lettura usa `fgets` con rimozione del `'\n'` tramite `strlen`
- Se l'input termina (`leggi_riga` restituisce 0) non si legge altro e
  l'etichetta non viene composta

### Assunzioni
- La sigla della provincia non è verificata come lettere né trasformata in
  maiuscolo
- Il campo più lungo non supera 49 caratteri

### Variabili di supporto

| Variabile  | Tipo     | Dimensione | Descrizione                         |
|------------|----------|------------|-------------------------------------|
| `riga`     | `char[]` | 31         | Riga dell'etichetta                 |
| `completa` | `int`    | —          | 1 se la riga è entrata tutta        |
| `troncate` | `int`    | —          | Righe troncate                      |

| Funzione | Descrizione |
|---|---|
| `int leggi_riga(char s[], int dim)` | `fgets` e rimozione del `'\n'` |
| `int solo_cifre(const char s[])` | 1 se la stringa contiene solo cifre |
| `int aggiungi(char dest[], int dim, const char sorg[])` | `strncat` nei limiti; 0 se tronca |
| `void stampa_riga(const char s[])` | Riga dentro il bordo |

### Algoritmo in linguaggio naturale
1. Leggere destinatario e via.
2. Leggere il CAP finché non ha 5 caratteri tutti cifre; leggere il comune;
   leggere la provincia finché non ha 2 caratteri.
3. Riga 1: svuotare la riga, aggiungere il destinatario, contare un
   eventuale troncamento, stampare.
4. Riga 2: lo stesso con la via.
5. Riga 3: copiare il CAP, aggiungere spazio, comune, " (", provincia e ")",
   tenendo traccia di ogni troncamento; stampare.
6. Stampare l'esito.

## 3. Casi di test

Si inseriscono i campi nell'ordine richiesto.

### Test 1 – Etichetta corretta
- **Input:** `Mario Rossi`, `Via Garibaldi 12`, `15011`, `Acqui Terme`,
  `AL`
- **Output atteso:**
```
+--------------------------------+
| Mario Rossi                    |
| Via Garibaldi 12               |
| 15011 Acqui Terme (AL)         |
+--------------------------------+
Etichetta pronta.
```

### Test 2 – Dati non validi e righe troncate
- **Cosa si verifica:** CAP troppo corto e con una lettera, provincia di 3
  caratteri, due righe oltre i 30 caratteri
- **Input:** `Dott.ssa Maria Vittoria Dell Acqua Bianchi`, `Via Roma 1`,
  `1501`, `15O11` (con la lettera O), `15011`,
  `Castelnuovo Bormida Superiore`, `ALE`, `AL`
- **Output atteso:** due volte `CAP non valido.`, una volta
  `Sigla non valida.`, poi
```
| Dott.ssa Maria Vittoria Dell A |
| Via Roma 1                     |
| 15011 Castelnuovo Bormida Supe |
+--------------------------------+
Attenzione: 2 righe troppo lunghe, controllare l'etichetta.
```
- **Nota:** il ternario sceglie l'intera espressione al singolare o al
  plurale ("riga troppo lunga" / "righe troppo lunghe")

### Test 3 – Fine dell'input prima della provincia
- **Cosa si verifica:** la chiusura senza ciclo infinito
- **Input:** `Mario Rossi`, `Via Roma 1`, `15121`, poi fine dell'input (Ctrl+D, o input da pipe)
- **Output atteso:**
```
Destinatario: Via e numero civico: CAP (5 cifre): Comune: 

Input terminato: etichetta non composta.
```
