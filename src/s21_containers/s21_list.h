#ifndef SRC_S21_CONTAINERS_S21_LIST_H_
#define SRC_S21_CONTAINERS_S21_LIST_H_

namespace s21 {
template <typename T>
class list {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;

 private:
  // ******************************************** //
  struct Node {
    Node *prev_ = nullptr;  //??
    Node *next_ = nullptr;  //??
    T value_;
    Node() noexcept : prev_(this), next_(this), value_(value_type{}) {}

    explicit Node(const_reference value) noexcept
        : prev_(nullptr), next_(nullptr), value_(value) {}

    void join_node(Node *new_node) noexcept {
      new_node->prev_ = prev_;
      new_node->next_ = this;
      prev_->next_ = new_node;
      prev_ = new_node;
    }

    void unhook_node() noexcept {
      prev_->next_ = next_;
      next_->prev_ = prev_;
      prev_ = this;
      next_ = this;
    }

    void unhook_node_double(Node *insert_node) noexcept {
      prev_->next_ = next_;
      next_->prev_ = prev_;
      prev_ = insert_node->prev_;
      next_ = insert_node;
      prev_->next_ = this;
      next_->prev_ = this;
    }

    void swap_pointers() noexcept { std::swap(prev_, next_); }
  };

  // ******************************************** //
  template <bool IsConst>
  class base_iterator {
   public:
    using pointer_type = std::conditional_t<IsConst, const Node *, Node *>;
    using reference_type = std::conditional_t<IsConst, const T &, T &>;

   private:
    friend list;
    explicit base_iterator(Node *ptr) noexcept : ptr_(ptr) {}

   public:
    base_iterator() = delete;
    reference_type operator*() const { return ptr_->value_; }

    bool operator==(const base_iterator &rhv) { return ptr_ == rhv.ptr_; }

    bool operator!=(const base_iterator &rhv) { return !(*this == rhv); }

    base_iterator operator++() {
      ptr_ = ptr_->next_;
      return *this;
    }

    base_iterator operator++(int) {
      base_iterator copy(*this);
      ++*this;
      return copy;
    }

    base_iterator operator--() {
      ptr_ = ptr_->prev_;
      return *this;
    }

    base_iterator operator--(int) {
      base_iterator copy(*this);
      --*this;
      return copy;
    }

   private:
    pointer_type ptr_;
  };

 public:
  using iterator = base_iterator<false>;
  using const_iterator = base_iterator<true>;

  // ****************************************************************************
  // // публичные методы для итерирования по элементам класса (доступ к //
  // итераторам): //
  iterator begin() { return iterator{head_->next_}; }
  iterator end() { return iterator{head_}; }

  const_iterator begin() const { return const_iterator{head_->next_}; }
  const_iterator end() const { return const_iterator{head_}; }

  const_iterator cbegin() const { return const_iterator{head_->next_}; }
  const_iterator cend() const { return const_iterator{head_}; }

  // ******************************************************* //
  // основные публичные методы для взаимодействия с классом: //
  list() : head_(new Node()), size_(0) {}

  explicit list(size_type size) : list() {
    while (size) {
      push_back(value_type{});
      size -= 1;
    }
  }

  explicit list(std::initializer_list<value_type> const &items) : list() {
    for (auto item : items) {
      push_back(item);
    }
  }

  explicit list(const list &other) : list() {
    for (auto item : other) {
      push_back(item);
    }
  }

  explicit list(list &&other) noexcept : list() { splice(cbegin(), other); }

  ~list() {
    while (size_) {
      erase(begin());
    }
    delete head_;
    head_ = nullptr;
  }

  list &operator=(list &&other) noexcept {
    if (this != &other) {
      clear();
      this->splice(cbegin(), other);
    }
    return *this;
  }

  list &operator=(const list &other) {
    if (this != &other) {
      list copy_object(other);
      *this = std::move(copy_object);
    }
    return *this;
  }

  // ******************************************************* //
  //     публичные методы для доступа к элементам класса     //

  const_reference front() { return *cbegin(); }

  const_reference back() { return *--cend(); }

  // ****************************************************************** //
  // публичные методы для доступа к информации о наполнении контейнера: //
  bool empty() { return size_ == 0; }

  size_type size() { return size_; }

  size_type max_size() const noexcept {
    return ((std::numeric_limits<size_type>::max()) / sizeof(Node));
  }

  // ****************************************** //
  // публичные методы для изменения контейнера: //
  void clear() {
    while (size_) {
      erase(begin());
    }
  }

  iterator insert(iterator position, const_reference value) {
    Node *new_node = new Node{value};
    position.ptr_->join_node(new_node);
    size_ += 1;
    return iterator{new_node};
  }

  iterator insert(const_iterator position, const_reference value) {
    Node *new_node = new Node{value};
    position.ptr_->join_node(new_node);
    size_ += 1;
    return iterator{new_node};
  }
  void erase(iterator position) {
    if (!empty()) {
      position.ptr_->unhook_node();
      delete position.ptr_;
      size_ -= 1;
    }
  }

  void push_back(const_reference value) { insert(end(), value); }

  void pop_back() { erase(--end()); }

  void push_front(const_reference value) { insert(begin(), value); }

  void pop_front() { erase(begin()); }

  void swap(list &other) noexcept {
    if (this != &other) {
      // it = end()  будет указывать на этот же список
      // но значения будут из другого списка
      iterator this_b = begin();
      iterator other_b = other.begin();
      iterator this_e = end();
      iterator other_e = other.end();
      this_e.ptr_->unhook_node();
      other_e.ptr_->unhook_node();
      other_b.ptr_->join_node(this_e.ptr_);
      this_b.ptr_->join_node(other_e.ptr_);
      // it = end()  будет указывать на другой список
      // std::swap(head_, other.head_); invalid.. iterator???
      std::swap(size_, other.size_);
    }
  }

  void merge(list &other) {
    if (this != &other) {
      iterator this_it = begin();
      iterator other_it = other.begin();
      while (this_it != end() && other_it != other.end()) {
        if (*other_it < *this_it) {
          iterator other_it_copy = other_it;
          ++other_it_copy;
          other_it.ptr_->unhook_node();
          this_it.ptr_->join_node(other_it.ptr_);
          other.size_ -= 1;
          other_it = other_it_copy;
          size_ += 1;
        } else {
          ++this_it;
        }
      }
      splice(cend(), other);
      other.head_->next_ = other.head_;
      other.head_->prev_ = other.head_;
    }
  }

  void splice(const_iterator position, list &other) {
    if (other.size()) {
      iterator this_position(const_cast<Node *>(position.ptr_));
      iterator other_position = other.end();
      other_position.ptr_->next_->prev_ = this_position.ptr_->prev_;
      other_position.ptr_->prev_->next_ = this_position.ptr_;
      this_position.ptr_->prev_->next_ = other.head_->next_;
      this_position.ptr_->prev_ = other.head_->prev_;
      size_ += other.size();
      other.size_ = 0;
      other.head_->next_ = other.head_;
      other.head_->prev_ = other.head_;
    }
  }

  void reverse() noexcept {
    iterator begin_it = begin();
    while (begin_it != end()) {
      begin_it.ptr_->swap_pointers();
      --begin_it;
    }
    head_->swap_pointers();
  }

  void unique() {
    iterator prev_it = begin();
    iterator current_it = ++begin();
    while (current_it != end()) {
      if (*prev_it == *current_it) {
        erase(current_it);
        current_it = prev_it;
        ++current_it;
      } else {
        ++prev_it;
        ++current_it;
      }
    }
  }

  void sort() {
    iterator current_it = begin();
    iterator cur = ++begin();
    iterator prev = begin();
    while (cur != end()) {
      if (*cur < *prev) {
        iterator position = find_min_object(cur);
        current_it = cur;
        ++current_it;
        cur.ptr_->unhook_node_double(position.ptr_);
        cur = current_it;
      } else {
        ++cur;
        ++prev;
      }
    }
  }

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args) {
    iterator next_position{const_cast<Node *>(pos.ptr_)};
    Node *prev_first_inserted_elem = next_position.ptr_->prev_;
    // Node* сurrent_node_for_join = next_position.ptr_->prev_;
    for (auto item : {std::forward<Args>(args)...}) {
      next_position = insert(next_position, std::move(item));
      ++next_position;
      // Node *new_node = new Node{std::move(item)};
      // сurrent_node_for_join->next_->join_node(new_node);
      // сurrent_node_for_join = сurrent_node_for_join->next_;
    }
    return iterator{prev_first_inserted_elem->next_};
  }
  template <typename... Args>
  void insert_many_back(Args &&...args) {
    for (auto item : {std::forward<Args>(args)...}) {
      // Node *new_node = new Node{std::move(item)};
      insert(end(), std::move(item));
    }
  }

  template <typename... Args>
  void insert_many_front(Args &&...args) {
    for (auto item : {std::forward<Args>(args)...}) {
      // Node *new_node = new Node{std::move(item)};
      insert(begin(), std::move(item));
    }
  }

 private:
  iterator find_min_object(iterator begin_it) {
    iterator curr = begin_it;
    --curr;
    while (*begin_it < *curr && curr != end()) {
      --curr;
    }
    return ++curr;
  }

  // *************************************************** //
 private:
  Node *head_ = nullptr;
  size_type size_ = 0U;
};

}  // namespace s21

#endif  // SRC_S21_CONTAINERS_S21_LIST_H_