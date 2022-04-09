/**
 * @file                    eventloop.h
 * @author                  yyang yyangoO@outlook.com & sjtu_yangyang@sjtu.edu.cn
 * @version                 1.0.0
 * @date                    7-APR-2022
 * @section                 description
 *                          event loop header
 * @section                 logs
 * <table>
 * <tr><th>date             <th>version     <th>author      <th>description     </tr>
 * <tr><td>2022.04.7        <td>1.0.0       <td>yyang       <td>initial version </tr>
 * </tr>
 */


#ifndef _ENVETLOOP_H
#define _ENVETLOOP_H


#include <atomic>
#include <functional>
#include <list>
#include <mutex>


/**
 * @brief event base
 * The event base.
 */
struct event_base;


/**
 * @brief event loop
 * This class is the event loop.
 */
class EventLoop
{
private:
    static EventLoop *_instance;
    struct event_base *_event;
    std::atomic<bool> _exit;
    int _exit_code;
    std::list<std::function<void()>> _calls;
    std::mutex _lock;

    void _interrupt();
    void _dispatch_calls();
    static void _timeout_triggered(int fd, short event, void *arg);

public:
    /**
     * @brief constructor
     * This constructor function.
     */
    EventLoop();
    /**
     * @brief destructor
     * This destructor function.
     */
    ~EventLoop();
    /**
     * @brief execution of event loop
     * This function execute the event loop. 
     */
    int exec();
    /**
     * @brief exit
     * This function exit the loop. 
     * @param code = 0      the exit code
     */
    void exit(int code = 0);
    /**
     * @brief set the timeout second
     * This function set the timeout second. 
     * @param sec       the timeout second
     */
    void timeout(int sec);
    /**
     * @brief store the function we need to call later
     * This function tore the function we need to call later.  
     * @param &func     the function
     */
    void call_later(const std::function<void()> &func);
};


#endif // _ENVETLOOP_H