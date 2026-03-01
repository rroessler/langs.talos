/// Forge Modules
#include "forge/bundle/fuse.hpp"

//  PROPERTIES  //

#define XX_FUSE(N, F, ...) "TALOS_FUSE_" #N "/" F ":0"
#define XX_VIEW(N, F, ...) $_FWD(XJCT::Sentinel::View N = XJCT::Sentinel::Fuse<XX_FUSE(N, F)>().view(), Forge::Fuse)
FORGE_XX_FUSES_LIST(XX_VIEW)
#undef XX_VIEW
#undef XX_FUSE
