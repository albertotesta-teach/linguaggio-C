# Analisi – 080-problema-log-sistema.c

## 1. Problema

Un'applicazione software deve registrare eventi in un log di sistema.
Il programma legge da tastiera il livello di severità (intero), il codice
evento (senza spazi, con `scanf`) e la descrizione (con spazi, con `fgets`),
poi compone e stampa la riga di log nel formato standard:
`[TIMESTAMP] [LIVELLO] APPLICAZIONE CODICE: descrizione`.

---

## 2. Analisi

### Input

| Variabile        | Tipo     | Dimensione | Descrizione                                 |
|------------------|----------|------------|---------------------------------------------|
| `scelta_livello` | `int`    | —          | 1 = INFO, 2 = WARN, 3 = ERROR               |
| `codice_evento`  | `char[]` | 21         | Identificatore senza spazi, max 20 caratteri |
| `descrizione`    | `char[]` | 201        | Testo con spazi, max 200 caratteri          |

Timestamp e nome dell'applicazione sono preimpostati nel codice.

### Output
- La riga di log nel formato
  `[TIMESTAMP] [LIVELLO] APPLICAZIONE CODICE: descrizione`;
- il dettaglio dei cinque campi.

### Vincoli
- Il livello è sempre di 5 caratteri ("INFO ", "WARN ", "ERROR"), così le
  righe di log restano allineate; si costruisce carattere per carattere,
  perché le funzioni su stringhe arrivano nella sezione 04
- Qualsiasi scelta diversa da 1 e 2 è trattata come ERROR
- Il codice si legge con `scanf("%20s")`, la descrizione con `fgets`
- Prima di ogni lettura successiva a una `scanf` si scarta il resto della
  riga, compreso il `'\n'`: è il punto chiave dell'uso combinato di `scanf` e
  `fgets`
- Il `'\n'` finale della descrizione si sostituisce con `'\0'`

### Assunzioni
- Il timestamp è una costante didattica

### Variabili di supporto

| Variabile      | Tipo     | Dimensione | Descrizione                         |
|----------------|----------|------------|-------------------------------------|
| `timestamp`    | `char[]` | 20         | Data e ora preimpostate             |
| `applicazione` | `char[]` | 14         | Nome dell'applicazione              |
| `livello`      | `char[]` | 6          | Livello di 5 caratteri + `'\0'`     |
| `i`, `c`       | `int`    | —          | Indice per il `'\n'` e carattere scartato |

### Algoritmo in linguaggio naturale
1. Stampare l'intestazione e il timestamp; mostrare i livelli e leggere la
   scelta.
2. Costruire la stringa del livello in base alla scelta.
3. Scartare il resto della riga; leggere il codice con `scanf`.
4. Scartare il resto della riga; leggere la descrizione con `fgets` e
   rimuovere il `'\n'`.
5. Stampare la riga di log e il dettaglio dei campi.

---

## 3. Casi di test

Per ogni caso si inseriscono livello, codice e descrizione.

### Test 1 – Evento di avviso con spazi nella descrizione
- **Input:** `2`, `DISK_LOW`, `Spazio su disco inferiore al 10%`
- **Output atteso:**
```
[2024-11-15 08:45:22] [WARN ] GestMagazzino DISK_LOW: Spazio su disco inferiore al 10%
```

### Test 2 – Evento informativo
- **Input:** `1`, `AUTH_OK`, `Login utente admin`
- **Output atteso:**
  `[2024-11-15 08:45:22] [INFO ] GestMagazzino AUTH_OK: Login utente admin`

### Test 3 – Livello non previsto
- **Cosa si verifica:** ogni valore diverso da 1 e 2 diventa ERROR
- **Input:** `7`, `X`, `Test`
- **Output atteso:** `[2024-11-15 08:45:22] [ERROR] GestMagazzino X: Test`
