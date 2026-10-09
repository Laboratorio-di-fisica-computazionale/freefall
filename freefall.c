#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define G 9.81
#define Y0 100.0
#define V0 0.0

double exact_position(double t) {
    return Y0 + V0 * t - 0.5 * G * t * t;
}

double exact_velocity(double t) {
    return V0 - G * t;
}

/* Aggiorna posizione e velocita' tramite i puntatori, usando per entrambi
 * i calcoli lo stato iniziale del passo. Dovrebbe restituire 1 se è implementata. */



int euler_step(double dt, double *y, double *v) {
  
  if(y == NULL || v == NULL){
    //se valori di y o v non validi
    return 0;
  }else{
    *y += (*v) * dt;
    *v += (-G) * dt;
    return 1;
  }
}

int main(int argc, char *argv[]) {
    if(argc != 3) {
        fprintf(stderr, "Uso: %s DT N\n", argv[0]);
        return 1;
    }

    // TODO: utilizzare le funzioni atof e atoi per convertire i parametri da stringa a double e int
    double dt = atof(argv[1]);
    int steps = atoi(argv[2]);
    
    
    // TODO: controllate che i parametri dt e steps abbiano senso fisico

    // Qui se il tempo lo permette potreste decidere di usare una struct
    /**
     * typedef struct {
     *    double y;
     *    double v;
     * } Punto;
     */
    double y = Y0;
    double v = V0;

    printf("# t y_euler v_euler y_exact v_exact error_y\n");
    for(int step = 0; step < steps; step++) {
        if(!euler_step(dt, &y, &v)) {
            fprintf(stderr, "Il passo numerico e' ancora da implementare!\n");
            return 1;
        }

        /* TODO: implementa il calcolo del tempo 
        * double t = ...; // calcola il tempo corrente
        */
        double t;
        double y_exact = exact_position(t);
        double v_exact = exact_velocity(t);
        double error_y = fabs(y - y_exact);

        printf("%.6f %.6f %.6f %.6f %.6f %.6f\n", t, y, v, y_exact, v_exact, error_y);
    }

    return 0;
}
