set(klusters_SRCS
    autosavethread.cpp
    baseframe.cpp
    channellist.cpp
    clusterPalette.cpp
    clusterinformationdialog.cpp
    clustersprovider.cpp
    clusterview.cpp
    configuration.cpp
    correlationthread.cpp
    correlationview.cpp
    data.cpp
    dataprovider.cpp
    errormatrixthread.cpp
    errormatrixview.cpp
    eventsprovider.cpp
    groupingassistant.cpp
    klusters.cpp
    klustersdoc.cpp
    klustersview.cpp
    klustersxmlreader.cpp
    main.cpp
    minmaxthread.cpp
    pair.cpp
    parameterxmlmodifier.cpp
    prefclusterview.cpp
    prefdialog.cpp
    prefgeneral.cpp
    prefwaveformview.cpp
    processlinemaker.cpp
    processwidget.cpp
    spinbox.cpp
    savethread.cpp
    sortabletable.cpp
    tags.cpp
    tracesprovider.cpp
    traceview.cpp
    tracewidget.cpp
    viewwidget.cpp
    waveformthread.cpp
    waveformview.cpp
    prefgenerallayout.cpp
    prefwaveformviewlayout.cpp
    prefclusterviewlayout.cpp
)

qt_add_resources(klusters_SRCS klusters-cursors.qrc klusters-icons.qrc)

set(klusters_UI prefwaveformviewlayout.ui prefgenerallayout.ui prefclusterviewlayout.ui)
qt_wrap_ui(klusters_SRCS ${klusters_UI})

if(APPBUNDLE)
    add_executable(klusters MACOSX_BUNDLE ${klusters_SRCS})
else()
    add_executable(klusters WIN32 ${klusters_SRCS})
endif()

target_link_libraries(klusters PRIVATE neurosuite::neurosuite Qt6::Widgets Qt6::PrintSupport Qt6::Xml)

# Bundle the Qt runtime on Windows and macOS at install time.
if(WIN32 OR APPBUNDLE)
    qt_generate_deploy_app_script(
        TARGET klusters
        OUTPUT_SCRIPT KLUSTERS_DEPLOY_SCRIPT
        NO_UNSUPPORTED_PLATFORM_ERROR
    )
    install(SCRIPT ${KLUSTERS_DEPLOY_SCRIPT})
endif()

if(APPBUNDLE)
    install(TARGETS klusters BUNDLE DESTINATION ".")
else()
    install(TARGETS klusters RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
endif()

if(UNIX AND NOT APPLE)
    set(APP_ID io.github.neurosuite.Klusters)
    foreach(SIZE 16 22 32 48 64)
        install(FILES hi${SIZE}-app-klusters.png
                DESTINATION ${CMAKE_INSTALL_DATADIR}/icons/hicolor/${SIZE}x${SIZE}/apps
                RENAME klusters.png)
    endforeach()
    install(FILES klusters.desktop
            DESTINATION ${CMAKE_INSTALL_DATADIR}/applications
            RENAME ${APP_ID}.desktop)
    install(FILES ${APP_ID}.metainfo.xml
            DESTINATION ${CMAKE_INSTALL_DATADIR}/metainfo)
endif()
