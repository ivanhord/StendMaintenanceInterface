#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_updateTimer(new QTimer(this))
{
    ui->setupUi(this);

    // Настройка адаптивности
    setMinimumSize(800, 600);
    // Настройка политик изменения размеров
    ui->centralWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->headerFrame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);



    // Переключение вкладок
    connect(ui->tabWidget, &QTabWidget::currentChanged, this, [this](int index) {
        Q_UNUSED(index);
        // Логика при переключении вкладок
    });

    // Проверка загрузки ресурсов
    qDebug() << "Доступные ресурсы:" << QDir(":/").entryList();
    // Проверка существования ресурса
    qDebug() << "Resource exists:" << QFile(":/icons/assets/alert.png").exists();
    qDebug() << "Resource exists:" << QFile("d:/Projects/StendMaintenanceInterface/assets/alert.png").exists();

    // Явная загрузка изображения
    /*QPixmap alertPixmap("d:/Projects/StendMaintenanceInterface/icons/assets/alert.svg");
    if(alertPixmap.isNull()) {
        qDebug() << "Ошибка: Не удалось загрузить :/icons/assets/alert.png";

        // Проверка физического наличия файла
        QString physicalPath = QCoreApplication::applicationDirPath() + "/../icons/assets/alert.svg";
        if(QFile::exists(physicalPath)) {
            qDebug() << "Файл существует по пути:" << physicalPath;
            alertPixmap.load(physicalPath);
        }
    }
    if(!alertPixmap.isNull()) {
        ui->alertIconLabel->setPixmap(alertPixmap.scaled(32, 24, Qt::KeepAspectRatio));
    } else {
            qDebug() << "Альтернативная загрузка также не удалась";
            // Установите запасной вариант
            ui->alertIconLabel->setText("⚠");
            ui->alertIconLabel->setStyleSheet("color: orange; font-size: 20px;");

    }*/

    // Настройка индикатора записи
    ui->recordIndicator->setFixedSize(16, 4);

    // Обновление даты/времени
    connect(m_updateTimer, &QTimer::timeout, this, [this]() {
        ui->dateTimeLabel->setText(QDateTime::currentDateTime().toString("hh:mm<br>dd.MM.yyyy"));
    });
    m_updateTimer->start(1000);
    /*// Автоматическое изменение размера шрифта даты/времени
    connect(m_updateTimer, &QTimer::timeout, this, [this]() {
        int fontSize = qMax(8, width() / 100);
        QString style = QString("font-size: %1px;").arg(fontSize);
        ui->dateTimeLabel->setStyleSheet(style);
    });*/


    // Инициализация состояния
    ui->recordIndicator->setStyleSheet(
        "background-color: #00aa00; border: 1px solid #007700; border-radius: 2px;");
    // Для тестирования адаптивности можно добавить кнопку изменения размера
    QPushButton *testResizeBtn = new QPushButton("Тест адаптивности", this);
    connect(testResizeBtn, &QPushButton::clicked, this, [this]() {
        static bool large = true;
        if (large) {
            resize(600, 450);
        } else {
            resize(1024, 768);
        }
        large = !large;
    });
    ui->verticalLayout->addWidget(testResizeBtn);
}

MainWindow::~MainWindow()
{
    delete ui;
}
