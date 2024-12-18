/**************************
 * Lab 3: exercise 3      *
 **************************/

// I denna exercise så ska koden läsa av en fil med "anagram" 
// (alltså bokstäver som lagts huller om buller för att bilda riktiga ord)
// T.ex på Anagram kan vara "listen" and "silent"
// Dessa två har subjektet "eilnst" gemensamt alltså
// deras gemensamma innehållande bokstäver sorterade i alfabetisk ordning.
//
// Lösning: Nyckeln är just att nyckeln i std::map<nyckeln,värde> kommer att vara subjectet


#include <iostream>       // For input and output
#include <fstream>        // For file handling
#include <map>            // To store groups of anagrams
#include <vector>         // To store lists of words
#include <algorithm>      // For sorting
#include <string>         // For handling strings
#include <set>            // For optional set usage


 
// Function to calculate the "subject" of a word (sorted letters)
// This function sorts the characters of the word in alphabetical order.
std::string get_subject(const std::string& word) {
    std::string subject = word;                 // Make a copy of the word
    std::sort(subject.begin(), subject.end());  // Sort its letters alphabetically
    return subject;                             // Return the sorted version
}

int main() {
    
    // Filsökvägar input
    // "C:\\Users\\rebec\\C++ kod\\tng033-labs\\lab3\\lab3\\code\\uppgift3_kort.txt"
    // "C:\\Users\\rebec\\C++ kod\\tng033-labs\\lab3\\lab3\\code\\uppgift3.txt"

    //Filsökvägar output
    // Resultatet hamnar i build mappen för att inte skriva över "facit-filer"

    // ***********************************************************************''

    // Växla mellan att skriva in filerna
    // Open the input file
    std::ifstream input_file("C:\\Users\\rebec\\C++ kod\\tng033-labs\\lab3\\lab3\\code\\uppgift3_kort.txt");  // Läs in från filen
    if (!input_file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    //Växla mellan att skriva in filerna 
    // out_uppgift3_kort.txt 
    // out_uppgift3.txt
    // Open the output file
    std::ofstream output_file("out_uppgift3_kort.txt");  // Skriv till filen
   
    // Map to store groups of anagrams
    // Key: "subject" (sorted letters of a word)
    // Value: Vector of words that share the same "subject"
    std::map<std::string, std::vector<std::string>> anagram_groups;  

    std::string word; // Variable to hold each word read from the file

    // Read words from the input file
    // Using normal while loop because it does'nt say that we are not allowed
    while (input_file >> word) {

        // Get the subject of the word (sorted letters)
        std::string subject = get_subject(word);   

        // Reference to the vector of words associated with the subject
        std::vector<std::string>& wordlist = anagram_groups[subject];

        // Check if the word is already in the list to avoid duplicates
        if (std::find(wordlist.begin(), wordlist.end(), word) != wordlist.end()) {
            continue; // Skip adding the word if it is already present
        }

        // Add the word to the correct anagram group
        anagram_groups[subject].push_back(word);  
    }

    // Write anagram groups with two or more words to the output file
    for (const auto& pair : anagram_groups) {
        if (pair.second.size() > 1) {  // Only consider groups with two or more words
            output_file << "Anagram group: ";

            // Sort the anagrams alphabetically before writing
            std::vector<std::string> sorted_anagrams = pair.second;
            std::sort(sorted_anagrams.begin(), sorted_anagrams.end());

            // Write each anagram in the group to the output file
            for (const auto& anagram : sorted_anagrams) {

                output_file << anagram << " ";
            }

            // Indicate the size of the group
            output_file << " ---> (" << pair.second.size() << " words" << ")\n";
        }
    }

    // Notify the user that processing is complete
    std::cout << "Anagram groups have been written to choosen file\n";

    return 0; // Return 0 to indicate successful execution



}
