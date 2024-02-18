#ifndef S21_CONTAINERS_S21_CONTAINERS_S21_RB_TREE_H_
#define S21_CONTAINERS_S21_CONTAINERS_S21_RB_TREE_H_
#include <functional>
#include <iostream>
#include <utility>
#include <vector>
namespace s21 {

enum NodeColor : bool { Red, Black };
enum NamePointer : std::int8_t { left, right, parent };

//// BASE NODE
template <typename Key>
struct BaseNode {
  bool color_;
  BaseNode *link_[3];  // ?заменить??
  BaseNode() {
    color_ = Red;
    link_[left] = nullptr;
    link_[right] = nullptr;
    link_[parent] = nullptr;
  }
  virtual ~BaseNode() {}  // ????   !!!!!!!!!!!!!!!!!!!!!
};

//// NODE
template <typename Key>
struct Node : public BaseNode<Key> {
  using value_type = Key;
  using reference = Key &;
  using const_reference = const Key &;
  using color_type = bool;
  using base_node = BaseNode<value_type>;
  value_type key_;
  Node() = delete;
  explicit Node(const_reference key) : base_node(), key_(key) {}
  Node(color_type color, const_reference key) : key_(key) {
    base_node::color_ = color;
  }
  explicit Node(value_type &&key) : key_(std::move(key)) {}
};

/////ITERATOR
template <typename Key, bool IsConst>
class RBTreeIterator {
 public:
  using pointer_type = std::conditional_t<IsConst, const Key *, Key *>;
  using value_type = Key;
  using value_type_pointer = value_type *;
  using reference =
      std::conditional_t<IsConst, const value_type &, value_type &>;
  using base_node = std::conditional_t<IsConst, const BaseNode<value_type> *,
                                       BaseNode<value_type> *>;
  using node =
      std::conditional_t<IsConst, const Node<value_type> *, Node<value_type> *>;
  using difference_type = ptrdiff_t;
  friend class RBTreeIterator<Key, true>;

 private:
  base_node ptr_;

 private:
  template <typename, typename>
  friend class RBTree;

  bool is_not_nil_(const base_node ptr) { return (ptr->link_[right]) != (ptr); }

  bool parent_left_child(const base_node ptr) {
    return (ptr->link_[parent]->link_[left]) == (ptr);
  }

  bool parent_right_child(const base_node ptr) {
    return (ptr->link_[parent]->link_[right]) == (ptr);
  }

  bool is_head_or_root(const base_node ptr) {
    return (ptr == ptr->link_[parent]->link_[parent]);
  }

 public:
  explicit RBTreeIterator(const base_node ptr) : ptr_(ptr) {}
  //   explicit RBTreeIterator(const base_node ptr) : ptr_(ptr) {}
  reference operator*() const { return static_cast<node>(ptr_)->key_; }

  value_type_pointer operator->() const {
    return &static_cast<node>(ptr_)->key_;
  }

  bool operator==(const RBTreeIterator &rhv) { return ptr_ == rhv.ptr_; }
  bool operator==(const RBTreeIterator &rhv) const { return ptr_ == rhv.ptr_; }

  bool operator!=(const RBTreeIterator &rhv) { return ptr_ != rhv.ptr_; }

  RBTreeIterator &operator++() {
    if (is_head_or_root(ptr_) && ptr_->color_ == Red) {
      ptr_ = ptr_->link_[left];
    } else if (is_not_nil_((this->ptr_->link_[right]))) {
      ptr_ = ptr_->link_[right];
      while (is_not_nil_((this->ptr_->link_[left]))) {
        ptr_ = ptr_->link_[left];
      }
    } else if (is_not_nil_(this->ptr_)) {
      while ((!is_head_or_root(ptr_)) && !parent_left_child(this->ptr_)) {
        ptr_ = ptr_->link_[parent];
      }
      if (is_not_nil_(this->ptr_)) {
        ptr_ = ptr_->link_[parent];
      }
    }
    return *this;
  }

  RBTreeIterator &operator--() {
    if (ptr_ == ptr_->link_[parent]->link_[parent] && ptr_->color_ == Red) {
      ptr_ = ptr_->link_[right];
    } else if (is_not_nil_((this->ptr_->link_[left]))) {
      ptr_ = ptr_->link_[left];
      while (is_not_nil_((this->ptr_->link_[right]))) {
        ptr_ = ptr_->link_[right];
      }
    } else if (is_not_nil_(this->ptr_)) {
      while ((ptr_ != (ptr_->link_[parent]->link_[parent])) &&
             !parent_right_child(this->ptr_)) {
        ptr_ = ptr_->link_[parent];
      }
      if (is_not_nil_(this->ptr_)) {
        ptr_ = ptr_->link_[parent];
      }
    }
    return *this;
  }

  RBTreeIterator operator++(int) {
    const RBTreeIterator copy_this = *this;
    ++(*this);
    return copy_this;
  }

  RBTreeIterator operator--(int) {
    const RBTreeIterator copy_this = *this;
    --(*this);
    return copy_this;
  }
};

///////// RBTREE
template <typename Key, typename Comp = std::less<Key>>
class RBTree {
  // private:
  // class RBTreeIterator<Key, IsConst>;
 public:
  using value_type = Key;
  using reference = Key &;
  using const_reference = const Key &;
  using base_node = BaseNode<value_type>;
  using node = Node<Key>;
  using iterator = RBTreeIterator<value_type, false>;
  using const_iterator = RBTreeIterator<value_type, true>;
  using tree_type = RBTree;
  using tree_type_reference = RBTree &;
  using const_tree_type_reference = const RBTree &;
  using pair_iterator_bool = std::pair<iterator, bool>;
  using size_type = std::size_t;

 public:
  // конструктор по умолчанию
  RBTree() : head_(new base_node{}), nil_(new base_node{}) {
    head_->link_[left] = head_;
    head_->link_[right] = head_;
    head_->link_[parent] = head_;
    nil_->link_[left] = nil_;
    nil_->link_[right] = nil_;
    nil_->link_[parent] = nil_;
    head_->color_ = Red;
    nil_->color_ = Black;
    size_ = 0;
  }

  // конструктор
  explicit RBTree(value_type key) : RBTree() {
    node *new_node = new node{key};
    this->CreateRoot(new_node);
  }

  // конструктор копирования
  RBTree(const_tree_type_reference other) : RBTree() {
    if (other.size_ > 0) {
      this->CopyOtherTree(other);
    }
  }

  // конструктор перемещения
  RBTree(tree_type &&other) noexcept : RBTree() { this->Swap(other); }

  // деструктор
  ~RBTree() {
    this->Clear();
    delete head_;
    delete nil_;
    head_ = nullptr;
    nil_ = nullptr;
  }

  // оператор присваивания копированием
  tree_type_reference operator=(const_tree_type_reference other) {
    if (this != &other) {
      tree_type copy{other};
      this->Clear();
      *this = std::move(copy);
    }
    return *this;
  }

  // оператор присваивания перемещением
  tree_type_reference operator=(tree_type &&other) {
    if (this != &other) {
      this->Clear();
      this->Swap(other);
    }
    return *this;
  }

  iterator Begin() { return iterator{head_->link_[left]}; }
  iterator End() { return iterator{head_}; }
  iterator begin() { return iterator{head_->link_[left]}; }
  iterator end() { return iterator{head_}; }
  const_iterator Begin() const { return const_iterator{head_->link_[left]}; }
  const_iterator End() const { return const_iterator{head_}; }

  const_iterator Cend() const { return const_iterator{head_}; }
  const_iterator Cbegin() const { return const_iterator{head_->link_[left]}; }

  pair_iterator_bool InsertUnique(const value_type &key) {
    pair_iterator_bool status{Find(key), false};
    if (head_->link_[parent] == head_) {
      node *new_node = new node{std::move(key)};
      CreateRoot(new_node);
      status = {iterator{head_->link_[parent]}, true};
    } else if (status.first == End()) {
      node *new_node = new node{key};
      status = Insert((head_->link_[parent]), new_node, true);
    }
    return status;
  }

  pair_iterator_bool InsertUnique(value_type &&key) {
    pair_iterator_bool status{Find(key), false};
    if (head_->link_[parent] == head_) {
      node *new_node = new node{std::move(key)};
      CreateRoot(new_node);
      status = {iterator{head_->link_[parent]}, true};
    } else if (status.first == End()) {
      node *new_node = new node{std::move(key)};
      status = Insert((head_->link_[parent]), new_node, true);
    }
    return status;
  }

  pair_iterator_bool Insert(const value_type &key) {
    pair_iterator_bool status{iterator{head_}, false};
    if (head_->link_[parent] == head_) {
      node *new_node = new node{key};
      CreateRoot(new_node);
      status = {iterator{head_->link_[parent]}, true};
    } else {
      node *new_node = new node{key};
      status = Insert((head_->link_[parent]), new_node, false);
      if (status.second == false) {
        delete new_node;
      }
    }
    return status;
  }

  void Erase(iterator position) {
    node *node_del = EraseNode(position, true);
    if (node_del != nullptr) {
      delete node_del;
    }
    if (head_->link_[parent] != head_) {
      // #if defined(S21_TEST_CONTAINERS_H_)
      //       CheckRedBlackTreeValidation(head_->link_[parent]);
      // #endif
    }
  }

  void Erase(const_reference key) {
    iterator position = Find(key);
    if (position.ptr_ != nil_ && position.ptr_ != head_) {
      node *node_del = EraseNode(position, true);
      delete node_del;
    }
    if (head_->link_[parent] != head_) {
      //////// TEST RBTREE
      // #if defined(S21_TEST_CONTAINERS_H_)
      //       CheckRedBlackTreeValidation(head_->link_[parent]);
      // #endif
      ////////
    }
  }

  iterator Find(const_reference key) {
    base_node *current = head_->link_[parent];
    base_node *result = head_;
    while (current != nil_ && current != head_) {
      if (!comp_(static_cast<node *>(current)->key_, key) &&
          !comp_(key, static_cast<node *>(current)->key_)) {
        result = current;
        current = nil_;
      } else if (!comp_(static_cast<node *>(current)->key_, key)) {
        current = current->link_[left];
      } else {
        current = current->link_[right];
      }
    }
    return iterator{result};
  }

  size_type Size() { return size_; }

  size_type MaxSize() const noexcept {
    return (std::numeric_limits<size_type>::max()) / (sizeof(tree_type));
  }

  bool Empty() const noexcept { return size_ == 0; }

  iterator UpperBound(const_reference key) const noexcept {
    base_node *root = head_->link_[parent];
    base_node *result = head_;
    while (root != nil_ && root != head_) {
      if (comp_(key, static_cast<node *>(root)->key_)) {
        result = root;
        root = root->link_[left];
      } else
        root = root->link_[right];
    }
    return iterator(result);
  }

  iterator LowerBound(const_reference key) const noexcept {
    base_node *root = head_->link_[parent];
    base_node *result = head_;
    while (root != nil_ && root != head_) {
      if (!comp_(static_cast<node *>(root)->key_, key)) {
        result = root;
        root = root->link_[left];
      } else
        root = root->link_[right];
    }
    return iterator(result);
  }

  std::pair<iterator, iterator> EqualRange(const_reference key) const noexcept {
    return {LowerBound(key), UpperBound(key)};
  }

  size_type Count(const_reference key) const noexcept {
    size_type count = 0;
    iterator root{head_->link_[left]};
    while (root.ptr_ != head_) {
      if (!comp_(static_cast<node *>(root.ptr_)->key_, key) &&
          !comp_(key, static_cast<node *>(root.ptr_)->key_)) {
        count += 1;
      } else if (comp_(key, static_cast<node *>(root.ptr_)->key_)) {
        return count;
      }
      ++root;
    }
    return count;
  }

  // дерево other должно оставаться корректным, так как узлы, c ключом имеющимся
  // в this, не извлекаются
  void MergeUnique(tree_type &other) noexcept {
    if (this != &other) {
      iterator other_current{other.head_->link_[left]};
      iterator other_end{other.head_};

      while (other_current != other_end && other.Size()) {
        if (Find(static_cast<node *>(other_current.ptr_)->key_) == End()) {
          iterator tmp = other_current;
          ++other_current;
          node *extracted_node = other.EraseNode(tmp, true);
          Insert(head_->link_[parent], extracted_node, true);
        } else {
          ++other_current;
        }
      }
    }
  }

  // рабочий, но медленный вариант в будущем переписать без балансировки при
  // удалении
  void Merge(tree_type &other) noexcept {
    if (this != &other) {
      iterator other_current{other.head_->link_[left]};
      iterator other_end{other.head_};
      while (other.Size()) {
        node *extracted_node = other.EraseNode(other.Begin(), true);
        Insert(head_->link_[parent], extracted_node, false);
        ++other_current;
      }
    }
  }

  void Clear() {
    if (head_) {
      Destroy(head_->link_[parent]);
      head_->link_[left] = head_;
      head_->link_[right] = head_;
      head_->link_[parent] = head_;
      size_ = 0;
    }
  }

  void Swap(tree_type &other) noexcept {
    std::swap(head_, other.head_);
    std::swap(nil_, other.nil_);
    std::swap(size_, other.size_);
    std::swap(comp_, other.comp_);
  }

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> InsertManyUnique(Args &&...args) {
    std::vector<std::pair<iterator, bool>> vector_tree;
    vector_tree.reserve(sizeof...(args));
    for (auto item : {std::forward<Args>(args)...}) {
      if (Find(item) == End()) {
        node *new_node = new node{std::move(item)};
        auto [it, status] = Insert(head_->link_[parent], new_node, true);
        if (status == true) {
          vector_tree.push_back({it, status});
        } else {
          delete new_node;
          new_node = nullptr;
        }
      }
    }
    //////// TEST RBTREE
    // #if defined(S21_TEST_CONTAINERS_H_)
    //     CheckRedBlackTreeValidation(head_->link_[parent]);
    // #endif
    ////////
    return vector_tree;
  }

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> InsertMany(Args &&...args) {
    std::vector<std::pair<iterator, bool>> vector_tree;
    vector_tree.reserve(sizeof...(args));
    for (auto item : {std::forward<Args>(args)...}) {
      node *new_node = new node{std::move(item)};
      auto [it, status] = Insert(head_->link_[parent], new_node, false);
      if (status == true) {
        vector_tree.push_back({it, status});
      } else {
        delete new_node;
        new_node = nullptr;
      }
    }
    //////// TEST RBTREE
    // #if defined(S21_TEST_CONTAINERS_H_)
    //     CheckRedBlackTreeValidation(head_->link_[parent]);
    // #endif
    ////////
    return vector_tree;
  }

 private:
  base_node *&Root() noexcept { return head_->link_[parent]; }

  void CopyOtherTree(const_tree_type_reference other) {
    if (other.head_->link_[parent] != other.head_) {
      base_node *future_root =
          CreateCopyTree(other.head_->link_[parent], head_, other.nil_);
      Clear();
      head_->link_[parent] = future_root;
      future_root->link_[parent] = head_;
      size_ = other.size_;
      comp_ = other.comp_;
      head_->link_[left] = FindMinElement(Root());
      head_->link_[right] = FindMaxElement(Root());
    }
    //////// TEST RBTREE
    // #if defined(S21_TEST_CONTAINERS_H_)
    //     CheckRedBlackTreeValidation(head_->link_[parent]);
    // #endif
    ////////
  }

  base_node *CreateCopyTree(base_node *this_node, base_node *parent_n,
                            base_node *nil) {
    base_node *copy_node =
        new node{this_node->color_, static_cast<node *>(this_node)->key_};
    iterator min{this_node};
    try {
      if (this_node->link_[right] != nil) {
        copy_node->link_[right] =
            CreateCopyTree(this_node->link_[right], copy_node, nil);
      } else {
        copy_node->link_[right] = nil_;
      }
      if (this_node->link_[left] != nil) {
        copy_node->link_[left] =
            CreateCopyTree(this_node->link_[left], copy_node, nil);
      } else {
        copy_node->link_[left] = nil_;
      }
    } catch (...) {
      Destroy(copy_node);
      throw;
      ;
    }
    copy_node->link_[parent] = parent_n;
    return copy_node;
  }

  void CreateRoot(node *new_node) noexcept {
    head_->link_[left] = new_node;
    head_->link_[right] = new_node;
    head_->link_[parent] = new_node;
    new_node->link_[left] = nil_;
    new_node->link_[right] = nil_;
    new_node->link_[parent] = head_;
    new_node->color_ = Black;
    size_ += 1;
  }

  void Destroy(base_node *node_del) noexcept {
    if (node_del != head_ && node_del != nil_) {
      Destroy(node_del->link_[left]);
      Destroy(node_del->link_[right]);
      delete node_del;
    }
  }

  node *FindInsertPosition(node *new_node, bool unique_el) noexcept {
    node *next_node = static_cast<node *>(head_->link_[parent]);
    node *this_node = next_node;
    while (next_node != nil_) {
      this_node = next_node;
      if (comp_(new_node->key_, next_node->key_)) {
        next_node = static_cast<node *>(next_node->link_[left]);
      } else {
        if (unique_el == false) {
          next_node = static_cast<node *>(next_node->link_[right]);
        } else {
          //   if (comp_(next_node->key_, new_node->key_)) {
          next_node = static_cast<node *>(next_node->link_[right]);
          //   } else {
          // std::cerr << "Запрещена вставка неуникальных ключей\n";
          // std::cerr << "Ключ со значением " << new_node->key_
          //           << " уже есть в дереве\n\n";
          // return nullptr;
          //   }
        }
      }
    }
    return this_node;
  }

  std::pair<iterator, bool> Insert(base_node *root, node *new_node,
                                   bool unique_el) {
    if (root == head_) {
      InsertRoot(new_node);
    } else {
      node *parent_node = FindInsertPosition(new_node, unique_el);
      //   if (parent_node == nullptr) {
      //     // ошибка, попытка вставить узел с ключом который уже усть в дереве
      //     return {iterator(head_), false};
      //   }
      new_node->link_[parent] = parent_node;
      if (comp_(new_node->key_, parent_node->key_)) {
        parent_node->link_[left] = new_node;
      } else {
        parent_node->link_[right] = new_node;
      }
      new_node->color_ = Red;
      new_node->link_[left] = nil_;
      new_node->link_[right] = nil_;
      if (comp_(new_node->key_,
                static_cast<node *>(head_->link_[left])->key_)) {
        head_->link_[left] = new_node;
      }
      if (!comp_(new_node->key_,
                 static_cast<node *>(head_->link_[right])->key_)) {
        head_->link_[right] = new_node;
      }
      if (parent_node->color_ == Red) {
        BalancingDuringInsertion(new_node);
      }
    }
    size_ += 1;
    //////// TEST RBTREE
    // #if defined(S21_TEST_CONTAINERS_H_)
    //     CheckRedBlackTreeValidation(head_->link_[parent]);
    // #endif
    ////////
    return {iterator(new_node), true};
  }

  void InsertRoot(base_node *new_node) noexcept {
    if (head_->link_[parent] == head_) {
      head_->link_[left] = new_node;
      head_->link_[right] = new_node;
      head_->link_[parent] = new_node;
      new_node->link_[parent] = head_;
      new_node->link_[left] = nil_;
      new_node->link_[right] = nil_;
      new_node->color_ = Black;
    }
  }

  size_type CheckRedBlackTreeValidation(base_node *root) {
    size_type left_depth = 0U;
    size_type right_depth = 0U;
    if (root == nil_ || root == head_)
      return 1;
    else {
      base_node *left_subtree = root->link_[left];
      base_node *right_subtree = root->link_[right];
      if (ThisNodeRed(root)) {
        if (ThisNodeRed(left_subtree) || ThisNodeRed(right_subtree)) {
          std::cerr << "\nКРАСНОЕ НАРУШЕНИЕ\n";
          throw "КРАСНОЕ НАРУШЕНИЕ";
          return 0;
        }
      }
      left_depth = CheckRedBlackTreeValidation(left_subtree);
      right_depth = CheckRedBlackTreeValidation(right_subtree);
      if ((left_subtree != nil_ &&
           comp_(static_cast<node *>(root)->key_,
                 static_cast<node *>(left_subtree)->key_)) ||
          (right_subtree != nil_ &&
           comp_(static_cast<node *>(right_subtree)->key_,
                 static_cast<node *>(root)->key_))) {
        std::cout << "\n\n\nБИНАРНОЕ НАРУШЕНИЕ\n\n\n";
        throw "БИНАРНОЕ НАРУШЕНИЕ";
        return 0;
      }
      if (left_depth != 0 && right_depth != 0 && left_depth != right_depth) {
        std::cerr << "\nЧЕРНОЕ НАРУШЕНИЕ\n";
        throw "ЧЕРНОЕ НАРУШЕНИЕ2";
        return 0;
      }
      if (left_depth != 0 && right_depth != 0)
        return ThisNodeRed(root) ? left_depth : left_depth + 1;
      else
        return 0;
    }
  }

  bool ThisNodeRed(base_node *root) noexcept {
    return root != nil_ && root->color_ == Red;
  }

  void BalancingDuringInsertion(base_node *new_node) noexcept {
    base_node *P = new_node->link_[parent];
    if (P == head_) {
      new_node->color_ = Black;
    } else if (new_node->color_ == Red && P->color_ == Red) {
      base_node *G = P->link_[parent];
      base_node *U = FindUncle(new_node);
      if (U->color_ == Black) {
        if (new_node == P->link_[right] && P == G->link_[right]) {
          // "Право-Право \n";
          RotateLeft(P);
        } else if (new_node == P->link_[right] && P == G->link_[left]) {
          // "Право-Лево \n";
          RotateLeft(new_node);
          P = new_node->link_[left];
          BalancingDuringInsertion(P);
        } else if (new_node == P->link_[left] && P == G->link_[left]) {
          // "Лево-Лево \n";
          RotateRight(P);
        } else if (new_node == P->link_[left] && P == G->link_[right]) {
          // "Лево-Право \n";
          RotateRight(new_node);
          P = new_node->link_[right];
          BalancingDuringInsertion(P);
        }
      } else {
        U->color_ = P->color_ = Black;
        G->color_ = Red;
        BalancingDuringInsertion(G);
      }
    }
  }

  void BalancingDuringErase(base_node *del_node) noexcept {
    base_node *P = del_node->link_[parent];
    base_node *B = FindBrother(del_node);
    // разбить код на процедуры
    if (P->color_ == Red && P != head_) {
      if (B == P->link_[right]) {
        if (B->link_[right]->color_ == Red) {
          RotateLeft(B);
          B->link_[right]->color_ = Black;
        } else if (B->link_[left]->color_ == Red) {
          RotateRight(B->link_[left]);
          RotateLeft(P->link_[right]);
          B->color_ = Black;
        } else {
          B->color_ = Red;
          P->color_ = Black;
        }

      } else if (B == P->link_[left]) {
        if (B->link_[left]->color_ == Red) {
          RotateRight(B);
          B->link_[left]->color_ = Black;
        } else if (B->link_[right]->color_ == Red) {
          RotateLeft(B->link_[right]);
          RotateRight(P->link_[left]);
          B->color_ = Black;
        } else {
          B->color_ = Red;
          P->color_ = Black;
        }
      }
    } else if (P->color_ == Black) {
      base_node *NR = B->link_[right];
      base_node *NL = B->link_[left];
      if (B == P->link_[right]) {
        if (B->color_ == Red) {
          RotateLeft(B);
          BalancingDuringErase(del_node);
        } else if (B->color_ == Black) {
          if (NR->color_ == Black && NL->color_ == Black) {
            B->color_ = Red;
            BalancingDuringErase(P);
          } else if (NR->color_ == Red) {
            RotateLeft(B);
            NR->color_ = Black;
          } else if (NL->color_ == Red) {
            RotateRight(NL);
            RotateLeft(NL);
            B->color_ = Black;
          }
        }
      } else if (B == P->link_[left]) {
        if (B->color_ == Red) {
          RotateRight(B);
          BalancingDuringErase(del_node);
        } else if (B->color_ == Black) {
          if (NR->color_ == Black && NL->color_ == Black) {
            B->color_ = Red;
            BalancingDuringErase(P);
          } else if (NL->color_ == Red) {
            RotateRight(B);
            NL->color_ = Black;
          } else if (NR->color_ == Red) {
            RotateLeft(NR);
            RotateRight(NR);
            B->color_ = Black;
          }
        }
      }
    }
  }

  void SwapNeighboringNodes(base_node *del_node,
                            base_node *successor) noexcept {
    // меняем указатели на родителей del_node и successor
    successor->link_[parent] = del_node->link_[parent];
    del_node->link_[parent] = successor;

    // если преемник правый ребенок удаляемого узела
    if (successor == del_node->link_[right]) {
      del_node->link_[right] = successor->link_[right];
      successor->link_[right] = del_node;
      std::swap(del_node->link_[left], successor->link_[left]);
      if (del_node->link_[right] != nil_) {
        del_node->link_[right]->link_[parent] = del_node;
      }
      if (del_node->link_[left] != nil_) {
        del_node->link_[left]->link_[parent] = del_node;
      }
      if (successor->link_[left] != nil_) {
        successor->link_[left]->link_[parent] = successor;
      }
      // если преемник левый ребенок удаляемого узела
    } else if (successor == del_node->link_[left]) {
      del_node->link_[left] = successor->link_[left];
      successor->link_[left] = del_node;
      std::swap(del_node->link_[right], successor->link_[right]);
      if (del_node->link_[left] != nil_) {
        del_node->link_[left]->link_[parent] = del_node;
      }
      if (del_node->link_[right] != nil_) {
        del_node->link_[right]->link_[parent] = del_node;
      }
      if (successor->link_[right] != nil_) {
        successor->link_[right]->link_[parent] = successor;
      }
    }

    // устанавливаем обратную связь с родителем successor
    if (del_node == successor->link_[parent]->link_[left]) {
      successor->link_[parent]->link_[left] = successor;
    } else if (del_node == successor->link_[parent]->link_[right]) {
      successor->link_[parent]->link_[right] = successor;
    } else if (del_node == successor->link_[parent]->link_[parent]) {
      successor->link_[parent]->link_[parent] = successor;
    }

    // обмениваем цвета
    std::swap(del_node->color_, successor->color_);
  }

  void SwapEraseNode(base_node *del_node, base_node *successor) noexcept {
    base_node *parent_d = del_node->link_[parent];
    base_node *parent_s = successor->link_[parent];

    // если узлы связаны
    if (del_node == parent_s) {
      SwapNeighboringNodes(del_node, successor);

      // если узлы находятся в разных местах дерева
    } else {
      if (parent_s->link_[left] == successor) {
        parent_s->link_[left] = del_node;
      } else if (parent_s->link_[right] == successor) {
        parent_s->link_[right] = del_node;
      }

      if (parent_d->link_[left] == del_node) {
        parent_d->link_[left] = successor;
      } else if (parent_d->link_[right] == del_node) {
        parent_d->link_[right] = successor;
      } else if (parent_d->link_[parent] == del_node) {
        parent_d->link_[parent] = successor;
      }

      // обмениваем указатели на узлы и цвет
      std::swap(del_node->link_[parent], successor->link_[parent]);
      std::swap(del_node->link_[left], successor->link_[left]);
      std::swap(del_node->link_[right], successor->link_[right]);
      std::swap(del_node->color_, successor->color_);

      // связываем детей с родителями
      if (del_node->link_[left] != nil_) {
        del_node->link_[left]->link_[parent] = del_node;
      }
      if (del_node->link_[right] != nil_) {
        del_node->link_[right]->link_[parent] = del_node;
      }
      if (successor->link_[left] != nil_) {
        successor->link_[left]->link_[parent] = successor;
      }
      if (successor->link_[right] != nil_) {
        successor->link_[right]->link_[parent] = successor;
      }
    }
  }

  node *EraseNode(iterator position_del, bool balance) {
    base_node *del_node = position_del.ptr_;
    if (position_del.ptr_ == head_) {
      return nullptr;
    }

    // если удаляется самый левый или правый элемент
    UpdateMinMaxTreeElements(del_node);

    // если  у узла два наследника
    if (del_node->link_[left] != nil_ && del_node->link_[right] != nil_) {
      ErasingWithTwoHeirs(del_node);
    }

    // если у узла есть один наследник
    if (del_node->link_[left] != nil_ || del_node->link_[right] != nil_) {
      ErasingWithOneHeirs(del_node);
    }
    // если узел  без наследников
    if (del_node->link_[left] == nil_ && del_node->link_[right] == nil_) {
      ErasingNodeWithoutHeirs(del_node, balance);
    }
    return static_cast<node *>(del_node);
  }

  void UpdateMinMaxTreeElements(base_node *del_node) noexcept {
    // min element rntree Begin()
    if (del_node == head_->link_[left]) {
      if (del_node->link_[right] != nil_) {
        head_->link_[left] = del_node->link_[right];
      } else {
        head_->link_[left] = del_node->link_[parent];
      }
    }

    // max element rbtree ( --End() )
    if (del_node == head_->link_[right]) {
      if (del_node->link_[left] != nil_) {
        head_->link_[right] = del_node->link_[left];
      } else {
        head_->link_[right] = del_node->link_[parent];
      }
    }
  }
  void ErasingWithTwoHeirs(base_node *del_node) noexcept {
    base_node *min_element = FindMinElement(del_node->link_[right]);
    base_node *max_element = FindMaxElement(del_node->link_[left]);
    base_node *successor = min_element;
    if (max_element->color_ == Red) {
      successor = max_element;
    } else if (min_element->color_ != Red &&
               max_element->link_[left]->color_ == Red) {
      successor = max_element;
    }
    SwapEraseNode(del_node, successor);
  }

  void ErasingWithOneHeirs(base_node *del_node) noexcept {
    base_node *successor = del_node->link_[left];
    if (successor == nil_) {
      successor = del_node->link_[right];
    }
    SwapEraseNode(del_node, successor);
  }

  void ErasingNodeWithoutHeirs(base_node *del_node, bool balance) noexcept {
    if (del_node->color_ == Black && balance == true) {
      BalancingDuringErase(del_node);
    }
    if (del_node == del_node->link_[parent]->link_[right]) {
      del_node->link_[parent]->link_[right] = nil_;
    } else if (del_node == del_node->link_[parent]->link_[left]) {
      del_node->link_[parent]->link_[left] = nil_;
    } else if (del_node == head_->link_[parent]) {
      head_->link_[parent] = head_;
    }
    del_node->link_[parent] = nil_;
    size_ -= 1;
  }

  void RotateLeft(base_node *n) noexcept {
    base_node *P = n->link_[parent];
    base_node *G = P->link_[parent];
    if (G == head_) {
      G->link_[parent] = n;
    } else if (G->link_[left] == P) {
      G->link_[left] = n;
    } else if (G->link_[right] == P) {
      G->link_[right] = n;
    }
    n->link_[parent] = P->link_[parent];
    P->link_[parent] = n;
    P->link_[right] = n->link_[left];
    n->link_[left] = P;
    if (P->link_[right] != nil_) {
      P->link_[right]->link_[parent] = P;
    }
    std::swap(n->color_, P->color_);
  }

  void RotateRight(base_node *n) noexcept {
    base_node *P = n->link_[parent];
    base_node *G = P->link_[parent];
    if (G == head_) {
      G->link_[parent] = n;
    } else if (G->link_[left] == P) {
      G->link_[left] = n;
    } else if (G->link_[right] == P) {
      G->link_[right] = n;
    }
    n->link_[parent] = P->link_[parent];
    P->link_[parent] = n;
    P->link_[left] = n->link_[right];
    n->link_[right] = P;
    if (P->link_[left] != nil_) {
      P->link_[left]->link_[parent] = P;
    }
    std::swap(n->color_, P->color_);
  }

  base_node *FindMinElement(base_node *current_node) {
    while (current_node->link_[left] != nil_) {
      current_node = current_node->link_[left];
    }
    return current_node;
  }

  base_node *FindMaxElement(base_node *current_node) {
    while (current_node->link_[right] != nil_) {
      current_node = current_node->link_[right];
    }
    return current_node;
  }

  base_node *FindBrother(base_node *this_bro) {
    if (this_bro == head_->link_[parent]) {
      return nil_;
    } else if (this_bro == this_bro->link_[parent]->link_[left]) {
      return this_bro->link_[parent]->link_[right];
    }
    return this_bro->link_[parent]->link_[left];
  }

  base_node *FindUncle(base_node *n) {
    base_node *G = n->link_[parent]->link_[parent];
    if (n->link_[parent] == G->link_[left]) {
      return G->link_[right];
    } else if (n->link_[parent] == G->link_[right]) {
      return G->link_[left];
    }
    return nil_;
  }

 private:
  base_node *head_;
  base_node *nil_;
  size_type size_;
  Comp comp_;
};

}  // namespace s21

#endif  // S21_CONTAINERS_S21_CONTAINERS_S21_RB_TREE_H_