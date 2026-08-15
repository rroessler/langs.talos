/// Vendor Includes
#include <boost/interprocess/detail/os_thread_functions.hpp>

//  PUBLIC METHODS  //

intptr_t $::System::pid() { return boost::interprocess::ipcdetail::get_current_process_id(); }
