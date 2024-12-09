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
    

    // Steg 3: Skriv ut sammanfattning av lån och skulder
    // Första delen skriver ut de som lånar ut pengar ("lends")
    std::cout << "Name  Balance:\n";
    for (const auto& entry : sorted_balances) {
        if (entry.second > 0) {
            std::cout << entry.first << "      " << entry.second << "\n";
        }
    }

    // Här så skrivs summor ut till vilka som är skyldiga ut med minustecken ( "owes")
    for (const auto& entry : sorted_balances) {
        if (entry.second < 0) {
            std::cout << entry.first << "      " << entry.second << "\n";
        }
    }

    // Steg 4: Beräkna och skriv ut medelvärde för lån och skulder
    std::vector<int> loans;
    std::vector<int> debts;

    for (const auto& entry : sorted_balances) {
        if (entry.second > 0) loans.push_back(entry.second);
        else debts.push_back(-entry.second);
    }

    double mean_loan = loans.empty() ? 0 : std::accumulate(loans.begin(), loans.end(), 0) / static_cast<double>(loans.size());
    double mean_debt = debts.empty() ? 0 : std::accumulate(debts.begin(), debts.end(), 0) / static_cast<double>(debts.size());

    std::cout << "\nMean loan amount: " << mean_loan << "\n";
    std::cout << "Mean debt amount: " << mean_debt << "\n";

    return 0; // endast för att ta bort extra onödig kod



}