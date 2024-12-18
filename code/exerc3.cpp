/**************************
 * Lab 3: exercise 3      *
 **************************/

// I denna exercise s� ska koden l�sa av en fil med "anagram" 
// (allts� bokst�ver som lagts huller om buller f�r att bilda riktiga ord)
// T.ex p� Anagram kan vara "listen" and "silent"
// Dessa tv� har subjektet "eilnst" gemensamt allts�
// deras gemensamma inneh�llande bokst�ver sorterade i alfabetisk ordning.
//
// L�sning: Nyckeln �r just att nyckeln i std::map<nyckeln,v�rde> kommer att vara subjectet


#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <string>
#include <set>



// Funktion f�r att sortera bokst�verna i ett ord alfabetiskt
std::string get_subject(const std::string& word) {
    std::string subject = word;
    std::sort(subject.begin(), subject.end());  // Sortera bokst�verna
    return subject;
}

int main() {
    
    // Fils�kv�gar input
    // "C:\\Users\\rebec\\C++ kod\\tng033-labs\\lab3\\lab3\\code\\uppgift3_kort.txt"
    // "C:\\Users\\rebec\\C++ kod\\tng033-labs\\lab3\\lab3\\code\\uppgift3.txt"

    //Fils�kv�gar output
    // Resultatet hamnar i build mappen f�r att inte skriva �ver "facit-filer"

    // ***********************************************************************''

    // V�xla mellan att skriva in filerna
    std::ifstream input_file("C:\\Users\\rebec\\C++ kod\\tng033-labs\\lab3\\lab3\\code\\uppgift3_kort.txt");  // L�s in fr�n filen
    if (!input_file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    //V�xla mellan att skriva in filerna 
    // out_uppgift3_kort.txt 
    // out_uppgift3.txt
    std::ofstream output_file("out_uppgift3_kort.txt");  // Skriv till filen
   

    std::map<std::string, std::vector<std::string>> anagram_groups;  // Map f�r att lagra anagram-grupper

    std::string word;

    // L�s ord fr�n filen
    while (input_file >> word) {
        std::string subject = get_subject(word);  // H�mta subject f�r ordet


        std::vector<std::string>& wordlist = anagram_groups[subject];
        if (std::find(wordlist.begin(), wordlist.end(), word) != wordlist.end()) {
            continue;
        }

        anagram_groups[subject].push_back(word);  // L�gg till ordet i r�tt anagram-grupp
    }

    // Skriv ut anagram-grupper som har tv� eller fler ord
    for (const auto& pair : anagram_groups) {
        if (pair.second.size() > 1) {  // Om gruppen har tv� eller fler ord
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
