/// Shell Modules
#include "shell/upgrade/action.hpp"

#if $_PLATFORM_WINDOWS

//  PRIVATE METHODS  //

void Shell::Upgrade::Action::m_remove() {
    // prepare the deletion handler
    auto command = "\"timeout /t 1 & rmdir /s /q " + m_installation().string() + "\"";

    // prepare the process builder to be used now
    auto builder = XPC::Shell::Builder(*XPC::Shell::Path::binary())
                       .cin(XPC::Pipe::Direct::IGNORE)
                       .cout(XPC::Pipe::Direct::IGNORE)
                       .cerr(XPC::Pipe::Direct::IGNORE)
                       .argv({ "/c", "start", "/b", "/min", "cmd", "/c", command });

    // and execute the incoming process
    XPC::Core::Child(builder).wait();
}

#endif
