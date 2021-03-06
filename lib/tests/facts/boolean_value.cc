#include <gmock/gmock.h>
#include <facter/facts/scalar_value.hpp>
#include <rapidjson/document.h>
#include <yaml-cpp/yaml.h>
#include <sstream>

using namespace std;
using namespace facter::facts;
using namespace rapidjson;
using namespace YAML;

TEST(facter_facts_boolean_value, constructor) {
    {
        boolean_value value(true);
        ASSERT_TRUE(value.value());
    }
    {
        boolean_value value(false);
        ASSERT_FALSE(value.value());
    }
}

TEST(facter_facts_boolean_value, to_json) {
    {
        boolean_value value(true);

        rapidjson::Value json_value;
        MemoryPoolAllocator<> allocator;
        value.to_json(allocator, json_value);
        ASSERT_TRUE(json_value.IsBool());
        ASSERT_TRUE(json_value.GetBool());
    }
    {
        boolean_value value(false);

        rapidjson::Value json_value;
        MemoryPoolAllocator<> allocator;
        value.to_json(allocator, json_value);
        ASSERT_TRUE(json_value.IsBool());
        ASSERT_FALSE(json_value.GetBool());
    }
}

TEST(facter_facts_boolean_value, insertion_operator) {
    {
        boolean_value value(true);
        Emitter emitter;
        emitter << value;
        ASSERT_EQ("true", string(emitter.c_str()));
    }
    {
        boolean_value value(false);
        Emitter emitter;
        emitter << value;
        ASSERT_EQ("false", string(emitter.c_str()));
    }
}
