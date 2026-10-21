# Analisi – 050-problema-ricevuta-cassa.c

## 1. Problema
Un sistema di cassa deve stampare una ricevuta fiscale formattata. La ricevuta
ha una struttura standardizzata: intestazione del punto vendita, tabella dei
prodotti acquistati con quantità e prezzi, riepilogo con IVA e totale, piede
con numero scontrino e data. Ogni sezione è indipendente e può essere
aggiornata senza toccare le altre.

## 2. Analisi

### Input
Nessuno: in questa versione semplificata articoli, quantità, prezzi e totali
sono fissi nel codice.

### Output
Una ricevuta composta da:
- intestazione del negozio (ragione sociale, indirizzo, P.IVA, telefono);
- tabella dei prodotti con le colonne Prodotto, Qta, Prezzo, Totale;
- riepilogo con subtotale, IVA, totale, metodo di pagamento e resto;
- piede con numero dello scontrino, cassa, data e ora.

Le sezioni sono divise da una riga di trattini sempre uguale.

### Vincoli
- Le colonne della tabella sono allineate: intestazione e righe usano le
  stesse larghezze di campo (`%-20s`, `%3d`, `%6.2f`, `%7.2f`)
- I nomi dei prodotti non superano 20 caratteri
- Il totale di ogni riga è prezzo × quantità, e il subtotale è la somma
  dei totali di riga
- Il separatore è stampato sempre dalla stessa funzione, così è identico
  in tutti i punti della ricevuta

### Assunzioni
- Un solo metodo di pagamento (carta), quindi il resto è sempre 0
- IVA al 5% applicata agli alimentari
- I totali sono calcolati a mano e scritti nel codice; il calcolo
  automatico arriva con i parametri (sezione 02)
- Il terminale è largo almeno 40 caratteri

### Variabili di supporto

| Variabile | Tipo | Descrizione |
|---|---|---|
| `subtotale` | double | Somma dei totali di riga (IVA esclusa) |
| `iva` | double | IVA al 5% del subtotale |
| `totale` | double | Subtotale + IVA |

| Funzione | Tipo | Descrizione |
|---|---|---|
| `stampa_intestazione_negozio` | void | Ragione sociale, indirizzo, P.IVA |
| `stampa_separatore_ricevuta` | void | Riga di trattini per separare sezioni |
| `stampa_prodotti` | void | Tabella articoli con qta, prezzo unitario, totale riga |
| `stampa_riepilogo` | void | Subtotale, IVA, totale, metodo di pagamento |
| `stampa_piede_ricevuta` | void | Numero scontrino, data, ora, messaggio |
| `stampa_ricevuta` | void | Chiama tutte le sezioni in ordine |

### Algoritmo in linguaggio naturale
1. Stampare l'intestazione del negozio.
2. Stampare il separatore.
3. Stampare la tabella dei prodotti: intestazione delle colonne, separatore,
   una riga per articolo.
4. Stampare separatore, subtotale e IVA.
5. Stampare separatore, totale, separatore.
6. Stampare il metodo di pagamento e il resto.
7. Stampare il piede con numero dello scontrino, data e ora.

## 3. Casi di test

Il programma non legge dati: si esegue una volta e si controlla quanto
stampato.

### Test 1 – Ricevuta completa
- **Input:** nessuno
- **Valori intermedi attesi:** totali di riga 2.70, 2.20, 2.97, 6.50, 4.40;
  subtotale 18.77; IVA 18.77 × 0.05 = 0.9385 → 0.94; totale 19.71
- **Output atteso (parte centrale):**
```
Prodotto             Qta Prezzo  Totale
------------------------------------
Latte intero 1L        2   1.35    2.70
Pane di casa           1   2.20    2.20
Passata pomodoro       3   0.99    2.97
Olio extravergine      1   6.50    6.50
Pasta 500g             4   1.10    4.40
------------------------------------
Subtotale (IVA escl.):       18.77
IVA (5% alimentari):          0.94
------------------------------------
TOTALE:                      19.71
------------------------------------
Pagamento: CARTA             19.71
Resto:                        0.00
```

### Test 2 – Allineamento delle colonne
- **Cosa si verifica:** le larghezze di campo dell'intestazione coincidono
  con quelle delle righe
- **Procedura:** nell'output del Test 1 controllare che le cifre dei prezzi e
  dei totali siano incolonnate sotto le rispettive intestazioni
- **Output atteso:** colonne Qta, Prezzo e Totale allineate a destra

### Test 3 – Coerenza dei totali
- **Cosa si verifica:** i valori scritti a mano nel codice sono corretti
- **Procedura:** sommare i totali di riga stampati e confrontarli con il
  subtotale; verificare che subtotale + IVA dia il totale
- **Output atteso:** 18.77 + 0.94 = 19.71
