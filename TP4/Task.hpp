#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <Eigen/Dense>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Task{
public:
    int identifier;
    int size;
    Eigen::MatrixXd a;
    Eigen::VectorXd b;
    Eigen::VectorXd x;
    double time;

    // Constructeur
    Task(int id = 0, int s = 0) : identifier(id), size(s), time(0.0){
        if (size > 0){
            a = Eigen::MatrixXd::Random(size, size);
            b = Eigen::VectorXd::Random(size);
            x = Eigen::VectorXd::Zero(size);
        }
    }

    // Méthode de travail (résolution du système)
    void work(){
        auto start = std::chrono::high_resolution_clock::now();
        // Résolution Ax = b
        x = a.colPivHouseholderQr().solve(b);

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        time = elapsed.count();
    }

    // Sérialisation vers JSON
    json to_json() const{
        // On convertit les matrices Eigen en vecteurs standard pour le JSON
        std::vector<std::vector<double>> a_vec(size, std::vector<double>(size));
        std::vector<double> b_vec(size);
        std::vector<double> x_vec(size);

        for (int i = 0; i < size; ++i){
            b_vec[i] = b(i);
            if (x.size() > 0) x_vec[i] = x(i);
            for (int j = 0; j < size; ++j) {
                a_vec[i][j] = a(i, j);
            }
        }
        return json{
            {"identifier", identifier},
            {"size", size},
            {"a", a_vec},
            {"b", b_vec},
            {"x", x_vec},
            {"time", time}
        };
    }

    // Désérialisation depuis JSON
    static Task from_json(const json& j){
        Task t;
        t.identifier = j.at("identifier").get<int>();
        t.size = j.at("size").get<int>();
        t.time = j.at("time").get<double>();

        auto a_vec = j.at("a").get<std::vector<std::vector<double>>>();
        auto b_vec = j.at("b").get<std::vector<double>>();
        auto x_vec = j.at("x").get<std::vector<double>>();

        t.a.resize(t.size, t.size);
        t.b.resize(t.size);
        t.x.resize(t.size);

        for (int i = 0; i < t.size; ++i){
            t.b(i) = b_vec[i];
            t.x(i) = x_vec[i];
            for (int j = 0; j < t.size; ++j){
                t.a(i, j) = a_vec[i][j];
            }
        }
        return t;
    }
};