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


#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <string>
#include <set>



// Funktion för att sortera bokstäverna i ett ord alfabetiskt
std::string get_subject(const std::string& word) {
    std::string subject = word;
    std::sort(subject.begin(), subject.end());  // Sortera bokstäverna
    return subject;
}

int main() {
    
    // Filsökvägar input
    // "C:\\Users\\rebec\\C++ kod\\tng033-labs\\lab3\\lab3\\code\\uppgift3_kort.txt"
    // "C:\\Users\\rebec\\C++ kod\\tng033-labs\\lab3\\lab3\\code\\uppgift3.txt"

    //Filsökvägar output
    // Resultatet hamnar i build mappen för att inte skriva över "facit-filer"

    // ***********************************************************************''

    // Växla mellan att skriva in filerna
    std::ifstream input_file("C:\\Users\\rebec\\C++ kod\\tng033-labs\\lab3\\lab3\\code\\uppgift3_kort.txt");  // Läs in från filen
    if (!input_file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    //Växla mellan att skriva in filerna 
    // out_uppgift3_kort.txt 
    // out_uppgift3.txt
    std::ofstream output_file("out_uppgift3_kort.txt");  // Skriv till filen
   

    std::map<std::string, std::vector<std::string>> anagram_groups;  // Map för att lagra anagram-grupper

    std::string word;

    // Läs ord från filen
    while (input_file >> word) {
        std::string subject = get_subject(word);  // Hämta subject för ordet


        std::vector<std::string>& wordlist = anagram_groups[subject];
        if (std::find(wordlist.begin(), wordlist.end(), word) != wordlist.end()) {
            continue;
        }

        anagram_groups[subject].push_back(word);  // Lägg till ordet i rätt anagram-grupp
    }

    // Skriv ut anagram-grupper som har två eller fler ord
    for (const auto& pair : anagram_groups) {
        if (pair.second.size() > 1) {  // Om gruppen har två eller fler ord
            output_file << "Anagram group: ";

            // Sortera anagrammen alfabetiskt innan de skrivs ut
            std::vector<std::string> sorted_anagrams = pair.second;
            std::sort(sorted_anagrams.begin(), sorted_anagrams.end());

            for (const auto& anagram : sorted_anagrams) {

                output_file << anagram << " ";
            }
            output_file << " ---> (" << pair.second.size() << " words" << ")\n";
        }
    }


    std::cout << "Anagram groups have been written to choosen file\n";

    return 0;



}
