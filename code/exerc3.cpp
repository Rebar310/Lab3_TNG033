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

// Funktion för att sortera bokstäverna i ett ord
std::string get_subject(const std::string& word) {
    std::string subject = word;
    std::sort(subject.begin(), subject.end());  // Sortera bokstäverna
    return subject;
}

int main() {

    // Växla mellan att skriva in filerna uppgift3.txt och uppgift3_kort.txt
    std::ifstream input_file("uppgift3_kort.txt");  // Läs in från filen

    //Växla mellan att skriva in filerna out_uppgift3_kort.txt och out_uppgift3.txt
    std::ofstream output_file("out_uppgift3_kort.txt");  // Skriv till filen

    std::map<std::string, std::vector<std::string>> anagram_groups;  // Map för att lagra anagram-grupper

    std::string word;

    // Läs ord från filen
    while (input_file >> word) {
        std::string subject = get_subject(word);  // Hämta subject för ordet
        anagram_groups[subject].push_back(word);  // Lägg till ordet i rätt anagram-grupp
    }

    // Skriv ut anagram-grupper som har två eller fler ord
    for (const auto& pair : anagram_groups) {
        if (pair.second.size() > 1) {  // Om gruppen har två eller fler ord
            output_file << "Anagram group: ";
            for (const auto& anagram : pair.second) {
                output_file << anagram << " ";
            }
            output_file << "(Count: " << pair.second.size() << ")\n";
        }
    }


    std::cout << "Anagram groups have been written to out_uppgift3.txt\n";

    return 0;



}
