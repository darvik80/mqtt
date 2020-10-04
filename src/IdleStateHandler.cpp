//
// Created by Ivan Kishchenko on 03.10.2020.
//

#include "IdleStateHandler.h"

#include <memory>

namespace mqtt {

    IdleStateHandler::IdleStateHandler(int readIdleSec, int writeIdleSec, int allIdleSec, std::function<void(IdleType idleType)> callback)
            : _readIdleSec(readIdleSec), _writeIdleSec(writeIdleSec), _allIdleSec(allIdleSec), _callback(callback) {
    }

    void IdleStateHandler::channelReadComplete(ChannelContext &ctx) {
        //resetTimers(ctx, IdleStateHandler::READ_IDLE);
    }

    void IdleStateHandler::channelWriteComplete(ChannelContext &ctx) {
        //resetTimers(ctx, IdleStateHandler::WRITE_IDLE);
    }

    void IdleStateHandler::channelActive(ChannelContext &ctx) {
        resetTimers(ctx, IdleStateHandler::IDLE);
    }

    void IdleStateHandler::channelInactive(ChannelContext &ctx) {
        _readTimer.reset(nullptr);
        _writeTimer.reset(nullptr);
        _allTimer.reset(nullptr);
    }

    void IdleStateHandler::onMessage(ChannelContext &ctx, const message::Message::Ptr& msg) {
        resetTimers(ctx, IdleStateHandler::READ_IDLE);
    }

    void IdleStateHandler::resetTimers(ChannelContext &ctx, IdleType idleType) {
        DefaultChannelContext timerCtx(ctx.getIoService(), ctx.getChannel(), boost::system::error_code(), 0);
        if (_readIdleSec && (idleType&IdleStateHandler::READ_IDLE)) {
            _readTimer = std::make_unique<Timer>(
                    ctx.getIoService(), _readIdleSec, [this, timerCtx]() { onIdle(timerCtx, IdleStateHandler::READ_IDLE); }
            );
        }

        if (_writeIdleSec && (idleType&IdleStateHandler::WRITE_IDLE)) {
            _writeTimer = std::make_unique<Timer>(
                    ctx.getIoService(), _writeIdleSec, [this, timerCtx]() { onIdle(timerCtx, IdleStateHandler::WRITE_IDLE); }
            );
        }

        if (_allIdleSec) {
            _allTimer = std::make_unique<Timer>(
                    ctx.getIoService(), _allIdleSec, [this, timerCtx]() { onIdle(timerCtx, IdleStateHandler::IDLE); }
            );
        }
    }
}