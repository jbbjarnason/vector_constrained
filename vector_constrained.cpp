export module nonstd.vector_constrained;

export import<cstddef>;         // size_t
export import<memory>;          // std::allocator
export import<initializer_list>;// std::std::initializer_list
export import<vector>;          // std::vector

import<stdexcept>;// std::invalid_argument
import<algorithm>;// std::all_of
import<utility>;  // std::forward

export namespace nonstd {

template<typename T>
struct predicate_true {
    inline constexpr bool operator()(const T &) {
        return true;
    }
};

template<typename T, typename Allocator = std::allocator<T>, typename Predicate = predicate_true<T>>
class vector_constrained {
public:
    constexpr vector_constrained() noexcept(noexcept(Allocator())) = default;
    constexpr explicit vector_constrained(const Allocator &alloc) noexcept : _vec(alloc) {}
    constexpr vector_constrained(size_t count, const T &value, const Allocator &alloc = Allocator()) : _vec(count, value, alloc) {}
    constexpr explicit vector_constrained(size_t count, const Allocator &alloc = Allocator()) : _vec(count, alloc) {}
    template<class InputIt>
    constexpr vector_constrained(InputIt first, InputIt last, const Allocator &alloc = Allocator()) : _vec(first, last, alloc) {}
    constexpr vector_constrained(const vector_constrained &other) : _vec(other._vec) {}
    constexpr vector_constrained(const vector_constrained &other, const Allocator &alloc) : _vec(other._vec, alloc) {}
    constexpr vector_constrained(vector_constrained &&other) noexcept : _vec(other) {}
    constexpr vector_constrained(vector_constrained &&other, const Allocator &alloc) : _vec(other, alloc) {}
    constexpr vector_constrained(std::initializer_list<T> init, const Allocator &alloc = Allocator()) : _vec(alloc) {
        throw_if_invalid(init.begin(), init.end());
        _vec = std::vector<T, Allocator>{init, alloc};
    }
    // constructor NOT from std::vector
    template<class OtherPred>
    constexpr explicit vector_constrained(const vector_constrained<T, Allocator, OtherPred> &other) {
        throw_if_invalid(other.begin(), other.end());
        _vec = other.vector();
    }
    // constructor NOT from std::vector
    constexpr explicit vector_constrained(const std::vector<T, Allocator> &other) {
        throw_if_invalid(other.begin(), other.end());
        _vec = other;
    }

    constexpr ~vector_constrained() = default;

    constexpr vector_constrained &operator=(const vector_constrained &other) {
        _vec = other._vec;
        return *this;
    }
    constexpr vector_constrained &operator=(vector_constrained &&other) noexcept {
        _vec = other._vec;
        return *this;
    }
    constexpr vector_constrained &operator=(std::initializer_list<T> ilist) {
        throw_if_invalid(ilist.begin(), ilist.end());
        _vec = ilist;
        return *this;
    }
    // operator= NOT from std::vector
    constexpr vector_constrained &operator=(const std::vector<T, Allocator> &other) {
        throw_if_invalid(other.begin(), other.end());
        _vec = other;
        return *this;
    }
    constexpr operator const std::vector<T, Allocator>&() const {
        return _vec;
    }

    constexpr void assign(size_t count, const T &value) {
        throw_if_invalid(value);
        _vec.assign(count, value);
    }
    template<class InputIt>
    constexpr void assign(InputIt first, InputIt last) {
        throw_if_invalid(first, last);
        _vec.assign(first, last);
    }
    constexpr void assign(std::initializer_list<T> ilist) {
        throw_if_invalid(ilist.begin(), ilist.end());
        _vec.assign(ilist);
    }

    constexpr Allocator get_allocator() const noexcept {
        return _vec.get_allocator();
    }

    /*
 * Unable to set predicate criteria for assignment operator of T.
 * All functions commented which this applies to.
 * */
    //    constexpr T& at( size_t pos ) {
    //        return _vec.at(pos);
    //    }
    constexpr const T &at(size_t pos) const {
        return _vec.at(pos);
    }

    //    constexpr T& operator[]( size_t pos ) {
    //        return _vec[pos];
    //    }
    constexpr const T &operator[](size_t pos) const {
        return _vec[pos];
    }

    //    constexpr T& front() {
    //        return _vec.front();
    //    }
    constexpr const T &front() const {
        return _vec.front();
    }

    //    constexpr T& back() {
    //        return _vec.back();
    //    }
    constexpr const T &back() const {
        return _vec.back();
    }

    //    constexpr T* data() noexcept {
    //        return _vec.data();
    //    }
    constexpr const T *data() const noexcept {
        return _vec.data();
    }

    using iterator = std::vector<T, Allocator>::iterator;
    using const_iterator = std::vector<T, Allocator>::const_iterator;
    using reverse_iterator = std::vector<T, Allocator>::reverse_iterator;
    using const_reverse_iterator = std::vector<T, Allocator>::const_reverse_iterator;

    //    constexpr iterator begin() noexcept {
    //        return _vec.begin();
    //    }
    [[nodiscard]] constexpr const_iterator begin() const noexcept {
        return _vec.begin();
    }
    [[nodiscard]] constexpr const_iterator cbegin() const noexcept {
        return _vec.cbegin();
    }

    //    constexpr iterator end() noexcept {
    //        return _vec.end();
    //    }
    [[nodiscard]] constexpr const_iterator end() const noexcept {
        return _vec.end();
    }
    [[nodiscard]] constexpr const_iterator cend() const noexcept {
        return _vec.cend();
    }

    //    constexpr reverse_iterator rbegin() noexcept {
    //        return _vec.rbegin();
    //    }
    [[nodiscard]] constexpr const_reverse_iterator rbegin() const noexcept {
        return _vec.rbegin();
    }
    [[nodiscard]] constexpr const_reverse_iterator crbegin() const noexcept {
        return _vec.crbegin();
    }

    //    constexpr reverse_iterator rend() noexcept {
    //        return _vec.rend();
    //    }
    [[nodiscard]] constexpr const_reverse_iterator rend() const noexcept {
        return _vec.rend();
    }
    [[nodiscard]] constexpr const_reverse_iterator crend() const noexcept {
        return _vec.crend();
    }

    [[nodiscard]] constexpr bool empty() const noexcept {
        return _vec.empty();
    }

    [[nodiscard]] constexpr size_t size() const noexcept {
        return _vec.size();
    }

    [[nodiscard]] constexpr size_t max_size() const noexcept {
        return _vec.max_size();
    }

    constexpr void reserve(size_t new_cap) {
        _vec.reserve(new_cap);
    }

    [[nodiscard]] constexpr size_t capacity() const noexcept {
        return _vec.capacity();
    }

    constexpr void shrink_to_fit() {
        _vec.shrink_to_fit();
    }

    constexpr void clear() noexcept {
        _vec.clear();
    }

    constexpr const_iterator insert(const_iterator pos, const T &value) {
        throw_if_invalid(value);
        return _vec.insert(pos, value);
    }
    constexpr const_iterator insert(const_iterator pos, T &&value) {
        throw_if_invalid(value);
        return _vec.insert(pos, value);
    }
    constexpr const_iterator insert(const_iterator pos, size_t count, const T &value) {
        throw_if_invalid(value);
        return _vec.insert(pos, count, value);
    }
    template<class InputIt>
    constexpr const_iterator insert(const_iterator pos, InputIt first, InputIt last) {
        throw_if_invalid(first, last);
        return _vec.insert(pos, first, last);
    }
    constexpr const_iterator insert(const_iterator pos, std::initializer_list<T> ilist) {
        throw_if_invalid(ilist.begin(), ilist.end());
        return _vec.insert(pos, ilist);
    }

    template<class... Args>
    constexpr const_iterator emplace(const_iterator pos, Args &&...args) {
        const auto value{T(std::forward<Args>(args)...)};
        throw_if_invalid(value);
        return _vec.emplace(pos, value);
    }

    constexpr const_iterator erase(const_iterator pos) {
        return _vec.erase(pos);
    }
    constexpr const_iterator erase(const_iterator first, const_iterator last) {
        return _vec.erase(first, last);
    }

    constexpr void push_back(const T &value) {
        throw_if_invalid(value);
        _vec.push_back(value);
    }
    constexpr void push_back(T &&value) {
        throw_if_invalid(value);
        _vec.push_back(value);
    }

    template<class... Args>
    constexpr const T &emplace_back(Args &&...args) {
        const auto value{T(std::forward<Args>(args)...)};
        throw_if_invalid(value);
        return _vec.emplace_back(value);
    }

    constexpr void pop_back() {
        _vec.pop_back();
    }

    constexpr void resize(size_t count) {
        _vec.resize(count);
    }
    constexpr void resize(size_t count, const T &value) {
        throw_if_invalid(value);
        _vec.resize(count, value);
    }

    constexpr void swap(vector_constrained &other) noexcept {
        _vec.swap(other._vec);
    }

    // function NOT from std::vector
    [[nodiscard]] constexpr const std::vector<T, Allocator> &vector() const noexcept {
        return _vec;
    }

private:
    template<class InputIt>
    constexpr void throw_if_invalid(InputIt first, InputIt last) const {
        if (!std::all_of(first, last, Predicate())) {
            throw std::invalid_argument("Arguments do not fulfill the predicate criteria");
        }
    }
    constexpr void throw_if_invalid(const T &value) const {
        if (!Predicate()(value)) {
            throw std::invalid_argument("Argument does not fulfill the predicate criteria");
        }
    }
    constexpr void throw_if_invalid(T &&value) const {
        if (!Predicate()(value)) {
            throw std::invalid_argument("Argument does not fulfill the predicate criteria");
        }
    }

    std::vector<T, Allocator> _vec{Allocator()};
};

template<class T, class Alloc, class Pred1, class Pred2>
inline constexpr auto operator==(const vector_constrained<T, Alloc, Pred1> &lhs, const vector_constrained<T, Alloc, Pred2> &rhs) {
    return lhs.vector() == rhs.vector();
}

template<class T, class Alloc, class Pred1, class Pred2>
inline constexpr auto operator<=>(const vector_constrained<T, Alloc, Pred1> &lhs, const vector_constrained<T, Alloc, Pred2> &rhs) {
    return lhs.vector() <=> rhs.vector();
}

}// namespace nonstd

export {

template<class T, class Alloc, class Pred>
inline constexpr auto operator==(const nonstd::vector_constrained<T, Alloc, Pred> &lhs, const std::vector<T, Alloc> &rhs) {
    return lhs.vector() == rhs;
}

template<class T, class Alloc, class Pred>
inline constexpr auto operator<=>(const nonstd::vector_constrained<T, Alloc, Pred> &lhs, const std::vector<T, Alloc> &rhs) {
    return lhs.vector() <=> rhs;
}

};