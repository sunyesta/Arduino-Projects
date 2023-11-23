

#ifndef MY_LIST_HPP
#define MY_LIST_HPP

template <typename T>
class List {
   private:
    int _arrSize;
    int _length = 0;
    T *arr;

   public:
    List();

    // push back
    void pback(T item);

    int length();

    T get(int i);
    void set(int i, T value);
};

template <typename T>
List<T>::List() {
    int initialSize = 1;

    arr = (T *)calloc(initialSize, sizeof(T));
    if (arr == NULL) {
        exit(-1);
    }

    _arrSize = initialSize;
}

template <typename T>
void List<T>::pback(T item) {
    _length += 1;
    if (_arrSize < _length) {
        _arrSize = 2 * _arrSize;

        realloc(arr, _arrSize);
        assert(arr);
    }

    arr[_length - 1] = item;
}

template <typename T>
int List<T>::length() {
    return _length;
}

template <typename T>
T List<T>::get(int i) {
    return arr[i];
}

template <typename T>
void List<T>::set(int i, T value) {
    arr[i] = value;
}

#endif /* MY_LIST_HPP */