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

    // Parse remaining fields (convert to appropriate types)
    info->age_percent_65_and_older = atof(strtok(NULL, ","));
    info->age_percent_under_18_years = atof(strtok(NULL, ","));
    info->age_percent_under_5_years = atof(strtok(NULL, ","));
    info->education_bachelors_degree_or_higher = atof(strtok(NULL, ","));
    info->education_high_school_or_higher = atof(strtok(NULL, ","));
    info->employment_nonemployer_establishments = atoll(strtok(NULL, ","));
    info->employment_private_non_farm_employment = atoll(strtok(NULL, ","));
    info->employment_private_non_farm_employment_change = atof(strtok(NULL, ","));
    info->employment_private_non_farm_establishments = atoll(strtok(NULL, ","));
    info->ethnicities_american_indian_and_alaska_native_alone = atof(strtok(NULL, ","));
    info->ethnicities_asian_alone = atof(strtok(NULL, ","));
    info->ethnicities_black_alone = atof(strtok(NULL, ","));
    info->ethnicities_hispanic_or_latino = atof(strtok(NULL, ","));
    info->ethnicities_native_hawaiian_and_other_pacific_islander_alone = atof(strtok(NULL, ","));
    info->ethnicities_two_or_more_races = atof(strtok(NULL, ","));
    info->ethnicities_white_alone = atof(strtok(NULL, ","));
    info->ethnicities_white_alone_not_hispanic_or_latino = atof(strtok(NULL, ","));
    info->housing_homeownership_rate = atof(strtok(NULL, ","));
    info->housing_households = atoll(strtok(NULL, ","));
    info->housing_housing_units = atoll(strtok(NULL, ","));
    info->housing_median_value_of_owner_occupied_units = atoll(strtok(NULL, ","));
    info->housing_persons_per_household = atof(strtok(NULL, ","));
    info->housing_units_in_multi_unit_structures = atof(strtok(NULL, ","));
    info->income_median_household_income = atoll(strtok(NULL, ","));
    info->income_per_capita_income = atoll(strtok(NULL, ","));
    info->income_persons_below_poverty_level = atof(strtok(NULL, ","));
    info->miscellaneous_building_permits = atoll(strtok(NULL, ","));
    info->miscellaneous_foreign_born = atof(strtok(NULL, ","));
    info->miscellaneous_land_area = atof(strtok(NULL, ","));
    info->miscellaneous_language_other_than_english_at_home = atof(strtok(NULL, ","));
    info->miscellaneous_living_in_same_house_1_year = atof(strtok(NULL, ","));
    info->miscellaneous_manufacturers_shipments = atoll(strtok(NULL, ","));
    info->miscellaneous_mean_travel_time_to_work = atof(strtok(NULL, ","));
    info->miscellaneous_percent_female = atof(strtok(NULL, ","));
    info->miscellaneous_veterans = atoll(strtok(NULL, ","));
    info->population_2010_population = atoll(strtok(NULL, ","));
    info->population_2014_population = atoll(strtok(NULL, ","));
    info->population_population_percent_change = atof(strtok(NULL, ","));
    info->population_population_per_square_mile = atof(strtok(NULL, ","));
    info->sales_accommodation_and_food_services_sales = atoll(strtok(NULL, ","));
    info->sales_merchant_wholesaler_sales = atoll(strtok(NULL, ","));
    info->sales_retail_sales = atoll(strtok(NULL, ","));
    info->sales_retail_sales_per_capita = atoll(strtok(NULL, ","));
    info->employment_firms_american_indian_owned = atoll(strtok(NULL, ","));
    info->employment_firms_asian_owned = atoll(strtok(NULL, ","));
    info->employment_firms_black_owned = atoll(strtok(NULL, ","));
    info->employment_firms_hispanic_owned = atoll(strtok(NULL, ","));
    info->employment_firms_native_hawaiian_owned = atoll(strtok(NULL, ","));
    info->employment_firms_total = atoll(strtok(NULL, ","));
    info->employment_firms_women_owned = atoll(strtok(NULL, ","));

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