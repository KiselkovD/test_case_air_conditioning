// mainwindow.cpp
#include "mainwindow.h"
#include "ui_mainwindow.h"




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // инерфейс
    ui->setupUi(this);
    this->resize(800, 600);

    TemperatureComboBox[0] = ui->comboBox;
    HumidityComboBox[0] = ui->comboBox_2;
    PressureComboBox[0] = ui->comboBox_3;

    TemperatureComboBox[1] = ui->comboBox_12;
    HumidityComboBox[1] = ui->comboBox_13;
    PressureComboBox[1] = ui->comboBox_14;

    TemperatureComboBox[2] = ui->comboBox_18;
    HumidityComboBox[2] = ui->comboBox_19;
    PressureComboBox[2] = ui->comboBox_20;

    setTemperatureComboBox[0] = ui->comboBox_6;
    setTemperatureComboBox[1] = ui->comboBox_9;
    setTemperatureComboBox[2] = ui->comboBox_15;

    TemperatureLineEdit[0] = ui->lineEdit;
    HumidityLineEdit[0] = ui->lineEdit_2;
    PressureLineEdit[0] = ui->lineEdit_3;

    TemperatureLineEdit[1] = ui->lineEdit_4;
    HumidityLineEdit[1] = ui->lineEdit_5;
    PressureLineEdit[1] = ui->lineEdit_6;

    TemperatureLineEdit[2] = ui->lineEdit_7;
    HumidityLineEdit[2] = ui->lineEdit_8;
    PressureLineEdit[2] = ui->lineEdit_9;

    loadSettings(); // Загружаем настройки при создании окна

    // создаем второе окно
    ControlWindow *controlWindow = new ControlWindow(this);

    // при изменении данных обновить отображаемые значения
    connect(controlWindow, &ControlWindow::temperatureChanged, this, &MainWindow::updateTemperature);
    connect(controlWindow, &ControlWindow::humidityChanged, this, &MainWindow::updateHumidity);
    connect(controlWindow, &ControlWindow::pressureChanged, this, &MainWindow::updatePressure);

    // при изменении едениц обновить отображаемые значения
    for (int i = 0; i < 3; ++i) {
        connect(TemperatureComboBox[i], QOverload<int>::of(&QComboBox::currentIndexChanged),
                [=]() {
                    onTemperatureComboBoxChanged(i);
                });
        connect(HumidityComboBox[i], QOverload<int>::of(&QComboBox::currentIndexChanged),
                [=]() {
                    onHumidityComboBoxChanged(i);
                });
        connect(PressureComboBox[i], QOverload<int>::of(&QComboBox::currentIndexChanged),
                [=]() {
                    onPressureComboBoxChanged(i);
                });

    }

    // настройки
    // смена темы
    connect(ui->comboBox_7, SIGNAL(currentIndexChanged(int)),
            this, SLOT(changeStyle(int)));

    // смена разрешения
    connect(ui->comboBox_8, SIGNAL(currentIndexChanged(int)),
            this, SLOT(changeResolution(int)));

    // открытие документации
    // ######################################################

    // показать второе окно
    controlWindow->show();

    this->changeStyle(0);
}

MainWindow::~MainWindow()
{
    saveSettings();
    delete ui;
}

void MainWindow::onTemperatureComboBoxChanged(int index) {
    int ComboBoxIndex = TemperatureComboBox[index]->currentIndex();
    if (ComboBoxIndex == 0) {
        TemperatureLineEdit[index]->setText(QString::number(Temperature[index]));
    } else if (ComboBoxIndex == 1) {
        TemperatureLineEdit[index]->setText(QString::number((Temperature[index] * 9/5) + 32));
    } else {
        TemperatureLineEdit[index]->setText(QString::number(Temperature[index] + 273.15));
    }
}
void MainWindow::onHumidityComboBoxChanged(int index) {
    HumidityLineEdit[index]->setText(QString::number(Humidity[index]));
}
void MainWindow::onPressureComboBoxChanged(int index) {
    int ComboBoxIndex = PressureComboBox[index]->currentIndex();
    if (ComboBoxIndex == 0) {
        PressureLineEdit[index]->setText(QString::number(Pressure[index]));
    } else {
        PressureLineEdit[index]->setText(QString::number(Pressure[index] * 0.0075006375541921));
    }
}

void MainWindow::updateTemperature(int index, double value) {
    Temperature[index] = value;
    onTemperatureComboBoxChanged(index);
}
void MainWindow::updateHumidity(int index, double value) {
    Humidity[index] = value;
    onHumidityComboBoxChanged(index);
}
void MainWindow::updatePressure(int index, double value) {
    Pressure[index] = value;
    onPressureComboBoxChanged(index);
}

void MainWindow::changeStyle(int index) {

    if (index == 0) {  // Светлый стиль при выборе второй опции ("Светлая")
        QFile file("light_theme.css");
        if (!file.open(QIODevice::ReadOnly)) {
            qDebug() << "Failed to open styles.css";
        }
        QString styleSheet = QTextStream(&file).readAll();
        setStyleSheet(styleSheet);

        ui->infoLabel->setStyleSheet(QString::fromUtf8("background-color: rgb(202, 202, 202)"));
        ui->infoLabel_2->setStyleSheet(QString::fromUtf8("background-color: rgb(202, 202, 202)"));
        ui->infoLabel_3->setStyleSheet(QString::fromUtf8("background-color: rgb(202, 202, 202)"));

        ui->setLabel->setStyleSheet(QString::fromUtf8("background-color: rgb(202, 202, 202)"));
        ui->setLabel_2->setStyleSheet(QString::fromUtf8("background-color: rgb(202, 202, 202)"));
        ui->setLabel_3->setStyleSheet(QString::fromUtf8("background-color: rgb(202, 202, 202)"));

        ui->label_10->setStyleSheet(QString::fromUtf8("background-color: rgb(202, 202, 202)"));

    } else {  // Темный стиль при выборе первой опции ("Темная")
        QFile file("dark_theme.css");
        if (!file.open(QIODevice::ReadOnly)) {
            qDebug() << "Failed to open styles.css";
        }
        QString styleSheet = QTextStream(&file).readAll();
        setStyleSheet(styleSheet);

        ui->infoLabel->setStyleSheet(QString::fromUtf8("background-color: #505259"));
        ui->infoLabel_2->setStyleSheet(QString::fromUtf8("background-color: #505259"));
        ui->infoLabel_3->setStyleSheet(QString::fromUtf8("background-color: #505259"));

        ui->setLabel->setStyleSheet(QString::fromUtf8("background-color: #505259"));
        ui->setLabel_2->setStyleSheet(QString::fromUtf8("background-color: #505259"));
        ui->setLabel_3->setStyleSheet(QString::fromUtf8("background-color: #505259"));

        ui->label_10->setStyleSheet(QString::fromUtf8("background-color: #505259"));
    }
}
void MainWindow::changeResolution(int index) {
    if (index == 0) {
        this->resize(800, 600);
        ui->centralwidget->setStyleSheet(QString::fromUtf8("*{font-size: 20px}"));
    } else {
        this->resize(1024, 768);
        ui->centralwidget->setStyleSheet(QString::fromUtf8("*{font-size: 24px}"));
    }
}

void MainWindow::saveSettings()
{
    // Имя файла настроек
    const QString filename = "settings.xml";

    // Открываем файл для записи
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qWarning() << "Не удалось открыть файл" << filename << "для записи.";
        return;
    }

    // Создаем объект для записи XML
    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true); // Форматирование для читаемости
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("Settings");

    // Сохраняем значения для каждого блока (1, 2, 3)
    for (int i = 1; i <= 3; ++i)
    {
        xmlWriter.writeStartElement("Block"); // Начинаем блок
        xmlWriter.writeAttribute("number", QString::number(i)); // Устанавливаем номер блока

        // Сохраняем значения TemperatureComboBox
        int index = TemperatureComboBox[i-1]->currentIndex();
        xmlWriter.writeStartElement("TemperatureComboBox");
        xmlWriter.writeAttribute("index", QString::number(index));
        xmlWriter.writeEndElement(); // Закрываем элемент TemperatureComboBox

        // Сохраняем значения setTemperatureComboBox
        index = setTemperatureComboBox[i-1]->currentIndex();
        xmlWriter.writeStartElement("setTemperatureComboBox");
        xmlWriter.writeAttribute("index", QString::number(index));
        xmlWriter.writeEndElement(); // Закрываем элемент TemperatureComboBox

        // Сохраняем значения HumidityComboBox
        index = HumidityComboBox[i-1]->currentIndex();
        xmlWriter.writeStartElement("HumidityComboBox");
        xmlWriter.writeAttribute("index", QString::number(index));
        xmlWriter.writeEndElement(); // Закрываем элемент HumidityComboBox

        // Сохраняем значения PressureComboBox
        index = PressureComboBox[i-1]->currentIndex();
        xmlWriter.writeStartElement("PressureComboBox");
        xmlWriter.writeAttribute("index", QString::number(index));
        xmlWriter.writeEndElement(); // Закрываем элемент PressureComboBox

        xmlWriter.writeEndElement(); // Закрываем блок <Block>
    }

    xmlWriter.writeEndElement(); // Закрываем элемент Settings
    xmlWriter.writeEndDocument();

    file.close();
}
void MainWindow::loadSettings()
{
    // Имя файла настроек
    const QString filename = "settings.xml";

    // Открываем файл для чтения
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "Не удалось открыть файл" << filename << "для чтения.";
        return;
    }

    // Создаем объект для чтения XML
    QXmlStreamReader xmlReader(&file);

    while (!xmlReader.atEnd())
    {
        xmlReader.readNext();

        if (xmlReader.isStartElement())
        {
            if (xmlReader.name() == "Block")
            {
                int currentBlock = xmlReader.attributes().value("number").toInt(); // Получаем номер блока

                while (!(xmlReader.isEndElement() && xmlReader.name() == "Block"))
                {
                    xmlReader.readNext();

                    if (xmlReader.isStartElement())
                    {
                        if (xmlReader.name() == "TemperatureComboBox")
                        {
                            bool ok;
                            int index = xmlReader.attributes().value("index").toString().toInt(&ok);
                            if (ok && index >= 0 && index < 3)
                                TemperatureComboBox[currentBlock - 1]->setCurrentIndex(index);
                        }
                        else if (xmlReader.name() == "setTemperatureComboBox")
                        {
                            bool ok;
                            int index = xmlReader.attributes().value("index").toString().toInt(&ok);
                            if (ok && index >= 0 && index < 3)
                                setTemperatureComboBox[currentBlock - 1]->setCurrentIndex(index);
                        }
                        else if (xmlReader.name() == "HumidityComboBox")
                        {
                            bool ok;
                            int index = xmlReader.attributes().value("index").toString().toInt(&ok);
                            if (ok && index >= 0 && index < 3)
                                HumidityComboBox[currentBlock - 1]->setCurrentIndex(index);
                        }
                        else if (xmlReader.name() == "PressureComboBox")
                        {
                            bool ok;
                            int index = xmlReader.attributes().value("index").toString().toInt(&ok);
                            if (ok && index >= 0 && index < 3)
                                PressureComboBox[currentBlock - 1]->setCurrentIndex(index);
                        }
                    }
                }
            }
        }
    }

    if (xmlReader.hasError())
    {
        qWarning() << "Ошибка парсинга XML:" << xmlReader.errorString();
    }

    file.close();
}
