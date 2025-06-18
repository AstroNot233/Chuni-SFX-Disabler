#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include <QMainWindow>
#include <QGroupBox>
#include <QLabel>
#include <QTextBrowser>
#include <QPushButton>
#include <QToolButton>
#include <QCheckBox>
#include <QRadioButton>
#include <QPaintEvent>

class Optimizer : public QMainWindow {
    Q_OBJECT

public:
    Optimizer(QWidget *parent = nullptr);
    ~Optimizer();

private:
    QGroupBox *bga, *sfx;
    QLabel *main_dir_text, *option_dir_text, *data_dir_text;
    QTextBrowser *main_dir, *option_dir, *data_dir;
    QPushButton *browse, *browse_option, *browse_data;
    QToolButton *bga_res, *bga_del, *sfx_res, *sfx_del;
    QCheckBox *checkall, *option[8];
    QString option_path, data_path;

    enum Notes {extap, air, airhold, tap, hold, slide, flick, damage}
        constexpr static ALLNOTES[]{extap, air, airhold, tap, hold, slide, flick, damage};

private slots:
    void handle_checkall_clicked();
    void handle_browse_clicked();
    void handle_browse_option_clicked();
    void handle_browse_data_clicked();
    void handle_bga_res_clicked();
    void handle_bga_del_clicked();
    void handle_sfx_res_clicked();
    void handle_sfx_del_clicked();
    void handle_option_clicked();
    void paintEvent(QPaintEvent*) override;

private:
    void init_QGroupBox();
    void init_QLabel();
    void init_QTextBrowser();
    void init_QPushButton();
    void init_QToolButton();
    void init_QCheckBox();
    void path_confirm();
};
#endif // OPTIMIZER_H
