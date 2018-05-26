#include "editor.h"
#include "editor_scene.h"
#include "editor_window.h"

#include "nlohmann/json.hpp"

#include <QFileDialog>
#include <QFile>
#include <QIODevice>
#include <QMessageBox>
#include <QTextStream>
#include <QWidget>

static const char* elements = "assets/configs/elements.json";
const QString editor::assets = "EditorAssets/";

editor& editor::instance()
{
    static editor e;
    return e;
}

void editor::new_scene()
{
    m_current_scene = editor_scene::create<editor_scene>();
    engine::director::instance().run_scene(m_current_scene);
}

void editor::save_scene()
{
    auto file_name = QFileDialog::getSaveFileName(m_main_window,
                                                  "Save Level", "",
                                                  "Level (*.json);;All Files (*)");
    
    if (!file_name.isEmpty())
    {
        QFile file(file_name);
        if (!file.open(QIODevice::WriteOnly))
        {
            QMessageBox::information(m_main_window, "Unable to open file",
                                     file.errorString());
            return;
        }
        QTextStream out(&file);
        out << QString(m_current_scene->to_json().c_str());
    }
}

bool editor::load_scene()
{
    auto file_name = QFileDialog::getOpenFileName(m_main_window,
                                                  "Save Level", "",
                                                  "Level (*.json);;All Files (*)");
    
    if (!file_name.isEmpty())
    {
        QFile file(file_name);
        
        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::information(m_main_window, "Unable to open file",
                                     file.errorString());
            return false;
        }
        
        QTextStream in(&file);
        QString data;
        
        in >> data;
        
        return m_current_scene->from_json(data.toStdString());
    }
    
    return false;
}

void editor::load_elements()
{
    QFile file(elements);
    
    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream in(&file);
        
        engine::logger() << " [editor] read elements config:";
        
        QString data = in.readAll();
        
        engine::logger() << data.toStdString();
        
        auto json = nlohmann::json::parse(data.toUtf8());
        auto elements = json["elements"];
        
        for (auto elem : elements)
        {
            auto obj = new editor_element();
            
            obj->texture = elem["texture"].get<std::string>();
            obj->type_name = elem["type"].get<std::string>();
            obj->layer = (element_layer)elem["layer"].get<int>();
            obj->dropable = elem["dropable"].get<bool>();
            m_elements.push_back(obj);
        }
    }
}

editor_element* editor::find_element(const std::string& type_name) const
{
    auto it = std::find_if(m_elements.begin(), m_elements.end(), [type_name](editor_element* e)
    {
        return type_name == e->type_name;
    });
    
    if (it != m_elements.end())
        return *it;
    
    return nullptr;
}
