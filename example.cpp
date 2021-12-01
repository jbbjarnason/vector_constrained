import <cstdio>;
import <memory>;

import nonstd.vector_constrained;

struct constrain_less_than_10 {
    bool operator() (int value) {
        return value < 10;
    }
};

struct constrain_less_than_20 {
    bool operator() (int value) {
        return value < 10;
    }
};

int main() {
    auto vec{ nonstd::vector_constrained<int, std::allocator<int>, constrain_less_than_10>() };
    vec.assign({1,2,3,4,5,6,7,8,9});
    auto vec2{ nonstd::vector_constrained<int, std::allocator<int>, constrain_less_than_20>() };
    vec2.assign({1,2,3,4,5,6,7});
    if (vec == vec2) {
        printf("wtf\n");
    }
    printf("size is %d\n", vec.size());
    return 0;
}