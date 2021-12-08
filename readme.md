# Intro
It has come to my attention recently where I would really like to use a constrained vector type. 
Since C++ is typed language it does not make any sense to often validate the input data into a function for example.
An input parameter in a function should be the correct type and shouldn't need validation, in my opinion.

# Objective
std::vector wrapper with additional template argument declaring the constraining relationship to the vector.
Seamless integration to current code, so you shouldn't need to put much effort in refactoring.

# Usage
All of the below code is from the `example.cpp` file.

## Declare a constraining relationship 
Make a struct with a callable bool operator,
```c++
struct constrain_less_than_20 {
    bool operator()(int value) {
        return value < 20;
    }
};
using lessthan20 = nonstd::vector_constrained<int, std::allocator<int>, constrain_less_than_20>;
```

## Construct vector_constrained from std::vector
```c++
std::vector<int> normal_vector{10, 11, 12, 13, 14};
lessthan20 third_vector{normal_vector};
```

## Most of std::vector member functions are implemented
```c++
lessthan20 second_vector{first_vector};// copy the first_vector
second_vector.assign({10, 11});// overwrite vector values
second_vector.insert(second_vector.end(), {12, 13});
second_vector.push_back(14);
```

## Implicit conversion to std::vector
```c++
void print(const std::vector<int>& vec) {
    for (const auto& item : vec) {
        printf("Item is %d\n", item);
    }
}
int main() {
    lessthan20 third_vector{normal_vector};
    print(third_vector);
}
```

# Known flaws
- All functions in std::vector where iterator is returned has either been commented or changed to const_iterator.