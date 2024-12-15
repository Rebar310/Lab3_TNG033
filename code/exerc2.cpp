/****************************
 * Lab 3: exercise 2        *
 ****************************/

 // I denna uppgift så ska programmet kunna läsa en fil med punkter (x,y) 
 // och sedan kunna räkna ut den totala distansen som m vi rest i den ordningen som punkterna ges. 
 // Alltså så ska den beräkna ut resultanten. Den totala resultanten kommer att bli längden av pythagoras sats 
 // som fås ut mellan varje punkt.

#include <iostream>
#include <fstream> // för att kunna läsa från filer
#include <vector>
#include <cmath>
#include <numeric>
#include <iterator>
#include <algorithm>
#include <string>
#include <sstream>

#include <filesystem>



// Beräknar avståndet mellan två punkter (x1, y1) och (x2, y2)
double calculate_distance(const std::pair<int, int>& point1, const std::pair<int, int>& point2) {
	int dx = point2.first - point1.first;
	int dy = point2.second - point1.second;
	return std::sqrt(dx * dx + dy * dy);  // Pythagoras sats
}


int main() {

	// Läs in punkterna från en fil

	std::ifstream file("C:\\Users\\rebec\\C++ kod\\tng033-labs\\lab3\\lab3\\code\\points.txt");
	if (!file.is_open()) {
		std::cerr << "Error opening file!" << std::endl;
		return 1;
	}

	std::vector<std::pair<int, int>> points;  // Vektor för att lagra punkterna (x, y)
	std::string line;

	while (file >> line) {
		// Extrahera x och y-koordinater från varje rad
		std::stringstream ss(line);
		int x, y;
		char comma; // För att hantera kommatecknet mellan x och y
		ss >> x >> comma >> y;
		points.push_back({ x, y });
	}

	// Visa alla lästa punkter
	std::cout << "Points: \n";
	// Måste kolla om jag får använda auto
	for (const auto& point : points) {
		std::cout << "(" << point.first << ", " << point.second << ")\n";
	}

	// Beräkna avståndet mellan varje par av på varandra följande punkter
	std::vector<double> distances;

	//Använd adjacent_difference för att beräkna avstånd mellan på varandra följande punkter
	//std::adjacent_difference(points.begin(), points.end(), std::back_inserter(distances),
	//	[](const std::pair<int, int>& a, const std::pair<int, int>& b) {
	//		return calculate_distance(a, b);  // Använda calculate_distance för att beräkna avstånd
	//	});


	// Beräkna avståndet mellan på varandra följande punkter manuellt    (lösning utan adjacent_difference)
	for (size_t i = 1; i < points.size(); ++i) {
		double dist = calculate_distance(points[i - 1], points[i]);
		distances.push_back(dist);
	}


	// Steg 3: Summera avstånden för att få det totala avståndet
	double total_distance = std::accumulate(distances.begin(), distances.end(), 0.0);

	// Skriv ut det totala avståndet
	std::cout << "Total distance: " << total_distance << "\n";

	return 0;

}