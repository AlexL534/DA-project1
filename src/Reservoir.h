#ifndef WATER_SUPPLY_MANAGEMENT_RESERVOIR_H
#define WATER_SUPPLY_MANAGEMENT_RESERVOIR_H

#include <string>

class Reservoir {
private:
    std::string name;
    std::string municipality;
    int id;
    std::string code;
    int maxDelivery;

public:
    Reservoir();

    Reservoir(
        const std::string &name,
        const std::string &municipality,
        const int &id,
        const std::string &code,
        const int &maxDelivery
    );

    std::string getName() const;
    std::string getMunicipality() const;
    /**
     * @brief Get the id of the reservoir
     *
     * @return int
     */
    int getId() const;
    /**
     * @brief Get the code of the reservoir
     *
     * @return string
     */
    std::string getCode() const;
    /**
     * @brief Get the max delivery of the reservoir
     *
     * @return int
     */
    int getMaxDelivery() const;
    bool operator<(const Reservoir r) const{
        return code < r.code;
    }
    bool operator==(const Reservoir r) const{
        return code == r.code;
    }

};


#endif //WATER_SUPPLY_MANAGEMENT_RESERVOIR_H
