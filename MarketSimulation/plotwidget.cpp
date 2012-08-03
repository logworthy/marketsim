#include "plotwidget.h"
#include "ui_plotwidget.h"

#include <qwt/qwt_scale_draw.h>
#include <qwt/qwt_plot_canvas.h>
#include <qwt/qwt_plot_layout.h>
#include <qwt/qwt_legend.h>

const int PlotWidget::historySize = 60;

PlotWidget::PlotWidget(QWidget *parent) :
    QwtPlot(parent),
    ui(new Ui::PlotWidget)
{
    ui->setupUi(this);

    // Setup plot stuff
    setAutoReplot(false);
    canvas()->setBorderRadius( 10 );

    plotLayout()->setAlignCanvasToScales(true);

    QwtLegend *legend = new QwtLegend;
    legend->setItemMode(QwtLegend::CheckableItem);
    insertLegend(legend, QwtPlot::RightLegend);

    setAxisTitle(QwtPlot::xBottom, " Time [s]");
    setAxisScaleDraw(QwtPlot::xBottom,
                     new QwtScaleDraw());
    //setAxisScale(QwtPlot::xBottom, 0, historySize); // Own Change
    setAxisLabelRotation(QwtPlot::xBottom, -50.0);
    setAxisLabelAlignment(QwtPlot::xBottom, Qt::AlignLeft | Qt::AlignBottom);

    setAxisTitle(QwtPlot::yLeft, " Price [$]");
    setAxisScaleDraw(QwtPlot::yLeft,
                     new QwtScaleDraw());
    setAxisLabelRotation(QwtPlot::yLeft, -50.0);
    setAxisLabelAlignment(QwtPlot::yLeft, Qt::AlignLeft | Qt::AlignBottom);

    // Setup the data
    asset1Data = new CircularBuffer(historySize);
    asset2Data = new CircularBuffer(historySize);
    timeData = new CircularBuffer(historySize);

    asset1Curve = new QwtPlotCurve("Asset 1");
    asset1Curve->setPen(QPen(Qt::red));
    asset1Curve->attach(this);

    asset2Curve = new QwtPlotCurve("Asset 2");
    asset2Curve->setPen(QPen(Qt::blue));
    asset2Curve->attach(this);
}

PlotWidget::~PlotWidget()
{
    delete ui;
}

void PlotWidget::addData(double time, double price1, double price2)
{
    timeData->insertItem(time);
    asset1Data->insertItem(price1);
    asset2Data->insertItem(price2);

    asset1Curve->setRawSamples(timeData->getData(),asset1Data->getData(),asset1Data->getSize());
    asset2Curve->setRawSamples(timeData->getData(),asset2Data->getData(),asset2Data->getSize());

    replot();
}