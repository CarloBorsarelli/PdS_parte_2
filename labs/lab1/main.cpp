/*
 * Gastaldi Paolo
 * 30-03-2020
 * prog II (Malnati)
 * lab1
 * */

#include <iostream>
#include "message.h"
#include "DurationLogger.h"
#include "MessageStore.h"

const bool debug = true;

static int cont = 0;
inline void check_objects(std::string comment=""){
    if constexpr(debug) std::cout << "Message::get_cont() #" << std::to_string(cont++) << ": " << Message::get_cont() << " - " << comment << std::endl;
}

int main(){
    {
        check_objects();
        {
            std::cout << "--- test 0 ---" << std::endl;
            Message m1{10};
            Message m2{20};
            std::cout << m1 << std::endl << m2 << std::endl;

            check_objects();

            /*
             * ATTENZIONE: le stampe a video influiscono molto sui tempi misurati
             * */

            std::cout << "--- test 1 ---" << std::endl;
            Message buff1[10]; // nello stack
            Message *buff2 = new Message[10]; // nello heap
            std::cout << "&buff1: " << &buff1 << ", buff1: " << buff1 << std::endl;
            std::cout << "&buff2: " << &buff2 << ", buff2: " << buff2 << std::endl;
            // #1: nel primo caso viene tutto allocato nello stack, nel secondo caso nell'heap (il riferimento rimane nello stack)

            check_objects("attesi 22 oggetti");

            std::cout << "--- test 2 ---" << std::endl;
            // #2: viene invocato il costruttore vuoto

            std::cout << "--- test 3 ---" << std::endl;
            // delete[] buff1; // allocato nello stack, no delete
            // delete[] buff2;
            // #3: è necessario fare la delete solo del buff2
            // ERRATA

            std::cout << "--- test 4 ---" << std::endl;
            std::cout << "&(buff1[0]): " << &(buff1[0]) << ", buff1[0]: " << buff1[0] << std::endl;
            buff1[0] = Message{100}; // l'oggetto, subito dopo la copia, viene subito distrutto > viene chiamato il distruttore
            std::cout << "&(buff1[0]): " << &(buff1[0]) << ", buff1[0]: " << buff1[0] << std::endl;
            // #4: avviene la copia nell'oggetto già esistente

            check_objects();

            std::cout << "--- test 5 ---" << std::endl;
            // #5: senza costruttore di default ci sono errori alla compilazione quando bisogna creare buff1

            std::cout << "--- test 6 ---" << std::endl;
            // #6: problema analogo a #5

            std::cout << "--- test 7 ---" << std::endl;
            // #7: non compila

            std::cout << "--- test 8 ---" << std::endl;
            // #8: no, viene copiato il riferimento di un oggetto (data) che poi viene distrutto assieme all'oggetto

            std::cout << "--- test 9 ---" << std::endl;
            // #9: disegnare i blocchi di memoria su carta di #8

            std::cout << "--- test 10 ---" << std::endl;
            for(auto &i: buff1)
                i = std::move(Message{1000000}); // 1MB = 1e6 caratteri
            check_objects("oggetti pronti, attesi 22 oggetti");

            {
                DurationLogger dl{"operatore di assegnazione"};
                for (int i = 0; i < 10; i++)
                    buff2[i] = buff1[1];
            }
            check_objects("operatore di assegnazione eseguito, attesi 22 oggetti");
            {
                DurationLogger dl{"operatore di assegnazione per movimento"};
                for (int i = 0; i < 10; i++)
                    buff2[i] = std::move(buff1[i]);
            }
            check_objects("operatore di assegnazione per movimento eseguito, attesi 22 oggetti");

            // operatore di assegnazione = 3366
            // operatore di assegnazione per movimento = 3
            // #10: con l'operatore di assegnazione per movimento si aumentano notevolmente le performance
            // danno valori descrescenti


            std::cout << "--- test 11 ---" << std::endl;
            // #11: DA RISPONDERE

            delete[] buff2;
        }
        check_objects("attesi 0 oggetti");
        {
            std::cout << "--- test 12 ---" << std::endl;

            MessageStore ms{10};
            Message *buff3 = new Message[100];

            check_objects("attesi 100+10 = 110 oggetti");
            {
                DurationLogger dl{"messageStore adding"};
                for (int i = 0; i < 100; i++) {
                    buff3[i] = std::move(Message{1000000});
                    ms.add(buff3[i]); // copia
                    if constexpr(debug) std::cout << "Message::get_count(): " << Message::get_cont() << ", MessageStore::get_valid_items(): " << ms.get_valid_items() << std::endl;
                }
            }
            check_objects("oggetti aggiunti alla lista, attesi 100+100 = 200 oggetti");
            {
                DurationLogger dl{"messageStore removing"};
                for (int i = 0; i < 100; i += 2) {
                    if(!ms.remove(buff3[i].getId()))
                        std::cout << "MessageStore::remove(): invalid item (id: " << std::to_string(buff3[i].getId()) << ")" << std::endl;
                    if constexpr(debug) std::cout << "Message::get_count(): " << Message::get_cont() << ", MessageStore::get_valid_items(): " << ms.get_valid_items() << std::endl;
                }
            }
            check_objects("metà degli oggetti rimossi dalla lista, attesi 100+100 = 200 oggetti (non ancora compact)");
            {
                DurationLogger dl{"messageStore compacting"};
                if constexpr(debug)  std::cout << "Message::get_cont(): " << Message::get_cont() << std::endl;
                if constexpr(debug)  std::cout << "MessageStore::get_dim(): " << ms.get_dim() << std::endl;
                ms.compact();
                if constexpr(debug)  std::cout << "Message::get_cont(): " << Message::get_cont() << std::endl;
                if constexpr(debug)  std::cout << "MessageStore::get_dim(): " << ms.get_dim() << std::endl;
            }
            check_objects("lista compattata, attesi 100+50 = 150 oggetti");
            // #12: per ottimizzare la riallocazione:
            // - costruttore di copia del buffer
            // - usare l'assegnazione di copia per movimento (come è stato fatto in MessageStore::compact)

            delete[] buff3;
        }
        check_objects("attesi 0 oggetti");

        /*
         * Message *get(long id):
         * restituisce l'originale come puntatore
         * in caso l'elemento non venga trovato: nullptr
         *
         * Message get(long id):
         * ne restituisce una copia
         * difficile decidere cosa fare in caso l'elemento non venga trovato
         *
         * Message &get(long id):
         * restituisce l'originale come riferimento
         *
         * std::optional<Message> get(long id):
         * restituisce una copia
         * gestione semplificata nel caso l'elemento non venga trovato
         *
         * void get(int id, Message message):
         * non posso ritornare nulla
         *
         * void get(int id, Message *message):
         * si può fare una copia in message se viene trovato
         *
         * void get(int id, Message **message):
         * possiamo modificare il referimento ed effettuare la copia
         *
         * void get(int id, Message &message):
         * possiamo modificare l'originale con il valore trovato
         *
         * void get(int id, const Message &message):
         * non è possibile restituire un risultato della ricerca
         */
    }
    check_objects("fine, attesi 0 oggetti");

    return(0);
}
