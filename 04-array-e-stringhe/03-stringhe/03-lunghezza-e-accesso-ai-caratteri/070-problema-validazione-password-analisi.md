# Analisi – 070-problema-validazione-password.c

## 1. Problema

Un sistema di autenticazione deve verificare che una password rispetti
cinque requisiti di sicurezza: lunghezza minima di 8 caratteri, presenza
di almeno una maiuscola, una minuscola, una cifra e un carattere speciale.
Il programma analizza la password in un singolo ciclo e comunica l'esito
dettagliato per ogni requisito.

---

## 2. Analisi generale e struttura dati

| Variabile       | Tipo     | Dimensione | Motivazione                                         |
|-----------------|----------|------------|-----------------------------------------------------|
| `password`      | `char[]` | 51         | Max 50 caratteri senza spazi + `'\0'`               |
| `lunghezza`     | `int`    | —          | Contatore incrementato a ogni iterazione            |
| `ha_maiuscola`  | `int`    | —          | Flag: 1 se trovata almeno una maiuscola             |
| `ha_minuscola`  | `int`    | —          | Flag: 1 se trovata almeno una minuscola             |
| `ha_cifra`      | `int`    | —          | Flag: 1 se trovata almeno una cifra                 |
| `ha_speciale`   | `int`    | —          | Flag: 1 se trovato almeno un carattere speciale     |
| `c`             | `char`   | —          | Carattere corrente durante la scansione             |
| `i`             | `int`    | —          | Indice per scorrere la password                     |
| `requisiti_ok`  | `int`    | —          | Contatore dei requisiti soddisfatti (0-5)           |

---

## 3. Casi d'uso e funzionalità

---

### Caso d'uso 1 – Lettura della password

**a) Input**
Stringa senza spazi, max 50 caratteri.

**b) Output**
Nessun output diretto: valore memorizzato in `password`.

**c) Variabili di supporto**
Nessuna.

**d) Vincoli**
- `scanf` con `"%50s"` garantisce che non si superi il buffer.
- Le password non contengono spazi per convenzione.

**e) Assunzioni**
- L'utente non inserisce spazi nella password.

**f) Algoritmo in linguaggio naturale**
```
1. Leggere la password con scanf("%50s", password).
```

---

### Caso d'uso 2 – Scansione e verifica requisiti

**a) Input**
La stringa `password`.

**b) Output**
Nessun output diretto: aggiorna `lunghezza` e i quattro flag booleani.

**c) Variabili di supporto**
- `c` (`char`): carattere corrente.
- `i` (`int`): indice di scansione.

**d) Vincoli**
- Un unico ciclo `while` copre tutti i requisiti simultaneamente.
- I flag vengono impostati a 1 appena il requisito è soddisfatto
  e non vengono più modificati nelle iterazioni successive.

**e) Assunzioni**
- I caratteri speciali ammessi sono: `!`, `@`, `#`, `$`, `%`, `&`, `*`.
- Non sono gestiti caratteri accentati o Unicode.

**f) Algoritmo in linguaggio naturale**
```
1. Inizializzare lunghezza=0, tutti i flag a 0, i a 0.
2. Finché password[i] non è '\0':
   a. c = password[i]; incrementare lunghezza.
   b. Se c tra 'A' e 'Z': ha_maiuscola = 1.
   c. Se c tra 'a' e 'z': ha_minuscola = 1.
   d. Se c tra '0' e '9': ha_cifra = 1.
   e. Se c è uno dei simboli speciali: ha_speciale = 1.
   f. Incrementare i.
```

---

### Caso d'uso 3 – Valutazione e output

**a) Input**
`lunghezza`, `ha_maiuscola`, `ha_minuscola`, `ha_cifra`, `ha_speciale`.

**b) Output**
```
════════════════════════════════════════════
  ANALISI PASSWORD: "Sicuro42!"
════════════════════════════════════════════
  Lunghezza (9 car.): OK
  Maiuscola         : OK
  Minuscola         : OK
  Cifra             : OK
  Carattere spec.   : OK
────────────────────────────────────────────
  Requisiti: 5/5 soddisfatti
────────────────────────────────────────────
  ESITO: PASSWORD ACCETTATA
════════════════════════════════════════════
```

**c) Variabili di supporto**
- `requisiti_ok` (`int`): somma dei requisiti soddisfatti.

**d) Vincoli**
- `requisiti_ok` viene calcolato sommando i singoli flag e il controllo
  sulla lunghezza, non all'interno del ciclo di scansione.

**e) Assunzioni**
- L'esito è ACCETTATA solo se tutti e 5 i requisiti sono soddisfatti.

**f) Algoritmo in linguaggio naturale**
```
1. Inizializzare requisiti_ok a 0.
2. Per ogni requisito: se soddisfatto, incrementare requisiti_ok.
3. Stampare l'esito di ogni requisito (OK o MANCANTE/INSUFFICIENTE).
4. Se requisiti_ok == 5: stampare "ACCETTATA".
5. Altrimenti: stampare "RIFIUTATA" con invito a correggere.
```
