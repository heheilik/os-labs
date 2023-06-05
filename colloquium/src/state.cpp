#include "state.hpp"

vehicle::power_off POWER_OFF;
vehicle::partial_power_supply PARTIAL_POWER_SUPPLY;
vehicle::full_power_supply FULL_POWER_SUPPLY;
vehicle::engine_on ENGINE_ON;

vehicle::context::context()
{
        current_state = &POWER_OFF;
}
vehicle::context::context(states state)
{
        switch (state)
        {
                case states::POWER_OFF:
                        current_state = &POWER_OFF;
                        break;

                case states::PARTIAL_POWER_SUPPLY:
                        current_state = &PARTIAL_POWER_SUPPLY;
                        break;

                case states::FULL_POWER_SUPPLY:
                        current_state = &FULL_POWER_SUPPLY;
                        break;

                case states::ENGINE_ON:
                        current_state = &ENGINE_ON;
                        break;
        }
}
void vehicle::context::set_state(vehicle::state *state)
{
        current_state = state;
}
vehicle::context &vehicle::context::press_engine_button(bool brake_pressed)
{
        current_state->press_engine_button(this, brake_pressed);
        return *this;
}
std::string vehicle::context::get_state_description()
{
        return current_state->get_state_description();
}

void vehicle::power_off::press_engine_button(context *c, bool brake_pressed)
{
        c->set_state(
                brake_pressed ?
                (vehicle::state*)&ENGINE_ON :
                (vehicle::state*)&PARTIAL_POWER_SUPPLY
        );
}
std::string vehicle::power_off::get_state_description()
{
        return "State: power off.";
}

void vehicle::partial_power_supply::press_engine_button(context *c, bool brake_pressed)
{
        c->set_state(
                brake_pressed ?
                (vehicle::state*)&ENGINE_ON :
                (vehicle::state*)&FULL_POWER_SUPPLY
        );
}
std::string vehicle::partial_power_supply::get_state_description()
{
        return "State: partial power supply.";
}

void vehicle::full_power_supply::press_engine_button(context *c, bool brake_pressed)
{
        c->set_state(
                brake_pressed ?
                (vehicle::state*)&ENGINE_ON :
                (vehicle::state*)&POWER_OFF
        );
}
std::string vehicle::full_power_supply::get_state_description()
{
        return "State: full power supply.";
}

void vehicle::engine_on::press_engine_button(context *c, bool brake_pressed)
{
        c->set_state((vehicle::state*)&POWER_OFF);
}
std::string vehicle::engine_on::get_state_description()
{
        return "State: engine on.";
}
