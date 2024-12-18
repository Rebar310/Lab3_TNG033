/*****************************************
 * Lab 3: exercise 1                      *
 ******************************************/
 
// I denna del av labben så ska man göra en "tracker" som håller koll på lånen 
// mellan en vän grupp.


#include <iostream>      // For in and output
#include <map>           // To store the balances for each person
#include <vector>        // To store multiple values in a sequential container
#include <algorithm>     // For sorting and partitioning
#include <numeric>       // For accumulation (summing values)
#include <cmath>         // For mathematical operators (if needed)
#include <iterator>      // For working with iterators and output streams
#include <string>        // For handeling strings

// <Payer name> <Receiver name> <price> , ska fås via std::cin
// Initialer på den som är skyldig och den som ska få pengar och sen summan
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

    // Variables to store transaction details and balances
    int price;                             // Amount of the transaction
    std::string payer;                     // Person lending the money
    std::string receiver;                  // Person receiving the money
    std::map<std::string, int> balances;   // Map to keep track of each person's balance
     
    // std::map< "key", "value"> 
    // is an associative container that stores elements as key-value pairs.


    // Step 1: Read loans from the user
    std::cout << "Enter list of friend-to-friend loans: ... ( to finish write z^)\n";

    // Read until user provides invalid input (e.g., non-numeric or unexpected input)
    while (std::cin >> payer >> receiver >> price) {
        balances[payer] += price;           // Add the amount to the payer's balance
        balances[receiver] -= price;        // Subtract the amount from the receiver's balance
    }

    // Step 2: Create a list of balance entries for sorting (fallande ordning)
    // std::pair used to pair up values with eachother, can be different types
    // balances.begin() and balances.end() are iterators representing the start and end of the map.
    std::vector<std::pair<std::string, int>> sorted_balances(balances.begin(), balances.end());


    // Sort the balances by amount
    // Positive balances (loans) will appear in descending order
    std::sort(sorted_balances.begin(), sorted_balances.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;  // Larger values appear first
    });
    

    // Separate balances into two lists: loans and debts
    std::vector<std::pair<std::string, int>> loans, debts;

    // std::partition_copy: It takes a range of elements, a condition (predicate), and two output iterators.
    // All elements that do not satisfy the condition are copied into the second output range.
    // [](const auto& entry) { return entry.second > 0; } It checks whether the second value of a std::pair in 
    // sorted_balances (the integer balance) is positive.
    std::partition_copy(sorted_balances.begin(), sorted_balances.end(),
        std::back_inserter(loans), std::back_inserter(debts),
        [](const auto& entry) { return entry.second > 0; });

    //std::back_inserter(container), it: Creates an output iterator.
    //Every time the algorithm writes to this iterator, 
    // it calls container.push_back(value) to append the value to the container.

    // Print loans
    std::cout << "Name  Balance:\n";
    //std::transform is used to apply a transformation to each element in a range 
    // and send the result to an output iterator
    std::transform(loans.begin(), loans.end(),
        std::ostream_iterator<std::string>(std::cout, "\n"),   // This creates an output iterator that writes strings to std::cout.
        [](const auto& entry) {
            return entry.first + "      " + std::to_string(entry.second); //Lambada function is for specyfying the output
        });

    // Print debts (same principles as the one above)
    std::transform(debts.begin(), debts.end(),
        std::ostream_iterator<std::string>(std::cout, "\n"),
        [](const auto& entry) {
            return entry.first + "      " + std::to_string(entry.second);
        });

    // Extract loan and debt amounts into separate vectors
    std::vector<int> loan_amounts, debt_amounts;

    std::transform(loans.begin(), loans.end(), std::back_inserter(loan_amounts),
        [](const auto& entry) { return entry.second; });
    std::transform(debts.begin(), debts.end(), std::back_inserter(debt_amounts),
        [](const auto& entry) { return -entry.second; });

     // Calculate the mean loan amount
    // std::accumulate This function is used to compute the sum of all elements in the range
    //The total sum is divided by the number of elements in the vector to compute the mean.
    double mean_loan = loan_amounts.empty() ? 0.0 : //checks if vector is empty and if that is the cas puts in 0.0
        std::accumulate(loan_amounts.begin(), loan_amounts.end(), 0.0) / loan_amounts.size(); 
    // Calculate the mean debt amount
    double mean_debt = debt_amounts.empty() ? 0.0 :
        std::accumulate(debt_amounts.begin(), debt_amounts.end(), 0.0) / debt_amounts.size();

    // Print the calculated mean values
    std::cout << "\nMean loan amount: " << mean_loan << "\n";
    std::cout << "Mean debt amount: " << mean_debt << "\n";

    return 0;  // Exit the program



}