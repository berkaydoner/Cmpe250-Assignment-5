/*
Student Name: Berkay Döner
Student Number: 2017400117
Project Number: 5
Compile Status: [SUCCESS]
Running Status: [SUCCESS]
Notes: Anything you want to say about your code that will be helpful in the grading process.
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]){
    //I copied the code for file reading errors from the previous projects.
    if (argc != 3) {
        // cerr should be used for errors
        cerr << "Run the code with the following command: ./cmpe250-assignment4 [input_file] [output_file]" << endl;
        return 1;
    }
    // Open the input and output files, check for failures
    ifstream inFile(argv[1]);
    if (!inFile) { // operator! is synonymous to .fail(), checking if there was a failure
        cerr << "There was a problem opening \"" << argv[1] << "\" as input file" << endl;
        return 1;
    }

    ofstream outFile(argv[2]);
    if (!outFile) {
        cerr << "There was a problem opening \"" << argv[2] << "\" as output file" << endl;
        return 1;
    }
    string line,temp;//these will be useful to read the input
    getline(inFile,line);//now line variable holds the first line
    istringstream linestream(line);//to read within the first line
    getline(linestream,temp,' ');//now temp holds the first number in the first line
    int N = stoi(temp);//this number is N, it is casted to int
    getline(linestream,temp,' ');//now temp holds the second number in the first line
    int M = stoi(temp);//this number is M
    int* prices = new int[N];//to store the prices
    getline(inFile,line);//line now holds the second line
    istringstream linest(line);//to read within the second line
    for(int i =0;i<N;i++){//to read N numbers
        getline(linest,temp,' ');//this line allow temp to hold the numbers in order
        prices[i] = stoi(temp);//we store the number in prices array
    }
    long long int* prev = new long long int[M];//this will be useful for storing variables for dynamic programming
    std::sort(prices,prices+N);
    //sorts the array, using std library. Sorting is needed since we want to minimize the costs
    prev[0] = prices[0];//we store the minimum price
    outFile<< prices[0] << " ";//write it to the file
    long long int sum = prices[0];//sum starts with this number
    for(int i =1;i<M;i++){
        /*For the costs until the M chocolate, Ayşe can buy all chocolates in the first day, so costs are just
         a sum of prices until some point. */
        prev[i]=prices[i];//prev is initialized as prices for first M numbers
        sum+= prices[i];//prices are just added to the sum
        outFile << sum << " ";//write the sum
    }
    /*For the remaining costs, we can notice a pattern in costs. For example, in the first input, third cost is
     11, while second cost is 5. The third cheapest chocolate costs 4. The difference between 11 and 5 is 6. This
     6 is the current cheapest cholocate(4) + the i%M cost( i=2 M=2, so i%2= 0 and the 0th cost is 2). To continue
     to this pattern, we must also update the previous costs. This can be seen fifth cost from the same input, it is
     30 while the previous is 18. The difference is 12, current lowest price is 6, so 6 should be the previous cost
     , so we should update it beforehand.*/
    for(int j=M;j<N;j++){//For the remaining costs
        int tmp = prices[j];//the current cheapest chocolate's price
        sum+=  prev[j%M] + tmp;//sum is equal to the j%M cost and the current price, by the pattern above
        prev[j%M] += tmp;//j%M cost is updated, we add the current price to it to continue the pattern.
        outFile << sum << " ";//write the sum
    }
    return 0;
}
