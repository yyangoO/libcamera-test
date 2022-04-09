/**
 * @file                    eventloop.cpp
 * @author                  yyang yyangoO@outlook.com & sjtu_yangyang@sjtu.edu.cn
 * @version                 1.0.0
 * @date                    7-APR-2022
 * @section                 description
 *                          event loop
 * @section                 logs
 * <table>
 * <tr><th>date             <th>version     <th>author      <th>description     </tr>
 * <tr><td>2022.04.7        <td>1.0.0       <td>yyang       <td>initial version </tr>
 * </tr>
 */
 

#include <assert.h>

#include <event2/event.h>
#include <event2/thread.h>

#include "eventloop.h"


using namespace std;


EventLoop *EventLoop::_instance = nullptr;


EventLoop::EventLoop()
{
    // if we already had the instance, assert
    assert(!_instance);

    // make sure the multi thread safe
    evthread_use_pthreads();
    // create a new `event_base`
    _event = event_base_new();
    // get the instance
    _instance = this;
}

EventLoop::~EventLoop()
{
    // clear the instance's pointer
    _instance = nullptr;
    // release the `event_base`
    event_base_free(_event);
    // turn off the libevent, but we need to release what libevent return by ourself
    libevent_global_shutdown();
}

int EventLoop::exec()
{
    // return if exit
    _exit_code = -1;
    // store the exit flag to the atomic value, and we don't form the memory order in this thread
    _exit.store(false, memory_order_release);

    // until the exit flag is true, loop
    // and we must acquire exit flag at first
    while (!_exit.load(memory_order_acquire))
    {
        _dispatch_calls();
        // execute the loop in libevent, until we use `event_base_loopbreak()` or `event_base_loopexit()`
        event_base_loop(_event, EVLOOP_NO_EXIT_ON_EMPTY);
    }
    return _exit_code;
}

void EventLoop::exit(int code)
{
    // set the exit code
    _exit_code = code;
    // set the atomic exit flag to be true, don't form the memory order in this thread
    _exit.store(true, memory_order_release);
    // then break the `event_base_loop()`
    _interrupt();
}

void EventLoop::_interrupt()
{
    // break the `event_base_loop()`
    event_base_loopbreak(_event);
}

void EventLoop::_timeout_triggered(int fd, short event, void *arg)
{
    // get this class's object and exit
    EventLoop *self = static_cast<EventLoop*>(arg);
    self->exit();
}

void EventLoop::timeout(int sec)
{
    // the timer event
    struct event *ev;
    struct timeval tv;

    // set the timer event
    tv.tv_sec = sec;
    tv.tv_usec = 0;
    ev = evtimer_new(_event, &_timeout_triggered, this);
    evtimer_add(ev, &tv);
}

void EventLoop::call_later(const function<void()> &func)
{
    // use the `mutex` to lock and add the functions we need to call later to vector
    {
        unique_lock<mutex> locker(_lock);
        _calls.push_back(func);
    }
    // then break the `event_base_loop()`
    _interrupt();
}

void EventLoop::_dispatch_calls()
{
    unique_lock<mutex> locker(_lock);

    for (auto i = _calls.begin(); i != _calls.end(); )
    {
        function<void()> call = move(*i);
        i = _calls.erase(i);
        locker.unlock();
        call();
        locker.lock();
    }
}