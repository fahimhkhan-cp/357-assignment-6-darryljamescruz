#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"

#define MAX_RECORDS 5000

void usage() {
    printf("Usage: ./main <demographics_file> <operations_file>\n");
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        usage();
        return 1;
    }

    const char *demographics_file = argv[1];
    const char *operations_file = argv[2];

    Demographic records[MAX_RECORDS];
    int record_count = load_demographics(demographics_file, records, MAX_RECORDS);
    if (record_count < 0) {
        fprintf(stderr, "Error loading demographics data.\n");
        return 1;
    }

    printf("%d records loaded\n", record_count);

    FILE *ops_file = fopen(operations_file, "r");
    if (!ops_file) {
        perror("Error opening operations file");
        return 1;
    }

    char line[256];
    while (fgets(line, sizeof(line), ops_file)) {
        char *op = strtok(line, ":");
        if (strcmp(op, "display") == 0) {
            printf("Operation not yet implemented: display\n");
        } else if (strcmp(op, "population-total") == 0) {
            long long total_population = 0;
            for (int i = 0; i < record_count; i++) {
                total_population += records[i].population_2014_population;
            }
            printf("2014 population: %lld\n", total_population);
        } else {
            printf("Unknown operation: %s\n", op);
        }
    }

    fclose(ops_file);
    return 0;
}