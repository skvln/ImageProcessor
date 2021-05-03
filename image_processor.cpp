#include "image_processor.h"

#define TO_DOUBLE(x) static_cast<double>(x)
#define TO_INT(x) static_cast<int>(x)
#define PIXEL_ITER for (int x = 0; x < current_image_->width(); ++x) { \
    for (int y = 0; y < current_image_->height(); ++y) {
#define PIXEL_ITER_END }}

// { constructors, destructors

ImageProcessor::~ImageProcessor()
{
    if (original_image_) delete original_image_;
    if (current_image_) delete current_image_;
}

// constructors, destructors }

// { public methods

// [ setters

void ImageProcessor::SetOriginalPic(QImage* image)
{
    if (!original_image_) {
        original_image_ = image;
    }
    else {
        delete original_image_;
        original_image_ = image;
    }
    if (!current_image_) {
        current_image_ = new QImage(*original_image_);
    }
    else {
        delete current_image_;
        current_image_ = new QImage(*original_image_);
    }
}

void ImageProcessor::SetOriginalPic(const QString& file_path)
{
    SetOriginalPic(new QImage(file_path));
}

// setters ]

// [ getters

const QImage& ImageProcessor::GetOriginalPic() const
{
    return *original_image_;
}

const QImage& ImageProcessor::GetCurrentPic() const
{
    return *current_image_;
}

// getters ]

// [ checkers

bool ImageProcessor::HasImage() const
{
    return current_image_;
}

// checkers ]

// [ default

void ImageProcessor::SetDefault()
{
    if (current_image_) *current_image_ = GetOriginalPic();
}

// default ]

// [ reflection

void ImageProcessor::Reflect(bool orientation)
{
    // При orientation == true: отражение по горизонтали
    // Иначе: отражение по вертикали
    *current_image_ = current_image_->mirrored(orientation, !orientation);
}

// reflection ]

// [ sliders

void ImageProcessor::ChangeBrightness(int value)
{
    auto change_color_brightness = [](int old_value, int delta) {
        int new_value = old_value + delta;
        new_value = new_value > 255 ? 255 : (new_value < 0 ? 0 : new_value);
        return new_value;
    };

    PIXEL_ITER
    QColor old_pixel = original_image_->pixel(x, y);

    int new_red = change_color_brightness(old_pixel.red(), value);
    int new_green = change_color_brightness(old_pixel.green(), value);
    int new_blue = change_color_brightness(old_pixel.blue(), value);
    QColor new_pixel(new_red, new_green, new_blue);

    current_image_->setPixelColor(x, y, new_pixel);
    PIXEL_ITER_END
}

void ImageProcessor::ChangeContrast(int value)
{
    double contrast = (100. + value) / 100.;

    contrast = contrast * contrast;

    auto change_color_contrast = [contrast](int old_value) {
        int new_value = TO_INT(((TO_DOUBLE(old_value) / 255. - 0.5) * contrast + 0.5) * 255.);
        new_value = new_value > 255 ? 255 : (new_value < 0 ? 0 : new_value);
        return new_value;
    };

    PIXEL_ITER
    QColor old_pixel = original_image_->pixel(x, y);

    int new_red = change_color_contrast(old_pixel.red());
    int new_green = change_color_contrast(old_pixel.green());
    int new_blue = change_color_contrast(old_pixel.blue());
    QColor new_pixel(new_red, new_green, new_blue);

    current_image_->setPixelColor(x, y, new_pixel);
    PIXEL_ITER_END
}

void ImageProcessor::ChangeRedScale(int value)
{
    PIXEL_ITER
    QColor old_original_pixel = original_image_->pixel(x, y);
    QColor old_current_pixel = current_image_->pixel(x, y);

    int new_red = old_original_pixel.red() + value;
    new_red = new_red > 255 ? 255 : (new_red < 0 ? 0 : new_red);

    QColor new_pixel(new_red, old_current_pixel.green(), old_current_pixel.blue());

    current_image_->setPixelColor(x, y, new_pixel);
    PIXEL_ITER_END
}

void ImageProcessor::ChangeGreenScale(int value)
{
    PIXEL_ITER
    QColor old_original_pixel = original_image_->pixel(x, y);
    QColor old_current_pixel = current_image_->pixel(x, y);

    int new_green = old_original_pixel.green() + value;
    new_green = new_green > 255 ? 255 : (new_green < 0 ? 0 : new_green);

    QColor new_pixel(old_current_pixel.red(), new_green, old_current_pixel.blue());

    current_image_->setPixelColor(x, y, new_pixel);
    PIXEL_ITER_END
}

void ImageProcessor::ChangeBlueScale(int value)
{
    PIXEL_ITER
    QColor old_original_pixel = original_image_->pixel(x, y);
    QColor old_current_pixel = current_image_->pixel(x, y);

    int new_blue = old_original_pixel.blue() + value;
    new_blue = new_blue > 255 ? 255 : (new_blue < 0 ? 0 : new_blue);

    QColor new_pixel(old_current_pixel.red(), old_current_pixel.green(), new_blue);

    current_image_->setPixelColor(x, y, new_pixel);
    PIXEL_ITER_END
}

// sliders ]

// [ filters

void ImageProcessor::SetBlackWhite()
{
    int sep = 255 / 9 * 7;

    PIXEL_ITER
    QColor old_pixel = original_image_->pixel(x, y);
    int sum = old_pixel.red() + old_pixel.green() + old_pixel.blue();
    int channel = sum > sep ? 255 : 0;
    current_image_->setPixelColor(x, y, QColor(channel, channel, channel));
    PIXEL_ITER_END
}

void ImageProcessor::SetBlur()
{
    PIXEL_ITER
    int red = 0, green = 0, blue = 0, count = 0;
    for (int sx = std::min(current_image_->width() - 1, (std::max(x - 2, 0)));
         sx <= std::min(x + 2, current_image_->width() - 1);
         ++sx)
    {
        for (int sy = std::min(current_image_->height() - 1, (std::max(y - 2, 0)));
             sy <= std::min(y + 2, current_image_->height() - 1);
             ++sy)
        {
            QColor curr_pixel = original_image_->pixel(sx, sy);
            red += curr_pixel.red();
            green += curr_pixel.green();
            blue += curr_pixel.blue();
            ++count;
        }
    }

    red /= count;
    green /= count;
    blue /= count;

    QColor new_color(red, green, blue);

    current_image_->setPixelColor(x, y, new_color);
    PIXEL_ITER_END
}

void ImageProcessor::SetColorless()
{
    PIXEL_ITER
    QColor old_pixel = original_image_->pixel(x, y);

    int channel_value = old_pixel.red() + old_pixel.green() + old_pixel.blue();
    channel_value /= 3;

    QColor new_pixel(channel_value, channel_value, channel_value);

    current_image_->setPixelColor(x, y, new_pixel);
    PIXEL_ITER_END
}

void ImageProcessor::SetSepia()
{
    PIXEL_ITER
    QColor old_pixel = original_image_->pixel(x, y);
    int old_red = old_pixel.red(), old_green = old_pixel.green(), old_blue = old_pixel.blue();

    int red = (old_red * 0.393) + (old_green * 0.769) + (old_blue * 0.189);
    int green = (old_red * 0.349) + (old_green * 0.686) + (old_blue * 0.168);
    int blue = (old_red * 0.272) + (old_green * 0.534) + (old_blue * 0.131);

    if (red > 255) red = 255;
    if (green > 255) green = 255;
    if (blue > 255) blue = 255;

    QColor new_color(red, green, blue);

    current_image_->setPixelColor(x, y, new_color);
    PIXEL_ITER_END
}

void ImageProcessor::SetNegative()
{
    PIXEL_ITER
    QColor old_pixel = original_image_->pixel(x, y);

    int red = 255 - old_pixel.red();
    int green = 255 - old_pixel.green();
    int blue = 255 - old_pixel.blue();

    QColor new_color(red, green, blue);

    current_image_->setPixelColor(x, y, new_color);
    PIXEL_ITER_END
}

// filters ]

// public methods }

// { private methods

// private methods }
