//
// Created by Tomás Silva on 18/03/2024.
//
#include <iostream>


void menu(){
    int choice;
    do {
        std::cout << "-------------------------------------------------------\n";
        std::cout << "Welcome to An Analysis Tool for Water Supply Management\n";
        std::cout << "-------------------------------------------------------\n";
        std::cout << "1. Determine the maximum amount of water that can reach each city\n";
        std::cout << "2. Check if an existing network configuration can meet the water needs of its customer\n";
        std::cout << "3. Balance the load across the network\n";
        std::cout << "4. Evaluate the network's resiliency if one specific water reservoir is out of commission\n";
        std::cout << "5. Check if any pumping station can be temporarily taken out of service without affecting the delivery capacity\n";
        std::cout << "6. Determine which pipelines, if ruptured, would make it impossible to deliver the desired amount of water to a given city\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch(choice) {
            case 1:
                // Call the function to determine the maximum amount of water that can reach each city
                break;
            case 2:
                // Call the function to check if an existing network configuration can meet the water needs of its customer
                break;
            case 3:
                // Call the function to balance the load across the network
                break;
            case 4:
                // Call the function to evaluate the network's resiliency if one specific water reservoir is out of commission
                break;
            case 5:
                // Call the function to check if any pumping station can be temporarily taken out of service without affecting the delivery capacity
                break;
            case 6:
                // Call the function to determine which pipelines, if ruptured, would make it impossible to deliver the desired amount of water to a given city
                break;
            default:
                std::cout << "Invalid choice. Please enter a number between 1 and 6.\n";
                break;
        }
    } while(choice < 1 || choice > 6);
}