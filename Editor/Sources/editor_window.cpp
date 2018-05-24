#include <QMenu>
#include <QMenuBar>
#include <QLabel>
#include <QPushButton>
#include <QGroupBox>
#include <QComboBox>
#include <QAction>
#include <QGridLayout>
#include <QLineEdit>
#include <QString>
#include <QHBoxLayout>
#include <QIcon>
#include <QButtonGroup>
#include <QSignalMapper>

#include "editor_window.h"
#include "editor_scene.h"
#include "editor.h"

editor_window::editor_window()
{    
    create_menu();
    create_elements_buttons();
    create_level_layout();
    on_level_loaded();
}

void editor_window::create_menu()
{
    auto file_menu = menuBar()->addMenu("&File");
    auto edit_menu = menuBar()->addMenu("&Edit");
    
    auto new_action = file_menu->addAction("&Create");
    auto save_action = file_menu->addAction("&Save");
    auto load_action = file_menu->addAction("&Load");
    
    auto elements_action = edit_menu->addAction("&Open elements editor");
    auto matches_action = edit_menu->addAction("&Open matches editor");
    
    new_action->setStatusTip(tr("Create a new Level"));
    save_action->setStatusTip(tr("Save current Level"));
    load_action->setStatusTip(tr("Load Level"));
    
    connect(new_action, &QAction::triggered, this, &editor_window::on_new_level);
    connect(save_action, &QAction::triggered, this, &editor_window::on_save_level);
    connect(load_action, &QAction::triggered, this, &editor_window::on_load_level);
    connect(elements_action, &QAction::triggered, this, &editor_window::on_open_elements_editor);
    connect(matches_action, &QAction::triggered, this, &editor_window::on_open_matches_editor);
    
    menuBar()->setNativeMenuBar(false);
}

void editor_window::create_elements_buttons()
{
    auto elements = editor::instance().m_elements;
    
    auto group = new QGroupBox("Elements");
    auto grid = new QGridLayout;
    
    auto buttons_group = new QButtonGroup(this);
    auto mapper = new QSignalMapper(this);
    
    for (auto el : elements)
    {
        auto button = new QPushButton;
        auto icon = QIcon(editor::assets + QString(el->texture.c_str()));
        
        mapper->setMapping(button, el->type_name.c_str());
        button->setIcon(icon);
        
        buttons_group->addButton(button);
    }
    
    static const char* field_buttons[] = { "clear", "disable", "spawn" };
    
    for (auto field_button : field_buttons)
    {
        auto button = new QPushButton;
        auto icon = QIcon(editor::assets + field_button);
        
        button->setIcon(icon);
        mapper->setMapping(button, field_button);
        
        buttons_group->addButton(button);
    }
    
    int x = 0;
    int y = 0;
    
    static const int max_row = 5;

    auto buttons = buttons_group->buttons();
    
    for (auto button : buttons)
    {
        button->setIconSize(QSize(30, 30));
        button->setCheckable(true);
        
        buttons_group->addButton(button);
        
        grid->addWidget(button, y, x++);
        
        if (x >= max_row)
        {
            x = 0;
            ++y;
        }
        
        connect(button, SIGNAL(clicked(bool)), mapper, SLOT(map()));
    }

    group->setLayout(grid);
    group->resize(240, 105);
    group->move(0, menuBar()->size().height());
    
    layout()->addWidget(group);
    connect(mapper, SIGNAL(mapped(QString)), this, SLOT(on_element_button(QString)));
}

void editor_window::on_element_button(const QString& str)
{
    m_edit_scene->m_selected_item = str.toStdString();
}

void editor_window::create_level_layout()
{
    auto group = new QGroupBox("Field:");
    auto grid = new QGridLayout;
    
    auto rows_label = new QLabel("Rows:");
    auto colls_label = new QLabel("Colls:");
    auto cell_label = new QLabel("Cell:");
    
    m_rows_edit = new QLineEdit;
    m_colls_edit = new QLineEdit;
    m_cell_edit = new QLineEdit;
    
    grid->addWidget(rows_label, 0, 0);
    grid->addWidget(m_rows_edit, 0, 1);
    grid->addWidget(colls_label, 1, 0);
    grid->addWidget(m_colls_edit, 1, 1);
    grid->addWidget(cell_label, 2, 0);
    grid->addWidget(m_cell_edit, 2, 1);
    
    group->setLayout(grid);
    group->resize(120, 120);
    
    group->move(390, menuBar()->size().height());
    
    connect(m_rows_edit, SIGNAL(textChanged(const QString&)), this, SLOT(on_set_colls(const QString&)));
    connect(m_colls_edit, SIGNAL(textChanged(const QString&)), this, SLOT(on_set_rows(const QString&)));
    connect(m_cell_edit, SIGNAL(textChanged(const QString&)), this, SLOT(on_set_cell(const QString&)));
    
    layout()->addWidget(group);
}

void editor_window::on_set_colls(const QString& str)
{
    m_edit_scene->m_colls = str.toInt();
}

void editor_window::on_set_rows(const QString& str)
{
    m_edit_scene->m_rows = str.toInt();
}

void editor_window::on_set_cell(const QString& str)
{
    m_edit_scene->m_cell_size = str.toInt();
}

void editor_window::on_new_level()
{
    editor::instance().new_scene();
    on_level_loaded();
}

void editor_window::on_load_level()
{
    if (editor::instance().load_scene())
        on_level_loaded();
}

void editor_window::on_save_level()
{
    editor::instance().save_scene();
}

void editor_window::on_level_loaded()
{
    m_edit_scene = editor::instance().m_current_scene;
    
    assert(m_edit_scene);
    
    m_rows_edit->setText(QString::number(m_edit_scene->m_rows));
    m_colls_edit->setText(QString::number(m_edit_scene->m_colls));
    m_cell_edit->setText(QString::number(m_edit_scene->m_cell_size));
}

void editor_window::on_open_elements_editor()
{

}

void editor_window::on_open_matches_editor()
{
    
}
