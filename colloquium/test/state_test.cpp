#include <gtest/gtest.h>
#include "../src/state.hpp"

TEST(StatePrint, All)
{
        EXPECT_EQ(vehicle::context().get_state_description(), "State: power off.");
        EXPECT_EQ(vehicle::context(vehicle::states::POWER_OFF).get_state_description(), "State: power off.");
        EXPECT_EQ(vehicle::context(vehicle::states::PARTIAL_POWER_SUPPLY).get_state_description(), "State: partial power supply.");
        EXPECT_EQ(vehicle::context(vehicle::states::FULL_POWER_SUPPLY).get_state_description(), "State: full power supply.");
        EXPECT_EQ(vehicle::context(vehicle::states::ENGINE_ON).get_state_description(), "State: engine on.");
}

TEST(StateChange, PowerOff)
{
        EXPECT_EQ(vehicle::context(vehicle::states::POWER_OFF).press_engine_button(false).get_state_description(), "State: partial power supply.");
        EXPECT_EQ(vehicle::context(vehicle::states::POWER_OFF).press_engine_button(true).get_state_description(), "State: engine on.");
}
TEST(StateChange, PartialPowerSupply)
{
        EXPECT_EQ(vehicle::context(vehicle::states::PARTIAL_POWER_SUPPLY).press_engine_button(false).get_state_description(), "State: full power supply.");
        EXPECT_EQ(vehicle::context(vehicle::states::PARTIAL_POWER_SUPPLY).press_engine_button(true).get_state_description(), "State: engine on.");
}
TEST(StateChange, FullPowerSupply)
{
        EXPECT_EQ(vehicle::context(vehicle::states::FULL_POWER_SUPPLY).press_engine_button(false).get_state_description(), "State: power off.");
        EXPECT_EQ(vehicle::context(vehicle::states::FULL_POWER_SUPPLY).press_engine_button(true).get_state_description(), "State: engine on.");
}
TEST(StateChange, EngineOn)
{
        EXPECT_EQ(vehicle::context(vehicle::states::ENGINE_ON).press_engine_button(false).get_state_description(), "State: power off.");
        EXPECT_EQ(vehicle::context(vehicle::states::ENGINE_ON).press_engine_button(true).get_state_description(), "State: power off.");
}

int main(int argc, char **argv)
{
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
}
