/****************************
 * Lab 3: exercise 2        *
 ****************************/

 // I denna uppgift så ska programmet kunna läsa en fil med punkter (x,y) 
 // och sedan kunna räkna ut den totala distansen som m vi rest i den ordningen som punkterna ges. 
 // Alltså så ska den beräkna ut resultanten. Den totala resultanten kommer att bli längden av pythagoras sats 
 // som fås ut mellan varje punkt.

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <numeric>
#include <iterator>
#include <algorithm>
#include <sstream>



struct Point {
	int x, y;
};

std::istream& operator>>(std::istream& is, Point& p) {
	std::string line;
	if (std::getline(is, line)) {
		std::stringstream ss(line);
		char comma;
		ss >> p.x >> comma >> p.y;
	}
	return is;
}


int main() {

	// Läs in punkterna från en fil

	std::ifstream file("C:\\Users\\rebec\\C++ kod\\tng033-labs\\lab3\\lab3\\code\\points.txt");
	if (!file.is_open()) {
		std::cerr << "Error opening file!" << std::endl;
		return 1;
	}

	// Läs in punkterna från filen med istream_iterator
	std::vector<Point> points((std::istream_iterator<Point>(file)), std::istream_iterator<Point>());

	// Skriv ut punkterna med std::transform och std::ostream_iterator
	std::cout << "Points:\n";
	std::transform(points.begin(), points.end(), std::ostream_iterator<std::string>(std::cout, "\n"),
		[](const Point& p) {
			return "(" + std::to_string(p.x) + ", " + std::to_string(p.y) + ")";
		});
	
	// Beräkna avstånd mellan på varandra följande punkter
	std::vector<double> distances(points.size() - 1);
	std::transform(points.begin(), points.end() - 1, points.begin() + 1, distances.begin(),
		[](const Point& a, const Point& b) {
			int dx = b.x - a.x;
			int dy = b.y - a.y;
			return std::sqrt(dx * dx + dy * dy);
		});


	// Steg 3: Summera avstånden för att få det totala avståndet
	double total_distance = std::accumulate(distances.begin(), distances.end(), 0.0);

	// Skriv ut det totala avståndet
	std::cout << "\n Distance travelled = " << total_distance << "\n";

	return 0;

}