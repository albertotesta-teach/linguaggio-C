# Analisi – 040-problema-dizionario.c

## 1. Problema

Per un'attività di inglese serve un piccolo dizionario: l'utente scrive una
parola, in italiano o in inglese, e il programma la traduce nell'altra
lingua. Se la parola non c'è, suggerisce le voci che iniziano con le stesse
due lettere. Maiuscole e minuscole non contano. Le ricerche continuano fino
a una riga vuota.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `italiano` | `char[][]` | 10 × 16 | Voci in italiano, in minuscolo |
| `inglese` | `char[][]` | 10 × 16 | Traduzioni (parallelo) |
| `parola` | `char[]` | 30 | Parola cercata, convertita in minuscolo |
| `suggerimenti` | `int` | — | Voci suggerite |

| Funzione | Compito |
|----------|---------|
| `in_minuscolo` | `tolower` su ogni carattere |
| `cerca` | Indice della parola in un elenco con `strcmp`, oppure -1 |
| `suggerisci` | Stampa le voci con le stesse prime due lettere (`strncmp`) |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Parola italiana

**a) Input** – `Scuola`

**b) Output** – `IT -> EN: scuola = school`

**c) Variabili di supporto** – `k`

**d) Vincoli** – la parola va convertita in minuscolo prima della ricerca

**e) Assunzioni** – il dizionario è scritto in minuscolo

**f) Algoritmo in linguaggio naturale**
1. Convertire la parola in minuscolo.
2. Cercarla nell'elenco italiano: se `k != -1` stampare `inglese[k]`.

### Caso d'uso 2 – Parola inglese

**a) Input** – `BOOK`

**b) Output** – `EN -> IT: book = libro`

**c) Variabili di supporto** – `k`

**d) Vincoli** – si cerca nell'inglese solo se la ricerca nell'italiano fallisce

**e) Assunzioni** – nessuna parola compare in entrambe le lingue

**f) Algoritmo in linguaggio naturale** – stessa ricerca nell'elenco inglese,
con traduzione da `italiano[k]`.

### Caso d'uso 3 – Parola sconosciuta

**a) Input** – `quadro`; `teach`; `gatto`

**b) Output** – "Forse cercavi: quaderno (notebook)"; "Forse cercavi: teacher (insegnante)"; "Nessun suggerimento."

**c) Variabili di supporto** – `suggerimenti`

**d) Vincoli** – i suggerimenti hanno senso solo se la parola ha almeno 2 lettere

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – in entrambi gli elenchi stampare le
voci con `strncmp(voce, parola, 2) == 0`; se il totale è 0 dirlo.
