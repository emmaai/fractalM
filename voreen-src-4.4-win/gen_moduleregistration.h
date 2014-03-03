// WARNING: This file is generated and will be overwritten on next cmake run!
#include "voreen/core/voreenapplication.h"

// include core module class headers
#include "C:/sharefolder/voreen-src-4.4-win/modules/advancedlighting/advancedlightingmodule.h"
#include "C:/sharefolder/voreen-src-4.4-win/modules/base/basemodule.h"
#include "C:/sharefolder/voreen-src-4.4-win/modules/connexe/connexemodule.h"
#include "C:/sharefolder/voreen-src-4.4-win/modules/core/coremodule.h"
#include "C:/sharefolder/voreen-src-4.4-win/modules/devil/devilmodule.h"
#include "C:/sharefolder/voreen-src-4.4-win/modules/dynamicglsl/dynamicglslmodule.h"
#include "C:/sharefolder/voreen-src-4.4-win/modules/flowreen/flowreenmodule.h"
#include "C:/sharefolder/voreen-src-4.4-win/modules/plotting/plottingmodule.h"
#include "C:/sharefolder/voreen-src-4.4-win/modules/pvm/pvmmodule.h"
#include "C:/sharefolder/voreen-src-4.4-win/modules/randomwalker/randomwalkermodule.h"
#include "C:/sharefolder/voreen-src-4.4-win/modules/segy/segymodule.h"
#include "C:/sharefolder/voreen-src-4.4-win/modules/staging/stagingmodule.h"
#include "C:/sharefolder/voreen-src-4.4-win/modules/stereoscopy/stereoscopymodule.h"
#include "C:/sharefolder/voreen-src-4.4-win/modules/volumelabeling/volumelabelingmodule.h"
#include "C:/sharefolder/voreen-src-4.4-win/modules/zip/zipmodule.h"

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
