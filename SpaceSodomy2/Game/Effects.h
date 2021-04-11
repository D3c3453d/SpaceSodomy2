#pragma once
#include <deque>
#include <AuxLib/AuxLib.h>
#include "Counter.h"

struct Effects_Def;

class Effects {
public:
    enum Types {
        INSTANT_HP,
        INSTANT_STAMINA,
        LASER,
        LASER_BURN,
        CHARGE,
        BERSERK,
        IMMORTALITY,
        COUNT
    };
    enum Algebraic_Type {
        ANNULATOR,         // multiplicative zero
        ADDITIVE,
        MAXIMAL
    };
    class Effect {
    private:
        Counter duration;
        float strength;
        Algebraic_Type type;
    public:
        Effect();
        Effect(Algebraic_Type);
        Effect(Counter, Algebraic_Type = Algebraic_Type::ADDITIVE);
        Effect(float, Algebraic_Type = Algebraic_Type::ADDITIVE);

        Algebraic_Type get_type();
        Counter* get_counter();
        float get_strength();

        void set_type(Algebraic_Type);
        void set_counter(Counter);
        void set_strength(float);


        void step(float dt);

        Effect& operator+=(Effect other);
        Effect operator+(Effect effect);
    };

private:
    std::deque<Effect> effects;

public:

    Effects();
    Effects(Effects_Def*);

    Effect* get_effect(Types type);
    void set_effect(Effect*, Types type);

    void step(float dt);

    void update(Effects_Def* effects);

};

struct Effects_Def {
public:
    std::deque<Effects::Effect> effects;

    Effects_Def();
    Effects_Def(Effects::Algebraic_Type);
};