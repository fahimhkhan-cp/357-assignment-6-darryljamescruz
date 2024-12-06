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
        // Remove trailing newline character, if any
        line[strcspn(line, "\r\n")] = '\0';

        char *op = strtok(line, ":");
        if (!op) continue; // Skip empty lines

        if (strcmp(op, "display") == 0) {
            display(records, record_count);
        } else if (strcmp(op, "population-total") == 0) {
            long long total_population = 0;
            for (int i = 0; i < record_count; i++) {
                // Debug: Print each record's population
                //printf("Record %d population: %lld\n", i, records[i].population_2014_population);

                total_population += records[i].population_2014_population;
            }
            printf("2014 population: %lld\n", total_population);
        } else if (strcmp(op, "population") == 0) {
            char *field = strtok(NULL, ":");
            if (!field) {
                printf("Invalid operation: Missing field for 'population'\n");
                continue;
            }

            double total = 0.0;
            for (int i = 0; i < record_count; i++) {
                if (strcmp(field, "Education.Bachelor's Degree or Higher") == 0) {
                    total += records[i].education_bachelors_degree_or_higher * records[i].population_2014_population / 100.0;
                } else if (strcmp(field, "Education.High School or Higher") == 0) {
                    total += records[i].education_high_school_or_higher * records[i].population_2014_population / 100.0;
                } else if (strcmp(field, "Ethnicities.American Indian and Alaska Native Alone") == 0) {
                    total += records[i].ethnicities_american_indian_and_alaska_native_alone * records[i].population_2014_population / 100.0;
                } else if (strcmp(field, "Ethnicities.Asian Alone") == 0) {
                    total += records[i].ethnicities_asian_alone * records[i].population_2014_population / 100.0;
                } else if (strcmp(field, "Ethnicities.Black Alone") == 0) {
                    total += records[i].ethnicities_black_alone * records[i].population_2014_population / 100.0;
                } else if (strcmp(field, "Ethnicities.Hispanic or Latino") == 0) {
                    total += records[i].ethnicities_hispanic_or_latino * records[i].population_2014_population / 100.0;
                } else if (strcmp(field, "Ethnicities.Native Hawaiian and Other Pacific Islander Alone") == 0) {
                    total += records[i].ethnicities_native_hawaiian_and_other_pacific_islander_alone * records[i].population_2014_population / 100.0;
                } else if (strcmp(field, "Ethnicities.Two or More Races") == 0) {
                    total += records[i].ethnicities_two_or_more_races * records[i].population_2014_population / 100.0;
                } else if (strcmp(field, "Ethnicities.White Alone") == 0) {
                    total += records[i].ethnicities_white_alone * records[i].population_2014_population / 100.0;
                } else if (strcmp(field, "Ethnicities.White Alone, not Hispanic or Latino") == 0) {
                    total += records[i].ethnicities_white_alone_not_hispanic_or_latino * records[i].population_2014_population / 100.0;
                } else if (strcmp(field, "Income.Persons Below Poverty Level") == 0) {
                    total += records[i].income_persons_below_poverty_level * records[i].population_2014_population / 100.0;
                } else {
                    printf("Unknown field: %s\n", field);
                }
            }
            printf("2014 %s population: %.6f\n", field, total);
        
        } else if (strcmp(op, "percent") == 0) {
            char *field = strtok(NULL, ":");
            if (!field) {
                printf("Invalid operation: Missing field for 'percent'\n");
                continue;
            }

            double total_population = 0.0;
            double field_total = 0.0;

            for (int i = 0; i < record_count; i++) {
                total_population += records[i].population_2014_population;

                if (strcmp(field, "Education.Bachelor's Degree or Higher") == 0) {
                    field_total += records[i].education_bachelors_degree_or_higher * records[i].population_2014_population / 100.0;
                } else if (strcmp(field, "Education.High School or Higher") == 0) {
                    field_total += records[i].education_high_school_or_higher * records[i].population_2014_population / 100.0;
                } else if (strcmp(field, "Ethnicities.American Indian and Alaska Native Alone") == 0) {
                    field_total += records[i].ethnicities_american_indian_and_alaska_native_alone * records[i].population_2014_population / 100.0;
                } else if (strcmp(field, "Ethnicities.Asian Alone") == 0) {
                    field_total += records[i].ethnicities_asian_alone * records[i].population_2014_population / 100.0;
                } else if (strcmp(field, "Ethnicities.Black Alone") == 0) {
                    field_total += records[i].ethnicities_black_alone * records[i].population_2014_population / 100.0;
                } else if (strcmp(field, "Ethnicities.Hispanic or Latino") == 0) {
                    field_total += records[i].ethnicities_hispanic_or_latino * records[i].population_2014_population / 100.0;
                } else if (strcmp(field, "Ethnicities.Native Hawaiian and Other Pacific Islander Alone") == 0) {
                    field_total += records[i].ethnicities_native_hawaiian_and_other_pacific_islander_alone * records[i].population_2014_population / 100.0;
                } else if (strcmp(field, "Ethnicities.Two or More Races") == 0) {
                    field_total += records[i].ethnicities_two_or_more_races * records[i].population_2014_population / 100.0;
                } else if (strcmp(field, "Ethnicities.White Alone") == 0) {
                    field_total += records[i].ethnicities_white_alone * records[i].population_2014_population / 100.0;
                } else if (strcmp(field, "Ethnicities.White Alone, not Hispanic or Latino") == 0) {
                    field_total += records[i].ethnicities_white_alone_not_hispanic_or_latino * records[i].population_2014_population / 100.0;
                } else if (strcmp(field, "Income.Persons Below Poverty Level") == 0) {
                    field_total += records[i].income_persons_below_poverty_level * records[i].population_2014_population / 100.0;
                } else {
                    printf("Unknown field: %s\n", field);
                    continue;
                }
            }

            if (total_population > 0) {
                printf("2014 %s percentage: %.6f\n", field, (field_total / total_population) * 100);
            } else {
                printf("2014 %s percentage: 0.000000\n", field);
            }
        } else if (strcmp(op, "filter-state") == 0) {
            char *state = strtok(NULL, ":");
            if (!state) {
                printf("Invalid operation: Missing state for 'filter-state'\n");
                continue;
            }
            filter_state(records, &record_count, state);
        } else if (strcmp(op, "filter") == 0) {
            char *field = strtok(NULL, ":");
            char *comparison = strtok(NULL, ":");
            char *value_str = strtok(NULL, ":");
            if (!field || !comparison || !value_str) {
                printf("Invalid filter operation: Missing arguments\n");
                continue;
            }
            float value = atof(value_str); // Convert value to a float
            filter(records, &record_count, field, comparison, value);
        } else {
            printf("Unknown operation: %s\n", op);
        } 
    }

    fclose(ops_file);
    return 0;
}