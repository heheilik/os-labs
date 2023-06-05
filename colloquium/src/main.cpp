#include <iostream>
#include "state.hpp"

int main()
{
        vehicle::context vehicle;
        std::cout << vehicle.get_state_description() << std::endl;

        vehicle.press_engine_button(false)
               .press_engine_button(false);
        std::cout << vehicle.get_state_description() << std::endl;

        vehicle.press_engine_button(true);
        std::cout << vehicle.get_state_description() << std::endl;

        vehicle.press_engine_button(false);
        std::cout << vehicle.get_state_description() << std::endl;

        vehicle::context another_vehicle(vehicle::states::ENGINE_ON);
        std::cout << another_vehicle.get_state_description() << std::endl;

        return 0;
}
