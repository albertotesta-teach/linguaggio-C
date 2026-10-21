# Analisi – 040-problema-menu-ristorante.c

## 1. Problema
Un ristorante vuole stampare il proprio menu a schermo in modo ordinato e
facilmente aggiornabile. Il menu è suddiviso in sezioni fisse (antipasti,
primi, secondi, dolci) ciascuna con i propri piatti e prezzi. L'obiettivo
è organizzare il codice in modo che modificare una sezione richieda di
intervenire in un solo punto.

## 2. Analisi

### Input
Nessuno: nomi dei piatti e prezzi sono testo fisso dentro le funzioni di
stampa.

### Output
Il menu completo: intestazione con nome e recapiti del locale, le quattro
sezioni (antipasti, primi, secondi, dolci) con i piatti e i prezzi in euro,
e un piede con coperto e orari.

### Vincoli
- Ogni sezione è separata visivamente dalle altre (titolo e riga vuota)
- I prezzi sono allineati in colonna
- Ogni sezione è stampata da una sola funzione: per aggiornare i prezzi di
  una sezione si modifica solo quella funzione
- Ogni funzione di sezione funziona anche se chiamata da sola, senza
  dipendere dalle altre

### Assunzioni
- I dati del menu non cambiano durante l'esecuzione
- Il terminale è abbastanza largo per la formattazione (circa 45 caratteri)

### Variabili di supporto
Nessuna variabile: la struttura del problema è data dalle funzioni.

| Funzione | Tipo | Descrizione |
|---|---|---|
| `stampa_intestazione_menu` | void | Nome, indirizzo e telefono del locale |
| `stampa_antipasti` | void | Sezione antipasti con prezzi |
| `stampa_primi` | void | Sezione primi piatti con prezzi |
| `stampa_secondi` | void | Sezione secondi piatti con prezzi |
| `stampa_dolci` | void | Sezione dolci con prezzi |
| `stampa_piede_menu` | void | Informazioni su coperto e orari |
| `stampa_menu_completo` | void | Chiama le funzioni in sequenza |

### Algoritmo in linguaggio naturale
1. Stampare l'intestazione con nome e recapiti del locale.
2. Stampare la sezione antipasti (titolo e voci con prezzi).
3. Stampare la sezione primi piatti.
4. Stampare la sezione secondi piatti.
5. Stampare la sezione dolci.
6. Stampare il piede con le informazioni aggiuntive.

Il `main` si limita a chiamare `stampa_menu_completo()`, che esegue i passi
nell'ordine.

## 3. Casi di test

Il programma non legge dati: si esegue una volta e si controlla quanto
stampato.

### Test 1 – Stampa del menu completo
- **Input:** nessuno
- **Output atteso:** nell'ordine, l'intestazione "TRATTORIA DA LUIGI",
  le sezioni ANTIPASTI (3 piatti), PRIMI PIATTI (4 piatti), SECONDI PIATTI
  (3 piatti), DOLCI (3 piatti), e il piede con il coperto di 2.00 EUR.
  Le sezioni sono separate da una riga vuota e i prezzi sono in colonna.

### Test 2 – Indipendenza di una sezione
- **Cosa si verifica:** una funzione di sezione funziona anche isolata
- **Procedura:** sostituire temporaneamente nel `main` la chiamata
  `stampa_menu_completo()` con `stampa_dolci()`, ricompilare ed eseguire
- **Output atteso:** solo la sezione DOLCI, senza intestazione né piede
