/*
 * Gastaldi Paolo
 * lab2
 * 27-04-2020
 *
 * smart pointer
 * template
 */

#include <iostream>
#include <memory>
#include <fstream>
#include <iostream>
#include <filesystem>
#include "Directory.h"
namespace fs = std::filesystem;

int main() {

    /*
     * -- PARTE 1 ---
     */
    {
        /*
         * domanda #1:
         * contenitore scelto per i figli: unordered_map
         * per i figli meglio un ptr_shared, esistono i link fisici
         */

        /*
         * domanda #2:
         * per il puntatore alla directory padre: weak_ptr
         * così se distruggo il padre, distruggo anche tutte le directory figlie in automatico
         * (come l'esempio della lista fatta a lezione)
         */

        /*
         * domanda #3:
         * make_shared dovrebbe fungere da named constructor
         * crea internamente un oggetto del tipo passato come parametro al template
         */

        /*
         * domanda #4:
         * devo ereditare da enable_shared_of_this
         * e poi utilizzare shared_of_this per creare uno shared_ptr
         */

        /*
         * domanda #5:
         * il costruttore viene richiamato 2 volte
         * il distruttore viene richiamato 1 sola volta
         * make_shared crea un nuovo oggetto classe del tipo del template, i parametri passati a make_shared vengono inoltrati al costruttore
         */

        /*
         * domanda #6:
         * implementare addDirectory
         */

        /*
         * domanda #7:
         * implementare getRoot
         */
        auto root = Directory::getRoot();

        /*
         * domanda #8:
         * implementare ls, get
         */
        std::cout << "--- test addDirectory" << std::endl;

        root->addDirectory("usr");
        root->addDirectory("proc");
        auto home_dir = root->addDirectory("home");
        auto paolo_dir = home_dir->addDirectory("paolo");
        auto doc_dir = paolo_dir->addDirectory("documents");
        doc_dir->addDirectory("programmazione di sistema");
        doc_dir->addDirectory("applicazioni web I");
        doc_dir->addDirectory("software engineering I");
        doc_dir->addDirectory("formal languages and compilers");
        paolo_dir->addDirectory("images");

        std::cout << "--- test ls" << std::endl;
        root->ls(4);

        std::cout << "--- test get" << std::endl;
        auto dir = root->getDir(".");
        dir = dir->getDir("home");
        dir = dir->getDir("paolo");

        std::cout << "--- test get + ls" << std::endl;
        dir = root->getDir(".");
        dir = root->getDir("home");
        dir = dir->getDir("paolo");
        dir = dir->getDir("documents");
        dir->ls();
        dir = dir->getDir("programmazione di sistema");
        dir->ls();

        std::cout << "--- test folder not found" << std::endl;
        dir = dir->getDir("AAA");}

    /*
     * -- PARTE 2 ---
     */
    {
        /*
         * domanda #9:
         * implementare la classe Base
         */

        /*
         * domanda #10:
         * implementare la classe Directory
         */

        /*
         * domanda #11:
         * implementare la classe File
         */

        // otteniamo la stessa root prima creata
        std::shared_ptr<Directory> root = Directory::getRoot();

        auto alfa = root->addDirectory("alfa");
        alfa->addDirectory("beta")->addFile("beta1", 100);
        alfa->getDir("beta")->addFile("beta2", 200);

        std::cout << "--- test ls" << std::endl;
        alfa->getDir("..")->ls();

        std::cout << "--- test remove" << std::endl;
        auto ret_val = alfa->remove("beta");
        std::cout << "remove return value: " << ret_val << std::endl;
        root->ls(0);

        /*
         * in totale: 12 elementi devono ancora essere distrutti
         * prima: 15 creati (13 Directory, 2 File), 3 rimossi (1 Directory, 2 File) con la precedente "remove")
         */

        /*
         * domanda #12:
         * testing con recursive_directory_iterator
         */
        root = Directory::getRoot();
        auto curr_dir = root;
        std::string test_dir = ".";

        auto it = fs::recursive_directory_iterator(test_dir); // iterator
        int curr_depth = 0;
        for(auto curr_item: it){
            // auto size = p.file_size(); // solo per le directory

            // per non gestire il path esplicitamente
            while(curr_depth > it.depth()) {
                curr_dir = curr_dir->getDir("..");
                curr_depth--;
            }

            if(curr_item.is_directory()) {
                curr_dir = curr_dir->addDirectory(curr_item.path().filename());
                curr_depth++;
            }
            else
                curr_dir->addFile(curr_item.path().filename(), curr_item.file_size());
        }

        root->ls();
    }

    std::cout << "--- end ---" << std::endl;

    return 0;
}
