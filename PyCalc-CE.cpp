#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <limits> // Required for std::numeric_limits
#include <stdexcept> // Required for std::stof/stoi exceptions
#include <curl/curl.h> // Required for libcurl
#include <algorithm>
#include <numbers> // Required for std::numbers::pi_v

// --- Constants ---
const std::string UPDATE_VERSION_URL = "https://gist.githubusercontent.com/Chill-Astro/3188d1da41a7d9de6225d01febafe32e/raw/1074e2f9489ea7d3603b14c59a7ea1fe1bc7afa1/PyCCPP_V.txt";
const std::string CURRENT_VERSION = "1.1"; // Linux Release + Installer & Winget Support
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// --- libcurl Write Callback Function ---
// This function gets called by libcurl as data arrives
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// --- Function to check for updates using libcurl ---
void check_for_updates() {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    // Global libcurl initialization (should ideally be done once)
    // For this simple script, doing it here is okay, but be mindful
    // in larger applications.
    curl_global_init(CURL_GLOBAL_DEFAULT);

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, UPDATE_VERSION_URL.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L); // Timeout after 5 seconds

        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            std::cerr << "--- UPDATE CHECK FAILED! ---\n"
                      << "⚠️ Could not check for updates. Please check your internet connection.\n"
                      << "Error: " << curl_easy_strerror(res) << "\n"
                      << "------------------------\n";
        } else {
            long http_code = 0;
            curl_easy_getinfo(curl, CURLINFO_HTTP_CODE, &http_code);

            if (http_code == 200) {
                // Trim whitespace from the fetched version
                size_t first = readBuffer.find_first_not_of(" \t\n\r");
                if (std::string::npos == first) {
                    readBuffer.clear(); // Buffer contains only whitespace
                } else {
                    size_t last = readBuffer.find_last_not_of(" \t\n\r");
                    readBuffer = readBuffer.substr(first, (last - first + 1));
                }

                std::string latest_version = readBuffer;

                // Version comparison (lexicographical string comparison as in Python)
                if (latest_version > CURRENT_VERSION) {
                    std::cout << "--- UPDATE AVAILABLE! ---\n"
                              << "🎉 A NEW version of PyCalc-CE is Available! : " << latest_version << "\n"
                              << "Currently using : " << CURRENT_VERSION << "\n"
                              << "Please visit github.com/Chill-Astro/PyCalc-CE to download the latest release!\n" // Provide URL for Updates
                              << "-----------------------\n";
                } else if (latest_version == CURRENT_VERSION) {
                    std::cout << "🎉 PyCalc is up to date!\n\n";
                } else {
                    std::cout << "⚠️ This is a DEV. Build of PyCalc!\n\n"; // For development scenarios
                }
            } else {
                 std::cerr << "--- UPDATE CHECK FAILED! ---\n"
                           << "⚠️ Could not check for updates. Received HTTP status code: " << http_code << "\n"
                           << "------------------------\n";
            }
        }

        // Clean up curl session
        curl_easy_cleanup(curl);
    } else {
        std::cerr << "--- UPDATE CHECK FAILED! ---\n"
                  << "⚠️ Could not initialize libcurl.\n"
                  << "------------------------\n";
    }

    // Global libcurl cleanup (should ideally be done once at program exit)
    curl_global_cleanup();
}

// --- Helper function to safely get float input ---
bool get_float_input(const std::string& prompt, float& value) {
    std::cout << prompt;
    std::cin >> value;
    if (std::cin.fail()) {
        std::cout << "Invalid input. Please enter a number.\n\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }
    std::cout << '\n';
    return true;
}

// --- Helper function to safely get int input ---
bool get_int_input(const std::string& prompt, int& value) {
    std::cout << prompt;
    std::cin >> value;
    if (std::cin.fail()) {
        std::cout << "Invalid input. Please enter an integer.\n\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }
    std::cout << '\n';
    return true;
}


// --- Perform Binary Operation ---
// Simplified from Python version to handle specific operators
void perform_binary_operation(char op) {
    float x, y;
    if (!get_float_input("Enter first number : ", x)) return;
    if (!get_float_input("Enter second number : ", y)) return;

    switch (op) {
        case '+':
            std::cout << x << " + " << y << " = " << x + y << "\n\n";
            break;
        case '-':
            std::cout << x << " - " << y << " = " << x - y << "\n\n";
            break;
        case '*':
            std::cout << x << " * " << y << " = " << x * y << "\n\n";
            break;
        case '^':
            std::cout << x << " ^ " << y << " = " << std::pow(x, y) << "\n\n";
            break;
        // Division is handled separately in main due to zero check
        default:
            std::cout << "Unknown operator in perform_binary_operation.\n\n";
            break;
    }
}

// --- Main Function ---
int main() {
    std::cout << "PyCalc-CE : A Simple and Lightweight Calculator. Made in C++!\n"
              << "Version : " << CURRENT_VERSION << "\n\n"; // Print Version

    check_for_updates(); // Perform update check at startup

    while (true) {
        std::cout << "Select a Mathematical Operation : \n"
                  << "\n1. Addition\n" << "2. Subtraction\n" << "3. Multiplication\n" << "4. Division\n"
                  << "5. Exponents (x^y)\n" << "6. Square Root\n" << "7. Cube Root\n"
                  << "8. Approximate / Rounding\n" << "9. Heron's Formula\n" << "10. Simple Interest\n"
                  << "11. Compound Interest\n" << "12. Prime No. Check\n" << "13. Triangle Check\n"
                  << "14. Right Triangle Check\n" << "15. Perimeter [Various Shapes]\n" << "16. Area [Various Shapes]\n"
                  << "17. Volume [Various Shapes]\n" << "18. Surface Area [Various Shapes]\n"
                  << "19. Curved Surface Area [Various Shapes]\n" << "20. Diagonal Calculation [Various Shapes]\n"
                  << "21. Factorial Calculator\n" << "22. Exit PyCalc-CE\n\n";

        std::string ch;
        std::cout << "Enter choice [ 1 - 22 ] : ";
        std::cin >> ch;
        std::cout << '\n';

        if (ch == "1") { // Addition
            perform_binary_operation('+');
        } else if (ch == "2") { // Subtraction
            perform_binary_operation('-');
        } else if (ch == "3") { // Multiplication
            perform_binary_operation('*');
        } else if (ch == "4") { // Division
            float x, y;
            if (!get_float_input("Enter first number : ", x)) continue;
            if (!get_float_input("Enter second number : ", y)) continue;

            if (y == 0) {
                std::cout << "Div. by Zero Not Defined!\n\n";
            } else {
                std::cout << x << " / " << y << " = " << x / y << "\n\n";
            }
        } else if (ch == "5") { // Exponents
            perform_binary_operation('^');
        } else if (ch == "6") { // Square Root
            float x;
            if (!get_float_input("Enter a number : ", x)) continue;
            if (x < 0) {
                 std::cout << "Cannot calculate square root of a negative number.\n\n";
            } else {
                std::cout << "Root " << x << " = " << std::sqrt(x) << "\n\n";
            }
        } else if (ch == "7") { // Cube Root
            float x;
            if (!get_float_input("Enter a number : ", x)) continue;
            std::cout << "C. Root " << x << " = " << std::cbrt(x) << "\n\n";
        } else if (ch == "8") { // Rounding
            float x;
            if (!get_float_input("Enter a number : ", x)) continue;
            std::cout << std::round(x) << "\n\n";
        } else if (ch == "9") { // Heron's Formula
            std::cout << "NOTE: Some Calculations may print 0.0 depending on the values!\n\n";
            float a, b, c;
            if (!get_float_input("Enter the first side [a] : ", a)) continue;
            if (!get_float_input("Enter the second side [b] : ", b)) continue;
            if (!get_float_input("Enter third side [c] : ", c)) continue;

            if (a <= 0 || b <= 0 || c <= 0) {
                std::cout << "Sides must be +ve.\n\n";
                continue;
            }
             // Check if it forms a valid triangle first (a + b > c, etc.)
            if (!((a + b > c) && (a + c > b) && (b + c > a))) {
                 std::cout << "Sides do not form a valid triangle. Area calculation is not possible.\n\n";
                 continue;
            }

            float s = a + b + c;
            std::cout << "Perimeter : " << s << '\n';
            s /= 2;
            std::cout << "s = " << s << '\n';
            float ar = std::sqrt(s * (s - a) * (s - b) * (s - c));
            std::cout << "Area : " << ar << "\n\n";
        } else if (ch == "10") { // Simple Interest
            float p, r, t;
            if (!get_float_input("Enter the Principal : ", p)) continue;
            if (!get_float_input("Enter the Rate [ % ] : ", r)) continue;
            if (!get_float_input("Enter the Time [ Years ] : ", t)) continue;

            float si = p * r * t / 100;
            std::cout << "Simple Interest : " << si << "\nAmount : " << (si + p) << "\n\n";
        } else if (ch == "11") { // Compound Interest
            std::cout << "Compound Interest Calculation\n\n";
            float p, r, n, t;
            if (!get_float_input("Enter the Principal : ", p)) continue;
            if (!get_float_input("Enter the Rate [ % ] : ", r)) continue;
            if (!get_float_input("Enter the number of times interest is compounded per year : ", n)) continue;
            if (!get_float_input("Enter the Time [ Years ] : ", t)) continue;

            // Ensure n and t are reasonable for pow
             if (n <= 0 || t <= 0) {
                 std::cout << "Number of times compounded per year and Time must be positive.\n\n";
                 continue;
             }


            float a = p * std::pow((1 + r / (100 * n)), n * t);
            float ci = a - p;
            std::cout << "Compound Interest : " << ci << "\nAmount : " << a << "\n\n";
        } else if (ch == "12") { // Prime Number Check
            int x;
            if (!get_int_input("Enter a Number : ", x)) continue;

            if (x > 1) {
                bool is_prime = true;
                for (int i = 2; i * i <= x; ++i) { // Optimization: check up to sqrt(x)
                    if ((x % i) == 0) {
                        is_prime = false;
                        break;
                    }
                }
                if (is_prime) {
                    std::cout << x << " is a Prime Number\n\n";
                } else {
                    std::cout << x << " is not a Prime Number\n\n";
                }
            } else {
                std::cout << x << " is not a Prime Number\n\n";
            }
        } else if (ch == "13") { // Triangle Check
            float a, b, c;
            if (!get_float_input("Enter first side [a] : ", a)) continue;
            if (!get_float_input("Enter second side [b] : ", b)) continue;
            if (!get_float_input("Enter third side [c] : ", c)) continue;

            if (a <= 0 || b <= 0 || c <= 0) {
                std::cout << "Sides must be +ve\n\n";
                continue;
            } else if ((a + b > c) && (a + c > b) && (b + c > a)) {
                std::cout << "Valid Triangle\n\n";
            } else {
                std::cout << "Not a Valid Triangle\n\n";
            }
        } else if (ch == "14") { // Right Triangle Check
             float a, b, c;
            if (!get_float_input("Enter first side [a] : ", a)) continue;
            if (!get_float_input("Enter second side [b] : ", b)) continue;
            if (!get_float_input("Enter third side [c] : ", c)) continue;

            if (a <= 0 || b <= 0 || c <= 0) {
                std::cout << "Sides must be +ve\n\n";
                continue;
            }

            // Sort sides to easily check a^2 + b^2 = c^2 where c is the longest side
            std::vector<float> sides = {a, b, c};
            std::sort(sides.begin(), sides.end());

            // Using a small epsilon for floating point comparison
            float epsilon = 1e-9; // A small tolerance

            if (std::fabs(std::pow(sides[0], 2) + std::pow(sides[1], 2) - std::pow(sides[2], 2)) < epsilon) {
                std::cout << "Is a Right Triangle\n\n";
            } else {
                std::cout << "Not a Right Triangle.\n\n";
            }
        } else if (ch == "15") { // Perimeter [Various Shapes]
            std::cout << "Perimeter Calculation [Various Shapes]\n"
                      << "Select a shape : \n" << "1. Equilateral Triangle\n" << "2. Isosceles Triangle\n"
                      << "3. Square / Rhombus\n" << "4. Rectangle / Parallelogram\n" << "5. Circle\n\n";

            std::string sch;
            std::cout << "Enter shape choice [ 1 - 5 ]: ";
            std::cin >> sch;
            std::cout << '\n';

            if (sch == "1") { // Equilateral Triangle
                float a;
                if (!get_float_input("Enter Side Length [a] : ", a)) continue;
                std::cout << "Perimeter : " << 3 * a << "\n\n";
            } else if (sch == "2") { // Isosceles Triangle
                 float a, b;
                if (!get_float_input("Enter Equal Side's Length : ", a)) continue;
                if (!get_float_input("Enter Non-Equal Side's Length : ", b)) continue;
                std::cout << "Perimeter : " << 2 * a + b << "\n\n"; // Corrected from Area
            } else if (sch == "3") { // Square / Rhombus
                 float a;
                if (!get_float_input("Enter Length of Side [a] : ", a)) continue;
                std::cout << "Perimeter : " << 4 * a << "\n\n";
            } else if (sch == "4") { // Rectangle / Parallelogram
                 float l, b;
                if (!get_float_input("Enter Length [l] : ", l)) continue;
                if (!get_float_input("Enter Breadth [b] : ", b)) continue;
                std::cout << "Perimeter : " << 2 * (l + b) << "\n\n";
            } else if (sch == "5") { // circle
                 float r;
                if (!get_float_input("Enter the Radius [r] : ", r)) continue;
                std::cout << "Circumference : " << 2 * M_PI * r << "\n\n";
            } else {
                std::cout << "Invalid Option! Exiting Perimeter Calculation ...\n\n";
            }
        } else if (ch == "16") { // Area [Various Shapes]
            std::cout << "Area Calculation [Various Shapes]\n"
                      << "Select a shape : \n" << "1. Equilateral Triangle\n" << "2. Isosceles Triangle\n"
                      << "3. Square\n" << "4. Rectangle / Parallelogram\n" << "5. Rhombus\n"
                      << "6. Circle\n" << "7. Semi-circle\n\n";

            std::string sch;
            std::cout << "Enter shape choice [ 1 - 7 ] : ";
            std::cin >> sch;
            std::cout << '\n';

            if (sch == "1") { // Equilateral Triangle
                float a;
                if (!get_float_input("Enter Side Length [a] : ", a)) continue;
                float ar = (std::sqrt(3) / 4) * std::pow(a, 2);
                std::cout << "Area : " << ar << "\n\n";
            } else if (sch == "2") { // Isosceles Triangle
                float a, b;
                if (!get_float_input("Enter Equal Side's Length : ", a)) continue;
                if (!get_float_input("Enter Non-Equal Side's Length : ", b)) continue;
                 if (4 * std::pow(a, 2) - std::pow(b, 2) < 0) {
                    std::cout << "Sides do not form a valid isosceles triangle.\n\n";
                    continue;
                 }
                float ar = (b / 4.0) * std::sqrt(4 * std::pow(a, 2) - std::pow(b, 2)); // Corrected Area formula
                std::cout << "Area : " << ar << "\n\n";
            } else if (sch == "3") { // Square
                float a;
                if (!get_float_input("Enter Length of Side [a] : ", a)) continue;
                float ar = std::pow(a, 2);
                std::cout << "Area : " << ar << "\n\n";
            } else if (sch == "4") { // Rectangle / Parallelogram
                float l, b;
                if (!get_float_input("Enter Length [l] : ", l)) continue;
                if (!get_float_input("Enter Breadth [b] : ", b)) continue;
                float ar = l * b;
                std::cout << "Area : " << ar << "\n\n";
            } else if (sch == "5") { // Rhombus
                float d1, d2;
                if (!get_float_input("Enter Diagonal 1 [d1] : ", d1)) continue;
                if (!get_float_input("Enter Diagonal 2 [d2] : ", d2)) continue;
                float area = 0.5 * d1 * d2;
                std::cout << "Area of Rhombus : " << area << "\n\n";
            } else if (sch == "6") { // circle
                float r;
                if (!get_float_input("Enter the Radius [r] : ", r)) continue;
                float area = M_PI * std::pow(r, 2);
                std::cout << "Area : " << area << "\n\n";
            } else if (sch == "7") { // Semi-circle
                float r;
                if (!get_float_input("Enter the Radius [r] : ", r)) continue;
                float area = 0.5 * M_PI * std::pow(r, 2);
                std::cout << "Area : " << area << "\n\n";
            } else {
                std::cout << "Invalid Option! Exiting Area Calculation ...\n\n";
            }
        } else if (ch == "17") { // Volume [Various Shapes]
            std::cout << "Volume Calculation [Various Shapes]\n"
                      << "Select a shape : \n" << "1. Cube\n" << "2. Cuboid\n" << "3. Cylinder\n"
                      << "4. Cone\n" << "5. Sphere\n\n";

            std::string sch;
            std::cout << "Enter shape choice [ 1 - 5 ] : ";
            std::cin >> sch;
            std::cout << '\n';

            if (sch == "1") { // Cube
                float a;
                if (!get_float_input("Enter Length of Side [a] : ", a)) continue;
                float vol = std::pow(a, 3);
                std::cout << "Volume : " << vol << "\n\n";
            } else if (sch == "2") { // Cuboid
                 float l, b, h;
                if (!get_float_input("Enter Length [l] : ", l)) continue;
                if (!get_float_input("Enter Breadth [b] : ", b)) continue;
                if (!get_float_input("Enter Height [h] : ", h)) continue;
                float vol = l * b * h;
                std::cout << "Volume : " << vol << "\n\n";
            } else if (sch == "3") { // Cylinder
                float r, h;
                if (!get_float_input("Enter the Radius [r] : ", r)) continue;
                if (!get_float_input("Enter the Height [h] : ", h)) continue;
                float vol = M_PI * std::pow(r, 2) * h;
                std::cout << "Volume : " << vol << "\n\n";
            } else if (sch == "4") { // Cone
                float r, h;
                if (!get_float_input("Enter the Radius [r] : ", r)) continue;
                if (!get_float_input("Enter the Height [h] : ", h)) continue;
                float vol = (1.0/3.0) * M_PI * std::pow(r, 2) * h;
                std::cout << "Volume : " << vol << "\n\n";
            } else if (sch == "5") { // Sphere
                float r;
                if (!get_float_input("Enter the Radius [r] : ", r)) continue;
                float vol = (4.0/3.0) * M_PI * std::pow(r, 3);
                std::cout << "Volume : " << vol << "\n\n";
            } else {
                std::cout << "Invalid Option! Exiting Volume Calculation ...\n\n";
            }
        } else if (ch == "18") { // Surface Area [Various Shapes]
             std::cout << "Surface Area Calculation [Various Shapes]\n"
                       << "Select a shape : \n" << "1. Cube\n" << "2. Cuboid\n" << "3. Cylinder\n"
                       << "4. Cone\n" << "5. Sphere\n\n";

            std::string sch;
            std::cout << "Enter shape choice [ 1 - 5 ] : ";
            std::cin >> sch;
            std::cout << '\n';

            if (sch == "1") { // Cube
                float a;
                if (!get_float_input("Enter Length of Side [a] : ", a)) continue;
                float sa = 6 * std::pow(a, 2);
                std::cout << "Surface Area : " << sa << "\n\n";
            } else if (sch == "2") { // Cuboid
                float l, b, h;
                if (!get_float_input("Enter Length [l] : ", l)) continue;
                if (!get_float_input("Enter Breadth [b] : ", b)) continue;
                if (!get_float_input("Enter Height [h] : ", h)) continue;
                float sa = 2 * (l * b + b * h + h * l);
                std::cout << "Surface Area : " << sa << "\n\n";
            } else if (sch == "3") { // Cylinder
                 float r, h;
                if (!get_float_input("Enter the Radius [r] : ", r)) continue;
                if (!get_float_input("Enter the Height [h] : ", h)) continue;
                float sa = 2 * M_PI * r * (r + h);
                std::cout << "Surface Area : " << sa << "\n\n";
            } else if (sch == "4") { // Cone
                float r, h;
                if (!get_float_input("Enter the Radius [r] : ", r)) continue;
                if (!get_float_input("Enter the Height [h] : ", h)) continue;
                float sa = M_PI * r * (r + std::sqrt(std::pow(h, 2) + std::pow(r, 2)));
                std::cout << "Surface Area : " << sa << "\n\n";
            } else if (sch == "5") { // Sphere
                float r;
                if (!get_float_input("Enter the Radius [r] : ", r)) continue;
                float sa = 4 * M_PI * std::pow(r, 2);
                std::cout << "Surface Area : " << sa << "\n\n";
            } else {
                std::cout << "Invalid Option! Exiting Surface Area Calculation ...\n\n";
            }
        } else if (ch == "19") { // Curved Surface Area [Various Shapes]
            std::cout << "Curved Surface Area Calculation [Various Shapes]\n"
                      << "Select a shape : \n" << "1. Cylinder\n" << "2. Cone\n" << "3. Sphere\n\n";

            std::string sch;
            std::cout << "Enter shape choice [ 1 - 3 ] : ";
            std::cin >> sch;
            std::cout << '\n';

            if (sch == "1") { // Cylinder
                float r, h;
                if (!get_float_input("Enter the Radius [r] : ", r)) continue;
                if (!get_float_input("Enter the Height [h] : ", h)) continue;
                float csa = 2 * M_PI * r * h;
                std::cout << "Curved Surface Area : " << csa << "\n\n";
            } else if (sch == "2") { // Cone
                float r, h;
                if (!get_float_input("Enter the Radius [r] : ", r)) continue;
                if (!get_float_input("Enter the Height [h] : ", h)) continue;
                float csa = M_PI * r * std::sqrt(std::pow(h, 2) + std::pow(r, 2));
                std::cout << "Curved Surface Area : " << csa << "\n\n";
            } else if (sch == "3") { // Sphere
                float r;
                if (!get_float_input("Enter the Radius [r] : ", r)) continue;
                float csa = 4 * M_PI * std::pow(r, 2); // Sphere's CSA is the same as its total surface area
                std::cout << "Curved Surface Area : " << csa << "\n\n";
            } else {
                std::cout << "Invalid Option! Exiting Curved Surface Area Calculation ...\n\n";
            }
        } else if (ch == "20") { // Diagonal Calculation [Various Shapes]
            std::cout << "Diagonal Calculation [Various Shapes]\n"
                      << "Select a shape : \n" << "1. Square\n" << "2. Rectangle\n"
                      << "3. Cube\n" << "4. Cuboid\n\n";

            std::string sch;
            std::cout << "Enter shape choice [ 1 - 4 ] : ";
            std::cin >> sch;
            std::cout << '\n';

            if (sch == "1") { // Square
                float a;
                if (!get_float_input("Enter Length of Side [a] : ", a)) continue;
                float d = std::sqrt(2) * a;
                std::cout << "Diagonal : " << d << "\n\n";
            } else if (sch == "2") { // Rectangle
                float l, b;
                if (!get_float_input("Enter Length [l] : ", l)) continue;
                if (!get_float_input("Enter Breadth [b] : ", b)) continue;
                float d = std::sqrt(std::pow(l, 2) + std::pow(b, 2));
                std::cout << "Diagonal : " << d << "\n\n";
            } else if (sch == "3") { // Cube
                float a;
                if (!get_float_input("Enter Length of Side [a] : ", a)) continue;
                float d = std::sqrt(3) * a;
                std::cout << "Diagonal : " << d << "\n\n";
            } else if (sch == "4") { // Cuboid
                float l, b, h;
                if (!get_float_input("Enter Length [l] : ", l)) continue;
                if (!get_float_input("Enter Breadth [b] : ", b)) continue;
                if (!get_float_input("Enter Height [h] : ", h)) continue;
                float d = std::sqrt(std::pow(l, 2) + std::pow(b, 2) + std::pow(h, 2));
                std::cout << "Diagonal : " << d << "\n\n";
            } else {
                std::cout << "Invalid Option! Exiting Diagonal Calculation ...\n\n";
            }
        } else if (ch == "21") { // Factorial Calculation
            int x;
            if (!get_int_input("Enter a Number : ", x)) continue;

            if (x < 0) {
                std::cout << "\nFactorial Not Defined for Negative Numbers!\n\n";
            } else if (x == 0 || x == 1) {
                std::cout << "\nFactorial of " << x << " is 1\n\n";
            } else {
                long long fact = 1; // Use long long for larger factorials
                for (int i = 2; i <= x; ++i) {
                    fact *= i;
                }
                std::cout << "\nFactorial of " << x << " is " << fact << "\n\n";
            }
        } else if (ch == "22") { // Exit Program
            break; // Exit the while loop
        } else { // Default Case
            std::cout << "Please enter a Valid Input! Restarting PyCalc-CE ...\n\n";
            continue;
        }

        std::string next_calc;
        std::cout << "Do you Want to Perform Another Calculation? [y/n]: "; // Next_Calc Loop
        std::cin >> next_calc;
        std::cout << '\n';

        if (next_calc == "n" || next_calc == "no") {
            break; // Exit the while loop
        } else if (next_calc == "y" || next_calc == "yes") {
             // continue (implicit)
        }
        else {
             std::cout << "Please enter a Valid Input! Restarting PyCalc-CE ...\n\n";
        }
    }

    return 0; // Indicate successful execution
}