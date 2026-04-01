# Analisi – 040-problema-scambio-valori.c

## 1. Problema
Un algoritmo di ordinamento ha bisogno di scambiare il contenuto di due
variabili intere. La funzione `scambia()` deve modificare entrambe le variabili
del chiamante, operazione impossibile con il solo passaggio per valore. Il
programma dimostra anche come chiamate ripetute a `scambia()` possano ordinare
tre numeri in ordine crescente.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Descrizione |
|---|---|---|
| `primo`, `secondo`, `terzo` | int | Valori da scambiare/ordinare nel main |
| `temp` | int (locale a `scambia`) | Variabile temporanea per lo scambio |

| Funzione | Firma | Descrizione |
|---|---|---|
| `scambia` | `void(int*, int*)` | Scambia i valori di due variabili int |
| `ordina_tre` | `void(int*, int*, int*)` | Ordina tre interi in ordine crescente |
| `stampa_tre` | `void(int, int, int)` | Stampa tre valori su una riga |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Scambio di due variabili

**a) Input** – `primo = 42`, `secondo = 7`

**b) Output** – `primo = 7`, `secondo = 42`

**c) Variabili di supporto** – `temp` (int) locale a `scambia`, usata per non perdere un valore durante lo scambio

**d) Vincoli** – i puntatori passati non devono essere `NULL`

**e) Assunzioni** – le due variabili sono distinte (non si passa due volte lo stesso indirizzo)

**f) Algoritmo in linguaggio naturale**
1. Salvare `*a` in `temp`
2. Copiare `*b` in `*a`
3. Copiare `temp` in `*b`

### Caso d'uso 2 – Ordinamento di tre numeri

**a) Input** – `primo = 9`, `secondo = 3`, `terzo = 6`

**b) Output** – `primo = 3`, `secondo = 6`, `terzo = 9`

**c) Variabili di supporto** – nessuna aggiuntiva (usa `scambia` internamente)

**d) Vincoli** – funziona correttamente anche con valori uguali

**e) Assunzioni** – tre elementi: bastano due passaggi di confronto

**f) Algoritmo in linguaggio naturale** (bubble sort a 3 elementi)
1. Se `*x > *y`: scambia x e y (il minore va a sinistra)
2. Se `*y > *z`: scambia y e z (il massimo va a destra)
3. Se `*x > *y`: scambia x e y (eventuale correzione del secondo elemento)

### Caso d'uso 3 – Tentativo errato (passaggio per valore)

**a) Input** – qualsiasi coppia di valori

**b) Output** – le variabili del chiamante rimangono invariate

**c) Variabili di supporto** – `a`, `b`, `temp` sono tutte locali e scompaiono a fine funzione

**d) Vincoli** – N/A: il caso errato è mostrato come commento didattico nel codice

**e) Assunzioni** – N/A

**f) Algoritmo in linguaggio naturale**
1. La funzione riceve copie di `primo` e `secondo`
2. Le copie vengono scambiate localmente
3. Le copie scompaiono: `primo` e `secondo` nel main restano invariati
