#ifndef WATER_SUPPLY_MANAGEMENT_CITY_H
#define WATER_SUPPLY_MANAGEMENT_CITY_H

#include <string>

using namespace std;

class City {
private:
    string name;
    int id;
    string code;
    float demand;
    int population;

public:
    City();

    City(
            const string &name,
            const int &id,
            const string &code,
            const float &demand,
            const int &population
    );
    /**
     * @brief Get the name of the city
     *
     * @return string
     */
    string getName() const;
    /**
     * @brief Get the id of the city
     *
     * @return int
     */
    int getId() const;
    /**
     * @brief Get the code of the city
     *
     * @return string
     */
    string getCode() const;
    /**
     * @brief Get the demand of the city
     *
     * @return float
     */
    float getDemand() const;
    /**
     * @brief Get the population of the city
     *
     * @return int
     */
    int getPopulation() const;

    bool operator<(const City city) const{
        return id < city.id;
    }
    bool operator==(const City city) const{
        return code == city.code;
    }
};


#endif //WATER_SUPPLY_MANAGEMENT_CITY_H
