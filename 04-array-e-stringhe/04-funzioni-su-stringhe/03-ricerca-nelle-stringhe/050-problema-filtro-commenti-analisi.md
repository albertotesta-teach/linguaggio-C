# Analisi – 050-problema-filtro-commenti.c

## 1. Problema

Il forum di una classe pubblica i commenti degli studenti dopo aver
sostituito con asterischi le parole di un elenco di parole vietate, senza
distinguere maiuscole e minuscole. Il programma legge un commento per riga
finché non riceve una riga vuota e per ognuno mostra il testo pubblicato e
il numero di parole oscurate.

## 2. Analisi generale e struttura dati

| Variabile | Tipo | Dimensione | Motivazione |
|-----------|------|------------|-------------|
| `vietate` | `char[][]` | 4 × 16 | Parole vietate, già in minuscolo |
| `commento` | `char[]` | 100 | Testo originale, modificato con gli asterischi |
| `minuscolo` | `char[]` | 100 | Copia in minuscolo usata per la ricerca |
| `posizione` | `int` | — | Indice dell'occorrenza trovata |
| `sostituzioni` | `int` | — | Parole oscurate nel commento |

| Funzione | Compito |
|----------|---------|
| `in_minuscolo` | Copia convertendo le maiuscole |
| `combacia`, `cerca_da` | Ricerca di una parola a partire da un indice |
| `oscura` | Sostituisce `n` caratteri con `'*'` |

## 3. Casi d'uso e funzionalità

### Caso d'uso 1 – Parola ripetuta con maiuscole diverse

**a) Input** – `Che compito STUPIDO, sei proprio uno stupido`

**b) Output** – `Che compito *******, sei proprio uno *******` (2 parole oscurate)

**c) Variabili di supporto** – `minuscolo`, `posizione`

**d) Vincoli** – le posizioni trovate in `minuscolo` valgono per `commento`
perché le due stringhe hanno la stessa lunghezza

**e) Assunzioni** – le parole vietate sono scritte in minuscolo

**f) Algoritmo in linguaggio naturale**
1. Copiare il commento in minuscolo.
2. Per ogni parola vietata presente (`strstr != NULL`): trovare la prima
   posizione con `cerca_da`, oscurarla nel commento originale, cercare la
   successiva da `posizione + 1`, finché `cerca_da` restituisce -1.

### Caso d'uso 2 – Commento pulito

**a) Input** – `Bella lezione oggi!`

**b) Output** – "Pubblicato: Bella lezione oggi!"

**c) Variabili di supporto** – `sostituzioni` = 0

**d) Vincoli** – nessuno

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – nessuna parola trovata: si pubblica
il testo così com'è.

### Caso d'uso 3 – Parole diverse nello stesso commento

**a) Input** – `Che schifo... non fare l'Idiota`

**b) Output** – `Che ******... non fare l'******` (2 parole oscurate)

**c) Variabili di supporto** – ciclo sulle parole vietate

**d) Vincoli** – nessuno

**e) Assunzioni** – nessuna

**f) Algoritmo in linguaggio naturale** – come nel caso 1, ripetuto per ogni
parola dell'elenco.
