#include "MessageDispatcher.h"
#include "Entity.h"

void MessageDispatcher::dispatchMessage(Message& message) {
    if (message.receiver) {
        message.receiver->receiveMessage(message);
    }
}
