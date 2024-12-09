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
    

    // Steg 3: Skriv ut sammanfattning av l�n och skulder
    // F�rsta delen skriver ut de som l�nar ut pengar ("lends")
    std::cout << "Name  Balance:\n";
    for (const auto& entry : sorted_balances) {
        if (entry.second > 0) {
            std::cout << entry.first << "      " << entry.second << "\n";
        }
    }

    // H�r s� skrivs summor ut till vilka som �r skyldiga ut med minustecken ( "owes")
    for (const auto& entry : sorted_balances) {
        if (entry.second < 0) {
            std::cout << entry.first << "      " << entry.second << "\n";
        }
    }

    // Steg 4: Ber�kna och skriv ut medelv�rde f�r l�n och skulder
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

    return 0; // endast f�r att ta bort extra on�dig kod



}