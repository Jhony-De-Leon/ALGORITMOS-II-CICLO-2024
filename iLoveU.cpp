#include <iostream>
#include <cmath> 

int main() {
    float x, y;
    
    for (y = 1.5; y > -1.5; y -= 0.1) { 
        for (x = -1.5; x < 1.5; x += 0.05) {
            
            float equation = (x*x + y*y - 1)*(x*x + y*y - 1)*(x*x + y*y - 1) - x*x*y*y*y;
            putchar(equation <= 0.0 ? '*' : ' ');
        }
        putchar('\n'); 
    }
    
    system("color 0c");

    std::cout << "I Love U <3" << std::endl;

    return 0;
}

