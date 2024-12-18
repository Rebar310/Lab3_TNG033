/****************************
 * Lab 3: exercise 2        *
 ****************************/

 // I denna uppgift så ska programmet kunna läsa en fil med punkter (x,y) 
 // och sedan kunna räkna ut den totala distansen som m vi rest i den ordningen som punkterna ges. 
 // Alltså så ska den beräkna ut resultanten. Den totala resultanten kommer att bli längden av pythagoras sats 
 // som fås ut mellan varje punkt.

#include <iostream>       // For input and output
#include <fstream>        // For reading from files
#include <vector>         // To store a collection of points
#include <cmath>          // For mathematical operations like sqrt
#include <numeric>        // For accumulate function
#include <iterator>       // For istream_iterator and ostream_iterator
#include <algorithm>      // For transform function
#include <sstream>        // For stringstream to parse points

// ************************   Disclaimer   ****************************************
// For this excercise there were hints of using std::adjacent_difference and std::pair to represent the points
// This did not work so instead the point is now a struct and we use std::tranform insted of adjacent


// Define a struct to represent a point in 2D space
struct Point {
	int x, y;
};

// Overload the >> operator to read a Point from a stream
// Input format: x,y (e.g., "3,4")
// Reads a line from the stream, splits it into x and y values, and stores them in a Point
std::istream& operator>>(std::istream& is, Point& p) {
	std::string line;
	if (std::getline(is, line)) {      // Read a line from the input stream
		std::stringstream ss(line);    // Create a stringstream for parsing the line
		char comma;                    // Variable to hold the comma separating x and y
		ss >> p.x >> comma >> p.y;     // Extract x, ',' and y
	}
	return is;  // Return the input stream for chaining
}


int main() {

	// Open the file containing points
	std::ifstream file("C:\\Users\\rebec\\C++ kod\\tng033-labs\\lab3\\lab3\\code\\points.txt");
	if (!file.is_open()) {
		std::cerr << "Error opening file!" << std::endl;
		return 1;
	}

	// Read points from the file into a vector using istream_iterator
	// The vector is initialized with all the points read from the file
	std::vector<Point> points((std::istream_iterator<Point>(file)), std::istream_iterator<Point>());

	//Print the points using std::transform and std::ostream_iterator
	std::cout << "Points:\n";
	std::transform(points.begin(), points.end(), std::ostream_iterator<std::string>(std::cout, "\n"),
		[](const Point& p) {
			// Lambda function to format each point as a string
			return "(" + std::to_string(p.x) + ", " + std::to_string(p.y) + ")";
		});
	
	// Calculate the distances between consecutive points
	std::vector<double> distances(points.size() - 1);  // Vector to store distances
	std::transform(points.begin(), points.end() - 1, points.begin() + 1, distances.begin(),
		[](const Point& a, const Point& b) {
			// Lambda function to calculate the Euclidean distance between two points
			int dx = b.x - a.x; // Difference in x-coordinates
			int dy = b.y - a.y; // Difference in y-coordinates
			return std::sqrt(dx * dx + dy * dy); // Euclidean distance formula
		});

	// Calculate the total distance traveled by summing the distances
	// std::accumulate adds all elements in the distances vector, starting with 0.0
	double total_distance = std::accumulate(distances.begin(), distances.end(), 0.0);

	// Print the total distance traveled
	std::cout << "\n Distance travelled = " << total_distance << "\n";

	return 0; // Return 0 to indicate successful execution

}