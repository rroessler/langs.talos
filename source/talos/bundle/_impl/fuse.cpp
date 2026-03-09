/// Talos Modules
#include "talos/bundle/fuse.hpp"

//  PROPERTIES  //

#define XX_FUSE(N, F, ...) "TALOS_FUSE_" #N "/" F ":0"
#define XX_VIEW(N, F, ...) $_FWD(Talos::Fuse, XJCT::Sentinel::View N = XJCT::Sentinel::Fuse<XX_FUSE(N, F)>().view())
TALOS_XX_FUSES_LIST(XX_VIEW)
#undef XX_VIEW
#undef XX_FUSE
