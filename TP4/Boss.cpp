#include <iostream>
#include <thread>
#include <cpr/cpr.h>
#include "Task.hpp"

int main(){
    std::cout << "Boss démarre..." << std::endl;
    
    for (int i=0; i < 10; ++i){
        Task t(i, 300);
        std::cout << "Boss envoie la tache " << i << std::endl;

        json j = t.to_json();
        cpr::Response r = cpr::Post(
            cpr::Url{"http://localhost:8000/task_queue"},
            cpr::Body{j.dump()},
            cpr::Header{{"Content-Type", "application/json"}}
        );

        if (r.status_code != 200){
            std::cerr << "Erreur lors de l'envoi de la tache " << i << std::endl;
        }
    }
    std::cout << "Toutes les taches sont envoyées." << std::endl;

    int received_count = 0;
    while (received_count < 10){
        cpr::Response r = cpr::Get(cpr::Url{"http://localhost:8000/result_queue"});
        
        if (r.status_code == 200 && !r.text.empty() && r.text != "null"){
            try{
                json j_res = json::parse(r.text);
                Task res = Task::from_json(j_res);
                
                std::cout << "Boss a reçu le résultat de la tache " 
                          << res.identifier 
                          << " (Temps calcul : " << res.time << std::endl;
                
                received_count++;
            }catch (const std::exception& e){
                std::cerr << "Erreur de parsing JSON :" << e.what() << std::endl;
            }
        }else{
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    }
    return 0;
}