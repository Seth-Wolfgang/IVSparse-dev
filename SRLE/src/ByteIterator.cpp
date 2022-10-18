//create an iterator struct


class ByteIterator {
    //NO VECTOR TYPES




    //constructor
    ByteIterator(pointer ptr) : ptr_(ptr) {}

    //returns value or pointer 
    referance operator* const {return *ptr;} //should return value to integer, even if reading a binary file
    // pointer operator->() {return ptr;} //returns the pointer

    //prefix increment
    ByteIterator& operator++() {
        //incrememnt until first signed byte
        //then increment based off of how many bytes are needed to represent the next value
        //incrememnt until next signed bit and read in the column indices

    }
    

    //equality operators
    bool operator==(const ByteIterator& start, const ByteIterator& end) {return start.ptr == end.ptr;} //replace with checking index
    bool operator!=(const ByteIterator& start, const ByteIterator& end) {return start.ptr != end.ptr;}

    private:

    public:

    void detectCompression(){
    //have user input for what kind of compression level they want
    //seamlessly detect compression type
    //COO -> uses n+1 size for col pointer
    //VSE -> 
    //vSRLE -> done (kinda)

    }

    void detectDataType(){
    //look up negative number in table



    }



};