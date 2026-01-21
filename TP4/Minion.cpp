#include <iostream>
#include <thread>
#include <cpr/cpr.h>
#include "Task.hpp"

int main(){
    std::cout << "Minion pret a travailler..." << std::endl;
    while (true){
        cpr::Response r = cpr::Get(cpr::Url{"http://localhost:8000/task_queue"});
        
        if(r.status_code == 200 && !r.text.empty() && r.text != "null"){
            try{
                json j_task = json::parse(r.text);
                Task t = Task::from_json(j_task);

                std::cout << "Minion traite la tache " << t.identifier << std::endl;

                t.work();

                json j_res = t.to_json();
                cpr::Response r_post = cpr::Post(
                    cpr::Url{"http://localhost:8000/result_queue"},
                    cpr::Body{j_res.dump()},
                    cpr::Header{{"Content-Type", "application/json"}}
                );

            }catch (const std::exception& e){
                std::cerr << "Erreur lors du traitement :" << e.what() << std::endl;
            }
        }else{
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }
    return 0;
}