#include <gtest/gtest.h>
#include "configuration.h"

bool load(const std::string &path){
    Configuration::Configuration config;
    return config.load(path);
}

// Test case to check the functionality of add function
TEST(ConfigurationTest, LoadTest) {
    EXPECT_TRUE(load("/home/tduvinage/Documents/CDR2024/KaribousBrainSystem/etc/KabirousSystem.yaml"));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}