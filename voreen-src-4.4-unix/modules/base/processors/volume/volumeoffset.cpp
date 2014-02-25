/***********************************************************************************
 *                                                                                 *
 * Voreen - The Volume Rendering Engine                                            *
 *                                                                                 *
 * Copyright (C) 2005-2013 University of Muenster, Germany.                        *
 * Visualization and Computer Graphics Group <http://viscg.uni-muenster.de>        *
 * For a list of authors please refer to the file "CREDITS.txt".                   *
 *                                                                                 *
 * This file is part of the Voreen software package. Voreen is free software:      *
 * you can redistribute it and/or modify it under the terms of the GNU General     *
 * Public License version 2 as published by the Free Software Foundation.          *
 *                                                                                 *
 * Voreen is distributed in the hope that it will be useful, but WITHOUT ANY       *
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR   *
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.      *
 *                                                                                 *
 * You should have received a copy of the GNU General Public License in the file   *
 * "LICENSE.txt" along with this file. If not, see <http://www.gnu.org/licenses/>. *
 *                                                                                 *
 * For non-commercial academic use see the license exception specified in the file *
 * "LICENSE-academic.txt". To get information about commercial licensing please    *
 * contact the authors.                                                            *
 *                                                                                 *
 ***********************************************************************************/

#include "volumeoffset.h"
#include "voreen/core/datastructures/volume/volumeram.h"
#include "voreen/core/datastructures/volume/volumedecorator.h"
#include "voreen/core/datastructures/meta/primitivemetadata.h"

namespace voreen {

const std::string VolumeOffset::loggerCat_("voreen.base.VolumeOffset");

VolumeOffset::VolumeOffset()
    : VolumeProcessor(),
    inport_(Port::INPORT, "volumehandle.input", "Volume Input"),
    outport_(Port::OUTPORT, "volumehandle.output", "Volume Output", false),
    enableProcessing_("enabled", "Enable", false),
    offset_("offset", "Offset", tgt::vec3(0.0f), tgt::vec3(-100.0), tgt::vec3(100.0))
{
    addPort(inport_);
    addPort(outport_);

    addProperty(enableProcessing_);
    addProperty(offset_);
}

Processor* VolumeOffset::create() const {
    return new VolumeOffset();
}

void VolumeOffset::process() {
    if (!enableProcessing_.get()) {
        outport_.setData(inport_.getData(), false);
    }
    else {
        VolumeBase* outputVolume =
            new VolumeDecoratorReplaceOffset(inport_.getData(), offset_.get());
        outport_.setData(outputVolume);
    }
}

}   // namespace
