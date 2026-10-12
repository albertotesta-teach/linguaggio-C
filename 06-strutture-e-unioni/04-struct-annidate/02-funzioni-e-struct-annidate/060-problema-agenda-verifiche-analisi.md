# Analisi – 060-problema-agenda-verifiche.c

## 1. Problema

Il coordinatore tiene l'agenda delle verifiche scritte: una classe non può avere due verifiche nello stesso giorno e le verifiche si fanno tra le 8:00 e le 13:00. Il comando S sposta una verifica: sposta modifica solo v->giorno e v->ora, lasciando classe e materia.

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Data` | `giorno, mese, anno` | data del calendario |
| `Orario` | `ore, minuti` | ora del giorno |
| `Verifica` | `classe, materia, giorno, ora` | verifica scritta |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `agenda` | `Verifica[]` | 5 | Verifiche |
| `giorno`, `ora` | `Data`, `Orario` | — | Nuova data e ora lette |
| `n`, `altra` | `int` | — | Verifica da spostare e verifica in conflitto |

| Funzione | Compito |
|----------|---------|
| `data_valida(d)` | Data esistente, anno dal 2025 |
| `orario_valido(o)` | Tra le 8:00 e le 13:00 |
| `stessa_data(a, b)` | Confronto campo per campo |
| `conflitto(v, n, escluso, classe, giorno)` | Altra verifica della classe in quel giorno, o -1 |
| `sposta(v, giorno, ora)` | Assegna solo le due parti |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Conflitto

**a) Input** – `S 0 12/02/2026 09:00`

**b) Output** – "La 3B ha gia' Inglese quel giorno."

**c) Variabili di supporto** – `altra`

**d) Vincoli** – una verifica al giorno per classe

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – cercare un'altra verifica, diversa dalla n, della stessa classe e nello stesso giorno.

### Caso d'uso 2 – Spostamento

**a) Input** – `S 0 11/02/2026 09:00`

**b) Output** – "Spostata: 3B Matematica 11/02/2026 09:00"

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – sposta(&agenda[n], &giorno, &ora).

### Caso d'uso 3 – Controlli

**a) Input** – `S 4 30/02/2026 08:00`; `S 4 17/02/2026 14:00`; `S 9 ...`

**b) Output** – "Data non valida."; orario fuori; "Verifica 9 inesistente."

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – prima il numero, poi la data, poi l'orario, infine il conflitto.

### Caso d'uso 4 – Elenco per classe

**a) Input** – `C 3B`

**b) Output** – le tre verifiche della 3B

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – confronto con strcmp sul campo classe.
