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

#ifndef VRN_TRANSFUNCPROPERTYWIDGET_H
#define VRN_TRANSFUNCPROPERTYWIDGET_H

#include "voreen/qt/widgets/property/qpropertywidgetwitheditorwindow.h"
#include "voreen/core/datastructures/volume/volume.h"

class QToolButton;
namespace tgt {
    class QtCanvas;
}

namespace voreen {

class TransFuncPlugin;
class VoreenToolWindow;
class TransFuncProperty;
class TransFunc1DHistogramPainter;
class DoubleSlider;

class TransFuncPropertyWidget : public QPropertyWidgetWithEditorWindow, public VolumeObserver {
Q_OBJECT
public:
    TransFuncPropertyWidget(TransFuncProperty* prop, QWidget* parent = 0);

    virtual void disconnect();

    /// Returns the null pointer, since this widget does not need a separate label.
    virtual CustomLabel* getNameLabel() const;

    // VolumeObserver methods:
    virtual void volumeDelete(const VolumeBase* source);
    virtual void volumeChange(const VolumeBase* source);
    virtual void derivedDataThreadFinished(const VolumeBase* source, const VolumeDerivedData* derivedData);

public slots:
    void setProperty();
    void zoomIn();
    void zoomOut();
    void resetZoom();
    void fitToData();
    void slidersMoved(float min, float max);
    void populateLoadTemplateMenu();
    void loadTemplate(QAction* action);
    void populateLoadWindowMenu();
    void loadWindow(QAction* action);
    virtual void showNameLabel(bool);
    /**
     * Starts or stops the interaction mode.
     *
     * @param on interaction mode on or off?
     */
    void toggleInteractionMode(bool on);

    void setUseAlpha(bool on);

protected:
    virtual QWidget* createEditorWindowWidget();
    virtual void customizeEditorWindow();
    virtual Property* getProperty();
    void adaptSliderToZoom();

    TransFuncPlugin* plugin_;
    TransFuncProperty* property_;

    tgt::QtCanvas* textureCanvas_;              ///< canvas that is used for displaying the texture of the transfer function
    TransFunc1DHistogramPainter* texturePainter_;   ///< painter for texture display of transfer function
    DoubleSlider* doubleSlider_;            ///< 2 slider for adjusting the thresholds
    bool ignoreSlideUpdates_;
    bool viewInitialized_;

    QToolButton* editBt_;
    QToolButton* useAlphaBt_;
    QToolButton* templateBt_;
    QToolButton* windowBt_;
    QMenu* loadTemplateMenu_;
    QMenu* loadWindowMenu_;
    QToolButton* zoomInBt_;
    QToolButton* zoomOutBt_;
    QToolButton* zoomResetBt_;

protected slots:
    virtual void updateFromPropertySlot();

};

} // namespace

#endif // VRN_COMPACTTRANSFUNCPROPERTYWIDGET_H
