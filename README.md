# mqtt

MQTT Client v3.1 on C++ with boost::asio & signals

# How to use

```cpp
#include "Library.h"
...
{
    using namespace mqtt;
    
    //init library
    auto lib = std::make_shared<Library>();
    lib->init();
    ...
    // get main factory for create connections to mqtt broker
    auto factory = lib->getFactory();
    ...
    // create connection
    properties::ConnectionProperties properties{
        "alicloud.crearts.xyz",
        1883,
    };    
    auto client = factory->create(properties);
    // and subscribe to some topic
    auto sub = client->subscribe("/home/new", message::QOS_AT_LEAST_ONCE, [](const ByteBuffer &data) {
        std::string msg((const char *) data.data(), data.size());
        MQTT_LOG(info) << "Got MSG: " << msg;
    });
    ...
    // create publisher & send data into topic 
    auto pub = client->publisher("/home/test", message::QOS_AT_LEAST_ONCE);
    pub.publish("Hello World");
    pub.publish("I still can send some text");
    ...
    // destroy all mqtt objects
    lib->shutdown();
}


```

## TODO
* Timeout for message responses
* Resend messages with QoS > 0