#include <iostream>
#include <string>
#include <vector>
using namespace std;

class User {
    int id_user;
    string full_name, role_in_wf_system;
public:
    User() : id_user(0), full_name(""), role_in_wf_system("") {}
    User(int id, string name, string role) : id_user(id), full_name(name), role_in_wf_system(role) {}

    void set_user_in_sys(int id, string name, string role) {
        id_user = id; full_name = name; role_in_wf_system = role;
    }

    string get_name() const { return full_name; }
    string get_role() const { return role_in_wf_system; }

    void display() const {
        cout << "User: " << full_name << " (" << role_in_wf_system << ")\n";
    }
};

class Document {
    string name_author, doc_name, main_text;
public:
    Document() : name_author(""), doc_name(""), main_text("") {}
    Document(string author, string name, string text)
        : name_author(author), doc_name(name), main_text(text) {}

    virtual void add_document() {
        cout << "Document '" << doc_name << "' added by " << name_author << ".\n";
    }

    string get_doc_name() const { return doc_name; }
};

class StoragePlace {
    int id_place;
    string name_department;
    vector<string> documents;
public:
    StoragePlace() : id_place(0), name_department("") {}
    StoragePlace(int id, string name) : id_place(id), name_department(name) {}

    void add_document_name(string doc_name) {
        documents.push_back(doc_name);
    }

    void view_all_documents() const {
        cout << "\nStorage in department: " << name_department << "\nDocuments:\n";
        for (const auto& d : documents) cout << "- " << d << endl;
    }
};

class WorkGroup {
    int id_group;
    string group_name;
    vector<User> composition_group;
public:
    WorkGroup() : id_group(0), group_name("") {}
    WorkGroup(int id, string name) : id_group(id), group_name(name) {}

    void add_user_to_group(const User& user) {
        composition_group.push_back(user);
    }

    void view_users_in_group() const {
        cout << "\nGroup '" << group_name << "' Members:\n";
        for (const auto& u : composition_group) u.display();
    }
};

class WorkDoc : public Document, public StoragePlace, public WorkGroup {
public:
    WorkDoc(string author, string name, string text,
            int sid, string dept, int gid, string gname)
        : Document(author, name, text),
          StoragePlace(sid, dept),
          WorkGroup(gid, gname) {}

    void editing_wd() { cout << "Editing work doc...\n"; }
    void delete_wd() { cout << "Work doc deleted.\n"; }
};

class OrgDoc : public Document {
    int doc_num;
    bool saining = false, signing = false;
    string doc_status;
    User signer, approver;
public:
    OrgDoc(string name, int num, string status)
        : Document("", name, ""), doc_num(num), doc_status(status) {}

    void set_signer(User u) { signer = u; }
    void set_approver(User u) { approver = u; }

    void signing_the_doc(User u) {
        if (u.get_role() == "signer") {
            signing = true;
            cout << u.get_name() << " signed the document.\n";
        }
    }

    void document_approval(User u) {
        if (u.get_role() == "approver") {
            saining = true;
            cout << u.get_name() << " approved the document.\n";
        }
    }

    void print_status() const {
        cout << "\nOrgDoc status: " << doc_status
             << ", Signed: " << (signing ? "Yes" : "No")
             << ", Approved: " << (saining ? "Yes" : "No") << endl;
    }
};

// ⬇️ MAIN — взаимодействие через пользовательский ввод
int main() {
    string name, role, doc_name, text, dept, group;
    int id, doc_id;

    cout << "Enter author name: "; getline(cin, name);
    cout << "Enter doc name: "; getline(cin, doc_name);
    cout << "Enter main text: "; getline(cin, text);

    cout << "Enter storage department: "; getline(cin, dept);
    cout << "Enter group name: "; getline(cin, group);

    WorkDoc wd(name, doc_name, text, 1, dept, 1, group);
    wd.add_document(); wd.add_document_name(doc_name);

    cout << "\nAdd user to group.\nEnter user name: "; getline(cin, name);
    cout << "Enter role (author/signer/approver): "; getline(cin, role);
    User u1(1, name, role);
    wd.add_user_to_group(u1);

    OrgDoc od(doc_name, 1001, "Pending");
    if (role == "signer") od.set_signer(u1);
    else if (role == "approver") od.set_approver(u1);

    wd.view_all_documents(); wd.view_users_in_group();

    if (role == "signer") od.signing_the_doc(u1);
    else if (role == "approver") od.document_approval(u1);

    od.print_status();
    return 0;
}
