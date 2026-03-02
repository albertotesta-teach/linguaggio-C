# Analisi – 080-problema-log-sistema.c

## 1. Problema

Un'applicazione software deve registrare eventi in un log di sistema.
Il programma legge da tastiera il livello di severità (intero), il codice
evento (senza spazi, con `scanf`) e la descrizione (con spazi, con `fgets`),
poi compone e stampa la riga di log nel formato standard:
`[TIMESTAMP] [LIVELLO] APPLICAZIONE CODICE: descrizione`.

---

## 2. Analisi generale e struttura dati

| Variabile       | Tipo     | Dimensione | Motivazione                                             |
|-----------------|----------|------------|---------------------------------------------------------|
| `timestamp`     | `char[]` | 20         | Data e ora preimpostate (19 caratteri + `'\0'`)         |
| `applicazione`  | `char[]` | 14         | Nome app preimpostato (13 caratteri + `'\0'`)           |
| `codice_evento` | `char[]` | 21         | Identificatore senza spazi, max 20 caratteri + `'\0'`   |
| `descrizione`   | `char[]` | 201        | Testo libero con spazi, max 200 caratteri + `'\0'`      |
| `scelta_livello`| `int`    | —          | Intero 1/2/3 scelto dall'utente                         |
| `livello`       | `char[]` | 6          | Stringa del livello (es. "INFO "), 5 caratteri + `'\0'` |
| `i`             | `int`    | —          | Indice per rimozione `'\n'` da fgets                    |

---

## 3. Casi d'uso e funzionalità

---

### Caso d'uso 1 – Selezione del livello di severità

**a) Input**
Intero da tastiera: 1 = INFO, 2 = WARN, qualsiasi altro valore = ERROR.

**b) Output**
Nessun output diretto: il buffer `livello` viene popolato con la stringa
corrispondente al livello scelto.

**c) Variabili di supporto**
- `scelta_livello` (`int`): valore letto da `scanf`.
- `livello` (`char[]`): stringa risultante, popolata carattere per carattere.

**d) Vincoli**
- Il buffer `livello` ha dimensione 6 (5 caratteri + `'\0'`).
- Tutti i livelli hanno esattamente 5 caratteri per allineamento nel log.

**e) Assunzioni**
- Valori diversi da 1 e 2 vengono tutti trattati come ERROR.
- La copia carattere per carattere è intenzionale: `strcpy` non è ancora
  stato introdotto.

**f) Algoritmo in linguaggio naturale**
```
1. Mostrare il menu dei livelli.
2. Leggere scelta_livello con scanf.
3. Se scelta_livello è 1: copiare "INFO " in livello.
4. Se scelta_livello è 2: copiare "WARN " in livello.
5. Altrimenti: copiare "ERROR" in livello.
6. Aggiungere '\0' in posizione 5.
```

---

### Caso d'uso 2 – Lettura codice evento e descrizione

**a) Input**
Codice evento (senza spazi) e descrizione (con spazi) da tastiera.

**b) Output**
Nessun output diretto: i valori sono memorizzati in `codice_evento`
e `descrizione`.

**c) Variabili di supporto**
- Blocco locale `c` (`int`): usato per svuotare il buffer dopo ogni `scanf`.
- `i` (`int`): indice per rimozione `'\n'` da `fgets`.

**d) Vincoli**
- Il buffer deve essere svuotato dal `'\n'` residuo dopo ogni `scanf`
  che precede una `fgets`.
- La rimozione del `'\n'` da `fgets` è obbligatoria prima dell'uso
  della stringa.

**e) Assunzioni**
- Il codice evento non contiene spazi (convenzione applicativa).
- La descrizione può contenere qualsiasi carattere inclusi spazi e punteggiatura.

**f) Algoritmo in linguaggio naturale**
```
1. Svuotare il buffer: getchar() fino a '\n' o EOF.
2. Leggere codice_evento con scanf("%20s", codice_evento).
3. Svuotare nuovamente il buffer.
4. Leggere descrizione con fgets(descrizione, 201, stdin).
5. Rimuovere '\n' da descrizione con ciclo while.
```

---

### Caso d'uso 3 – Composizione e stampa della riga di log

**a) Input**
Tutti i campi: `timestamp`, `livello`, `applicazione`,
`codice_evento`, `descrizione`.

**b) Output**
Riga di log nel formato standard e riepilogo dei singoli campi:
```
════════════════════════════════════════════════════════════
  RIGA DI LOG GENERATA
════════════════════════════════════════════════════════════
[2024-11-15 08:45:22] [ERROR] GestMagazzino DB_CONN_ERR: Connessione al database fallita
════════════════════════════════════════════════════════════

Dettaglio campi:
  Timestamp    : 2024-11-15 08:45:22
  Livello      : ERROR
  Applicazione : GestMagazzino
  Codice       : DB_CONN_ERR
  Descrizione  : Connessione al database fallita
```

**c) Variabili di supporto**
Nessuna variabile aggiuntiva.

**d) Vincoli**
- Il formato della riga di log deve rispettare la struttura:
  `[timestamp] [livello] applicazione codice: descrizione`.

**e) Assunzioni**
- La scrittura su file di log è simulata (output solo su `stdout`).
- Il formato è fisso e non configurabile dall'utente.

**f) Algoritmo in linguaggio naturale**
```
1. Stampare la riga di log con printf usando tutti i campi.
2. Stampare il riepilogo dei singoli campi con etichette allineate.
```
