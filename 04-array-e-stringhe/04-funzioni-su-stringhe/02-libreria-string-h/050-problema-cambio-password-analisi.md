# Analisi – 050-problema-cambio-password.c

## 1. Problema

Il portale del registro elettronico permette di cambiare la password. Prima
si verifica quella attuale (al massimo 3 tentativi), poi si chiede la nuova:
deve avere da 8 a 20 caratteri ed essere diversa dall'attuale. La nuova
password va riscritta per conferma; se le due versioni non coincidono si
ricomincia. Alla fine la nuova password sostituisce la vecchia.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `password` | `char[]` | 40 | Password memorizzata (inizialmente "Sole2024") |
| `inserita` | `char[]` | 40 | Tentativo di password attuale |
| `nuova`, `conferma` | `char[]` | 40 | Nuova password e sua ripetizione |
| `errori` | `int` | — | Tentativi sbagliati |
| `autenticato`, `cambiata` | `int` | — | Flag che governano i due cicli |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Password attuale errata, poi corretta

**a) Input** – `sole2024`, poi `Sole2024`

**b) Output** – "Password errata (1 di 3 tentativi)."; poi richiesta della nuova password

**c) Variabili di supporto** – `errori`, `autenticato`

**d) Vincoli** – `strcmp` distingue maiuscole e minuscole

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – finché non autenticato e
`errori < 3`: leggere, confrontare con `strcmp`; se uguale impostare
`autenticato`, altrimenti incrementare `errori`.

### Caso d'uso 2 – Nuova password non valida

**a) Input** – `abc`; `Sole2024`

**b) Output** – "Lunghezza non valida: 3 caratteri."; "La nuova password deve essere diversa…"

**c) Variabili di supporto** – `lung`

**d) Vincoli** – 8 ≤ `strlen(nuova)` ≤ 20; `strcmp(nuova, password) != 0`

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – controllare prima la lunghezza, poi
la differenza dalla password attuale; in caso di errore si richiede.

### Caso d'uso 3 – Conferma diversa, poi corretta

**a) Input** – `Luna2025!` / `Luna2025`, poi `Luna2025!` / `Luna2025!`

**b) Output** – "Le due password non coincidono, ricomincia."; poi "Password cambiata (9 caratteri)."

**c) Variabili di supporto** – `conferma`, `cambiata`

**d) Vincoli** – la sostituzione avviene solo dopo la conferma

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – se `strcmp(nuova, conferma) == 0`
copiare `nuova` in `password` con `strcpy` e impostare `cambiata`.

### Caso d'uso 4 – Tentativi esauriti

**a) Input** – tre password attuali sbagliate

**b) Output** – "Troppi tentativi errati: procedura annullata."

**c) Variabili di supporto** – `errori`, `autenticato`

**d) Vincoli** – il secondo ciclo non parte se `autenticato` vale 0

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – al termine si stampa l'esito in base
al valore di `cambiata`.
