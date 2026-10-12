# Analisi – 080-problema-registro-di-classe.c

## 1. Problema

Il registro elettronico di una classe contiene gli studenti, ognuno con i suoi voti; ogni voto ha valore, data e materia. Il programma registra nuovi voti e calcola le medie per materia o per periodo con una sola funzione a due filtri facoltativi: un puntatore NULL significa "nessun filtro".

## 2. Analisi generale e struttura dati

| Tipo | Campi | Significato |
|------|-------|-------------|
| `Data` | `giorno, mese, anno` | data del calendario |
| `Voto` | `valore, data, materia` | voto con la sua Data |
| `Studente` | `nome, voti[], n_voti` | studente con i voti |
| `Registro` | `classe, studenti[], n_studenti` | registro della classe |

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `registro` | `Registro` | — | Studenti con i voti |
| `nuovo` | `Voto` | — | Voto letto |
| `da`, `a` | `Data` | — | Estremi del periodo |
| `studente` | `Studente *` | — | Studente trovato |

| Funzione | Compito |
|----------|---------|
| `confronta_date(a, b)` | Negativo, zero o positivo |
| `cerca(r, nome)` | Puntatore allo studente o NULL |
| `aggiungi_voto(s, v)` | 0 se lo spazio è esaurito |
| `media(s, materia, da, a, &quanti)` | Media con filtri; materia, da e a possono essere NULL |
| `stampa_medie(r, materia, da, a)` | Una riga per studente |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Media per materia

**a) Input** – `M Matematica`

**b) Output** – Bassi 6.50 (2 voti), Conte 6.00 (2 voti), Dini 9.00 (1 voto)

**c) Variabili di supporto** – `quanti`

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – media(&r->studenti[s], materia, NULL, NULL, &quanti).

### Caso d'uso 2 – Nuovo voto

**a) Input** – `V Dini Matematica 6 10/01/2026`

**b) Output** – "Registrato: Dini, Matematica 6"

**c) Variabili di supporto** – `studente`

**d) Vincoli** – voto da 1 a 10, al massimo 8 voti

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – cerca lo studente e copia il voto in coda.

### Caso d'uso 3 – Media per periodo

**a) Input** – `P 01/12/2025 31/01/2026`

**b) Output** – Bassi "nessun voto", Conte 7.00, Dini 7.00 (2 voti)

**c) Variabili di supporto** – —

**d) Vincoli** – estremi compresi

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – media con materia NULL e i due indirizzi delle date.

### Caso d'uso 4 – Errori

**a) Input** – `V Rossi ...`; voto 11; periodo rovesciato

**b) Output** – "Rossi non e' nella 3B."; "Voto non valido."; "Periodo non valido."

**c) Variabili di supporto** – —

**d) Vincoli** – —

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – confronta_date(&da, &a) > 0 rifiuta il periodo.
