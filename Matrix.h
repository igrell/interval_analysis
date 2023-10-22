#pragma include once

#include <iostream>
#include <algorithm>
#include <iomanip>
#include <utility>

//using namespace std;

template<typename T, const size_t N, const size_t M>
class Matrix {
    T data[N * M];
    unsigned startId = 0;
    unsigned stopId = (N * M);

public:

    class iterator : public std::iterator<
            std::forward_iterator_tag,   // iterator_category
            T,                      // value_type
            T,                      // difference_type
            const T *,               // pointer
            T> {
        unsigned valId = startId;
        Matrix matrix;

    public:
        iterator(unsigned _valId, Matrix matrix) : valId(_valId), matrix(matrix) {}

        iterator &operator++() {
            valId++;
            return *this;
        }

        iterator operator++(int) {
            iterator res = *this;
            ++(*this);
            return res;
        }

        bool operator==(iterator other) const {
            return valId == other.valId;
        }

        bool operator!=(iterator other) const {
            return !(*this == other);
        }

        T &operator*() { return matrix.data[valId]; }

        T *operator->() { return matrix.data[valId]; }
    };

    iterator begin() { return iterator(startId, *this); }

    iterator end() { return iterator(stopId, *this); }


    class const_iterator : public std::iterator<
            std::forward_iterator_tag,   // iterator_category
            T,                      // value_type
            T,                      // difference_type
            const T *,               // pointer
            T> {
        unsigned valId = 0;
        Matrix matrix;

    public:
        const_iterator(unsigned _valId, Matrix matrix) : valId(_valId), matrix(matrix) {}

        const_iterator &operator++() {
            valId++;
            return *this;
        }

        const_iterator operator++(int) {
            const_iterator res = *this;
            ++(*this);
            return res;
        }

        bool operator==(const_iterator other) const {
            return valId == other.valId;
        }

        bool operator!=(const_iterator other) const {
            return !(*this == other);
        }

        T &operator*() { return matrix.data[valId]; }
    };

    const_iterator begin() const { return const_iterator(startId, *this); }

    const_iterator end() const { return const_iterator(stopId, *this); }

    class row_iterator : public std::iterator<
            std::forward_iterator_tag,   // iterator_category
            T,                      // value_type
            T,                      // difference_type
            const T *,               // pointer
            T> {
        unsigned valId = startId;
        Matrix matrix;

    public:
        row_iterator(unsigned _valId, Matrix matrix) : valId(_valId), matrix(matrix) {}

        row_iterator &operator++() {
            valId++;
            return *this;
        }

        row_iterator operator++(int) {
            iterator res = *this;
            ++(*this);
            return res;
        }

        bool operator==(row_iterator other) const {
            return valId == other.valId;
        }

        bool operator!=(row_iterator other) const {
            return !(*this == other);
        }

        T &operator*() { return matrix.data[valId]; }

        T *operator->() { return &matrix.data[valId]; }
    };

    row_iterator row_begin(const unsigned rowNo) {
        return row_iterator((rowNo - 1) * M, *this);
    }

    row_iterator row_end(const unsigned rowNo) {
        return row_iterator(rowNo * M, *this);
    }

    class col_iterator : public std::iterator<
            std::forward_iterator_tag,   // iterator_category
            T,                      // value_type
            T,                      // difference_type
            const T *,               // pointer
            T> {
        unsigned valId = startId;
        Matrix matrix;

    public:
        col_iterator(unsigned _valId, Matrix matrix) : valId(_valId), matrix(matrix) {}

        col_iterator &operator++() {
            valId += M;
            return *this;
        }

        col_iterator operator++(int) {
            iterator res = *this;
            ++(*this);
            return res;
        }

        bool operator==(col_iterator other) const {
            return valId == other.valId;
        }

        bool operator!=(col_iterator other) const {
            return !(*this == other);
        }

        T &operator*() { return matrix.data[valId]; }

        T *operator->() { return matrix.data[valId]; }
    };

    col_iterator col_begin(const unsigned colNo) {
        return col_iterator(colNo - 1, *this);
    }

    col_iterator col_end(const unsigned colNo) {
        return col_iterator(M * N + (colNo - 1), *this);
    }

    [[nodiscard]] constexpr size_t numberOfRows() const { return N; }

    [[nodiscard]] constexpr size_t numberOfColumns() const { return M; }

    explicit Matrix(const int nrows = N, const int ncols = M) {
        std::fill_n(data, N * M, T{});
    }

    Matrix(const std::initializer_list<std::initializer_list<T>> &list) {
        T *p = data;
        for (const auto &row: list) {
            T *p2 = std::copy(row.begin(), row.end(), p);
            std::fill(p2, p += M, T{});
        }
    }

    Matrix(const Matrix &m) {
        std::copy_n(m.data, N * M, data);
    }

    Matrix &operator=(const Matrix &m) {
        if (&m != this) {
            std::copy_n(m.data, N * M, data);
        }
        return *this;
    }

    T &operator()(int i, int j) {
        return data[(i - 1) * M + j - 1];
    }

    const T &operator()(int i, int j) const {
        return data[(i - 1) * M + j - 1];
    }

    friend Matrix operator+(const Matrix &a, const Matrix &b) {
        Matrix r;
        for (int i = 1; i <= N; ++i) {
            for (int j = 1; j <= M; ++j) {
                r(i, j) = a(i, j) + b(i, j);
            }
        }
        return r;
    }

};

template<typename T, size_t N, size_t M>
const void printMatrix(const Matrix<T, N, M> &m, const int width = 10) {
    for (int i = 1; i <= m.numberOfRows(); ++i) {
        for (int j = 1; j <= m.numberOfColumns(); ++j) {
            if (j != 1) std::cout << " ";
            std::cout << std::setw(width) << m(i, j);
        }
        std::cout << std::endl;
    }
}
