#include <iostream>
#include <cmath> // For mathematical functions like sqrt, pow, cbrt
#include <string>
#include <limits> // Required for numeric_limits
#include <cctype> // Required for tolower
#include <algorithm> // Required for transform

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
using namespace std;
const double PI = M_PI;
const string CURRENT_VERSION = "1.0";

// Helper function to get double input with basic error handling
double getDoubleInput(const string& prompt) {
    string input_str;
    double value;
    while (true) {
        cout << prompt;
        getline(cin, input_str);
        try {
            // Attempt to convert the string to a double
            size_t processed_chars; // To check if entire string was consumed
            value = stod(input_str, &processed_chars);

            // Check if there were unexpected characters after the number
            if (processed_chars != input_str.length()) {
                 throw invalid_argument("Non-numeric characters present.");
            }

            return value; // Return the valid double value
        } catch (const invalid_argument& e) {
            cout << "Invalid input. Please enter a valid number." << endl;
        } catch (const out_of_range& e) {
            cout << "Input value out of range for a number." << endl;
        }
        cout << endl; // Add newline after error message as in original
    }
}
int getIntInput(const string& prompt) {
    string input_str;
    int value;
    while (true) {
        cout << prompt;
        getline(cin, input_str);
        try {
            // Attempt to convert the string to an integer
            size_t processed_chars;
            value = stoi(input_str, &processed_chars);

             // Check if there were unexpected characters after the number
            if (processed_chars != input_str.length()) {
                 throw invalid_argument("Non-integer characters present.");
            }

            return value; // Return the valid integer value
        } catch (const invalid_argument& e) {
            cout << "Invalid input. Please enter a whole number." << endl;
        } catch (const out_of_range& e) {
            cout << "Input value out of range for an integer." << endl;
        }
        cout << endl; // Add newline after error message as in original
    }
}
int main() {
    cout << "PyCalc-CE : A Simple and Lightweight Calculator. Now in C++!" << endl;
    cout << "Version : " << CURRENT_VERSION << "\n\n";

    // Removed the check_for_updates function call

    cout << "Select a Mathematical Operation : " << endl;
    cout << "1. Addition\n"
         << "2. Subtraction\n"
         << "3. Multiplication\n"
         << "4. Division\n"
         << "5. Exponents (x^y)\n"
         << "6. Square Root\n"
         << "7. Cube Root\n"
         << "8. Approximate / Rounding\n"
         << "9. Heron's Formula\n"
         << "10. Simple Interest\n"
         << "11. Compound Interest\n"
         << "12. Prime No. Check\n"
         << "13. Triangle Check\n"
         << "14. Right Triangle Check\n"
         << "15. Perimiter [Various Shapes]\n"
         << "16. Area [Varoius Shapes]\n"
         << "17. Volume [Various Shapes]\n"
         << "18. Surface Area [Various Shapes]\n"
         << "19. Curved Surface Area [Various Shapes]\n"
         << "20. Diagonal Calculation [Various Shapes]\n"
         << "21. Factorial Calculator\n"
         << "22. Exit PyCalc-CE\n";

    while (true) {
        string ch;
        cout << endl;
        cout << "Enter choice [ 1 - 22 ] : ";
        getline(cin, ch);
        cout << endl; 
        // Use if-else if-else for string comparison as C++ switch doesn't work on strings
        if (ch == "1") { // Addition
            double x = getDoubleInput("Enter first number : "); cout << endl;
            double y = getDoubleInput("Enter second number : "); cout << endl;
            cout << x << " + " << y << " = " << (x + y) << "\n\n";
        } else if (ch == "2") { // Subtraction
            double x = getDoubleInput("Enter first number : "); cout << endl;
            double y = getDoubleInput("Enter second number : "); cout << endl;
            cout << x << " - " << y << " = " << (x - y) << "\n\n";
        } else if (ch == "3") { // Multiplication
            double x = getDoubleInput("Enter first number : "); cout << endl;
            double y = getDoubleInput("Enter second number : "); cout << endl;
            cout << x << " * " << y << " = " << (x * y) << "\n\n";
        } else if (ch == "4") { // Division
             double x = getDoubleInput("Enter first number : "); cout << endl;
             double y = getDoubleInput("Enter second number : "); cout << endl;
             if (y == 0) {
                 cout << "Div. by Zero Not Defined!\n\n";
             } else {
                 cout << x << " / " << y << " = " << (x / y) << "\n\n";
             }
        } else if (ch == "5") { // Exponents
            double x = getDoubleInput("Enter base number (x) : "); cout << endl;
            double y = getDoubleInput("Enter exponent number (y) : "); cout << endl;
            cout << x << " ^ " << y << " = " << pow(x, y) << "\n\n";
        } else if (ch == "6") { // Square Root
            double x = getDoubleInput("Enter a number : "); cout << endl;
            if (x < 0) {
                // Standard sqrt returns NaN for negative, add a check for user clarity
                cout << "Square root of a negative number is not a real number.\n\n";
            } else {
                cout << "Root " << x << " = " << sqrt(x) << "\n\n";
            }
        } else if (ch == "7") { // Cube Root
            double x = getDoubleInput("Enter a number : "); cout << endl;
            cout << "C. Root " << x << " = " << cbrt(x) << "\n\n";
        } else if (ch == "8") { // Rounding
            double x = getDoubleInput("Enter a number : "); cout << endl;
            cout << round(x) << "\n\n"; // std::round rounds to nearest integer
        } else if (ch == "9") { // Heron's Formula
            cout << "NOTE: Some Calculations may print NaN or result in errors depending on the values!\n";
            double a = getDoubleInput("Enter the first side [a] : "); cout << endl;
            double b = getDoubleInput("Enter the second side [b] : "); cout << endl;
            double c = getDoubleInput("Enter third side [c] : "); cout << endl;
            if (a <= 0 || b <= 0 || c <= 0) { // Check for positive sides
                cout << "Sides must be positive.\n\n";
            } else if ((a + b <= c) || (a + c <= b) || (b + c <= a)) { // Check triangle inequality
                 cout << "These side lengths do not form a valid triangle.\n\n";
            }
            else {
                double s = (a + b + c);
                cout << "Perimeter : " << s << endl;
                s /= 2;
                cout << "s = " << s << endl;
                // Calculate the term inside the square root
                double radicand = s * (s - a) * (s - b) * (s - c);

                // Due to floating point inaccuracies, radicand might be slightly negative for a valid triangle
                if (radicand < 0 && radicand > -1e-9) { // Check if it's very close to zero
                     radicand = 0; // Treat it as zero
                }

                if (radicand < 0) { // Still negative means invalid input that passed basic checks
                     cout << "Area : Calculation Error (invalid triangle or floating point issue)\n\n";
                } else {
                     double ar = sqrt(radicand);
                     cout << "Area : " << ar << "\n\n";
                }
            }
        } else if (ch == "10") { // Simple Interest
             double p = getDoubleInput("Enter the Principal : "); cout << endl;
             double r = getDoubleInput("Enter the Rate [ % ] : "); cout << endl;
             double t = getDoubleInput("Enter the Time [ Years ] : "); cout << endl;
             if (p < 0 || r < 0 || t < 0) {
                 cout << "Principal, Rate, and Time must be non-negative.\n\n";
             } else {
                double si = p * r * t / 100.0;
                cout << "Simple Interest : " << si << "\n";
                cout << "Amount : " << (si + p) << "\n\n";
             }
        } else if (ch == "11") { // Compound Interest
             cout << "Compound Interest Calculation\n\n";
             double p = getDoubleInput("Enter the Principal : "); cout << endl;
             double r = getDoubleInput("Enter the Rate [ % ] : "); cout << endl;
             double n = getDoubleInput("Enter the number of times interest is compounded per year : "); cout << endl;
             double t = getDoubleInput("Enter the Time [ Years ] : "); cout << endl;

             if (p < 0 || r < 0 || n <= 0 || t < 0) {
                  cout << "Principal, Rate, and Time must be non-negative. Compounding frequency (n) must be positive.\n\n";
             } else {
                 // Calculate amount A = P(1 + R/(100*n))^(n*t)
                 double rate_per_period = r / (100.0 * n);
                 double num_periods = n * t;
                 double amount = p * pow(1.0 + rate_per_period, num_periods);
                 double ci = amount - p;
                 cout << "Compound Interest : " << ci << "\n";
                 cout << "Amount : " << amount << "\n\n";
             }
        } else if (ch == "12") { // Prime Number Check
             int x = getIntInput("Enter a Number : "); cout << endl;
             bool is_prime = true;
             if (x <= 1) {
                 is_prime = false; // Numbers <= 1 are not prime
             } else {
                 // Check for factors from 2 up to the square root of x
                 // This is an optimization; original code checked up to x-1
                 for (int i = 2; i * i <= x; ++i) {
                     if ((x % i) == 0) {
                         is_prime = false;
                         break; // Found a factor, not prime
                     }
                 }
             }
             if (is_prime) {
                 cout << x << " is a Prime Number\n\n";
             } else {
                 cout << x << " is not a Prime Number\n\n";
             }
        } else if (ch == "13") { // Triangle Check
             double a = getDoubleInput("Enter first side [a] : "); cout << endl;
             double b = getDoubleInput("Enter second side [b] : "); cout << endl;
             double c = getDoubleInput("Enter third side [c] : "); cout << endl;
             if (a <= 0 || b <= 0 || c <= 0) { // Check for positive sides
                 cout << "Sides must be positive\n\n";
             } else if ((a + b > c) && (a + c > b) && (b + c > a)) { // Triangle inequality theorem
                 cout << "Valid Triangle\n\n";
             } else {
                 cout << "Not a Valid Triangle\n\n";
             }
        } else if (ch == "14") { // Right Triangle Check
             double a = getDoubleInput("Enter first side [a] : "); cout << endl;
             double b = getDoubleInput("Enter second side [b] : "); cout << endl;
             double c = getDoubleInput("Enter third side [c] : "); cout << endl;
             if (a <= 0 || b <= 0 || c <= 0) { // Check for positive sides
                 cout << "Sides must be positive\n\n";
             } else {
                 // Using a small tolerance for floating point comparisons with pow()
                 double tol = 1e-9; // Tolerance
                 bool is_right = false;
                 // Check Pythagorean theorem a^2 + b^2 = c^2 (and permutations)
                 if (abs(pow(a, 2) + pow(b, 2) - pow(c, 2)) < tol) is_right = true;
                 if (abs(pow(a, 2) + pow(c, 2) - pow(b, 2)) < tol) is_right = true;
                 if (abs(pow(b, 2) + pow(c, 2) - pow(a, 2)) < tol) is_right = true;

                 if (is_right) {
                     cout << "Is a Right Triangle\n\n";
                 } else {
                     cout << "Not a Right Triangle.\n\n";
                 }
             }
        } else if (ch == "15") { // Perimeter [Various Shapes]
             cout << "Perimeter Calculation [Various Shapes]\n\n";
             cout << "Select a shape : \n"
                   << "1. Equilateral Triangle\n"
                   << "2. Isosceles Triangle\n"
                   << "3. Square / Rhombus\n"
                   << "4. Rectangle / Parallelogram\n"
                   << "5. Circle\n";
             string sch;
             cout << "Enter shape choice [ 1 - 5 ]: ";
             getline(cin, sch);
             cout << endl; // Python print() after input

             if (sch == "1") { // Equilateral Triangle
                 double a = getDoubleInput("Enter Side Length [a] : "); cout << endl;
                 if (a < 0) { cout << "Side length cannot be negative.\n\n"; } else { cout << "Perimeter : " << 3 * a << "\n\n"; }
             } else if (sch == "2") { // Isosceles Triangle
                 double a = getDoubleInput("Enter Equal Side's Length : "); cout << endl;
                 double b = getDoubleInput("Enter Non-Equal Side's Length : "); cout << endl;
                  if (a < 0 || b < 0) { cout << "Side lengths cannot be negative.\n\n"; } else { cout << "Perimeter : " << 2 * a + b << "\n\n"; }
             } else if (sch == "3") { // Square / Rhombus
                 double a = getDoubleInput("Enter Length of Side [a] : "); cout << endl;
                 if (a < 0) { cout << "Side length cannot be negative.\n\n"; } else { cout << "Perimeter : " << 4 * a << "\n\n"; }
             } else if (sch == "4") { // Rectangle / Parallelogram
                 double l = getDoubleInput("Enter Length [l] : "); cout << endl;
                 double b = getDoubleInput("Enter Breadth [b] : "); cout << endl;
                  if (l < 0 || b < 0) { cout << "Length and Breadth cannot be negative.\n\n"; } else { cout << "Perimeter : " << 2 * (l + b) << "\n\n"; }
             } else if (sch == "5") { // circle
                 double r = getDoubleInput("Enter the Radius [r] : "); cout << endl;
                  if (r < 0) { cout << "Radius cannot be negative.\n\n"; } else { double c = 2 * PI * r; cout << "Circumference : " << c << "\n\n"; }
             } else {
                 cout << "Invalid Option! Exiting Perimeter Calculation ...\n\n";
             }
        } else if (ch == "16") { // Area [Various Shapes]
             cout << "Area Calculation [Various Shapes]\n\n";
             cout << "Select a shape : \n"
                   << "1. Equilateral Triangle\n"
                   << "2. Isosceles Triangle\n"
                   << "3. Square\n"
                   << "4. Rectangle / Parallelogram\n"
                   << "5. Rhombus\n"
                   << "6. Circle\n"
                   << "7. Semi-circle\n";
             string sch;
             cout << "Enter shape choice [ 1 - 7 ] : ";
             getline(cin, sch);
             cout << endl; // Python print() after input

             if (sch == "1") { // Equilateral Triangle
                 double a = getDoubleInput("Enter Side Length [a] : "); cout << endl;
                 if (a < 0) { cout << "Side length cannot be negative.\n\n"; } else { double ar = (sqrt(3) / 4.0) * pow(a, 2); cout << "Area : " << ar << "\n\n"; }
             } else if (sch == "2") { // Isosceles Triangle
                 double a = getDoubleInput("Enter Equal Side's Length : "); cout << endl;
                 double b = getDoubleInput("Enter Non-Equal Side's Length : "); cout << endl;
                 if (a < 0 || b < 0) { cout << "Side lengths cannot be negative.\n\n"; }
                 // Add a check for valid isosceles triangle side lengths
                 else if (2 * a <= b) { cout << "Invalid side lengths for an isosceles triangle (2a <= b).\n\n"; }
                 else {
                     // Area = (b/4) * sqrt(4a^2 - b^2)
                     double radicand = 4 * pow(a, 2) - pow(b, 2);
                     if (radicand < 0 && radicand > -1e-9) { // Handle potential small negative due to float
                          radicand = 0;
                     }
                     if (radicand < 0) { // Still negative means invalid input
                          cout << "Area : Calculation Error (invalid triangle or floating point issue)\n\n";
                     } else {
                          double ar = (b / 4.0) * sqrt(radicand);
                          cout << "Area : " << ar << "\n\n";
                     }
                 }
             } else if (sch == "3") { // Square
                 double a = getDoubleInput("Enter Length of Side [a] : "); cout << endl;
                 if (a < 0) { cout << "Side length cannot be negative.\n\n"; } else { double ar = pow(a, 2); cout << "Area : " << ar << "\n\n"; }
             } else if (sch == "4") { // Rectangle / Parallelogram
                 double l = getDoubleInput("Enter Length [l] : "); cout << endl;
                 double b = getDoubleInput("Enter Breadth [b] : "); cout << endl;
                  if (l < 0 || b < 0) { cout << "Length and Breadth cannot be negative.\n\n"; } else { double ar = l * b; cout << "Area : " << ar << "\n\n"; }
             } else if (sch == "5") { // Rhombus
                 double d1 = getDoubleInput("Enter Diagonal 1 [d1] : "); cout << endl;
                 double d2 = getDoubleInput("Enter Diagonal 2 [d2] : "); cout << endl;
                 if (d1 < 0 || d2 < 0) { cout << "Diagonals cannot be negative.\n\n"; } else { double area = 0.5 * d1 * d2; cout << "Area of Rhombus : " << area << "\n\n"; }
             } else if (sch == "6") { // circle
                 double r = getDoubleInput("Enter the Radius [r] : "); cout << endl;
                 if (r < 0) { cout << "Radius cannot be negative.\n\n"; } else { double area = PI * pow(r, 2); cout << "Area : " << area << "\n\n"; }
             } else if (sch == "7") { // Semi-circle
                 double r = getDoubleInput("Enter the Radius [r] : "); cout << endl;
                  if (r < 0) { cout << "Radius cannot be negative.\n\n"; } else { double area = 0.5 * PI * pow(r, 2); cout << "Area : " << area << "\n\n"; }
             }
             else {
                 cout << "Invalid Option! Exiting Area Calculation ...\n\n";
             }
        } else if (ch == "17") { // Volume [Various Shapes]
             cout << "Volume Calculation [Various Shapes]\n\n";
             cout << "Select a shape : \n"
                   << "1. Cube\n"
                   << "2. Cuboid\n"
                   << "3. Cylinder\n"
                   << "4. Cone\n"
                   << "5. Sphere\n";
             string sch;
             cout << "Enter shape choice [ 1 - 5 ] : ";
             getline(cin, sch);
             cout << endl; // Python print() after input

             if (sch == "1") { // Cube
                 double a = getDoubleInput("Enter Length of Side [a] : "); cout << endl;
                 if (a < 0) { cout << "Side length cannot be negative.\n\n"; } else { double vol = pow(a, 3); cout << "Volume : " << vol << "\n\n"; }
             } else if (sch == "2") { // Cuboid
                 double l = getDoubleInput("Enter Length [l] : "); cout << endl;
                 double b = getDoubleInput("Enter Breadth [b] : "); cout << endl;
                 double h = getDoubleInput("Enter Height [h] : "); cout << endl;
                  if (l < 0 || b < 0 || h < 0) { cout << "Length, Breadth, and Height cannot be negative.\n\n"; } else { double vol = l * b * h; cout << "Volume : " << vol << "\n\n"; }
             } else if (sch == "3") { // Cylinder
                 double r = getDoubleInput("Enter the Radius [r] : "); cout << endl;
                 double h = getDoubleInput("Enter the Height [h] : "); cout << endl;
                  if (r < 0 || h < 0) { cout << "Radius and Height cannot be negative.\n\n"; } else { double vol = PI * pow(r, 2) * h; cout << "Volume : " << vol << "\n\n"; }
             } else if (sch == "4") { // Cone
                 double r = getDoubleInput("Enter the Radius [r] : "); cout << endl;
                 double h = getDoubleInput("Enter the Height [h] : "); cout << endl;
                  if (r < 0 || h < 0) { cout << "Radius and Height cannot be negative.\n\n"; } else { double vol = (1.0/3.0) * PI * pow(r, 2) * h; cout << "Volume : " << vol << "\n\n"; }
             } else if (sch == "5") { // Sphere
                 double r = getDoubleInput("Enter the Radius [r] : "); cout << endl;
                  if (r < 0) { cout << "Radius cannot be negative.\n\n"; } else { double vol = (4.0/3.0) * PI * pow(r, 3); cout << "Volume : " << vol << "\n\n"; }
             }
             else {
                 cout << "Invalid Option! Exiting Volume Calculation ...\n\n";
             }
        } else if (ch == "18") { // Surface Area [Various Shapes]
             cout << "Surface Area Calculation [Various Shapes]\n\n";
             cout << "Select a shape : \n"
                   << "1. Cube\n"
                   << "2. Cuboid\n"
                   << "3. Cylinder\n"
                   << "4. Cone\n"
                   << "5. Sphere\n";
             string sch;
             cout << "Enter shape choice [ 1 - 5 ] : ";
             getline(cin, sch);
             cout << endl; // Python print() after input

             if (sch == "1") { // Cube
                 double a = getDoubleInput("Enter Length of Side [a] : "); cout << endl;
                  if (a < 0) { cout << "Side length cannot be negative.\n\n"; } else { double sa = 6 * pow(a, 2); cout << "Surface Area : " << sa << "\n\n"; }
             } else if (sch == "2") { // Cuboid
                 double l = getDoubleInput("Enter Length [l] : "); cout << endl;
                 double b = getDoubleInput("Enter Breadth [b] : "); cout << endl;
                 double h = getDoubleInput("Enter Height [h] : "); cout << endl;
                  if (l < 0 || b < 0 || h < 0) { cout << "Length, Breadth, and Height cannot be negative.\n\n"; } else { double sa = 2 * (l * b + b * h + h * l); cout << "Surface Area : " << sa << "\n\n"; }
             } else if (sch == "3") { // Cylinder
                 double r = getDoubleInput("Enter the Radius [r] : "); cout << endl;
                 double h = getDoubleInput("Enter the Height [h] : "); cout << endl;
                  if (r < 0 || h < 0) { cout << "Radius and Height cannot be negative.\n\n"; } else { double sa = 2 * PI * r * (r + h); cout << "Surface Area : " << sa << "\n\n"; }
             } else if (sch == "4") { // Cone
                 double r = getDoubleInput("Enter the Radius [r] : "); cout << endl;
                 double h = getDoubleInput("Enter the Height [h] : "); cout << endl;
                  if (r < 0 || h < 0) { cout << "Radius and Height cannot be negative.\n\n"; } else { double sa = PI * r * (r + sqrt(pow(h, 2) + pow(r, 2))); cout << "Surface Area : " << sa << "\n\n"; }
             } else if (sch == "5") { // Sphere
                 double r = getDoubleInput("Enter the Radius [r] : "); cout << endl;
                  if (r < 0) { cout << "Radius cannot be negative.\n\n"; } else { double sa = 4 * PI * pow(r, 2); cout << "Surface Area : " << sa << "\n\n"; }
             }
             else {
                 cout << "Invalid Option! Exiting Surface Area Calculation ...\n\n";
             }
        } else if (ch == "19") { // Curved Surface Area [Various Shapes]
             cout << "Curved Surface Area Calculation [Various Shapes]\n\n";
             cout << "Select a shape : \n"
                   << "1. Cylinder\n"
                   << "2. Cone\n"
                   << "3. Sphere\n";
             string sch;
             cout << "Enter shape choice [ 1 - 3 ] : ";
             getline(cin, sch);
             cout << endl; // Python print() after input

             if (sch == "1") { // Cylinder
                 double r = getDoubleInput("Enter the Radius [r] : "); cout << endl;
                 double h = getDoubleInput("Enter the Height [h] : "); cout << endl;
                 if (r < 0 || h < 0) { cout << "Radius and Height cannot be negative.\n\n"; } else { double csa = 2 * PI * r * h; cout << "Curved Surface Area : " << csa << "\n\n"; }
             } else if (sch == "2") { // Cone
                 double r = getDoubleInput("Enter the Radius [r] : "); cout << endl;
                 double h = getDoubleInput("Enter the Height [h] : "); cout << endl;
                  if (r < 0 || h < 0) { cout << "Radius and Height cannot be negative.\n\n"; } else { double csa = PI * r * sqrt(pow(h, 2) + pow(r, 2)); cout << "Curved Surface Area : " << csa << "\n\n"; }
             } else if (sch == "3") { // Sphere
                 double r = getDoubleInput("Enter the Radius [r] : "); cout << endl;
                 if (r < 0) { cout << "Radius cannot be negative.\n\n"; } else { double csa = 4 * PI * pow(r, 2); // Note: CSA of Sphere is the same as SA
                 cout << "Curved Surface Area : " << csa << "\n\n"; }
             }
             else {
                 cout << "Invalid Option! Exiting Curved Surface Area Calculation ...\n\n";
             }
        } else if (ch == "20") { // Diagonal Calculation [Various Shapes]
             cout << "Diagonal Calculation [Various Shapes]\n\n";
             cout << "Select a shape : \n"
                   << "1. Square\n"
                   << "2. Rectangle\n"
                   << "3. Cube\n"
                   << "4. Cuboid\n";
             string sch;
             cout << "Enter shape choice [ 1 - 4 ] : "; // Corrected choice range from Python
             getline(cin, sch);
             cout << endl; // Python print() after input

             if (sch == "1") { // Square
                 double a = getDoubleInput("Enter Length of Side [a] : "); cout << endl;
                 if (a < 0) { cout << "Side length cannot be negative.\n\n"; } else { double d = sqrt(2.0) * a; cout << "Diagonal : " << d << "\n\n"; }
             } else if (sch == "2") { // Rectangle
                 double l = getDoubleInput("Enter Length [l] : "); cout << endl;
                 double b = getDoubleInput("Enter Breadth [b] : "); cout << endl;
                  if (l < 0 || b < 0) { cout << "Length and Breadth cannot be negative.\n\n"; } else { double d = sqrt(pow(l, 2) + pow(b, 2)); cout << "Diagonal : " << d << "\n\n"; }
             } else if (sch == "3") { // Cube
                 double a = getDoubleInput("Enter Length of Side [a] : "); cout << endl;
                  if (a < 0) { cout << "Side length cannot be negative.\n\n"; } else { double d = sqrt(3.0) * a; cout << "Diagonal : " << d << "\n\n"; }
             } else if (sch == "4") { // Cuboid
                 double l = getDoubleInput("Enter Length [l] : "); cout << endl;
                 double b = getDoubleInput("Enter Breadth [b] : "); cout << endl;
                 double h = getDoubleInput("Enter Height [h] : "); cout << endl;
                  if (l < 0 || b < 0 || h < 0) { cout << "Length, Breadth, and Height cannot be negative.\n\n"; } else { double d = sqrt(pow(l, 2) + pow(b, 2) + pow(h, 2)); cout << "Diagonal : " << d << "\n\n"; }
             }
             else {
                 cout << "Invalid Option! Exiting Diagonal Calculation ...\n\n";
             }
        } else if (ch == "21") { // Factorial Calculation
             int x = getIntInput("Enter a Number : "); cout << endl;
             if (x < 0) {
                 cout << "Factorial Not Defined for Negative Numbers!\n\n";
             } else if (x == 0 || x == 1) {
                 cout << "Factorial of " << x << " is 1\n\n";
             } else {
                 // Use unsigned long long for potentially large factorials
                 unsigned long long fact = 1;
                 for (int i = 2; i <= x; ++i) {
                     // Add a check for overflow if needed for very large numbers
                     // This simple conversion doesn't include full overflow handling
                     fact *= i;
                 }
                 cout << "Factorial of " << x << " is " << fact << "\n\n";
             }
        } else if (ch == "22") { // Exit Program
             cout << "Exiting PyCalc-CE...\n";
             exit(0);
        } else { // Default Case (Invalid Choice)
             cout << "Please enter a Valid Input! Retry Again....\n\n";
             continue;
        }

        // Next_Calc Loop - Only ask if the user didn't choose to exit (choice 22)
        if (ch != "22") {
             string next_calc;
             cout << "Do you Want to Perform Another Calculation? [y/n]: ";
             getline(cin, next_calc);
             cout << endl; // Python print() after input

             // Convert input to lowercase for case-insensitive comparison
             transform(next_calc.begin(), next_calc.end(), next_calc.begin(),
                            ::tolower);

             if (next_calc == "n" || next_calc == "no") {
                 cout << "Exiting PyCalc-CE...\n";
                 break; // Exit the main while(true) loop
             } else if (next_calc != "y" && next_calc != "yes") {
                 // If input is neither 'y', 'yes', 'n', nor 'no', print a message and continue
                 cout << "Invalid input. Continuing...\n\n";
             }
             // If input was 'y' or 'yes', the loop continues naturally
        }
    }    
    return 0;
}