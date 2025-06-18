#include "optimizer.h"
#include <QRegularExpression>
#include <QMessageBox>
#include <QSettings>
#include <QFileDialog>
#include <QFile>
#include <QDir>
#include <QPainter>

Optimizer::Optimizer(QWidget *parent)
    : QMainWindow(parent) {
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
    setFont(QFont("黑体", 10));
    setFixedSize(360, 440);
    setWindowIcon(QIcon(":/logo.ico"));
    setWindowTitle("音符特效/背景动画 禁用工具");
    init_QGroupBox();
    init_QLabel();
    init_QTextBrowser();
    init_QPushButton();
    init_QToolButton();
    init_QCheckBox();
}

Optimizer::~Optimizer() {
    QMessageBox::information(nullptr, "感谢使用！", "感谢使用！\n作者：三両落葉\nQQ: 1455645352\n\
邮箱：tyz.err.233@gmail.com\n发布地址：https://github.com/AstroNot233/Chuni-SFX-Disabler",
        QMessageBox::Ok, QMessageBox::Ok);
    delete bga;
    delete sfx;
    delete main_dir;
    delete option_dir;
    delete data_dir;
    delete main_dir_text;
    delete option_dir_text;
    delete data_dir_text;
    delete browse;
    delete browse_option;
    delete browse_data;
    delete bga_res;
    delete bga_del;
    delete sfx_res;
    delete sfx_del;
    for (auto p : option)
        delete p;
}

void Optimizer::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    painter.drawPixmap(10, 150, 200, 260, QPixmap(":/res/penguin.png"));
}

void Optimizer::init_QGroupBox() {
    bga = new QGroupBox("背景动画", this);
    sfx = new QGroupBox("音符特效", this);
    bga->setGeometry(220, 140, 120, 30);
    sfx->setGeometry(220, 180, 120, 245);
}

void Optimizer::init_QLabel() {
    main_dir_text = new QLabel("主路径", this);
    option_dir_text = new QLabel("option", this);
    data_dir_text = new QLabel("data", this);
    main_dir_text->setGeometry(10, 20, 40, 20);
    option_dir_text->setGeometry(10, 60, 40, 20);
    data_dir_text->setGeometry(10, 100, 40, 20);
    main_dir_text->setAlignment(Qt::AlignmentFlag::AlignRight);
    option_dir_text->setAlignment(Qt::AlignmentFlag::AlignRight);
    data_dir_text->setAlignment(Qt::AlignmentFlag::AlignRight);
}

void Optimizer::init_QTextBrowser() {
    main_dir = new QTextBrowser(this);
    option_dir = new QTextBrowser(this);
    data_dir = new QTextBrowser(this);
    main_dir->setGeometry(60, 15, 240, 30);
    option_dir->setGeometry(60, 55, 240, 30);
    data_dir->setGeometry(60, 95, 240, 30);
    main_dir->setText("单击“浏览”按钮选择游戏根目录");
    option_dir->setText("`option` 与 `data` 会自动识别");
    data_dir->setText("若识别有误则请手动选择");
}

void Optimizer::init_QPushButton() {
    browse = new QPushButton("浏览", this);
    browse_option = new QPushButton("浏览", this);
    browse_data = new QPushButton("浏览", this);
    browse->setGeometry(300, 15, 50, 30);
    browse_option->setGeometry(300, 55, 50, 30);
    browse_data->setGeometry(300, 95, 50, 30);
    browse->setCursor(Qt::PointingHandCursor);
    browse_option->setCursor(Qt::PointingHandCursor);
    browse_data->setCursor(Qt::PointingHandCursor);
    browse_option->setEnabled(false);
    browse_data->setEnabled(false);
    connect(browse, &QPushButton::clicked, this, &Optimizer::handle_browse_clicked);
    connect(browse_option, &QPushButton::clicked, this, &Optimizer::handle_browse_option_clicked);
    connect(browse_data, &QPushButton::clicked, this, &::Optimizer::handle_browse_data_clicked);
}

void Optimizer::init_QToolButton() {
    bga_res = new QToolButton(bga);
    bga_del = new QToolButton(bga);
    sfx_res = new QToolButton(sfx);
    sfx_del = new QToolButton(sfx);
    bga_res->setCursor(Qt::PointingHandCursor);
    bga_del->setCursor(Qt::PointingHandCursor);
    sfx_res->setCursor(Qt::PointingHandCursor);
    sfx_del->setCursor(Qt::PointingHandCursor);
    bga_res->setGeometry(90, 0, 20, 20);
    bga_del->setGeometry(70, 0, 20, 20);
    sfx_res->setGeometry(90, 0, 20, 20);
    sfx_del->setGeometry(70, 0, 20, 20);
    bga_res->setIcon(QIcon(":/res/restore.ico"));
    bga_del->setIcon(QIcon(":/res/delete.ico"));
    sfx_res->setIcon(QIcon(":/res/restore.ico"));
    sfx_del->setIcon(QIcon(":/res/delete.ico"));
    bga_res->setEnabled(false);
    bga_del->setEnabled(false);
    sfx_res->setEnabled(false);
    sfx_del->setEnabled(false);
    connect(bga_res, &QToolButton::clicked, this, &Optimizer::handle_bga_res_clicked);
    connect(bga_del, &QToolButton::clicked, this, &Optimizer::handle_bga_del_clicked);
    connect(sfx_res, &QToolButton::clicked, this, &Optimizer::handle_sfx_res_clicked);
    connect(sfx_del, &QToolButton::clicked, this, &Optimizer::handle_sfx_del_clicked);
}

void Optimizer::init_QCheckBox() {
    const QString ALLNOTES_NAMES[]
        {"EXTAP", "AIR", "AIRHOLD", "TAP", "HOLD", "SLIDE", "FLICK", "DAMAGE"};
    for (auto i : ALLNOTES) {
        option[i] = new QCheckBox(ALLNOTES_NAMES[i], sfx);
        option[i]->setGeometry(10, 45 + 25 * i, 100, 16);
        option[i]->setChecked(false);
        option[i]->setEnabled(false);
        option[i]->setCursor(Qt::PointingHandCursor);
        connect(option[i], &QCheckBox::clicked, this, &Optimizer::handle_option_clicked);
    }
    checkall = new QCheckBox("全选", sfx);
    checkall->setGeometry(10, 20, 100, 16);
    checkall->setTristate(true);
    checkall->setCheckState(Qt::Unchecked);
    checkall->setEnabled(false);
    checkall->setCursor(Qt::PointingHandCursor);
    connect(checkall, &QCheckBox::clicked, this, &Optimizer::handle_checkall_clicked);
}

void Optimizer::handle_checkall_clicked() {
    switch (checkall->checkState()) {
    case Qt::PartiallyChecked:
        checkall->setCheckState(Qt::Checked);
        [[fallthrough]];
    case Qt::Checked:
        for (auto i : option)
            i->setChecked(true);
        break;
    case Qt::Unchecked:
        for (auto i : option)
            i->setChecked(false);
        break;
    }
}

void Optimizer::handle_browse_clicked() {
    QString dir_select;
    for (;;) {
        dir_select = QFileDialog::getExistingDirectory(this,
            "选择游戏根目录", ".", QFileDialog::ShowDirsOnly);
        if (dir_select.isEmpty())
            return;
        if (!QFile::exists(dir_select + "\\data")) {
            if (QMessageBox::critical(browse, "路径有误",
                "当前目录不包含 `data` 目录，请重新选择游戏所在根目录。",
                QMessageBox::Retry | QMessageBox::Cancel,
                QMessageBox::Cancel) == QMessageBox::Retry)
                continue;
            return;
        }
        if (!QFile::exists(dir_select + "\\bin")) {
            if (QMessageBox::critical(browse, "路径有误",
                "当前目录不包含 `bin` 目录，请重新选择游戏所在根目录。",
                QMessageBox::Retry | QMessageBox::Cancel,
                QMessageBox::Cancel) == QMessageBox::Retry)
                continue;
            return;
        }
        if (!QFile::exists(dir_select + "\\bin\\segatools.ini")) {
            if (QMessageBox::critical(browse, "路径有误",
                "`bin` 目录不包含 `segatools.ini` 文件，请重新选择游戏所在根目录。",
                QMessageBox::Retry | QMessageBox::Cancel,
                QMessageBox::Cancel) == QMessageBox::Retry)
                continue;
            return;
        }
        main_dir->setText(dir_select);
        data_path = QDir::cleanPath(dir_select + "\\data\\");
        option_path = QSettings(dir_select + "\\bin\\segatools.ini",
            QSettings::IniFormat, nullptr).value("vfs/option").toString();
        if (!QFile::exists(option_path))
            option_path = QDir::cleanPath(dir_select + "\\bin\\" + option_path);
        if (QMessageBox::question(browse, "识别是否正确？",
            "option-> " + option_path + "\ndata-> " + data_path,
            QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes) == QMessageBox::Yes) {
            option_dir->setText(option_path);
            data_dir->setText(data_path);
            browse_option->setEnabled(false);
            browse_data->setEnabled(false);
            break;
        } else {
            QMessageBox::information(browse, "路径有误",
                "请手动选择 `option` 目录与 `data` 目录。", QMessageBox::Ok, QMessageBox::Ok);
            browse_option->setEnabled(true);
            browse_data->setEnabled(true);
            browse_option->setCursor(Qt::PointingHandCursor);
            browse_data->setCursor(Qt::PointingHandCursor);
            return;
        }
    }
    path_confirm();
}

void Optimizer::handle_browse_option_clicked() {
    QString dir_select;
    dir_select = QFileDialog::getExistingDirectory(this,
        "选择 `option` 目录", main_dir->toPlainText(), QFileDialog::ShowDirsOnly);
    if (dir_select.isEmpty())
        return;
    option_path = dir_select;
    option_dir->setText(option_path);
    if (!data_path.isEmpty())
        path_confirm();
}

void Optimizer::handle_browse_data_clicked() {
    QString dir_select;
    dir_select = QFileDialog::getExistingDirectory(this,
        "选择 `data` 目录", main_dir->toPlainText(), QFileDialog::ShowDirsOnly);
    if (dir_select.isEmpty())
        return;
    data_path = dir_select;
    data_dir->setText(data_path);
    if (!option_path.isEmpty())
        path_confirm();
}

void Optimizer::path_confirm() {
    for (auto i : option) {
        i->setEnabled(true);
        i->setChecked(true);
        i->setCursor(Qt::PointingHandCursor);
    }
    checkall->setEnabled(true);
    checkall->setCheckState(Qt::Checked);
    checkall->setCursor(Qt::PointingHandCursor);
    bga_res->setEnabled(true);
    bga_del->setEnabled(true);
    sfx_res->setEnabled(true);
    sfx_del->setEnabled(true);
}

void Optimizer::handle_option_clicked() {
    int state(0);
    for (auto i : ALLNOTES)
        state |= (option[i]->isChecked() << i);
    switch (state) {
    case 0:
        checkall->setCheckState(Qt::Unchecked);
        break;
    case 255:
        checkall->setCheckState(Qt::Checked);
        break;
    default:
        checkall->setCheckState(Qt::PartiallyChecked);
        break;
    }
}

void Optimizer::handle_bga_res_clicked() {
    QDir dir_A000;
    dir_A000.setCurrent(data_path + "\\A000\\DISABLED");
    if (dir_A000.exists("stage"))
        dir_A000.rename("stage", "..\\stage");
    QDir dir_option(option_path);
    dir_option.setFilter(QDir::Dirs | QDir::NoSymLinks);
    const auto &subdir_list(dir_option.entryInfoList());
    for (const auto &subdir : subdir_list) {
        if (dir_option.exists(subdir.fileName() + "\\DISABLED\\stage"))
            dir_option.rename(subdir.fileName() + "\\DISABLED\\stage",
                subdir.fileName() + "\\stage");
    }
}

void Optimizer::handle_bga_del_clicked() {
    QDir dir_A000(data_path + "\\A000");
    if (!dir_A000.exists("DISABLED"))
        dir_A000.mkdir("DISABLED");
    if (dir_A000.exists("stage"))
        dir_A000.rename("stage", "DISABLED\\stage");
    QDir dir_option(option_path);
    dir_option.setFilter(QDir::Dirs | QDir::NoSymLinks);
    const auto &subdir_list(dir_option.entryInfoList());
    for (const auto &subdir : subdir_list) {
        if (dir_option.exists(subdir.fileName() + "\\stage")) {
            if (!subdir.exists("DISABLED"))
                dir_option.mkdir(subdir.fileName() + "\\DISABLED");
            dir_option.rename(subdir.fileName() + "\\stage",
                subdir.fileName() + "\\DISABLED\\stage");
        }
    }
}

void Optimizer::handle_sfx_res_clicked() {
    QDir dir_acroarts(data_path + "\\acroarts\\DISABLED");
    const auto &subfile_list_arcroarts(dir_acroarts.entryList());
    for (const auto& subfile : subfile_list_arcroarts)
        dir_acroarts.rename(subfile, "..\\" + subfile);
    QDir dir_uvc(data_path + "\\uvc\\DISABLED");
    const auto &subfile_list_uvc(dir_uvc.entryList());
    for (const auto& subfile : subfile_list_uvc)
        dir_uvc.rename(subfile, "..\\" + subfile);
}

void Optimizer::handle_sfx_del_clicked() {
    static const QRegularExpression ACROARTS_NAMES[8] {
        QRegularExpression{"^chu_ef_ex.+$", QRegularExpression::CaseInsensitiveOption},
        QRegularExpression{"^(?!chu_ef_airhold)(?=chu_ef_air).+$", QRegularExpression::CaseInsensitiveOption},
        QRegularExpression{"^chu_ef_airhold.+$", QRegularExpression::CaseInsensitiveOption},
        QRegularExpression{"^chu_ef_tap_(bomb|reaction).+$", QRegularExpression::CaseInsensitiveOption},
        QRegularExpression{"^chu_ef_hold.+$", QRegularExpression::CaseInsensitiveOption},
        QRegularExpression{"^chu_ef_slide.+$", QRegularExpression::CaseInsensitiveOption},
        QRegularExpression{"^chu_ef_flick.+$", QRegularExpression::CaseInsensitiveOption},
        QRegularExpression{"^chu_ef_dmg.+$", QRegularExpression::CaseInsensitiveOption}};
    static const QRegularExpression UVC_NAMES[8] {
        QRegularExpression{"^ntt_extap.+$", QRegularExpression::CaseInsensitiveOption},
        QRegularExpression{"^ntt_air.+$", QRegularExpression::CaseInsensitiveOption},
        QRegularExpression{"^ntt_ah.+$", QRegularExpression::CaseInsensitiveOption},
        QRegularExpression{"^ntt_tap.+$", QRegularExpression::CaseInsensitiveOption},
        QRegularExpression{"^ntt_hold.+$", QRegularExpression::CaseInsensitiveOption},
        QRegularExpression{"^ntt_slide.+$", QRegularExpression::CaseInsensitiveOption},
        QRegularExpression{"^ntt_flick.+$", QRegularExpression::CaseInsensitiveOption},
        QRegularExpression{"^ntt_dmg.+$", QRegularExpression::CaseInsensitiveOption}};
    static const QRegularExpression UVC_CHU("^chu_mark_number.+$", QRegularExpression::CaseInsensitiveOption);
    QDir dir_acroarts(data_path + "\\acroarts");
    if (!dir_acroarts.exists("DISABLED"))
        dir_acroarts.mkdir("DISABLED");
    const auto &subfile_list_acroarts(dir_acroarts.entryList());
    for (auto note : ALLNOTES)
        if (option[note]->isChecked())
            for (const auto &subfile : subfile_list_acroarts)
                if (ACROARTS_NAMES[note].match(subfile).hasMatch())
                    dir_acroarts.rename(subfile, "DISABLED\\" + subfile);
    QDir dir_uvc(data_path + "\\uvc");
    if (!dir_uvc.exists("DISABLED"))
        dir_uvc.mkdir("DISABLED");
    const auto &subfile_list_uvc(dir_uvc.entryList());
    for (auto note : ALLNOTES)
        if (option[note]->isChecked())
            for (const auto &subfile : subfile_list_uvc)
                if (UVC_NAMES[note].match(subfile).hasMatch())
                    dir_uvc.rename(subfile, "DISABLED\\" + subfile);
    for (const auto &subfile : subfile_list_uvc)
        if (UVC_CHU.match(subfile).hasMatch())
            dir_uvc.rename(subfile, "DISABLED\\" + subfile);
}
