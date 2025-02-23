// controlwindow.h
#ifndef CONTROLWINDOW_H
#define CONTROLWINDOW_H

#include <QDialog>

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


/*!
 * \brief Класс окна управления параметрами температуры, влажности и давления.
 *
 * Этот класс предназначен для предоставления интерфейса пользователя,
 * который позволяет изменять параметры температуры, влажности и давления.
 */
class ControlWindow : public QDialog {
    Q_OBJECT

public:
    /*!
     * \brief Конструктор класса ControlWindow.
     *
     * Создает новое окно управления параметрами.
     *
     * \param parent Указатель на родительский виджет.
     */
    explicit ControlWindow(QWidget *parent = nullptr);

signals:
    /*!
     * \brief Сигнал изменения температуры.
     *
     * Отправляется, когда изменяется значение температуры.
     *
     * \param index Индекс изменяемого параметра.
     * \param value Новое значение температуры.
     */
    void temperatureChanged(int index, double value);

    /*!
     * \brief Сигнал изменения влажности.
     *
     * Отправляется, когда изменяется значение влажности.
     *
     * \param index Индекс изменяемого параметра.
     * \param value Новое значение влажности.
     */
    void humidityChanged(int index, double value);

    /*!
     * \brief Сигнал изменения давления.
     *
     * Отправляется, когда изменяется значение давления.
     *
     * \param index Индекс изменяемого параметра.
     * \param value Новое значение давления.
     */
    void pressureChanged(int index, double value);
};

#endif // CONTROLWINDOW_H
