// controlwindow.cpp
#include "controlwindow.h"
#include <QTabWidget>
#include <QVBoxLayout>

ControlWindow::ControlWindow(QWidget *parent) : QDialog(parent) {
    // интерфейс
    this->resize(300, 200);

    QTabWidget *tabWidget = new QTabWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(tabWidget);
    this->setLayout(mainLayout);

    const int tabCount = 3;
    QPushButton *setTemperatureButton[tabCount];
    QDoubleSpinBox *humiditySpinBox[tabCount];
    QPushButton *setHumidityButton[tabCount];
    QDoubleSpinBox *temperatureSpinBox[tabCount];
    QDoubleSpinBox *pressureSpinBox[tabCount];
    QPushButton *setPressureButton[tabCount];

    // интерфейс вкладок
    for (int i = 0; i < tabCount; ++i) {
        QWidget *tab = new QWidget();
        QHBoxLayout *horizontalLayout = new QHBoxLayout(tab);
        QGridLayout *gridLayout = new QGridLayout();
        horizontalLayout->addLayout(gridLayout);
        tab->setLayout(horizontalLayout);
        tabWidget->addTab(tab, QString("Tab %1").arg(i + 1));

        setTemperatureButton[i] = new QPushButton(tab);
        setTemperatureButton[i]->setMinimumSize(QSize(0, 30));
        humiditySpinBox[i] = new QDoubleSpinBox(tab);
        humiditySpinBox[i]->setMinimumSize(QSize(0, 30));
        setHumidityButton[i] = new QPushButton(tab);
        setHumidityButton[i]->setMinimumSize(QSize(0, 30));
        temperatureSpinBox[i] = new QDoubleSpinBox(tab);
        temperatureSpinBox[i]->setMinimumSize(QSize(0, 30));
        pressureSpinBox[i] = new QDoubleSpinBox(tab);
        pressureSpinBox[i]->setMinimumSize(QSize(0, 30));
        setPressureButton[i] = new QPushButton(tab);
        setPressureButton[i]->setMinimumSize(QSize(0, 30));

        gridLayout->addWidget(setTemperatureButton[i], 0, 1, 1, 1);
        gridLayout->addWidget(humiditySpinBox[i], 1, 0, 1, 1);
        gridLayout->addWidget(setHumidityButton[i], 1, 1, 1, 1);
        gridLayout->addWidget(temperatureSpinBox[i], 0, 0, 1, 1);
        gridLayout->addWidget(pressureSpinBox[i], 2, 0, 1, 1);
        gridLayout->addWidget(setPressureButton[i], 2, 1, 1, 1);

        temperatureSpinBox[i]->setMinimum(-60.00);
        temperatureSpinBox[i]->setMaximum(370.00);
        humiditySpinBox[i]->setMinimum(0.00);
        humiditySpinBox[i]->setMaximum(100.00);
        pressureSpinBox[i]->setMinimum(600.00);
        pressureSpinBox[i]->setMaximum(120000.00);

        setTemperatureButton[i]->setText(QCoreApplication::translate("MainWindow", "set \302\260C temperature", nullptr));
        setHumidityButton[i]->setText(QCoreApplication::translate("MainWindow", "set % humidity", nullptr));
        setPressureButton[i]->setText(QCoreApplication::translate("MainWindow", "set Pa pressure", nullptr));

        // по нажатию кнопок вспомогательного окна вызвать изменение данных
        connect(setTemperatureButton[i], &QPushButton::clicked, [this, i, temperatureSpinBox]() {
            emit temperatureChanged(i, temperatureSpinBox[i]->value());
        });
        connect(setHumidityButton[i], &QPushButton::clicked, [this, i, humiditySpinBox]() {
            emit humidityChanged(i, humiditySpinBox[i]->value());
        });
        connect(setPressureButton[i], &QPushButton::clicked, [this, i, pressureSpinBox]() {
            emit pressureChanged(i, pressureSpinBox[i]->value());
        });

    }

}
