#include <Platform.Equality.h>
#include <gtest/gtest.h>

namespace Platform::Equality::Tests
{/*
    TEST(EqualityTest, BaseAnyEqual)
    {
        {
            int a = 0x228;
            int b = 0x1337;
            ASSERT_NE(std::any(a), std::any(b));
        }

        {
            int a = 0x177013;
            float b = 0x177013;
            ASSERT_EQ(std::any(a), std::any(b));
        }

        {
            auto a = "i love green stuff";
            auto b = (std::string)"i love green stuff";
            ASSERT_NE(std::any(a), std::any(b));
        }

        {
            auto a = "i love green stuff";
            auto b = "i love green stuff";
            ASSERT_EQ(std::any(a), std::any(b));
        }

        {
            auto a = (std::string)"i love green stuff";
            auto b = (std::string)"i love green stuff";
            ASSERT_EQ(std::any(a), std::any(b));
        }

        {
            std::vector<int> a {1, 2, 3, 4};
            std::vector<int> b {1, 2, 3, 4};
            //EXPECT_ANY_THROW(std::any(a) == std::any(b));
        }
    }

    TEST(EqualityTest, AggressiveAnyTest)
    {
        {
            int steps = 1e6;
            while(steps--)
            {
                int number = rand();
                ASSERT_EQ(std::any(number), std::any(number));
            }
        }

        {
            int steps = 1e6;
            while(steps--)
            {
                int a = rand();
                int b = rand();

                if(a == b)
                {
                    ASSERT_EQ(std::any(a), std::any(b));
                }
                else
                {
                    ASSERT_NE(std::any(a), std::any(b));
                }
            }
        }
    }

    TEST(EqualityTest, RegisterTest)
    {
        {
            struct Nil {};
            RegisterEqualityComparer<Nil>([](auto a, auto b){ return true; });
            ASSERT_EQ(std::any(Nil{}), std::any(Nil{}));
        }

        {
            struct Nil {};
            RegisterEqualityComparer<Nil>([](auto a, auto b){ return false; });
            ASSERT_NE(std::any(Nil{}), std::any(Nil{}));
        }
    }*/
}
