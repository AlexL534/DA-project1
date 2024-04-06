#include <iostream>
#include "Actions.h"

void menu(Graph& graph, Actions& actions){
    std::vector<City> cities = parseCities();
    std::map<std::string, std::string> cityCodeMap = createCityCodeMap(cities);
    map<string, int> citiesInNeed;
    int choice;
    do {
        std::cout << "-------------------------------------------------------\n";
        std::cout << "Welcome to Water Supply Management Analysis Tool\n";
        std::cout << "-------------------------------------------------------\n";
        std::cout << "1. Determine the maximum amount of water that can reach a specific city or each city\n";
        std::cout << "2. Check if an existing network configuration can meet the water needs of its customer\n";
        std::cout << "3. Balance the load across the network\n";
        std::cout << "4. Evaluate the network's resiliency if one specific water reservoir is out of commission\n";
        std::cout << "5. Check if any pumping station can be temporarily taken out of service without affecting the delivery capacity\n";
        std::cout << "6. Determine which pipelines, if ruptured, would make it impossible to deliver the desired amount of water to a given city\n";
        std::cout << "7. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        Graph g;

        switch(choice) {
            case 1:
                std::cout << "1. See the maximum amount of water that can reach a specific city\n";
                std::cout << "2. See the maximum amount of water that can reach each city\n";
                int subChoice;
                std::cin >> subChoice;
                std::cin.ignore();  // Ignore the newline character left in the input buffer by std::cin
                if(subChoice == 1) {
                    std::string cityName;
                    std::cout << "Enter the city name: ";
                    std::cin >> cityName;

                    std::string cityCode = cityCodeMap[cityName];

                    int maxFlow = actions.maxFlowSpecificCity(graph, cityCode);

                    std::cout << "The maximum amount of water that can reach " << cityName << " is " << maxFlow << " m^3/s" << std::endl;
                } else if(subChoice == 2) {
                    map<string, int> cityFlow = actions.maxFlowAllCities(graph);

                    for(auto it : cityFlow){
                        // Get the city name from the city code
                        string cityName;
                        for (auto& city : cityCodeMap) {
                            if (city.second == it.first) {
                                cityName = city.first;
                                break;
                            }
                        }

                        std::cout << cityName << ' ' << it.second << " m^3/s" << std::endl;
                    }
                }
                else {
                    std::cout << "Invalid choice. Please enter 1 or 2.\n";
                }
                break;
            case 2:
                citiesInNeed = actions.citiesInNeed(graph);
                for(auto it:cities){
                    float value = (float) citiesInNeed[it.getCode()];
                    if(it.getDemand() - value > 0) {
                        cout << it.getCode() << "-" << it.getName() << endl;
                        cout << "Demand: " << it.getDemand() << endl;
                        cout << "Actual Flow: " << value << endl;
                        cout << "Deficit: " << it.getDemand() - value << endl;
                    }
                }
                break;
            case 3:{
                actions.balanceAndCalculateMetrics(graph);
                break;
            }
            case 4:
                // Call the function to evaluate the network's resiliency if one specific water reservoir is out of commission
                break;
            case 5:
                actions.analyzePumpingStations(graph);
                graph = g.buildGraph(parseReservoirs(),parseStations(),parsePipes(),parseCities());
                break;
            case 6:
                actions.crucialPipelines(graph);
                break;
            case 7:
                std::cout << "Exiting the program.\n";
                return; // Exit the menu loop and the function
            default:
                std::cout << "Invalid choice. Please enter a number between 1 and 6.\n";
                break;
        }

        int continueChoice;
        do {
            std::cout << "-------------------------------------------------------\n";
            std::cout << "Do you want to continue using the analysis tool?\n";
            std::cout << "1. Yes\n";
            std::cout << "2. No\n";
            std::cout << "Enter your choice: ";
            std::cin >> continueChoice;

            if (continueChoice == 2) {
                std::cout << "Exiting the program.\n";
                return; // Exit the menu loop and the function
            }
            else if (continueChoice != 1) {
                std::cout << "Invalid choice. Please enter 1 or 2.\n";
            }
        } while (continueChoice != 1);
    } while(choice != 7);
}