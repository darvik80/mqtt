//
// Created by Ivan Kishchenko on 19.12.2020.
//

#ifndef MQTT_COMPONENT_H
#define MQTT_COMPONENT_H
namespace mqtt {

    class Component {
    private:
        std::string _name{};
    public:
        explicit Component(std::string_view name)
                : _name(name) {}

        const std::string &name() {
            return _name;
        }
    };
}

#endif //MQTT_COMPONENT_H
