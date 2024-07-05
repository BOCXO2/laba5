#include "pch.h"
#include "v_t.h"
TEST(MyValidator,validate_login) {
	MyValidator v;
  EXPECT_TRUE(v.validate_login(std::string("sta2s3")));
  EXPECT_FALSE(v.validate_login(std::string("Stas25")));
}
TEST(MyValidator, validate_pass) {
	MyValidator vo;
    EXPECT_TRUE(vo.validate_pass(std::string("St999999")));
    EXPECT_FALSE(vo.validate_pass(std::string("231")));
}
