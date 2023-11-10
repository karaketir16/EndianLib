#include <cstdint>
#include <gtest/gtest.h>
#include "EndianLib/endian.hpp"
#include <cstring>

TEST(EndianLibTest, SwapEndian) {
    // Test endian swapping
    uint16_t original = 0x1234;
    uint16_t swapped = EndianLib::swap_endian(original);
    EXPECT_EQ(swapped, 0x3412);
}


TEST(EndianLibTest, LittleEndianConversion) {
    EndianLib::le_uint16_t leOriginal = 0x1234;
    const uint8_t expectedLittleEndian[2] = {0x34, 0x12}; // little-endian representation

    // Compare memory representation
    ASSERT_EQ(0, memcmp(&leOriginal, expectedLittleEndian, sizeof(leOriginal)));
}

TEST(EndianLibTest, BigEndianConversion) {
    EndianLib::be_uint16_t beOriginal = 0x1234;
    const uint8_t expectedBigEndian[2] = {0x12, 0x34}; // big-endian representation

    // Compare memory representation
    ASSERT_EQ(0, memcmp(&beOriginal, expectedBigEndian, sizeof(beOriginal)));
}

TEST(EndianLibTest, SameEndianCheck) {
    // Test if the endian check is correct
    EXPECT_TRUE(EndianLib::IsSameEndian(std::endian::little) == EndianLib::is_little_endian());
    EXPECT_TRUE(EndianLib::IsSameEndian(std::endian::big) != EndianLib::is_little_endian());
}



TEST(EndianLibTest, LittleEndianArithmeticOperations) {
    EndianLib::le_uint16_t leValue1 = 0x0102;
    EndianLib::le_uint16_t leValue2 = 0x0304;

    // Assuming operator+ is overloaded
    EndianLib::le_uint16_t leSum = leValue1 + leValue2;
    uint16_t expectedSum = 0x0406; // expected result in little endian

    ASSERT_EQ(static_cast<uint16_t>(leSum), expectedSum);
}

TEST(EndianLibTest, BigEndianArithmeticOperations) {
    EndianLib::be_uint16_t beValue1 = 0x0102;
    EndianLib::be_uint16_t beValue2 = 0x0304;

    // Assuming operator+ is overloaded
    EndianLib::be_uint16_t beSum = beValue1 + beValue2;
    uint16_t expectedSum = 0x0406; // expected result in big endian

    ASSERT_EQ(static_cast<uint16_t>(beSum), expectedSum);
}

TEST(EndianLibTest, TypeCastingOperations) {
    EndianLib::le_uint16_t leValue = 0x1234;
    EndianLib::be_uint16_t beValue = 0x1234;

    // Check type casting to native types
    uint16_t nativeFromLe = static_cast<uint16_t>(leValue);
    uint16_t nativeFromBe = static_cast<uint16_t>(beValue);

    ASSERT_EQ(nativeFromLe, leValue);
    ASSERT_EQ(nativeFromBe, beValue);
}






using namespace EndianLib; // Replace with your actual namespace


TEST(EndianLibTest, Addition) {
    le_uint16_t le1 = 1, le2 = 2;
    ASSERT_EQ(static_cast<uint16_t>(le1 + le2), 3);

    be_uint16_t be1 = 1, be2 = 2;
    ASSERT_EQ(static_cast<uint16_t>(be1 + be2), 3);
}

TEST(EndianLibTest, Subtraction) {
    le_uint16_t le1 = 5, le2 = 2;
    ASSERT_EQ(static_cast<uint16_t>(le1 - le2), 3);

    be_uint16_t be1 = 5, be2 = 2;
    ASSERT_EQ(static_cast<uint16_t>(be1 - be2), 3);
}

// TODO multiplication, division, modulus

TEST(EndianLibTest, Increment) {
    le_uint16_t le = 1;
    le++;
    ASSERT_EQ(static_cast<uint16_t>(le), 2);

    be_uint16_t be = 1;
    be++;
    ASSERT_EQ(static_cast<uint16_t>(be), 2);
}

// TODO decrement

TEST(EndianLibTest, AdditionAssignment) {
    le_uint16_t le = 5;
    le += 3;
    ASSERT_EQ(static_cast<uint16_t>(le), 8);

    be_uint16_t be = 5;
    be += 3;
    ASSERT_EQ(static_cast<uint16_t>(be), 8);

    uint16_t native_u = 3;
    int native_i = 3;

    le += native_u;
    ASSERT_EQ(static_cast<uint16_t>(le), 11);

    be += native_u;
    ASSERT_EQ(static_cast<uint16_t>(be), 11);

    le += native_i;
    ASSERT_EQ(static_cast<uint16_t>(le), 14);

    be += native_i;
    ASSERT_EQ(static_cast<uint16_t>(be), 14);

    le += le;
    ASSERT_EQ(static_cast<uint16_t>(le), 28);

    be += be;
    ASSERT_EQ(static_cast<uint16_t>(be), 28);

    le += be;
    ASSERT_EQ(static_cast<uint16_t>(le), 56);

    be += le;
    ASSERT_EQ(static_cast<uint16_t>(be), 84);
}

// TODO other compound assignments

TEST(EndianLibTest, BitwiseAnd) {
    le_uint16_t le1 = 0b1010, le2 = 0b1100;
    ASSERT_EQ(static_cast<uint16_t>(le1 & le2), 0b1000);

    be_uint16_t be1 = 0b1010, be2 = 0b1100;
    ASSERT_EQ(static_cast<uint16_t>(be1 & be2), 0b1000);

    be_uint16_t be = 0xFF00;
    le_uint16_t le = 0x00FF;

    ASSERT_EQ(static_cast<uint16_t>(be & le), 0x0000);
}

// TODO OR, XOR

TEST(EndianLibTest, TypeConversion) {
    le_uint16_t le = 0x1234;
    ASSERT_EQ(static_cast<uint16_t>(le), 0x1234);

    be_uint16_t be = 0x1234;
    ASSERT_EQ(static_cast<uint16_t>(be), 0x1234);
}

TEST(EndianLibTest, CrossEndianConversion) {
    be_uint16_t sourceValue = 0x1234;
    le_uint16_t convertedValue = 0x1234;

    ASSERT_EQ(sourceValue, convertedValue);

    sourceValue = convertedValue;
    ASSERT_EQ(sourceValue, convertedValue);
}

TEST(EndianLibTest, LeftShift) {
    le_uint16_t le = 1;
    le <<= 2;
    ASSERT_EQ(static_cast<uint16_t>(le), 4);

    be_uint16_t be = 1;
    be <<= 2;
    ASSERT_EQ(static_cast<uint16_t>(be), 4);
}

// TODO right shift


TEST(EndianLibTest, MixedTypeAddition) {
    uint16_t nativeValue = 0x0102;
    be_uint16_t bigEndianValue = 0x0304;
    le_uint16_t littleEndianValue = 0x0506;

    // Perform addition
    uint16_t sumBE = nativeValue + bigEndianValue;
    uint16_t sumLE = nativeValue + littleEndianValue;

    // Expected sums in native uint16_t
    uint16_t expectedSumBE = 0x0406; // Adjust based on your endianness handling
    uint16_t expectedSumLE = 0x0608; // Adjust based on your endianness handling

    ASSERT_EQ(sumBE, expectedSumBE);
    ASSERT_EQ(sumLE, expectedSumLE);
}

TEST(EndianLibTest, ImplicitCasting) {
    be_uint16_t bigEndianValue = 0x0102;
    le_uint16_t littleEndianValue = 0x0304;

    // Implicit casting to native uint16_t
    uint16_t nativeFromBE = bigEndianValue; // implicit cast
    uint16_t nativeFromLE = littleEndianValue; // implicit cast

    // Expected native values after casting
    uint16_t expectedNativeFromBE = 0x0102;
    uint16_t expectedNativeFromLE = 0x0304;

    ASSERT_EQ(nativeFromBE, expectedNativeFromBE);
    ASSERT_EQ(nativeFromLE, expectedNativeFromLE);
}

TEST(EndianLibTest, ExplicitCasting) {
    be_uint16_t bigEndianValue = 0x0102;
    le_uint16_t littleEndianValue = 0x0304;

    // Explicit casting to native uint16_t
    uint16_t nativeFromBE = static_cast<uint16_t>(bigEndianValue);
    uint16_t nativeFromLE = static_cast<uint16_t>(littleEndianValue);

    // Expected native values after casting
    uint16_t expectedNativeFromBE = 0x0102;
    uint16_t expectedNativeFromLE = 0x0304;

    ASSERT_EQ(nativeFromBE, expectedNativeFromBE);
    ASSERT_EQ(nativeFromLE, expectedNativeFromLE);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
