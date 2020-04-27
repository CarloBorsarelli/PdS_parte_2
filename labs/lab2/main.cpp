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
#include "Directory.h"

int main() {

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

    auto dir = root->get(".");
    dir = dir->get("home");
    dir = dir->get("paolo");

    std::cout << "--- test get + ls" << std::endl;

    dir = root->get(".");
    dir = root->get("home");
    dir = dir->get("paolo");
    dir = dir->get("documents");
    dir->ls();
    dir = dir->get("programmazione di sistema");
    dir->ls();


    std::cout << "--- test folder not found" << std::endl;
    dir = dir->get("AAA");

    return 0;
}
