// WARNING: This file is generated and will be overwritten on next cmake run!
#include "voreen/core/voreenapplication.h"

// include core module class headers
#include "/home/emma/code/gitrepo/voreen-src-4.3-unix/modules/advancedlighting/advancedlightingmodule.h"
#include "/home/emma/code/gitrepo/voreen-src-4.3-unix/modules/base/basemodule.h"
#include "/home/emma/code/gitrepo/voreen-src-4.3-unix/modules/connexe/connexemodule.h"
#include "/home/emma/code/gitrepo/voreen-src-4.3-unix/modules/core/coremodule.h"
#include "/home/emma/code/gitrepo/voreen-src-4.3-unix/modules/devil/devilmodule.h"
#include "/home/emma/code/gitrepo/voreen-src-4.3-unix/modules/dynamicglsl/dynamicglslmodule.h"
#include "/home/emma/code/gitrepo/voreen-src-4.3-unix/modules/flowreen/flowreenmodule.h"
#include "/home/emma/code/gitrepo/voreen-src-4.3-unix/modules/opencl/openclmodule.h"
#include "/home/emma/code/gitrepo/voreen-src-4.3-unix/modules/openmp/openmpmodule.h"
#include "/home/emma/code/gitrepo/voreen-src-4.3-unix/modules/plotting/plottingmodule.h"
#include "/home/emma/code/gitrepo/voreen-src-4.3-unix/modules/pvm/pvmmodule.h"
#include "/home/emma/code/gitrepo/voreen-src-4.3-unix/modules/randomwalker/randomwalkermodule.h"
#include "/home/emma/code/gitrepo/voreen-src-4.3-unix/modules/segy/segymodule.h"
#include "/home/emma/code/gitrepo/voreen-src-4.3-unix/modules/staging/stagingmodule.h"
#include "/home/emma/code/gitrepo/voreen-src-4.3-unix/modules/stereoscopy/stereoscopymodule.h"
#include "/home/emma/code/gitrepo/voreen-src-4.3-unix/modules/volumelabeling/volumelabelingmodule.h"
#include "/home/emma/code/gitrepo/voreen-src-4.3-unix/modules/zip/zipmodule.h"

namespace voreen {

// instantiate core module classes
void registerAllModules(VoreenApplication* vapp) {
    VoreenModule* module;

    module = new AdvancedLightingModule("modules/advancedlighting");
    vapp->registerModule(module);

    module = new BaseModule("modules/base");
    vapp->registerModule(module);

    module = new ConnexeModule("modules/connexe");
    vapp->registerModule(module);

    module = new CoreModule("modules/core");
    vapp->registerModule(module);

    module = new DevILModule("modules/devil");
    vapp->registerModule(module);

    module = new DynamicGLSLModule("modules/dynamicglsl");
    vapp->registerModule(module);

    module = new FlowreenModule("modules/flowreen");
    vapp->registerModule(module);

    module = new OpenCLModule("modules/opencl");
    vapp->registerModule(module);

    module = new OpenMPModule("modules/openmp");
    vapp->registerModule(module);

    module = new PlottingModule("modules/plotting");
    vapp->registerModule(module);

    module = new PVMModule("modules/pvm");
    vapp->registerModule(module);

    module = new RandomWalkerModule("modules/randomwalker");
    vapp->registerModule(module);

    module = new SEGYModule("modules/segy");
    vapp->registerModule(module);

    module = new StagingModule("modules/staging");
    vapp->registerModule(module);

    module = new StereoscopyModule("modules/stereoscopy");
    vapp->registerModule(module);

    module = new VolumeLabelingModule("modules/volumelabeling");
    vapp->registerModule(module);

    module = new ZIPModule("modules/zip");
    vapp->registerModule(module);

}

} // namespace
