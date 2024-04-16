#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

#define d 256
#define MAX_LENGTH 1000

void search(const std::string& pat, const std::string& txt, int q) {
    int M = pat.length();
    int N = txt.length();
    int i, j;
    int p = 0; 
    int t = 0; 
    int h = 1;

    for (i = 0; i < M - 1; i++)
        h = (h * d) % q;

    for (i = 0; i < M; i++) {
        p = (d * p + pat[i]) % q;
        t = (d * t + txt[i]) % q;
    }

    for (i = 0; i <= N - M; i++) {
        if (p == t) {
            for (j = 0; j < M; j++) {
                if (txt[i + j] != pat[j])
                    break;
            }
            if (j == M)
                std::cout << "Pattern found at index " << i << std::endl;
        }
        if (i < N - M) {
            t = (d * (t - txt[i] * h) + txt[i + M]) % q;
            if (t < 0)
                t = (t + q);
        }
    }
}

int main() {
    std::string txt, pat, textFilePath;

    // Prompt the user to enter the file path for the text
    std::cout << "Enter the file path for the text: ";
    std::cin >> textFilePath;

    std::ifstream textFile(textFilePath);
    if (!textFile.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    // Read both text and pattern strings from the file
    if (!(textFile >> txt >> pat)) {
        std::cerr << "Error reading text and pattern from file!" << std::endl;
        textFile.close();
        return 1;
    }
    
    textFile.close();

    // A prime number
    int q = 101;

    // Perform the search
    search(pat, txt, q);

    return 0;
}
