//
// Created by Tomás Silva on 18/03/2024.
//
#include <iostream>
#include "Actions.h"

void menu(Graph& graph, Actions& actions){
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
                if(subChoice == 1) {
                    std::string city;
                    std::cout << "Enter the city code: ";
                    std::cin >> city;

                    int maxFlow = actions.maxFlowSpecificCity(graph, city);

                    std::cout << "The maximum amount of water that can reach " << city << " is " << maxFlow << std::endl;
                } else if(subChoice == 2) {
                    // Call the function to determine the maximum amount of water that can reach each city
                    map<string, int> cityFlow = actions.maxFlowAllCities(graph);

                    for(auto it : cityFlow){
                        std::cout << it.first << ' ' << it.second << std::endl;
                    }

                }
                else {
                    std::cout << "Invalid choice. Please enter 1 or 2.\n";
                }
                break;
            case 2:
                // Call the function to check if an existing network configuration can meet the water needs of its customer
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
                // Call the function to determine which pipelines, if ruptured, would make it impossible to deliver the desired amount of water to a given city
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