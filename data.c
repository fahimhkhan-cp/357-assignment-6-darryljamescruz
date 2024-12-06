#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"

// Trim whitespace and remove enclosing quotes
void trim_whitespace(char *str) {
    int len = strlen(str);
    if (len > 1 && str[0] == '"' && str[len - 1] == '"') {
        memmove(str, str + 1, len - 2);
        str[len - 2] = '\0';
    }
}

// Helper to parse long long values safely
long long parse_long_long(char *token) {
    if (!token || strlen(token) == 0) {
        return 0; // Default value for missing fields
    }
    trim_whitespace(token);
    return atoll(token);
}

// Helper to parse double values safely
double parse_double(char *token) {
    if (!token || strlen(token) == 0) {
        return 0.0; // Default value for missing fields
    }
    trim_whitespace(token);
    return atof(token);
}

// Parse a single CSV line
int parse_line(char *line, Demographic *info) {
    char buffer[4000];
    strcpy(buffer, line);

    char *token = strtok(buffer, ",");
    if (!token) return -1;
    trim_whitespace(token);
    strcpy(info->county, token);

    token = strtok(NULL, ",");
    if (!token) return -1;
    trim_whitespace(token);
    strcpy(info->state, token);

    // Parse all fields using helper functions
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

    char line[4000];
    int count = 0;

    // Skip the header
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        if (count >= max_records) {
            fprintf(stderr, "Warning: Max records reached. Skipping line.\n");
            continue;
        }

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