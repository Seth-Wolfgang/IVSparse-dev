

int main() {
    std::ifstream newFile;
    string filePath = ("inputFiles/test.txt"); //file path will become an argument
    string fileToEncode = ("inputFiles/testEncode.txt"); //whether or not the file is encoded/decoded will become an argument
    vector<int> decodeVec;
    decodeFile(decodeVec, filePath);
    encodeFile(decodeVec, fileToEncode);
    for (int i = 0; i < decodeVec.size(); i++) {
        std::cout << decodeVec[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}


void decodeFile(vector<int> &newVector, string fileName) {
    std::ifstream newFile;
    newFile.open(fileName);
    if (newFile.is_open()) {
        std::istream_iterator<int> byteRead(newFile);
        std::istream_iterator<int> end;
        int counter;
        int newValue;
        while (byteRead != end) {
            if (*byteRead < 0) { // if the value is negative, then its a new value for the matrix
                newValue = *byteRead; //IMPORTANT NOTE: actual values are set to negative as a delimitor
                counter = 0;
            } 
            else { //else its a counter for the number of times the value is repeated
                counter += *byteRead;
                for(int j = 0; j < counter; j++){
                    newVector.push_back(0);
                }
                newVector.push_back(newValue);
            }            
            byteRead++;
        }
    } else {
        cout << "File not found" << endl;
    }
    newFile.close();
}

// example: -1 5 10 23 44... <some negative followed by positive>
// turns to -1 5 5 13 31... <some negative followed by positive deltas>

void encodeFile(vector<int> myVector, string fileName) {
    ofstream newFile;
    newFile.open(fileName);
    std::vector<int>::iterator vecRead(myVector.begin());
    std::vector<int>::iterator end(myVector.end());
    int counter = 0;
    int delta = 0;
    int newValue = 0;
    while(vecRead != end) {
        if(*vecRead < 0){ //if the value is negative, we will adjust the counter and delta
            if(newValue != *vecRead){ //if the value is different, delta will reset and the new value will be printed
                newFile << *vecRead << " ";
                newValue = *vecRead; //newValue is set to the new value
                delta = 0;
            }
            newFile << counter - delta << " "; //prints new delta to file
            delta += counter - delta; //adds new delta to delta
            counter = 0;
        } else {
            counter++; //iterates counter for each 0
        }
        vecRead++;
    }

    newFile.close();
}
