import nonstd.vector_constrained;
import<cassert>;
import<cstdio>;
import<exception>;

struct constrain_less_than_10 {
    bool operator()(int value) {
        return value < 10;
    }
};
using lessthan10 = nonstd::vector_constrained<int, std::allocator<int>, constrain_less_than_10>;

struct constrain_less_than_20 {
    bool operator()(int value) {
        return value < 20;
    }
};
using lessthan20 = nonstd::vector_constrained<int, std::allocator<int>, constrain_less_than_20>;

void print(const std::vector<int>& vec) {
    for (const auto& item : vec) {
        printf("Item is %d\n", item);
    }
}

int main() {
    lessthan10 first_vector{{1, 2, 3, 4, 5, 6, 7, 8, 9}};
    lessthan20 second_vector{first_vector};// copy the first_vector
    assert(("Oboj something is wrong", first_vector == second_vector));

    second_vector.assign({10, 11});// overwrite vector values
    second_vector.insert(second_vector.end(), {12, 13});
    second_vector.push_back(14);
    printf("14 is at 4, see: %d\n", second_vector[4]);// out: 14 is at 4, see: 14

    try {
        first_vector.push_back(10);// invalid value ...
    } catch (const std::exception &ex) {
        printf("Catched it: %s\n", ex.what());// out: Catched it: Argument does not fulfill the predicate criteria
    }

    std::vector<int> normal_vector{10, 11, 12, 13, 14};
    assert(("constrained vec can be compared with regular", second_vector == normal_vector));

    lessthan20 third_vector{normal_vector};// construct from std::vector
    assert(("still the same", third_vector == normal_vector));

    print(third_vector);

    // ... you get the point

    return 0;
}