#-------------------------------------------------
#
# Project created by QtCreator 2021-12-13T22:15:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RealTime
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    main.cpp \
    mainwindow.cpp \
    Simd/SimdAvx1SquaredDifferenceSum.cpp \
    Simd/SimdAvx1Svm.cpp \
    Simd/SimdAvx2AbsDifferenceSum.cpp \
    Simd/SimdAvx2AbsGradientSaturatedSum.cpp \
    Simd/SimdAvx2AddFeatureDifference.cpp \
    Simd/SimdAvx2AlphaBlending.cpp \
    Simd/SimdAvx2Background.cpp \
    Simd/SimdAvx2BgraToGray.cpp \
    Simd/SimdAvx2BgraToYuv.cpp \
    Simd/SimdAvx2BgrToBgra.cpp \
    Simd/SimdAvx2BgrToGray.cpp \
    Simd/SimdAvx2BgrToYuv.cpp \
    Simd/SimdAvx2Binarization.cpp \
    Simd/SimdAvx2Conditional.cpp \
    Simd/SimdAvx2DeinterleaveUv.cpp \
    Simd/SimdAvx2EdgeBackground.cpp \
    Simd/SimdAvx2Fill.cpp \
    Simd/SimdAvx2GaussianBlur3x3.cpp \
    Simd/SimdAvx2GrayToBgr.cpp \
    Simd/SimdAvx2GrayToBgra.cpp \
    Simd/SimdAvx2Histogram.cpp \
    Simd/SimdAvx2Hog.cpp \
    Simd/SimdAvx2Interference.cpp \
    Simd/SimdAvx2InterleaveUv.cpp \
    Simd/SimdAvx2Laplace.cpp \
    Simd/SimdAvx2Lbp.cpp \
    Simd/SimdAvx2MedianFilter.cpp \
    Simd/SimdAvx2Operation.cpp \
    Simd/SimdAvx2ReduceGray2x2.cpp \
    Simd/SimdAvx2ReduceGray3x3.cpp \
    Simd/SimdAvx2ReduceGray4x4.cpp \
    Simd/SimdAvx2ReduceGray5x5.cpp \
    Simd/SimdAvx2Reorder.cpp \
    Simd/SimdAvx2ResizeBilinear.cpp \
    Simd/SimdAvx2Segmentation.cpp \
    Simd/SimdAvx2ShiftBilinear.cpp \
    Simd/SimdAvx2Sobel.cpp \
    Simd/SimdAvx2SquaredDifferenceSum.cpp \
    Simd/SimdAvx2Statistic.cpp \
    Simd/SimdAvx2StretchGray2x2.cpp \
    Simd/SimdAvx2Texture.cpp \
    Simd/SimdAvx2YuvToBgr.cpp \
    Simd/SimdAvx2YuvToBgra.cpp \
    Simd/SimdAvx2YuvToHue.cpp \
    Simd/SimdBaseAbsDifferenceSum.cpp \
    Simd/SimdBaseAbsGradientSaturatedSum.cpp \
    Simd/SimdBaseAddFeatureDifference.cpp \
    Simd/SimdBaseAlphaBlending.cpp \
    Simd/SimdBaseBackground.cpp \
    Simd/SimdBaseBayerToBgr.cpp \
    Simd/SimdBaseBayerToBgra.cpp \
    Simd/SimdBaseBgraToBayer.cpp \
    Simd/SimdBaseBgraToBgr.cpp \
    Simd/SimdBaseBgraToGray.cpp \
    Simd/SimdBaseBgraToYuv.cpp \
    Simd/SimdBaseBgrToBayer.cpp \
    Simd/SimdBaseBgrToBgra.cpp \
    Simd/SimdBaseBgrToGray.cpp \
    Simd/SimdBaseBgrToHsl.cpp \
    Simd/SimdBaseBgrToHsv.cpp \
    Simd/SimdBaseBgrToYuv.cpp \
    Simd/SimdBaseBinarization.cpp \
    Simd/SimdBaseConditional.cpp \
    Simd/SimdBaseCopy.cpp \
    Simd/SimdBaseCrc32.cpp \
    Simd/SimdBaseDeinterleaveUv.cpp \
    Simd/SimdBaseEdgeBackground.cpp \
    Simd/SimdBaseFill.cpp \
    Simd/SimdBaseGaussianBlur3x3.cpp \
    Simd/SimdBaseGrayToBgr.cpp \
    Simd/SimdBaseGrayToBgra.cpp \
    Simd/SimdBaseHistogram.cpp \
    Simd/SimdBaseHog.cpp \
    Simd/SimdBaseIntegral.cpp \
    Simd/SimdBaseInterference.cpp \
    Simd/SimdBaseInterleaveUv.cpp \
    Simd/SimdBaseLaplace.cpp \
    Simd/SimdBaseLbp.cpp \
    Simd/SimdBaseMedianFilter.cpp \
    Simd/SimdBaseOperation.cpp \
    Simd/SimdBaseReduceGray2x2.cpp \
    Simd/SimdBaseReduceGray3x3.cpp \
    Simd/SimdBaseReduceGray4x4.cpp \
    Simd/SimdBaseReduceGray5x5.cpp \
    Simd/SimdBaseReorder.cpp \
    Simd/SimdBaseResizeBilinear.cpp \
    Simd/SimdBaseSegmentation.cpp \
    Simd/SimdBaseShiftBilinear.cpp \
    Simd/SimdBaseSobel.cpp \
    Simd/SimdBaseSquaredDifferenceSum.cpp \
    Simd/SimdBaseStatistic.cpp \
    Simd/SimdBaseStretchGray2x2.cpp \
    Simd/SimdBaseSvm.cpp \
    Simd/SimdBaseTexture.cpp \
    Simd/SimdBaseYuvToBgr.cpp \
    Simd/SimdBaseYuvToBgra.cpp \
    Simd/SimdBaseYuvToHsl.cpp \
    Simd/SimdBaseYuvToHsv.cpp \
    Simd/SimdBaseYuvToHue.cpp \
    Simd/SimdLib.cpp \
    Simd/SimdSse1SquaredDifferenceSum.cpp \
    Simd/SimdSse1Svm.cpp \
    Simd/SimdSse2AbsDifferenceSum.cpp \
    Simd/SimdSse2AbsGradientSaturatedSum.cpp \
    Simd/SimdSse2AddFeatureDifference.cpp \
    Simd/SimdSse2AlphaBlending.cpp \
    Simd/SimdSse2Background.cpp \
    Simd/SimdSse2BgraToGray.cpp \
    Simd/SimdSse2BgraToYuv.cpp \
    Simd/SimdSse2BgrToBgra.cpp \
    Simd/SimdSse2BgrToGray.cpp \
    Simd/SimdSse2Binarization.cpp \
    Simd/SimdSse2Conditional.cpp \
    Simd/SimdSse2DeinterleaveUv.cpp \
    Simd/SimdSse2EdgeBackground.cpp \
    Simd/SimdSse2Fill.cpp \
    Simd/SimdSse2GaussianBlur3x3.cpp \
    Simd/SimdSse2GrayToBgra.cpp \
    Simd/SimdSse2Histogram.cpp \
    Simd/SimdSse2Hog.cpp \
    Simd/SimdSse2Interference.cpp \
    Simd/SimdSse2InterleaveUv.cpp \
    Simd/SimdSse2Laplace.cpp \
    Simd/SimdSse2Lbp.cpp \
    Simd/SimdSse2MedianFilter.cpp \
    Simd/SimdSse2Operation.cpp \
    Simd/SimdSse2ReduceGray2x2.cpp \
    Simd/SimdSse2ReduceGray3x3.cpp \
    Simd/SimdSse2ReduceGray4x4.cpp \
    Simd/SimdSse2ReduceGray5x5.cpp \
    Simd/SimdSse2Reorder.cpp \
    Simd/SimdSse2ResizeBilinear.cpp \
    Simd/SimdSse2Segmentation.cpp \
    Simd/SimdSse2ShiftBilinear.cpp \
    Simd/SimdSse2Sobel.cpp \
    Simd/SimdSse2SquaredDifferenceSum.cpp \
    Simd/SimdSse2Statistic.cpp \
    Simd/SimdSse2StretchGray2x2.cpp \
    Simd/SimdSse2Texture.cpp \
    Simd/SimdSse2YuvToBgra.cpp \
    Simd/SimdSse2YuvToHue.cpp \
    Simd/SimdSse41Segmentation.cpp \
    Simd/SimdSse42Crc32.cpp \
    Simd/SimdSsse3AlphaBlending.cpp \
    Simd/SimdSsse3BgraToBayer.cpp \
    Simd/SimdSsse3BgraToBgr.cpp \
    Simd/SimdSsse3BgraToYuv.cpp \
    Simd/SimdSsse3BgrToBayer.cpp \
    Simd/SimdSsse3BgrToBgra.cpp \
    Simd/SimdSsse3BgrToGray.cpp \
    Simd/SimdSsse3BgrToYuv.cpp \
    Simd/SimdSsse3GaussianBlur3x3.cpp \
    Simd/SimdSsse3GrayToBgr.cpp \
    Simd/SimdSsse3Laplace.cpp \
    Simd/SimdSsse3ReduceGray2x2.cpp \
    Simd/SimdSsse3ReduceGray4x4.cpp \
    Simd/SimdSsse3Reorder.cpp \
    Simd/SimdSsse3ResizeBilinear.cpp \
    Simd/SimdSsse3Sobel.cpp \
    Simd/SimdSsse3SquaredDifferenceSum.cpp \
    Simd/SimdSsse3Texture.cpp \
    Simd/SimdSsse3YuvToBgr.cpp \
    Simd/SimdVmxAbsDifferenceSum.cpp \
    Simd/SimdVmxAbsGradientSaturatedSum.cpp \
    Simd/SimdVmxAddFeatureDifference.cpp \
    Simd/SimdVmxAlphaBlending.cpp \
    Simd/SimdVmxBackground.cpp \
    Simd/SimdVmxBgraToBayer.cpp \
    Simd/SimdVmxBgraToBgr.cpp \
    Simd/SimdVmxBgraToGray.cpp \
    Simd/SimdVmxBgraToYuv.cpp \
    Simd/SimdVmxBgrToBayer.cpp \
    Simd/SimdVmxBgrToBgra.cpp \
    Simd/SimdVmxBgrToGray.cpp \
    Simd/SimdVmxBgrToYuv.cpp \
    Simd/SimdVmxBinarization.cpp \
    Simd/SimdVmxConditional.cpp \
    Simd/SimdVmxDeinterleaveUv.cpp \
    Simd/SimdVmxEdgeBackground.cpp \
    Simd/SimdVmxFill.cpp \
    Simd/SimdVmxGaussianBlur3x3.cpp \
    Simd/SimdVmxGrayToBgr.cpp \
    Simd/SimdVmxGrayToBgra.cpp \
    Simd/SimdVmxHistogram.cpp \
    Simd/SimdVmxInterference.cpp \
    Simd/SimdVmxInterleaveUv.cpp \
    Simd/SimdVmxLaplace.cpp \
    Simd/SimdVmxLbp.cpp \
    Simd/SimdVmxMedianFilter.cpp \
    Simd/SimdVmxOperation.cpp \
    Simd/SimdVmxReduceGray2x2.cpp \
    Simd/SimdVmxReduceGray3x3.cpp \
    Simd/SimdVmxReduceGray4x4.cpp \
    Simd/SimdVmxReduceGray5x5.cpp \
    Simd/SimdVmxReorder.cpp \
    Simd/SimdVmxResizeBilinear.cpp \
    Simd/SimdVmxSegmentation.cpp \
    Simd/SimdVmxShiftBilinear.cpp \
    Simd/SimdVmxSobel.cpp \
    Simd/SimdVmxSquaredDifferenceSum.cpp \
    Simd/SimdVmxStatistic.cpp \
    Simd/SimdVmxStretchGray2x2.cpp \
    Simd/SimdVmxTexture.cpp \
    Simd/SimdVmxYuvToBgr.cpp \
    Simd/SimdVmxYuvToBgra.cpp \
    Simd/SimdVsxHog.cpp \
    Simd/SimdVsxSquaredDifferenceSum.cpp \
    Simd/SimdVsxSvm.cpp \
    Simd/SimdVsxYuvToHue.cpp \
    drawingview.cpp \
    rtplot.cpp


HEADERS += \
    mainwindow.h \
    Simd/SimdAllocator.hpp \
    Simd/SimdAvx1.h \
    Simd/SimdAvx2.h \
    Simd/SimdBase.h \
    Simd/SimdCompare.h \
    Simd/SimdConfig.h \
    Simd/SimdConst.h \
    Simd/SimdConversion.h \
    Simd/SimdDefs.h \
    Simd/SimdEnable.h \
    Simd/SimdExtract.h \
    Simd/SimdFrame.hpp \
    Simd/SimdHelp.h \
    Simd/SimdInit.h \
    Simd/SimdLib.h \
    Simd/SimdLib.hpp \
    Simd/SimdLoad.h \
    Simd/SimdLog.h \
    Simd/SimdMath.h \
    Simd/SimdMemory.h \
    Simd/SimdPixel.hpp \
    Simd/SimdPoint.hpp \
    Simd/SimdPyramid.hpp \
    Simd/SimdRectangle.hpp \
    Simd/SimdSet.h \
    Simd/SimdSse1.h \
    Simd/SimdSse2.h \
    Simd/SimdSse41.h \
    Simd/SimdSse42.h \
    Simd/SimdSsse3.h \
    Simd/SimdStore.h \
    Simd/SimdVersion.h \
    Simd/SimdView.hpp \
    Simd/SimdVmx.h \
    Simd/SimdVsx.h \
    drawingview.h \
    rtplot.h



FORMS += \
        mainwindow.ui

unix:!macx: LIBS += -L$$PWD/FreeType2/lib/ -lfreetype

INCLUDEPATH += $$PWD/FreeType2/include/freetype2
DEPENDPATH += $$PWD/FreeType2/include/freetype2

unix:!macx: PRE_TARGETDEPS += $$PWD/FreeType2/lib/libfreetype.a

QMAKE_CXXFLAGS += -mavx2
