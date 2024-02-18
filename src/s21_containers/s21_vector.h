#include <iostream>
#include <limits>
#include <utility>
namespace s21 {
template <class T>
class vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;

 private:
  template <bool IsConst>
  class v_iterator {
   private:
    using pointer_type = std::conditional_t<IsConst, const T *, T *>;
    using reference_type = std::conditional_t<IsConst, const T &, T &>;
    using value_type = std::conditional_t<IsConst, const T, T>;
    // нужно ли определить size_typeype????

   public:
    v_iterator(pointer_type ptr)
        : ptr_(ptr) {
    }  // explicit = ошибки связанные с арифиетическими операциями с итераторами
    v_iterator(const v_iterator &) = default;

    pointer_type get_ptr() { return ptr_; }

    bool operator!=(const v_iterator &other) {
      return this->ptr_ != other.ptr_;
    }
    bool operator==(const v_iterator &other) {
      return this->ptr_ == other.ptr_;
    }

    const_reference operator*() { return *ptr_; }  // изменил на const_reference

    v_iterator operator++() {
      ++ptr_;
      return *this;
    }

    v_iterator operator++(int) {
      v_iterator copy = *this;
      ++ptr_;
      return copy;
    }

    v_iterator &operator--() {
      --ptr_;
      return *this;
    }
    const v_iterator operator--(int) {
      v_iterator copy = *this;

      --ptr_;
      return copy;
    }
    pointer_type operator->() { return ptr_; }
    pointer_type operator+(size_type _offset_) { return ptr_ + _offset_; }
    pointer_type operator-(size_type _offset_) { return ptr_ - _offset_; }
    size_type operator-(v_iterator reduced) {
      return &ptr_ - &reduced.ptr;
    }  // необходимо убедиться, что с константными указателями тоже работает

   private:
    pointer_type ptr_;
  };

 public:
  vector &operator=(const vector &v) {
    if (*this != v) {
      if (capacity_ < v.capacity_) {
        capacity_ = v.capacity_;
        delete[] arr_;
        arr_ = new int[capacity_];
      }
      size_ = v.size_;
      for (size_type index = 0; index < size_; ++index) {
        arr_[index] = v.arr_[index];
      }
    }
    return *this;
  }

  vector &operator=(std::initializer_list<value_type> ilist) {
    size_type count = 0;
    size_ = ilist.size();
    arr_ == nullptr ? arr_ = new value_type[capacity_]() : arr_;
    for (auto first = ilist.begin(); first != ilist.end(); ++first) {
      arr_[count++] = *first;
    }
    return *this;
  }

  bool operator!=(vector const &v) { return &(*this) != &(v); }

 public:
  using iterator = v_iterator<false>;
  using const_iterator = v_iterator<true>;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;
  iterator begin() { return (arr_); }
  iterator end() { return (arr_ + size_); }
  const_iterator begin() const { return (arr_); }
  const_iterator end() const { return (arr_ + size_); }
  const_iterator cbegin() const { return (arr_); }
  const_iterator cend() const { return (arr_ + size_); }

  // основные публичные методы для взаимодействия с классом

  vector() noexcept : capacity_(0), size_(0), arr_(nullptr) {}

  vector(size_type size, const value_type &value)
      : capacity_(size), size_(size) {
    arr_ = new T[capacity_]();
    for (size_type index = 0; index < size; ++index) {
      arr_[index] = value;
    }
  }

  explicit vector(size_type size) { *this = vector(size, 0); }

  vector(std::initializer_list<value_type> const &items)
      : capacity_(items.size()), size_(capacity_), arr_(nullptr) {
    *this = items;
  }

  vector(vector const &v)
      : capacity_(v.capacity_), size_(v.size_), arr_(nullptr) {
    size_type count = 0;
    if (capacity_ > 0) arr_ = new value_type[capacity_]();
    for (auto elem : v) arr_[count++] = elem;
  }

  vector(vector &&v) noexcept { *this = std::move(v); };

  vector(iterator first, iterator last) {
    auto count = 0;
    iterator tmp = first;
    for (; tmp != last; ++tmp) {
      ++count;
    }
    capacity_ = count;
    size_ = count;
    arr_ = new value_type[capacity_]();
    for (auto index = 0; index < size_; ++index, ++first) {
      arr_[index] = *first;
    }
  }

  ~vector() {
    delete[] arr_;
    arr_ = nullptr;
    capacity_ = 0;
    size_ = 0;
  }

  vector &operator=(vector &&v) noexcept {
    capacity_ = v.capacity_;
    size_ = v.size_;
    arr_ = v.arr_;
    v.capacity_ = 0;
    v.size_ = 0;
    v.arr_ = nullptr;
    return *this;
  };

  //  публичные методы для доступа к элементам класса
  reference at(size_type pos) {
    if (pos >= size_ || pos < 0)
      throw std::out_of_range(
          "Требуемая позиция находится вне определенного вектора!\n");
    return arr_[pos];
  }

  reference operator[](size_type pos) { return &arr_; }
  const_reference back() { return arr_[size_ - 1]; }
  const_reference front() { return arr_[0]; }
  T *data() { return arr_; }

  //  публичные методы для доступа к информации о наполнении контейнера
  bool empty() { return size_ == 0; }
  size_type size() { return size_; }
  size_type max_size() {
    return std::numeric_limits<std::size_t>::max() / sizeof(value_type) / 2;
  }

  value_type *get() { return arr_; }

  void reserve(size_type size) {
    if (size > capacity_) {
      value_type *tmp = arr_;
      capacity_ = size * 2;
      arr_ = new value_type[capacity_];
      for (size_type index = 0; index < size_; ++index) {
        arr_[index] = tmp[index];
      }
      delete[] tmp;
    }
  }

  size_type capacity() { return capacity_; }

  void shrink_to_fit() {
    if (capacity_ > size_) {
      value_type *tmp = arr_;
      capacity_ = size_;
      arr_ = new value_type[capacity_];
      for (size_type index = 0; index < size_; ++index) {
        arr_[index] = tmp[index];
      }
      delete[] tmp;
    }
  }

  //  публичные методы для изменения контейнера
  void clear() {
    size_ = 0;
    delete[] arr_;
    arr_ = nullptr;
  }

  iterator insert(iterator pos, const_reference value) {
    if (pos.get_ptr() == end().get_ptr()) {
      push_back(value);
    } else {
      vector tmp_end = vector(pos, end());
      *pos.get_ptr() = value;
      for (iterator end = begin() + size_ - 1; end != pos; --end) pop_back();
      for (auto start = tmp_end.begin(); start != tmp_end.end(); ++start) {
        push_back(*start);
      }
    }
    return pos;
  }

  void erase(iterator pos) {
    for (auto elem = pos; elem != end(); ++elem) {
      if (*elem.get_ptr() != back()) {
        *elem.get_ptr() = std::move(*(elem.get_ptr() + 1));
      }
    }
    size_ -= 1;
  }

  void push_back(const_reference value) {
    size_type position = size_;
    reserve(size_ + 1);
    arr_[position] = value;
    if (position == size_) ++size_;
  }

  void pop_back() { erase(end() - 1); }

  void swap(vector &other) {
    vector tmp = std::move(other);
    other = std::move(*this);
    *this = std::move(tmp);
  }

  // бонусная часть
  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args) {
    size_type number_of_args = sizeof...(args);
    size_type position = pos.get_ptr() - cbegin().get_ptr();
    iterator start_insert = begin() + position;
    iterator to_return_it = start_insert;

    if (number_of_args > 0) {
      for (auto elem : {std::forward<Args>(args)...}) {
        insert(start_insert, elem);
        ++start_insert;
      }
    }

    return to_return_it;
  }

  template <typename... Args>
  void insert_many_back(Args &&...args) {
    if (sizeof...(args) > 0) {
      for (auto elem : {std::forward<Args>(args)...}) {
        push_back(elem);
      }
    }
  }

 private:
  size_type capacity_;
  size_type size_;
  value_type *arr_;
};
};  // namespace s21
