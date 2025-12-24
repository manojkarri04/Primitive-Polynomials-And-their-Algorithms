#include <iostream>
#include <vector>
#include <cmath>

// Function to check if a polynomial is irreducible (simplified for demonstration)
bool isIrreducible(const std::vector<bool>& poly) {
    // For simplicity, this function just checks if the polynomial is not divisible by x or x+1
    // Real implementation should check all possible factors
    if (poly[0] == 0) return false; // Not divisible by x
    if (poly.size() == 2 && poly[1] == 0) return false; // Special case for x+1
    
    // Simplified check; actual implementation should be more comprehensive
    return true;
}

// Function to compute x^n mod P(x)
bool computeMod(const std::vector<bool>& poly, int n) {
    bool result = true; // Start with x^0 = 1
    for (int i = 0; i < n; ++i) {
        result = result ^ (poly[0] && result); // Simplified multiplication by x
        for (int j = 1; j < poly.size(); ++j) {
            if (poly[j]) {
                result = result ^ (poly[0] && result); // Simplified multiplication by x^j
            }
        }
    }
    return result;
}

// Function to check if a polynomial is primitive
bool isPrimitive(const std::vector<bool>& poly, int degree) {
    if (!isIrreducible(poly)) return false; // Must be irreducible
    
    int targetValue = (1 << degree) - 1;
    
    // Check if x^(2^n - 1) ≡ 1 mod P(x)
    bool condition1 = computeMod(poly, targetValue);
    
    // Check for all prime factors of 2^n - 1
    for (int p = 2; p <= targetValue; ++p) {
        if (targetValue % p == 0) {
            bool condition2 = computeMod(poly, targetValue / p);
            if (condition2) return false; // Not primitive if any condition fails
        }
    }
    
    return condition1; // Primitive if all conditions pass
}

int main() {
    // Example polynomial: x^3 + x + 1 (primitive over GF(2))
    std::vector<bool> poly = {1, 1, 0, 1}; // Coefficients from lowest to highest degree
    
    int degree = poly.size() - 1; // Degree of the polynomial
    
    if (isPrimitive(poly, degree)) {
        std::cout << "The polynomial is primitive." << std::endl;
    } else {
        std::cout << "The polynomial is not primitive." << std::endl;
    }
    
    return 0;
}

