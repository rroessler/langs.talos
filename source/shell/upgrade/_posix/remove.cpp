/// Shell Modules
#include "shell/upgrade/action.hpp"

#if $_PLATFORM_POSIX

//  PRIVATE METHODS  //

void Shell::Upgrade::Action::m_remove() { std::filesystem::remove_all(m_installation()); }

#endif
