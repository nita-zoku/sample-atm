#include "messaging.h"

std::shared_ptr<messaging::message_base>
    messaging::queue::wait_and_pop()
{
    std::unique_lock<std::mutex> lk(m);
    c.wait(lk, [&]{return !q.empty();});
    auto res = q.front();
    q.pop();
    return res;
}

messaging::receiver::operator sender()
{
    return sender(&q);
}

messaging::dispatcher messaging::receiver::wait()
{
    return dispatcher (&q);
}
