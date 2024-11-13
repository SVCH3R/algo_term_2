#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H
template <typename T>
class UniquePtr {
 private:
  T *ptr_;

 public:
  UniquePtr() : ptr_(nullptr) {
  }

  explicit UniquePtr(T *ptr) : ptr_(ptr) {
  }

  UniquePtr(const UniquePtr &) = delete;

  UniquePtr &operator=(const UniquePtr &) = delete;

  UniquePtr(UniquePtr &other) {
    ptr_ = other.ptr_;
    delete other.ptr_;
  }

  UniquePtr &operator=(UniquePtr &other) {
    T *ptr = other.ptr_;
    delete other.ptr_;
    return UniquePtr(ptr);
  }

  ~UniquePtr() {
    delete ptr_;
  }

  T *Release() {
    T *ptr = ptr_;
    ptr_ = nullptr;
    return ptr;
  }

  void Reset(T *ptr = nullptr) {
    delete ptr_;
    ptr_ = ptr;
  }

  void Swap(UniquePtr<T> &other) {
    std::swap(ptr_, other.ptr_);
  }

  T *Get() const {
    return ptr_;
  }

  explicit operator bool() const {
    return ptr_ != nullptr;
  }

  T &operator*() const {
    return *ptr_;
  }

  T *operator->() const {
    return ptr_;
  }
};
#endif