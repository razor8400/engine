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
#include <QIcon>

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
    
    int x = 0;
    int y = 0;
    
    static int max_row = 5;
    
    for (auto el : elements)
    {
        if (x >= max_row)
        {
            x = 0;
            ++y;
        }
        
        auto button = new QPushButton;
        auto icon = QIcon(QString("EditorAssets/") + QString(el->texture.c_str()));
        
        button->setIcon(icon);
        button->setIconSize(QSize(40, 40));
        button->resize(60, 60);
        
        grid->addWidget(button, y, x);
        
        ++x;
    }
    
    group->setLayout(grid);
    group->resize(240, 20 + 60 * (y + 1));
    group->move(0, menuBar()->size().height());
    
    layout()->addWidget(group);
}

void editor_window::create_level_layout()
{
    auto group = new QGroupBox;
    auto grid = new QGridLayout;
    
    auto rows_label = new QLabel(tr("Rows:"));
    auto colls_label = new QLabel(tr("Colls:"));
    auto cell_label = new QLabel(tr("Cell:"));
    
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
