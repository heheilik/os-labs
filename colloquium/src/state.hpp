#ifndef STATE_HPP
#define STATE_HPP

#include <iostream>

namespace vehicle {

class context;


class state
{
public:
        virtual void press_engine_button(context*, bool brake_pressed) = 0;
        virtual std::string get_state_description() = 0;
};

enum class states {
        POWER_OFF,
        PARTIAL_POWER_SUPPLY,
        FULL_POWER_SUPPLY,
        ENGINE_ON
};


class power_off : public state
{
        void press_engine_button(context*, bool) override;
        std::string get_state_description() override;
};

class partial_power_supply : public state
{
        void press_engine_button(context*, bool) override;
        std::string get_state_description() override;
};

class full_power_supply : public state
{
        void press_engine_button(context*, bool) override;
        std::string get_state_description() override;
};

class engine_on : public state
{
        void press_engine_button(context*, bool) override;
        std::string get_state_description() override;
};


class context
{
        state *current_state;
        void set_state(state*);

public:
        context();
        context(states);
        context &press_engine_button(bool);
        std::string get_state_description();

        friend class power_off;
        friend class partial_power_supply;
        friend class full_power_supply;
        friend class engine_on;
};

}

#endif
