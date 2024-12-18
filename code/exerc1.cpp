/*****************************************
 * Lab 3: exercise 1                      *
 ******************************************/
 
// I denna del av labben så ska man göra en "tracker" som håller koll på lånen 
// mellan en vän grupp.


#include <iostream>  //standard
#include <map>       // används för att beräkna totala skuld summan 
#include <vector>    // För att lagra flera värden smidigt
#include <algorithm>  
#include <numeric>
#include <cmath>
#include <iterator>
#include <string>

// <Payer name> <Receiver name> <price> , ska fås via std::cin
// Initialer på den som är skyldig och den 
// som ska få pengar och sen summan
 /*
AE EM 102
AN PS 190
EM BD 23
CK EM 15
FF CK 17
AE CK 9
PS FF 50
DH FF 35
DH EM 65
PS AN 75
FF CK 18
AE EM 91
JP FF 203
*/

int main() {

    // Deklarerar de variabler vi behöver
    int price;
    std::string payer;
    std::string receiver;
    std::map<std::string, int> balances;
     
    // Steg 1: Läs in lån från std::cin
    std::cout << "Enter list of friend-to-friend loans: ... ( to finish write z^)\n";

    while (std::cin >> payer >> receiver >> price) {
        balances[payer] += price; // Lån från payer (ökar balans)
        balances[receiver] -= price; // Skuld för receiver (minskar balans)
    }

    // Steg 2: Sortera lån i fallande ordning och skulder i stigande ordning
    std::vector<std::pair<std::string, int>> sorted_balances(balances.begin(), balances.end());

    // Sortera lån i fallande ordning (positiva värden)
    std::sort(sorted_balances.begin(), sorted_balances.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;  // Jämför balanser
    });
    
    // Använd std::partition_copy för att separera lån och skulder
    std::vector<std::pair<std::string, int>> loans, debts;
    std::partition_copy(sorted_balances.begin(), sorted_balances.end(),
        std::back_inserter(loans), std::back_inserter(debts),
        [](const auto& entry) { return entry.second > 0; });

    // Skriv ut lån och skulder med std::transform och std::ostream_iterator
    std::cout << "Name  Balance:\n";
    std::transform(loans.begin(), loans.end(),
        std::ostream_iterator<std::string>(std::cout, "\n"),
        [](const auto& entry) {
            return entry.first + "      " + std::to_string(entry.second);
        });

    std::transform(debts.begin(), debts.end(),
        std::ostream_iterator<std::string>(std::cout, "\n"),
        [](const auto& entry) {
            return entry.first + "      " + std::to_string(entry.second);
        });

    // Separera och summera lån och skulder för att beräkna medelvärden
    std::vector<int> loan_amounts, debt_amounts;
    std::transform(loans.begin(), loans.end(), std::back_inserter(loan_amounts),
        [](const auto& entry) { return entry.second; });
    std::transform(debts.begin(), debts.end(), std::back_inserter(debt_amounts),
        [](const auto& entry) { return -entry.second; });

    // Medelvärdesberäkning
    double mean_loan = loan_amounts.empty() ? 0.0 :
        std::accumulate(loan_amounts.begin(), loan_amounts.end(), 0.0) / loan_amounts.size();
    double mean_debt = debt_amounts.empty() ? 0.0 :
        std::accumulate(debt_amounts.begin(), debt_amounts.end(), 0.0) / debt_amounts.size();

    
    std::cout << "\nMean loan amount: " << mean_loan << "\n";
    std::cout << "Mean debt amount: " << mean_debt << "\n";

    return 0; // endast för att ta bort extra onödig kod



}