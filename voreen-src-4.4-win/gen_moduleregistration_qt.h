// WARNING: This file is generated and will be overwritten on next cmake run!
#include "voreen/qt/voreenapplicationqt.h"

// include qt module class headers
#include "C:/sharefolder/voreen-src-4.4-win/modules/base/basemoduleqt.h"
#include "C:/sharefolder/voreen-src-4.4-win/modules/core/coremoduleqt.h"
#include "C:/sharefolder/voreen-src-4.4-win/modules/dynamicglsl/dynamicglslmoduleqt.h"
#include "C:/sharefolder/voreen-src-4.4-win/modules/plotting/plottingmoduleqt.h"
#include "C:/sharefolder/voreen-src-4.4-win/modules/randomwalker/randomwalkermoduleqt.h"
#include "C:/sharefolder/voreen-src-4.4-win/modules/stereoscopy/stereoscopymoduleqt.h"

namespace voreen {

// instantiate qt module classes
void registerAllQtModules(VoreenApplicationQt* vappQt) {
    VoreenModuleQt* module;

    module = new BaseModuleQt("modules/base");
    vappQt->registerQtModule(module);

    module = new CoreModuleQt("modules/core");
    vappQt->registerQtModule(module);

    module = new DynamicGLSLModuleQt("modules/dynamicglsl");
    vappQt->registerQtModule(module);

    module = new PlottingModuleQt("modules/plotting");
    vappQt->registerQtModule(module);

    module = new RandomWalkerModuleQt("modules/randomwalker");
    vappQt->registerQtModule(module);

    module = new StereoscopyModuleQt("modules/stereoscopy");
    vappQt->registerQtModule(module);

}

} // namespace
