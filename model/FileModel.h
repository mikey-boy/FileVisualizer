#include <vector>
#include "wx/dataview.h"

class FileModelNode {
public:
    wxString title;
    wxString value;
    bool container;

    FileModelNode(wxString title, wxString value, FileModelNode * parent, bool container);
    FileModelNode(wxString title, FileModelNode * parent, bool container);
    virtual ~FileModelNode();

    void AppendChild(FileModelNode * child);
    FileModelNode * GetParent();
    FileModelNode * GetChild(unsigned int);
    unsigned int GetChildCount();

private:
    FileModelNode *parent;
    std::vector<FileModelNode *> children;
};

class FileModel: public wxDataViewModel {
public:
    FileModel();
    virtual ~FileModel() {};

    virtual unsigned int GetColumnCount() const;
    virtual wxString GetColumnType(unsigned int col) const;
    virtual void GetValue(wxVariant &variant, const wxDataViewItem &item, unsigned int col) const;
    virtual bool SetValue(const wxVariant &variant, const wxDataViewItem &item, unsigned int col);
    virtual bool IsContainer(const wxDataViewItem &item) const;
    virtual wxDataViewItem GetParent(const wxDataViewItem &item) const;
    virtual unsigned int GetChildren(const wxDataViewItem &parent,wxDataViewItemArray &array) const;

private:
    FileModelNode *root;
};
