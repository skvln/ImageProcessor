#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <memory>
#include <QPixmap>

class ImageProcessor
{
public:

    ImageProcessor() = default;

    ~ImageProcessor();

    void SetOriginalPic(QImage* pm);
    void SetOriginalPic(const QString& file_path);

    const QImage& GetOriginalPic() const;
    const QImage& GetCurrentPic() const;

    bool HasImage() const;

    void SetDefault();

    // Отражение изображения
    void Reflect(bool orientation);

    // Обработка ползунков
    void ChangeBrightness(int value);
    void ChangeContrast(int value);
    void ChangeRedScale(int value);
    void ChangeGreenScale(int value);
    void ChangeBlueScale(int value);

    // Применение фильтров
    void SetBlackWhite();
    void SetBlur();
    void SetColorless();
    void SetSepia();
    void SetNegative();

private:

    QImage* original_image_ = nullptr;
    QImage* current_image_ = nullptr;

};

#endif // IMAGEPROCESSOR_H
