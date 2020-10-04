//
// Created by Ivan Kishchenko on 03.10.2020.
//

#ifndef MQTT_IDLESTATEHANDLER_H
#define MQTT_IDLESTATEHANDLER_H

#include <cstdint>
#include "Channel.h"
#include "Timer.h"

namespace mqtt {
    class IdleStateHandler : public ChannelInboundHandler, public ChannelOutboundHandler {
    public:
        enum IdleType {
            READ_IDLE = 0x01,
            WRITE_IDLE = 0x02,
            IDLE = (READ_IDLE|WRITE_IDLE),
        };
    private:
        uint64_t _readIdleSec;
        uint64_t _writeIdleSec;
        uint64_t _allIdleSec;

        Timer::AutoPtr _readTimer;
        Timer::AutoPtr _writeTimer;
        Timer::AutoPtr _allTimer;

        std::function<void(IdleType idleType)> _callback;
    private:
        void resetTimers(ChannelContext &ctx, IdleType idleType);
    public:
        IdleStateHandler(int readIdleSec, int writeIdleSec, int allIdleSec, std::function<void(IdleType idleType)> callback);

        void channelReadComplete(ChannelContext &ctx) override;
        void channelWriteComplete(ChannelContext &ctx) override;

        void channelActive(ChannelContext &ctx) override;

        void channelInactive(ChannelContext &ctx) override;

        void onMessage(ChannelContext &ctx, const message::Message::Ptr& msg) override;

        virtual void onIdle(const ChannelContext &ctx, IdleType idleType) {
            _callback(idleType);
        }
    };
}


#endif //MQTT_IDLESTATEHANDLER_H
