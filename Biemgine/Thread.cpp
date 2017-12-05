#include "stdafx.h"
#include "Thread.h"
#include <SDL_thread.h>

namespace biemgine {

    struct sdl_thread_wrapper : Thread::wrapper {
        SDL_Thread* thread = nullptr;

        sdl_thread_wrapper()
        { }

        sdl_thread_wrapper(SDL_Thread* thread)
            :thread(thread)
        { }

        ~sdl_thread_wrapper() {
            if(thread != nullptr)
                SDL_DetachThread(thread);
        }
    };

    Thread::Thread(std::string name, Thread::function function)
        :threadName(std::move(name))
    {
        thread = std::move(sdl_thread_wrapper{
            SDL_CreateThread(function, threadName.c_str(), nullptr)
        });
    }
}
