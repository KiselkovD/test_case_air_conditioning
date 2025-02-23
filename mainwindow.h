// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "controlwindow.h"

#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QFile>
#include <QDebug>
#include <QTextStream>

QT_BEGIN_NAMESPACE
namespace Ui {

class MainWindow;
}
QT_END_NAMESPACE

/*!
 * \brief Главный класс окна приложения.
 *
 * Этот класс представляет собой главное окно приложения, которое управляет
 * настройками температуры, влажности и давления через комбинационные боксы
 * и линии редактирования. Поддерживает сохранение настроек в файл.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * \brief Конструктор главного окна.
     *
     * Создается основное окно приложения с инициализацией всех необходимых элементов.
     *
     * \param parent Указатель на родительский виджет.
     */
    MainWindow(QWidget *parent = nullptr);

    /*!
     * \brief Деструктор главного окна.
     *
     * Сохраняет текущие настройки перед закрытием окна.
     */
    ~MainWindow();

private slots:
    /*!
     * \brief Слот для изменения стиля интерфейса.
     *
     * Применяет выбранный стиль оформления к приложению.
     *
     * \param index Индекс выбранного стиля в комбобоксе.
     */
    void changeStyle(int index);

    /*!
     * \brief Слот для изменения разрешения экрана.
     *
     * Устанавливает новое разрешение окна приложения.
     *
     * \param index Индекс выбранного разрешения в комбобоксе.
     */
    void changeResolution(int index);

    /*!
     * \brief Обновляет значение температуры.
     *
     * Получает новые данные от вспомогательного окна и обновляет соответствующие элементы интерфейса.
     *
     * \param index Индекс вкладки, для которой происходит обновление.
     * \param value Новое значение температуры.
     */
    void updateTemperature(int index, double value);

    /*!
     * \brief Обновляет значение влажности.
     *
     * Получает новые данные от вспомогательного окна и обновляет соответствующие элементы интерфейса.
     *
     * \param index Индекс вкладки, для которой происходит обновление.
     * \param value Новое значение влажности.
     */
    void updateHumidity(int index, double value);

    /*!
     * \brief Обновляет значение давления.
     *
     * Получает новые данные от вспомогательного окна и обновляет соответствующие элементы интерфейса.
     *
     * \param index Индекс вкладки, для которой происходит обновление.
     * \param value Новое значение давления.
     */
    void updatePressure(int index, double value);

    /*!
     * \brief Обработчик изменения комбобокса температуры.
     *
     * Вызывается при изменении индекса в комбобоксе выбора единиц измерения температуры.
     *
     * \param index Индекс вкладки, для которой произошло изменение.
     */
    void onTemperatureComboBoxChanged(int index);

    /*!
     * \brief Обработчик изменения комбобокса влажности.
     *
     * Вызывается при изменении индекса в комбобоксе выбора единиц измерения влажности.
     *
     * \param index Индекс вкладки, для которой произошло изменение.
     */
    void onHumidityComboBoxChanged(int index);

    /*!
     * \brief Обработчик изменения комбобокса давления.
     *
     * Вызывается при изменении индекса в комбобоксе выбора единиц измерения давления.
     *
     * \param index Индекс вкладки, для которой произошло изменение.
     */
    void onPressureComboBoxChanged(int index);

private:
    /*!
     * \brief Комбобокс для выбора единицы измерения температуры.
     *
     * Позволяет выбрать между различными единицами измерения температуры
     * (например, Цельсий, Фаренгейт, Кельвин).
     */
    QComboBox *TemperatureComboBox[3];

    /*!
     * \brief Комбобокс для выбора единицы измерения влажности.
     *
     * Позволяет выбрать между различными единицами измерения влажности
     * (например, проценты).
     */
    QComboBox *HumidityComboBox[3];

    /*!
     * \brief Комбобокс для выбора единицы измерения давления.
     *
     * Позволяет выбрать между различными единицами измерения давления
     * (например, паскали, бары).
     */
    QComboBox *PressureComboBox[3];

    /*!
     * \brief Комбобокс для задания значения температуры.
     *
     * Используются для установки конкретного значения температуры.
     */
    QComboBox *setTemperatureComboBox[3];

    /*!
     * \brief Линии редактирования для отображения значений температуры.
     *
     * Показывают текущее значение температуры в выбранной единице измерения.
     */
    QLineEdit *TemperatureLineEdit[3];

    /*!
     * \brief Линии редактирования для отображения значений влажности.
     *
     * Показывают текущее значение влажности в выбранной единице измерения.
     */
    QLineEdit *HumidityLineEdit[3];

    /*!
     * \brief Линии редактирования для отображения значений давления.
     *
     * Показывают текущее значение давления в выбранной единице измерения.
     */
    QLineEdit *PressureLineEdit[3];

    /*!
     * \brief Текущие значения температуры.
     *
     * Массив хранит последние установленные значения температуры.
     */
    double Temperature[3] = {0,0,0};

    /*!
     * \brief Текущие значения влажности.
     *
     * Массив хранит последние установленные значения влажности.
     */
    double Humidity[3] = {0,0,0};

    /*!
     * \brief Текущие значения давления.
     *
     * Массив хранит последние установленные значения давления.
     */
    double Pressure[3] = {0,0,0};

    /*!
     * \brief Сохранение настроек.
     *
     * Сохраняет текущие настройки в файл для последующего восстановления.
     */
    void saveSettings();

    /*!
     * \brief Загрузка настроек.
     *
     * Восстанавливает ранее сохранённые настройки из файла.
     */
    void loadSettings();

    /*!
     * \brief Указатель на пользовательский интерфейс.
     *
     * Содержит ссылку на объект UI, предоставляющий доступ ко всем виджетам формы.
     */
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
