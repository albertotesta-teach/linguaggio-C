# Analisi – 070-problema-validazione-password.c

## 1. Problema

Un sistema di autenticazione deve verificare che una password rispetti
cinque requisiti di sicurezza: lunghezza minima di 8 caratteri, presenza
di almeno una maiuscola, una minuscola, una cifra e un carattere speciale.
Il programma analizza la password in un singolo ciclo e comunica l'esito
dettagliato per ogni requisito.

---

## 2. Analisi

### Input

| Variabile  | Tipo     | Dimensione | Descrizione                        |
|------------|----------|------------|------------------------------------|
| `password` | `char[]` | 51         | Password senza spazi, max 50 caratteri |

### Output
- Per ogni requisito l'esito: "OK", "MANCANTE" oppure, per la lunghezza,
  "INSUFFICIENTE (minimo 8)";
- il numero di requisiti soddisfatti su 5;
- l'esito finale: "PASSWORD ACCETTATA" solo se sono soddisfatti tutti,
  altrimenti "PASSWORD RIFIUTATA".

### Vincoli
- Lunghezza di almeno 8 caratteri (8 è accettato)
- Maiuscola: `'A'`–`'Z'`; minuscola: `'a'`–`'z'`; cifra: `'0'`–`'9'`
- Caratteri speciali ammessi: `! @ # $ % & *`; qualsiasi altro simbolo non
  soddisfa il requisito
- Un solo ciclo conta la lunghezza e verifica tutti i requisiti con dei flag
- La password si legge con `scanf("%50s")`: non può contenere spazi e non
  supera il buffer

### Assunzioni
- La codifica è ASCII

### Variabili di supporto

| Variabile      | Tipo   | Descrizione                                   |
|----------------|--------|-----------------------------------------------|
| `lunghezza`    | `int`  | Caratteri contati                             |
| `ha_maiuscola`, `ha_minuscola`, `ha_cifra`, `ha_speciale` | `int` | Flag dei requisiti |
| `requisiti_ok` | `int`  | Requisiti soddisfatti (0–5)                   |
| `c`, `i`       | `char`, `int` | Carattere corrente e indice            |

### Algoritmo in linguaggio naturale
1. Leggere la password.
2. Per ogni carattere fino a `'\0'`: incrementare la lunghezza e alzare il
   flag della classe a cui appartiene (maiuscola, minuscola, cifra,
   speciale).
3. Contare i requisiti soddisfatti.
4. Stampare l'esito di ogni requisito, il conteggio e l'esito finale.

---

## 3. Casi di test

Per ogni caso si inserisce la password indicata.

### Test 1 – Password valida
- **Input:** `Sicura#2024`
- **Output atteso:** tutti i requisiti `OK`,
  `Requisiti: 5/5 soddisfatti`, `ESITO: PASSWORD ACCETTATA`

### Test 2 – Esattamente 8 caratteri
- **Cosa si verifica:** il caso limite della lunghezza
- **Input:** `Abcdef1!` (accettata) e `Abcde1!` (7 caratteri)
- **Output atteso:** `Lunghezza (8 car.): OK` e `PASSWORD ACCETTATA`;
  `Lunghezza (7 car.): INSUFFICIENTE (minimo 8)` e `PASSWORD RIFIUTATA`

### Test 3 – Un solo requisito mancante
- **Cosa si verifica:** basta un requisito per il rifiuto
- **Input:** `Password1`
- **Output atteso:** `Carattere spec. : MANCANTE`, `Requisiti: 4/5
  soddisfatti`, `ESITO: PASSWORD RIFIUTATA`

### Test 4 – Più requisiti mancanti
- **Input:** `PASSWORD123`
- **Output atteso:** `Minuscola       : MANCANTE`,
  `Carattere spec. : MANCANTE`, `Requisiti: 3/5 soddisfatti`

### Test 5 – Password corta
- **Input:** `abc`
- **Output atteso:** `Lunghezza (3 car.): INSUFFICIENTE (minimo 8)`,
  `Requisiti: 1/5 soddisfatti`
