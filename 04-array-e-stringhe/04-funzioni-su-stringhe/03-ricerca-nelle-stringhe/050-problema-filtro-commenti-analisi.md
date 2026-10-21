# Analisi – 050-problema-filtro-commenti.c

## 1. Problema

Il forum di una classe pubblica i commenti degli studenti dopo aver
sostituito con asterischi le parole di un elenco di parole vietate, senza
distinguere maiuscole e minuscole. Il programma legge un commento per riga
finché non riceve una riga vuota e per ognuno mostra il testo pubblicato e
il numero di parole oscurate.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `commento` | `char[100]` | Commento letto da tastiera, uno per riga; una riga vuota termina |
| `vietate` | `char[4][16]` | Parole vietate (nel sorgente, in minuscolo): `stupido`, `idiota`, `schifo`, `cretino` |

### Output

- Per ogni commento: `Pubblicato: <testo>` se non contiene parole vietate,
  altrimenti `Pubblicato con N parola oscurata / parole oscurate: <testo>`
  con ogni occorrenza sostituita da tanti `*` quante sono le sue lettere.
- Alla fine: `Fine moderazione.`

### Vincoli

- La ricerca non distingue maiuscole e minuscole: si cerca in una copia del
  commento convertita in minuscolo, che ha la stessa lunghezza dell'originale.
- Si oscurano tutte le occorrenze di ogni parola vietata.
- Il commento si ferma anche a fine input (EOF).

### Assunzioni

- Le parole vietate sono scritte in minuscolo e senza accenti.
- La ricerca è per sottostringa: una parola vietata viene oscurata anche
  quando è parte di una parola più lunga (vedi Test 5).

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `minuscolo` | `char[100]` | Copia in minuscolo usata per la ricerca |
| `letta` | `int` | 1 se la lettura è riuscita |
| `v` | `int` | Indice della parola vietata in esame |
| `posizione` | `int` | Indice dell'occorrenza trovata (-1 se nessuna) |
| `sostituzioni` | `int` | Parole oscurate nel commento |

| Funzione | Compito |
|----------|---------|
| `leggi_riga` | Legge una riga e toglie il `'\n'` |
| `in_minuscolo` | Copia convertendo le maiuscole |
| `combacia`, `cerca_da` | Ricerca di una parola a partire da un indice |
| `oscura` | Sostituisce `n` caratteri con `'*'` |

### Algoritmo in linguaggio naturale

1. Leggere un commento.
2. Finché la lettura riesce e il commento non è vuoto:
   1. copiare il commento in minuscolo e azzerare `sostituzioni`;
   2. per ogni parola vietata, se `strstr` la trova nella copia:
      cercare la prima posizione con `cerca_da`; finché la posizione non è -1,
      oscurare i caratteri nell'originale, incrementare `sostituzioni` e
      cercare di nuovo dalla posizione successiva;
   3. stampare il commento con il numero di parole oscurate;
   4. leggere il commento successivo.
3. Stampare `Fine moderazione.`

## 3. Casi di test

### Test 1 – Parola ripetuta con maiuscole diverse

- **Cosa si verifica**: la ricerca ignora maiuscole/minuscole e trova tutte le occorrenze.
- **Input**: `Che compito STUPIDO, sei proprio uno stupido`, poi riga vuota.
- **Valori intermedi attesi**: in `minuscolo` `stupido` compare alle posizioni 12 e 37; `sostituzioni` = 2.
- **Output atteso**:
  ```
    Pubblicato con 2 parole oscurate: Che compito *******, sei proprio uno *******
  ```

### Test 2 – Commento pulito

- **Cosa si verifica**: un commento senza parole vietate resta invariato.
- **Input**: `Bella lezione oggi`, poi riga vuota.
- **Output atteso**:
  ```
    Pubblicato: Bella lezione oggi
  ```

### Test 3 – Parole vietate diverse nello stesso commento

- **Cosa si verifica**: il conteggio somma le occorrenze di parole diverse.
- **Input**: `che schifo, IDIOTA cretino`, poi riga vuota.
- **Output atteso**:
  ```
    Pubblicato con 3 parole oscurate: che ******, ****** *******
  ```

### Test 4 – Occorrenze attaccate e parola simile

- **Cosa si verifica**: due occorrenze consecutive senza spazio sono trovate
  entrambe; una parola solo simile (`Stupidaggini` non contiene `stupido`) non viene toccata.
- **Input**: `stupidostupido`, `Stupidaggini`, poi riga vuota.
- **Output atteso**:
  ```
    Pubblicato con 2 parole oscurate: **************
    Pubblicato: Stupidaggini
  ```

### Test 5 – Parola vietata dentro una parola più lunga

- **Cosa si verifica**: limite della ricerca per sottostringa.
- **Input**: `che film schifoso`, poi riga vuota.
- **Output atteso**:
  ```
    Pubblicato con 1 parola oscurata: che film ******so
  ```
- **Osservazione**: il programma oscura solo la parte che coincide con la
  parola vietata; per oscurare parole intere bisognerebbe controllare anche
  che prima e dopo l'occorrenza ci sia un separatore.

### Test 6 – Fine del programma

- **Cosa si verifica**: la riga vuota (o la fine dell'input) termina il ciclo.
- **Input**: `ciao`, poi riga vuota.
- **Output atteso**:
  ```
    Pubblicato: ciao
  Commento (riga vuota per terminare): Fine moderazione.
  ```
