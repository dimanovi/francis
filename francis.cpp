#define CATCH_CONFIG_MAIN
#include "catch.hpp"

uint8_t memory[4096];

struct kv_pair { uint8_t key; uint16_t val; };
kv_pair *itr = nullptr;

bool has(uint16_t key) {
   itr = reinterpret_cast<kv_pair*>(memory);
   return itr->key == key;
}

bool add(uint16_t key, uint64_t val) {
    itr = reinterpret_cast<kv_pair*>(memory);
    itr->key = key;
    itr->val = val;
    return true;
}

auto get(uint16_t key) {
    itr = reinterpret_cast<kv_pair*>(memory);
    return itr->val;
}

TEST_CASE( "Adding a single key-val pair" , "") {

    constexpr uint16_t key = 1;
    constexpr uint64_t val = 2;

    SECTION( "Initially memory contains no values" ) {
        REQUIRE( has(key) == false );
        REQUIRE( has(0) == false ); // currently failing
    }
    SECTION( "After an add, memory contains added key" ) {
        REQUIRE( add(key, val) == true );
        REQUIRE( has(key) == true );
    }
    SECTION( "Value at key matches added value" ) {
        REQUIRE( get(key) == val );
    }
}
