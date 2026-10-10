# Taccuino — Caduta libera

Componenti del gruppo (nome, cognome e username GitHub di entrambi):
- Tewodros Boffa (boffatewodross)
- Francesco Annesi (Fraaa16)

Contributo di ciascuno e come abbiamo controllato insieme il lavoro:
- Abbiamo lavorato in parallelo su rami Git dedicati (mio-sviluppo e main), verificando a ogni passaggio la correttezza della compilazione e confrontando riga per riga l'output generato in traiettoria.dat.

## Preparazione: conversione degli argomenti

Quali controlli abbiamo aggiunto alle funzioni viste nell'esercitazione 0:
- Verifica del numero di argomenti passati da terminale con if (argc != 3).
- Controllo di validità fisica: verifica che dt > 0.0 e steps > 0 prima di procedere con l'allocazione e il ciclo.

Input validi e non validi provati, risultati e codici di uscita:
- ./freefall: stampa il messaggio d'uso su stderr, codice di uscita 1.
- ./freefall -0.1 10: stampa errore su valori non strettamente positivi, codice di uscita 1.
- ./freefall 0.1 0: stampa errore su valori non strettamente positivi, codice di uscita 1.
- ./freefall 0.1 10: esecuzione corretta con stampa della tabella a 6 colonne, codice di uscita 0.

## Step 1: prima della simulazione

La mia previsione e il motivo:
- Previsione: al primo passo la velocità calcolata sarà esatta, mentre la posizione resterà ferma a 100 m accumulando subito un errore rispetto alla traiettoria reale.
- Motivo: l'accelerazione è costante quindi l'integrazione al primo ordine per la velocità è esatta; per la posizione invece v0 = 0, quindi il termine v0 * dt si annulla e trascura completamente lo spostamento dovuto a 0.5 * g * dt^2.

Un passo calcolato a mano:
- Parametri: dt = 0.1 s, stato iniziale y0 = 100.0 m, v0 = 0.0 m/s.
- Numerico:
  - y1 = 100.0 + (0.0) * 0.1 = 100.0 m
  - v1 = 0.0 - (9.81) * 0.1 = -0.981 m/s
- Esatto:
  - y_exact(0.1) = 100.0 - 0.5 * 9.81 * (0.1)^2 = 99.95095 m (errore: 0.04905 m)
  - v_exact(0.1) = 0.0 - 9.81 * 0.1 = -0.981 m/s (errore: 0.0 m/s)

## Step 1: la prova

Comando, risultato atteso e risultato osservato:
- Comando: ./freefall 0.1 10
- Risultato atteso: tabella a 6 colonne con 10 righe; prima riga a t = 0.100000 con y = 100.000000, ultima riga a t = 1.000000.
- Risultato osservato: output coincidente con le previsioni teoriche dopo aver impostato il calcolo del tempo su (step + 1) * dt.

Che cosa ho verificato? Che cosa resta incerto?
- Ho verificato: la corretta esecuzione del passo di Eulero esplicito e l'annullamento dell'errore sulla velocità lungo tutto il moto.
- Resta incerto: la legge di scala quantitativa con cui l'errore globale sulla posizione si riduce al diminuire del passo temporale dt.

Commit discusso e osservazione ricevuta al checkpoint:
- Commit discusso: 0033ffa ("funzione eulero funzionante") e commit successivo con correzione dell'indice di tempo.
- Osservazione ricevuta: calcolare il tempo usando l'indice dell'iterazione corrente step e non la costante steps, per evitare che il tempo rimanga fisso nell'output.

## Step 2: progettare un confronto

La domanda a cui risponde il confronto:
- In che modo scala l'errore globale sulla posizione finale all'istante fissato T al tendere di dt a zero?

Che cosa vario, che cosa mantengo costante e perché:
- Vario: il passo temporale dt (dimezzandolo progressivamente: 0.2, 0.1, 0.05, 0.025, 0.0125 s) e di conseguenza aumento il numero di passi N = T / dt.
- Mantengo costante: il tempo totale di simulazione T = 1.0 s, per confrontare l'errore sullo stesso stato fisico finale del sistema.

Misura dell'errore scelta e unità:
- Errore assoluto sulla posizione all'istante finale: |y_euler(T) - y_exact(T)|, espresso in metri (m).

## Step 2: evidenze e interpretazione

![Dati di convergenza](convergenza.png)

Comandi per ottenere i dati e procedura per riprodurre il grafico:
- Comandi: esecuzione di ./freefall DT N per i vari valori di dt con N = int(1.0 / dt).
- Procedura grafico: estrazione dell'ultima riga (colonna 6) per ogni run e generazione del grafico logaritmico in Python con fit lineare tramite numpy.polyfit(np.log(dt), np.log(error_y), 1).

Come abbiamo stimato l'esponente e come interpretiamo i dati:
- Stima dell'esponente: la pendenza della retta di regressione nel piano log-log è risultata compatibile con 1.0.
- Interpretazione: l'errore globale scala linearmente come O(dt), confermando empiricamente che il metodo di Eulero è un algoritmo del primo ordine.

Una prova aggiuntiva scelta da me (ipotesi, comando, dati o figura):
- Ipotesi: a parità di dt = 0.1 s, raddoppiando l'intervallo temporale a T = 2.0 s, l'errore globale sulla posizione cresce con andamento quadratico rispetto a T.
- Comando: ./freefall 0.1 20 a confronto con ./freefall 0.1 10.
- Esito: l'errore finale sale da circa 0.49 m a circa 1.96 m, confermando un fattore di crescita circa pari a 4 coerente con la dipendenza da T^2.

Quale risultato mi avrebbe fatto cambiare idea?
- Una pendenza nel grafico log-log significativamente diversa da 1 (ad esempio pendenza 2) o un errore finale indipendente dal valore di dt.

## Conclusione

Che cosa posso sostenere e in quale intervallo di validità:
- Il metodo di Eulero esplicito applicato alla caduta libera ha convergenza del primo ordine: dimezzando dt, l'errore sulla posizione finale si dimezza. La conclusione è valida per dt sufficientemente piccoli da essere in regime asintotico, ma non così piccoli da far dominare gli errori di arrotondamento della macchina.

Un limite, un risultato inatteso o una domanda ancora aperta:
- Limite: per ottenere un'elevata accuratezza è necessario ridurre drasticamente dt, aumentando il carico computazionale. Inoltre, su potenziali non costanti (come oscillatori), Eulero esplicito non conserva l'energia meccanica.