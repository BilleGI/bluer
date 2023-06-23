#include "my_window.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QFuture>
#include <QtConcurrent/QtConcurrent>


#include <QGraphicsScene>
#include <QGraphicsBlurEffect>
#include <QGraphicsPixmapItem>
#include <QPainter>

#include <QFileDialog>

const int STARTPOS(0);

//Constructor

MY_WINDOW::MY_WINDOW() :  label(new QLabel), meanBlure(new QSlider(this)),
    newImage(new QPushButton("New file", this)) , saveImage(new QPushButton("Save", this)) , originalImage(new QImage)
{
    label->setAlignment(Qt::AlignCenter);
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    meanBlure->setOrientation(Qt::Horizontal);
    meanBlure->setSliderPosition(STARTPOS);
    meanBlure->setMaximum(10);

    newImage->setFixedSize(150,30);
    newImage->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    saveImage->setFixedSize(newImage->size());
    saveImage->setSizePolicy(newImage->sizePolicy());

    auto *vbox = new QVBoxLayout(this);

    auto *hbox = new QHBoxLayout;

    hbox->addWidget(newImage);
    hbox->addWidget(saveImage);

    vbox->addWidget(label);
    vbox->addWidget(meanBlure);
    vbox->addLayout(hbox);

    setLayout(vbox);
    setWindowTitle("Image blure");
}

//Methods

void MY_WINDOW::Rendering(const int& numBlure)
{
    originalImage->load(imagePath);
    QGraphicsScene scene;
    QGraphicsPixmapItem item;
    item.setPixmap(QPixmap::fromImage(*originalImage));

    auto *blur = new QGraphicsBlurEffect;
    blur->setBlurRadius(numBlure);
    item.setGraphicsEffect(blur);
    scene.addItem(&item);
    QImage result(originalImage->size(), QImage::Format_ARGB32_Premultiplied);
    result.fill(Qt::transparent);
    QPainter painter(&result);

    scene.render(&painter, QRectF(), QRect(0, 0, originalImage->width(), originalImage->height()));

    *originalImage = result;

    label->setPixmap(QPixmap::fromImage(*originalImage).scaled(label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void MY_WINDOW::bluer_effect()
{
    QObject::connect(meanBlure, &QSlider::valueChanged,this, &MY_WINDOW::newBlure);
}

void MY_WINDOW::choice_picture()
{
    QObject::connect(newImage, &QPushButton::clicked, this, &MY_WINDOW::clickedNew);
}

void MY_WINDOW::save_picture()
{
    QObject::connect(saveImage, &QPushButton::clicked, this, &MY_WINDOW::clickImage);
}

//Slots

void MY_WINDOW::newBlure(int value)
{
    if(!(label->pixmap().isNull()))
    {
//        QFuture<void> future = QtConcurrent::run(this, &MY_WINDOW::Rendering, value); не работает!!
        QFuture<void> future = QtConcurrent::run([&]{Rendering(value);});
        future.waitForFinished();
//        Rendering(value);
//    label->setPixmap(QPixmap::fromImage(*originalImage).scaled(label->size(),Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
    else
        meanBlure->setSliderPosition(0);
}

void MY_WINDOW::clickedNew()
{
    imagePath = QFileDialog::getOpenFileName(nullptr, "Select one or more files open",
                                             "./",
                                             "Images (*.png, *.jpg)");
    originalImage->load(imagePath);
    label->setPixmap(QPixmap::fromImage(*originalImage).scaled(label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void MY_WINDOW::clickImage()
{
    QString directoryPath;
    directoryPath = QFileDialog::getSaveFileName(nullptr, "Save file", "./", "Images (*.png, *.jpg)");
    if(!directoryPath.isEmpty() && !originalImage->isNull())
        originalImage->save(directoryPath);
}


