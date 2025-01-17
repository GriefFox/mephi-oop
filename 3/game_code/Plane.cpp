#include "game_headers/Plane.hpp"
#include "game_headers/generic.hpp"
#include <memory>
#include <thread>
#include <mutex>

namespace zasada {

    Plane::Plane()
        : damage(0), activity(false), health(0), speed(0), fuel_capacity(0),
        fuel_cons(0), refill_fuel(0), position(point(0,0)), price(0), range(0) {}
    Plane::Plane(size_t _damage, bool _activity, size_t _health, size_t _speed,
          const std::string& _name, std::shared_ptr<Ammo> _ammo, size_t _max_ammo,
          size_t _fuel_capacity, size_t _fuel_current, size_t _fuel_cons,
          size_t _refill_fuel, point _position, size_t _price, size_t _range): damage(_damage),
          activity(_activity),
          health(_health),
          speed(_speed),
          name(_name),
          ammo(_ammo),
          max_ammo(_max_ammo),
          fuel_capacity(_fuel_capacity),
          fuel_current(_fuel_current),
          fuel_cons(_fuel_cons),
          refill_fuel(_refill_fuel),
          position(_position),
          price(_price),
          range(_range) {}
          
    Plane::~Plane() {}

    // getters
    size_t Plane::getDamage() const{
        return damage;
    }

    bool Plane::getActivity() const{
        return activity;
    }

    size_t Plane::getHealth() const{
        return health;
    }

    size_t Plane::getSpeed() const{
        return speed;
    }

    std::string Plane::getName() const {
        return name;
    }

    std::shared_ptr<Ammo> Plane::getAmmo() const{
        return ammo;
    }

    size_t Plane::getMaxAmmo() const{
        return max_ammo;
    }

    size_t Plane::getFuelCurrent() const{
        return fuel_current;
    }

    size_t Plane::getFuelCapacity() const{
        return fuel_capacity;
    }

    size_t Plane::getFuelCons() const{
        return fuel_cons;
    }

    size_t Plane::getRefillFuel() const{
        return refill_fuel;
    }

    point Plane::getPosition() const{
        return position;
    }

    size_t Plane::getPrice() const{
        return price;
    }

    size_t Plane::getRange() const{
        return range;
    }

    // setters
    Plane& Plane::setDamage(size_t dmg) {
        damage = dmg;
        return *this;
    }

    Plane& Plane::setActivity(bool isActive) {
        activity = isActive;
        return *this;
    }

    Plane& Plane::setHealth(size_t hp) {
        health = hp;
        if (health == 0) {
            activity = false;
        }
        return *this;
    }

    Plane& Plane::setSpeed(size_t spd) {
        //? maybe add max_speed
        speed = spd;
        return *this;
    }

    Plane& Plane::setName(const std::string& newName) {
        name = newName;
        return *this;
    }

    Plane& Plane::setAmmo(std::shared_ptr<Ammo> new_ammo){
        ammo = new_ammo;
        return *this;
    }

    Plane& Plane::setMaxAmmo(size_t max_ammo){
        this->max_ammo = max_ammo;
        return *this;
    }

    Plane& Plane::setFuelCurrent(size_t cur){
        fuel_current = cur;
        return *this;
    }

    Plane& Plane::setFuelCapacity(size_t capacity) {
        fuel_capacity = capacity;
        return *this;
    }

    Plane& Plane::setFuelCons(size_t consumption) {
        fuel_cons = consumption;
        return *this;
    }

    Plane& Plane::setRefillFuel(size_t refill) {
        refill_fuel = refill;
        return *this;
    }

    Plane& Plane::moveTo(point n_pos){
        double distance = calculate_distace(n_pos, position);
        if (distance == 0)
            return *this;

        double nx = (n_pos.x - position.x) / distance;
        double ny = (n_pos.y - position.y) / distance;

        double moveDistance = std::min(static_cast<double>(speed), distance);
        position.x += nx * moveDistance;
        position.y += ny * moveDistance;

        return *this;
    }

    void Plane::moveToAsync(point n_pos) {
            std::thread([this, n_pos]() {
                std::lock_guard<std::mutex> lock(mtx);
                this->moveTo(n_pos);
            }).detach();  // Detach thread to run independently
        }

    Plane& Plane::setPosition(point n_pos){
        position = n_pos;
        return *this;
    }

    Plane& Plane::setPrice(size_t cost) {
        price = cost;
        return *this;
    }

    Plane& Plane::setRange(size_t rng) {
        range = rng;
        return *this;
    }

    Plane& Plane::takeDamage(size_t dmg) {
        if (health > dmg) {
            health -= dmg;
        } else {
            health = 0;
            activity = false; //* Destroyed
        }
        return *this;
    }

    size_t Plane::attack(double distance, std::shared_ptr<Plane>){
        throw std::runtime_error("This plane cannot attack planes");
    }

    void Plane::attackAsync(double distance, std::shared_ptr<Plane> target) {
            std::thread([this, distance, target]() {
                std::lock_guard<std::mutex> lock(mtx);
                this->attack(distance, target);
            }).detach();  // Detach thread to run independently
        }

    size_t Plane::attack(double distance, std::shared_ptr<Ship>){
        throw std::runtime_error("This plane cannot attack ships");
    }

    void Plane::attackAsync(double distance, std::shared_ptr<Ship> target) {
            std::thread([this, distance, target]() {
                std::lock_guard<std::mutex> lock(mtx);
                this->attack(distance, target);
            }).detach();  // Detach thread to run independently
        }

    size_t Plane::cost(){
        return price;
    }

    //* Fighter
    size_t Fighter::attack(double distance, std::shared_ptr<Plane> to) {
        if (!activity || (ammo->getCurrent() == 0))
            throw std::runtime_error("unactive plane can't fly");
        
        // Check if the target is within range
        if (distance > range) {
            return 0; // Target is out of range
        }

        size_t consumed = 0;
        try {
            consumed = ammo->consume();
        } catch (const std::out_of_range& e) {
            return 0; // No ammo left to fire
        }

        to->takeDamage(damage);
        return consumed;
    }

    //* StormTrooper
    
    size_t StormTrooper::attack(double distance, std::shared_ptr<Ship> to) {
        if (!activity || (ammo->getCurrent() == 0))
            return 0;

        // Check if the target is within range
        if (distance > range) {
            return 0; // Target is out of range
        }

        size_t consumed = 0;
        try {
            consumed = ammo->consume();
        } catch (const std::out_of_range& e) {
            return 0; // No ammo left to fire
        }

        to->takeDamage(damage);
        return consumed;
    }

    Fighter::Fighter(size_t _damage, bool _activity, size_t _health, size_t _speed,
                     const std::string& _name, std::shared_ptr<Ammo> _ammo, size_t _max_ammo,
                     size_t _fuel_capacity, size_t _fuel_current, size_t _fuel_cons,
                     size_t _refill_fuel, point _position, size_t _price, size_t _range)
        : Plane(_damage, _activity, _health, _speed, _name, _ammo, _max_ammo,
                _fuel_capacity, _fuel_current, _fuel_cons, _refill_fuel, _position, _price, _range) {
        // Additional initialization for Fighter, if needed
    }

    StormTrooper::StormTrooper(size_t _damage, bool _activity, size_t _health, size_t _speed,
                               const std::string& _name, std::shared_ptr<Ammo> _ammo, size_t _max_ammo,
                               size_t _fuel_capacity, size_t _fuel_current, size_t _fuel_cons,
                               size_t _refill_fuel, point _position, size_t _price, size_t _range)
        : Plane(_damage, _activity, _health, _speed, _name, _ammo, _max_ammo,
                _fuel_capacity, _fuel_current, _fuel_cons, _refill_fuel, _position, _price, _range) {
        // Additional initialization for StormTrooper, if needed
    }
} // namespace zasada