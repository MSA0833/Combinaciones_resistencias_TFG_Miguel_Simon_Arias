#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <string.h>

// Definimos constantes para el tamaño máximo de las cadenas de configuración
// y modo, así como el tamaño del buffer de lectura.
#define CONFIG_SIZE  20
#define MODO_SIZE    20
#define LINE_BUFFER_SIZE 1024

// Función: read_values_from_file
// Esta función recibe el nombre de un fichero que contiene una lista de valores (uno por línea)
// y lee todos esos valores, almacenándolos en un array dinámicamente asignado en memoria.
//
// Parámetros:
//   filename: nombre del fichero a leer (ej: "resistors.txt")
//   array: doble puntero a double, donde se guardará la dirección del array dinámico.
//   size: puntero a entero donde se almacenará el número total de valores leídos.
//
// Retorna:
//   0 si se leyó todo con éxito,
//  -1 si hubo algún error (ej: no se pudo abrir el fichero o problema de memoria).
int read_values_from_file(const char *filename, double **array, int *size) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        fprintf(stderr, "Error: No se pudo abrir el archivo %s\n", filename);
        return -1;
    }

    // Primero contamos cuántas líneas tiene el archivo para saber cuántos valores vamos a leer.
    int count = 0;
    char line[LINE_BUFFER_SIZE];
    while (fgets(line, sizeof(line), f)) {
        count++;
    }

    // Regresamos el puntero del archivo al inicio para leer de nuevo y esta vez guardar los valores.
    rewind(f);

    // Reservamos memoria dinámica para almacenar 'count' valores double.
    double *temp = (double *)malloc(count * sizeof(double));
    if (!temp) {
        fclose(f);
        fprintf(stderr, "Error: Falló la asignación de memoria.\n");
        return -1;
    }

    // Leemos línea a línea, convertimos a double y guardamos en el array.
    int idx = 0;
    while (fgets(line, sizeof(line), f)) {
        double val;
        if (sscanf(line, "%lf", &val) == 1) {
            temp[idx++] = val;
        }
    }
    fclose(f);

    // Actualizamos los valores de salida: array y tamaño.
    *array = temp;
    *size = count;
    return 0;
}

// Función: find_best_combination
// Dada una resistencia objetivo (target) y una lista de resistencias disponibles,
// esta función encuentra la mejor combinación de dos resistencias usando:
//
// - Conexión en serie o paralelo
// - Configuración en estrella o triángulo
//
// La condición es que el valor resultante debe ser mayor o igual a la resistencia objetivo
// y lo más cercano posible a esta.
//
// Parámetros:
//   target: el valor objetivo de resistencia que queremos alcanzar
//   resistors: array de resistencias disponibles
//   total_res: cantidad de resistencias en el array
//   best_value: puntero a double donde se guardará el mejor valor encontrado
//   best_r1, best_r2: punteros a double donde se guardarán las resistencias que forman la mejor combinación
//   best_config: cadena donde se almacenará "Serie" o "Paralelo"
//   best_modo: cadena donde se almacenará "Estrella" o "Triangulo"
//
// Notas:
// - Se prueban todas las combinaciones de dos resistencias del array.
// - Para cada par (R1, R2), se calcula la configuración en serie y paralelo.
// - Luego se aplica la configuración estrella (el valor es el mismo) y la triangulo (dividiendo por 3).
void find_best_combination(double target, double *resistors, int total_res,
                           double *best_value, double *best_r1, double *best_r2,
                           char *best_config, char *best_modo) {
    *best_value = DBL_MAX;  // Inicializamos el mejor valor con el máximo posible para luego compararlo.

    // Aquí definimos las cadenas para las configuraciones y modos posibles.
    const char *configs[4] = {"Serie", "Serie", "Paralelo", "Paralelo"};
    const char *modos[4]   = {"Estrella", "Triangulo", "Estrella", "Triangulo"};

    // Recorremos todas las resistencias dos a dos.
    for (int i = 0; i < total_res; i++) {
        for (int j = 0; j < total_res; j++) {
            // Si no queremos usar la misma resistencia dos veces, podríamos habilitar esta línea:
            // if (i == j) continue;

            double R1 = resistors[i];
            double R2 = resistors[j];

            // Calculamos la combinación en serie y en paralelo.
            double R_series = R1 + R2;
            double R_parallel = (R1 * R2) / (R1 + R2);

            // Candidatos:
            //   0: Serie Estrella   (R_series)
            //   1: Serie Triangulo  (R_series / 3)
            //   2: Paralelo Estrella(R_parallel)
            //   3: Paralelo Triangulo(R_parallel / 3)
            double candidates[4];
            candidates[0] = R_series;
            candidates[1] = R_series / 3.0;
            candidates[2] = R_parallel;
            candidates[3] = R_parallel / 3.0;

            // Ahora comprobamos cada uno de estos cuatro casos.
            for (int c = 0; c < 4; c++) {
                double val = candidates[c];
                // La condición es que val >= target y que esté lo más cerca posible de target.
                if (val >= target && (val - target) < (*best_value - target)) {
                    *best_value = val;
                    *best_r1 = R1;
                    *best_r2 = R2;
                    strncpy(best_config, configs[c], CONFIG_SIZE - 1);
                    best_config[CONFIG_SIZE - 1] = '\0';
                    strncpy(best_modo, modos[c], MODO_SIZE - 1);
                    best_modo[MODO_SIZE - 1] = '\0';
                }
            }
        }
    }
}

// Función: print_table_header
// Imprime el encabezado de la tabla de resultados.
// Esto es puramente decorativo para entender la salida.
void print_table_header() {
    printf("Valor Objetivo |    R1   |    R2   |  Config   |   Modo     | Valor Resultante\n");
    printf("-----------------------------------------------------------------------------\n");
}

// Función: print_result_line
// Imprime una línea con el resultado para un valor objetivo dado.
// Si no se encontró combinación, lo indica.
void print_result_line(double target, double best_value, double best_r1, double best_r2,
                       const char *best_config, const char *best_modo) {
    if (best_value == DBL_MAX) {
        // Significa que no se encontró una combinación que cumpla las condiciones.
        printf("%12.3f |   ---   |   ---   |    ---    |     ---    | No match found\n", target);
    } else {
        // Imprimimos el valor objetivo, las resistencias encontradas, la configuración, el modo y el valor resultante.
        printf("%12.3f | %7.2f | %7.2f | %9s | %10s | %14.3f\n",
               target, best_r1, best_r2, best_config, best_modo, best_value);
    }
}

int main() {
    // Leemos las resistencias del fichero "resistors.txt"
    double *resistors = NULL;
    int total_res = 0;
    // Paso por referencia las variables para que tomen un valor dependiendo del contenido del fichero
    if (read_values_from_file("resistors.txt", &resistors, &total_res) != 0) {
        return 1; // Si falla, salimos del programa.
    }

    // Leemos los valores objetivos del fichero "targets.txt"
    double *targets = NULL;
    int total_targets = 0;
    // Paso por referencia las variables para que tomen un valor dependiendo del contenido del fichero
    if (read_values_from_file("targets.txt", &targets, &total_targets) != 0) {
        free(resistors);
        return 1;
    }

    // Imprimimos el encabezado de la tabla
    print_table_header();

    // Para cada valor objetivo, encontramos la mejor combinación.
    for (int t = 0; t < total_targets; t++) {
        double target = targets[t];
        double best_value, best_r1, best_r2;
        char best_config[CONFIG_SIZE], best_modo[MODO_SIZE];

        // Buscamos la mejor combinación para este valor objetivo
        find_best_combination(target, resistors, total_res, 
                              &best_value, &best_r1, &best_r2, 
                              best_config, best_modo);

        // Imprimimos el resultado
        print_result_line(target, best_value, best_r1, best_r2, best_config, best_modo);
    }

    // Liberamos la memoria dinámica
    free(resistors);
    free(targets);

    return 0;
}
