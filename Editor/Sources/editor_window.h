#pragma once

#include <QMainWindow>

class editor_scene;
class QLineEdit;
class QPushButton;
class QButtonGroup;

class editor_window : public QMainWindow
{
    Q_OBJECT
public:
    editor_window();
private:
    void create_menu();
    void create_elements_buttons();
    void create_level_layout();
    void on_level_loaded();
private slots:
    void on_set_colls(const QString& str);
    void on_set_rows(const QString& str);
    void on_set_cell(const QString& str);
    
    void on_new_level();
    void on_save_level();
    void on_load_level();
    
    void on_open_elements_editor();
    void on_open_matches_editor();
    
    void on_element_button(const QString& str);
private:
    QLineEdit* m_rows_edit = nullptr;
    QLineEdit* m_colls_edit = nullptr;
    QLineEdit* m_cell_edit = nullptr;
    
    editor_scene* m_edit_scene = nullptr;
};

