/*****************************************
 * Lab 3: exercise 1                      *
 ******************************************/
 
// I denna del av labben s� ska man g�ra en "tracker" som h�ller koll p� l�nen 
// mellan en v�n grupp.


#include <iostream>  //standard
#include <map>       // anv�nds f�r att ber�kna totala skuld summan 
#include <vector>    // F�r att lagra flera v�rden smidigt
#include <algorithm>  
#include <numeric>
#include <cmath>
#include <iterator>
#include <string>

// <Payer name> <Receiver name> <price> , ska f�s via std::cin
// Initialer p� den som �r skyldig och den 
// som ska f� pengar och sen summan
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

    // Deklarerar de variabler vi beh�ver
    int price;
    std::string payer;
    std::string receiver;
    std::map<std::string, int> balances;
     
    // Steg 1: L�s in l�n fr�n std::cin
    std::cout << "Enter list of friend-to-friend loans: ... ( to finish write z^)\n";

    while (std::cin >> payer >> receiver >> price) {
        balances[payer] += price; // L�n fr�n payer (�kar balans)
        balances[receiver] -= price; // Skuld f�r receiver (minskar balans)
    }

    // Steg 2: Sortera l�n i fallande ordning och skulder i stigande ordning
    std::vector<std::pair<std::string, int>> sorted_balances(balances.begin(), balances.end());

    // Sortera l�n i fallande ordning (positiva v�rden)
    std::sort(sorted_balances.begin(), sorted_balances.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;  // J�mf�r balanser
    });
    
    // Anv�nd std::partition_copy f�r att separera l�n och skulder
    std::vector<std::pair<std::string, int>> loans, debts;
    std::partition_copy(sorted_balances.begin(), sorted_balances.end(),
        std::back_inserter(loans), std::back_inserter(debts),
        [](const auto& entry) { return entry.second > 0; });

    // Skriv ut l�n och skulder med std::transform och std::ostream_iterator
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

    // Separera och summera l�n och skulder f�r att ber�kna medelv�rden
    std::vector<int> loan_amounts, debt_amounts;
    std::transform(loans.begin(), loans.end(), std::back_inserter(loan_amounts),
        [](const auto& entry) { return entry.second; });
    std::transform(debts.begin(), debts.end(), std::back_inserter(debt_amounts),
        [](const auto& entry) { return -entry.second; });

    // Medelv�rdesber�kning
    double mean_loan = loan_amounts.empty() ? 0.0 :
        std::accumulate(loan_amounts.begin(), loan_amounts.end(), 0.0) / loan_amounts.size();
    double mean_debt = debt_amounts.empty() ? 0.0 :
        std::accumulate(debt_amounts.begin(), debt_amounts.end(), 0.0) / debt_amounts.size();

    
    std::cout << "\nMean loan amount: " << mean_loan << "\n";
    std::cout << "Mean debt amount: " << mean_debt << "\n";

    return 0; // endast f�r att ta bort extra on�dig kod



}