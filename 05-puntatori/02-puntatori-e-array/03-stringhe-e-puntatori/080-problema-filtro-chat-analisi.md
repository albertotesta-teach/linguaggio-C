# Analisi – 080-problema-filtro-chat.c

## 1. Problema

La chat di classe della piattaforma scolastica deve sostituire con
asterischi le parole di un elenco di parole vietate, senza distinguere
maiuscole e minuscole, prima di pubblicare un messaggio. Per ogni messaggio
si indicano le parole filtrate e alla fine il totale della sessione. Una
riga vuota termina.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `messaggio` | `char[120]` | Messaggio letto con `fgets`; riga vuota per finire |
| `vietate` | `char[3][12]` | `scemo`, `stupido`, `idiota` (nel sorgente, in minuscolo) |

### Output

- Per ogni messaggio: `pubblicato: <messaggio filtrato>`, con
  `(N parola filtrata / parole filtrate)` se c'è stata almeno una
  sostituzione.
- Alla fine: `Parole filtrate nella sessione: N`.

### Vincoli

- La ricerca si fa su una copia del messaggio in minuscolo, costruita con
  due puntatori; la copia ha la stessa lunghezza dell'originale, quindi la
  posizione `trovato − copia` è la stessa nel messaggio.
- Le occorrenze si cercano con `strstr`, ripartendo da
  `trovato + lunghezza`; i caratteri da `q` a `fine` (escluso) del
  messaggio originale diventano `*`.
- Singolare e plurale: `1 parola filtrata`, `N parole filtrate`.
- Un messaggio più lungo del buffer viene troncato e il resto della riga si
  scarta; la fine dell'input termina come la riga vuota.

### Assunzioni

- Le parole vietate sono scritte in minuscolo.
- La ricerca è per sottostringa: una parola vietata viene filtrata anche
  dentro una parola più lunga (vedi Test 2).

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `a_capo` | `char *` | Posizione del `'\n'`, `NULL` se la riga è troppo lunga |
| `c` | `int` | Carattere scartato da una riga troppo lunga |
| `continua` | `int` | Flag del ciclo |
| `sostituite`, `totale` | `int` | Parole filtrate nel messaggio e nella sessione |
| `copia` | `char[120]` | In `censura`: messaggio in minuscolo |
| `trovato` | `const char *` | In `censura`: occorrenza trovata da `strstr` nella copia |
| `q`, `fine` | `char *` | In `censura`: caratteri da sostituire nel messaggio |

| Funzione | Compito |
|----------|---------|
| `censura(messaggio, parole, n)` | Sostituisce le occorrenze e le conta |

### Algoritmo in linguaggio naturale

1. Finché `continua`: leggere un messaggio (a fine input terminare), togliere
   il `'\n'` o scartare il resto della riga; se è vuoto terminare,
   altrimenti filtrarlo, aggiornare il totale e stamparlo.
2. In `censura`: costruire la copia in minuscolo; per ogni parola vietata
   cercarla con `strstr` e, per ogni occorrenza, sostituire con `*` i
   caratteri corrispondenti nel messaggio e contarla.
3. Stampare il totale della sessione.

## 3. Casi di test

Nell'output i messaggi inseriti non compaiono (input da pipe).

### Test 1 – Maiuscole e più occorrenze

- **Input:** `Sei proprio uno SCEMO, anzi uno scemo stupido`
- **Output atteso:**
  ```
    pubblicato: Sei proprio uno *****, anzi uno ***** *******   (3 parole filtrate)
  ```

### Test 2 – Messaggi senza parole vietate e sottostringhe

- **Input:** `Domani verifica di matematica`; `che IDIOTAggine`;
  `sei stupidissimo`
- **Output atteso:**
  ```
    pubblicato: Domani verifica di matematica
    pubblicato: che ******ggine   (1 parola filtrata)
    pubblicato: sei stupidissimo
  ```
  ("stupidissimo" non contiene "stupido").

### Test 3 – Totale della sessione

- **Input:** i quattro messaggi dei test 1 e 2, poi riga vuota
- **Output atteso:** `Parole filtrate nella sessione: 4`

### Test 4 – Messaggio più lungo del buffer

- **Cosa si verifica:** il resto della riga non viene pubblicato come un
  secondo messaggio.
- **Input:** 125 caratteri `x` seguiti da ` scemo`, poi fine dell'input
- **Output atteso:** una sola riga `pubblicato:` con i primi 119 caratteri
  (la parola vietata, oltre il buffer, non compare).
