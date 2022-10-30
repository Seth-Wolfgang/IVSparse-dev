//create an iterator struct


class ByteIterator {
    private:
        uint32_t const magicByteSize;
        uint32_t const paramType;
        uint32_t const rowType;
        uint32_t const nRows;
        uint32_t const colType;
        uint32_t const nCols;
        uint32_t const valueType;
        uint32_t const oldIndexType;
        uint8_t const delimitor = 0;
        


    public:
        char[] data;
    //constructor
    //read in first few bytes for data
    
    ByteIterator::ByteIterator(string filePath) {
        //read in first few bytes for data
        //set up the iterator
        uint32_t[] params = new uint32_t[8]
        std::ifstream fileStream(filePath, ios::in | std::ios::binary);
        if (fileStream.is_open()) {
            fileStream.read(data, 4); //assuming all magic numbers are uint32_t
            for(int i = 0; i < 8; i++) {
                fileStream.read(data, 4);
                params[i] = (uint32_t)data;

                if(data == delimitor) {
                    break;
                }
            }
            
        this.magicByteSize = params[0]; //change
        this.paramType     = params[1];
        this.rowType       = params[2];
        this.nRows         = params[3];
        this.colType       = params[4];
        this.nCols         = params[5];
        this.valueType     = params[6];
        this.oldIndexType  = params[7];
        cout << Parameters set << endl;

        }
        else {
            cout << "File not found" << endl;
        }

    }

    //NO VECTOR TYPES

    //LOOK INTO 
    //https://en.cppreference.com/w/cpp/language/partial_specialization

    //constructor
    ByteIterator(pointer ptr) : ptr(ptr) {}

    //returns value or pointer 
    referance operator* const {return *ptr;} //should return value to char, even if reading a binary file

    //prefix increment
    ByteIterator& operator++() {
        ptr += 4;
        read(*ptr, 4); //wrong
        //read until delimiter
        //then increment based off of how many bytes are needed to represent the next value
        //incrememnt until next signed bit and read in the column indices
    }
    



    //equality operators -> REPLACE WITH ABILITY TO WORK WITH MANY BYTES
    bool operator==(const ByteIterator& start, const ByteIterator& end) {return start.ptr == end.ptr;} 
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