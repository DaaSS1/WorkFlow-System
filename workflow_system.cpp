#include <iostream>
#include <string>
using namespace std;

class Document
{
private:
    string name_author;
    string doc_name;
    string main_text;

public:
    Document() : name_author(""), doc_name(""), main_text("") {}
    Document(string name_author, string doc_name, string main_text) : name_author(name_author),
                                                                      doc_name(doc_name),
                                                                      main_text(main_text) {}

    void add_work_document()
    {
    }
};

class StoragePlace
{ // место хранения
private:
    int id_place;
    string name_department;

public:
    StoragePlace() : id_place(0), name_department("") {}
    StoragePlace(int id_place, string name_department) : id_place(id_place),
                                                         name_department(name_department) {}
};

class WorkGroup
{
private:
    int id_group;
    string group_name;
    string composition_group;

public:
    WorkGroup() : id_group(0), group_name(""), composition_group("") {}
    WorkGroup(int id, const string &name, const string &composition) : id_group(id),
                                                                       group_name(name),
                                                                       composition_group(composition) {}
};

class WorkDoc : public Document, public StoragePlace, public WorkGroup // Наследуется от Document, StoragePlace, WorkGroup
{
public:
    WorkDoc() : Document(), StoragePlace(), WorkGroup() {}

    WorkDoc(string name_author, string doc_name, string main_text,
            int id_place, string name_department,
            int id_group, string group_name, string composition) : Document(name_author, doc_name, main_text),
                                                                   StoragePlace(id_place, name_department),
                                                                   WorkGroup(id_group, group_name, composition) {}
};

class OrgDoc : public Document // Наследуется от Document
{
private:
    int doc_num;
    bool saining;
    bool signing;
    string doc_status;

public:
    OrgDoc() : Document(), doc_num(0), saining(false), signing(false), doc_status("") {}

    OrgDoc(string doc_name, int d_num, bool saining, bool signing, string d_status) : Document("", doc_name, ""),
                                                                                      doc_num(d_num),
                                                                                      saining(saining),
                                                                                      signing(signing),
                                                                                      doc_status(d_status) {}
};

class User
{
private:
    int id_user;
    string full_name;
    string role_in_wf_system;

public:
    User() : id_user(0), full_name(""), role_in_wf_system("") {}
    User(int id_user, string full_name, string role) : id_user(id_user),
                                                       full_name(full_name),
                                                       role_in_wf_system(role) {}

    void set_user_in_sys()
    { // .    Роль в системе документооборота (подписывающий, визирующий, автор)
    }
};

int main()
{
}