/****************************
 * Lab 3: exercise 2        *
 ****************************/

 // I denna uppgift s� ska programmet kunna l�sa en fil med punkter (x,y) 
 // och sedan kunna r�kna ut den totala distansen som m vi rest i den ordningen som punkterna ges. 
 // Allts� s� ska den ber�kna ut resultanten. Den totala resultanten kommer att bli l�ngden av pythagoras sats 
 // som f�s ut mellan varje punkt.

#include <iostream>
#include <fstream> // f�r att kunna l�sa fr�n filer
#include <vector>
#include <cmath>
#include <numeric>
#include <iterator>
#include <algorithm>
#include <string>
#include <sstream>

#include <filesystem>



// Ber�knar avst�ndet mellan tv� punkter (x1, y1) och (x2, y2)
double calculate_distance(const std::pair<int, int>& point1, const std::pair<int, int>& point2) {
	int dx = point2.first - point1.first;
	int dy = point2.second - point1.second;
	return std::sqrt(dx * dx + dy * dy);  // Pythagoras sats
}


int main() {

	// L�s in punkterna fr�n en fil

	std::ifstream file("C:\\Users\\rebec\\C++ kod\\tng033-labs\\lab3\\lab3\\code\\points.txt");
	if (!file.is_open()) {
		std::cerr << "Error opening file!" << std::endl;
		return 1;
	}

	std::vector<std::pair<int, int>> points;  // Vektor f�r att lagra punkterna (x, y)
	std::string line;

	while (file >> line) {
		// Extrahera x och y-koordinater fr�n varje rad
		std::stringstream ss(line);
		int x, y;
		char comma; // F�r att hantera kommatecknet mellan x och y
		ss >> x >> comma >> y;
		points.push_back({ x, y });
	}

	// Visa alla l�sta punkter
	std::cout << "Points: \n";
	// M�ste kolla om jag f�r anv�nda auto
	for (const auto& point : points) {
		std::cout << "(" << point.first << ", " << point.second << ")\n";
	}

	// Ber�kna avst�ndet mellan varje par av p� varandra f�ljande punkter
	std::vector<double> distances;

	//Anv�nd adjacent_difference f�r att ber�kna avst�nd mellan p� varandra f�ljande punkter
	//std::adjacent_difference(points.begin(), points.end(), std::back_inserter(distances),
	//	[](const std::pair<int, int>& a, const std::pair<int, int>& b) {
	//		return calculate_distance(a, b);  // Anv�nda calculate_distance f�r att ber�kna avst�nd
	//	});


	// Ber�kna avst�ndet mellan p� varandra f�ljande punkter manuellt    (l�sning utan adjacent_difference)
	for (size_t i = 1; i < points.size(); ++i) {
		double dist = calculate_distance(points[i - 1], points[i]);
		distances.push_back(dist);
	}


	// Steg 3: Summera avst�nden f�r att f� det totala avst�ndet
	double total_distance = std::accumulate(distances.begin(), distances.end(), 0.0);

	// Skriv ut det totala avst�ndet
	std::cout << "Total distance: " << total_distance << "\n";

	return 0;

}