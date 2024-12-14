#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"

int parse_line(char *line, Demographic *info) {
    char *token;

    // Parse County
    token = strtok(line, ",");
    if (!token) return -1;
    strncpy(info->county, token, sizeof(info->county) - 1);

    // Parse State
    token = strtok(NULL, ",");
    if (!token) return -1;
    strncpy(info->state, token, sizeof(info->state) - 1);

    // Parse Education.High School or Higher
    token = strtok(NULL, ",");
    if (!token) return -1;
    info->education_high_school_or_higher = atof(token);

    // Parse Education.Bachelor's Degree or Higher
    token = strtok(NULL, ",");
    if (!token) return -1;
    info->education_bachelors_degree_or_higher = atof(token);

    // Parse Ethnicities.American Indian and Alaska Native Alone
    token = strtok(NULL, ",");
    if (!token) return -1;
    info->ethnicities_american_indian_and_alaska_native_alone = atof(token);

    // Parse Ethnicities.Asian Alone
    token = strtok(NULL, ",");
    if (!token) return -1;
    info->ethnicities_asian_alone = atof(token);

    // Parse Ethnicities.Black Alone
    token = strtok(NULL, ",");
    if (!token) return -1;
    info->ethnicities_black_alone = atof(token);

    // Parse Ethnicities.Hispanic or Latino
    token = strtok(NULL, ",");
    if (!token) return -1;
    info->ethnicities_hispanic_or_latino = atof(token);

    // Parse Ethnicities.Native Hawaiian and Other Pacific Islander Alone
    token = strtok(NULL, ",");
    if (!token) return -1;
    info->ethnicities_native_hawaiian_and_other_pacific_islander_alone = atof(token);

    // Parse Ethnicities.Two or More Races
    token = strtok(NULL, ",");
    if (!token) return -1;
    info->ethnicities_two_or_more_races = atof(token);

    // Parse Ethnicities.White Alone
    token = strtok(NULL, ",");
    if (!token) return -1;
    info->ethnicities_white_alone = atof(token);

    // Parse Ethnicities.White Alone, Not Hispanic or Latino
    token = strtok(NULL, ",");
    if (!token) return -1;
    info->ethnicities_white_alone_not_hispanic_or_latino = atof(token);

    // Parse Income.Persons Below Poverty Level
    token = strtok(NULL, ",");
    if (!token) return -1;
    info->income_persons_below_poverty_level = atof(token);

    // Parse Population.2014 Population
    token = strtok(NULL, ",");
    if (!token) return -1;
    info->population_2014_population = atoll(token);

    return 0;
}

int load_demographics(const char *filename, Demographic *records, int max_records) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return -1;
    }

    char line[4000];
    int count = 0;

    // Skip the header
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        if (count >= max_records) {
            fprintf(stderr, "Warning: Max records reached. Skipping line.\n");
            continue;
        }

        // Remove trailing newline characters
        line[strcspn(line, "\r\n")] = '\0';

        // Parse and validate line
        if (parse_line(line, &records[count]) == 0) {
            count++;
        } else {
            fprintf(stderr, "Warning: Malformed line. Skipping...\n");
        }
    }

    fclose(file);
    return count;
}

void filter_state(Demographic *records, int *record_count, const char *state) {
    int new_count = 0;
    for (int i = 0; i < *record_count; i++) {
        if (strcmp(records[i].state, state) == 0) {
            records[new_count++] = records[i];
        }
    }
    *record_count = new_count;
    printf("Filter: state == %s (%d entries)\n", state, new_count);
}

void filter(Demographic *records, int *count, const char *field, const char *comparison, float value) {
    int new_count = 0;

    for (int i = 0; i < *count; i++) {
        float field_value = 0.0;

        // Map field names to struct members
        if (strcmp(field, "Education.High School or Higher") == 0) {
            field_value = records[i].education_high_school_or_higher;
        } else if (strcmp(field, "Education.Bachelor's Degree or Higher") == 0) {
            field_value = records[i].education_bachelors_degree_or_higher;
        } else if (strcmp(field, "Ethnicities.American Indian and Alaska Native Alone") == 0) {
            field_value = records[i].ethnicities_american_indian_and_alaska_native_alone;
        } else if (strcmp(field, "Ethnicities.Asian Alone") == 0) {
            field_value = records[i].ethnicities_asian_alone;
        } else if (strcmp(field, "Ethnicities.Black Alone") == 0) {
            field_value = records[i].ethnicities_black_alone;
        } else if (strcmp(field, "Ethnicities.Hispanic or Latino") == 0) {
            field_value = records[i].ethnicities_hispanic_or_latino;
        } else if (strcmp(field, "Ethnicities.White Alone") == 0) {
            field_value = records[i].ethnicities_white_alone;
        } else if (strcmp(field, "Income.Persons Below Poverty Level") == 0) {
            field_value = records[i].income_persons_below_poverty_level;
        } else {
            fprintf(stderr, "Error: Unknown field '%s'. Skipping...\n", field);
            continue;
        }

        // Apply the comparison
        int include = 0;
        if (strcmp(comparison, "le") == 0 && field_value <= value) {
            include = 1;
        } else if (strcmp(comparison, "ge") == 0 && field_value >= value) {
            include = 1;
        }

        // Include the record if it matches the criteria
        if (include) {
            records[new_count++] = records[i];
        }
    }

    // Update the count of filtered records
    *count = new_count;

    printf("Filter: %s %s %.2f (%d entries)\n", field, comparison, value, *count);
}

void display(const Demographic *records, int count) {
    for (int i = 0; i < count; i++) {
        printf("%s, %s\n", records[i].county, records[i].state);
        printf("\tPopulation: %lld\n", records[i].population_2014_population);
        printf("\tEducation:\n");
        printf("\t\t>= High School: %.2f%%\n", records[i].education_high_school_or_higher);
        printf("\t\t>= Bachelor's Degree: %.2f%%\n", records[i].education_bachelors_degree_or_higher);
        printf("\tEthnicities:\n");
        printf("\t\tAmerican Indian and Alaska Native: %.2f%%\n", records[i].ethnicities_american_indian_and_alaska_native_alone);
        printf("\t\tAsian: %.2f%%\n", records[i].ethnicities_asian_alone);
        printf("\t\tBlack: %.2f%%\n", records[i].ethnicities_black_alone);
        printf("\t\tHispanic or Latino: %.2f%%\n", records[i].ethnicities_hispanic_or_latino);
        printf("\t\tWhite Alone: %.2f%%\n", records[i].ethnicities_white_alone);
        printf("\tIncome:\n");
        printf("\t\tBelow Poverty Level: %.2f%%\n", records[i].income_persons_below_poverty_level);
    }
}