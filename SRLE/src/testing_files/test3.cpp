#include <iostream>
#include <vector>

using namespace std;

void testing(int *mat) {
    mat[0] = 1;
}


int main()
{
    
    void* data;
    data = malloc(100 * sizeof(int));

    void* ptr = data;

    uint32_t* ptr2 = static_cast<uint32_t*>(ptr);

    ptr2[0] = 34;

    cout << *(static_cast<uint32_t*>(ptr)) << endl;

    *(static_cast<uint32_t*>(ptr)) = 35;

    cout << *(static_cast<uint32_t*>(ptr)) << endl;

    // move ptr to next element
    ptr = static_cast<uint32_t*>(ptr) + 1;

    *(static_cast<uint32_t*>(ptr)) = 36;

    cout << *(static_cast<uint32_t*>(ptr)) << endl;

    free(data);


    int mat [4] = {0, 0, 0, 0};

    testing(mat);

    cout << mat[0] << endl;

    return 0;
}