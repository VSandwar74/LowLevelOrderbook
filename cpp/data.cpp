#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

struct RowData {
    std::string name;
    double score1;
    double score2;
    double score3;
};

int main() {
    std::ifstream file("/Users/VishakhS/QFS/CPPOrderbook/LOBSTER_SampleFile_AMZN_2012-06-21_1/AMZN_2012-06-21_34200000_57600000_message_1.csv"); // Open the CSV file

    if (!file.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }

    std::string line;
    std::getline(file, line); // Read and ignore the header line

    while (std::getline(file, line)) { // Read each line from the file
        std::istringstream iss(line);
        RowData rowData;
        
        if (std::getline(iss, rowData.name, ',') &&
            (iss >> rowData.score1 >> rowData.score2 >> rowData.score3)) {
            // Successfully read and parsed the row
            
            // Perform data analysis on the rowData
            // Example: Calculate the average score
            double averageScore = (rowData.score1 + rowData.score2 + rowData.score3) / 3.0;
            
            // Print the analysis results
            std::cout << "Name: " << rowData.name << std::endl;
            std::cout << "Average Score: " << averageScore << std::endl;
            std::cout << std::endl;
        }
    }

    file.close(); // Close the file when done

    return 0;
}
