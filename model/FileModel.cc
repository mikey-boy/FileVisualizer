#include "FileModel.h"
#include <iostream>

// ----------------- FileModel ----------------- //

FileModel::FileModel() {
    root = new FileModelNode("Songs", NULL, true);
    root->AppendChild(new FileModelNode("Long time coming", "okay", root, false));
    root->AppendChild(new FileModelNode("Ohio", "pretty good", root, false));
    root->AppendChild(new FileModelNode("Harvest moon", "great", root, false));
}

unsigned int FileModel::GetColumnCount() const{
    return 2;
}

wxString FileModel::GetColumnType(unsigned int col) const{
    return "string";
}

void FileModel::GetValue(wxVariant &variant, const wxDataViewItem &item, unsigned int col) const {
    FileModelNode *node = (FileModelNode *) item.GetID();
    switch (col) {
    case 0:
        variant = node->title;
        break;
    case 1:
        variant = node->value;
        break;
    }
}

bool FileModel::SetValue(const wxVariant &variant, const wxDataViewItem &item, unsigned int col) {
    return true;
}

bool FileModel::IsContainer(const wxDataViewItem &item) const {
     FileModelNode *node = (FileModelNode *) item.GetID();
     if (node == NULL) {
        return false;
     }
     return node->container;
}

wxDataViewItem FileModel::GetParent(const wxDataViewItem &item) const {
    // the invisible root node has no parent
    if (!item.IsOk())
        return wxDataViewItem(0);

    FileModelNode *node = (FileModelNode *) item.GetID();

    // "Songs" also has no parent
    if (node == root)
        return wxDataViewItem(0);

    return wxDataViewItem((void*) node->GetParent());
}

unsigned int FileModel::GetChildren(const wxDataViewItem &parent,wxDataViewItemArray &array) const {
    FileModelNode *node = (FileModelNode *) parent.GetID();
    if (!node)
    {
        array.Add( wxDataViewItem( (void*) root ) );
        return 1;
    }

    if (node->GetChildCount() == 0)
    {
        return 0;
    }

    unsigned int count = node->GetChildCount();
    for (unsigned int pos = 0; pos < count; pos++) {
        FileModelNode *child = node->GetChild(pos);
        array.Add(wxDataViewItem((void*) child));
    }
    return count;
}

// ----------------- FileModelNode ----------------- //

FileModelNode::FileModelNode(wxString title, wxString value, FileModelNode * parent, bool container):
    title(title), value(value), container(container), parent(parent) {}

FileModelNode::FileModelNode(wxString title, FileModelNode * parent, bool container):
    title(title), value(""), container(container), parent(parent) {}

FileModelNode::~FileModelNode() {
    for (auto & node: children)
        delete node;
}

FileModelNode *FileModelNode::GetParent() { return parent; }

FileModelNode *FileModelNode::GetChild(unsigned int pos) { return children[pos]; }

unsigned int FileModelNode::GetChildCount() { return children.size(); }

void FileModelNode::AppendChild(FileModelNode * child) {
    children.push_back(child);
}
