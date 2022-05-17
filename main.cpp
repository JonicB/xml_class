#include <iostream>
#include <string>
#include "tinyxml2.h"
#include "sqlite3.h"

class XmlClass{
    private:
        tinyxml2::XMLDocument doc;
        std::string fileName;

    public:

        XmlClass(std::string xmlName){
            fileName = xmlName;
            doc.LoadFile(fileName.c_str());
        }

        ~XmlClass(){
            doc.SaveFile(fileName.c_str());
        }

        const char * getElement(std::string elementName){
            tinyxml2::XMLElement* element = doc.RootElement()->FirstChildElement(elementName.c_str());
            if (element != NULL)
                return element->GetText();
            return "";
        }

        void setElement(std::string elementName, std::string value){
            tinyxml2::XMLElement* root = doc.RootElement();
            if (root->FirstChildElement(elementName.c_str()))
                root->FirstChildElement(elementName.c_str())->SetText(value.c_str());
            else
                root->InsertNewChildElement(elementName.c_str())->SetText(value.c_str());
        }
};

int main() {
    XmlClass example("C:\\Users\\Женя\\Desktop\\Работа\\Аладдин\\bd\\prov.xml");
    for (int i=0; i<100; i++){
        example.setElement("User"+std::to_string(i),"Password"+std::to_string(i));
    }

    sqlite3 *db;
    int rc = sqlite3_open_v2("C:\\Users\\Женя\\Desktop\\Работа\\Аладдин\\bd\\test.db", &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);

    std::string sql = "CREATE TABLE IF NOT EXISTS user("  \
      "id INTEGER PRIMARY KEY AUTOINCREMENT," \
      "login TEXT NOT NULL," \
      "password TEXT NOT NULL);";
    sqlite3_stmt *query;
    sqlite3_prepare_v2(db,sql.c_str(),-1,&query,NULL);
    if (sqlite3_step(query) != SQLITE_DONE) {
        std::cout << "Didn't Create Table!\n"<<sqlite3_errmsg(db) << std::endl;
    }

    sql = "INSERT INTO user (login, password) VALUES(?,?);";
    for(int i=0; i<100; i++){
        std::string user = "User"+std::to_string(i);
        const char * password = example.getElement(user);
        sqlite3_prepare_v2(db, sql.c_str(), -1, &query, NULL);
        sqlite3_bind_text(query, 1, user.c_str(), user.length(), NULL);
        sqlite3_bind_text(query, 2, password, strlen(password), NULL);
        if (sqlite3_step(query) != SQLITE_DONE) {
            std::cout << "Didn't insert values\n"<<sqlite3_errmsg(db) << std::endl;
        }
    }

    sql = "SELECT * FROM user WHERE user.id=?";
    sqlite3_prepare_v2(db, sql.c_str(), -1, &query, NULL);
    sqlite3_bind_int(query, 1, 10);
    int r;

    while(1) {
        r = sqlite3_step(query);
        if (r == SQLITE_ROW) {
            int id;
            const unsigned char *login;
            const unsigned char *password;
            id = sqlite3_column_int(query, 0);
            login = sqlite3_column_text(query, 1);
            password = sqlite3_column_text(query, 2);
            std::cout << "id: " << id << std::endl << "login: " << login << std::endl << "password: " << password
                      << std::endl;
        } else if (r == SQLITE_DONE) {
            break;
        } else {
            std::cout << "Can't read data from table" << std::endl;
        }
    }

    sqlite3_close(db);

    return 0;
}
