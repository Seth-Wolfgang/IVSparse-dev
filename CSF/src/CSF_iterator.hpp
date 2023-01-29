#pragma once


namespace CSF {
    template <typename T, int compression_level>
    class SparseMatrix<T, compression_level>::Iterator {
        public:
            int y = 2;
    };
}