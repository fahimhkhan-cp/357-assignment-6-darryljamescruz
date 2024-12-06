#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include "data.h"

#include <string.h>
#include <ctype.h>
#include <errno.h>

// Helper function to remove leading/trailing whitespace
void trim_whitespace(char *str) {
    char *end;

    // Trim leading spaces
    while (isspace((unsigned char)*str)) str++;

    // Trim trailing spaces
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;
    end[1] = '\0';
}

// Helper function to remove leading and trailing quotes from strings
void strip_quotes(char *str) {
    size_t len = strlen(str);
    if (len > 1 && str[0] == '"' && str[len - 1] == '"') {
        memmove(str, str + 1, len - 2);  // Remove the first and last characters
        str[len - 2] = '\0';  // Null-terminate the string
    }
}

// Parse a long long number from a string
long long parse_long_long(char *str) {
    strip_quotes(str); // Clean the string before parsing
    char *endptr;
    long long value = strtoll(str, &endptr, 10);
    if (*endptr != '\0') {
        fprintf(stderr, "Error parsing long long: '%s'\n", str);
        return 0;  // You can return an error code if needed
    }
    return value;
}

// Parse a double number from a string
double parse_double(char *str) {
    strip_quotes(str); // Clean the string before parsing
    char *endptr;
    double value = strtod(str, &endptr);
    if (*endptr != '\0') {
        fprintf(stderr, "Error parsing double: '%s'\n", str);
        return 0.0;  // You can return an error code if needed
    }
    return value;
}

// Parse a single line of CSV
int parse_line(char *line, Demographic *info) {
    char buffer[4000];
    strncpy(buffer, line, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';

    char *token = strtok(buffer, ",");
    if (!token) return -1;
    trim_whitespace(token);
    strip_quotes(token);  // Strip quotes from the token
    strncpy(info->county, token, sizeof(info->county) - 1);
    info->county[sizeof(info->county) - 1] = '\0';

    token = strtok(NULL, ",");
    if (!token) return -1;
    trim_whitespace(token);
    strip_quotes(token);  // Strip quotes from the token
    strncpy(info->state, token, sizeof(info->state) - 1);
    info->state[sizeof(info->state) - 1] = '\0';

    // Parse numeric fields
    info->age_percent_65_and_older = parse_double(strtok(NULL, ","));
    info->age_percent_under_18_years = parse_double(strtok(NULL, ","));
    info->age_percent_under_5_years = parse_double(strtok(NULL, ","));
    info->education_bachelors_degree_or_higher = parse_double(strtok(NULL, ","));
    info->education_high_school_or_higher = parse_double(strtok(NULL, ","));
    info->employment_nonemployer_establishments = parse_long_long(strtok(NULL, ","));
    info->employment_private_non_farm_employment = parse_long_long(strtok(NULL, ","));
    info->employment_private_non_farm_employment_change = parse_double(strtok(NULL, ","));
    info->employment_private_non_farm_establishments = parse_long_long(strtok(NULL, ","));
    info->ethnicities_american_indian_and_alaska_native_alone = parse_double(strtok(NULL, ","));
    info->ethnicities_asian_alone = parse_double(strtok(NULL, ","));
    info->ethnicities_black_alone = parse_double(strtok(NULL, ","));
    info->ethnicities_hispanic_or_latino = parse_double(strtok(NULL, ","));
    info->ethnicities_native_hawaiian_and_other_pacific_islander_alone = parse_double(strtok(NULL, ","));
    info->ethnicities_two_or_more_races = parse_double(strtok(NULL, ","));
    info->ethnicities_white_alone = parse_double(strtok(NULL, ","));
    info->ethnicities_white_alone_not_hispanic_or_latino = parse_double(strtok(NULL, ","));
    info->housing_homeownership_rate = parse_double(strtok(NULL, ","));
    info->housing_households = parse_long_long(strtok(NULL, ","));
    info->housing_housing_units = parse_long_long(strtok(NULL, ","));
    info->housing_median_value_of_owner_occupied_units = parse_long_long(strtok(NULL, ","));
    info->housing_persons_per_household = parse_double(strtok(NULL, ","));
    info->housing_units_in_multi_unit_structures = parse_double(strtok(NULL, ","));
    info->income_median_household_income = parse_long_long(strtok(NULL, ","));
    info->income_per_capita_income = parse_long_long(strtok(NULL, ","));
    info->income_persons_below_poverty_level = parse_double(strtok(NULL, ","));
    info->miscellaneous_building_permits = parse_long_long(strtok(NULL, ","));
    info->miscellaneous_foreign_born = parse_double(strtok(NULL, ","));
    info->miscellaneous_land_area = parse_double(strtok(NULL, ","));
    info->miscellaneous_language_other_than_english_at_home = parse_double(strtok(NULL, ","));
    info->miscellaneous_living_in_same_house_1_year = parse_double(strtok(NULL, ","));
    info->miscellaneous_manufacturers_shipments = parse_long_long(strtok(NULL, ","));
    info->miscellaneous_mean_travel_time_to_work = parse_double(strtok(NULL, ","));
    info->miscellaneous_percent_female = parse_double(strtok(NULL, ","));
    info->miscellaneous_veterans = parse_long_long(strtok(NULL, ","));
    info->population_2010_population = parse_long_long(strtok(NULL, ","));
    info->population_2014_population = parse_long_long(strtok(NULL, ","));
    info->population_population_percent_change = parse_double(strtok(NULL, ","));
    info->population_population_per_square_mile = parse_double(strtok(NULL, ","));
    info->sales_accommodation_and_food_services_sales = parse_long_long(strtok(NULL, ","));
    info->sales_merchant_wholesaler_sales = parse_long_long(strtok(NULL, ","));
    info->sales_retail_sales = parse_long_long(strtok(NULL, ","));
    info->sales_retail_sales_per_capita = parse_long_long(strtok(NULL, ","));
    info->employment_firms_american_indian_owned = parse_long_long(strtok(NULL, ","));
    info->employment_firms_asian_owned = parse_long_long(strtok(NULL, ","));
    info->employment_firms_black_owned = parse_long_long(strtok(NULL, ","));
    info->employment_firms_hispanic_owned = parse_long_long(strtok(NULL, ","));
    info->employment_firms_native_hawaiian_owned = parse_long_long(strtok(NULL, ","));
    info->employment_firms_total = parse_long_long(strtok(NULL, ","));
    info->employment_firms_women_owned = parse_long_long(strtok(NULL, ","));

    return 0;
}

// Load demographics from CSV file
int load_demographics(const char *filename, Demographic *records, int max_records) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return -1;
    }

    char *line = malloc(4000);
    if (!line) {
        perror("Error allocating memory");
        fclose(file);
        return -1;
    }

    int count = 0;
    fgets(line, 4000, file); // Skip header

    while (fgets(line, 4000, file)) {
        if (count >= max_records) {
            fprintf(stderr, "Max records reached. Skipping line.\n");
            continue;
        }

        if (parse_line(line, &records[count]) == 0) {
            count++;
        } else {
            fprintf(stderr, "Malformed line. Skipping...\n");
        }
    }

    free(line);
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
        } else if (strcmp(field, "Ethnicities.Native Hawaiian and Other Pacific Islander Alone") == 0) {
            field_value = records[i].ethnicities_native_hawaiian_and_other_pacific_islander_alone;
        } else if (strcmp(field, "Ethnicities.Two or More Races") == 0) {
            field_value = records[i].ethnicities_two_or_more_races;
        } else if (strcmp(field, "Ethnicities.White Alone") == 0) {
            field_value = records[i].ethnicities_white_alone;
        } else if (strcmp(field, "Ethnicities.White Alone, not Hispanic or Latino") == 0) {
            field_value = records[i].ethnicities_white_alone_not_hispanic_or_latino;
        } else {
            printf("Unknown field: %s\n", field);
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

    printf("Filter: %s, %s, %.2f (%d entries)\n", field, comparison, value, *count);
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
        printf("\t\tNative Hawaiian and Other Pacific Islander: %.2f%%\n", records[i].ethnicities_native_hawaiian_and_other_pacific_islander_alone);
        printf("\t\tTwo or More Races: %.2f%%\n", records[i].ethnicities_two_or_more_races);
        printf("\t\tWhite Alone: %.2f%%\n", records[i].ethnicities_white_alone);
        printf("\t\tWhite Alone, Not Hispanic or Latino: %.2f%%\n", records[i].ethnicities_white_alone_not_hispanic_or_latino);
        printf("\tIncome:\n");
        printf("\t\tMedian Household Income: %lld\n", records[i].income_median_household_income);
        printf("\t\tPer Capita Income: %lld\n", records[i].income_per_capita_income);
        printf("\t\tBelow Poverty Level: %.2f%%\n", records[i].income_persons_below_poverty_level);
    }
}