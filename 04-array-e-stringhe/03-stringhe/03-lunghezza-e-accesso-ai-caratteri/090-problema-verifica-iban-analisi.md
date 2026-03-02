# Analisi – 090-problema-verifica-iban.c

## 1. Problema

Un'applicazione bancaria deve verificare il formato formale di un IBAN
italiano prima di procedere con una transazione. La verifica controlla:
lunghezza (27 caratteri), country code ("IT"), check digits (2 cifre),
CIN (1 lettera), ABI (5 cifre), CAB (5 cifre), BBAN (12 alfanumerici).

---

## 2. Analisi generale e struttura dati

| Variabile       | Tipo     | Dimensione | Motivazione                                         |
|-----------------|----------|------------|-----------------------------------------------------|
| `iban`          | `char[]` | 28         | 27 caratteri IBAN + `'\0'`                          |
| `lunghezza`     | `int`    | —          | Lunghezza calcolata con ciclo while                 |
| `lunghezza_ok`  | `int`    | —          | Flag: 1 se lunghezza == 27                          |
| `country_ok`    | `int`    | —          | Flag: 1 se posizioni 0-1 sono "IT"                  |
| `checkdigit_ok` | `int`    | —          | Flag: 1 se posizioni 2-3 sono cifre                 |
| `cin_ok`        | `int`    | —          | Flag: 1 se posizione 4 è lettera maiuscola          |
| `abi_ok`        | `int`    | —          | Flag: 1 se posizioni 5-9 sono tutte cifre           |
| `cab_ok`        | `int`    | —          | Flag: 1 se posizioni 10-14 sono tutte cifre         |
| `bban_ok`       | `int`    | —          | Flag: 1 se posizioni 15-26 sono alfanumerici        |
| `errori`        | `int`    | —          | Contatore degli errori trovati                      |
| `i`             | `int`    | —          | Indice per i cicli di verifica                      |
| `segmento_ok`   | `int`    | —          | Flag temporaneo per la verifica di un segmento      |

Struttura dell'IBAN italiano (indici):
```
 0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15..26
 I  T  0  0  A  0  0  0  0  0  0  0  0  0  0  000000000000
|CT |CD |CI|    ABI    |    CAB    |       BBAN         |
```

---

## 3. Casi d'uso e funzionalità

---

### Caso d'uso 1 – Lettura e verifica lunghezza

**a) Input**
Stringa IBAN senza spazi, max 27 caratteri.

**b) Output**
Nessun output diretto: imposta `lunghezza` e `lunghezza_ok`.

**c) Variabili di supporto**
- `i` (`int`): indice del ciclo di conteggio.
- `lunghezza` (`int`): contatore.

**d) Vincoli**
- Tutti i controlli successivi vengono eseguiti solo se `lunghezza_ok` è 1.
- Con lunghezza errata, gli accessi per indice potrebbero riferirsi
  a posizioni al di fuori del contenuto significativo.

**e) Assunzioni**
- L'IBAN è inserito senza spazi (formato compatto).

**f) Algoritmo in linguaggio naturale**
```
1. Leggere l'IBAN con scanf("%27s", iban).
2. Inizializzare i e lunghezza a 0.
3. Finché iban[i] non è '\0': incrementare lunghezza e i.
4. Se lunghezza == 27: lunghezza_ok = 1.
```

---

### Caso d'uso 2 – Verifica dei campi per indice (solo se lunghezza ok)

**a) Input**
La stringa `iban` con lunghezza verificata.

**b) Output**
Nessun output diretto: imposta i flag `country_ok`, `checkdigit_ok`,
`cin_ok`, `abi_ok`, `cab_ok`, `bban_ok`.

**c) Variabili di supporto**
- `segmento_ok` (`int`): flag temporaneo riutilizzato per ABI, CAB, BBAN.
- `i` (`int`): indice per i cicli sui segmenti multi-carattere.

**d) Vincoli**
- I controlli sui campi singoli (country, checkdigit, CIN) usano
  accesso diretto per indice.
- I controlli sui segmenti (ABI, CAB, BBAN) usano cicli `while`
  con condizione composta (indice nel range E segmento ancora valido).

**e) Assunzioni**
- Solo lettere maiuscole sono ammesse (nessuna lettera minuscola nell'IBAN).
- La verifica matematica del checksum non è implementata.

**f) Algoritmo in linguaggio naturale**
```
1. Se iban[0]=='I' && iban[1]=='T': country_ok = 1.
2. Se iban[2] e iban[3] sono cifre: checkdigit_ok = 1.
3. Se iban[4] è tra 'A' e 'Z': cin_ok = 1.
4. Per ABI (i da 5 a 9): se tutti cifre → abi_ok = 1.
5. Per CAB (i da 10 a 14): se tutti cifre → cab_ok = 1.
6. Per BBAN (i da 15 a 26): se tutti alfanumerici → bban_ok = 1.
```

---

### Caso d'uso 3 – Output risultati e conteggio errori

**a) Input**
Tutti i flag e la variabile `lunghezza`.

**b) Output**
```
════════════════════════════════════════════
  RISULTATO VERIFICA: IT60A0542811101000000123456
════════════════════════════════════════════
  [OK] Lunghezza    : 27 caratteri
  [OK] Country code : IT
  [OK] Check digits : 60
  [OK] CIN          : A
  [OK] ABI          : 05428
  [OK] CAB          : 11101
  [OK] Conto (BBAN) : 000000123456
────────────────────────────────────────────
  ESITO: FORMATO VALIDO
  (verifica formale superata, non matematica)
════════════════════════════════════════════
```

**c) Variabili di supporto**
- `errori` (`int`): incrementato per ogni flag a 0.

**d) Vincoli**
- I campi vengono mostrati solo se `lunghezza_ok` è 1.
- L'esito è VALIDO solo se `errori == 0`.

**e) Assunzioni**
- La verifica matematica del checksum non è inclusa.

**f) Algoritmo in linguaggio naturale**
```
1. Stampare lunghezza con esito OK o errore; se errore: errori++.
2. Se lunghezza_ok:
   a. Per ogni campo: stampare OK o errore; se errore: errori++.
3. Se errori == 0: stampare "FORMATO VALIDO".
4. Altrimenti: stampare "FORMATO NON VALIDO" con numero errori.
```
