from flask import Flask, request, jsonify
import queue
import json

app = Flask(__name__)

# Les files d'attente (en mémoire)
task_queue = queue.Queue()
result_queue = queue.Queue()

@app.route('/task_queue', methods=['GET', 'POST'])
def handle_task_queue():
    if request.method == 'GET':
        try:
            # Tente de récupérer une tâche sans bloquer
            task = task_queue.get_nowait()
            return jsonify(task)
        except queue.Empty:
            # Si vide, retourne null
            return jsonify(None)
    
    elif request.method == 'POST':
        # Ajoute la tâche reçue en JSON dans la file
        task = request.json
        task_queue.put(task)
        return "OK", 200

@app.route('/result_queue', methods=['GET', 'POST'])
def handle_result_queue():
    if request.method == 'GET':
        try:
            result = result_queue.get_nowait()
            return jsonify(result)
        except queue.Empty:
            return jsonify(None)
            
    elif request.method == 'POST':
        result = request.json
        result_queue.put(result)
        return "OK", 200

if __name__ == '__main__':
    print("Serveur Proxy démarré sur http://localhost:8000")
    app.run(host='0.0.0.0', port=8000)