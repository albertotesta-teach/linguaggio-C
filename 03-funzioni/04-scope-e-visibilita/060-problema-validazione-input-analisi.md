# Analisi – 060-problema-validazione-input.c

## 1. Problema
Un modulo di registrazione raccoglie età e codice cliente. Ogni campo viene
validato da una funzione dedicata. Un contatore globale di errori viene
incrementato da ciascuna funzione di validazione quando rileva un dato non
valido. Al termine, il main legge il contatore per decidere se accettare o
rifiutare il modulo. Il programma simula la validazione di tre moduli distinti,
azzerando il contatore tra uno e l'altro.

## 2. Analisi generale e struttura dati

| Variabile globale | Tipo | Descrizione |
|---|---|---|
| `errori_trovati` | int | Contatore di errori; azzerato prima di ogni nuovo modulo |

| Funzione | Firma | Descrizione |
|---|---|---|
| `segnala_errore` | `void(const char*)` | Stampa il messaggio e incrementa `errori_trovati` |
| `valida_eta` | `int(int)` | Controlla 18 ≤ eta ≤ 120; restituisce 1 se valida |
| `valida_codice` | `int(int)` | Controlla 10000 ≤ codice ≤ 99999; restituisce 1 se valido |
| `stampa_esito` | `void(void)` | Legge `errori_trovati` e stampa ACCETTATO o RIFIUTATO |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Modulo corretto

**a) Input** – `eta = 35`, `codice = 47231`

**b) Output**
```
--- Caso 1: dati corretti ---
  Eta':    35
  Codice:  47231

Modulo ACCETTATO. Nessun errore rilevato.
```

**c) Variabili di supporto** – `errori_trovati = 0` a inizio caso

**d) Vincoli** – `errori_trovati` deve essere azzerato prima di ogni nuovo modulo

**e) Assunzioni** – i valori inseriti rispettano entrambi i vincoli

**f) Algoritmo in linguaggio naturale**
1. Azzerare `errori_trovati`
2. `valida_eta(35)` → 18 ≤ 35 ≤ 120 → valida, nessun errore segnalato
3. `valida_codice(47231)` → 10000 ≤ 47231 ≤ 99999 → valido
4. `stampa_esito()` → `errori_trovati == 0` → ACCETTATO

### Caso d'uso 2 – Età non valida

**a) Input** – `eta = 15`, `codice = 83400`

**b) Output**
```
--- Caso 2: eta' non valida ---
  Eta':    15
  Codice:  83400
  ERRORE: eta' non valida (deve essere compresa tra 18 e 120)

Modulo RIFIUTATO. Errori rilevati: 1
```

**c) Variabili di supporto** – `errori_trovati` portato a 1 da `segnala_errore`

**d) Vincoli** – il codice è valido ma il modulo viene comunque rifiutato per l'età

**e) Assunzioni** – tutti i campi vengono sempre validati, anche dopo il primo errore

**f) Algoritmo in linguaggio naturale**
1. `valida_eta(15)` → 15 < 18 → chiama `segnala_errore` → `errori_trovati = 1`
2. `valida_codice(83400)` → valido → nessun errore
3. `stampa_esito()` → `errori_trovati == 1` → RIFIUTATO

### Caso d'uso 3 – Tutti i campi errati

**a) Input** – `eta = 200`, `codice = 999`

**b) Output**
```
--- Caso 3: tutti i campi errati ---
  Eta':    200
  Codice:  999
  ERRORE: eta' non valida (deve essere compresa tra 18 e 120)
  ERRORE: codice cliente non valido (deve essere a 5 cifre)

Modulo RIFIUTATO. Errori rilevati: 2
```

**c) Variabili di supporto** – `errori_trovati` portato a 2

**d) Vincoli** – entrambi i campi vengono validati indipendentemente

**e) Assunzioni** – nessun campo è valido; tutti producono un errore

**f) Algoritmo in linguaggio naturale**
1. `valida_eta(200)` → 200 > 120 → `errori_trovati = 1`
2. `valida_codice(999)` → 999 < 10000 → `errori_trovati = 2`
3. `stampa_esito()` → RIFIUTATO con 2 errori
