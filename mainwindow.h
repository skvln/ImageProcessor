#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "image_processor.h"

#include <memory>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QLabel>
#include <QMainWindow>
#include <QMessageBox>
#include <QRadioButton>
#include <QSlider>
#include <unordered_map>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Слоты для обработки нажатия на кнопки изменения значений слайдеров
    void on_zoom_increase_button_clicked();
    void on_zoom_decrease_button_clicked();

    void on_rotate_right_button_clicked();
    void on_rotate_left_button_clicked();

    void on_brightness_increase_button_clicked();
    void on_brightness_decrease_button_clicked();

    void on_contrast_increase_button_clicked();
    void on_contrast_decrease_button_clicked();

    void on_red_increase_button_clicked();
    void on_red_decrease_button_clicked();

    void on_green_increase_button_clicked();
    void on_green_decrease_button_clicked();

    void on_blue_increase_level_clicked();
    void on_blue_decrease_level_clicked();

    void on_horizontal_reflection_button_clicked();
    void on_vertical_reflection_button_clicked();

    // Слоты для обработки изменения значений слайдеров
    void on_zoom_slider_valueChanged(int value);
    void on_rotate_slider_valueChanged(int value);
    void on_brightness_slider_valueChanged(int value);
    void on_contrast_slider_valueChanged(int value);
    void on_red_slider_valueChanged(int value);
    void on_green_slider_valueChanged(int value);
    void on_blue_slider_valueChanged(int value);

    // Слоты для реакции на нажатие кнопок в верхнем меню
    void on_open_action_triggered();
    void on_save_action_triggered();
    void on_save_as_action_triggered();
    void on_revert_action_triggered();

    // Слоты для обработки нажатий на переключатели
    void on_black_white_radio_clicked();
    void on_blur_radio_clicked();
    void on_colorless_radio_clicked();
    void on_sepia_radio_clicked();
    void on_negative_radio_clicked();


private:
    Ui::MainWindow *ui;
    QString file_path_;
    ImageProcessor ip_;
    std::unordered_map<const QLabel*, int> slider_values_;
    std::unique_ptr<QPixmap> pm_;
    std::unique_ptr<QGraphicsScene> scene_ptr_;

    // Установка изображения
    void UpdateImageView();

    // Изменение позиции слайдера на переданное значение
    void ChangeSliderPos(QSlider* slider, int value);
    void SetColorCorrectLabelText(QLabel* label, int value);
    void SetDefault();

};
#endif // MAINWINDOW_H
