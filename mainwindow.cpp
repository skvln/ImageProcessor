#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , pm_(new QPixmap)
    , scene_ptr_(new QGraphicsScene)
{
    ui->setupUi(this);

    connect(
        ui->quit_action,
        &QAction::triggered,
        qApp,
        &QApplication::quit
    );

    slider_values_ = {
        {ui->zoom_percentage_label, 100},
        {ui->rotate_degree_label, 0},
        {ui->brightness_level_label, 0},
        {ui->contrast_level_label, 0},
        {ui->red_delta_label, 0},
        {ui->green_delta_label, 0},
        {ui->blue_delta_label, 0}
    };
}

MainWindow::~MainWindow()
{
    delete ui;
}

// { public methods

// public methods }

// { slots

// [ push buttons

void MainWindow::on_zoom_increase_button_clicked()
{
    constexpr int percentage_change = 20;

    ChangeSliderPos(ui->zoom_slider, percentage_change);
}

void MainWindow::on_zoom_decrease_button_clicked()
{
    constexpr int percentage_change = -20;

    ChangeSliderPos(ui->zoom_slider, percentage_change);
}

void MainWindow::on_rotate_right_button_clicked()
{
    constexpr int degree_change = 10;

    ChangeSliderPos(ui->rotate_slider, degree_change);
}

void MainWindow::on_rotate_left_button_clicked()
{
    constexpr int degree_change = -10;

    ChangeSliderPos(ui->rotate_slider, degree_change);
}

void MainWindow::on_brightness_increase_button_clicked()
{
    constexpr int value_change = 10;

    ChangeSliderPos(ui->brightness_slider, value_change);
}

void MainWindow::on_brightness_decrease_button_clicked()
{
    constexpr int value_change = -10;

    ChangeSliderPos(ui->brightness_slider, value_change);
}


void MainWindow::on_contrast_increase_button_clicked()
{
    constexpr int value_change = 10;

    ChangeSliderPos(ui->contrast_slider, value_change);
}

void MainWindow::on_contrast_decrease_button_clicked()
{
    constexpr int value_change = -10;

    ChangeSliderPos(ui->contrast_slider, value_change);
}

void MainWindow::on_red_increase_button_clicked()
{
    constexpr int value_change = 10;

    ChangeSliderPos(ui->red_slider, value_change);
}

void MainWindow::on_red_decrease_button_clicked()
{
    constexpr int value_change = -10;

    ChangeSliderPos(ui->red_slider, value_change);
}

void MainWindow::on_green_increase_button_clicked()
{
    constexpr int value_change = 10;

    ChangeSliderPos(ui->green_slider, value_change);
}

void MainWindow::on_green_decrease_button_clicked()
{
    constexpr int value_change = -10;

    ChangeSliderPos(ui->green_slider, value_change);
}

void MainWindow::on_blue_increase_level_clicked()
{
    constexpr int value_change = 10;

    ChangeSliderPos(ui->blue_slider, value_change);
}

void MainWindow::on_blue_decrease_level_clicked()
{
    constexpr int value_change = -10;

    ChangeSliderPos(ui->blue_slider, value_change);
}

void MainWindow::on_horizontal_reflection_button_clicked()
{
    ip_.Reflect(true);
    UpdateImageView();
}

void MainWindow::on_vertical_reflection_button_clicked()
{
    ip_.Reflect(false);
    UpdateImageView();
}

// push buttons ]

// [ sliders

void MainWindow::on_zoom_slider_valueChanged(int value)
{
    QLabel*& label = ui->zoom_percentage_label;
    label->setText(QString::number(value) + '%');
    QGraphicsView*& view = ui->pic_view;
    view->scale(static_cast<double>(value) / slider_values_.at(label),
                static_cast<double>(value) / slider_values_.at(label));
    slider_values_.at(label) = value;
}

void MainWindow::on_rotate_slider_valueChanged(int value)
{
    QLabel*& label = ui->rotate_degree_label;
    label->setText(QString::number(value) + QChar(0x00b0));
    ui->pic_view->rotate(value - slider_values_.at(label));
    slider_values_.at(label) = value;
}

void MainWindow::on_brightness_slider_valueChanged(int value)
{
    QLabel*& label = ui->brightness_level_label;
    SetColorCorrectLabelText(label, value);
    ip_.ChangeBrightness(value);
    UpdateImageView();
    slider_values_.at(label) = value;
}

void MainWindow::on_contrast_slider_valueChanged(int value)
{
    QLabel*& label = ui->contrast_level_label;
    SetColorCorrectLabelText(label, value);
    ip_.ChangeContrast(value);
    UpdateImageView();
    slider_values_.at(label) = value;
}

void MainWindow::on_red_slider_valueChanged(int value)
{
    QLabel*& label = ui->red_delta_label;
    SetColorCorrectLabelText(label, value);
    // RedDeltaChange(int value);
    ip_.ChangeRedScale(value);
    UpdateImageView();
    slider_values_.at(label) = value;
}

void MainWindow::on_green_slider_valueChanged(int value)
{
    QLabel*& label = ui->green_delta_label;
    SetColorCorrectLabelText(label, value);
    // GreenDeltaChange(int value);
    ip_.ChangeGreenScale(value);
    UpdateImageView();
    slider_values_.at(label) = value;
}

void MainWindow::on_blue_slider_valueChanged(int value)
{
    QLabel*& label = ui->blue_delta_label;
    SetColorCorrectLabelText(label, value);
    // BlueDeltaChange(int value);
    ip_.ChangeBlueScale(value);
    UpdateImageView();
    slider_values_.at(label) = value;
}

// sliders ]

// [ upper menu

void MainWindow::on_open_action_triggered()
{
    file_path_ = QFileDialog::getOpenFileName(this, tr("Open File"),
                                              "C:/Users/Leonid/Desktop", tr("Images (*.png, *.bmp, *jpg)"));

    if (!file_path_.isEmpty()) {
        ip_.SetOriginalPic(file_path_);
        SetDefault();
        UpdateImageView();
    }
}

void MainWindow::on_save_action_triggered()
{
    const QImage& image = ip_.GetCurrentPic();
    image.save(file_path_);
    ip_.SetOriginalPic(file_path_);
}

void MainWindow::on_save_as_action_triggered()
{
    QString new_file_path = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                         file_path_, tr("Images (*.png, *.bmp, *.jpg"));
    if (!new_file_path.isEmpty()) {
        file_path_ = new_file_path;
        on_save_action_triggered();
    }
}

void MainWindow::on_revert_action_triggered()
{
    SetDefault();
}

// upper menu ]

// [ radio buttons

void MainWindow::on_black_white_radio_clicked()
{
    if (ip_.HasImage()) {
        ip_.SetBlackWhite();
        UpdateImageView();
    }
    else {
        QMessageBox::critical(this, "No image", "Image has not setted. Please open the file.");
        ui->black_white_radio->setCheckable(false);
        ui->black_white_radio->setCheckable(true);
    }
}

void MainWindow::on_blur_radio_clicked()
{
    if (ip_.HasImage()) {
        ip_.SetBlur();
        UpdateImageView();
    }
    else {
        QMessageBox::critical(this, "No image", "Image has not setted. Please open the file.");
        ui->blur_radio->setCheckable(false);
        ui->blur_radio->setCheckable(true);
    }
}

void MainWindow::on_colorless_radio_clicked()
{
    if (ip_.HasImage()) {
        ip_.SetColorless();
        UpdateImageView();
    }
    else {
        QMessageBox::critical(this, "No image", "Image has not setted. Please open the file.");
        ui->colorless_radio->setCheckable(false);
        ui->colorless_radio->setCheckable(true);
    }
}

void MainWindow::on_sepia_radio_clicked()
{
    if (ip_.HasImage()) {
        ip_.SetSepia();
        UpdateImageView();
    }
    else {
        QMessageBox::critical(this, "No image", "Image has not setted. Please open the file.");
        ui->sepia_radio->setCheckable(false);
        ui->sepia_radio->setCheckable(true);
    }
}

void MainWindow::on_negative_radio_clicked()
{
    if (ip_.HasImage()) {
        ip_.SetNegative();
        UpdateImageView();
    }
    else {
        QMessageBox::critical(this, "No image", "Image has not setted. Please open the file.");
        ui->negative_radio->setCheckable(false);
        ui->negative_radio->setCheckable(true);
    }
}

// radio buttons ]

// slots }

// { private methods

void MainWindow::UpdateImageView()
{
    *pm_ = QPixmap::fromImage(ip_.GetCurrentPic());

    scene_ptr_->clear();
    scene_ptr_->addPixmap(*pm_);

    ui->pic_view->setScene(scene_ptr_.get());
}

void MainWindow::ChangeSliderPos(QSlider* slider, int value)
{
    // Если новое значение после увеличения больше максимума или минимума,
    // то присваиваем слайдеру максимум или минимум соответственно.
    // Иначе присваиваем новое значение после увеличения
    int new_value = slider->value() + value;

    if (int slider_max = slider->maximum(); new_value >= slider_max) {
        slider->setValue(slider_max);
    }
    else if (int slider_min = slider->minimum(); new_value <= slider_min) {
        slider->setValue(slider_min);
    }
    else {
        slider->setValue(new_value);
    }
}

void MainWindow::SetColorCorrectLabelText(QLabel* label, int value)
{
    QString text = (value < 0 ? "" : "+");
    text.push_back(QString::number(value));
    label->setText(text);
}

void MainWindow::SetDefault() {
    ui->zoom_slider->setValue(100);
    ui->rotate_slider->setValue(0);
    ui->brightness_slider->setValue(0);
    ui->contrast_slider->setValue(0);
    ui->red_slider->setValue(0);
    ui->green_slider->setValue(0);
    ui->blue_slider->setValue(0);

    ui->black_white_radio->setCheckable(false);
    ui->blur_radio->setCheckable(false);
    ui->sepia_radio->setCheckable(false);
    ui->negative_radio->setCheckable(false);
    ui->colorless_radio->setCheckable(false);

    ui->black_white_radio->setCheckable(true);
    ui->blur_radio->setCheckable(true);
    ui->sepia_radio->setCheckable(true);
    ui->negative_radio->setCheckable(true);
    ui->colorless_radio->setCheckable(true);

    ip_.SetDefault();
    UpdateImageView();
}

// private methods }
