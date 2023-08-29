QT       += core gui network printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -Wa,-mbig-obj

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    lib/koshi8bit/easyliving.cpp \
    lib/koshi8bit/errorhandler/errorhandler.cpp \
    lib/koshi8bit/log/channel.cpp \
    lib/koshi8bit/log/channelbool.cpp \
    lib/koshi8bit/log/channeldouble.cpp \
    lib/koshi8bit/log/channelqstring.cpp \
    lib/koshi8bit/log/excel/excel.cpp \
    lib/koshi8bit/log/excel/excelfile.cpp \
    lib/koshi8bit/log/excel/excelsimple.cpp \
    lib/koshi8bit/log/excel/timelog/timelog.cpp \
    lib/koshi8bit/log/log.cpp \
    lib/koshi8bit/log/simple/simplelog.cpp \
    lib/koshi8bit/log/sql/sql.cpp \
    lib/koshi8bit/operationresult.cpp \
    lib/koshi8bit/qdebuglogger/qdebuglogger.cpp \
    lib/koshi8bit/settings/settings.cpp \
    lib/koshi8bit/shared-variable/tcp/netvars/initnvclient.cpp \
    lib/koshi8bit/shared-variable/tcp/netvars/initnvserver.cpp \
    lib/koshi8bit/shared-variable/tcp/netvars/netclient.cpp \
    lib/koshi8bit/shared-variable/tcp/netvars/netvar.cpp \
    lib/koshi8bit/shared-variable/tcp/netvars/netvarbase.cpp \
    lib/koshi8bit/shared-variable/tcp/netvars/varscontainer.cpp \
    lib/koshi8bit/shared-variable/udp/shared-variable.cpp \
    lib/koshi8bit/ui/double_spin_box_cursor/doublespinboxcursor.cpp \
    lib/koshi8bit/ui/faults/fault.cpp \
    lib/koshi8bit/ui/faults/faultswidget.cpp \
    lib/koshi8bit/ui/gradientlineedit/gradientlineedit.cpp \
    lib/koshi8bit/ui/gradientlineedit/minmax.cpp \
    lib/koshi8bit/ui/hotcolormap/hotspot.cpp \
    lib/koshi8bit/ui/hotcolormap/hotspotmap.cpp \
    lib/koshi8bit/ui/label/qlabelext.cpp \
    lib/koshi8bit/ui/plots/base/abstractgraph.cpp \
    lib/koshi8bit/ui/plots/base/abstractplot.cpp \
    lib/koshi8bit/ui/plots/base/axisvalueconfig.cpp \
    lib/koshi8bit/ui/plots/base/colorsetter.cpp \
    lib/koshi8bit/ui/plots/base/graphlegenditem.cpp \
    lib/koshi8bit/ui/plots/radar/radargraph.cpp \
    lib/koshi8bit/ui/plots/radar/radarplot.cpp \
    lib/koshi8bit/ui/plots/radar/radartemperature4graph.cpp \
    lib/koshi8bit/ui/plots/radar/radartemperature4plot.cpp \
    lib/koshi8bit/ui/plots/realtime/axistimeconfig.cpp \
    lib/koshi8bit/ui/plots/realtime/realtimegraph.cpp \
    lib/koshi8bit/ui/plots/realtime/realtimeplot.cpp \
    lib/koshi8bit/ui/plots/simple/errorxygraph.cpp \
    lib/koshi8bit/ui/plots/simple/errorygraph.cpp \
    lib/koshi8bit/ui/plots/simple/simplegraph.cpp \
    lib/koshi8bit/ui/plots/simple/simpleplot.cpp \
    lib/koshi8bit/ui/printscreener/printscreener.cpp \
    lib/koshi8bit/ui/qcustomplot/qcustomplot.cpp \
    lib/koshi8bit/ui/scientificnotationedit/scientificnotationedit.cpp \
    lib/koshi8bit/ui/value/bool/clickablelabel.cpp \
    lib/koshi8bit/ui/value/bool/valuebool.cpp \
    lib/koshi8bit/ui/value/bool_color/valueboolcolor.cpp \
    lib/koshi8bit/ui/value/double/valuedouble.cpp \
    lib/koshi8bit/worker/worker.cpp \
    main.cpp \
    mainwindow.cpp \
    pid.cpp

HEADERS += \
    lib/koshi8bit/easyliving.h \
    lib/koshi8bit/errorhandler/errorhandler.h \
    lib/koshi8bit/log/channel.h \
    lib/koshi8bit/log/channelbool.h \
    lib/koshi8bit/log/channeldouble.h \
    lib/koshi8bit/log/channelqstring.h \
    lib/koshi8bit/log/channelrealtimegraph.h \
    lib/koshi8bit/log/channelt.h \
    lib/koshi8bit/log/excel/excel.h \
    lib/koshi8bit/log/excel/excelfile.h \
    lib/koshi8bit/log/excel/excelsimple.h \
    lib/koshi8bit/log/excel/timelog/timelog.h \
    lib/koshi8bit/log/log.h \
    lib/koshi8bit/log/simple/simplelog.h \
    lib/koshi8bit/log/sql/sql.h \
    lib/koshi8bit/operationresult.h \
    lib/koshi8bit/qdebuglogger/qdebuglogger.h \
    lib/koshi8bit/settings/settings.h \
    lib/koshi8bit/shared-variable/tcp/netvars.h \
    lib/koshi8bit/shared-variable/tcp/netvars/initnvclient.h \
    lib/koshi8bit/shared-variable/tcp/netvars/initnvserver.h \
    lib/koshi8bit/shared-variable/tcp/netvars/netclient.h \
    lib/koshi8bit/shared-variable/tcp/netvars/netvar.h \
    lib/koshi8bit/shared-variable/tcp/netvars/netvarbase.h \
    lib/koshi8bit/shared-variable/tcp/netvars/nvDebug.h \
    lib/koshi8bit/shared-variable/tcp/netvars/varscontainer.h \
    lib/koshi8bit/shared-variable/udp/shared-variable.h \
    lib/koshi8bit/ui/double_spin_box_cursor/doublespinboxcursor.h \
    lib/koshi8bit/ui/faults/fault.h \
    lib/koshi8bit/ui/faults/faultswidget.h \
    lib/koshi8bit/ui/gradientlineedit/gradientlineedit.h \
    lib/koshi8bit/ui/gradientlineedit/minmax.h \
    lib/koshi8bit/ui/hotcolormap/hotspot.h \
    lib/koshi8bit/ui/hotcolormap/hotspotmap.h \
    lib/koshi8bit/ui/label/qlabelext.h \
    lib/koshi8bit/ui/plots/base/abstractgraph.h \
    lib/koshi8bit/ui/plots/base/abstractplot.h \
    lib/koshi8bit/ui/plots/base/axisvalueconfig.h \
    lib/koshi8bit/ui/plots/base/colorsetter.h \
    lib/koshi8bit/ui/plots/base/graphlegenditem.h \
    lib/koshi8bit/ui/plots/radar/radargraph.h \
    lib/koshi8bit/ui/plots/radar/radarplot.h \
    lib/koshi8bit/ui/plots/radar/radartemperature4graph.h \
    lib/koshi8bit/ui/plots/radar/radartemperature4plot.h \
    lib/koshi8bit/ui/plots/realtime/axistimeconfig.h \
    lib/koshi8bit/ui/plots/realtime/realtimegraph.h \
    lib/koshi8bit/ui/plots/realtime/realtimeplot.h \
    lib/koshi8bit/ui/plots/simple/errorxygraph.h \
    lib/koshi8bit/ui/plots/simple/errorygraph.h \
    lib/koshi8bit/ui/plots/simple/simplegraph.h \
    lib/koshi8bit/ui/plots/simple/simpleplot.h \
    lib/koshi8bit/ui/printscreener/printscreener.h \
    lib/koshi8bit/ui/qcustomplot/qcustomplot.h \
    lib/koshi8bit/ui/scientificnotationedit/scientificnotationedit.h \
    lib/koshi8bit/ui/value/bool/clickablelabel.h \
    lib/koshi8bit/ui/value/bool/valuebool.h \
    lib/koshi8bit/ui/value/bool_color/valueboolcolor.h \
    lib/koshi8bit/ui/value/double/valuedouble.h \
    lib/koshi8bit/worker/worker.h \
    mainwindow.h \
    pid.h

FORMS += \
    lib/koshi8bit/ui/gradientlineedit/minmax.ui \
    lib/koshi8bit/ui/plots/base/abstractplot.ui \
    lib/koshi8bit/ui/plots/base/axisvalueconfig.ui \
    lib/koshi8bit/ui/plots/base/graphlegenditem.ui \
    lib/koshi8bit/ui/plots/realtime/axistimeconfig.ui \
    lib/koshi8bit/ui/value/bool/valuebool.ui \
    lib/koshi8bit/ui/value/double/valuedouble.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    lib/koshi8bit/lib.qrc \
    lib/koshi8bit/pic/ui-res.qrc

DISTFILES += \
    lib/koshi8bit/pic/ico/clean-web.bat \
    lib/koshi8bit/pic/ico/custom/ask-question_002.png \
    lib/koshi8bit/pic/ico/custom/gears-white.png \
    lib/koshi8bit/pic/ico/custom/gears.png \
    lib/koshi8bit/pic/ico/custom/gears2.png \
    lib/koshi8bit/pic/ico/readme.md \
    lib/koshi8bit/pic/ico/web/about.png \
    lib/koshi8bit/pic/ico/web/add--v2.png \
    lib/koshi8bit/pic/ico/web/add-link.png \
    lib/koshi8bit/pic/ico/web/add-link_002.png \
    lib/koshi8bit/pic/ico/web/add-tag.png \
    lib/koshi8bit/pic/ico/web/alpha.png \
    lib/koshi8bit/pic/ico/web/alpha_002.png \
    lib/koshi8bit/pic/ico/web/ask-question.png \
    lib/koshi8bit/pic/ico/web/ask-question_002.png \
    lib/koshi8bit/pic/ico/web/ask-question_003.png \
    lib/koshi8bit/pic/ico/web/attach.png \
    lib/koshi8bit/pic/ico/web/attach_002.png \
    lib/koshi8bit/pic/ico/web/beta.png \
    lib/koshi8bit/pic/ico/web/beta_002.png \
    lib/koshi8bit/pic/ico/web/bookmark-ribbon.png \
    lib/koshi8bit/pic/ico/web/broken-link.png \
    lib/koshi8bit/pic/ico/web/broken-link_002.png \
    lib/koshi8bit/pic/ico/web/camera.png \
    lib/koshi8bit/pic/ico/web/cancel.png \
    lib/koshi8bit/pic/ico/web/checked.png \
    lib/koshi8bit/pic/ico/web/checkmark.png \
    lib/koshi8bit/pic/ico/web/contact-card.png \
    lib/koshi8bit/pic/ico/web/delete-link.png \
    lib/koshi8bit/pic/ico/web/delete-link_002.png \
    lib/koshi8bit/pic/ico/web/delta.png \
    lib/koshi8bit/pic/ico/web/do-not-disturb.png \
    lib/koshi8bit/pic/ico/web/do-not-disturb_002.png \
    lib/koshi8bit/pic/ico/web/document.png \
    lib/koshi8bit/pic/ico/web/double-tick.png \
    lib/koshi8bit/pic/ico/web/edit-link.png \
    lib/koshi8bit/pic/ico/web/eppendorf.png \
    lib/koshi8bit/pic/ico/web/epsilon.png \
    lib/koshi8bit/pic/ico/web/equal-sign.png \
    lib/koshi8bit/pic/ico/web/error.png \
    lib/koshi8bit/pic/ico/web/eta.png \
    lib/koshi8bit/pic/ico/web/expired.png \
    lib/koshi8bit/pic/ico/web/filled-trash.png \
    lib/koshi8bit/pic/ico/web/filled-trash_002.png \
    lib/koshi8bit/pic/ico/web/flip-horizontal.png \
    lib/koshi8bit/pic/ico/web/flip-vertical.png \
    lib/koshi8bit/pic/ico/web/folder-invoices.png \
    lib/koshi8bit/pic/ico/web/full-trash.png \
    lib/koshi8bit/pic/ico/web/gamma.png \
    lib/koshi8bit/pic/ico/web/gamma_002.png \
    lib/koshi8bit/pic/ico/web/gears.png \
    lib/koshi8bit/pic/ico/web/ground-symbol.png \
    lib/koshi8bit/pic/ico/web/idea.png \
    lib/koshi8bit/pic/ico/web/infinity.png \
    lib/koshi8bit/pic/ico/web/information.png \
    lib/koshi8bit/pic/ico/web/invisible.png \
    lib/koshi8bit/pic/ico/web/invisible_002.png \
    lib/koshi8bit/pic/ico/web/iota-letter.png \
    lib/koshi8bit/pic/ico/web/kappa.png \
    lib/koshi8bit/pic/ico/web/key.png \
    lib/koshi8bit/pic/ico/web/ksi--v1.png \
    lib/koshi8bit/pic/ico/web/ksi.png \
    lib/koshi8bit/pic/ico/web/lambda.png \
    lib/koshi8bit/pic/ico/web/lambda_002.png \
    lib/koshi8bit/pic/ico/web/like.png \
    lib/koshi8bit/pic/ico/web/like_002.png \
    lib/koshi8bit/pic/ico/web/link.png \
    lib/koshi8bit/pic/ico/web/link_002.png \
    lib/koshi8bit/pic/ico/web/lock--v1.png \
    lib/koshi8bit/pic/ico/web/login-rounded-right.png \
    lib/koshi8bit/pic/ico/web/logout-rounded.png \
    lib/koshi8bit/pic/ico/web/maintenance.png \
    lib/koshi8bit/pic/ico/web/messaging-.png \
    lib/koshi8bit/pic/ico/web/microscope.png \
    lib/koshi8bit/pic/ico/web/minus-math.png \
    lib/koshi8bit/pic/ico/web/minus.png \
    lib/koshi8bit/pic/ico/web/mu.png \
    lib/koshi8bit/pic/ico/web/mu_002.png \
    lib/koshi8bit/pic/ico/web/multiply.png \
    lib/koshi8bit/pic/ico/web/no-reminders.png \
    lib/koshi8bit/pic/ico/web/no-reminders_002.png \
    lib/koshi8bit/pic/ico/web/not-equal.png \
    lib/koshi8bit/pic/ico/web/nu.png \
    lib/koshi8bit/pic/ico/web/ok.png \
    lib/koshi8bit/pic/ico/web/omega.png \
    lib/koshi8bit/pic/ico/web/omega_002.png \
    lib/koshi8bit/pic/ico/web/omicron.png \
    lib/koshi8bit/pic/ico/web/opened-folder.png \
    lib/koshi8bit/pic/ico/web/phi.png \
    lib/koshi8bit/pic/ico/web/pi.png \
    lib/koshi8bit/pic/ico/web/pi_002.png \
    lib/koshi8bit/pic/ico/web/plus-math.png \
    lib/koshi8bit/pic/ico/web/print.png \
    lib/koshi8bit/pic/ico/web/psi.png \
    lib/koshi8bit/pic/ico/web/radio-active.png \
    lib/koshi8bit/pic/ico/web/rho.png \
    lib/koshi8bit/pic/ico/web/save-all.png \
    lib/koshi8bit/pic/ico/web/save-as.png \
    lib/koshi8bit/pic/ico/web/save-close.png \
    lib/koshi8bit/pic/ico/web/save.png \
    lib/koshi8bit/pic/ico/web/screenshot.png \
    lib/koshi8bit/pic/ico/web/screenshot_002.png \
    lib/koshi8bit/pic/ico/web/screenshot_003.png \
    lib/koshi8bit/pic/ico/web/screenshot_004.png \
    lib/koshi8bit/pic/ico/web/services.png \
    lib/koshi8bit/pic/ico/web/settings.png \
    lib/koshi8bit/pic/ico/web/sigma.png \
    lib/koshi8bit/pic/ico/web/sigma_002.png \
    lib/koshi8bit/pic/ico/web/sos.png \
    lib/koshi8bit/pic/ico/web/sos_002.png \
    lib/koshi8bit/pic/ico/web/star.png \
    lib/koshi8bit/pic/ico/web/star_002.png \
    lib/koshi8bit/pic/ico/web/support.png \
    lib/koshi8bit/pic/ico/web/tau.png \
    lib/koshi8bit/pic/ico/web/terms-and-conditions.png \
    lib/koshi8bit/pic/ico/web/test-tube.png \
    lib/koshi8bit/pic/ico/web/theta.png \
    lib/koshi8bit/pic/ico/web/thin-test-tube.png \
    lib/koshi8bit/pic/ico/web/toggle-off.png \
    lib/koshi8bit/pic/ico/web/toggle-on.png \
    lib/koshi8bit/pic/ico/web/translation.png \
    lib/koshi8bit/pic/ico/web/unlock.png \
    lib/koshi8bit/pic/ico/web/upload.png \
    lib/koshi8bit/pic/ico/web/visible.png \
    lib/koshi8bit/pic/ico/web/visible_002.png \
    lib/koshi8bit/pic/ico/web/xi.png \
    lib/koshi8bit/pic/ico/web/zeta.png \
    lib/koshi8bit/pic/ico/web/zoom-in.png \
    lib/koshi8bit/pic/ico/web/zoom-out.png \
    lib/koshi8bit/pic/ico/web/zoom-to-actual-size.png \
    lib/koshi8bit/pic/ico/web/zoom-to-extents.png \
    lib/koshi8bit/pic/paint.png \
    lib/koshi8bit/pic/ui-gradientlineedit-gears.png \
    lib/koshi8bit/pic/ui-plot-axis-value-01.png \
    lib/koshi8bit/pic/ui-plot-axis-value-02.png \
    lib/koshi8bit/pic/ui-plot-axis-value-03.png \
    lib/koshi8bit/pic/ui-realtimeqcp-cursor01.PNG \
    lib/koshi8bit/pic/ui-realtimeqcp-cursor0102 — копия.PNG \
    lib/koshi8bit/pic/ui-realtimeqcp-cursor0102.PNG \
    lib/koshi8bit/pic/ui-realtimeqcp-mouse-area.PNG \
    lib/koshi8bit/pic/ui-realtimeqcp-realtime.PNG \
    lib/koshi8bit/pic/ui-realtimeqcp.PNG \
    lib/koshi8bit/shared-variable/tcp/netvars/example/example.7z \
    lib/koshi8bit/ui/faults/template.html \
    lib/koshi8bit/ui/plots/base/base.7z \
    lib/koshi8bit/ui/qcustomplot/qt5-diff.7z \
    lib/update-koshi8bit.bat
