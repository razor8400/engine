#pragma once

#include <QMainWindow>

class editor_scene;
class QLineEdit;

class editor_window : public QMainWindow
{
    Q_OBJECT
public:
    editor_window(editor_scene* scene);
private:
    void create_menu();
    void create_level_layout();
    void on_level_loaded();
private slots:
    void on_set_colls(const QString& str);
    void on_set_rows(const QString& str);
    void on_set_cell(const QString& str);
    
    void on_new_level();
    void on_save_level();
    void on_load_level();
private:
    editor_scene* m_scene = nullptr;
    QLineEdit* m_rows_edit = nullptr;
    QLineEdit* m_colls_edit = nullptr;
    QLineEdit* m_cell_edit = nullptr;
};

