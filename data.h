#ifndef DATA_H
#define DATA_H

#define MAX_RECORDS 5000

// struct store all the expected header info from county_demographics
typedef struct {
    char county[100];
    char state[3];
    float age_percent_65_and_older;
    float age_percent_under_18_years;
    float age_percent_under_5_years;
    float education_bachelors_degree_or_higher;
    float education_high_school_or_higher;
    long long employment_nonemployer_establishments;
    long long employment_private_non_farm_employment;
    float employment_private_non_farm_employment_change;
    long long employment_private_non_farm_establishments;
    float ethnicities_american_indian_and_alaska_native_alone;
    float ethnicities_asian_alone;
    float ethnicities_black_alone;
    float ethnicities_hispanic_or_latino;
    float ethnicities_native_hawaiian_and_other_pacific_islander_alone;
    float ethnicities_two_or_more_races;
    float ethnicities_white_alone;
    float ethnicities_white_alone_not_hispanic_or_latino;
    float housing_homeownership_rate;
    long long housing_households;
    long long housing_housing_units;
    long long housing_median_value_of_owner_occupied_units;
    float housing_persons_per_household;
    float housing_units_in_multi_unit_structures;
    long long income_median_household_income;
    long long income_per_capita_income;
    float income_persons_below_poverty_level;
    long long miscellaneous_building_permits;
    float miscellaneous_foreign_born;
    float miscellaneous_land_area;
    float miscellaneous_language_other_than_english_at_home;
    float miscellaneous_living_in_same_house_1_year;
    long long miscellaneous_manufacturers_shipments;
    float miscellaneous_mean_travel_time_to_work;
    float miscellaneous_percent_female;
    long long miscellaneous_veterans;
    long long population_2010_population;
    long long population_2014_population;
    float population_population_percent_change;
    float population_population_per_square_mile;
    long long sales_accommodation_and_food_services_sales;
    long long sales_merchant_wholesaler_sales;
    long long sales_retail_sales;
    long long sales_retail_sales_per_capita;
    long long employment_firms_american_indian_owned;
    long long employment_firms_asian_owned;
    long long employment_firms_black_owned;
    long long employment_firms_hispanic_owned;
    long long employment_firms_native_hawaiian_owned;
    long long employment_firms_total;
    long long employment_firms_women_owned;
} Demographic;

int parse_line(char *line, Demographic *info);
int load_demographics(const char *filename, Demographic *records, int max_records);

#endif