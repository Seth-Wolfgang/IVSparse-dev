//create an iterator struct


struct ByteIterator {
        
    using iterator_category = std::forward_iterator_tag;
    using value_type        = char; //change to bytes?
    using pointer           = char*;
    using reference         = char&;

    //constructor
    ByteIterator(pointer ptr) : ptr_(ptr) {}

    //returns value or pointer 
    referance operator* const {return *ptr;} //should return value to integer, even if reading a binary file
    pointer operator->() {return ptr;} //returns the pointer

    //prefix increment
    ByteIterator& operator++() { 
        if (*ptr < 0) { // if the value is negative, then its a new value for the matrix
            newValue = *ptr; //IMPORTANT NOTE: actual values are set to negative as a delimitor
            counter = 0;
        } 
        else { //else its a counter for the number of times the value is repeated
            counter += *ptr;
            for(int i = 0; i < counter; i++){
                newVector.push_back(0);
            }
            newVector.push_back(newValue);
        }            
        ptr++; 
        return *this
    }

    //postfix increment
    ByteIterator& operator++(int) {ByteIterator temp = *this; ptr++; return temp;}

    //equality operators
    friend bool operator==(const ByteIterator& start, const ByteIterator& end) {return start.ptr == end.ptr;}
    friend bool operator!=(const ByteIterator& start, const ByteIterator& end) {return start.ptr != end.ptr;}

    private:
        int value;
        int counter;
        int delta;
        pointer ptr;
        std::vector<int>::iterator vecRead;
        std::vector<int>::iterator end;


};