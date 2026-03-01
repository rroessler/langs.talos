/// Shell Modules
#include "shell/upgrade/action.hpp"

#if $_PLATFORM_WINDOWS

//  PRIVATE METHODS  //

void Shell::Upgrade::Action::m_remove() {
    // we just execute the underlying "remove.ps1" script
    auto script = Talos::Product::scripts() / "remove.ps1";

    // prepare the process builder to be used now
    auto builder = XPC::Shell::Builder("powershell")
                       .cin(XPC::Pipe::Direct::IGNORE)
                       .cout(XPC::Pipe::Direct::IGNORE)
                       .cerr(XPC::Pipe::Direct::IGNORE)
                       .argv({ "-File", script.string(), "-Schedule", "-Location", m_installation().string() });

    // and execute the incoming process
    XPC::Core::Child(builder).wait();
}

#endif
