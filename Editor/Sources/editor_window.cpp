#include <QMenu>
#include <QMenuBar>
#include <QLabel>
#include <QGroupBox>
#include <QComboBox>
#include <QAction>
#include <QGridLayout>
#include <QLineEdit>
#include <QFileDialog>
#include <QFile>
#include <QIODevice>
#include <QMessageBox>
#include <QTextStream>

#include "editor_window.h"
#include "editor_scene.h"

editor_window::editor_window(editor_scene* scene) : m_scene(scene)
{
    assert(scene);
    
    create_menu();
    create_level_layout();
    on_level_loaded();
}

void editor_window::create_menu()
{
    auto file_menu = menuBar()->addMenu("&Level");
    auto new_action = file_menu->addAction("&Create");
    auto save_action = file_menu->addAction("&Save");
    auto load_action = file_menu->addAction("&Load");
    
    new_action->setStatusTip(tr("Create a new level"));
    save_action->setStatusTip(tr("Save current level"));
    load_action->setStatusTip(tr("Load level"));
    
    connect(new_action, &QAction::triggered, this, &editor_window::on_new_level);
    connect(save_action, &QAction::triggered, this, &editor_window::on_save_level);
    connect(load_action, &QAction::triggered, this, &editor_window::on_load_level);
    
    menuBar()->setNativeMenuBar(false);
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
    m_scene->m_colls = str.toInt();
}

void editor_window::on_set_rows(const QString& str)
{
    m_scene->m_rows = str.toInt();
}

void editor_window::on_set_cell(const QString& str)
{
    m_scene->m_cell_size = str.toInt();
}

void editor_window::on_new_level()
{
    m_scene = editor_scene::create<editor_scene>();
    engine::director::instance().run_scene(m_scene);
    on_level_loaded();
}

void editor_window::on_load_level()
{
    auto file_name = QFileDialog::getOpenFileName(this,
                                                     tr("Save Level"), "",
                                                     tr("Level (*.json);;All Files (*)"));
    
    if (!file_name.isEmpty())
    {
        QFile file(file_name);
        
        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::information(this, tr("Unable to open file"),
                                     file.errorString());
            return;
        }
        
        QTextStream in(&file);
        QString data;
        
        in >> data;
        
        if (m_scene->from_json(data.toStdString()))
            on_level_loaded();
    }
}

void editor_window::on_save_level()
{
    auto file_name = QFileDialog::getSaveFileName(this,
                                                    tr("Save Level"), "",
                                                    tr("Level (*.json);;All Files (*)"));
    
    if (!file_name.isEmpty())
    {
        QFile file(file_name);
        if (!file.open(QIODevice::WriteOnly))
        {
            QMessageBox::information(this, tr("Unable to open file"),
                                     file.errorString());
            return;
        }
        QTextStream out(&file);
        out << QString(m_scene->to_json().c_str());
    }
}

void editor_window::on_level_loaded()
{
    m_rows_edit->setText(QString::number(m_scene->m_rows));
    m_colls_edit->setText(QString::number(m_scene->m_colls));
    m_cell_edit->setText(QString::number(m_scene->m_cell_size));
}
