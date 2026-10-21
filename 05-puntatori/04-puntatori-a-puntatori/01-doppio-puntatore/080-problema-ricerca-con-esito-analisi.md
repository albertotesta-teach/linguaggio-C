# Analisi – 080-problema-ricerca-con-esito.c

## 1. Problema

La rastrelliera della scuola ha 6 posti con lucchetto elettronico. Con
`E tessera` la bici occupa il primo posto libero (se la tessera non ne
occupa già uno), con `U tessera` il posto si libera. Il programma segnala
tessere sconosciute e rastrelliera piena.

## 2. Analisi

### Input

| Dato | Tipo | Descrizione |
|------|------|-------------|
| `comando` | `char` | `E` entrata, `U` uscita, `Q` fine |
| `tessera` | `int` | Numero della tessera, positivo |
| `posti` | `int[6]` | Stato iniziale (nel sorgente): tessera 2041 al posto 2, 1877 al posto 4 |

### Output

- La mappa della rastrelliera all'inizio e dopo ogni comando E/U.
- `Posto N assegnato.`, `La tessera T ha gia' una bici al posto N.`,
  `Posto N liberato.`, `Nessuna bici con la tessera T.`,
  `Rastrelliera piena.`, `Tessera non valida.`, `Comando sconosciuto.`

### Vincoli

- `cerca` restituisce l'esito con `return` (1 trovato, 0 no) e scrive
  l'indirizzo dell'elemento trovato nel puntatore del chiamante
  (`int **trovato`), oppure `NULL`; con esito 0 il puntatore non si usa.
- In entrata prima si controlla che la tessera non abbia già un posto, poi
  si cerca un posto libero (valore 0).
- Il numero del posto si ricava con `posto − posti + 1`.
- Una tessera non numerica o non positiva è rifiutata (la riga si scarta) e
  il programma continua; a fine input si comporta come `Q`.

### Assunzioni

- I comandi sono maiuscoli.

### Variabili di supporto

| Variabile | Tipo | Motivazione |
|-----------|------|-------------|
| `posto` | `int *` | Elemento trovato dalla ricerca, `NULL` se nessuno |
| `letti` | `int` | Valore restituito da `scanf` |

| Funzione | Compito |
|----------|---------|
| `cerca(v, n, valore, &trovato)` | 1 se trovato e indirizzo nel parametro di uscita; 0 e `NULL` altrimenti |
| `stampa(posti, n)` | Mappa della rastrelliera |
| `svuota_riga` | Scarta i caratteri rimasti dopo un inserimento non valido |

### Algoritmo in linguaggio naturale

1. Stampare la rastrelliera.
2. Finché il comando non è `Q`:
   1. leggere il comando (a fine input `Q`);
   2. per `E` o `U` leggere la tessera; se non valida segnalarlo;
   3. `E`: se la tessera ha già un posto segnalarlo; altrimenti se c'è un
      posto libero assegnarlo; altrimenti rastrelliera piena;
   4. `U`: se la tessera c'è liberare il posto, altrimenti segnalarlo;
   5. stampare la rastrelliera; ogni altro comando è sconosciuto.

## 3. Casi di test

Nell'output i comandi inseriti non compaiono (input da pipe).

### Test 1 – Entrate e uscite

- **Input:** `E 3310`, `E 2041`, `U 1877`, `U 9999`
- **Output atteso** (risposte):
  ```
    Posto 1 assegnato.
    La tessera 2041 ha gia' una bici al posto 2.
    Posto 4 liberato.
    Nessuna bici con la tessera 9999.
  ```

### Test 2 – Rastrelliera piena e dati non validi

- **Input** (di seguito al Test 1): `E 4500`, `E 4501`, `E 4502`, `E 4503`,
  `E 4504`, `E abc`, `X`, `Q`
- **Output atteso** (risposte):
  ```
    Posto 3 assegnato.
    Posto 4 assegnato.
    Posto 5 assegnato.
    Posto 6 assegnato.
    Rastrelliera piena.
    Tessera non valida.
    Comando sconosciuto.
  ```
